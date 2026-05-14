#pragma once
#include "gamelogic.h"
#include "piece.h"
#include <vector>

// =========================================================
// CÁC BIẾN DÙNG CHUNG NỘI BỘ CHO GAME LOGIC
// =========================================================

// Mảng lưới của ván game
extern char board[GRID_ROWS][GRID_COLS];
extern Color boardColors[GRID_ROWS][GRID_COLS];

// Tọa độ và tốc độ của khối gạch hiện tại
extern int x, y;
extern float moveTimer;
extern float dropDelay;
extern bool isHardDropping;

// Con trỏ quản lý khối gạch
extern Piece* currentPiece;
extern Piece* nextPiece;
extern int currentPieceType;
extern int nextPieceType;

// Túi gạch ngẫu nhiên (7 Bag system)
extern std::vector<int> bag;

// Ảnh nền
extern Texture2D backgroundSpace, backgroundJungle, backgroundEgypt;

// Bảng màu ngẫu nhiên cho gạch
extern const int NUM_COLORS;
extern Color randomPalette[];

// Quản lý trạng thái màn chơi
extern int totalLinesCleared;
extern bool isPaused;
extern bool showVolumeSlider;
extern float currentVolume;
extern bool isDraggingSlider;
extern char originalCurShape[4][4];

// Tọa độ các nút UI (Để logic xử lý click, draw để vẽ)
extern Rectangle btnPauseRect;
extern Rectangle btnVolRect;
extern Rectangle sliderBarRect;
extern Rectangle btnContinueRect;
extern Rectangle btnMenuRect;
