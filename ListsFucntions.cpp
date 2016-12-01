#include "Header.h"


void Addenemy(enemy*& head, enemy* ptrnew)
{
	ptrnew->link = head;
	head = ptrnew;


}

/*void Deleteenemy(Node* Pretemp)
{
	Node* Temp;
	Temp = Pretemp->link;
	Pretemp->link = Temp->link;
	delete Temp;

}*/


void Destroy(enemy*& head)
{
	enemy* temp;

	while (head != NULL)
	{
		temp = head;
		head = head->link;
		delete temp;
	}


}


/*void Removekilledenemies(Node** Regions, int CurrentTimeStep)
{
for (int i = 0; i < 4; i++)
{
Node* temp1;
Node* delltemp;
temp1 = Regions[i];
if (Regions[i] == NULL) continue;

while (temp1->link!=NULL)
{
if (temp1->link->data_enemy.TimeStep <= CurrentTimeStep&&temp1->link->data_enemy.Health == 0)
{
delltemp = temp1->link;
temp1->link = delltemp->link;
delete delltemp;

}
else
delltemp = delltemp->link;

}

if (Regions[i]->data_enemy.Health == 0)
{
delltemp = Regions[i];
Regions[i] = Regions[i]->link;
}




}

}*/


void Firstorder(Castle& Cstl)
{
	//	GetShieldedFisrt(at top of linked list)
	enemy* temp1=NULL;
	enemy* temp2 = NULL;
	for (int i = 0; i < 4; i++)
	{
		if (Cstl.towers[i].Region == NULL) continue;
		temp1 = Cstl.towers[i].Region;

		while (!!temp1->link)
		{
			if (temp1->link->Type == 2)
			{
				temp2 = temp1->link;
				temp1->link = temp1->link->link;
				Addenemy(Cstl.towers[i].Region,temp2);
			}
			else 
				temp1 = temp1->link;
			
		}

		//      Sort enemies after shielded by timestep
		temp1 = Cstl.towers[i].Region;
		temp2 = NULL;
		while (temp1 != NULL&&temp1->Type == 2)
			temp1 = temp1->link;

		while (!!temp1)
		{
			temp2 = temp1->link;
			while (!!temp2)

			{
				enemy*temp3 = new enemy;
				if (temp1->TimeStep>temp2->TimeStep)
				{
					//
					temp3->Distance = temp1->Distance;
					temp3->Health = temp1->Health;
					temp3->ID = temp1->ID;
					temp3->Priority = temp1->Priority;
					temp3->PW = temp1->PW;
					temp3->Region = temp1->Region;
					temp3->Reload_Period = temp1->Reload_Period;
					temp3->RemainingTimetoShoot = temp1->RemainingTimetoShoot;
					temp3->TimeStep = temp1->TimeStep;
					temp3->Type = temp1->Type;
					//
					temp1->Distance = temp2->Distance;
					temp1->Health = temp2->Health;
					temp1->ID = temp2->ID;
					temp1->Priority = temp2->Priority;
					temp1->PW = temp2->PW;
					temp1->Region = temp2->Region;
					temp1->Reload_Period = temp2->Reload_Period;
					temp1->RemainingTimetoShoot = temp2->RemainingTimetoShoot;
					temp1->TimeStep = temp2->TimeStep;
					temp1->Type = temp2->Type;
					//
					temp3->Distance = temp3->Distance;
					temp3->Health = temp3->Health;
					temp3->ID = temp3->ID;
					temp3->Priority = temp3->Priority;
					temp3->PW = temp3->PW;
					temp3->Region = temp3->Region;
					temp3->Reload_Period = temp3->Reload_Period;
					temp3->RemainingTimetoShoot = temp3->RemainingTimetoShoot;
					temp3->TimeStep = temp3->TimeStep;
					temp3->Type = temp3->Type;
					//
				}

				temp2 = temp2->link;
				delete[] temp3;
				temp3 = 0;

			}
			temp1 = temp1->link;
		}
	}

}




void AdjustShieldedPriorityandReorder(Castle& Cstl, float c1, float c2, float c3)
{
	for (int i = 0; i < 4; i++) // For each Region do following
	{
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

		enemy*temp2 = NULL;
		temp1 = Cstl.towers[i].Region;
		while (!!temp1 && !!temp1->Priority)
		{
			temp2 = temp1->link;
			while (!!temp2 && !!temp2->Priority)

			{
				enemy*temp3 = new enemy;
				if (temp1->Priority < temp2->Priority)
				{
					//
					temp3->Distance = temp1->Distance;
					temp3->Health = temp1->Health;
					temp3->ID = temp1->ID;
					temp3->Priority = temp1->Priority;
					temp3->PW = temp1->PW;
					temp3->Region = temp1->Region;
					temp3->Reload_Period = temp1->Reload_Period;
					temp3->RemainingTimetoShoot = temp1->RemainingTimetoShoot;
					temp3->TimeStep = temp1->TimeStep;
					temp3->Type = temp1->Type;
					//
					temp1->Distance = temp2->Distance;
					temp1->Health = temp2->Health;
					temp1->ID = temp2->ID;
					temp1->Priority = temp2->Priority;
					temp1->PW = temp2->PW;
					temp1->Region = temp2->Region;
					temp1->Reload_Period = temp2->Reload_Period;
					temp1->RemainingTimetoShoot = temp2->RemainingTimetoShoot;
					temp1->TimeStep = temp2->TimeStep;
					temp1->Type = temp2->Type;
					//
					temp3->Distance = temp3->Distance;
					temp3->Health = temp3->Health;
					temp3->ID = temp3->ID;
					temp3->Priority = temp3->Priority;
					temp3->PW = temp3->PW;
					temp3->Region = temp3->Region;
					temp3->Reload_Period = temp3->Reload_Period;
					temp3->RemainingTimetoShoot = temp3->RemainingTimetoShoot;
					temp3->TimeStep = temp3->TimeStep;
					temp3->Type = temp3->Type;
					//

				}

				temp2 = temp2->link;
				delete[] temp3;
				temp3 = 0;

			}
			temp1 = temp1->link;
		}

	}

}



enemy** EnimiesReadyForGraph(Castle Cstl,int Currenttimestep,int &size)
{
	for (int i = 0; i < 4; i++)// get n_enm
	{
		if (Cstl.towers[i].Region == NULL)
			continue;
		enemy*temp = Cstl.towers[i].Region;
		while (temp != NULL)
		{
			if (temp->TimeStep <= Currenttimestep)
				size++;
			temp = temp->link;
		}

	}

	if (size == 0)// if there is no active enmeies in this time step
		return NULL;

		enemy** enemies = new enemy*[size]; //array of pointers
		int j = 0; // index of array of pointers

		for (int i = 0; i < 4; i++)
		{
			if (Cstl.towers[i].Region == NULL)
				continue;

			enemy*temp = Cstl.towers[i].Region;
			while (temp != NULL)
			{
				if (temp->TimeStep <= Currenttimestep)
				{

					enemies[j] = temp;
					j++;
				}
				temp = temp->link;
			}
		}
		return enemies;

}



