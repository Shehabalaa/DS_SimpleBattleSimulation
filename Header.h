#include <iostream>
#include <fstream>
#include <iomanip>
#include <windows.h>

using namespace std;

//Structs

//Tower
struct Tower
{
	int TW; //Tower width
	int TH; //Tower Height
	int Health; //Tower Health
	int N_enemies;  //number of enemies that tower will attack each timestep
	int  F_Pow;     //fire power of the tower
};


struct Castle
{
	//starting x,y
	int Xstrt;
	int Ystrt;
	int W;	//width
	int L;  //Height
	Tower towers[4];	//Castle has 4 towers
};

struct enemy
{

	int ID;			//Each enemy has a unique ID (sequence number)
	int Type;       // PVR, FITR, SHLD_FITR
	int TimeStep;   // time that enemy will arrive
	int PW;         // power of enemy
	float Health;	//Enemy health
	int Region;	//Region of this enemy
	int Reload_Period;
	int Distance;	//Distance to the Castle
	float Priority;
	int RemainingTimetoShoot;

};
struct Node {
	enemy data_enemy;
	Node*link;

};
//Fucntions prototypes

bool FileloadData(Node**, Castle&, float &, float &, float&);
void PrintTest(Node**, Castle&, int);
void AdjustShieldedPriorityandReorder(Node **, float, float, float);
void Addenemy(Node*&, enemy);
void Deleteenemy(Node*);
void Destroy(Node*&);
void Firstorder(Node**);
void ReorderShield(Node**);
//void Deleteenemy(Node*&, Node*);
void Removekilledenemies(Node**,int);
//void void Sortlinkedlistbyhp(Node*);#pragma once
enemy** EnimiesReadyForGraph(Node**, int, int&);




//Graph Code

//constants
#define CmdWidth		150
#define CmdHeight		50
#define CastleWidth		30
#define CastleLength	20
#define CastleXStrt		(CmdWidth/2-(CastleWidth/2))
#define CastleYStrt		(CmdHeight/2-(CastleLength/2))
#define TowerWidth      7
#define TowerLength     3

#define EnemyShape		219  //ASCII code of enemy char shape 






//Functions Prototype

/*A function to set the position of cursor on the screen*/
void gotoxy(int x, int y);

/*A function to set the command window lenght and height for the game specification*/
void SetWindow();

/*A function to color the cmd text*/
void color(int thecolor);

/*A function to partition the Castle into regions (A,B,C,D)*/
void DrawRegions(const Castle & C);

/*A function to draw the Castle and the towers*/
void DrawCastle(const Castle & C, int SimulationTime);

/*A function to draw a single enemy using its distance from the Castle*/
void DrawEnemy(const enemy& E, int Ypos = 0);

/*A function to draw a list of enemies exist in all regions and ensure there is no overflow in the drawing*/
void DrawEnemies(enemy* enemies[], int size);

/*Student use this function to print his/her message*/
void PrintMsg(char*msg);






