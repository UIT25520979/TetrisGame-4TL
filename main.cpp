#include <iostream>
#include <conio.h>
#include <windows.h>
#include <time.h>
#include "Piece.h"

using namespace std;

#define H 20
#define W 15
#define B_BORDER '#'

char board[H][W] = {};

int x = 5, y = 0;
int speed = 200;

void gotoxy(int x, int y) {
    COORD c = { (short)x, (short)y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

Piece* currentPiece = NULL;

void spawnPiece() {
    if (currentPiece != NULL) delete currentPiece;
    int r = rand() % 7;
    switch(r) {
        case 0: currentPiece = new PieceI(); break;
        case 1: currentPiece = new PieceO(); break;
        case 2: currentPiece = new PieceT(); break;
        case 3: currentPiece = new PieceS(); break;
        case 4: currentPiece = new PieceZ(); break;
        case 5: currentPiece = new PieceL(); break;
        case 6: currentPiece = new PieceJ(); break;
    }
    x = 5; y = 0;
}

void boardDelBlock() {
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            if (currentPiece -> shape[i][j] != ' ' && y + j < H)
                board[y + i][x + j] = ' ';
}

void block2Board() {
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            if (currentPiece -> shape[i][j] != ' ')
                board[y + i][x + j] = currentPiece -> shape[i][j];
}

void initBoard() {
    for (int i = 0; i < H; i++)
        for (int j = 0; j < W; j++)
            if ((i == H - 1) || (j == 0) || (j == W - 1)) board[i][j] = B_BORDER;
            else board[i][j] = ' ';
}

void draw() {
    gotoxy(0, 0);
    for (int i = 0; i < H; i++) {
        for (int j = 0; j < W; j++) {
            if (board[i][j] == B_BORDER) {
                cout << (char)178 << (char)178 << (char)178;
            }
            else if (board[i][j] != ' ') {
                cout << "[" << (char)254 << "]";
            }
            else {
                cout << "   ";
            }
        }
        cout << endl;
    }
}

bool canMove(int dx, int dy) {
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            if (currentPiece -> shape[i][j] != ' ') {
                int tx = x + j + dx;
                int ty = y + i + dy;
                if (tx < 1 || tx >= W - 1 || ty >= H - 1) return false;
                if (board[ty][tx] != ' ') return false;
            }
    return true;
}

bool rotateBlock() {
    if (currentPiece == nullptr) return false;
    char backupShape[4][4];
    int backupState = currentPiece -> state;
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            backupShape[i][j] = currentPiece -> shape[i][j];
    currentPiece -> rotate();
    if (!canMove(0, 0)) {
        currentPiece -> copyShape(backupShape);
        currentPiece -> state = backupState;
        return false;
    }
    return true;
}

void removeLine() {
    int j;
    for (int i = H - 2; i > 0; i--) {
        for (j = 0; j < W - 1; j++)
            if (board[i][j] == ' ') break;
        if (j == W - 1) {
            for (int ii = i; ii > 0; ii--)
                for (int j = 0; j < W - 1; j++) board[ii][j] = board[ii - 1][j];
            i++;
            draw();
            if (speed > 50) speed -= 10;
            _sleep(200);
        }
    }
}

int main() {
    system("chcp 437");
    srand((unsigned int)time(0));
    system("cls");
    initBoard();
    spawnPiece();
    DWORD lastDropTime = GetTickCount();
    bool isUpdated = true;
    while (1) {
        boardDelBlock();
        if (kbhit()) {
            char c = getch();
            if (c == 'a' && canMove(-1, 0)) { x--; isUpdated = true; }
            if (c == 'd' && canMove(1, 0)) { x++; isUpdated = true; }
            if (c == 's' && canMove(0, 1)) {
                y++;
                lastDropTime = GetTickCount();
                isUpdated = true;
            }
            if (c == 'w') {
                if (rotateBlock()) isUpdated = true;
            }
            if (c == 'q') break;
        }

        if (GetTickCount() - lastDropTime >= (DWORD)speed) {
            if (canMove(0, 1)) y++;
            else {
                block2Board();
                removeLine();
                spawnPiece();
                if (!canMove(0, 0)) {
                    block2Board();
                    draw();
                    cout << "\n   GAME OVER !!!\n" << endl;
                    break;
                }
            }
            lastDropTime = GetTickCount();
            isUpdated = true;
        }
        block2Board();
        if (isUpdated) {
            draw();
            isUpdated = false;
        }
        _sleep(10);
    }
    delete currentPiece;
    return 0;
}