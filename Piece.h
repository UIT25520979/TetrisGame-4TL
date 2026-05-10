#ifndef PIECE_H
#define PIECE_H

// Lớp cơ sở trừu tượng Piece
class Piece {
public:
    char shape[4][4];
    int state;

    Piece();
    virtual ~Piece();
    virtual void rotate() = 0;
    void copyShape(const char source[4][4]);
};

class PieceI : public Piece { public: PieceI(); void rotate() override; };
class PieceO : public Piece { public: PieceO(); void rotate() override; };
class PieceT : public Piece { public: PieceT(); void rotate() override; };
class PieceS : public Piece { public: PieceS(); void rotate() override; };
class PieceZ : public Piece { public: PieceZ(); void rotate() override; };
class PieceL : public Piece { public: PieceL(); void rotate() override; };
class PieceJ : public Piece { public: PieceJ(); void rotate() override; };

#endif