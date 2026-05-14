#pragma once
#include "common.h"
#include <vector>
#include <string>

// =========================================================
// QUẢN LÝ ETERNAL MONUMENT
// =========================================================

// Đường dẫn tĩnh tới file dữ liệu
const std::string MONUMENT_FILE_PATH = "assets/data/highscore.txt";

// Nạp danh sách 5 kỷ lục từ file txt lên game
std::vector<HighScore> LoadMonumentData();

// Ghi đè danh sách 5 kỷ lục mới xuống file
void SaveMonumentData(const std::vector<HighScore>& scores);

// Kiểm tra xem điểm số vừa đạt được có lọt top 5 không
bool IsEligibleForMonument(int newScore);

// Thêm kỷ lục mới
void AddRecordToMonument(int score, Difficulty level, GameTheme theme);

// Chuyển enum Difficulty thành chuỗi "EASY", "MEDIUM", "HARD" để vẽ lên màn hình
std::string GetLevelName(Difficulty level);

// Chuyển enum GameTheme thành chuỗi "SPACE", "JUNGLE", "EGYPT" để vẽ lên màn hình
std::string GetThemeName(GameTheme theme);