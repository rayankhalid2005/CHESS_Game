// Piece.h
  #ifndef PIECE_H
#define PIECE_H

class Piece {
protected:     //  piece will be used latter in move validation function, so protected will allow access directly
    char color;
    int row, col;

public:
    Piece(char color, int row, int col);
    
    char get_color();
    int get_row();
    int get_col();
    
    void set_row(int r);
    void set_col(int c);

    virtual bool is_valid_move(int to_row, int to_col, Piece* board[8][8]) = 0;
    virtual char get_symbol() = 0;

    virtual ~Piece() {} // till now it is void
};

#endif

// Rook.h
#ifndef ROOK_H
#define ROOK_H
#include "Piece.h"

class Rook : public Piece {
public:
    Rook(char color, int row, int col);
    bool is_valid_move(int to_row, int to_col, Piece* board[8][8]) override;
    char get_symbol() override;
};

#endif

// Bishop.h
#ifndef BISHOP_H
#define BISHOP_H
#include "Piece.h"

class Bishop : public Piece {
public:
    Bishop(char color, int row, int col);
    bool is_valid_move(int to_row, int to_col, Piece* board[8][8]) override;
    char get_symbol() override;
};
#endif

// Knight.h
#ifndef KNIGHT_H
#define KNIGHT_H

#include "Piece.h"

class Knight : public Piece {
public:
    Knight(char color, int row, int col);
    bool is_valid_move(int to_row, int to_col, Piece* board[8][8]) override;
    char get_symbol() override;
};

#endif

// Queen.h

#ifndef QUEEN_H
#define QUEEN_H

#include "Piece.h"

class Queen : public Piece {
public:
    Queen(char color, int row, int col);
    bool is_valid_move(int to_row, int to_col, Piece* board[8][8]) override;
    char get_symbol() override;
};

#endif

// Pawn.h

#ifndef PAWN_H
#define PAWN_H

#include "Piece.h"

class Pawn : public Piece {
public:
    Pawn(char color, int row, int col);
    bool is_valid_move(int to_row, int to_col, Piece* board[8][8]) override;
    char get_symbol() override;
};

#endif

// King.h

#ifndef KING_H
#define KING_H

#include "Piece.h"

class King : public Piece {
public:
    King(char color, int row, int col);
    bool is_valid_move(int to_row, int to_col, Piece* board[8][8]) override;
    char get_symbol() override;
};

#endif
