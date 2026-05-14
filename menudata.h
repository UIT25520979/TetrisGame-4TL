#pragma once
#include "menu.h"
#include "raymath.h"

// =========================================================
// CÁC BIẾN DÙNG CHUNG NỘI BỘ CHO MENU
// =========================================================
extern Texture2D menuBackground;
extern Button btnNewGame, btnMonument, btnHowTo, btnBack;
extern Button btnEasy, btnMedium, btnHard;
extern Button btnSpace, btnJungle, btnEgypt;
extern Button btnPlayAgain;
extern Button btnExitRed;
extern float menuTime;

// Khai báo các hàm hỗ trợ vẽ để menu_draw.cpp sử dụng
void DrawLayoutBase(const char* screenTitle);
bool IsButtonClicked(Button& btn);
