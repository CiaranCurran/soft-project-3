#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "operations.h"

int getPlayers(player * players, const char ** playerType){
    //declare variables
    int i;
    int numPlayers;
    int typeChoice;
    char playerName[MAX_NAME_LEN];
    //first get the number of players the user will be working with
    printf("Please enter the number of players:");
    do{
        scanf("%d", &numPlayers);
        if(numPlayers>MAX_PLAYERS || numPlayers<2){// validate input
            printf("\nPlease enter a valid number of players:");
        }
    }while(numPlayers>MAX_PLAYERS || numPlayers<2); //repeat until valid input registered
   
     //allocate player names and types and store in struct array
    for(i=0;i<numPlayers;i++){
        printf("\nWhat type is player %d?", (i+1));
        //display options for type
        printf("\n%-10s%d\n%-10s%d\n%-10s%d\n%-10s%d",
        playerType[0], 1,
        playerType[1], 2,
        playerType[2], 3,
        playerType[3], 4);
        //repeat until a valid input has been registered
        do {
            printf("\nplayer type:");
            scanf("%d", &typeChoice);
            if((typeChoice<1) || (typeChoice>4)){
				printf("\n---Please enter a number between 1 and 4---");
            }
        }while((typeChoice<1) || (typeChoice>4));
  
        //now that a type has been identified, get the corresponding player name
        printf("\nWhat is player %d's name?", (i+1));
		fflush(stdin);
        fgets(playerName, MAX_NAME_LEN, stdin);
        strtok(playerName, "\n");
         
        //now that the type and name have been identified, allocate to the struct array
        strcpy(players[i].name, playerName);
        strcpy(players[i].type, playerType[typeChoice-1]);      //See initialisation of the type array, it stores the types, "typeChoice-1" is the position of the type chosen by the user in that array
        players[i].row = -1; //default initialisation
		players[i].column = -1;
		players[i].number = i;
	}
    
	return numPlayers;   //returns the number of players  to be used later in main
}

void makeMoves(slot ** board, int boardSize, player * players, const char **slotTypes, int numPlayers){
	char decision;
	int attackPlayer, moveNumber, playerDistance, i, j;
	int near[numPlayers];
	int distance[numPlayers];
	int quit = 0;
	int numAlive = numPlayers;
	while(numAlive > 1 && quit != numAlive){
		quit = 0;
		for(i=0;i<numPlayers;i++){
			if(players[i].number != -1){
				//set attack arrays to default initialisation
				for(j=0;j<numPlayers;j++){
					near[j] = -1;
					distance[j] = -1;
				}
				
				for(j=0;j<numPlayers;j++){
					if(players[j].number != -1 && players[j].number != players[i].number){
						//player distance is the sum of the differences in row and column
						playerDistance = (abs(players[j].row - players[i].row) + abs(players[j].column - players[i].column));
						//if the distance between the currentPlayer and the other player is less than or equal to 1 then add to near attack
						if(playerDistance<=1){
							near[j] = j;
						}
						//if the distance between the currentPlayer and the other player is greater than 1 and less than 5 add to distance attack
						else if(playerDistance > 1 && playerDistance < 5){
							distance[j] = j;
						}
					}
				}
				
				printf("\nWhat would player %s like to do?\n", players[i].name,  players[i].row, players[i].column);
				//player can always move
				printf("m)Move?\n");
				
				//if player can attack then print option to attack
				for(j=0;j<numPlayers;j++){
					if(near[j] != -1 || distance[j] != -1 || (players[i].smartness + players[i].magicSkills) > 150){
						printf("a)Attack?\n");
						break;
					}
				}
				//option to quit
				printf("q)Quit?\n");

				scanf(" %c", &decision);
				
				//if player chooses to move
				if(decision=='m'){
					printf("\nWould you like to move:\n");
					if(players[i].row < boardSize-1){
						printf("d) Down\n");
					}
					if(players[i].row > 0){
						printf("u) Up\n");
					}
					if(players[i].column < boardSize-1){
						printf("r) Right\n");
					}
					if(players[i].column > 0){
						printf("l) Left\n");
					}

					scanf(" %c", &decision);
					movePlayer(board, &players[i], decision, slotTypes, numPlayers);
				}
				
				else if(decision=='a'){
					printf("\nWould you like to:\n");
					
					//if there exists a player who can be near attacked display that option
					for(j=0;j<numPlayers;j++){
						if(near[j] != -1){
							printf("n) Near Attack\n");
							break;
						}

					}
					
					//if there exists a player who can be distance attacked display that option
					for(j=0;j<numPlayers;j++){
						if(distance[j] != -1){
							printf("d) Distance Attack\n");
							break;
						}
					}
					
					//if there exists a player who can be magic attacked display that option
					if((players[i].smartness + players[i].magicSkills) > 150){
						printf("m) Magic Attack\n");
					}
					
					scanf(" %c", &decision);
					
					if(decision=='n'){
						printf("\nWho would you like to near attack?\n");
						for(j=0;j<numPlayers;j++){
							if(near[j] != -1){
								printf("%d %s\n", j, players[j].name);
							}
						}
						printf("Please enter the player number:");
						scanf(" %d", &attackPlayer);
						nearAttack(&players[i], &players[attackPlayer]);
					}
					
					else if(decision=='d'){
						printf("\nWho would you like to distance attack?\n");
						for(j=0;j<numPlayers;j++){
							if(distance[j] != -1){
								printf("%d %s\n", j, players[j].name);
							}
						}
						printf("Please enter the player number:");
						scanf(" %d", &attackPlayer);
						distanceAttack(&players[i], &players[attackPlayer]);
					}
					
					else if(decision=='m'){
						printf("\nWho would you like to magic attack?\n");
						for(j=0;j<numPlayers;j++){
							if(players[j].number != -1 && (i != j)){
								printf("%d %s\n", players[j].number, players[j].name);
							}
						}
						printf("Please enter the player number:");
						scanf(" %d", &attackPlayer);
						magicAttack(&players[i], &players[attackPlayer]);
					}
				}
				
				else if(decision == 'q'){
					quit++;
				} 
				
				numAlive = removeDeadPlayers(board, players, numPlayers);
				if(numAlive<=1){
					return;
				}
			}
		}
	}
}

//takes in attacking player and attacked player and impliments a magic attack
void magicAttack(player * attacker, player * attacked){
	attacked->lifePoints -= (0.5*attacker->magicSkills) + (0.2*attacker->smartness);
}

//checks for players who have died and removes them from game and returns updated number of players alive
int removeDeadPlayers(slot ** board, player * players, int numPlayers){
	int i;
	int numAlive = 0;
	for(i=0;i<numPlayers;i++){
		if(players[i].number != -1){
			if(players[i].lifePoints<=0){
				players[i].number = -1;
				numAlive--;
				printf("Player %s has died", players[i].name);
			}
			else{
				numAlive++;
			}
		}
	}
	return numAlive;
}
