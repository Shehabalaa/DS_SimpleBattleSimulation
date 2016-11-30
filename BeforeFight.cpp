#include "Header.h"

bool FileloadData(Node** Regions, Castle &Cstl, float &c1, float &c2, float&c3)
{
	ifstream infile("test.txt", ios::in);
	if (!infile.is_open())
		return false;

	for (int i = 0; i < 4; i++) // Read towers
		infile >> Cstl.towers[i].Health >> Cstl.towers[i].N_enemies >> Cstl.towers[i].F_Pow;

	infile >> c1 >> c2 >> c3; // Read constants

	//Readenemies
	while (!infile.eof()) {
		enemy E;
		infile >> E.ID;

		if (E.ID == -1)
			break;


		char Region;
		infile>> E.Type >> E.TimeStep;
		infile >> E.Health >> E.PW >> E.Reload_Period;
		infile.ignore();
		infile >> Region;
		if (Region == 'A')
			E.Region = 0;
		else if (Region == 'B')
			E.Region = 1;
		else if (Region == 'C')
			E.Region = 2;
		else E.Region = 3;
		E.Distance = 60;
		E.RemainingTimetoShoot = 0;
		E.Priority = 0;


		if (E.Region == 'A')
			Addenemy(Regions[0], E);

		else if (E.Region == 'B')
			Addenemy(Regions[1], E);

		else if (E.Region == 'C')
			Addenemy(Regions[2], E);
		else 
			Addenemy(Regions[3], E);

	}

	infile.close();
	return true; //end of function
}









void AdjustShieldedPriorityandReorder(Node** Regions, float c1, float c2, float c3)
{
	for (int i = 0; i < 4; i++) // For each Region do following
	{
		Node*temp1 = Regions[i];
		while (temp1 != NULL) // Give Shielded new Priority
		{
			if (temp1->data_enemy.Type == 2)
				temp1->data_enemy.Priority = (temp1->data_enemy.PW / temp1->data_enemy.Distance)*c1 + (c2 / (temp1->data_enemy.RemainingTimetoShoot + 1)) + temp1->data_enemy.Health*c3;
			else
				break;
			temp1 = temp1->link;

		}

		//ReorderShielded
		
		Node*temp2 = NULL;
		temp1 = Regions[i];
		while (!!temp1&&!!temp1->data_enemy.Priority)
		{
			temp2 = temp1->link;
			while (!!temp2&&!!temp2->data_enemy.Priority)

			{
				Node*temp3 = new Node;
				if (temp1->data_enemy.Priority < temp2->data_enemy.Priority)
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
