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

class PieceS : public Piece {
public:
    PieceS() {
        char s[4][4] = {
            {' ',' ',' ',' '},
            {' ','S','S',' '},
            {'S','S',' ',' '},
            {' ',' ',' ',' '}
        };
        copyShape(s);
    }
    void rotate() override {
        state = (state + 1) % 2;
        if (state == 0) {
            char s[4][4] = {
                {' ',' ',' ',' '},
                {' ','S','S',' '},
                {'S','S',' ',' '},
                {' ',' ',' ',' '}
            };
            copyShape(s);
        }
        else {
            char s[4][4] = {
                {'S',' ',' ',' '},
                {'S','S',' ',' '},
                {' ','S',' ',' '},
                {' ',' ',' ',' '}
            };
            copyShape(s);
        }
    }
};

class PieceZ : public Piece {
public:
    PieceZ() {
        char s[4][4] = {
            {' ',' ',' ',' '},
            {'Z','Z',' ',' '},
            {' ','Z','Z',' '},
            {' ',' ',' ',' '}
        };
        copyShape(s);
    }
    void rotate() override {
        state = (state + 1) % 2;
        if (state == 0) {
            char s[4][4] = {
                {' ',' ',' ',' '},
                {'Z','Z',' ',' '},
                {' ','Z','Z',' '},
                {' ',' ',' ',' '}
            };
            copyShape(s);
        }
        else {
            char s[4][4] = {
                {' ',' ','Z',' '},
                {' ','Z','Z',' '},
                {' ','Z',' ',' '},
                {' ',' ',' ',' '}
            };
            copyShape(s);
        }
    }
};
