#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

#define minLives 1
#define maxLives 10

#define minPath 10
#define maxPath 70

struct playerInformation {
	int numLives;
	char charSymbol;
	int numTreasure;
	int pastPositions[maxPath];
};

struct gameInformation {
	int numMoves;
	int pathLength;
	int numBombs[maxPath];
	int numTreasure[maxPath];
};

int main(void) {

	int keepgoing, i, j, k = 1; // loops
	int nextMove, ruler = 0;
	int const multiPath = 5; // mutliple of 5
	char undiscovered = '-', bombs = '!', treasure = '$', both = '&', neither = '.';
	double x;

	struct playerInformation playerINFO; // structs for player information
	struct gameInformation gameINFO; // structs for game information


	printf("================================\n"); // Header
	printf("         Treasure Hunt!         \n");
	printf("================================\n");

	printf("\nPLAYER Configuration\n"); // Player Configuration Stage
	printf("--------------------\n");
	printf("Enter a single character to represent the player: ");
	scanf(" %c", &playerINFO.charSymbol);

	do // User input for number of lives setting
	{
		keepgoing = 1;
		printf("Set the number of lives: ");
		scanf("%d", &playerINFO.numLives);

		if (playerINFO.numLives < minLives || playerINFO.numLives > maxLives) // Error Range with appropriate error message
		{
			printf("     Must be between 1 and 10!\n");
			keepgoing = 0;
		}

	} while (keepgoing != 1);

	printf("Player configuration set-up is complete\n\n");

	for (i = 0; i < maxPath; i++)
	{
		playerINFO.pastPositions[i] = 0; //  History or moves set to a safe empty state
	}

	printf("GAME Configuration\n"); // Game Configuration Phase
	printf("------------------\n");

	do // User input for path length
	{
		keepgoing = 1;
		printf("Set the path length (a multiple of 5 between 10-70): ");
		scanf("%d", &gameINFO.pathLength);

		if (gameINFO.pathLength < minPath || gameINFO.pathLength > maxPath || gameINFO.pathLength % multiPath) // Error Range with appropriate error message
		{
			printf("     Must be a multiple of 5 and between 10-70!!!\n");
			keepgoing = 0;
		}

	} while (keepgoing != 1);



	do // User input for limit number of moves
	{
		keepgoing = 1;
		printf("Set the limit for number of moves allowed: ");
		scanf("%d", &gameINFO.numMoves);

		if (gameINFO.numMoves < playerINFO.numLives || gameINFO.numMoves >(int)(double)(gameINFO.pathLength * 0.75)) // Error Range with instructed requirements and  with appropriate error mesage
		{
			printf("    Value must be between %d and %d\n", playerINFO.numLives, (int)(double)(gameINFO.pathLength * 0.75));
			keepgoing = 0;
		}



	} while (keepgoing != 1);


	printf("\nBOMB Placement\n"); // Bomb Placement Phase
	printf("--------------\n");
	printf("Enter the bomb positions in sets of 5 where a value\nof 1=BOMB, and 0=NO BOMB. Space-delimit your input.\n(Example: 1 0 0 1 1) NOTE: there are 20 to set!\n");


	for (i = 0; i < gameINFO.pathLength; i = i + 5) // Display for the set of bomb placements with the multiples of 5
	{
		printf("   Positions [%2d-%2d]: ", i + 1, i + 5);
		for (j = i; j < i + 5; j++)
		{
			scanf("%d", &gameINFO.numBombs[j]);
		}

	}
	printf("BOMB placement set\n");

	printf("\nTREASURE Placement\n"); // Treasure Placement Phase
	printf("------------------\n");
	printf("Enter the treasure placements in sets of 5 where a value\nof 1=TREASURE, and 0=NO TREASURE. Space-delimit your input.\n(Example: 1 0 0 1 1) NOTE: there are 20 to set!\n");


	for (i = 0; i < gameINFO.pathLength; i = i + 5) // Display for the set of Treasure placements with the multiples of 5
	{
		printf("   Positions [%2d-%2d]: ", i + 1, i + 5);
		for (j = i; j < i + 5; j++)
		{
			scanf("%d", &gameINFO.numTreasure[j]);
		}

	}
	printf("TREASURE placement set\n"); 

	printf("\nGAME configuration set-up is complete...\n"); // Display for configuration completetion
	printf("\n------------------------------------\n");
	printf("TREASURE HUNT Configuration Settings\n");
	printf("------------------------------------\n");

	printf("Player:\n"); // Display Player's Info
	printf("   Symbol     : %c\n", playerINFO.charSymbol);
	printf("   Lives      : %d\n", playerINFO.numLives);
	printf("   Treasure   : [ready for gameplay]\n");
	printf("   History    : [ready for gameplay]\n");

	printf("\nGame:"); // Display Game Info
	printf("\n   Path Length: %d", gameINFO.pathLength);
	printf("\n   Bombs      : ");
	for (i = 0; i < gameINFO.pathLength; i++)
	{
		printf("%d", gameINFO.numBombs[i]);
	}

	printf("\n   Treasure   : ");
	for (i = 0; i < gameINFO.pathLength; i++)
	{
		printf("%d", gameINFO.numTreasure[i]);
	}

	printf("\n\n====================================\n");
	printf("~ Get ready to play TREASURE HUNT! ~\n");
	printf("====================================\n");

	x = 0;
	nextMove = 1;
	playerINFO.numTreasure = 0;

	while (1)
	{
		if (x == 0)
			++x;
		else
		{
			printf("\n  "); // Recent move represented with the User's set symbol (Line-1)
			for (i = 0; i < gameINFO.pathLength; i++)
			{
				if ((playerINFO.pastPositions[i] == 1 && i == (nextMove - 1)))
				{
					printf("%c", playerINFO.charSymbol);
				}
				else
				{
					printf(" ");
				}
			}
		}
		printf("\n  "); // Displaying the gamepath with required representing symbols (Line-2)
		for (i = 0; i < gameINFO.pathLength; i++)
		{
			if (playerINFO.pastPositions[i] == 0)
			{
				printf("%c", undiscovered);
			}
			else if (gameINFO.numBombs[i] == 1 && gameINFO.numTreasure[i] == 1)
			{
				printf("%c", both);
			}
			else if (gameINFO.numBombs[i] == 1)
			{
				printf("%c", bombs);
			}
			else if (gameINFO.numTreasure[i] == 1)
			{
				printf("%c", treasure);
			}
			
			else
			{
				printf("%c", neither);
			}
					
		}
		printf("\n  "); // Posistion Ruler Major (Line-3)
		for ( i = 0; i < gameINFO.pathLength; i++)
		{
			if ((i + 1) % 10 == 0)
			{
				++ruler;
				printf("%d", ruler);
			}
			else
			{
				printf("|");
			}
		}
		ruler = 0;
		printf("\n  "); // Posistion Ruler Minor (Line-4)
		for ( i = 0; i < gameINFO.pathLength; i++)
		{
			if ((i + 1) % 10 == 0)
			{
				printf("0");
				k = 1;
			}
			else
			{
				printf("%d", k++);
			}
		}
		printf("\n");
		printf("+---------------------------------------------------+\n"); // Display User information
		printf("  Lives: %2d  | Treasures: %2d  |  Moves Remaining: %2d\n", playerINFO.numLives, playerINFO.numTreasure, gameINFO.numMoves);
		printf("+---------------------------------------------------+\n");
		if (playerINFO.numLives == 0 || gameINFO.numMoves == 0)
			break;

		while (1) // Recieving User's input for moves with error range displaying appropriate error message
		{
			printf("Next Move [1-%d]: ", gameINFO.pathLength);
			scanf("%d", &nextMove);
			if (nextMove < 1 || nextMove > gameINFO.pathLength)
				printf("  Out of Range!!!\n");

			else
				break;
		}

		if (playerINFO.pastPositions[nextMove - 1] == 1) // If statement when user has enter the same posistion from previous input
		{
			printf("\n===============> Dope! You've been here before!\n");
		}
		else // Display appropriate message when player lands on a space with treasure, bombs, neither, or both
		{
			playerINFO.pastPositions[nextMove - 1] = 1;
			gameINFO.numMoves -= 1;
			if (gameINFO.numBombs[nextMove - 1] == 1 && gameINFO.numTreasure[nextMove - 1] == 1)
			{
				playerINFO.numLives -= 1;
				playerINFO.numTreasure += 1;
				printf("\n===============> [%c] !!! BOOOOOM !!! [%c]", both, both);
				printf("\n===============> [%c] $$$ Life Insurance Payout!!! [%c]\n", both, both);
				if (playerINFO.numLives == 0)
					printf("\nNo more LIVES remaining!\n");
				else if (gameINFO.numMoves == 0)
					printf("\nNo more MOVES remaining!\n");
			}
			else  if (gameINFO.numBombs[nextMove - 1] == 1)
			{
				playerINFO.numLives -= 1;
				printf("\n===============> [%c] !!! BOOOOOM !!! [%c]\n", bombs, bombs);
				if (playerINFO.numLives == 0)
					printf("\nNo more LIVES remaining!\n");
				else if (gameINFO.numMoves == 0)
					printf("\nNo more MOVES remaining!\n");
			}
			else if (gameINFO.numTreasure[nextMove - 1] == 1) 
			{
				playerINFO.numTreasure += 1;
				printf("\n===============> [%c] $$$ Found Treasure! $$$ [%c]\n", treasure, treasure);
			}
			else
			{
					printf("\n===============> [%c] ...Nothing found here... [%c]\n", neither, neither);
			}

		}
		
	}
	printf("\n##################\n"); // Display required Gameover message
	printf("#   Game over!   #");
	printf("\n##################\n");
	printf("\nYou should play again and try to beat your score!");



	return 0;
}

