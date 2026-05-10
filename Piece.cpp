#include "Piece.h"

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