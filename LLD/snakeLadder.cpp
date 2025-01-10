#include <bits/stdc++.h>
using namespace std;

class Player
{
public:
    string id;
    int position;
};
class Dice
{
public:
    int totalDice;
    Dice()
    {
        this->totalDice = 1;
    }
    Dice(int totalDice)
    {
        this->totalDice = totalDice;
    }
    int rollDice()
    {
        int sum = 0;
        int total_dice = totalDice;
        while (total_dice-- > 0)
        {
            sum += rand() % 6 + 1;
        }
        return sum;
    }
};
class Jump
{
public:
    int start;
    int end;
};
class Cells
{
public:
    Jump *jump;
};
class Board
{
public:
    int n;
    vector<vector<Cells *>> board;
    Board() {}
    Board(int n, int snakes, int ladders)
    {
        this->n = n;
        board.resize(n, vector<Cells *>(n));
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {

                board[i][j] = new Cells();
                board[i][j]->jump = NULL;
            }
        }
        for (int i = 0; i < snakes; i++)
        {
            int start, end;
            do
            {
                start = rand() % (n * n - 1) + 1;
                end = rand() % start;
            } while (start / n == end / n || start <= end);
            cout << start << " " << end << endl;
            board[start / n][start % n]->jump = new Jump();
            board[start / n][start % n]->jump->start = start;
            board[start / n][start % n]->jump->end = end;
        }
        for (int i = 0; i < ladders; i++)
        {
            int start, end;
            do
            {
                start = rand() % (n * n - 1) + 1;
                end = rand() % (n * n - start) + start;
            } while (start / n == end / n || start >= end);
            cout << start << " " << end << endl;
            board[start / n][start % n]->jump = new Jump();
            board[start / n][start % n]->jump->start = start;
            board[start / n][start % n]->jump->end = end;
        }
    }
};
class Game
{
public:
    Board *boardObj;
    Dice *dice;
    queue<Player *> players;
    Player *winner;
    Game() {}
    Game(int n, int snakes, int ladders, int totalDice)
    {
        // cout << "Game constructor" << endl;
        boardObj = new Board(n, snakes, ladders);
        dice = new Dice(totalDice);
        winner = NULL;
        addPlayers();
    }
    void addPlayers()
    {
        for (int i = 0; i < 2; i++)
        {
            Player *player = new Player();
            player->id = to_string(i);
            player->position = 0;
            players.push(player);
        }
    }
    void startGame()
    {

        // cout << "Game started" << endl;
        while (winner == NULL)
        {

            Player *p = players.front();
            players.pop();
            cout << "Player " << p->id << " turn" << ", " << "current position:" << p->position << " ";
            int diceValue = dice->rollDice();
            int newPosition = p->position + diceValue;
            newPosition = jumpCheck(newPosition);
            cout << "new position:" << newPosition << endl;

            if (newPosition >= (boardObj->n * boardObj->n))
            {
                winner = p;
                cout << "Player " << p->id << " wins" << endl;
                break;
            }
            p->position = newPosition;
            players.push(p);
        }
    }
    int jumpCheck(int position)
    {
        int row = position / (boardObj->n);
        int col = position % (boardObj->n);
        if (boardObj->board[row][col]->jump)
        {
            int newPosition = boardObj->board[row][col]->jump->end;
            if (newPosition >= (boardObj->n * boardObj->n))
            {
                return position;
            }
            return newPosition;
        }
        return position;
    }
};
int main()
{
    srand(time(0)); // Seed the random number generator

    int n, snakes, ladders, totalDice;
    cout << "Enter the board size, number of snakes, number of ladders and total dice" << endl;
    cin >> n >> snakes >> ladders >> totalDice;

    Game *game = new Game(n, snakes, ladders, totalDice);
    game->startGame();
    return 0;
}