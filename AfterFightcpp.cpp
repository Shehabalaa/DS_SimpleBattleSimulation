#include "Header.h"



void AdjustDistance(Castle& Cstl, int CurrentTimeStep) 
{

	for (int i = 0; i < 4; i++)
	{
		enemy* temp = Cstl.towers[i].Region; 

		while (temp != NULL&&Cstl.towers[i].unpaved_distance>2)
		{
			if (temp->TimeStep <= CurrentTimeStep)
			{
				if(temp->Type==0&&temp->Distance== Cstl.towers[i].unpaved_distance)
				{
					if (temp->RemainingTimetoShoot == 0)
					{
						Cstl.towers[i].unpaved_distance -= temp->PW;

						if (Cstl.towers[i].unpaved_distance < 2)
							Cstl.towers[i].unpaved_distance = 2;

						temp->RemainingTimetoShoot = temp->Reload_Period;
					}
					else
					{
						temp->RemainingTimetoShoot--;

					}
				}

			}
			else if(temp->Type != 2)
				break;
			temp = temp->link;
		}



		temp = Cstl.towers[i].Region;
		while (temp != NULL) 
		{
			if (temp->TimeStep <= CurrentTimeStep&& temp->Distance > 2)
			{



				if (temp->Distance > Cstl.towers[i].unpaved_distance)
					temp->Distance--;
				


			}
			else if (temp->TimeStep > CurrentTimeStep&&temp->Type != 2  ) // to avoid uselless traverse
				break;

			temp = temp->link;
		}
	}
}



bool CheckTowersAndEnemiesRegions(Castle& Cstl)
{
	bool x = false;
	for (int i = 0; i <= 4; i++)
	{
		if (Cstl.towers[i].Health == 0&& Cstl.towers[i].Region!=NULL)
		{


			if (Cstl.towers[(i + 1) % 4].Health > 0)
			{

				enemy * temp = Cstl.towers[i].Region;
				while (temp != NULL)
				{
					temp->Region = (i + 1) % 4;
					temp = temp->link;

				}
				append(Cstl.towers[(i + 1) % 4].Region,Cstl.towers[i].Region);
				afterappend(Cstl.towers[i].Region, Cstl.towers[(i + 1) % 4].unpaved_distance);
				Cstl.towers[i].Region = NULL;
				x = true;
			}
			else if (Cstl.towers[(i + 2) % 4].Health > 0)
			{

				enemy * temp = Cstl.towers[i].Region;
				while (temp != NULL)
				{
					temp->Region = (i + 2) % 4;
					temp = temp->link;

				}
				append(Cstl.towers[(i + 2) % 4].Region, Cstl.towers[i].Region);
				afterappend(Cstl.towers[i].Region, Cstl.towers[(i + 2) % 4].unpaved_distance);
				Cstl.towers[i].Region = NULL;
				x = true;
			}
			else if (Cstl.towers[(i + 3) % 4].Health > 0)

			{

				enemy  * temp = Cstl.towers[i].Region;
				while (temp != NULL)
				{
					temp->Region = (i + 3) % 4;
					temp = temp->link;

				}
				append(Cstl.towers[(i + 3) % 4].Region, Cstl.towers[i].Region);
				afterappend(Cstl.towers[i].Region, Cstl.towers[(i + 3) % 4].unpaved_distance);
				Cstl.towers[i].Region = NULL;
				x = true;
			}
			else 
				return x; // gamefinished all towers dead 
		}
		
	}
	return x;

}



int CheckGameReuslt(Castle Cstl) // detremine gameresult
{
	int gameresult = 0;
	if (Cstl.towers[0].Health == 0 && Cstl.towers[1].Health == 0 && Cstl.towers[2].Health == 0 && Cstl.towers[3].Health == 0)
		gameresult = 1;

	if (Cstl.towers[0].Region == NULL && Cstl.towers[1].Region == NULL && Cstl.towers[2].Region == NULL && Cstl.towers[3].Region == NULL)
		gameresult += 2;

	return gameresult;



}


