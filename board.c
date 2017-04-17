#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "operations.h"

void initBoard(slot **board, int boardSize, const char ** slotTypes){
	int i, j;
	
	//set all rows and columns
	for (i=0;i<boardSize;i++){
		board[i] = malloc(boardSize * sizeof(slot));
		
		for(j=0;j<boardSize;j++){
			board[i][j].row = i;
			board[i][j].column = j;
		}
	}
	//assign types to the slots
	for(i=0;i<boardSize;i++){
		for(j=0;j<boardSize;j++){
			strcpy(board[i][j].type, slotTypes[randRange(0,3)]); 
		}
	}
}

/********ASSIGN PLAYERS GOES HERE ***********/

//returns random value between min and max inclusive
int randRange(int min, int max){
	return (rand()%(max-min))+min;
}


