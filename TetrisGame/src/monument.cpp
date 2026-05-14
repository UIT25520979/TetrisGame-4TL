#include "../include/monument.h"
#include <fstream>
#include <sstream>
#include <algorithm>
#include <filesystem>

// =========================================================
// NẠP DỮ LIỆU TỪ FILE
// =========================================================
std::vector<HighScore> LoadMonumentData() {
    std::vector<HighScore> scores;
    std::ifstream inFile(MONUMENT_FILE_PATH);
    // Tạo dữ liệu mặc định
    if (!inFile.is_open()) {
        for (int i = 1; i <= 5; i++) {
            scores.push_back({ i, 0, DIFF_EASY, THEME_SPACE });
        }
        return scores;
    }
    std::string line;
    while (std::getline(inFile, line)) {
        std::stringstream ss(line);
        HighScore hs;
        int diffInt, themeInt;
        // Cấu trúc file
        if (ss >> hs.rank >> hs.score >> diffInt >> themeInt) {
            hs.level = static_cast<Difficulty>(diffInt);
            hs.theme = static_cast<GameTheme>(themeInt);
            scores.push_back(hs);
        }
    }
    inFile.close();
    // Đảm bảo luôn có đủ 5 hàng hiển thị
    while (scores.size() < 5) {
        scores.push_back({ (int)scores.size() + 1, 0, DIFF_EASY, THEME_SPACE });
    }
    return scores;
}

// =========================================================
// GHI DỮ LIỆU XUỐNG FILE
// =========================================================
void SaveMonumentData(const std::vector<HighScore>& scores) {
    std::filesystem::create_directories("assets/data");
    std::ofstream outFile(MONUMENT_FILE_PATH);
    if (outFile.is_open()) {
        for (const auto& hs : scores) {
            outFile << hs.rank << " "
                << hs.score << " "
                << (int)hs.level << " "
                << (int)hs.theme << "\n";
        }
        outFile.close();
    }
}

// =========================================================
// KIỂM TRA ĐIỀU KIỆN LỌT TOP 5
// =========================================================
bool IsEligibleForMonument(int newScore) {
    if (newScore <= 0) return false;
    std::vector<HighScore> currentTop = LoadMonumentData();
    return (newScore > currentTop.back().score);
}

// =========================================================
// THÊM KỶ LỤC MỚI VÀ SẮP XẾP
// =========================================================
void AddRecordToMonument(int score, Difficulty level, GameTheme theme) {
    std::vector<HighScore> scores = LoadMonumentData();
    // Thêm kỷ lục mới vào danh sách
    scores.push_back({ 0, score, level, theme });
    // Sắp xếp giảm dần theo điểm số
    std::sort(scores.begin(), scores.end(), [](const HighScore& a, const HighScore& b) {
        return a.score > b.score;
        });
    // Chỉ giữ lại Top 5 và cập nhật lại thứ hạng
    if (scores.size() > 5) scores.resize(5);
    for (int i = 0; i < (int)scores.size(); i++) {
        scores[i].rank = i + 1;
    }
    SaveMonumentData(scores);
}

// =========================================================
// CÁC HÀM HỖ TRỢ HIỂN THỊ
// =========================================================
std::string GetLevelName(Difficulty level) {
    switch (level) {
    case DIFF_EASY:   return "EASY";
    case DIFF_MEDIUM: return "MEDIUM";
    case DIFF_HARD:   return "HARD";
    default:          return "UNKNOWN";
    }
}

std::string GetThemeName(GameTheme theme) {
    switch (theme) {
    case THEME_SPACE:  return "SPACE";
    case THEME_JUNGLE: return "JUNGLE";
    case THEME_EGYPT:  return "EGYPT";
    default:           return "UNKNOWN";
    }
}