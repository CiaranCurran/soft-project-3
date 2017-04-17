#ifndef CROSSFIREOPERATIONS_H_
#define CROSSFIREOPERATIONS_H_

#define MAX_NAME_LEN 50
#define MAX_PLAYERS 6
#define BOARD_SIZE 7

typedef enum bool {false=0, true=1} bool;
typedef enum direction {left=0, right=1, up=2, down=3} direction;

typedef struct slot{
	int row; //row number
	int column; //column number
	char type[MAX_NAME_LEN];
}slot;

typedef struct player{//declare player structure
    char name[MAX_NAME_LEN];
    char type[MAX_NAME_LEN];
	int number; //a unique number which identifies the player
    int row;
	int column;
    int lifePoints;
    int smartness;
    int strength;
    int magicSkills; 
    int luck;
    int dexterity; 
}player;

//extern const char *playerTypes[];
//extern const char *slotTypes[];

void initBoard(slot **board, int boardSize, const char ** slotType);
int randRange(int min, int max);
int getPlayers(player * players, const char ** playerTypes);
void setCapabilities(player * players, const char ** playerTypes, int numPlayers);
void assignPlayers(slot **board, int boardSize, player * players, int numPlayers);
void movePlayer(slot ** board, player * player, char direction, const char ** slotTypes, int numPlayers);
void makeMoves(slot ** board, int boardSize, player * players, const char ** slotTypes, int numPlayers);
void nearAttack(player * attacker, player * attacked);
void distanceAttack(player * attacker, player * attacked);
void magicAttack(player * attacker, player * attacked);
int removeDeadPlayers(slot **board, player * players, int numPlayers);

#endif /* CROSSFIREOPERATIONS_H_ */
