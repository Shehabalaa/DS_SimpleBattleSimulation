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
		temp1 = Cstl.towers[i].Region;
		temp2 = NULL;
		while (temp1 != NULL&&temp1->Type == 2)
			temp1 = temp1->link;

		while (!!temp1)
		{
			temp2 = temp1->link;
			while (!!temp2)

			{
				enemy E;
				if (temp1->TimeStep>temp2->TimeStep)
				{
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
					temp1->firstshot = temp2->firstshot;
					temp1->TFS = temp2->TFS;
					temp1->KTS = temp2->KTS;
					//
					temp2->Distance = E.Distance;
					temp2->Health = E.Health;
					temp2->ID = E.ID;
					temp2->Priority = E.Priority;
					temp2->PW = E.PW;
					temp2->Region = E.Region;
					temp2->Reload_Period = E.Reload_Period;
					temp2->RemainingTimetoShoot = E.RemainingTimetoShoot;
					temp2->TimeStep = E.TimeStep;
					temp2->Type = E.Type;
					temp2->firstshot = E.firstshot;
					temp2->TFS = E.TFS;
					temp2->KTS = E.KTS;
					//
				}

				temp2 = temp2->link;

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
				enemy E;
				if (temp1->Priority < temp2->Priority)
				{
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
					temp1->firstshot = temp2->firstshot;
					temp1->TFS = temp2->TFS;
					temp1->KTS = temp2->KTS;
					//
					temp2->Distance = E.Distance;
					temp2->Health = E.Health;
					temp2->ID = E.ID;
					temp2->Priority = E.Priority;
					temp2->PW = E.PW;
					temp2->Region = E.Region;
					temp2->Reload_Period = E.Reload_Period;
					temp2->RemainingTimetoShoot = E.RemainingTimetoShoot;
					temp2->TimeStep = E.TimeStep;
					temp2->Type = E.Type;
					temp2->firstshot = E.firstshot;
					temp2->TFS = E.TFS;
					temp2->KTS = E.KTS;
					//

				}

				temp2 = temp2->link;

			}
			temp1 = temp1->link;
		}

	}

}






