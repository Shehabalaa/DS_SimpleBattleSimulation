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


