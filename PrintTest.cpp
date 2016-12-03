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
			
			ptrActive = Cstl.towers[i].Region;//start printing active enemies
			Outfile << "Enimies:"  << endl;
			Outfile << setiosflags(ios::left) << setw(5) << "ID" << setw(7) << "Type" << setw(11) << "TimeStep";
			Outfile << setw(9) << "TFS" << setw(12) << "Health" << "Priority" << endl;
			while (ptrActive != NULL)
			{
					Outfile << setiosflags(ios::left) << setw(5) << ptrActive->ID << setw(7) << ptrActive->Type;
					Outfile << setw(11) << ptrActive->TimeStep << setw(9) << ptrActive->TFS;
					Outfile << setw(12) << ptrActive->PW << ptrActive->Health << endl;

				ptrActive = ptrActive->link;
			}


	}

		Outfile.close();

}
