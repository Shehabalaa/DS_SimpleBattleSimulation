#include "Header.h"

void PrintTest(Castle& Cstl,int CurrentTimeStep)
{
	    ofstream Outfile("Result.txt", ios::app);
		Outfile << "At Current Time Step = " << CurrentTimeStep << endl;// for future printg int current timestep

		//int  activeenemies = 0;
		for (int i = 0; i < 4; i++)
		{
			//For every region
			if (i == 0) Outfile << "Region A " << endl;
			else if (i == 1) Outfile << "Region B " << endl;
			else if (i == 2) Outfile << "Region C" << endl;
			else  Outfile << "Region D" << endl;
			if (Cstl.towers[i].Region == NULL)
			{
				Outfile << "Empty\n";
				Outfile << "---------------------------------------------------------" << endl;
				continue;
			}

			enemy * ptrActive = Cstl.towers[i].Region;
			/*int activeenemies = 0;
			while (ptrActive != NULL) //get number of active enemies
			{SampleFunction
				if (ptrActive->data_enemy.TimeStep <= CurrentTimeStep)
					activeenemies++;
				ptrActive = ptrActive->link;

			}*/

			ptrActive = Cstl.towers[i].Region;//start printing active enemies
			Outfile << "Enimies:"  << endl;
			Outfile << setiosflags(ios::left) << setw(5) << "ID" << setw(7) << "Type" << setw(11) << "TimeStep";
			Outfile << setw(9) << "Health" << setw(12) << "FirePower" << "Priority" << endl;
			while (ptrActive != NULL)
			{
				//if (ptrActive->data_enemy.TimeStep <= CurrentTimeStep)
				//{
					Outfile << setiosflags(ios::left) << setw(5) << ptrActive->ID << setw(7) << ptrActive->Type;
					Outfile << setw(11) << ptrActive->TimeStep << setw(9) << ptrActive->Health;
					Outfile << setw(12) << ptrActive->PW << ptrActive->Priority << endl;
				//}
				ptrActive = ptrActive->link;
			}


	}

		Outfile.close();

}
