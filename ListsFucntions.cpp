#include "Header.h"


void Addenemy(Node*& head, enemy E)
{
	Node * temp = new Node;
	temp->data_enemy = E;
	temp->link = head;
	head = temp;
}

void Deleteenemy(Node* Pretemp)
{
	Node* Temp;
	Temp = Pretemp->link;
	Pretemp->link = Temp->link;
	delete Temp;

}


void Destroy(Node*& head)
{
	Node*temp;

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


void Firstorder(Node** Regions)
{
	//	GetShieldedFisrt(at top of linked list)
	Node* temp1;
	Node* temp2 = NULL;
	for (int i = 0; i < 4; i++)
	{
		if (Regions[i] == NULL) continue;
		temp1 = Regions[i];
		temp2 = temp1->link;

		while (!!temp2)
		{
			enemy E;
			if (temp2->data_enemy.Type == 2)
			{
				E = temp2->data_enemy;
				temp2 = temp2->link;
				Deleteenemy(temp1);
				Addenemy(Regions[i], E);
			}
			else
			{
				temp2 = temp2->link;
				temp1 = temp1->link;
			}
		}

		//      Sort enemies after shielded by timestep
		temp1 = Regions[i];
		temp2 = NULL;
		while (temp1 != NULL&&temp1->data_enemy.Type == 2)
			temp1 = temp1->link;

		while (!!temp1)
		{
			temp2 = temp1->link;
			while (!!temp2)

			{
				Node*temp3 = new Node;
				if (temp1->data_enemy.TimeStep>temp2->data_enemy.TimeStep)
				{
					temp3->data_enemy = temp1->data_enemy;
					temp1->data_enemy = temp2->data_enemy;
					temp2->data_enemy = temp3->data_enemy;
				}

				temp2 = temp2->link;
				delete[] temp3;
				temp3 = 0;

			}
			temp1 = temp1->link;
		}
	}

}



enemy** EnimiesReadyForGraph(Node** Regions,int Currenttimestep,int &size)
{
	for (int i = 0; i < 4; i++)// get n_enm
	{
		if (Regions[i] == NULL)
			continue;
		Node*temp = Regions[i];
		while (temp != NULL)
		{
			if (temp->data_enemy.TimeStep <= Currenttimestep)
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
			if (Regions[i] == NULL)
				continue;

			Node*temp = Regions[i];
			while (temp != NULL)
			{
				if (temp->data_enemy.TimeStep <= Currenttimestep)
				{

					enemies[j] = &temp->data_enemy;
					j++;
				}
				temp = temp->link;
			}
		}
		return enemies;

}



