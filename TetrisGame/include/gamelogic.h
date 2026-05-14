#pragma once
#include "common.h"
#include "piece.h"

// =========================================================
// QUẢN LÝ LOGIC TRÒ CHƠI
// =========================================================

extern int currentScore;    // Điểm số hiện tại 
extern bool isGameOver;     // Trạng thái game over

// Khởi tạo ván game mới
void InitGame();

// Cập nhật logic game mỗi khung hình
void UpdateGame(float deltaTime, Difficulty level);

// Vẽ toàn bộ giao diện màn chơi
void DrawGame(GameTheme theme);

// Khởi tạo tài nguyên hình ảnh cho các theme
void LoadGameThemes();

// Giải phóng tài nguyên hình ảnh cho các theme
void UnloadGameThemes();

// Giải phóng bộ nhớ cho các khối
void UnloadGameLogic();