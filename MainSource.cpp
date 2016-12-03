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
		AdjustShieldedPriorityandReorder(Cstl, c1, c2, c3);







		//Fight Logic

		Fight(Cstl,CurrentTimeStep);

		// After Fight










		PrintTest(Cstl, CurrentTimeStep);









		



		if (gamemode != 3)//start by showing the enemies
		{
			DrawCastle(Cstl, CurrentTimeStep);
			int arrsize = 0;
			enemies_show = EnimiesReadyForGraph(Cstl, CurrentTimeStep, arrsize); //get ready enmies to draw
			if (enemies_show != NULL)
				DrawEnemies(enemies_show, arrsize);



			PrintMsg("Total current eneimes\t");
			PrintMsg("A = ");
			cout << getnumberofactive(Cstl.towers[0].Region, CurrentTimeStep);
			PrintMsg("\tB = ");
			cout << getnumberofactive(Cstl.towers[1].Region, CurrentTimeStep);
			PrintMsg("\tC = ");
			cout << getnumberofactive(Cstl.towers[2].Region, CurrentTimeStep);
			PrintMsg("\tD = ");
			cout << getnumberofactive(Cstl.towers[3].Region, CurrentTimeStep);

			PrintMsg("\nLast time step kill\t");
			PrintMsg("A = ");
			cout << getnumberofkilledat(Cstl.towers[0].DeadInRegion, CurrentTimeStep - 1);
			PrintMsg("\tB = ");
			cout << getnumberofkilledat(Cstl.towers[1].DeadInRegion, CurrentTimeStep - 1);
			PrintMsg("\tC = ");
			cout << getnumberofkilledat(Cstl.towers[2].DeadInRegion, CurrentTimeStep - 1);
			PrintMsg("\tD = ");
			cout << getnumberofkilledat(Cstl.towers[3].DeadInRegion, CurrentTimeStep - 1);


			PrintMsg("\nTotal killed by\t\t");
			PrintMsg("A = ");
			cout << getTotalnumberofKilled(Cstl.towers[0].DeadInRegion);
			PrintMsg("\tB = ");
			cout << getTotalnumberofKilled(Cstl.towers[1].DeadInRegion);
			PrintMsg("\tC = ");
			cout << getTotalnumberofKilled(Cstl.towers[2].DeadInRegion);
			PrintMsg("\tD = ");
			cout << getTotalnumberofKilled(Cstl.towers[3].DeadInRegion);



			PrintMsg("\nUnpaved distance\t");
			PrintMsg("A = ");
			cout << Cstl.towers[0].unpaved_dsitanse;
			PrintMsg("\tB = ");
			cout << Cstl.towers[1].unpaved_dsitanse;
			PrintMsg("\tC = ");
			cout << Cstl.towers[2].unpaved_dsitanse;
			PrintMsg("\tD = ");
			cout << Cstl.towers[3].unpaved_dsitanse;





			cout << endl;

			if (CurrentTimeStep == 0 && gamemode == 2) PrintMsg("\nPress ENTER to start motion demo");
			if (gamemode == 2) cin.get();

			for (int i = 0; i < arrsize; i++)///////////////////////////////////////////////////////////////////
				enemies_show[i]->Distance --;///////////////////////////////////////

			delete[] enemies_show;// remove after graph

			if (gamemode == 1) Sleep(1000);
			if (CurrentTimeStep == 60)
				break;



		}
	}




	if (gamemode == 3)
	{
		PrintstatisticFile(Cstl, gameresult, TOT_enemies);
		cout << "Please Check Statistics file:\n";
	}


}
	


/*
when go to fight 
if(!isshot)
{ptrnew->TFS=currenttimestep;
ishot=true;
}


wlma ymot 
ptrnew->KTS=currenttimestep; w5las
*/



























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

