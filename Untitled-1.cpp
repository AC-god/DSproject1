#include <iostream>
#include <fstream>
using namespace std;
ifstream fin("Tetris.data");
ofstream fout("Tetris.final");
int T1[4][4] =
{
	{0, 0, 0, 0},
	{0, 0, 0, 0},
	{1, 1, 1, 0},
	{0, 1, 0, 0}
};
int T2[4][4] =
{
	{0, 0, 0, 0},
	{0, 1, 0, 0},
	{1, 1, 0, 0},
	{0, 1, 0, 0}
};
int T3[4][4] =
{
	{0, 0, 0, 0},
	{0, 0, 0, 0},
	{0, 1, 0, 0},
	{1, 1, 1, 0}
};
int T4[4][4] =
{
	{0, 0, 0, 0},
	{1, 0, 0, 0},
	{1, 1, 0, 0},
	{1, 0, 0, 0}
};
int L1[4][4] =
{
	{0, 0, 0, 0},
	{1, 0, 0, 0},
	{1, 0, 0, 0},
	{1, 1, 0, 0}
};
int L2[4][4] =
{
	{0, 0, 0, 0},
	{0, 0, 0, 0},
	{1, 1, 1, 0},
	{1, 0, 0, 0}
};
int L3[4][4] =
{
	{0, 0, 0, 0},
	{1, 1, 0, 0},
	{0, 1, 0, 0},
	{0, 1, 0, 0}
};
int L4[4][4] =
{
	{0, 0, 0, 0},
	{0, 0, 0, 0},
	{0, 0, 1, 0},
	{1, 1, 1, 0}
};
int J1[4][4] =
{
	{0, 0, 0, 0},
	{0, 1, 0, 0},
	{0, 1, 0, 0},
	{1, 1, 0, 0}
};
int J2[4][4] =
{
	{0, 0, 0, 0},
	{0, 0, 0, 0},
	{1, 0, 0, 0},
	{1, 1, 1, 0}
};
int J3[4][4] =
{
	{0, 0, 0, 0},
	{1, 1, 0, 0},
	{1, 0, 0, 0},
	{1, 0, 0, 0}
};
int J4[4][4] =
{
	{0, 0, 0, 0},
	{0, 0, 0, 0},
	{1, 1, 1, 0},
	{0, 0, 1, 0}
};
int S1[4][4] =
{
	{0, 0, 0, 0},
	{0, 0, 0, 0},
	{0, 1, 1, 0},
	{1, 1, 0, 0}
};
int S2[4][4] =
{
	{0, 0, 0, 0},
	{1, 0, 0, 0},
	{1, 1, 0, 0},
	{0, 1, 0, 0}
};
int Z1[4][4] =
{
	{0, 0, 0, 0},
	{0, 0, 0, 0},
	{1, 1, 0, 0},
	{0, 1, 1, 0}
};
int Z2[4][4] =
{
	{0, 0, 0, 0},
	{0, 1, 0, 0},
	{1, 1, 0, 0},
	{1, 0, 0, 0}
};
int I1[4][4] =
{
	{1, 0, 0, 0},
	{1, 0, 0, 0},
	{1, 0, 0, 0},
	{1, 0, 0, 0}
};
int I2[4][4] =
{
	{0, 0, 0, 0},
	{0, 0, 0, 0},
	{0, 0, 0, 0},
	{1, 1, 1, 1}
};
int O[4][4] =
{
	{0, 0, 0, 0},
	{0, 0, 0, 0},
	{1, 1, 0, 0},
	{1, 1, 0, 0}
};
int **board;
int row_end, row_begin = 3;
int m, n;
bool gamecontinue = true;
void showboard()
{
	for (int i = row_begin + 1; i <= row_end; i++)
	{
		for (int j = 1; j <= n; j++)
		{
			fout << board[i][j];
		}
		fout << "\n";
	}
	fout << "\n";
}
void is_gameover()
{
	for (int i = 0; i <= 3 && gamecontinue; i++)
	{
		for (int j = 1; j <= n; j++)
		{
			if (board[i][j] == 1)
			{
				gamecontinue = false;
			}
		}
	}
}
void disappear(int row)
{
	for (int j = 1; j <= n; j++)
	{
		board[row][j] = 0;
	}
	for (int i = row - 1; i >= 0; i--)
	{
		for (int j = 1; j <= n; j++)
		{
			if (board[i][j] == 1)
			{
				board[i][j] = 0;
				board[i + 1][j] = 1;
			}
		}
	}
}
void check()
{
	for (int i = row_end; i > row_begin;)
	{
		bool isfull = true;
		for (int j = 1; j <= n; j++)
		{
			if (board[i][j] == 0)
			{
				isfull = false;
				break;
			}
		}
		if (isfull)
		{
			disappear(i);
		}
		else
			i--;

	}
}
void movebrick(int brick[4][4], int pos)
{
	int newbrick[4][2] = {};
	int flag = 0;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (brick[i][j] == 1)
			{
				board[i][j + pos] = 1;
				newbrick[flag][0] = i;
				newbrick[flag][1] = j + pos;
				flag++;
			}
		}
	}
	while (1)
	{
		//cout << "!";
		//showboard();
		bool collide = false, out_of_bound = false;
		int i = 3;
		for (; i >= 0; i--)
		{

			if (newbrick[i][0] + 1 <= row_end)
			{
				if (board[newbrick[i][0] + 1][newbrick[i][1]] == 0)
				{
					board[newbrick[i][0] + 1][newbrick[i][1]] = 1;
					board[newbrick[i][0]][newbrick[i][1]] = 0;
					newbrick[i][0]++;
				}
				else
				{
					collide = true;
					//cout << "!";
					break;
				}
			}
			else
			{
				out_of_bound = true;
				break;
			}

		}
		if (out_of_bound)
		{
			check();
			break;
		}

		if (collide)
		{
			//check();
			i++;
			for (; i < 4; i++)
			{
				board[newbrick[i][0] - 1][newbrick[i][1]] = 1;
				board[newbrick[i][0]][newbrick[i][1]] = 0;
				newbrick[i][0]--;
			}
			check();
			is_gameover();
			break;
		}
		//showboard();
	}
}

int main()
{


	fin >> m >> n;
	row_end = m + 3;
	board = new int *[m + 4];
	for (int i = 0; i < m + 4; i++)
	{
		board[i] = new int[n + 5]{};
	}
	//showboard();
	string input;
	while (gamecontinue && fin >> input && input != "End")
	{
		int pos;
		fin >> pos;
		if (input == "T1")
		{
			movebrick(T1, pos);
			//showboard();
		}
		else if (input == "T2")
		{
			movebrick(T2, pos);
		}
		else if (input == "T3")
		{
			movebrick(T3, pos);
		}
		else if (input == "T4")
		{
			movebrick(T4, pos);
		}
		else if (input == "L1")
		{
			movebrick(L1, pos);
		}
		else if (input == "L2")
		{
			movebrick(L2, pos);
		}
		else if (input == "L3")
		{
			movebrick(L3, pos);
		}
		else if (input == "L4")
		{
			movebrick(L4, pos);
		}
		else if (input == "J1")
		{
			movebrick(J1, pos);
		}
		else if (input == "J2")
		{
			movebrick(J2, pos);
		}
		else if (input == "J3")
		{
			movebrick(J3, pos);
		}
		else if (input == "J4")
		{
			movebrick(J4, pos);
		}
		else if (input == "S1")
		{
			movebrick(S1, pos);
		}
		else if (input == "S2")
		{
			movebrick(S2, pos);
		}
		else if (input == "Z1")
		{
			movebrick(Z1, pos);
		}
		else if (input == "Z2")
		{
			movebrick(Z2, pos);
		}
		else if (input == "I1")
		{
			movebrick(I1, pos);
		}
		else if (input == "I2")
		{
			movebrick(I2, pos);
		}
		else if (input == "O")
		{
			movebrick(O, pos);
		}
		//check();
		//showboard();
	}
	showboard();
	return 0;
}
