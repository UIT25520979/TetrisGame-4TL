#include <iostream>
#include <conio.h>
#include <windows.h>
#include <time.h>

using namespace std;

#define H 20
#define W 15
#define B_BORDER '#'

char board[H][W] = {};
// Nâng cấp mảng lên 19 phần tử để chứa toàn bộ các trạng thái xoay của 7 loại block
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

// Chỉnh sửa x = 5 để block luôn rơi ở chính giữa
int x = 5, y = 0, b = 0;

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
            if (blocks[b][i][j] != ' ') {
                int tx = x + j + dx;
                int ty = y + i + dy;
                if (tx < 1 || tx >= W - 1 || ty >= H - 1) return false;
                if (board[ty][tx] != ' ') return false;
            }
    return true;
}

// Kiểm tra không gian an toàn trước khi xoay (tránh cấn viền / block)
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

// Tính toán chỉ số xoay tiếp theo dựa trên phép chia lấy dư %
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
            _sleep(200);
        }
    }
}

int main() {
    system("chcp 437");
    srand((unsigned int)time(0));
    // Định nghĩa mảng 7 trạng thái gốc để đảm bảo block tạo ra 
    int basicBlocks[] = { 0, 2, 3, 7, 9, 11, 15 };
    b = basicBlocks[rand() % 7];
    system("cls");
    initBoard();
    while (1) {
        boardDelBlock();
        if (kbhit()) {
            char c = getch();
            if (c == 'a' && canMove(-1, 0)) x--;
            if (c == 'd' && canMove(1, 0)) x++;
            if (c == 's' && canMove(0, 1)) y++;
            // Nhấn phím 'w' để gọi logic xoay block
            if (c == 'w') {
                int nextB = nextRotation(b);
                if (canRotate(nextB)) b = nextB;
            }
            if (c == 'q') break;
        }
        if (canMove(0, 1)) y++;
        else {
            block2Board();
            removeLine();
            x = 5; y = 0;
            //Chọn random 1 trong 7 block ở trạng thái gốc
            b = basicBlocks[rand() % 7];
        }
        block2Board();
        draw();
        _sleep(200);
    }
    return 0;
}
