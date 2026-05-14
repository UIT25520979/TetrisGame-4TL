#pragma once
#include "common.h"
#include <vector>

// =========================================================
// HIỆU ỨNG HÌNH ẢNH
// =========================================================

// Hiệu ứng nổ gạch (Particle)
struct Particle {
    Vector2 position;   // Vị trí hiện tại
    Vector2 speed;      // Vận tốc bay (hướng và tốc độ)
    Color color;        // Màu sắc của hạt (lấy theo màu khối gạch)
    float alpha;        // Độ trong suốt (để mờ dần rồi biến mất)
    float lifeTime;     // Thời gian tồn tại còn lại
};

// =========================================================
// ĐIỀU KHIỂN HỆ THỐNG
// =========================================================

// Khởi tạo hệ thống hiệu ứng (Xóa sạch danh sách hạt, reset biến rung)
void InitEffectSystem();

// Cập nhật trạng thái hiệu ứng mỗi khung hình (Di chuyển hạt, tính toán độ rung)
void UpdateEffects(float deltaTime);

// Vẽ toàn bộ hiệu ứng lên màn hình
void DrawEffects();

// Tạo hiệu ứng nổ tung tại hàng vừa bị xóa
void CreateLineClearEffect(int rowY, Color color);

// Kích hoạt hiệu ứng rung màn hình
void TriggerScreenShake(float intensity, float duration);

// Trả về giá trị dịch chuyển tọa độ do rung màn hình
Vector2 GetScreenShakeOffset();
