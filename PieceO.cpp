#include "Piece.h"

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