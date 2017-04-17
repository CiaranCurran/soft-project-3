#include <stdio.h>
#include <stdlib.h>
#include "operations.h"


int main(void){
	const char *playerTypes[]= {"Elf", "Human", "Ogre", "Wizard"};
	const char *slotTypes[]= {"Level Ground", "Hill", "City"};
	
	int boardSize, numPlayers, i;
	
	struct player players[MAX_PLAYERS];//can take maximum size of players

	boardSize = BOARD_SIZE;
	
	slot ** board= malloc(boardSize * sizeof(slot *)); //initialise board 
  	
	numPlayers = getPlayers(players, playerTypes);
	setCapabilities(players, playerTypes, numPlayers);
	initBoard(board, boardSize, slotTypes);
	/*-----After this line------*/
  
}
