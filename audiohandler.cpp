#include "../include/audiohandler.h"
#include <string>

// =========================================================
// BIẾN TOÀN CỤC NỘI BỘ
// =========================================================
static Music menuBGM;
static Music spaceBGM, jungleBGM, egyptBGM;
static Sound sfxHover, sfxClick, sfxMove, sfxRotate, sfxDrop, sfxLine, sfxTetris, sfxGameOver;
static Music currentPlayingBGM;
static GameState lastState = STATE_MENU;
static GameTheme lastTheme = THEME_SPACE;

// ---------------------------------------------------------
// KHỞI TẠO & GIẢI PHÓNG ÂM THANH
// ---------------------------------------------------------
void InitAudioSystem() {
    InitAudioDevice(); // Kích hoạt phần cứng âm thanh
    // Nạp nhạc nền 
    menuBGM = LoadMusicStream("assets/audio/bgm_menu.mp3");
    spaceBGM = LoadMusicStream("assets/audio/bgm_space.mp3");
    jungleBGM = LoadMusicStream("assets/audio/bgm_jungle.mp3");
    egyptBGM = LoadMusicStream("assets/audio/bgm_egypt.mp3");
    // Nạp hiệu ứng âm thanh
    sfxHover = LoadSound("assets/audio/sfx_hover.wav");
    sfxClick = LoadSound("assets/audio/sfx_click.wav");
    sfxMove = LoadSound("assets/audio/sfx_move.wav");
    sfxRotate = LoadSound("assets/audio/sfx_rotate.wav");
    sfxDrop = LoadSound("assets/audio/sfx_drop.wav");
    sfxLine = LoadSound("assets/audio/sfx_line.wav");
    sfxTetris = LoadSound("assets/audio/sfx_tetris.wav");
    sfxGameOver = LoadSound("assets/audio/sfx_gameover.wav");
    currentPlayingBGM = menuBGM;
    PlayMusicStream(currentPlayingBGM);
}

void CloseAudioSystem() {
    // Giải phóng nhạc nền
    UnloadMusicStream(menuBGM);
    UnloadMusicStream(spaceBGM);
    UnloadMusicStream(jungleBGM);
    UnloadMusicStream(egyptBGM);
    // Giải phóng hiệu ứng âm thanh 
    UnloadSound(sfxHover); UnloadSound(sfxClick);
    UnloadSound(sfxMove); UnloadSound(sfxRotate);
    UnloadSound(sfxDrop); UnloadSound(sfxLine);
    UnloadSound(sfxTetris); UnloadSound(sfxGameOver);
    CloseAudioDevice();
}

// =========================================================
// CHUYỂN ĐỔI NHẠC NỀN
// =========================================================
void UpdateGameMusic(GameState currentState, GameTheme currentTheme) {
    Music nextBGM;
    bool shouldPlayBGM = true;
    // Xác định nhạc nền theo trạng thái
    if (currentState == STATE_PLAYING) {
        if (currentTheme == THEME_SPACE) nextBGM = spaceBGM;
        else if (currentTheme == THEME_JUNGLE) nextBGM = jungleBGM;
        else if (currentTheme == THEME_EGYPT) nextBGM = egyptBGM;
    }
    else if (currentState == STATE_GAMEOVER) {
        shouldPlayBGM = false;
    }
    else {
        nextBGM = menuBGM;
    }
    // Chuyển đổi / Tắt nhạc
    if (!shouldPlayBGM) {
        if (IsMusicStreamPlaying(currentPlayingBGM)) {
            StopMusicStream(currentPlayingBGM);
        }
        currentPlayingBGM.stream.buffer = nullptr; 
    }
    // Đổi nhạc khi bản nhạc mới khác bản nhạc cũ
    else if (nextBGM.stream.buffer != currentPlayingBGM.stream.buffer) {
        StopMusicStream(currentPlayingBGM);
        currentPlayingBGM = nextBGM;
        PlayMusicStream(currentPlayingBGM);
    }
    // Cập nhật luồng nhạc nếu có nhạc đang phát
    if (shouldPlayBGM && currentPlayingBGM.stream.buffer != nullptr) {
        UpdateMusicStream(currentPlayingBGM);
    }
}

// =========================================================
// PHÁT HIỆU ỨNG ÂM THANH
// =========================================================

void PlayGameSound(SoundEvent event) {
    switch (event) {
    case SFX_UI_HOVER:     PlaySound(sfxHover); break;
    case SFX_UI_CLICK:     PlaySound(sfxClick); break;
    case SFX_BLOCK_MOVE:   PlaySound(sfxMove); break;
    case SFX_BLOCK_ROTATE: PlaySound(sfxRotate); break;
    case SFX_BLOCK_DROP:   PlaySound(sfxDrop); break;
    case SFX_LINE_CLEAR:   PlaySound(sfxLine); break;
    case SFX_TETRIS_CLEAR: PlaySound(sfxTetris); break;
    case SFX_GAMEOVER:     PlaySound(sfxGameOver); break;
    }
}