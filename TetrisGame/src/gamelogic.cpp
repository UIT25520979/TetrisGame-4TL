#include "../include/gamedata.h"
#include "../include/audiohandler.h"
#include "../include/effects.h"
#include <algorithm>
#include <random>
#include <math.h>

// =========================================================
// KHAI BÁO THỰC THỂ CÁC BIẾN TOÀN CỤC VÀ NỘI BỘ
// =========================================================
int currentScore = 0;
bool isGameOver = false;

char board[GRID_ROWS][GRID_COLS];
Color boardColors[GRID_ROWS][GRID_COLS];

int x, y;
float moveTimer = 0.0f;
float dropDelay = 0.5f;
bool isHardDropping = false;

Piece* currentPiece = nullptr;
Piece* nextPiece = nullptr;
int currentPieceType = -1;
int nextPieceType = -1;

std::vector<int> bag;
Texture2D backgroundSpace, backgroundJungle, backgroundEgypt;

const int NUM_COLORS = 8;
Color randomPalette[NUM_COLORS] = { RED, GREEN, BLUE, ORANGE, PURPLE, YELLOW, SKYBLUE, MAGENTA };

int totalLinesCleared = 0;
bool isPaused = false;
bool showVolumeSlider = false;
float currentVolume = 1.0f;
bool isDraggingSlider = false;
char originalCurShape[4][4];

Rectangle btnPauseRect;
Rectangle btnVolRect;
Rectangle sliderBarRect;
Rectangle btnContinueRect;
Rectangle btnMenuRect;

// ---------------------------------------------------------
// 1. CÁC HÀM XỬ LÝ LOGIC GẠCH
// ---------------------------------------------------------
bool CheckCollision(int dx, int dy) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (currentPiece->shape[i][j] != ' ') {
                int tx = x + j + dx;
                int ty = y + i + dy;
                if (tx < 1 || tx >= GRID_COLS - 1 || ty >= GRID_ROWS - 1) return true;
                if (board[ty][tx] != ' ') return true;
            }
        }
    }
    return false;
}

Piece* GenerateRandomPiece(int& outType) {
    if (bag.empty()) {
        for (int i = 0; i < 7; i++) bag.push_back(i);
        static std::random_device rd;
        static std::mt19937 g(rd());
        std::shuffle(bag.begin(), bag.end(), g);
    }
    int r = bag.back(); bag.pop_back();
    outType = r;

    Piece* p = nullptr;
    switch (r) {
    case 0: p = new PieceI(); break; case 1: p = new PieceO(); break;
    case 2: p = new PieceT(); break; case 3: p = new PieceS(); break;
    case 4: p = new PieceZ(); break; case 5: p = new PieceL(); break;
    case 6: p = new PieceJ(); break;
    }
    p->color = randomPalette[GetRandomValue(0, NUM_COLORS - 1)];
    return p;
}

void SpawnNewPiece() {
    isHardDropping = false;
    if (currentPiece) delete currentPiece;

    if (!nextPiece) nextPiece = GenerateRandomPiece(nextPieceType);

    currentPiece = nextPiece;
    currentPieceType = nextPieceType;

    if (currentPiece != nullptr) {
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                originalCurShape[i][j] = currentPiece->shape[i][j];
            }
        }
    }

    nextPiece = GenerateRandomPiece(nextPieceType);

    x = 4; y = 0;
    if (CheckCollision(0, 0)) isGameOver = true;
}

// ---------------------------------------------------------
// 2. CÁC HÀM ĐIỀU KHIỂN GAME FLOW
// ---------------------------------------------------------
void InitGame() {
    currentScore = 0;
    totalLinesCleared = 0;
    isGameOver = false;
    isPaused = false;
    showVolumeSlider = false;
    isDraggingSlider = false;

    SetMasterVolume(currentVolume);
    bag.clear();

    if (currentPiece) { delete currentPiece; currentPiece = nullptr; }
    if (nextPiece) { delete nextPiece; nextPiece = nullptr; }

    for (int i = 0; i < GRID_ROWS; i++) {
        for (int j = 0; j < GRID_COLS; j++) {
            if (i == GRID_ROWS - 1 || j == 0 || j == GRID_COLS - 1) board[i][j] = '#';
            else board[i][j] = ' ';
            boardColors[i][j] = BLANK;
        }
    }
    SpawnNewPiece();
}

void UpdateGame(float deltaTime, Difficulty level) {
    if (isGameOver) return;
    Vector2 mousePos = GetMousePosition();

    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(mousePos, btnPauseRect)) {
        isPaused = !isPaused;
        PlayGameSound(SFX_UI_CLICK);
        showVolumeSlider = false;
    }

    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(mousePos, btnVolRect)) {
        showVolumeSlider = !showVolumeSlider;
        PlayGameSound(SFX_UI_CLICK);
    }

    if (showVolumeSlider) {
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(mousePos, sliderBarRect)) {
            isDraggingSlider = true;
        }
        if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) {
            isDraggingSlider = false;
        }

        if (isDraggingSlider) {
            float newVal = (mousePos.x - sliderBarRect.x) / sliderBarRect.width;
            if (newVal < 0.0f) newVal = 0.0f;
            if (newVal > 1.0f) newVal = 1.0f;

            currentVolume = roundf(newVal * 10.0f) / 10.0f;
            SetMasterVolume(currentVolume);
        }
    }

    if (isPaused) {
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            if (CheckCollisionPointRec(mousePos, btnContinueRect)) {
                isPaused = false;
                PlayGameSound(SFX_UI_CLICK);
            }
            if (CheckCollisionPointRec(mousePos, btnMenuRect)) {
                isPaused = false;
                currentState = STATE_MENU;
                SetMasterVolume(1.0f);
                PlayGameSound(SFX_UI_CLICK);
            }
        }
        return;
    }

    float initialDelay = (level == DIFF_EASY) ? 0.8f : (level == DIFF_MEDIUM) ? 0.4f : 0.15f;
    int speedLevel = totalLinesCleared / 10;
    float calculatedDelay = initialDelay - (speedLevel * 0.05f);
    dropDelay = fmaxf(calculatedDelay, 0.05f);

    moveTimer += deltaTime;

    if (!isHardDropping) {
        if (IsKeyPressed(KEY_A) || IsKeyPressed(KEY_LEFT)) { if (!CheckCollision(-1, 0)) { x--; PlayGameSound(SFX_BLOCK_MOVE); } }
        if (IsKeyPressed(KEY_D) || IsKeyPressed(KEY_RIGHT)) { if (!CheckCollision(1, 0)) { x++; PlayGameSound(SFX_BLOCK_MOVE); } }
        if (IsKeyPressed(KEY_W) || IsKeyPressed(KEY_UP)) {
            currentPiece->rotate();
            if (CheckCollision(0, 0)) { currentPiece->rotate(); currentPiece->rotate(); currentPiece->rotate(); }
            else { PlayGameSound(SFX_BLOCK_ROTATE); }
        }
    }

    if (IsKeyPressed(KEY_SPACE) && !isHardDropping) {
        isHardDropping = true;
    }

    float currentDropSpeed = dropDelay;
    if (isHardDropping) {
        currentDropSpeed = 0.015f;
    }
    else if (IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN)) {
        currentDropSpeed = 0.05f;
    }

    if (moveTimer >= currentDropSpeed) {
        if (!CheckCollision(0, 1)) {
            y++;
            if (isHardDropping) currentScore += 2;
        }
        else {
            for (int i = 0; i < 4; i++) {
                for (int j = 0; j < 4; j++) {
                    if (currentPiece->shape[i][j] != ' ') {
                        board[y + i][x + j] = currentPiece->shape[i][j];
                        boardColors[y + i][x + j] = currentPiece->color;
                    }
                }
            }
            PlayGameSound(SFX_BLOCK_DROP);

            int linesCleared = 0;
            for (int i = GRID_ROWS - 2; i > 0; i--) {
                bool full = true;
                for (int j = 1; j < GRID_COLS - 1; j++) if (board[i][j] == ' ') full = false;
                if (full) {
                    linesCleared++;
                    CreateLineClearEffect(i - linesCleared + 1, WHITE);
                    for (int ii = i; ii > 0; ii--) {
                        for (int c = 1; c < GRID_COLS - 1; c++) {
                            board[ii][c] = board[ii - 1][c];
                            boardColors[ii][c] = boardColors[ii - 1][c];
                        }
                    }
                    for (int c = 1; c < GRID_COLS - 1; c++) {
                        board[0][c] = ' ';
                        boardColors[0][c] = BLANK;
                    }
                    i++;
                }
            }

            if (linesCleared > 0) {
                totalLinesCleared += linesCleared;
                if (linesCleared == 1) currentScore += 100;
                else if (linesCleared == 2) currentScore += 300;
                else if (linesCleared == 3) currentScore += 500;
                else if (linesCleared >= 4) currentScore += 1000;

                PlayGameSound((linesCleared >= 4) ? SFX_TETRIS_CLEAR : SFX_LINE_CLEAR);
            }
            SpawnNewPiece();
        }
        moveTimer = 0.0f;
    }
}

void UnloadGameLogic() {
    if (currentPiece) { delete currentPiece; currentPiece = nullptr; }
    if (nextPiece) { delete nextPiece; nextPiece = nullptr; }
}