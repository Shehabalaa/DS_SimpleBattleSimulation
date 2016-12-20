#include "Header.h"


void Addenemy(enemy*& head, enemy* ptrnew)
{
	ptrnew->link = head;
	head = ptrnew;


}

void append(enemy*& head1, enemy* head2)
{
	enemy  * temp = head1;
	if (head1 == NULL)
		head1 = head2;

	else 
	{
		while (temp->link != NULL)
			temp = temp->link;

		temp->link = head2;
	}



}

void afterappend(enemy* head, int unpavedinnewregion)
{
	while (head != NULL)
	{
		if (head->Distance < unpavedinnewregion)
			head->Distance = unpavedinnewregion;
		head = head->link;
	}
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


void adjustkilled(Castle& Cstl)
{
	for (int i = 0; i < 4; i++)
	{
		enemy* temp1;
		temp1 = Cstl.towers[i].Region;
		if (Cstl.towers[i].Region == NULL)
			continue;
		while (temp1->link != NULL) // check whole list except head
		{
			if (temp1->Health != 0 && temp1->Type != 2)
				break;

			if (temp1->link->Health == 0)
			{
				enemy*temp2 = temp1->link;
				temp1->link = temp1->link->link;
				Addenemy(Cstl.towers[i].DeadInRegion,temp2);
				
			}
			else
				temp1 = temp1->link;
			
		}

		if (Cstl.towers[i].Region->Health == 0) // check at head 
		{
			enemy*temp2 = Cstl.towers[i].Region;
			Cstl.towers[i].Region = Cstl.towers[i].Region->link;
			Addenemy(Cstl.towers[i].DeadInRegion, temp2);
			
		}
	}
}



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
		temp1 = Cstl.towers[i].Region; // i will use it as curr ptr
		temp2 = NULL; // i will use it as walker ptr
		while (temp1 != NULL&&temp1->Type == 2)
			temp1 = temp1->link;// curr i will firstly point to non shielded enemy

		while (!!temp1->link)
		{
			temp2 = temp1->link;
			enemy* min = temp1; // min points to smalles enemy that has timestep
			while (!!temp2)
			{
				if (temp2->TimeStep < min->TimeStep)
					min = temp2;

				temp2 = temp2->link;
			}

			if (temp1!=min) {
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
				temp1->Distance = min->Distance;
				temp1->Health = min->Health;
				temp1->ID = min->ID;
				temp1->Priority = min->Priority;
				temp1->PW = min->PW;
				temp1->Region = min->Region;
				temp1->Reload_Period = min->Reload_Period;
				temp1->RemainingTimetoShoot = min->RemainingTimetoShoot;
				temp1->TimeStep = min->TimeStep;
				temp1->Type = min->Type;
				temp1->firstshot = min->firstshot;
				temp1->TFS = min->TFS;
				temp1->KTS = min->KTS;
				//
				min->Distance = E.Distance;
				min->Health = E.Health;
				min->ID = E.ID;
				min->Priority = E.Priority;
				min->PW = E.PW;
				min->Region = E.Region;
				min->Reload_Period = E.Reload_Period;
				min->RemainingTimetoShoot = E.RemainingTimetoShoot;
				min->TimeStep = E.TimeStep;
				min->Type = E.Type;
				min->firstshot = E.firstshot;
				min->TFS = E.TFS;
				min->KTS = E.KTS;
				//
			}
			
			temp1 = temp1->link;
		}
	}

}








