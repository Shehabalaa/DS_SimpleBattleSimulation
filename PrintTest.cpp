#include "Header.h"

void PrintTest(Node** Regions, Castle& Cstl,int CurrentTimeStep)
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
			if (Regions[i] == NULL)
			{
				Outfile << "Empty\n";
				Outfile << "---------------------------------------------------------" << endl;
				continue;
			}

			Node * ptrActive = Regions[i];
			/*int activeenemies = 0;
			while (ptrActive != NULL) //get number of active enemies
			{SampleFunction
				if (ptrActive->data_enemy.TimeStep <= CurrentTimeStep)
					activeenemies++;
				ptrActive = ptrActive->link;

			}*/

			ptrActive = Regions[i];//start printing active enemies
			Outfile << "Enimies:"  << endl;
			Outfile << setiosflags(ios::left) << setw(5) << "ID" << setw(7) << "Type" << setw(11) << "TimeStep";
			Outfile << setw(9) << "Health" << setw(12) << "FirePower" << "Priority" << endl;
			while (ptrActive != NULL)
			{
				//if (ptrActive->data_enemy.TimeStep <= CurrentTimeStep)
				//{
					Outfile << setiosflags(ios::left) << setw(5) << ptrActive->data_enemy.ID << setw(7) << ptrActive->data_enemy.Type;
					Outfile << setw(11) << ptrActive->data_enemy.TimeStep << setw(9) << ptrActive->data_enemy.Health;
					Outfile << setw(12) << ptrActive->data_enemy.PW << ptrActive->data_enemy.Priority << endl;
				//}
				ptrActive = ptrActive->link;
			}


	}

		Outfile.close();

}
