#pragma once
#include "common.h"

// =========================================================
// HỆ THỐNG ÂM THANH
// =========================================================

// Khởi tạo âm thanh
void InitAudioSystem();

// Dọn dẹp bộ nhớ âm thanh.
void CloseAudioSystem();

// Quản lý nhạc nền
void UpdateGameMusic(GameState currentState, GameTheme currentTheme);

// Phát ra âm thanh ngay lập tức dựa trên mã sự kiện.
void PlayGameSound(SoundEvent event);

/* DANH SÁCH CÁC MÃ SỰ KIỆN SFX:
   - SFX_UI_HOVER      : Rê chuột vào nút
   - SFX_UI_CLICK      : Nhấn nút
   - SFX_BLOCK_MOVE    : Di chuyển khối
   - SFX_BLOCK_ROTATE  : Xoay khối 
   - SFX_BLOCK_DROP    : Chạm đáy / Khóa khối
   - SFX_LINE_CLEAR    : Ăn dòng thường
   - SFX_TETRIS_CLEAR  : Ăn 4 dòng cùng lúc 
   - SFX_GAMEOVER      : Game over
*/
