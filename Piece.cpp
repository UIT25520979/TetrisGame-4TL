#include "Piece.h"

// Cài đặt các hàm của lớp cha
Piece::Piece() {
    state = 0;
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            shape[i][j] = ' ';
}

Piece::~Piece() {}

void Piece::copyShape(const char source[4][4]) {
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            shape[i][j] = source[i][j];
}

PieceI::PieceI() {
    char s[4][4] = {
        {' ','I',' ',' '},
        {' ','I',' ',' '},
        {' ','I',' ',' '},
        {' ','I',' ',' '}
    };
    copyShape(s);
}

void PieceI::rotate() {
    state = (state + 1) % 2;
    if (state == 0) {
        char s[4][4] = {
            {' ','I',' ',' '},
            {' ','I',' ',' '},
            {' ','I',' ',' '},
            {' ','I',' ',' '}
        };
        copyShape(s);
    }
    else {
        char s[4][4] = {
            {' ',' ',' ',' '},
            {'I','I','I','I'},
            {' ',' ',' ',' '},
            {' ',' ',' ',' '}
        };
        copyShape(s);
    }
}


// Constructor khởi tạo khối O
PieceO::PieceO() {
    char s[4][4] = {
        {' ', ' ', ' ', ' '},
        {' ', 'O', 'O', ' '},
        {' ', 'O', 'O', ' '},
        {' ', ' ', ' ', ' '}
    };
    copyShape(s);
    state = 0;
}

// Khối vuông xoay không đổi hình dạng
void PieceO::rotate() {
    state = (state + 1) % 4; // Vẫn cập nhật state cho đúng chuẩn nhưng không cần đổi shape
}


// Constructor khởi tạo khối T (Mặc định trạng thái 0)
PieceT::PieceT() {
    char s[4][4] = {
        {' ', 'T', ' ', ' '},
        {'T', 'T', 'T', ' '},
        {' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' '}
    };
    copyShape(s);
    state = 0;
}

// Hàm xoay khối T qua 4 góc
void PieceT::rotate() {
    state = (state + 1) % 4;

    if (state == 0) {
        // T hướng lên: 
        //   . T .
        //   T T T
        char s[4][4] = {
            {' ', 'T', ' ', ' '},
            {'T', 'T', 'T', ' '},
            {' ', ' ', ' ', ' '},
            {' ', ' ', ' ', ' '}
        };
        copyShape(s);
    }
    else if (state == 1) {
        // T hướng sang phải:
        //   T . .
        //   T T .
        //   T . .
        char s[4][4] = {
            {'T', ' ', ' ', ' '},
            {'T', 'T', ' ', ' '},
            {'T', ' ', ' ', ' '},
            {' ', ' ', ' ', ' '}
        };
        copyShape(s);
    }
    else if (state == 2) {
        // T hướng xuống:
        //   T T T
        //   . T .
        char s[4][4] = {
            {'T', 'T', 'T', ' '},
            {' ', 'T', ' ', ' '},
            {' ', ' ', ' ', ' '},
            {' ', ' ', ' ', ' '}
        };
        copyShape(s);
    }
    else if (state == 3) {
        // T hướng sang trái:
        //   . T .
        //   T T .
        //   . T .
        char s[4][4] = {
            {' ', 'T', ' ', ' '},
            {'T', 'T', ' ', ' '},
            {' ', 'T', ' ', ' '},
            {' ', ' ', ' ', ' '}
        };
        copyShape(s);
    }
}