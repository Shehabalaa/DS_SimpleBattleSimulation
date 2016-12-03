#include "Header.h"

void PrintstatisticFile(Castle Cstl,int gameresult,int TOT_enemies)
{
	int s = 0; // seqiontal of enemy can be use as number of dead enemies
	float AVG_FD = 0;   // Average Fight Delay
	float AVG_KD = 0; // Average Kill Delay
	ofstream outfile("StatisticsFile.txt", ios::out);
    outfile << setiosflags(ios::left) << setw(5) <<"KTS"<< setw(3) <<"S";
	outfile << setw(4) <<"FD" << setw(4) <<"KD"<<"FT\n";
	for (int i = 0; i < 4; i++)
	{
		enemy* temp1;
		if (Cstl.towers[i].DeadInRegion == NULL) continue;
		temp1 = Cstl.towers[i].Region;
		while (!!temp1) {
			int FD = temp1->TFS - temp1->TimeStep; // fight delay
			AVG_FD += FD; // get AVG_FD of all step by step firstly get sum and end divide by  number of dead enemies
			int KD = temp1->KTS - temp1->TFS; // kill delay
			AVG_KD += FD; // get AVG_KD of all step by step firstly get sum and end divide by  number of dead enemies
			int FT = FD + KD; // fight time
			outfile << setw(5) << temp1->KTS<<setw(3) << ++s <<setw(4) << FD<< setw(4) << KD;
			outfile << FT<<endl;
		
		}
	}
	if (s != 0)
	{
		AVG_FD /= s; // get AVG_FD
		AVG_KD /= s; // get AVG_KD 
	}
	outfile << endl;
	outfile << setiosflags(ios::left) << setw(18) << "T1_Total_Damage" << setw(18) << "T2_Total_Damage";
	outfile << setw(18) << "T3_Total_Damage" <<"T4_Total_Damage\n";
	outfile << setiosflags(ios::left);

	for (int i = 0; i < 4; i++)
		outfile << setw(18) << Cstl.towers[i].TotlaDamage;

	outfile << endl<<endl;
	outfile << setiosflags(ios::left) << setw(18) << "R1_Distance" << setw(18) << "R2_Distance";
	outfile << setw(18) << "R3_Distance" << "R4_Distancen\n";

	outfile << setiosflags(ios::left);
	for (int i = 0; i < 4; i++)
		outfile << setw(18) << Cstl.towers[i].unpaved_distance;

	outfile << endl<<endl;
	if (gameresult == 1)
		outfile << "Game is WIN\n\n";
	else if (gameresult == 2)
		outfile << "Game is LOSE\n\n";
	else outfile << "Game is DRAW\n\n";

	outfile << "Total Enemies = " << TOT_enemies<<endl<<endl;
	outfile << "Average Fight Delay = " << AVG_FD << endl << endl;
	outfile << "Average Kill Delay = " << AVG_KD << endl;

	outfile.close();
}