#include "../include/menudata.h"
#include "../include/audiohandler.h"
#include "../include/gamelogic.h"

// =========================================================
// KHAI BÁO THỰC THỂ CÁC BIẾN (Bỏ chữ static)
// =========================================================
Texture2D menuBackground;
Button btnNewGame, btnMonument, btnHowTo, btnBack;
Button btnEasy, btnMedium, btnHard;
Button btnSpace, btnJungle, btnEgypt;
Button btnPlayAgain;
Button btnExitRed;
float menuTime = 0.0f;

// ---------------------------------------------------------
// 1. KHỞI TẠO TỌA ĐỘ VÀ DỮ LIỆU NÚT BẤM
// ---------------------------------------------------------
void InitMenuButtons() {
    menuBackground = LoadTexture("assets/images/bg_tetris.jpg");
    int btnW = 650;
    int btnH = 110;
    int centerX = (SCREEN_WIDTH - btnW) / 2;

    btnNewGame = { {(float)centerX, 420, (float)btnW, (float)btnH}, "NEW GAME", SKYBLUE, false, false };
    btnMonument = { {(float)centerX, 560, (float)btnW, (float)btnH}, "ETERNAL MONUMENT", GOLD, false, false };
    btnHowTo = { {(float)centerX, 700, (float)btnW, (float)btnH}, "HOW TO PLAY", VIOLET, false, false };

    btnExitRed = { {(float)SCREEN_WIDTH - 100, 30, 80, 80}, "X", RED, false, false };
    btnBack = { {(float)(SCREEN_WIDTH - 350) / 2, (float)SCREEN_HEIGHT - 130, 350, 90}, "BACK", GRAY, false, false };

    btnPlayAgain = { {(float)centerX, 600, (float)btnW, (float)btnH}, "PLAY AGAIN", GREEN, false, false };

    btnEasy = { {(float)centerX, 420, (float)btnW, (float)btnH}, "EASY", GREEN, false, false };
    btnMedium = { {(float)centerX, 560, (float)btnW, (float)btnH}, "MEDIUM", ORANGE, false, false };
    btnHard = { {(float)centerX, 700, (float)btnW, (float)btnH}, "HARD", RED, false, false };

    btnSpace = { {(float)centerX, 420, (float)btnW, (float)btnH}, "SPACE THEME", PURPLE, false, false };
    btnJungle = { {(float)centerX, 560, (float)btnW, (float)btnH}, "JUNGLE THEME", DARKGREEN, false, false };
    btnEgypt = { {(float)centerX, 700, (float)btnW, (float)btnH}, "EGYPT THEME", GOLD, false, false };
}

bool IsButtonClicked(Button& btn) {
    Vector2 mouse = GetMousePosition();
    btn.isHovered = CheckCollisionPointRec(mouse, btn.rect);

    if (btn.isHovered && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        btn.isPressed = true;
        PlayGameSound(SFX_UI_CLICK);
    }

    if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON) && btn.isPressed) {
        btn.isPressed = false;
        if (btn.isHovered) return true;
    }

    if (!IsMouseButtonDown(MOUSE_LEFT_BUTTON)) btn.isPressed = false;
    return false;
}

// ---------------------------------------------------------
// 2. LOGIC CẬP NHẬT TRẠNG THÁI (STATE MACHINE)
// ---------------------------------------------------------
void UpdateMenu(GameState& currentState) {
    switch (currentState) {
    case STATE_MENU:
        if (IsButtonClicked(btnNewGame)) currentState = STATE_LEVEL_SELECT;
        if (IsButtonClicked(btnMonument)) currentState = STATE_MONUMENT;
        if (IsButtonClicked(btnHowTo)) currentState = STATE_HOW_TO_PLAY;
        if (IsButtonClicked(btnExitRed)) quitGame = true;
        break;

    case STATE_LEVEL_SELECT:
        if (IsButtonClicked(btnEasy)) { currentDifficulty = DIFF_EASY; currentState = STATE_THEME_SELECT; }
        if (IsButtonClicked(btnMedium)) { currentDifficulty = DIFF_MEDIUM; currentState = STATE_THEME_SELECT; }
        if (IsButtonClicked(btnHard)) { currentDifficulty = DIFF_HARD; currentState = STATE_THEME_SELECT; }
        if (IsButtonClicked(btnBack)) currentState = STATE_MENU;
        break;

    case STATE_THEME_SELECT:
        if (IsButtonClicked(btnSpace)) { currentTheme = THEME_SPACE; InitGame(); currentState = STATE_PLAYING; }
        if (IsButtonClicked(btnJungle)) { currentTheme = THEME_JUNGLE; InitGame(); currentState = STATE_PLAYING; }
        if (IsButtonClicked(btnEgypt)) { currentTheme = THEME_EGYPT; InitGame(); currentState = STATE_PLAYING; }
        if (IsButtonClicked(btnBack)) currentState = STATE_LEVEL_SELECT;
        break;

    case STATE_GAMEOVER:
        if (IsButtonClicked(btnPlayAgain)) {
            btnBack.rect.y = (float)SCREEN_HEIGHT - 120;
            InitGame();
            currentState = STATE_PLAYING;
        }
        else if (IsButtonClicked(btnBack)) {
            btnBack.rect.y = (float)SCREEN_HEIGHT - 120;
            currentState = STATE_MENU;
        }
        break;
    default:
        if (IsButtonClicked(btnBack)) currentState = STATE_MENU;
        break;
    }
}

void UnloadMenuResources() {
    if (menuBackground.id > 0) {
        UnloadTexture(menuBackground);
    }
}