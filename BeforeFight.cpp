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




void AdjustShieldedPriorityandReorder(Castle& Cstl, float c1, float c2, float c3)
{
	for (int i = 0; i < 4; i++) // For each Region do following
	{
		if (Cstl.towers[i].Region == NULL)
			continue;
		enemy*temp1 = Cstl.towers[i].Region;
		while (temp1 != NULL) // Give Shielded new Priority
		{
			if (temp1->Type == 2)
				temp1->Priority = (temp1->PW / temp1->Distance)*c1 + (c2 / (temp1->RemainingTimetoShoot + 1)) + temp1->Health*c3;
			else
				break;
			temp1 = temp1->link;

		}

		//ReorderShielded
		
		temp1 = Cstl.towers[i].Region; // i will use it as curr ptr
		enemy*temp2 = NULL; //i will use it as walker ptr
		while (!!temp1->link && !!temp1->link->Priority)
		{
			temp2 = temp1->link;
			enemy *max = temp1;

			while (!!temp2&&!!temp2->Priority)

			{
				if (temp2->Priority > max->Priority)
					max = temp2;

				temp2 = temp2->link;
			}
			if (max != temp1) {
				enemy E;
				//
				E.Distance = temp1->Distance;
				E.Health = temp1->Health;
				E.ID = temp1->ID;
				E.Priority = temp1->Priority;
				E.PW = temp1->PW;
				E.Region = temp1->Region;
				E.Reload_Period = temp1->Reload_Period;
				E.RemainingTimetoShoot = temp1->RemainingTimetoShoot;
				E.TimeStep = temp1->TimeStep;
				E.Type = temp1->Type;
				E.firstshot = temp1->firstshot;
				E.TFS = temp1->TFS;
				E.KTS = temp1->KTS;

				//
				temp1->Distance = max->Distance;
				temp1->Health = max->Health;
				temp1->ID = max->ID;
				temp1->Priority = max->Priority;
				temp1->PW = max->PW;
				temp1->Region = max->Region;
				temp1->Reload_Period = max->Reload_Period;
				temp1->RemainingTimetoShoot = max->RemainingTimetoShoot;
				temp1->TimeStep = max->TimeStep;
				temp1->Type = max->Type;
				temp1->firstshot = max->firstshot;
				temp1->TFS = max->TFS;
				temp1->KTS = max->KTS;
				//
				max->Distance = E.Distance;
				max->Health = E.Health;
				max->ID = E.ID;
				max->Priority = E.Priority;
				max->PW = E.PW;
				max->Region = E.Region;
				max->Reload_Period = E.Reload_Period;
				max->RemainingTimetoShoot = E.RemainingTimetoShoot;
				max->TimeStep = E.TimeStep;
				max->Type = E.Type;
				max->firstshot = E.firstshot;
				max->TFS = E.TFS;
				max->KTS = E.KTS;
				//
			}

			temp1 = temp1->link;
		}

	}

}


