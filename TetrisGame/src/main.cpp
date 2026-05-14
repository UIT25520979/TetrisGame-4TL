#include "../include/common.h"
#include "../include/menu.h"
#include "../include/audiohandler.h"
#include "../include/gamelogic.h"
#include "../include/effects.h"
#include "../include/monument.h"

// =========================================================
// BIẾN TOÀN CỤC
// =========================================================
GameState currentState = STATE_MENU;        
Difficulty currentDifficulty = DIFF_MEDIUM; 
GameTheme currentTheme = THEME_SPACE;     
bool quitGame = false;

int main() {
    // =========================================================
    // KHỞI TẠO HỆ THỐNG
    // =========================================================
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "TETRIS SURVIVAL GAME"); // Khởi tạo cửa sổ
    Image logoIcon = LoadImage("assets/images/logo.png"); // Load logo game
    SetWindowIcon(logoIcon);  //Khởi tạo logo game
    UnloadImage(logoIcon); // Giải phóng bộ nhớ sau khi hệ điều hành đã nhận icon
    InitAudioSystem();     // Âm thanh
    InitMenuButtons();     // Giao diện nút bấm
    InitEffectSystem();    // Hiệu ứng hạt và rung
    LoadGameThemes();      // Nạp ảnh nền
    SetTargetFPS(TARGET_FPS);  // Thiết lập tốc độ khung hình
    // =========================================================
    // VÒNG LẶP GAME CHÍNH
    // =========================================================
    while (!WindowShouldClose() && !quitGame) {
        float deltaTime = GetFrameTime();
        // Cập nhật nhạc nền và các hạt hiệu ứng mỗi khung hình
        UpdateGameMusic(currentState, currentTheme);
        UpdateEffects(deltaTime);
        // Điều phối hoạt động dựa trên trạng thái hiện tại
        switch (currentState) {
        case STATE_MENU:
        case STATE_LEVEL_SELECT:
        case STATE_THEME_SELECT:
        case STATE_HOW_TO_PLAY:
        case STATE_MONUMENT:
        case STATE_GAMEOVER:
            UpdateMenu(currentState);
            // Chơi lại sau khi thua
            if (currentState == STATE_PLAYING && isGameOver) {
                InitGame();
            }
            break;
        case STATE_PLAYING:
            UpdateGame(deltaTime, currentDifficulty);
            // Sự kiện game over
            if (isGameOver) {
                currentState = STATE_GAMEOVER;
                SetMasterVolume(1.0f);
                TriggerScreenShake(12.0f, 0.6f); // Kích hoạt rung mạnh khi game over
                PlayGameSound(SFX_GAMEOVER);     // Phát nhạc game over
                // Kiểm tra và lưu kỷ lục vào bảng vàng
                if (IsEligibleForMonument(currentScore)) {
                    AddRecordToMonument(currentScore, currentDifficulty, currentTheme);
                }
            }
            break;
        }
        // =========================================================
        // VẼ GIAO DIỆN
        // =========================================================
        // Thiết lập Camera ảo để tạo hiệu ứng rung
        Vector2 shake = GetScreenShakeOffset();
        Camera2D camera = { 0 };
        camera.offset = shake;        
        camera.target = { 0, 0 };
        camera.rotation = 0.0f;
        camera.zoom = 1.0f;
        BeginDrawing();
        ClearBackground(BLACK);
        // Bắt đầu vẽ qua ống kính của Camera để thấy được hiệu ứng rung
        BeginMode2D(camera);
        switch (currentState) {
        case STATE_MENU:         DrawMainMenu(); break;
        case STATE_LEVEL_SELECT: DrawLevelSelectScreen(); break;
        case STATE_THEME_SELECT: DrawThemeSelectScreen(); break;
        case STATE_HOW_TO_PLAY:  DrawHowToPlayScreen(); break;
        case STATE_MONUMENT:     DrawMonumentScreen(); break;
        case STATE_PLAYING:
            DrawGame(currentTheme); 
            DrawEffects();          
            break;
        case STATE_GAMEOVER:
            DrawGameOverScreen(currentScore);
            break;
        }
        EndMode2D(); 
        EndDrawing();
    }
    // =========================================================
    // GIẢI PHÓNG TÀI NGUYÊN
    // =========================================================
    CloseAudioSystem();    // Đóng thiết bị âm thanh
    UnloadGameThemes();    // Giải phóng ảnh nền theme
    UnloadMenuResources(); // Giải phóng ảnh nền menu
    UnloadGameLogic();     // Giải phóng các khối
    CloseWindow();         // Đóng cửa sổ game
    return 0;
}