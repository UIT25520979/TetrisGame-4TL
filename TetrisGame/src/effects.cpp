#include "../include/effects.h"
#include <stdlib.h> 

// =========================================================
// BIẾN TOÀN CỤC NỘI BỘ
// =========================================================
static std::vector<Particle> particles;
static float shakeIntensity = 0.0f;
static float shakeTimeLeft = 0.0f;

// =========================================================
// KHỞI TẠO VÀ DỌN DẸP HIÊU ỨNG
// =========================================================
void InitEffectSystem() {
    particles.clear();
    shakeIntensity = 0.0f;
    shakeTimeLeft = 0.0f;
}

// =========================================================
// CẬP NHẬT HIỆU ỨNG
// =========================================================
void UpdateEffects(float deltaTime) {
    // A. Cập nhật hệ thống hạt (Particles)
    for (int i = (int)particles.size() - 1; i >= 0; i--) {
        // Di chuyển hạt dựa trên vận tốc
        particles[i].position.x += particles[i].speed.x * deltaTime;
        particles[i].position.y += particles[i].speed.y * deltaTime;
        // Thêm trọng lực 
        particles[i].speed.y += 600.0f * deltaTime;
        // Giảm thời gian sống
        particles[i].lifeTime -= deltaTime;
        // Nếu hạt đã hết thì xóa nó khỏi danh sách
        if (particles[i].lifeTime <= 0.0f) {
            particles.erase(particles.begin() + i);
        }
        // Hiệu ứng Hạt mờ dần đi trước khi biến mất
        else {
            particles[i].alpha = particles[i].lifeTime;
        }
    }
    // Cập nhật hiệu ứng rung màn hình
    if (shakeTimeLeft > 0.0f) {
        shakeTimeLeft -= deltaTime;
        if (shakeTimeLeft <= 0.0f) {
            shakeIntensity = 0.0f;
        }
    }
}

// =========================================================
// VẼ HIỆU ỨNG
// =========================================================
void DrawEffects() {
    for (const auto& p : particles) {
        // Tạo màu với độ trong suốt hiện tại của hạt
        Color particleColor = ColorAlpha(p.color, p.alpha);
        // Vẽ hạt là các mảnh hình vuông nhỏ (kích thước 6x6 pixel)
        DrawRectangle((int)p.position.x, (int)p.position.y, 6, 6, particleColor);
    }
}

// =========================================================
// KÍCH HOẠT HIỆU ỨNG
// =========================================================
void CreateLineClearEffect(int rowY, Color color) {
    // Tính toán lại tọa độ màn hình 
    int offsetX = (SCREEN_WIDTH - (GRID_COLS * BLOCK_SIZE)) / 2;
    int offsetY = (SCREEN_HEIGHT - (GRID_ROWS * BLOCK_SIZE)) / 2;
    // Tọa độ Y thực tế trên màn hình của hàng gạch bị xóa
    float screenY = offsetY + rowY * BLOCK_SIZE + (BLOCK_SIZE / 2.0f);
    // Sinh hạt cho toàn bộ chiều ngang của bảng 
    for (int j = 1; j < GRID_COLS - 1; j++) {
        float screenX = offsetX + j * BLOCK_SIZE + (BLOCK_SIZE / 2.0f);
        // Tạo 8 mảnh vỡ li ti cho mỗi ô gạch bị xóa
        for (int i = 0; i < 8; i++) {
            Particle p;
            // Vị trí xuất phát ngẫu nhiên xung quanh tâm ô gạch
            p.position = { screenX + GetRandomValue(-15, 15), screenY + GetRandomValue(-15, 15) };
            // Vận tốc văng nổ: Văng mạnh sang hai bên và nảy nhẹ lên trên
            p.speed = { (float)GetRandomValue(-250, 250), (float)GetRandomValue(-400, 50) };
            p.color = color;
            // Thời gian ngẫu nhiên từ 0.5s - 1.2s
            p.lifeTime = (float)GetRandomValue(50, 120) / 100.0f;
            p.alpha = 1.0f;
            particles.push_back(p);
        }
    }
}

void TriggerScreenShake(float intensity, float duration) {
    shakeIntensity = intensity;
    shakeTimeLeft = duration;
}

Vector2 GetScreenShakeOffset() {
    // Nếu đang trong thời gian rung, trả về một độ lệch tọa độ ngẫu nhiên
    if (shakeTimeLeft > 0.0f) {
        float offsetX = (float)GetRandomValue(-(int)shakeIntensity, (int)shakeIntensity);
        float offsetY = (float)GetRandomValue(-(int)shakeIntensity, (int)shakeIntensity);
        return { offsetX, offsetY };
    }
    return { 0.0f, 0.0f };
}