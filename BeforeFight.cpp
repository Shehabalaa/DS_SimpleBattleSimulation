#include "Header.h"

bool FileloadData(Castle &Cstl, float &c1, float &c2, float&c3,int&TOT)
{
	ifstream infile("test.txt", ios::in);
	if (!infile.is_open())
		return false;

	for (int i = 0; i < 4; i++) // Read towers
	{
		infile >> Cstl.towers[i].Health >> Cstl.towers[i].N_enemies >> Cstl.towers[i].F_Pow;
		Cstl.towers[i].Region = NULL;
		Cstl.towers[i].DeadInRegion = NULL;
		Cstl.towers[i].unpaved_distance = 30;
		Cstl.towers[i].TotlaDamage = 0;
	}

	infile >> c1 >> c2 >> c3; // Read constants

	//Readenemies
	while (!infile.eof()) {
		enemy* ptrnew = new enemy; //create new enemy pointed by ptr
		infile >> ptrnew->ID;

		if (ptrnew->ID == -1)
		{
			delete ptrnew;
			break;
		}
		char Region;
		infile>> ptrnew->Type >> ptrnew->TimeStep;
		infile >> ptrnew->Health >> ptrnew->PW >> ptrnew->Reload_Period;
		infile >> Region;
		if (Region == 'A')
			ptrnew->Region = 0;
		else if (Region == 'B')
			ptrnew->Region = 1;
		else if (Region == 'C')
			ptrnew->Region = 2;
		else ptrnew->Region = 3;
		ptrnew->Distance = 60;
		ptrnew->RemainingTimetoShoot = 0;
		ptrnew->Priority = 0;
		ptrnew->firstshot = true;
		ptrnew->KTS = -1;
		ptrnew->TFS = -1;


		if (Region == 'A')
			Addenemy(Cstl.towers[0].Region, ptrnew);

		else if (Region == 'B')
			Addenemy(Cstl.towers[1].Region, ptrnew);

		else if (Region == 'C')
			Addenemy(Cstl.towers[2].Region, ptrnew);
		else 
			Addenemy(Cstl.towers[3].Region, ptrnew);
		TOT++; // increase number of enemies
	}

	infile.close();
	return true; //end of function
}








