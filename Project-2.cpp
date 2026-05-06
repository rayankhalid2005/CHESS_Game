#include <iostream>
using namespace std;
class Piece
{
private:
public:
	Piece();
	virtual bool isValidMove(int& sx, int& sy, int& ex, int& ey, Piece* board[8][8]) = 0;
	virtual bool isWhite() = 0; 
	virtual char getSymbol() = 0;
};

class Game
{
private:
	Piece* board[8][8];
	bool white;
public:
	Game();
	void startGame();
	void input(int &sx, int &sy, int &ex, int &ey);
	bool canMove(int& sx, int& sy, int& ex, int& ey);
	void doMove(int& sx, int& sy, int& ex, int& ey);
	bool isKingInDanger(bool whiteColor);
	bool isMoveSafe(int& sx, int& sy, int& ex, int& ey);
	bool isKingDead(bool whiteColor);
};
void Game::input(int &sx, int &sy,int &ex, int &ey)
{
	string f, t;
	cin >> f >> t;
	sx = f[0] - 'a';
	sy = 8 - (f[1] - '0');
	ex = t[0] - 'a';
	ey = 8 - (t[1] - '0');
}
bool Game::canMove(int &sx, int &sy, int &ex, int &ey)
{
	if (board[sx][sy] == nullptr)
		return false;
	if (board[sx][sy]->isWhite() != white)
		return false;
	if (board[ex][ey] != nullptr && board[ex][ey]->isWhite()==white)
		return false;
	if (board[ex][ey]->isValidMove(sx, sy, ex, ey, board) != true)
		return false;
	return true;
}
void Game::doMove(int& sx, int& sy, int& ex, int& ey)
{
	board[ex][ey] = board[sx][sy];
	board[sx][sy] = nullptr;
	white = false;
}
bool Game::isKingInDanger(bool whiteColor)
{
	int kx, ky;
	for (int i= 0;i<8 ; i++)
	{
		for (int j =0 ;j<8 ; j++)
		{
			if (board[i][j]!=nullptr && board[i][j]->isWhite()==whiteColor &&
				board[i][j]->getSymbol()=='k')
			{
				kx = i;
				ky = j;
			}
		}
	}
	for (int i= 0;i<8 ; i++)
	{
		for (int j = 0;j<8 ; j++)
		{
			if (board[i][j] && board[i][j]->isWhite() != whiteColor)
			{
				if (board[i][j]->isValidMove(i, j, kx, ky, board))
					return true;
			}
		}
	}
	return false;
}
bool Game::isMoveSafe(int&sx, int&sy, int&ex, int&ey)
{
	Piece* temp = board[ex][ey];
	board[ex][ey] = board[sx][sy];
	board[sx][sy] = nullptr;

	bool s = !isKingInDanger(white);

	board[sx][sy] = board[ex][ey];
	board[ex][ey] = temp;
	return s;
}
bool Game::isKingDead(bool whiteColor)
{
	for (int i =0 ;i<8 ; i++)
	{
		for (int j =0;j<8 ; j++)
		{
			if (board[i][j] && board[i][j]->isWhite()==whiteColor)
			{
				for (int m = 0;m<8 ; m++)
				{
					for (int n = 0;n<8 ; n++)
					{
						if (board[m][n]->isValidMove(i, j, m, n, board) && canMove(i,j,m,n))
						{
							if (isMoveSafe(i, j, m, n))
								return false;
						}
					}
				}
			}
		}
	}
	return true;
}
void Game::startGame()
{
	white = true;
	while (true)
	{
		int sx, sy, ex, ey;
		input(sx, sy, ex, ey);

		if (!canMove(sx, sy, ex, ey))
			continue;

		if (!board[sx][sy]->isValidMove(sx, sy, ex, ey, board))
		{
			cout << "\n<--You cannot move this way-->\n";
			continue;
		}

		if (!isMoveSafe(sx, sy, ex, ey))
		{
			cout << "\n<<--Your KING is in DANGER!-->\n";
			continue;
		}

		doMove(sx, sy, ex, ey);

		if (isKingDead(!white))
		{
			cout << "\nOoo! Your KING is DEAD\n";
			cout << "<<--CheckMate-->>\n";
			break;
		}

		white = !white;
	}
}
int main()
{

	system("pause");
	return 0;
}