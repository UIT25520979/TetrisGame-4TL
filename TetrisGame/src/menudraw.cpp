#include "../include/menudata.h"
#include "../include/monument.h"
#include <string>
#include <math.h>

// ---------------------------------------------------------
// 1. CÁC HÀM HỖ TRỢ VẼ NÚT VÀ LAYOUT CHUNG
// ---------------------------------------------------------

void DrawButton(Button btn) {
    // Xác định màu sắc dựa trên trạng thái chuột
    Color drawColor = btn.isHovered ? ColorBrightness(btn.baseColor, 0.4f) : btn.baseColor;

    // Hiệu ứng bóng đổ và lún nút khi nhấn
    float shadowOffset = 12.0f;
    float pressOffset = btn.isPressed ? 10.0f : 0.0f;

    // Vẽ bóng đổ phía sau để tạo độ sâu
    DrawRectangleRec({ btn.rect.x + 5, btn.rect.y + shadowOffset, btn.rect.width, btn.rect.height }, Fade(BLACK, 0.6f));

    // Vẽ thân nút chính
    DrawRectangleRec({ btn.rect.x, btn.rect.y + pressOffset, btn.rect.width, btn.rect.height }, drawColor);
    DrawRectangleLinesEx({ btn.rect.x, btn.rect.y + pressOffset, btn.rect.width, btn.rect.height }, 4, RAYWHITE);

    // Vẽ chữ bên trong nút với phông chữ lớn và bóng đổ
    int fontSize = 50;
    int textW = MeasureText(btn.text, fontSize);
    int tx = btn.rect.x + (btn.rect.width - textW) / 2;
    int ty = btn.rect.y + pressOffset + (btn.rect.height - fontSize) / 2;

    DrawText(btn.text, tx + 4, ty + 4, fontSize, Fade(BLACK, 0.5f));

    // Tự động đổi màu chữ cho dễ nhìn dựa trên độ sáng của nút
    Color textColor = (btn.baseColor.r > 150) ? YELLOW : WHITE;
    if (TextIsEqual(btn.text, "ETERNAL MONUMENT")) {
        textColor = WHITE;
    }
    DrawText(btn.text, tx, ty, fontSize, textColor);
}

void DrawLayoutBase(const char* screenTitle) {
    menuTime += GetFrameTime();

    // Vẽ ảnh nền toàn màn hình
    if (menuBackground.id > 0) {
        DrawTexturePro(menuBackground,
            { 0, 0, (float)menuBackground.width, (float)menuBackground.height },
            { 0, 0, (float)SCREEN_WIDTH, (float)SCREEN_HEIGHT },
            { 0, 0 }, 0.0f, WHITE);
        DrawRectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, Fade(BLACK, 0.4f));
    }
    else {
        ClearBackground({ 15, 15, 35, 255 });
    }

    if (TextIsEqual(screenTitle, "MAIN_MENU")) {
        // HIỆU ỨNG RAINBOW NEON CHO TIÊU ĐỀ CHÍNH
        const char* gameTitle = "SURVIVAL TETRIS GAME";
        int fontSize = 130;
        int spaceKerning = 25;
        int totalWidth = 0;

        for (int i = 0; gameTitle[i] != '\0'; i++) {
            char c[2] = { gameTitle[i], '\0' };
            totalWidth += MeasureText(c, fontSize) + (fontSize / 12);
            if (i == 8) totalWidth -= spaceKerning;
        }
        totalWidth -= (fontSize / 12);

        int startX = (SCREEN_WIDTH - totalWidth) / 2;
        int startY = 120;
        int currentX = startX;

        float pulse = sinf(menuTime * 2.5f);
        float slowPulse = sinf(menuTime * 0.5f);
        Color rainbow[] = { RED, ORANGE, GOLD, LIME, SKYBLUE, VIOLET, MAGENTA };

        for (int i = 0; gameTitle[i] != '\0'; i++) {
            char c[2] = { gameTitle[i], '\0' };
            if (gameTitle[i] != ' ') {
                Color baseColor = rainbow[i % 7];
                float ghostOffset = 10.0f + pulse * 5.0f;

                // Vẽ các lớp bóng mờ nhấp nháy
                DrawText(c, currentX + ghostOffset, startY + ghostOffset, fontSize, Fade(PURPLE, 0.2f + slowPulse * 0.1f));
                DrawText(c, currentX - ghostOffset, startY - ghostOffset, fontSize, Fade(DARKBLUE, 0.2f - slowPulse * 0.1f));

                Color neonColor = (slowPulse > 0) ? LIME : SKYBLUE;
                for (int j = 1; j <= 4; j++) {
                    float glowFade = 0.3f - (j * 0.08f) + (pulse * 0.05f);
                    if (glowFade > 0) DrawText(c, currentX, startY, fontSize + j * 2, Fade(neonColor, glowFade));
                }
                DrawText(c, currentX + 8, startY + 8, fontSize, DARKGRAY);
                DrawText(c, currentX, startY, fontSize, Fade(baseColor, 0.85f + pulse * 0.15f));

                // Hiệu ứng tia lửa (Sparks)
                if (slowPulse > 0.8f || slowPulse < -0.8f) {
                    if (GetRandomValue(0, 10) > 7) {
                        int sparkX = currentX + GetRandomValue(0, MeasureText(c, fontSize));
                        int sparkY = startY + GetRandomValue(0, fontSize);
                        DrawCircle(sparkX, sparkY, GetRandomValue(3, 6), Fade(WHITE, 0.8f));
                    }
                }
            }
            int stepX = MeasureText(c, fontSize) + (fontSize / 12);
            if (i == 8) stepX -= spaceKerning;
            currentX += stepX;
        }
    }
    else if (TextIsEqual(screenTitle, "GAME OVER")) {
        // HIỆU ỨNG TRÔI NỔI VÀ HÀO QUANG CHO GAME OVER
        int fontSize = 180;
        int textW = MeasureText("GAME OVER", fontSize);
        int startX = (SCREEN_WIDTH - textW) / 2;
        int baseY = 180;

        float waveY = sinf(menuTime * 3.0f) * 15.0f;
        float pulse = (sinf(menuTime * 6.0f) + 1.0f) / 2.0f;
        int currentY = baseY + (int)waveY;

        DrawText("GAME OVER", startX + 15, currentY + 15, fontSize, Fade(BLACK, 0.9f));
        DrawText("GAME OVER", startX - 8, currentY - 8, fontSize, Fade(RED, pulse * 0.7f));
        DrawText("GAME OVER", startX + 8, currentY + 8, fontSize, Fade(RED, pulse * 0.7f));
        DrawText("GAME OVER", startX + 6, currentY + 6, fontSize, MAROON);
        DrawText("GAME OVER", startX, currentY, fontSize, RED);
    }
    else {
        // XỬ LÝ CHO CÁC MÀN HÌNH CHỌN VÀ THÔNG TIN
        bool isSelectScreen = TextIsEqual(screenTitle, "SELECT YOUR DIFFICULTY") || TextIsEqual(screenTitle, "SELECT YOUR BATTLEFIELD");
        bool isInfoScreen = TextIsEqual(screenTitle, "HOW TO PLAY") || TextIsEqual(screenTitle, "ETERNAL MONUMENT");

        if (isSelectScreen) {
            // Hiệu ứng Glitch Chromatic Aberration
            int fontSize = 100;
            int textW = MeasureText(screenTitle, fontSize);
            int startX = (SCREEN_WIDTH - textW) / 2;

            float floatY = sinf(menuTime * 3.0f) * 6.0f;
            int startY = 80 + (int)floatY;
            float glitchOffset = 3.0f + sinf(menuTime * 12.0f) * 3.0f;

            DrawText(screenTitle, startX + 8, startY + 8, fontSize, Fade(BLACK, 0.8f));
            DrawText(screenTitle, startX - (int)glitchOffset, startY, fontSize, Fade(RED, 0.6f));
            DrawText(screenTitle, startX + (int)glitchOffset, startY, fontSize, Fade(SKYBLUE, 0.6f));
            DrawText(screenTitle, startX, startY, fontSize, GOLD);
        }
        else if (isInfoScreen) {
            // HIỆU ỨNG BREATHING GLOW VÀ ICON CHIẾC CÚP
            bool isHowTo = TextIsEqual(screenTitle, "HOW TO PLAY");
            bool isMonument = TextIsEqual(screenTitle, "ETERNAL MONUMENT");

            std::string titleStr = screenTitle;
            if (isHowTo) titleStr += " ?";

            const char* displayText = titleStr.c_str();
            int fontSize = 95;
            int textW = MeasureText(displayText, fontSize);

            int iconW = 75;
            int gap = 20;
            int totalW = isMonument ? (textW + gap + iconW) : textW;

            int startX = (SCREEN_WIDTH - totalW) / 2;
            int startY = 85;
            float glow = (sinf(menuTime * 4.0f) + 1.0f) / 2.0f;

            DrawText(displayText, startX + 6, startY + 6, fontSize, Fade(BLACK, 0.8f));
            DrawText(displayText, startX - 3, startY - 3, fontSize, Fade(ORANGE, glow * 0.7f));
            DrawText(displayText, startX + 3, startY + 3, fontSize, Fade(ORANGE, glow * 0.7f));
            DrawText(displayText, startX, startY, fontSize, YELLOW);
            DrawText(displayText, startX, startY, fontSize, Fade(WHITE, glow * 0.4f));

            if (isMonument) {
                // Tự vẽ icon Trophy bằng các khối Rectangle
                int iconX = startX + textW + gap;
                int iconY = startY + 12;

                auto DrawTrophyLayer = [&](int x, int y, Color c) {
                    DrawRectangle(x + 18, y + 58, 39, 9, c);
                    DrawRectangle(x + 33, y + 43, 9, 15, c);
                    DrawRectangle(x + 27, y + 31, 21, 12, c);
                    DrawRectangle(x + 21, y + 7, 33, 24, c);
                    DrawRectangle(x + 6, y + 12, 9, 22, c);
                    DrawRectangle(x + 15, y + 12, 6, 7, c);
                    DrawRectangle(x + 15, y + 27, 6, 7, c);
                    DrawRectangle(x + 60, y + 12, 9, 22, c);
                    DrawRectangle(x + 54, y + 12, 6, 7, c);
                    DrawRectangle(x + 54, y + 27, 6, 7, c);
                    };

                DrawTrophyLayer(iconX + 6, iconY + 6, Fade(BLACK, 0.8f));
                DrawTrophyLayer(iconX - 3, iconY - 3, Fade(ORANGE, glow * 0.7f));
                DrawTrophyLayer(iconX + 3, iconY + 3, Fade(ORANGE, glow * 0.7f));
                DrawTrophyLayer(iconX, iconY, YELLOW);
                DrawTrophyLayer(iconX, iconY, Fade(WHITE, glow * 0.4f));
            }
        }
    }
}

// ---------------------------------------------------------
// 2. CÁC MÀN HÌNH CỤ THỂ
// ---------------------------------------------------------

void DrawMainMenu() {
    DrawLayoutBase("MAIN_MENU");
    DrawButton(btnNewGame);
    DrawButton(btnMonument);
    DrawButton(btnHowTo);
    DrawButton(btnExitRed);
}

void DrawLevelSelectScreen() {
    btnBack.text = "BACK";
    DrawLayoutBase("SELECT YOUR DIFFICULTY");
    DrawButton(btnEasy);
    DrawButton(btnMedium);
    DrawButton(btnHard);
    DrawButton(btnBack);
}

void DrawThemeSelectScreen() {
    btnBack.text = "BACK";
    DrawLayoutBase("SELECT YOUR BATTLEFIELD");
    DrawButton(btnSpace);
    DrawButton(btnJungle);
    DrawButton(btnEgypt);
    DrawButton(btnBack);
}

// Hàm tĩnh hỗ trợ vẽ phím điều khiển
static void DrawKeyCap(const char* text, int x, int y, int size) {
    int keySize = 50;
    DrawRectangle(x + 4, y + 6, keySize, keySize, Fade(BLACK, 0.6f));
    DrawRectangleRec({ (float)x, (float)y, (float)keySize, (float)keySize }, DARKGRAY);
    DrawRectangleLinesEx({ (float)x, (float)y, (float)keySize, (float)keySize }, 3, RAYWHITE);

    int fontSize = 35;
    int tw = MeasureText(text, fontSize);
    DrawText(text, x + (keySize - tw) / 2, y + (keySize - fontSize) / 2, fontSize, WHITE);
}

void DrawHowToPlayScreen() {
    DrawLayoutBase("HOW TO PLAY");

    int panelW = 1400;
    int panelH = 590;
    int panelX = (SCREEN_WIDTH - panelW) / 2;
    int panelY = 200;

    float pulse = (sinf(menuTime * 5.0f) + 1.0f) / 2.0f;
    Color borderPulse = Fade(GOLD, 0.4f + pulse * 0.6f);
    Color bgPulse = Fade(BLACK, 0.85f + pulse * 0.1f);

    DrawRectangle(panelX, panelY, panelW, panelH, bgPulse);
    DrawRectangleLinesEx({ (float)panelX, (float)panelY, (float)panelW, (float)panelH }, 5 + pulse * 3, borderPulse);

    int col1W = 800;
    int cx2 = col1W;

    // CỘT 1: ĐIỀU KHIỂN
    int startY = panelY + 30;
    DrawText("GAME CONTROLS", panelX + (col1W - MeasureText("GAME CONTROLS", 35)) / 2, startY, 35, VIOLET);
    DrawLineEx({ (float)panelX + 50, (float)startY + 50 }, { (float)panelX + col1W - 50, (float)startY + 50 }, 4, GRAY);

    int keyY = startY + 100;
    int keyX = panelX + 80;
    DrawKeyCap("A", keyX, keyY, 50); DrawText("- MOVE BLOCK LEFT", keyX + 75, keyY + 12, 30, WHITE);
    keyY += 85;
    DrawKeyCap("D", keyX, keyY, 50); DrawText("- MOVE BLOCK RIGHT", keyX + 75, keyY + 12, 30, WHITE);
    keyY += 85;
    DrawKeyCap("W", keyX, keyY, 50); DrawText("- ROTATE BLOCK", keyX + 75, keyY + 12, 30, WHITE);
    keyY += 85;
    DrawKeyCap("S", keyX, keyY, 50); DrawText("- SOFT DROP (FASTER)", keyX + 75, keyY + 12, 30, WHITE);
    keyY += 85;
    int spaceW = MeasureText("SPACE", 30) + 60;
    DrawRectangleRec({ (float)keyX, (float)keyY, (float)spaceW, 50 }, DARKGRAY);
    DrawRectangleLinesEx({ (float)keyX, (float)keyY, (float)spaceW, 50 }, 3, RAYWHITE);
    DrawText("SPACE", keyX + (spaceW - MeasureText("SPACE", 30)) / 2, keyY + 12, 30, WHITE);
    DrawText("- HARD DROP (INSTANT)", keyX + spaceW + 25, keyY + 12, 30, WHITE);

    DrawLine(panelX + cx2, panelY + 10, panelX + cx2, panelY + panelH - 10, Fade(WHITE, 0.8f));

    // CỘT 2: LUẬT CHƠI VÀ ĐIỂM SỐ
    DrawText("GAME RULES", panelX + cx2 + (600 - MeasureText("GAME RULES", 35)) / 2, startY, 35, SKYBLUE);
    DrawLineEx({ (float)panelX + cx2 + 40, (float)startY + 50 }, { (float)panelX + panelW - 40, (float)startY + 50 }, 4, GRAY);
    DrawText("- Connect blocks to form lines.\n- Complete full rows to clear them.\n- Game over if blocks reach the top.", panelX + cx2 + 40, startY + 80, 28, LIGHTGRAY);

    int scoreY = startY + 200;
    DrawText("LINE CLEAR SCORES:", panelX + cx2 + (600 - MeasureText("LINE CLEAR SCORES:", 30)) / 2, scoreY, 30, GREEN);
    DrawLine(panelX + cx2 + 50, scoreY + 45, panelX + panelW - 50, scoreY + 45, DARKGRAY);

    int scoreRowY = scoreY + 70;
    auto DrawScoreRow = [&](const char* label, const char* pts, Color c, int& y) {
        DrawText(label, panelX + cx2 + 60, y, 28, WHITE);
        DrawText(pts, panelX + panelW - MeasureText(pts, 28) - 70, y, 28, c);
        y += 45;
        };
    DrawScoreRow("1 ROW CLEAR:", "100 PTS", SKYBLUE, scoreRowY);
    DrawScoreRow("2 ROWS CLEAR:", "300 PTS", GREEN, scoreRowY);
    DrawScoreRow("3 ROWS CLEAR:", "500 PTS", GOLD, scoreRowY);
    DrawScoreRow("4 ROWS CLEAR:", "1000 PTS", RED, scoreRowY);
    DrawText("BONUS: Hard Drop (+2 PTS / Block)", panelX + cx2 + 60, scoreRowY, 28, MAGENTA);

    btnBack.text = "BACK";
    btnBack.rect.y = SCREEN_HEIGHT - 130;
    DrawButton(btnBack);
}

// ---------------------------------------------------------
// 3. MÀN HÌNH BẢNG VÀNG (MONUMENT) VÀ GAME OVER
// ---------------------------------------------------------

static Color GetLevelColorHelper(Difficulty diff) {
    if (diff == DIFF_EASY) return GREEN;
    if (diff == DIFF_MEDIUM) return ORANGE;
    if (diff == DIFF_HARD) return RED;
    return WHITE;
}

static Color GetThemeColorHelper(GameTheme theme) {
    if (theme == THEME_SPACE) return PURPLE;
    if (theme == THEME_JUNGLE) return DARKGREEN;
    if (theme == THEME_EGYPT) return GOLD;
    return WHITE;
}

static void DrawTextCenteredInCol(const char* text, int panelX, int colX, int colW, int Y, int fontSize, Color color) {
    int textW = MeasureText(text, fontSize);
    int startX = colX + (colW - textW) / 2;
    DrawText(text, panelX + startX, Y, fontSize, color);
}

void DrawMonumentScreen() {
    DrawLayoutBase("ETERNAL MONUMENT");
    std::vector<HighScore> scores = LoadMonumentData();

    int panelW = 1400; int panelH = 510;
    int panelX = (SCREEN_WIDTH - panelW) / 2; int panelY = 260;

    float pulse = (sinf(menuTime * 5.0f) + 1.0f) / 2.0f;
    DrawRectangle(panelX, panelY, panelW, panelH, Fade(BLACK, 0.85f + pulse * 0.1f));
    DrawRectangleLinesEx({ (float)panelX, (float)panelY, (float)panelW, (float)panelH }, 5 + pulse * 3, Fade(GOLD, 0.4f + pulse * 0.6f));

    int c1W = (int)(panelW * 0.20f); int c2W = (int)(panelW * 0.25f);
    int c3W = (int)(panelW * 0.25f); int c4W = panelW - c1W - c2W - c3W;
    int cx2 = c1W; int cx3 = cx2 + c2W; int cx4 = cx3 + c3W;

    DrawLine(panelX + cx2, panelY + 10, panelX + cx2, panelY + panelH - 10, Fade(WHITE, 0.8f));
    DrawLine(panelX + cx3, panelY + 10, panelX + cx3, panelY + panelH - 10, Fade(WHITE, 0.8f));
    DrawLine(panelX + cx4, panelY + 10, panelX + cx4, panelY + panelH - 10, Fade(WHITE, 0.8f));

    DrawTextCenteredInCol("RANK", panelX, 0, c1W, panelY + 30, 35, YELLOW);
    DrawTextCenteredInCol("SCORE", panelX, cx2, c2W, panelY + 30, 35, YELLOW);
    DrawTextCenteredInCol("DIFFICULTY", panelX, cx3, c3W, panelY + 30, 35, YELLOW);
    DrawTextCenteredInCol("BATTLEFIELD", panelX, cx4, c4W, panelY + 30, 35, YELLOW);
    DrawLineEx({ (float)panelX + 20, (float)panelY + 85 }, { (float)panelX + panelW - 20, (float)panelY + 85 }, 4, GRAY);

    for (int i = 0; i < (int)scores.size() && i < 5; i++) {
        int rowY = panelY + 130 + (i * 75);
        Color rankColor;
        switch (i) {
        case 0: rankColor = ORANGE; break;
        case 1: rankColor = PURPLE; break;
        case 2: rankColor = GREEN; break;
        case 3: rankColor = SKYBLUE; break;
        default: rankColor = LIGHTGRAY; break;
        }
        DrawTextCenteredInCol(TextFormat("TOP %d", scores[i].rank), panelX, 0, c1W, rowY, 35, rankColor);

        if (scores[i].score > 0) {
            DrawTextCenteredInCol(TextFormat("%d PTS", scores[i].score), panelX, cx2, c2W, rowY, 35, WHITE);
            DrawTextCenteredInCol(GetLevelName(scores[i].level).c_str(), panelX, cx3, c3W, rowY, 35, GetLevelColorHelper(scores[i].level));
            DrawTextCenteredInCol(GetThemeName(scores[i].theme).c_str(), panelX, cx4, c4W, rowY, 35, GetThemeColorHelper(scores[i].theme));
        }
        if (i < 4) DrawLine(panelX + 40, rowY + 55, panelX + panelW - 40, rowY + 55, Fade(DARKGRAY, 0.4f));
    }

    btnBack.text = "BACK"; btnBack.rect.y = SCREEN_HEIGHT - 130;
    DrawButton(btnBack);
}

void DrawGameOverScreen(int finalScore) {
    DrawLayoutBase("GAME OVER");

    std::vector<HighScore> scores = LoadMonumentData();
    bool isNewHighScore = scores.empty() || finalScore > scores[0].score;

    std::string scoreTxt = (isNewHighScore ? "NEW HIGH SCORE: " : "YOUR SCORE: ") + std::to_string(finalScore);

    int fontSize = 100;
    int startX = (SCREEN_WIDTH - MeasureText(scoreTxt.c_str(), fontSize)) / 2;
    int startY = 420;

    float glow = (sinf(menuTime * 4.0f) + 1.0f) / 2.0f;
    Color mainColor = isNewHighScore ? LIME : GOLD;
    Color glow1 = isNewHighScore ? GREEN : ORANGE;
    Color glow2 = isNewHighScore ? LIME : RED;

    DrawText(scoreTxt.c_str(), startX + 10, startY + 10, fontSize, Fade(BLACK, 0.8f));
    DrawText(scoreTxt.c_str(), startX - 5, startY - 5, fontSize, Fade(glow1, glow * 0.7f));
    DrawText(scoreTxt.c_str(), startX + 5, startY + 5, fontSize, Fade(glow2, glow * 0.7f));
    DrawText(scoreTxt.c_str(), startX, startY, fontSize, mainColor);
    DrawText(scoreTxt.c_str(), startX, startY, fontSize, Fade(WHITE, glow * 0.5f));

    btnPlayAgain.rect.y = 620; DrawButton(btnPlayAgain);
    btnBack.text = "MENU"; btnBack.rect.y = 780; DrawButton(btnBack);
}