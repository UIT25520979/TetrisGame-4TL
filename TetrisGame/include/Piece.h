#pragma once  
#include "common.h"

// =========================================================
// QUẢN LÝ CẤU TRÚC DỮ LIỆU CÁC KHỐI
// =========================================================

// Khối
class Piece {
public:
    char shape[4][4]; // Ma trận 4x4 lưu hình dáng gạch
    int state;        // Trạng thái xoay
    Color color;      // Lưu màu sắc của khối gạch
    Piece();
    virtual ~Piece();
    virtual void rotate() = 0;
    void copyShape(const char source[4][4]);
};

// Các lớp con kế thừa (Các khối I O T S Z L J)
class PieceI : public Piece { public: PieceI(); void rotate() override; };
class PieceO : public Piece { public: PieceO(); void rotate() override; };
class PieceT : public Piece { public: PieceT(); void rotate() override; };
class PieceS : public Piece { public: PieceS(); void rotate() override; };
class PieceZ : public Piece { public: PieceZ(); void rotate() override; };
class PieceL : public Piece { public: PieceL(); void rotate() override; };
class PieceJ : public Piece { public: PieceJ(); void rotate() override; };