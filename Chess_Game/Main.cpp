#include <iostream>
#include <vector>
#include<string>
using namespace std;
// Enum for piece type
enum PieceType { EMPTY, PAWN, KNIGHT, BISHOP, ROOK, QUEEN, KING };
// Enum for piece color
enum PieceColor { NONE, WHITE, BLACK };
// Structure for a chess piece
struct Piece {
    PieceType type;
    PieceColor color;
    Piece(PieceType t = EMPTY, PieceColor c = NONE) : type(t), color(c) {}
};
// Class to represent the chess board
class ChessBoard {
private:
    vector<vector<Piece>> board;

public:
    ChessBoard() {
        board.resize(8, vector<Piece>(8));

        // Initialize the board with pieces
        for (int i = 0; i < 8; ++i) {
            board[1][i] = Piece(PAWN, WHITE); // White pawns
            board[6][i] = Piece(PAWN, BLACK); // Black pawns
        }

        // Rooks
        board[0][0] = Piece(ROOK, WHITE);
        board[0][7] = Piece(ROOK, WHITE);
        board[7][0] = Piece(ROOK, BLACK);
        board[7][7] = Piece(ROOK, BLACK);

        // Knights
        board[0][1] = Piece(KNIGHT, WHITE);
        board[0][6] = Piece(KNIGHT, WHITE);
        board[7][1] = Piece(KNIGHT, BLACK);
        board[7][6] = Piece(KNIGHT, BLACK);

        // Bishops
        board[0][2] = Piece(BISHOP, WHITE);
        board[0][5] = Piece(BISHOP, WHITE);
        board[7][2] = Piece(BISHOP, BLACK);
        board[7][5] = Piece(BISHOP, BLACK);

        // Queens
        board[0][3] = Piece(QUEEN, WHITE);
        board[7][3] = Piece(QUEEN, BLACK);

        // Kings
        board[0][4] = Piece(KING, WHITE);
        board[7][4] = Piece(KING, BLACK);
    }

    void printBoard() {
        for (int i = 0; i < 8; ++i) {
            for (int j = 0; j < 8; ++j) {
                char pieceChar = '.';
                if (board[i][j].type != EMPTY) {
                    switch (board[i][j].type) {
                    case PAWN: pieceChar = (board[i][j].color == WHITE) ? 'P' : 'p'; break;
                    case KNIGHT: pieceChar = (board[i][j].color == WHITE) ? 'N' : 'n'; break;
                    case BISHOP: pieceChar = (board[i][j].color == WHITE) ? 'B' : 'b'; break;
                    case ROOK: pieceChar = (board[i][j].color == WHITE) ? 'R' : 'r'; break;
                    case QUEEN: pieceChar = (board[i][j].color == WHITE) ? 'Q' : 'q'; break;
                    case KING: pieceChar = (board[i][j].color == WHITE) ? 'K' : 'k'; break;
                    }
                }
                cout << pieceChar << " ";
            }
            cout << endl;
        }
    }

    bool movePiece(int startX, int startY, int endX, int endY) {
        if (startX < 0 || startX >= 8 || startY < 0 || startY >= 8 ||
            endX < 0 || endX >= 8 || endY < 0 || endY >= 8) {
            cout << "Invalid move: out of bounds." << endl;
            return false;
        }

        Piece& piece = board[startX][startY];
        if (piece.type == EMPTY) {
            cout << "Invalid move: no piece at starting position." << endl;
            return false;
        }

        // Move the piece to the new location
        board[endX][endY] = piece;
        board[startX][startY] = Piece(); // Clear the old position
        return true;
    }
};

int main() {
    ChessBoard chessBoard;
    chessBoard.printBoard();

    string command;
    while (true) {
        cout << "Enter your move (format: startX startY endX endY, or 'exit' to quit): ";
        getline(cin, command);
        if (command == "exit") break;

        int startX, startY, endX, endY;
        if (sscanf(command.c_str(), "%d %d %d %d", &startX, &startY, &endX, &endY) != 4) {
            cout << "Invalid input format." << endl;
            continue;
        }

        if (chessBoard.movePiece(startX, startY, endX, endY)) {
            chessBoard.printBoard(); // Print the board after a successful move
        }
    }

    return 0;
}
