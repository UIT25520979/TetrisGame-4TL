#pragma once
#include "raylib.h"

// =========================================================
// CẤU HÌNH HỆ THỐNG
// =========================================================
const int SCREEN_WIDTH = 1920;   // Chiều rộng màn hình
const int SCREEN_HEIGHT = 1080;  // Chiều cao màn hình
const int TARGET_FPS = 60;       // Tốc độ khung hình (FPS)
const int GRID_ROWS = 21;        // Số hàng
const int GRID_COLS = 12;        // Số cột
const int BLOCK_SIZE = 40;       // Kích thước mỗi ô gạch (pixel)

// =========================================================
// CÁC TRẠNG THÁI VÀ ĐỊNH DANH (ENUMS)
// =========================================================

// Trạng thái màn hình
enum GameState {
    STATE_MENU,         // Menu chính
    STATE_HOW_TO_PLAY,  // Hướng dẫn chơi
    STATE_LEVEL_SELECT, // Chọn độ khó
    STATE_THEME_SELECT, // Chọn chủ đề
    STATE_PLAYING,      // Trong màn chơi
    STATE_MONUMENT,     // Bảng xếp hạng (Top 5)
    STATE_GAMEOVER      // Màn hình kết thúc
};

// Độ khó màn chơi
enum Difficulty {
    DIFF_EASY,          // Dễ
    DIFF_MEDIUM,        // Trung bình
    DIFF_HARD           // Khó
};

// Chủ đề màn chơi
enum GameTheme {
    THEME_SPACE,        // Không gian vũ trụ
    THEME_JUNGLE,       // Rừng rậm nhiệt đới
    THEME_EGYPT         // Ai Cập cổ đại
};

// Hiệu ứng âm thanh
enum SoundEvent {
    SFX_UI_HOVER,       // Rê chuột vào nút
    SFX_UI_CLICK,       // Nhấp chuột vào nút
    SFX_BLOCK_MOVE,     // Di chuyển khối
    SFX_BLOCK_ROTATE,   // Xoay khối 
    SFX_BLOCK_DROP,     // Khối chạm đáy
    SFX_LINE_CLEAR,     // Xóa dòng thường (1 - 3 dòng)
    SFX_TETRIS_CLEAR,   // Xóa 4 dòng (Tetris)
    SFX_GAMEOVER        // Kết thúc game
};

// =========================================================
// CẤU TRÚC DỮ LIỆU
// =========================================================

// Giao diện màn chơi
struct ThemeConfig {
    GameTheme type;
    Texture2D background; // Ảnh nền màn chơi
    Music bgm;            // Nhạc nền tương ứng
    Color blockColor;     // Màu khối gạch đặc trưng
    const char* name;     // Tên hiển thị
};

// Kỷ lục cá nhân
struct HighScore {
    int rank;             // Thứ hạng (1 - 5)
    int score;            // Điểm số
    Difficulty level;     // Độ khó
    GameTheme theme;      // Chủ đề
};

// =========================================================
// BẢNG MÀU CỦA DỰ ÁN
// =========================================================
const Color COLOR_4TL_NEON = { 0, 255, 255, 255 }; // Xanh Neon
const Color COLOR_4TL_PANEL = ColorAlpha(BLACK, 0.7f); // Nền UI (Đen mờ 70%)

// =========================================================
// BIẾN TOÀN CỤC 
// =========================================================
extern GameState currentState;        // Trạng thái màn hình hiện tại
extern Difficulty currentDifficulty;  // Độ khó hiện tại
extern GameTheme currentTheme;        // Chủ đề hiện tại
extern bool quitGame;                 // Cờ thoát game