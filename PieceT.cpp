#include "Piece.h"

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