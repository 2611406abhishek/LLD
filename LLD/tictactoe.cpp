#include <bits/stdc++.h>
using namespace std;

// create Enum for playing symbol like X , O
enum class playingPiece
{
    X,
    O,
    None
};

// player Class
class Player
{

public:
    string name;
    playingPiece pieceType;

    Player() {}
    Player(string name, playingPiece pieceType)
    {
        this->name = name;
        this->pieceType = pieceType;
    }
};

// Board
class Board
{

public:
    int size;
    playingPiece **board;

    Board() {}
    Board(int size)
    {
        this->size = size;
        this->board = new playingPiece *[size];
        for (int i = 0; i < size; ++i)
        {
            this->board[i] = new playingPiece[size];
            for (int j = 0; j < size; j++)
                board[i][j] = playingPiece::None;
        }
    }
    set<pair<int, int>> getFreeCell()
    {
        set<pair<int, int>> st;
        for (int i = 0; i < this->size; i++)
        {
            for (int j = 0; j < this->size; j++)
            {
                if (board[i][j] == playingPiece::None)
                    st.insert({i, j});
            }
        }
        return st;
    }

    bool makeMove(playingPiece pieceType, int row, int col)
    {
        set<pair<int, int>> st = getFreeCell();
        if (st.count({row, col}) == 0)
        {
            return false;
        }
        board[row][col] = pieceType;
        return true;
    }

    void Print()
    {

        for (int i = 0; i < this->size; i++)
        {
            for (int j = 0; j < this->size; j++)
            {
                if (board[i][j] == playingPiece::O)
                    cout << " O "
                         << " ";
                else if (board[i][j] == playingPiece::X)
                    cout << " X "
                         << " ";
                else if (board[i][j] == playingPiece::None)
                    cout << " . "
                         << " ";
            }
            cout << endl;
        }
    }
};

// TicToe
class TicTacToe
{

    deque<Player> list;
    Board gameBoard;

public:
    void initializeGame()
    {
        gameBoard = Board(3);
        Player p1("player1", playingPiece::X), p2("player2", playingPiece::O);
        list.push_back(p1);
        list.push_back(p2);
    }
    bool checkWinner(playingPiece pieceType, int row, int column)
    {
        bool rowMatch = true;
        bool columnMatch = true;
        bool diagonalMatch = true;
        bool antiDiagonalMatch = true;

        // need to check in row
        for (int i = 0; i < gameBoard.size; i++)
        {

            if (gameBoard.board[row][i] != pieceType)
            {
                rowMatch = false;
            }
        }

        // need to check in column
        for (int i = 0; i < gameBoard.size; i++)
        {

            if (gameBoard.board[i][column] != pieceType)
            {
                columnMatch = false;
            }
        }

        // need to check diagonals
        for (int i = 0, j = 0; i < gameBoard.size; i++, j++)
        {
            if (gameBoard.board[i][j] != pieceType)
            {
                diagonalMatch = false;
            }
        }

        // need to check anti-diagonals
        for (int i = 0, j = gameBoard.size - 1; i < gameBoard.size; i++, j--)
        {
            if (gameBoard.board[i][j] != pieceType)
            {
                antiDiagonalMatch = false;
            }
        }
        return rowMatch || columnMatch || diagonalMatch || antiDiagonalMatch;
    }
    string startGame()
    {

        bool isWin = true;
        while (isWin)
        {
            Player p = list.front();
            int r, c;
            gameBoard.Print();
            cout << p.name << " "
                 << " Enter row and col  : ";
            cin >> r >> c;
            if (gameBoard.getFreeCell().size() == false)
            {
                break;
            }
            if (gameBoard.makeMove(p.pieceType, r, c) == false)
            {
                cout << "Incorrect cell! Try Again : "
                     << " ";
                continue;
            }
            list.pop_front();
            list.push_back(p);
            if (checkWinner(p.pieceType, r, c) == true)
            {
                return p.name + " wins";
            }
            if (gameBoard.getFreeCell().size() == false)
            {
                break;
            }
        }
        return "tie";
    }
};
int main()
{

    TicTacToe t;
    t.initializeGame();
    cout << t.startGame() << endl;
    return 0;
}