// Piece.cpp
#include "Piece.h"

Piece::Piece(char color, int row, int col) { // Becaose inheriting from piece, initializer list is necessary
    this->color = color;
    this->row = row;
    this->col = col;
}

char Piece::get_color() {
    return color; // through colour, solider can be recognized
}

int Piece::get_row() {
    return row;
}

int Piece::get_col() {
    return col;
}

void Piece::set_row(int r) {
    row = r; // updates row when peice moves
}

void Piece::set_col(int c) {
    col = c; // updates coloum when peice moves
}


// Rook.cpp
#include "Rook.h"
#include <cstdlib>

Rook::Rook(char color, int row, int col) : Piece(color, row, col) { // Becaose inheriting from piece, initializer list is necessary 
}

char Rook::get_symbol() {
    return 'R';
}

bool Rook::is_valid_move(int to_row, int to_col, Piece* board[8][8]) {
    if (to_row != row && to_col != col) { // Rook can only move straight
        return false;
    }
    if (to_row == row) {
        int dir;    // describes the direction of the piece
        if (to_col > col) {
            dir = 1;  //+ve
        } else {
            dir = -1;    //-ve
        }
        int c = col + dir;
        while (c != to_col) { // Checking squares one by one and does not includes the destinatoin.
            if (board[row][c] != NULL) {
                return false;
            }
            c = c + dir;
        }
    }
    if (to_col == col) { // coloums is fixed
        int dir; // describes the direction of the piece
        if (to_row > row) {
            dir = 1;
        } else {
            dir = -1;
        }
           int r = row + dir;
        while (r != to_row) {       // Checking squares one by one and does not includes the destinatoin.
            if (board[r][col] != NULL) {
            return false;
            }
            r = r + dir;
        }
    }
    if (board[to_row][to_col] != NULL && board[to_row][to_col]->get_color() == color) { // can't capture our own solider
        return false; // through colour, solider can be recognized.
    }
    return true;  // means the solider of opponent will be arrested.
}


// Pawn.cpp
#include "Pawn.h"
#include <cstdlib>

Pawn::Pawn(char color, int row, int col) : Piece(color, row, col) { // Becaose inheriting from piece, initializer list is necessary
}

char Pawn::get_symbol() {
    return 'P';
}

bool Pawn::is_valid_move(int to_row, int to_col, Piece* board[8][8]) {
    int dir;
    int start_row;
    if (color == 'W') {
        dir = -1; // white moves upwward
        start_row = 6;
    } else {
        dir = 1; // black moves downwward
        start_row = 1;
    }
    if (to_col == col && to_row == row + dir) {
        if (board[to_row][to_col] != NULL) { // Pawn cannoot capture forward
            return false;
        }
        return true;
    }
    if (to_col == col && row == start_row && to_row == row + 2 * dir) { // two steps only from starting row
        if (board[row + dir][col] != NULL) {
            return false;
        }
        if (board[to_row][to_col] != NULL) {
            return false;
        }
        return true;
    }
    if (abs(to_col - col) == 1 && to_row == row + dir) {
        if (board[to_row][to_col] != NULL && board[to_row][to_col]->get_color() != color) { // enimy must be present to capture diagonaly
            return true;
        }
        return false;
    }
    return false;
}


// Bishop.cpp
#include "Bishop.h"
#include <cstdlib>

Bishop::Bishop(char color, int row, int col) : Piece(color, row, col) {
}

char Bishop::get_symbol() {
    return 'B';
}

bool Bishop::is_valid_move(int to_row, int to_col, Piece* board[8][8]) {
    if (abs(to_row - row) != abs(to_col - col)) {// Bishop can move just diagonally.
        return false;
    }
    int row_dir;
    int col_dir;
    if (to_row > row) {
        row_dir = 1;
    } else {
         row_dir = -1;
    }
    if (to_col > col) {
    col_dir = 1; 
    } else {
        col_dir = -1;
    }
    int r = row + row_dir;
    int c = col + col_dir;
    while (r != to_row && c != to_col) { // go untill untill the destination square(not included)
        if (board[r][c] != NULL) { // checking whether the whole path is free or captured
            return false;
        }
        r = r + row_dir;
        c = c + col_dir;
    }
    if (board[to_row][to_col] != NULL && board[to_row][to_col]->get_color() == color) { // can't capture our own solider
        return false;  through colour, solider can be recognized.
    }
    return true;    // means the solider of opponent will be arrested.
}


// Knight.cpp
#include "Knight.h"
#include <cstdlib>

Knight::Knight(char color, int row, int col) : Piece(color, row, col) { // Becaose inheriting from piece, initializer list is necessary
}

char Knight::get_symbol() {
    return 'N'; // N is used becuase K is taken by King
}

bool Knight::is_valid_move(int to_row, int to_col, Piece* board[8][8]) {
    int row_diff = abs(to_row - row);
    int col_diff = abs(to_col - col);
    if (!((row_diff == 2 && col_diff == 1) || (row_diff == 1 && col_diff == 2))) { // Knigt moves in L shape only
        return false;
    }
    if (board[to_row][to_col] != NULL && board[to_row][to_col]->get_color() == color) { // can't capture our own solider
        return false; // through colour, solider can be recognized
    }
    return true; // means the solider of opponent will be arrested
}

// Queen.cpp
#include "Queen.h"
#include <cstdlib>

Queen::Queen(char color, int row, int col) : Piece(color, row, col) { // Becaose inheriting from piece, initializer list is necessary
}

char Queen::get_symbol() {
    return 'Q';
}

bool Queen::is_valid_move(int to_row, int to_col, Piece* board[8][8]) {
    bool straight = (to_row == row || to_col == col);
    bool diagonal = (abs(to_row - row) == abs(to_col - col));
    if (!straight && !diagonal) { // Queen combines Rook and Bishop movement
        return false;
    }
    if (straight) {
        if (to_row == row) { // coloum is fixed
            int dir;
            if (to_col > col) {
                dir = 1;
            } else {
                dir = -1;
            }
            int c = col + dir;
            while (c != to_col) { // checking squares one by one and does not includes the destinatoin
                if (board[row][c] != NULL) {
                    return false;
                }
                c = c + dir;
            }
        }
        if (to_col == col) { // row is fixed
            int dir;
            if (to_row > row) {
                dir = 1;
            } else {
                dir = -1;
            }
            int r = row + dir;
            while (r != to_row) { // checking squares one by one and does not includes the destinatoin
                if (board[r][col] != NULL) {
                    return false;
                }
                r = r + dir;
            }
        }
    }
    if (diagonal) {
        int row_dir;
        int col_dir;
        if (to_row > row) {
            row_dir = 1;
        } else {
            row_dir = -1;
        }
        if (to_col > col) {
            col_dir = 1;
        } else {
            col_dir = -1;
        }
        int r = row + row_dir;
        int c = col + col_dir;
        while (r != to_row && c != to_col) { // checking squares one by one and does not includes the destinatoin
            if (board[r][c] != NULL) {
                return false;
            }
            r = r + row_dir;
            c = c + col_dir;
        }
    }
    if (board[to_row][to_col] != NULL && board[to_row][to_col]->get_color() == color) { // can't capture our own solider
        return false; // through colour, solider can be recognized
    }
    return true; // means the solider of opponent will be arrested
}


// King.cpp
#include "King.h"
#include <cstdlib>

King::King(char color, int row, int col) : Piece(color, row, col) {
}

char King::get_symbol() {
    return 'K';
}

bool King::is_valid_move(int to_row, int to_col, Piece* board[8][8]) {
    int row_diff = abs(to_row - row);
    int col_diff = abs(to_col - col);
    if (row_diff > 1 || col_diff > 1) {
        return false;
    }
    if (row_diff == 0 && col_diff == 0) {
        return false;
    }
    if (board[to_row][to_col] != NULL && board[to_row][to_col]->get_color() == color) {
        return false;
    }
    return true;
}
