#include "../include/gamedata.h"
#include "../include/monument.h"
#include <math.h>

// ---------------------------------------------------------
// 1. CÁC HÀM HỖ TRỢ VẼ BÊN TRONG (Không cần đưa ra header)
// ---------------------------------------------------------
static void Draw3DBlock(int boardX, int boardY, Color color) {
    int offsetX = (SCREEN_WIDTH - (GRID_COLS * BLOCK_SIZE)) / 2;
    int offsetY = (SCREEN_HEIGHT - (GRID_ROWS * BLOCK_SIZE)) / 2;
    int px = offsetX + boardX * BLOCK_SIZE;
    int py = offsetY + boardY * BLOCK_SIZE;

    DrawRectangle(px, py, BLOCK_SIZE, BLOCK_SIZE, color);
    DrawRectangle(px, py, BLOCK_SIZE, BLOCK_SIZE / 8, Fade(WHITE, 0.4f));
    DrawRectangle(px, py, BLOCK_SIZE / 8, BLOCK_SIZE, Fade(WHITE, 0.4f));
    DrawRectangle(px, py + BLOCK_SIZE - (BLOCK_SIZE / 8), BLOCK_SIZE, BLOCK_SIZE / 8, Fade(BLACK, 0.3f));
    DrawRectangle(px + BLOCK_SIZE - (BLOCK_SIZE / 8), py, BLOCK_SIZE / 8, BLOCK_SIZE, Fade(BLACK, 0.3f));
    DrawRectangleLines(px, py, BLOCK_SIZE, BLOCK_SIZE, Fade(BLACK, 0.5f));
}

static void DrawMiniPiece(Piece* p, int px, int py) {
    if (!p) return;
    int miniSize = 40;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (p->shape[i][j] != ' ') {
                int blockX = px + j * miniSize;
                int blockY = py + i * miniSize;

                DrawRectangle(blockX, blockY, miniSize, miniSize, p->color);
                DrawRectangle(blockX, blockY, miniSize, miniSize / 8, Fade(WHITE, 0.4f));
                DrawRectangle(blockX, blockY, miniSize / 8, miniSize, Fade(WHITE, 0.4f));
                DrawRectangle(blockX, blockY + miniSize - (miniSize / 8), miniSize, miniSize / 8, Fade(BLACK, 0.3f));
                DrawRectangle(blockX + miniSize - (miniSize / 8), blockY, miniSize / 8, miniSize, Fade(BLACK, 0.3f));
                DrawRectangleLines(blockX, blockY, miniSize, miniSize, Fade(BLACK, 0.5f));
            }
        }
    }
}

// ---------------------------------------------------------
// 2. VẼ TOÀN BỘ MÀN HÌNH GAME
// ---------------------------------------------------------
void DrawGame(GameTheme theme) {
    Texture2D currentBg = (theme == THEME_SPACE) ? backgroundSpace : ((theme == THEME_JUNGLE) ? backgroundJungle : backgroundEgypt);
    if (currentBg.id > 0) {
        DrawTexturePro(currentBg, { 0, 0, (float)currentBg.width, (float)currentBg.height }, { 0, 0, (float)SCREEN_WIDTH, (float)SCREEN_HEIGHT }, { 0, 0 }, 0.0f, WHITE);
    }

    int gridWidth = GRID_COLS * BLOCK_SIZE;
    int gridHeight = GRID_ROWS * BLOCK_SIZE;
    int offsetX = (SCREEN_WIDTH - gridWidth) / 2;
    int offsetY = (SCREEN_HEIGHT - gridHeight) / 2;

    float pulse = (sin(GetTime() * 6.0f) + 1.0f) / 2.0f;
    Color highlightColor = (theme == THEME_SPACE) ? SKYBLUE : (theme == THEME_JUNGLE) ? LIME : GOLD;
    Color glowColor = ColorAlpha(highlightColor, 0.4f + 0.5f * pulse);

    // =========================================================
    // HUD BÊN TRÁI: MISSION INFO 
    // =========================================================
    int leftFarX = 120;
    int missionW = 500;
    int missionH = 340;

    DrawRectangle(leftFarX, 100, missionW, missionH, Fade(BLACK, 0.7f));
    DrawRectangle(leftFarX, 100, missionW, missionH, Fade(highlightColor, pulse * 0.1f));
    DrawRectangleLinesEx({ (float)leftFarX - 3, 100 - 3, (float)missionW + 6, (float)missionH + 6 }, 8, Fade(highlightColor, pulse * 0.4f));
    DrawRectangleLinesEx({ (float)leftFarX, 100, (float)missionW, (float)missionH }, 5, highlightColor);

    const char* missionText = "MISSION";
    int missionFontSize = 55;

    int totalMissionW = 0;
    for (int i = 0; missionText[i] != '\0'; i++) {
        char c[2] = { missionText[i], '\0' };
        totalMissionW += MeasureText(c, missionFontSize) + 4;
    }
    totalMissionW -= 4;

    int currentMissionX = leftFarX + (missionW - totalMissionW) / 2;

    Color themePalette[5];
    if (theme == THEME_SPACE) {
        themePalette[0] = SKYBLUE; themePalette[1] = BLUE; themePalette[2] = PURPLE; themePalette[3] = VIOLET; themePalette[4] = MAGENTA;
    }
    else if (theme == THEME_JUNGLE) {
        themePalette[0] = LIME; themePalette[1] = GREEN; themePalette[2] = DARKGREEN; themePalette[3] = YELLOW; themePalette[4] = LIME;
    }
    else {
        themePalette[0] = GOLD; themePalette[1] = ORANGE; themePalette[2] = RED; themePalette[3] = MAROON; themePalette[4] = YELLOW;
    }

    int missionColorShift = (int)(GetTime() * 6.0f);

    for (int i = 0; missionText[i] != '\0'; i++) {
        char c[2] = { missionText[i], '\0' };
        Color letterColor = themePalette[(i + missionColorShift) % 5];
        DrawText(c, currentMissionX + 4, 125 + 4, missionFontSize, Fade(BLACK, 0.8f));
        DrawText(c, currentMissionX, 125, missionFontSize, letterColor);
        currentMissionX += MeasureText(c, missionFontSize) + 4;
    }

    DrawLineEx({ (float)leftFarX + 20, 190 }, { (float)leftFarX + missionW - 20, 190 }, 3, GRAY);

    Color diffColor = (currentDifficulty == DIFF_EASY) ? GREEN : (currentDifficulty == DIFF_MEDIUM) ? ORANGE : RED;
    Color themeColor = (theme == THEME_SPACE) ? PURPLE : (theme == THEME_JUNGLE) ? DARKGREEN : GOLD;

    DrawText("DIFFICULTY:", leftFarX + 30, 240, 35, LIGHTGRAY);
    DrawText(GetLevelName(currentDifficulty).c_str(), leftFarX + 290, 237, 45, diffColor);

    DrawText("BATTLEFIELD:", leftFarX + 30, 310, 35, LIGHTGRAY);
    DrawText(GetThemeName(theme).c_str(), leftFarX + 310, 307, 45, themeColor);

    // =========================================================
    // HUD BÊN TRÁI DƯỚI: CURRENT & NEXT BLOCK
    // =========================================================
    int panelW = 240;
    int panelH = 280;
    int blocksY = 470;

    auto GetCenteredOffset = [](Piece* p, int pW, int pH) -> Vector2 {
        if (!p) return { 0, 0 };
        int minX = 4, maxX = -1, minY = 4, maxY = -1;

        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                if (p->shape[i][j] != ' ') {
                    if (j < minX) minX = j;
                    if (j > maxX) maxX = j;
                    if (i < minY) minY = i;
                    if (i > maxY) maxY = i;
                }
            }
        }
        if (minX == 4) return { 0, 0 };

        int piecePixelW = (maxX - minX + 1) * BLOCK_SIZE;
        int piecePixelH = (maxY - minY + 1) * BLOCK_SIZE;

        float offsetX = (pW - piecePixelW) / 2.0f - minX * BLOCK_SIZE;
        float offsetY = 65 + (pH - 65 - piecePixelH) / 2.0f - minY * BLOCK_SIZE;
        return { offsetX, offsetY };
        };

    int curX = leftFarX;
    DrawRectangle(curX, blocksY, panelW, panelH, Fade(BLACK, 0.7f));
    DrawRectangleLinesEx({ (float)curX, (float)blocksY, (float)panelW, (float)panelH }, 4, glowColor);

    const char* curText = "CURRENT";
    DrawText(curText, curX + (panelW - MeasureText(curText, 40)) / 2, blocksY + 20, 40, highlightColor);

    if (currentPiece != nullptr) {
        char tempShape[4][4];
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                tempShape[i][j] = currentPiece->shape[i][j];
                currentPiece->shape[i][j] = originalCurShape[i][j];
            }
        }

        Vector2 curOffset = GetCenteredOffset(currentPiece, panelW, panelH);
        DrawMiniPiece(currentPiece, curX + curOffset.x, blocksY + curOffset.y);

        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                currentPiece->shape[i][j] = tempShape[i][j];
            }
        }
    }

    int nxtX = leftFarX + panelW + 20;
    DrawRectangle(nxtX, blocksY, panelW, panelH, Fade(BLACK, 0.7f));
    DrawRectangleLinesEx({ (float)nxtX, (float)blocksY, (float)panelW, (float)panelH }, 4, glowColor);

    const char* nxtText = "NEXT";
    DrawText(nxtText, nxtX + (panelW - MeasureText(nxtText, 40)) / 2, blocksY + 20, 40, highlightColor);

    if (nextPiece != nullptr) {
        Vector2 nxtOffset = GetCenteredOffset(nextPiece, panelW, panelH);
        DrawMiniPiece(nextPiece, nxtX + nxtOffset.x, blocksY + nxtOffset.y);
    }

    // =========================================================
    // HUD BÊN PHẢI: YOUR SCORE
    // =========================================================
    int rightX = offsetX + (GRID_COLS * BLOCK_SIZE) + 40;
    int scoreW = 500;
    int scoreH = 280;

    DrawRectangle(rightX, 100, scoreW, scoreH, Fade(BLACK, 0.8f));
    DrawRectangleLinesEx({ (float)rightX, 100, (float)scoreW, (float)scoreH }, 6, glowColor);

    const char* scoreTitle = "YOUR SCORE";
    int sTitleFontSize = 45;
    int sTw = MeasureText(scoreTitle, sTitleFontSize);
    int startX = rightX + (scoreW - sTw) / 2;
    int startY = 140;

    float scorePulse = (sinf(GetTime() * 4.0f) + 1.0f) / 2.0f;
    float glitchOffset = 2.0f + scorePulse * 3.0f;

    DrawText(scoreTitle, startX + 5, startY + 5, sTitleFontSize, Fade(BLACK, 0.8f));
    DrawText(scoreTitle, startX - (int)glitchOffset, startY, sTitleFontSize, Fade(RED, 0.5f + scorePulse * 0.3f));
    DrawText(scoreTitle, startX + (int)glitchOffset, startY, sTitleFontSize, Fade(SKYBLUE, 0.5f + scorePulse * 0.3f));
    DrawText(scoreTitle, startX, startY, sTitleFontSize, GOLD);
    DrawText(scoreTitle, startX, startY, sTitleFontSize, Fade(WHITE, scorePulse * 0.4f));

    const char* scoreStr = TextFormat("%07i", currentScore);
    int strW = MeasureText(scoreStr, 80);
    DrawText(scoreStr, rightX + (scoreW - strW) / 2, 220, 80, ORANGE);

    // =========================================================
    // KHUNG LINES CLEARED
    // =========================================================
    int linesY = 410;
    int linesH = 170;

    DrawRectangle(rightX, linesY, scoreW, linesH, Fade(BLACK, 0.8f));
    DrawRectangleLinesEx({ (float)rightX, (float)linesY, (float)scoreW, (float)linesH }, 6, glowColor);

    const char* linesTitle = "LINES";
    int lTw = MeasureText(linesTitle, 40);
    DrawText(linesTitle, rightX + (scoreW - lTw) / 2, linesY + 20, 40, SKYBLUE);

    const char* linesStr = TextFormat("%03i", totalLinesCleared);
    int lStrW = MeasureText(linesStr, 70);
    DrawText(linesStr, rightX + (scoreW - lStrW) / 2, linesY + 70, 70, WHITE);

    // =========================================================
    // NÚT PAUSE VÀ VOLUME 
    // =========================================================
    int btnY = linesY + linesH + 30;
    int btnSize = 90;

    btnPauseRect = { (float)rightX, (float)btnY, (float)btnSize, (float)btnSize };
    btnVolRect = { (float)(rightX + btnSize + 20), (float)btnY, (float)btnSize, (float)btnSize };

    DrawRectangleRec(btnPauseRect, btnPauseRect.y > 0 && CheckCollisionPointRec(GetMousePosition(), btnPauseRect) ? DARKGRAY : Fade(BLACK, 0.8f));
    DrawRectangleLinesEx(btnPauseRect, 4, isPaused ? GREEN : RAYWHITE);

    if (isPaused) {
        Vector2 v1 = { btnPauseRect.x + 30, btnPauseRect.y + 20 };
        Vector2 v2 = { btnPauseRect.x + 30, btnPauseRect.y + 70 };
        Vector2 v3 = { btnPauseRect.x + 70, btnPauseRect.y + 45 };
        DrawTriangle(v1, v2, v3, GREEN);
    }
    else {
        DrawRectangle(btnPauseRect.x + 25, btnPauseRect.y + 25, 14, 40, WHITE);
        DrawRectangle(btnPauseRect.x + 51, btnPauseRect.y + 25, 14, 40, WHITE);
    }

    DrawRectangleRec(btnVolRect, CheckCollisionPointRec(GetMousePosition(), btnVolRect) ? DARKGRAY : Fade(BLACK, 0.8f));
    DrawRectangleLinesEx(btnVolRect, 4, showVolumeSlider ? GOLD : RAYWHITE);

    DrawRectangle(btnVolRect.x + 20, btnVolRect.y + 35, 12, 20, WHITE);
    DrawTriangle({ btnVolRect.x + 32, btnVolRect.y + 35 }, { btnVolRect.x + 32, btnVolRect.y + 55 }, { btnVolRect.x + 55, btnVolRect.y + 20 }, WHITE);
    DrawTriangle({ btnVolRect.x + 32, btnVolRect.y + 55 }, { btnVolRect.x + 55, btnVolRect.y + 70 }, { btnVolRect.x + 55, btnVolRect.y + 20 }, WHITE);

    if (currentVolume > 0.0f) DrawCircleLines(btnVolRect.x + 65, btnVolRect.y + 45, 10, WHITE);
    if (currentVolume > 0.5f) DrawCircleLines(btnVolRect.x + 65, btnVolRect.y + 45, 16, WHITE);
    if (currentVolume == 0.0f) DrawLineEx({ btnVolRect.x + 20, btnVolRect.y + 20 }, { btnVolRect.x + 70, btnVolRect.y + 70 }, 5, RED);

    if (showVolumeSlider) {
        sliderBarRect = { (float)(btnVolRect.x + btnSize + 20), (float)(btnY + 40), 200.0f, 10.0f };
        DrawRectangleRec(sliderBarRect, DARKGRAY);

        float filledW = sliderBarRect.width * currentVolume;
        DrawRectangle(sliderBarRect.x, sliderBarRect.y, filledW, sliderBarRect.height, GOLD);

        Rectangle sliderKnobRect = { sliderBarRect.x + filledW - 10, sliderBarRect.y - 10, 20, 30 };
        DrawRectangleRec(sliderKnobRect, isDraggingSlider ? LIME : WHITE);

        const char* volText = TextFormat("%d%%", (int)(currentVolume * 100));
        DrawText(volText, sliderBarRect.x + sliderBarRect.width + 20, btnY + 30, 30, GOLD);
    }

    // =========================================================
    // KHUNG CHỮ CHẠY (MARQUEE TEXT)
    // =========================================================
    int marqueeY = btnY + btnSize + 30;
    int marqueeH = 65;

    DrawRectangle(rightX, marqueeY, scoreW, marqueeH, Fade(BLACK, 0.8f));
    DrawRectangleLinesEx({ (float)rightX, (float)marqueeY, (float)scoreW, (float)marqueeH }, 4, glowColor);

    BeginScissorMode(rightX, marqueeY, scoreW, marqueeH);

    const char* marqueeText = "SURVIVAL TETRIS GAME - HAVE A FUN PLAY ^ ^    ";
    int fontSize = 35;

    int tWidth = 0;
    for (int i = 0; marqueeText[i] != '\0'; i++) {
        char c[2] = { marqueeText[i], '\0' };
        tWidth += MeasureText(c, fontSize) + 2;
    }

    static float scrollX = 0.0f;
    if (!isPaused && !isGameOver) {
        scrollX -= 150.0f * GetFrameTime();
    }

    if (scrollX <= -tWidth) scrollX = 0;

    Color rainbow[] = { RED, ORANGE, GOLD, LIME, SKYBLUE, VIOLET, MAGENTA };
    int colorShift = (int)(GetTime() * 4.0f);

    for (int copy = 0; copy < 2; copy++) {
        float currentPosX = rightX + scrollX + (copy * tWidth);

        for (int i = 0; marqueeText[i] != '\0'; i++) {
            char c[2] = { marqueeText[i], '\0' };

            if (marqueeText[i] != ' ') {
                Color letterColor = rainbow[(i + colorShift) % 7];
                float waveY = sinf(GetTime() * 6.0f + i * 0.3f) * 5.0f;

                DrawText(c, currentPosX + 3, marqueeY + 15 + waveY + 3, fontSize, Fade(BLACK, 0.6f));
                DrawText(c, currentPosX, marqueeY + 15 + waveY, fontSize, letterColor);
            }
            currentPosX += MeasureText(c, fontSize) + 2;
        }
    }
    EndScissorMode();

    // =========================================================
    // VẼ BẢNG GAME CHÍNH
    // =========================================================
    DrawRectangle(offsetX, offsetY, gridWidth, gridHeight, COLOR_4TL_PANEL);

    for (int i = 0; i < GRID_ROWS; i++) {
        for (int j = 0; j < GRID_COLS; j++) {
            DrawRectangleLines(offsetX + j * BLOCK_SIZE, offsetY + i * BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE, Fade(GRAY, 0.1f));
            if (board[i][j] != ' ' && board[i][j] != '#') Draw3DBlock(j, i, boardColors[i][j]);
            else if (board[i][j] == '#') Draw3DBlock(j, i, DARKGRAY);
        }
    }
    if (currentPiece && !isGameOver) {
        if (isHardDropping) {
            for (int i = 0; i < 4; i++) {
                for (int j = 0; j < 4; j++) {
                    if (currentPiece->shape[i][j] != ' ') {
                        int px = offsetX + (x + j) * BLOCK_SIZE;
                        int py = offsetY + (y + i) * BLOCK_SIZE;
                        if (py - BLOCK_SIZE >= offsetY) {
                            DrawRectangle(px, py - BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE, Fade(currentPiece->color, 0.4f));
                            DrawLine(px + 8, py, px + 8, py - BLOCK_SIZE, Fade(WHITE, 0.7f));
                            DrawLine(px + 32, py, px + 32, py - BLOCK_SIZE, Fade(WHITE, 0.7f));
                        }
                        if (py - BLOCK_SIZE * 2 >= offsetY) {
                            DrawRectangle(px, py - BLOCK_SIZE * 2, BLOCK_SIZE, BLOCK_SIZE, Fade(currentPiece->color, 0.15f));
                            DrawLine(px + 15, py - BLOCK_SIZE, px + 15, py - BLOCK_SIZE * 2, Fade(WHITE, 0.4f));
                            DrawLine(px + 25, py - BLOCK_SIZE, px + 25, py - BLOCK_SIZE * 2, Fade(WHITE, 0.4f));
                        }
                    }
                }
            }
        }

        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                if (currentPiece->shape[i][j] != ' ') {
                    Draw3DBlock(x + j, y + i, currentPiece->color);
                }
            }
        }
    }

    // =========================================================
    // OVERLAY MENU PAUSE
    // =========================================================
    if (isPaused) {
        DrawRectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, Fade(BLACK, 0.85f));
        const char* pTitle = "GAME PAUSED";
        int pTw = MeasureText(pTitle, 90);
        DrawText(pTitle, (SCREEN_WIDTH - pTw) / 2, 300, 90, GOLD);
        int btnPW = 450;
        int btnPH = 80;
        btnContinueRect = { (float)(SCREEN_WIDTH - btnPW) / 2, 450, (float)btnPW, (float)btnPH };
        btnMenuRect = { (float)(SCREEN_WIDTH - btnPW) / 2, 560, (float)btnPW, (float)btnPH };
        Vector2 mPos = GetMousePosition();

        bool hoverCont = CheckCollisionPointRec(mPos, btnContinueRect);
        DrawRectangleRec(btnContinueRect, hoverCont ? DARKGREEN : Fade(GREEN, 0.8f));
        DrawRectangleLinesEx(btnContinueRect, 4, RAYWHITE);
        DrawText("CONTINUE", btnContinueRect.x + (btnPW - MeasureText("CONTINUE", 40)) / 2, btnContinueRect.y + 20, 40, WHITE);

        bool hoverMenu = CheckCollisionPointRec(mPos, btnMenuRect);
        DrawRectangleRec(btnMenuRect, hoverMenu ? MAROON : Fade(RED, 0.8f));
        DrawRectangleLinesEx(btnMenuRect, 4, RAYWHITE);
        DrawText("MENU", btnMenuRect.x + (btnPW - MeasureText("MENU", 40)) / 2, btnMenuRect.y + 20, 40, WHITE);
    }
}

// ---------------------------------------------------------
// 3. TẢI TÀI NGUYÊN (Hình ảnh đồ họa)
// ---------------------------------------------------------
void LoadGameThemes() {
    backgroundSpace = LoadTexture("assets/images/bg_space.png");
    backgroundJungle = LoadTexture("assets/images/bg_jungle.png");
    backgroundEgypt = LoadTexture("assets/images/bg_egypt.png");
}

void UnloadGameThemes() {
    UnloadTexture(backgroundSpace);
    UnloadTexture(backgroundJungle);
    UnloadTexture(backgroundEgypt);
}