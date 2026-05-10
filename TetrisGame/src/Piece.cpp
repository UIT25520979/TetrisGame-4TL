#include "../include/Piece.h"

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

// --- KHỐI I ---
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
    } else {
        char s[4][4] = {
            {' ',' ',' ',' '},
            {'I','I','I','I'},
            {' ',' ',' ',' '},
            {' ',' ',' ',' '}
        };
        copyShape(s);
    }
}

// --- KHỐI O ---
PieceO::PieceO() {
    char s[4][4] = {
        {' ',' ',' ',' '},
        {' ','O','O',' '},
        {' ','O','O',' '},
        {' ',' ',' ',' '}
    };
    copyShape(s);
}

void PieceO::rotate() {
    // Khối O không thay đổi hình dáng khi xoay
}

// --- KHỐI T ---
PieceT::PieceT() {
    char s[4][4] = {
        {' ',' ',' ',' '},
        {' ','T',' ',' '},
        {'T','T','T',' '},
        {' ',' ',' ',' '}
    };
    copyShape(s);
}

void PieceT::rotate() {
    state = (state + 1) % 4;
    if (state == 0) {
        char s[4][4] = {
            {' ',' ',' ',' '},
            {' ','T',' ',' '},
            {'T','T','T',' '},
            {' ',' ',' ',' '}
        };
        copyShape(s);
    } else if (state == 1) {
        char s[4][4] = {
            {' ','T',' ',' '},
            {' ','T','T',' '},
            {' ','T',' ',' '},
            {' ',' ',' ',' '}
        };
        copyShape(s);
    } else if (state == 2) {
        char s[4][4] = {
            {' ',' ',' ',' '},
            {'T','T','T',' '},
            {' ','T',' ',' '},
            {' ',' ',' ',' '}
        };
        copyShape(s);
    } else {
        char s[4][4] = {
            {' ','T',' ',' '},
            {'T','T',' ',' '},
            {' ','T',' ',' '},
            {' ',' ',' ',' '}
        };
        copyShape(s);
    }
}

// Khối S
PieceS::PieceS() {
    char s[4][4] = {
        {' ',' ',' ',' '},
        {' ','S','S',' '},
        {'S','S',' ',' '},
        {' ',' ',' ',' '}
    };
    copyShape(s);
}

void PieceS::rotate() {
    state = (state + 1) % 2;
    if (state == 0) {
        char s[4][4] = {
            {' ',' ',' ',' '},
            {' ','S','S',' '},
            {'S','S',' ',' '},
            {' ',' ',' ',' '}
        };
        copyShape(s);
    } else {
        char s[4][4] = {
            {'S',' ',' ',' '},
            {'S','S',' ',' '},
            {' ','S',' ',' '},
            {' ',' ',' ',' '}
        };
        copyShape(s);
    }
}

// Khối Z
PieceZ::PieceZ() {
    char s[4][4] = {
        {' ',' ',' ',' '},
        {'Z','Z',' ',' '},
        {' ','Z','Z',' '},
        {' ',' ',' ',' '}
    };
    copyShape(s);
}

void PieceZ::rotate() {
    state = (state + 1) % 2;
    if (state == 0) {
        char s[4][4] = {
            {' ',' ',' ',' '},
            {'Z','Z',' ',' '},
            {' ','Z','Z',' '},
            {' ',' ',' ',' '}
        };
        copyShape(s);
    } else {
        char s[4][4] = {
            {' ',' ','Z',' '},
            {' ','Z','Z',' '},
            {' ','Z',' ',' '},
            {' ',' ',' ',' '}
        };
        copyShape(s);
    }
}

// Khối L
PieceL::PieceL() {
    char s[4][4] = {
        {' ',' ',' ',' '},
        {' ',' ','L',' '},
        {'L','L','L',' '},
        {' ',' ',' ',' '}
    };
    copyShape(s);
}

void PieceL::rotate() {
    state = (state + 1) % 4;
    if (state == 0) {
        char s[4][4] = {
            {' ',' ',' ',' '},
            {' ',' ','L',' '},
            {'L','L','L',' '},
            {' ',' ',' ',' '}
        };
        copyShape(s);
    } else if (state == 1) {
        char s[4][4] = {
            {'L',' ',' ',' '},
            {'L',' ',' ',' '},
            {'L','L',' ',' '},
            {' ',' ',' ',' '}
        };
        copyShape(s);
    } else if (state == 2) {
        char s[4][4] = {
            {'L','L','L',' '},
            {'L',' ',' ',' '},
            {' ',' ',' ',' '},
            {' ',' ',' ',' '}
        };
        copyShape(s);
    } else {
        char s[4][4] = {
            {' ','L','L',' '},
            {' ',' ','L',' '},
            {' ',' ','L',' '},
            {' ',' ',' ',' '}
        };
        copyShape(s);
    }
}

// Khối J
PieceJ::PieceJ() {
    char s[4][4] = {
        {' ',' ',' ',' '},
        {'J',' ',' ',' '},
        {'J','J','J',' '},
        {' ',' ',' ',' '}
    };
    copyShape(s);
}

void PieceJ::rotate() {
    state = (state + 1) % 4;
    if (state == 0) {
        char s[4][4] = {
            {' ',' ',' ',' '},
            {'J',' ',' ',' '},
            {'J','J','J',' '},
            {' ',' ',' ',' '}
        };
        copyShape(s);
    } else if (state == 1) {
        char s[4][4] = {
            {' ','J','J',' '},
            {' ','J',' ',' '},
            {' ','J',' ',' '},
            {' ',' ',' ',' '}
        };
        copyShape(s);
    } else if (state == 2) {
        char s[4][4] = {
            {'J','J','J',' '},
            {' ',' ','J',' '},
            {' ',' ',' ',' '},
            {' ',' ',' ',' '}
        };
        copyShape(s);
    } else {
        char s[4][4] = {
            {' ','J',' ',' '},
            {' ','J',' ',' '},
            {'J','J',' ',' '},
            {' ',' ',' ',' '}
        };
        copyShape(s);
    }
}
