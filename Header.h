#include <iostream>
#include <fstream>
#include <iomanip>
#include <windows.h>

using namespace std;

//Structs

//enemies
struct enemy
{

	int ID;			//Each enemy has a unique ID (sequence number)
	int Type;       // PVR, FITR, SHLD_FITR
	int TimeStep;   // time that enemy will be active
	int PW;         // power of enemy
	float Health;	//Enemy health
	int Region;	//Region of this enemy
	int Reload_Period;
	int Distance;	//Distance to the Castle
	float Priority;
	int RemainingTimetoShoot;
	bool firstshot; // tells if enemy first shot by tower
	int TFS; // time first shot
	int KTS; // timestep that killed in
	enemy* link;

};

//Tower
struct Tower
{
	int TW; //Tower width
	int TH; //Tower Height
	int Health; //Tower Health
	int N_enemies;  //number of enemies that tower will attack each timestep
	int  F_Pow;     //fire power of the tower
	int unpaved_distance; // evert tower has region that has unpaved distance
	float TotlaDamage;
	enemy* Region; // enemy list
	enemy* DeadInRegion;// deadenemy list
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


//Fucntions' prototypes before Fight

bool FileloadData(Castle&, float &, float &, float&,int&);
void AdjustShieldedPriorityandReorder(Castle&, float, float, float);

//Fucntions' prototypes of fight
void Fight(Castle &, int);


//Fucntions' prototypes after fight
void AdjustDistance(Castle&, int);
bool CheckTowersAndEnemiesRegions(Castle& Cstl);
int CheckGameReuslt(Castle Cstl);



// some lists Fucntions' prototypes
void Addenemy(enemy*&, enemy*);
void Firstorder(Castle& Cstl);
void adjustkilled(Castle&);
void append(enemy*& head1, enemy* head2);
void afterappend(enemy*,int);


//just test function weil be deleted later
void PrintTest(Castle&, int);


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
//ASCII code of enemy char shape 
#define EnemyShapeRight		60 // for right regions
#define EnemyShapeLeft		62 // for left regions 






//Functions Prototype of graph

// Function that collect enemies ready for graph
enemy** EnimiesReadyForGraph(Castle, int, int&);

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

/*This function to print statistics to the user*/
void PrintStatistics(Castle, int);

// printing statistics file
void PrintstatisticFile(Castle,int,int);

// this fucntion helps to return nubmer of active enemies in such regiosn
int getnumberofactive(enemy *,int);

// this fucntion helps to return nubmer of killed enemies in any regiosn at certian timestep
int getnumberofkilledat(enemy *, int);


// this fucntion helps to return total nubmer of killed enemies in such  regiosn
int getTotalnumberofKilled(enemy *);