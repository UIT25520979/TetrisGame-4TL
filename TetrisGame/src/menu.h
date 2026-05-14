#pragma once
#include "common.h"

// =========================================================
// QUẢN LÝ GIAO DIỆN MENU
// =========================================================

// Trạng thái nút bấm
struct Button {
    Rectangle rect;      // Tọa độ (x, y) và kích thước của nút
    const char* text;    // Dòng chữ hiển thị bên trong nút
    Color baseColor;     // Màu nền mặc định của nút
    bool isHovered;      // Kiểm tra xem nếu chuột đang nằm trên nút
    bool isPressed;      // Kiểm tra xem nếu chuột đang nhấn giữ nút
};

// Khởi tạo các nút bấm
void InitMenuButtons();

// Cập nhật liên tục mỗi khung hình các màn hình
void UpdateMenu(GameState& currentState);

// Vẽ nút bấm 
void DrawButton(Button btn);

// Màn hình menu
void DrawMainMenu();

// Màn hình chọn độ khó
void DrawLevelSelectScreen();

// Màn hình chọn chủ đề
void DrawThemeSelectScreen();

// Màn hình hướng dẫn chơi game
void DrawHowToPlayScreen();

// Màn hình Eternal Monument
void DrawMonumentScreen();

// Màn hình kết thúc game
void DrawGameOverScreen(int finalScore);

// Giải phóng tài nguyên màn hình menu
void UnloadMenuResources();