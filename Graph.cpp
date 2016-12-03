#include "Header.h"

/*A function to set the position of cursor on the screen*/
void gotoxy(int x, int y)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	_COORD pos;
	pos.X = x;
	pos.Y = y;

	SetConsoleCursorPosition(hConsole, pos);
}
///////////////////////////////////////////////////////////////////////////////////////

/*A function to set the command window lenght and height for the game specification*/
void SetWindow()
{
	system("mode 150,50");   //Set mode to ensure window does not exceed buffer size
	SMALL_RECT WinRect = { 0, 0, CmdWidth, CmdHeight };   //New dimensions for window in 8x12 pixel chars
	SMALL_RECT* WinSize = &WinRect;
	SetConsoleWindowInfo(GetStdHandle(STD_OUTPUT_HANDLE), true, WinSize);   //Set new size for window
}
///////////////////////////////////////////////////////////////////////////////////////

/*A function to color the cmd text*/
void color(int thecolor)
{
	HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hStdout,
		thecolor | FOREGROUND_INTENSITY);
}
///////////////////////////////////////////////////////////////////////////////////////

/*A function to partition the Castle into regions (A,B,C,D)*/
void DrawRegions(const Castle & C)
{
	color(FOREGROUND_RED | FOREGROUND_BLUE);
	gotoxy(0, C.Ystrt + C.L / 2);
	for (int i = 0; i<C.W + 2 * C.Xstrt; i++)
		cout << "-";
	for (int j = 0; j<C.L + 2 * C.Ystrt; j++)
	{
		gotoxy(C.Xstrt + C.W / 2, j);
		cout << "|";
	}
	color(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
}
///////////////////////////////////////////////////////////////////////////////////////

/*A function to draw the Castle and the towers*/
void DrawCastle(const Castle & C, int SimulationTime)
{
	system("CLS");

	//Draw the Castle
	cout << endl;
	gotoxy(C.Xstrt, C.Ystrt);
	for (int i = 0; i<C.W; i++)
		cout << "=";
	for (int j = 1; j<C.L; j++)
	{
		gotoxy(C.Xstrt, C.Ystrt + j);
		cout << "|";
		gotoxy(C.Xstrt + C.W - 1, C.Ystrt + j);
		cout << "|";
	}
	gotoxy(C.Xstrt, C.Ystrt + C.L - 1);
	for (int i = 0; i<C.W; i++)
		cout << "=";

	//Draw towers
	int T1X, T2X, T3X, T4X, T1Y, T2Y, T3Y, T4Y;
	for (int i = 0; i<4; i++)
	{

		if (i == 0)
		{
			T1X = C.Xstrt + 1;
			T1Y = C.Ystrt + TowerLength;
			gotoxy(T1X, T1Y);
			for (int i = 0; i<TowerWidth; i++)
				cout << "=";
			gotoxy(T1X + 1, T1Y - 1);
			cout << "T1" << "(" << C.towers[0].Health << ")";

			gotoxy(C.Xstrt + C.W / 4, C.Ystrt + C.L / 4);
			cout << "(A)";
		}
		else if (i == 1)
		{
			T2X = C.Xstrt + C.W - 2 - TowerWidth;
			T2Y = T1Y;
			gotoxy(T2X, T2Y);
			for (int i = 0; i<TowerWidth + 1; i++)
				cout << "=";
			gotoxy(T2X + 1, T2Y - 1);
			cout << "T2" << "(" << C.towers[1].Health << ")";
			gotoxy(C.Xstrt + (3 * C.W / 4), C.Ystrt + C.L / 4);
			cout << "(B)";
		}
		else if (i == 2)
		{
			T3X = T2X;
			T3Y = C.Ystrt + C.L - TowerLength - 1;;
			gotoxy(T3X, T3Y);
			for (int i = 0; i<TowerWidth + 1; i++)
				cout << "=";
			gotoxy(T3X + 1, T3Y + 1);
			cout << "T3" << "(" << C.towers[2].Health << ")";
			gotoxy(C.Xstrt + (3 * C.W / 4), C.Ystrt + (3 * C.L / 4) - 1);
			cout << "(C)";

		}
		else
		{
			T4X = T1X;
			T4Y = C.Ystrt + C.L - TowerLength - 1;
			gotoxy(T4X, T4Y);
			for (int i = 0; i<TowerWidth; i++)
				cout << "=";
			gotoxy(T4X + 1, T4Y + 1);
			cout << "T4" << "(" << C.towers[3].Health << ")";
			gotoxy(C.Xstrt + (C.W / 4), C.Ystrt + (3 * C.L / 4) - 1);
			cout << "(D)";

		}
	}


	DrawRegions(C);

	//****************************
	gotoxy(CmdWidth / 2 - 10, CmdHeight - 1);
	cout << "Simulation Time : " << SimulationTime << endl;
}

///////////////////////////////////////////////////////////////////////////////////////

/*A function to draw a single enemy using its distance from the Castle*/
void DrawEnemy(const enemy& E, int Ypos)
{
	int x, y;
	//First calcuale x,y position of the enemy on the output screen
	//It depends on the region and the enemy distance
	switch (E.Region)
	{
	case 0:
		x = CastleXStrt - E.Distance ;
		y = (CmdHeight / 2) - (CastleLength / 4) - Ypos;
		break;
	case 1:
		x = CastleXStrt + CastleWidth + E.Distance - 1;
		y = (CmdHeight / 2) - (CastleLength / 4) - Ypos;
		break;
	case 2:
		x = CastleXStrt + CastleWidth + E.Distance - 1;
		y = (CmdHeight / 2) + (CastleLength / 4) + Ypos;
		break;
	default:
		x = CastleXStrt - E.Distance ;
		y = (CmdHeight / 2) + (CastleLength / 4) + Ypos;

	}

	gotoxy(x, y);

	//set enemy color according to it type
	switch (E.Type)
	{
	case 2:
		color(FOREGROUND_GREEN);
		break;
	case 1:
		color(FOREGROUND_RED | FOREGROUND_GREEN);//Yellow
		break;
	default:
		color(FOREGROUND_RED);
	}

	if(E.Region==1|| E.Region == 2)
	cout << (char)EnemyShapeRight; //Draw the enemy
	else cout << (char)EnemyShapeLeft;
	color(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
}
///////////////////////////////////////////////////////////////////////////////////////

/*A function to draw a list of enemies and ensure there is no overflow in the drawing*/
//To use this function, you must prepare its input parameters as specified
//Input Parameters:
// enemies [ ] : array of enemy pointers (ALL enemies from all regions in one array)
// size : the size of the array (total no. of enemies)
void DrawEnemies(enemy* enemies[], int size)
{
	//draw enemies at each region 
	for (int region = 0; region <= 3; region++)
	{
		int CountEnemies = 0;	//count Enemies at the same distance to draw them vertically if they are <= 15 enemy else print number of enemy in the region
		bool draw = true;
		for (int distance = ((CmdWidth / 2) - (CastleWidth / 2)); distance>1; distance--)
		{
			CountEnemies = 0;

			for (int i = 0; i<size; i++)
			{
				if (enemies[i]->Distance == distance && enemies[i]->Region == region)
				{
					CountEnemies++;
				}
			}
			if (CountEnemies>15)
			{
				draw = false;
				break;
			}

		}
		if (draw)
		{
			for (int distance = ((CmdWidth / 2) - (CastleWidth / 2)); distance>1; distance--)
			{
				CountEnemies = 0;

				for (int i = 0; i<size; i++)
				{
					if (enemies[i]->Distance == distance && enemies[i]->Region == region)
					{
						DrawEnemy(*(enemies[i]), CountEnemies);
						CountEnemies++;
					}
				}

			}


		}
		else // print message maximum reached in this region
		{
			int x; int y;
			if (region == 0)
			{
				x = CastleXStrt - 30;
				y = (CmdHeight / 2) - (CastleLength / 4);
			}
			else if (region == 1)
			{
				x = CastleXStrt + CastleWidth + 30;
				y = (CmdHeight / 2) - (CastleLength / 4);


			}
			else if (region == 2)
			{
				x = CastleXStrt + CastleWidth + 30;
				y = (CmdHeight / 2) + (CastleLength / 4);

			}
			else
			{
				x = CastleXStrt - 30;
				y = (CmdHeight / 2) + (CastleLength / 4);

			}
			gotoxy(x, y);
			cout << "Maximum limit";
		}

	}
	gotoxy(0, CmdHeight - 1);
}
///////////////////////////////////////////////////////////////////////////////////////

/*This function to print statistics to the user*/
void PrintStatistics(Castle Cstl,int CurrentTimeStep)
{
cout<<"Total current eneimes\t";
cout<<"A = ";
cout << getnumberofactive(Cstl.towers[0].Region, CurrentTimeStep);
cout<<"\tB = ";
cout << getnumberofactive(Cstl.towers[1].Region, CurrentTimeStep);
cout<<"\tC = ";
cout << getnumberofactive(Cstl.towers[2].Region, CurrentTimeStep);
cout<<"\tD = ";
cout << getnumberofactive(Cstl.towers[3].Region, CurrentTimeStep);

cout<<"\nLast time step kill\t";
cout<<"A = ";
cout << getnumberofkilledat(Cstl.towers[0].DeadInRegion, CurrentTimeStep - 1);
cout<<"\tB = ";
cout << getnumberofkilledat(Cstl.towers[1].DeadInRegion, CurrentTimeStep - 1);
cout<<"\tC = ";
cout << getnumberofkilledat(Cstl.towers[2].DeadInRegion, CurrentTimeStep - 1);
cout<<"\tD = ";
cout << getnumberofkilledat(Cstl.towers[3].DeadInRegion, CurrentTimeStep - 1);


cout<<"\nTotal killed by\t\t";
cout<<"A = ";
cout<< getTotalnumberofKilled(Cstl.towers[0].DeadInRegion);
cout<<"\tB = ";
cout << getTotalnumberofKilled(Cstl.towers[1].DeadInRegion);
cout<<"\tC = ";
cout << getTotalnumberofKilled(Cstl.towers[2].DeadInRegion);
cout<<"\tD = ";
cout << getTotalnumberofKilled(Cstl.towers[3].DeadInRegion);



cout<<"\nUnpaved distance\t";
cout<<"A = ";
cout << Cstl.towers[0].unpaved_dsitanse;
cout<<"\tB = ";
cout << Cstl.towers[1].unpaved_dsitanse;
cout<<"\tC = ";
cout << Cstl.towers[2].unpaved_dsitanse;
cout<<"\tD = ";
cout << Cstl.towers[3].unpaved_dsitanse;

cout << endl;
}

// this fucntion helps to return nubmer of active enemies in ant region
int getnumberofactive(enemy *temp,int CurrentTimeStep)
{
	int num = 0;
	while (!!temp)
	{
		if (temp->TimeStep <= CurrentTimeStep)
			num++;
		else if(temp->Type != 2)
			break;
		temp = temp->link;

	}
	return num;

}


// this fucntion helps to return nubmer of killed enemies in any regiosn at certian timestep
int getnumberofkilledat(enemy* temp , int TimeStep)
{
	int num = 0;
	if (TimeStep == -1)
		return num;
	while (!!temp)
	{
		if (temp->KTS == TimeStep)
			num++;
		temp = temp->link;
	}
	return num;
}



// this fucntion helps to return total nubmer of killed enemies in such  region
int getTotalnumberofKilled(enemy* temp)
{
	int num = 0;
	while (!!temp)
	{
			num++;
		temp = temp->link;

	}
	return num;
}