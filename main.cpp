#include <iostream>
#include <conio.h>
#include <windows.h>
#include <time.h>

using namespace std;

#define H 20
#define W 15
#define B_BORDER '#'

char board[H][W] = {};
char blocks[19][4][4] = {
        {{' ','I',' ',' '},
         {' ','I',' ',' '},
         {' ','I',' ',' '},
         {' ','I',' ',' '}},
        {{' ',' ',' ',' '},
         {'I','I','I','I'},
         {' ',' ',' ',' '},
         {' ',' ',' ',' '}},
        {{' ',' ',' ',' '},
         {' ','O','O',' '},
         {' ','O','O',' '},
         {' ',' ',' ',' '}},
        {{' ',' ',' ',' '},
         {' ','T',' ',' '},
         {'T','T','T',' '},
         {' ',' ',' ',' '}},
        {{' ','T',' ',' '},
         {' ','T','T',' '},
         {' ','T',' ',' '},
         {' ',' ',' ',' '}},
        {{' ',' ',' ',' '},
         {'T','T','T',' '},
         {' ','T',' ',' '},
         {' ',' ',' ',' '}},
        {{' ','T',' ',' '},
         {'T','T',' ',' '},
         {' ','T',' ',' '},
         {' ',' ',' ',' '}},
        {{' ',' ',' ',' '},
         {' ','S','S',' '},
         {'S','S',' ',' '},
         {' ',' ',' ',' '}},
        {{'S',' ',' ',' '},
         {'S','S',' ',' '},
         {' ','S',' ',' '},
         {' ',' ',' ',' '}},
        {{' ',' ',' ',' '},
         {'Z','Z',' ',' '},
         {' ','Z','Z',' '},
         {' ',' ',' ',' '}},
        {{' ',' ','Z',' '},
         {' ','Z','Z',' '},
         {' ','Z',' ',' '},
         {' ',' ',' ',' '}},
        {{' ',' ',' ',' '},
         {' ',' ','L',' '},
         {'L','L','L',' '},
         {' ',' ',' ',' '}},
        {{'L',' ',' ',' '},
         {'L',' ',' ',' '},
         {'L','L',' ',' '},
         {' ',' ',' ',' '}},
        {{'L','L','L',' '},
         {'L',' ',' ',' '},
         {' ',' ',' ',' '},
         {' ',' ',' ',' '}},
        {{' ','L','L',' '},
         {' ',' ','L',' '},
         {' ',' ','L',' '},
         {' ',' ',' ',' '}},
        {{' ',' ',' ',' '},
         {'J',' ',' ',' '},
         {'J','J','J',' '},
         {' ',' ',' ',' '}},
        {{' ','J','J',' '},
         {' ','J',' ',' '},
         {' ','J',' ',' '},
         {' ',' ',' ',' '}},
        {{'J','J','J',' '},
         {' ',' ','J',' '},
         {' ',' ',' ',' '},
         {' ',' ',' ',' '}},
        {{' ','J',' ',' '},
         {' ','J',' ',' '},
         {'J','J',' ',' '},
         {' ',' ',' ',' '}}
};

int x = 5, y = 0, b = 0;
int speed = 200;

void gotoxy(int x, int y) {
    COORD c = { (short)x, (short)y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

void boardDelBlock() {
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            if (blocks[b][i][j] != ' ' && y + j < H)
                board[y + i][x + j] = ' ';
}

void block2Board() {
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            if (blocks[b][i][j] != ' ')
                board[y + i][x + j] = blocks[b][i][j];
}

void initBoard() {
    for (int i = 0; i < H; i++)
        for (int j = 0; j < W; j++)
            if ((i == H - 1) || (j == 0) || (j == W - 1)) board[i][j] = B_BORDER;
            else board[i][j] = ' ';
}

void draw() {
    gotoxy(0,0);
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
            if (blocks[b][i][j] != ' ') {
                int tx = x + j + dx;
                int ty = y + i + dy;
                if (tx < 1 || tx >= W - 1 || ty >= H - 1) return false;
                if (board[ty][tx] != ' ') return false;
            }
    return true;
}

bool canRotate(int nextB) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (blocks[nextB][i][j] != ' ') {
                int tx = x + j;
                int ty = y + i;
                if (tx < 1 || tx >= W - 1 || ty >= H - 1) return false;
                if (board[ty][tx] != ' ') return false;
            }
        }
    }
    return true;
}

int nextRotation(int currentB) {
    if (currentB >= 0 && currentB <= 1) return (currentB - 0 + 1) % 2 + 0;
    if (currentB == 2) return 2;
    if (currentB >= 3 && currentB <= 6) return (currentB - 3 + 1) % 4 + 3;
    if (currentB >= 7 && currentB <= 8) return (currentB - 7 + 1) % 2 + 7;
    if (currentB >= 9 && currentB <= 10) return (currentB - 9 + 1) % 2 + 9;
    if (currentB >= 11 && currentB <= 14) return (currentB - 11 + 1) % 4 + 11;
    if (currentB >= 15 && currentB <= 18) return (currentB - 15 + 1) % 4 + 15;
    return currentB;
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
    int basicBlocks[] = {0, 2, 3, 7, 9, 11, 15};
    b = basicBlocks[rand() % 7];
    system("cls");
    initBoard();
    // Dùng đồng hồ hệ thống để tách biệt input và rơi tự do
    DWORD lastDropTime = GetTickCount();
    bool isUpdated = true; // Kiểm tra để vẽ lần đầu tiên
    while (1) {
        boardDelBlock();
        // Quét phím
        if (kbhit()){
            char c = getch();
            if (c == 'a' && canMove(-1,0)) { x--; isUpdated = true; }
            if (c == 'd' && canMove(1,0)) { x++; isUpdated = true; }
            if (c == 's' && canMove(0,1)) {
                y++;
                lastDropTime = GetTickCount(); // Khởi động lại mốc rơi
                isUpdated = true;
            }
            if (c == 'w') {
                int nextB = nextRotation(b);
                if (canRotate(nextB)) { b = nextB; isUpdated = true; }
            }
            if (c == 'q') break;
        }
        // Logic rơi tự do theo thời gian thực
        if (GetTickCount() - lastDropTime >= (DWORD)speed) {
            if (canMove(0,1)) y++;
            else {
                block2Board();
                removeLine();
                x = 5; y = 0;
                b = basicBlocks[rand() % 7];
                if (!canMove(0, 0)) {
                    block2Board();
                    draw();
                    cout << "\n   GAME OVER !!!\n" << endl;
                    break;
                }
            }
            lastDropTime = GetTickCount();
            isUpdated = true; // Báo hiệu gạch vừa rớt xuống, cần vẽ lại
        }
        block2Board();
        // Chỉ vẽ lại nếu màn hình có gì đó thay đổi
        if (isUpdated) {
            draw();
            isUpdated = false;
        }
        _sleep(10);
    }
    return 0;
}
