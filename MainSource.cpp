#include "Header.h"
using namespace std;

void main() {
	Castle Cstl;
	Node* Regions[4];
	Node* DeadInRegions[4];
	enemy** enemies_show = NULL; // will hold array of pointers that point to enemies ready for graph
	float c1, c2, c3;
	SetWindow();
	Cstl.Xstrt = CastleXStrt;
	Cstl.Ystrt = CastleYStrt;
	Cstl.W = CastleWidth;
	Cstl.L = CastleLength;
	int CurrentTimeStep=0;
	
	Regions[0] = Regions[1] = Regions[2] = Regions[3] = NULL;
	DeadInRegions[0] = DeadInRegions[1] = DeadInRegions[2] = DeadInRegions[3] = NULL;

	if (!FileloadData(Regions, Cstl, c1, c2, c3))//Read Data
	{
		cout << "File (test.txt) doesnot exist:\nPlease rename any sample file in project folder to (test.txt)" << endl;
		return;
	}
	Firstorder(Regions);
	while (CurrentTimeStep < 9)
	{
		//AdjustShieldedPriorityandReorder(Regions,c1,c2,c3);
		//PrintTest(Regions, Cstl, CurrentTimeStep);
		


		
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

		



		//beginig of graph
		DrawCastle(Cstl,CurrentTimeStep);
		int arrsize = 0;
		enemies_show = EnimiesReadyForGraph(Regions,CurrentTimeStep,arrsize); //get ready enmies to draw
		if (enemies_show != NULL)
			DrawEnemies(enemies_show, arrsize);


		for (int i = 0; i < arrsize; i++)
			enemies_show[i]->Distance--;

			delete[] enemies_show;// remove after graph
		CurrentTimeStep++;
		cin.get();
	}





	/*for (int i = 0; i < 4; i++)
	{
	cout << Cstl.towers[i].F_Pow;
	cout << endl;


	}


	Node* temp1 = Regions[0];
	Node* temp2 = Regions[1];
	while (!!temp1)
	{
	cout << temp1->data_enemy.ID << " ";
	cout << temp1->data_enemy.Type << " ";
	cout << temp1->data_enemy.TimeStep << " ";

	cout << endl;
	temp1 = temp1->link;
	}
	while (!!temp2)
	{
	cout << temp2->data_enemy.Type << " ";
	cout << temp2->data_enemy.TimeStep << " ";

	cout << endl;
	temp2 = temp2->link;
	}

	cout << c1 << endl << c2 << endl << c3;*/


}