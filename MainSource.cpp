#include "Header.h"
using namespace std;

void main() {
	int gamemode = 0;
	cout << "Please Select Gamemode:\n";
	cout << "1.interactive mode.\n";
	cout << "2.step-by-step mode.\n";
	cout << "3.silent mode.\n";
	cin >> gamemode;
	cin.ignore();


	Castle Cstl;
	enemy** enemies_show = NULL; // will hold array of pointers that point to enemies ready for graph
	float c1, c2, c3;
	SetWindow();
	Cstl.Xstrt = CastleXStrt;
	Cstl.Ystrt = CastleYStrt;
	Cstl.W = CastleWidth;
	Cstl.L = CastleLength;
	int CurrentTimeStep = -1;
	if (gamemode == 2)
		(CurrentTimeStep = -2);
	int gameresult = 0; // 0 game is on 1 means win 2 means lose 3 means draw
	int TOT_enemies = 0; // total number of enemies

	if (!FileloadData(Cstl, c1, c2, c3, TOT_enemies))//Read Data
	{
		cout << "File (test.txt) doesnot exist:\nPlease rename any sample file in project folder to (test.txt)" << endl;
		return;
	}
	Firstorder(Cstl);


	while (gameresult == 0)
	{
		CurrentTimeStep++;

		// Directly before fight
		if (CurrentTimeStep >= 0) // in step by step we start with -1 showing only screen
			AdjustShieldedPriorityandReorder(Cstl, c1, c2, c3);



		//Fight Logic

		if(CurrentTimeStep>=0) // in step by step we start with -1 showing only screen
			Fight(Cstl,CurrentTimeStep);

		// After Fight

		AdjustDistance(Cstl,CurrentTimeStep);
		bool x=CheckTowersAndEnemiesRegions(Cstl); //to adjust regions
		if(x)
			Firstorder(Cstl);
		

		if (gamemode != 3)
		{
			DrawCastle(Cstl, CurrentTimeStep);
			int arrsize = 0;
			enemies_show = EnimiesReadyForGraph(Cstl, CurrentTimeStep, arrsize); //get ready enmies to draw
			if (enemies_show != NULL)
				DrawEnemies(enemies_show, arrsize);

			PrintStatistics(Cstl, CurrentTimeStep);// Print all Statistics on screen


			if (CurrentTimeStep == -1 && gamemode == 2) cout<<"\nPress ENTER to start motion demo";
			if (gamemode == 2) cin.get();

			delete[] enemies_show;// remove after graph

			if (gamemode == 1) Sleep(1000);

		}


		gameresult = CheckGameReuslt(Cstl); // determine game result

		if (gameresult == 1)
			cout << "Game is Win:\n";
		else if(gameresult ==2)
			cout << "Game is Lose:\n";
		else if (gameresult == 3)
			cout << "Game is Draw :\n";
		// if game result == 0 game continue


	}

	


	if (gamemode == 3)
	{
		PrintstatisticFile(Cstl, gameresult, TOT_enemies);
		cout << "Please Check Statistics file:\n";
	}


}
	





/*
update hp check
loop(N(numberofenemies) of Tower)
{
if (acive)
{
if (priorty > 0)
{
update its hp
N--
}
else
{
update its hp
N--
}
}
else if (low)
break;
}

*/

