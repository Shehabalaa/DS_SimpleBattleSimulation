#include "Header.h"
using namespace std;

void main() {
	int gamemode = 0;
	cout << "Please Select Gamemode:\n";
	cout << "1.interactive mode.\n";
	cout << "2.step-by-step mode.\n";
	cout << "3.silent mode.\n";
	cin>> gamemode;


	Castle Cstl;
	enemy** enemies_show = NULL; // will hold array of pointers that point to enemies ready for graph
	float c1, c2, c3;
	SetWindow();
	Cstl.Xstrt = CastleXStrt;
	Cstl.Ystrt = CastleYStrt;
	Cstl.W = CastleWidth;
	Cstl.L = CastleLength;
	int CurrentTimeStep=0;
	int gameresult = 0; // 0 game is on 1 means win 2 means lose 3 means draw

	if (!FileloadData(Cstl, c1, c2, c3))//Read Data
	{
		cout << "File (test.txt) doesnot exist:\nPlease rename any sample file in project folder to (test.txt)" << endl;
		return;
	}
	Firstorder(Cstl);
	while (gameresult==0)
	{
		AdjustShieldedPriorityandReorder(Cstl,c1,c2,c3);
		PrintTest(Cstl, CurrentTimeStep);
		






		//beginig of graph
		DrawCastle(Cstl,CurrentTimeStep);
		int arrsize = 0;
		enemies_show = EnimiesReadyForGraph(Cstl,CurrentTimeStep,arrsize); //get ready enmies to draw
		if (enemies_show != NULL)
			DrawEnemies(enemies_show, arrsize);


		for (int i = 0; i < arrsize; i++)
			enemies_show[i]->Distance--;

			delete[] enemies_show;// remove after graph
			cin.get();
		CurrentTimeStep++;
	}


	if (gamemode == 3)
		PrintstatisticFile(Cstl);


	

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

