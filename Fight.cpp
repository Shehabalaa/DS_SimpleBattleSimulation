#include "Header.h"

void Fight(Castle& Cstl, int CurrentTimeStep)
{
	float k = 0; float DTE = 0; float DET = 0; //D = damage T =TOWER E = ENEMY TOT=TOTAL

	for (int i = 0; i < 4; i++)
	{
		int No_ofEnemies = 1;
		enemy * temp = Cstl.towers[i].Region;

		while (temp != NULL && No_ofEnemies <= Cstl.towers[i].N_enemies)
		{
			if (temp->TimeStep <= CurrentTimeStep)
			{
				if (temp->Type == 2)
				{
					k = 2;
					DTE = ((float(1) / temp->Distance)*Cstl.towers[i].F_Pow*(1 / k));
					temp->Health -= DTE;
					No_ofEnemies++;
					Cstl.towers[i].TotlaDamage += DTE;
					if (temp->firstshot)
					{
						temp->TFS = CurrentTimeStep;
						temp->firstshot = false;
					}

					if (temp->Health <= 0)
					{
						temp->Health = 0;
						temp->KTS = CurrentTimeStep;

					}


				}

				else
				{

					k = 1;
					DTE = ((float(1) / temp->Distance)*Cstl.towers[i].F_Pow*(1 / k));
					temp->Health -= DTE;
					No_ofEnemies++;
					Cstl.towers[i].TotlaDamage += DTE;
					if (temp->firstshot)
					{
						temp->TFS = CurrentTimeStep;
						temp->firstshot = false;
					}

					if (temp->Health <= 0)
					{
						temp->Health = 0;
						temp->KTS = CurrentTimeStep;

					}

				}
			}
			else if (temp->Type != 2)
				break;


			temp = temp->link;

		}

	}

	adjustkilled(Cstl);// to move killed for their list to deadlist


	for (int i = 0; i < 4; i++)
	{

		enemy * temp2 = Cstl.towers[i].Region;
		while (temp2 != NULL)
		{
			if (temp2->TimeStep <= CurrentTimeStep && temp2->Type != 0)
			{
				if (temp2->RemainingTimetoShoot == 0)
				{
					if (temp2->Type == 2)
						k = 2;
					else
						k = 1;

					DET = ((k / temp2->Distance)*temp2->PW);
					Cstl.towers[i].Health -= int(DET);
					temp2->RemainingTimetoShoot = temp2->Reload_Period;
				}

				else if (temp2->RemainingTimetoShoot > 0) temp2->RemainingTimetoShoot--;
			}

			else if (temp2->TimeStep > CurrentTimeStep&&temp2->Type != 2)
				break;

			
			temp2 = temp2->link;
		}
		if (Cstl.towers[i].Health < 0) Cstl.towers[i].Health = 0;
	}


}