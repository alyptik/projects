#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <limits.h>
#include <time.h>
#include <assert.h>

typedef struct{
	char name[21];
	int** grid;
	char symbol;
}Player;


void clear_buffer();
void initialize_player(Player* player);
void display_player(Player player);
void display_player_grid(Player player);
void display_grid(Player player1, Player player2);
int get_nb_moves(Player ai, Player opponent);
int check_end(Player player);
void free_player(Player* player);
void add_symbol(Player* player,Player opponent);
extern void add_symbol_ai(Player* ai, Player opponent);
void display_value_cell(Player player, Player ai);
void display_value_grid(Player player, Player opponent);

int minimum(int a,int b);
int maximum(int a,int b);
int valueDirection(Player player,Player opponent,int row, int column,int direction,int* length,int* row_connected);
int get_value_cell(Player player,Player opponent,int row, int column);
int get_value_grid(Player ai, Player opponent);
void get_ordered_moves(Player ai, Player opponent,int* nb,int** values);
Player copy_player(Player* ai);
void free_array(int ** x);
int minimax_recursive(Player ai, Player opponent,int row, int column, int depth, int alpha, int beta, int maximazing);
void add_symbol_ai(Player* ai, Player opponent);


//Minimum width is 5
int grid_width=15;
//Minimum height is 5
int grid_height=15;

int nb_leaf=0;
// Number of branches for the decisional tree at each step
int BRANCHING_FACTOR = 2;
// Depth of the decisional treew
int LOOK_AHEAD = 10;

// Combination of the eight possible directions represented by the value of i and j
int ADJACENT_DIRECTION[2][8] = {{ -1, 1, 0, 0, 1, -1, -1, 1 }, { -1, 1, -1, 1, -1, 1, 0, 0 } };

// Minimum between two numbers
int minimum(int a,int b){
	if(a<b)
		return a;
	else
		return b;
}
// Maximum between two numbers
int maximum(int a,int b){
	if(a>b)
		return a;
	else
		return b;
}

// Gives the value of a given cell, in a given direction
int valueDirection(Player player,Player opponent,int row, int column,int direction,int* length,int* row_connected){
		int value=0;
		int nb_checked=0;
		int check_row=1;
		while(row<grid_height && row>=0 && column<grid_width && column>=0 /*&& nb_checked < 6*/){
			//If player has the cell
			if(player.grid[row][column]==1){
				// 4-nb_checked is used to put a better weight near the cell
				value=value+100;
				if(check_row)
					*row_connected*=10;
			}
			else{
				//If opponent has the cell, we stop
				if(opponent.grid[row][column]==1){
					break;
				}
				//available move
				else{
					value++;
					//we stop checking row
					check_row=0;
				}
			}
			row += ADJACENT_DIRECTION[0][direction];
			column += ADJACENT_DIRECTION[1][direction];
			nb_checked++;

			//to check if we have enough space to make 5 in a row
			*length=*length+1;
		}
		return value;
}

// Evaluate value of the cell
int get_value_cell(Player player,Player opponent,int row, int column){
	int totalValue = 0;
	int i,length=1,row_connected=1;
	/* 4 iterations
	-We first check diagonal /
	-then we check horizontal line -
	-then we check diagonal \
	-then we check vertical line |
	*/
		for (i = 0; i < 8; i += 2) {
			// value of direction
			int value1, value2, x = row + ADJACENT_DIRECTION[0][i];
			int y = column + ADJACENT_DIRECTION[1][i];
			value1 = valueDirection(player,opponent, x, y, i,&length,&row_connected);

			// value of opposite direction
			x = row + ADJACENT_DIRECTION[0][i + 1];
			y = column + ADJACENT_DIRECTION[1][i + 1];
			value2 = valueDirection(player,opponent, x, y, i + 1,&length,&row_connected);

			// Sum of the two directions, 0 if we haven't enough space to make 5 connections
			if(length>4){
				if(row_connected==0)
					totalValue = totalValue +  value1 + value2;
				else
					totalValue = totalValue +  (value1 + value2)*row_connected;
			}
			row_connected=1;
			length=1;
		}
	printf("cell value :[%d,%d]=%d\n",row,column,totalValue);
	return totalValue;
}

// Evaluate value of the grid
int get_value_grid(Player ai, Player opponent){
	long long value=0;
	long long i,j,val_opponent,val_ai;
	for(i=0;i<grid_height;i++){
		for(j=0;j<grid_width;j++){
			val_opponent=get_value_cell(opponent,ai,i,j);
			val_ai=get_value_cell(ai,opponent,i,j);
			value+=val_ai-val_opponent;
		}
	}
	return value;
}

// Get available moves, ordering them by their decreasing value
void get_ordered_moves(Player ai, Player opponent,int* nb,int** values){
	int i,j,k,l,val;
	int swap_value[3];
	val=0;
	assert(ai.grid);
	for(i=0;i<grid_height;i++){
		for(j=0;j<grid_width;j++){
			if(ai.grid[i][j]==0 && opponent.grid[i][j]==0){
				//Store the row, the column and the value of the available cell
				values[0][val]=i;
				values[1][val]=j;
				values[2][val]=get_value_cell(ai,opponent,i,j)+get_value_cell(opponent,ai,i,j);
				val=val+1;
			}
		}
	}
	//Bubble sort
	for(k=0;k<val-1;k++){
		for (l = 0 ; l < val-k-1; l++)
		{
			if (values[2][l] < values[2][l+1])
			{
				for(i=0;i<3;i++){
					swap_value[i]=values[i][l];
					values[i][l]=values[i][l+1];
					values[i][l+1]=swap_value[i];
				}
			}
		}
	}
	// return the number of available moves
	*nb=val;
}

// Make a copy of a player given as parameter to prevent modifying the original one
Player copy_player(Player* ai){

	Player new_player;
	int i,j;

	// Copy name and symbol
	strcpy(new_player.name,ai->name);
	new_player.symbol=ai->symbol;

	// Allocate memory for the grid
	new_player.grid = malloc(grid_height*sizeof(int*));
	for(i=0;i<grid_height;i++)
		new_player.grid[i] = malloc(grid_width*sizeof(int));

	// Copy values of the grid
	for(i=0;i<grid_height;i++) {
		for(j=0;j<grid_width;j++) {
			if(ai->grid[i][j]==1)
				new_player.grid[i][j]=1;
			else
				new_player.grid[i][j]=0;
		}
	}

	return new_player;
}


// Free allocated memory used to store ordered moves
void free_array(int ** x){
	int i;
	for (i=0; i<3; i++){
		free(x[i]);
	}
	free(x);
}


// Minimax algorithm
int minimax_recursive(Player ai, Player opponent,int row, int column, int depth, int alpha, int beta, int maximazing)
{
	int val;
	// If we reach a leaf
	val=get_value_grid(ai,opponent);

	if (depth == 0){
		nb_leaf++;
		return val;
	}
	else{
		if(check_end(opponent)||check_end(ai)||get_nb_moves(ai,opponent)<2){
			nb_leaf++;
			return depth*val;
		}
	}


	Player ai_copy;
	Player opponent_copy;

	ai_copy=copy_player(&ai);
	opponent_copy=copy_player(&opponent);

	if(maximazing)
		ai_copy.grid[row][column]=1;
	else
		opponent_copy.grid[row][column]=1;

	int nb,mini,i,j;
	int bestValue;

	// Allocate array to store available moves. Size of grid is [3 ; grid_width * grid_height]
	int** moves;
	moves = malloc(3*sizeof(int*));
	for(i=0;i<3;i++)
		moves[i]=malloc((grid_width*grid_height)*sizeof(int));

	// Initialize array of available moves
	for(i=0;i<3;i++){
		for(j=0;j<(grid_width*grid_height);j++){
			 moves[i][j]=0;
		}
	}

	// Get available moves ordered by their decreasing value
	get_ordered_moves(ai_copy,opponent_copy,&nb,moves);

	if (maximazing) {
		bestValue = INT_MIN;
		mini=minimum(BRANCHING_FACTOR,nb);
		for (i=0;i<mini;i++){
				bestValue=maximum(bestValue,minimax_recursive(ai_copy,opponent_copy,moves[0][i],moves[1][i],depth-1,alpha,beta,0));

				// Tree pruning
				alpha=maximum(alpha,bestValue);
				if(beta<=alpha)
					break;

		}
		free_player(&ai_copy);
		free_player(&opponent_copy);
		free_array(moves);
		return bestValue;
	}
	else {
		bestValue = INT_MAX;
		mini=minimum(BRANCHING_FACTOR,nb);
		 for (i=0;i<mini;i++){
				bestValue=minimum(bestValue,minimax_recursive(ai_copy,opponent_copy,moves[0][i],moves[1][i],depth-1,alpha,beta,1));

				// Tree pruning
				beta=minimum(beta, bestValue);
				if (beta <= alpha) // alpha cut-off
					break;
		}
		free_player(&ai_copy);
		free_player(&opponent_copy);
		free_array(moves);
		return bestValue;
	}
}

// Launch the minimax algorithm and add the result in the ai grid
void add_symbol_ai(Player* ai, Player opponent)
{
	int row=0;
	int column=0;
	int mini;
	Player ai_copy;
	Player opponent_copy;

	/* Min Max Algorithm */

	int maxi = INT_MIN;
	int nb,i,j;

	// Copy players for simulation
	ai_copy=copy_player(ai);
	opponent_copy=copy_player(&opponent);

	// Allocate array to store available moves. Size of grid is [3 ; grid_width * grid_height].
	// First row for rows, second row for columns, third row for values
	int** moves;
	moves = malloc(3*sizeof(int*));
	for(i=0;i<3;i++)
		moves[i] = malloc((grid_width*grid_height)*sizeof(int));

	// Initialize array of available moves
	for(i=0;i<3;i++)
		for(j=0;j<(grid_width*grid_height);j++)
		   moves[i][j]=0;

	// Get available moves ordered by they decreasing value
	get_ordered_moves(ai_copy,opponent_copy,&nb,moves);

	// Check the minimum between the number of available moves and the number of moves we want to try
	mini=minimum(BRANCHING_FACTOR,nb);

	// Apply minimax on the best moves
	for (i=0;i<mini;i++){
		int value = minimax_recursive(ai_copy,opponent_copy,moves[0][i],moves[1][i],LOOK_AHEAD,INT_MIN,INT_MAX,1);
		if (value > maxi) {
			maxi=value;
			row=moves[0][i];
			column=moves[1][i];
		}
	}


	/* ------------ */

	ai->grid[row][column]=1;
	free_array(moves);
	free_player(&ai_copy);
	free_player(&opponent_copy);
}





/*Clear the buffer after input from the user*/
void clear_buffer()
{
	int c = 0;
	while (c != '\n' && c != EOF)
	{
		c = getchar();
	}
}

/*Initialize the player by allocating the grid, choosing a name and a symbol */
void initialize_player(Player* player){
	int i,j;
	//Grid allocation
	player->grid = malloc(grid_height*sizeof(int*));
	for(i=0;i<grid_height;i++)
		player->grid[i] = malloc(grid_width*sizeof(int));
	for(i=0;i<grid_height;i++)
		for(j=0;j<grid_width;j++)
			player->grid[i][j]=0;

	//Name
	printf("Choose a name (max 20 characters) : ");
	fgets(player->name,21,stdin);
	player->name[strcspn(player->name, "\n")] = 0;
	if(strlen(player->name)==20)
		clear_buffer();

	//Symbol
	printf("Choose a symbol (1 character) : ");
	scanf(" %c",&player->symbol);
	clear_buffer();

	printf("\n");
}

/* Display player name and symbol */
void display_player(Player player){
	printf("Player '%s' uses symbol '%c'\n",player.name,player.symbol);
}

/* Display moves of the given player as parameter */
void display_player_grid(Player player){
	int i,j,k;

	display_player(player);

	//Display column letter
	printf("  ");
	for(k=0;k<grid_width;k++)
		printf(" %c",'A'+k);
	printf("\n");

	//First horizontal line of the grid
	printf("  ");
	for(k=0;k<grid_width;k++)
		printf(" -");
	printf("\n");

	for(i=0;i<grid_height;i++){
		//Display row number
		printf(" %c",'A'+i);
		//Display symbol or nothing
		for(j=0;j<grid_width;j++){
			if(player.grid[i][j]==0)
				printf("| ");
			else
				printf("|%c",player.symbol);
		}
		printf("|\n");

		//Horizontal lines
		printf("  ");
		for(k=0;k<grid_width;k++)
			printf(" -");
		printf("\n");
	}
	printf("\n");
}

void display_grid(Player player1, Player player2){
	int i,j,k;
	printf("\n");
	//Display column letter
	printf("   ");
	for(k=0;k<grid_width;k++)
		printf(" %c ",'A'+k);
	printf("\n");

	//First horizontal line of the grid
	printf("   ");
	for(k=0;k<grid_width;k++)
		printf("+--");
	printf("+\n");


	for(i=0;i<grid_height;i++){
		//Display row number
		printf(" %c ",'A'+i);
		for(j=0;j<grid_width;j++){
			//Display symbol or nothing
			if(player1.grid[i][j]==0&&player2.grid[i][j]==0)
				printf("|  ");
			else{
				if(player1.grid[i][j]==0)
					printf("|%c ",player2.symbol);
				else
					printf("|%c ",player1.symbol);
			}
		}
		printf("|\n");

		//Horizontal lines
		printf("   ");
		for(k=0;k<grid_width;k++)
			printf("+--");
		printf("+\n");

	}
	printf("\n");
}

/* Get the number of available moves, used to check if it's the end of the game */
int get_nb_moves(Player ai, Player opponent){
	int i,j,val;
	val=0;
	for(i=0;i<grid_height;i++){
		for(j=0;j<grid_width;j++){
			if(opponent.grid[i][j]==0&&ai.grid[i][j]==0){
				val=val+1;
			}
		}
	}
	return val;
}

/* Check if a row of 5 symbols exists for the given player as parameter */
int check_end(Player player){
	int i,j;

	 //For each row
	for(i=0;i<grid_height;i++){
		//For each column
		for(j=0;j<grid_width;j++){

			//if cell isn't taken we skip
			if (player.grid[i][j]==0)
				continue;

			// check right
			if (j+4<grid_width &&
				player.grid[i][j+1]==1 &&
				player.grid[i][j+2]==1 &&
				player.grid[i][j+3]==1 &&
				player.grid[i][j+4]==1)
			return 1;


			if (i+4<grid_height){
				// check down
				if(player.grid[i+1][j]==1 &&
					player.grid[i+2][j]==1 &&
					player.grid[i+3][j]==1 &&
					player.grid[i+4][j]==1)
				return 1;

				//check right and down
				if (j+4<grid_width &&
					player.grid[i+1][j+1]==1 &&
					player.grid[i+2][j+2]==1 &&
					player.grid[i+3][j+3]==1 &&
					player.grid[i+4][j+4]==1)
					return 1;

				//check left and down
				if (j-4>=0 &&
					player.grid[i+1][j-1]==1 &&
					player.grid[i+2][j-2]==1 &&
					player.grid[i+3][j-3]==1 &&
					player.grid[i+4][j-4]==1)
				return 1;
			}
		}
	}
	return 0;
}

/* Free memory allocated for a player */
void free_player(Player* player){
	int i;
	for (i = 0; i < grid_height; i++)
	{
		int* Ptr = player->grid[i];
		free(Ptr);
	}
	free(player->grid);
}

/* Add symbol on the grid for the player given as first parameter */
void add_symbol(Player* player,Player opponent)
{
	char row=0;
	char column=0;
	printf("%s (symbol: %c)\n",player->name,player->symbol);
	//Loop until valid cell
	while(row==0){
		//Loop until valid row
		while(row<'A'||row>'A'+grid_height-1){
			printf("Choose a valid row letter: ");
			scanf(" %c",&row);
			clear_buffer();
		}
		//Loop until valid column
		while(column<'A'||column>'A'+grid_width-1){
			printf("Choose a valid column letter: ");
			scanf(" %c",&column);
			clear_buffer();
		}
		//If cell already taken
		if(opponent.grid[row-'A'][column-'A']==1||player->grid[row-'A'][column-'A']==1){
			printf("Cell already taken, choose a new cell.\n");
			row=0;
			column=0;
		}
	}
	//if valid cell, add in the grid of the player
	player->grid[row-'A'][column-'A']=1;
}

void display_value_cell(Player player, Player ai){
	char row=0;
	char column=0;
	printf("%s (symbol: %c), Choose cell to see its value:\n",player.name,player.symbol);
	//Loop until valid cell
	while(row==0){
		//Loop until valid row
		while(row<'A'||row>'A'+grid_height-1){
			printf("Choose a valid row letter: ");
			scanf(" %c",&row);
			clear_buffer();
		}
		//Loop until valid column
		while(column<'A'||column>'A'+grid_width-1){
			printf("Choose a valid column letter: ");
			scanf(" %c",&column);
			clear_buffer();
		}
		//If cell already taken
		if(ai.grid[row-'A'][column-'A']==1||player.grid[row-'A'][column-'A']==1){
			printf("Cell already taken, choose a new cell.\n");
			row=0;
			column=0;
		}
	}
	printf("Cell value : %d\n",get_value_cell(ai,player,row-'A',column-'A'));
}

void display_value_grid(Player player, Player opponent){
	int i,j,k;
	printf("\n");
	printf("%s value grid (symbol: %c)\n",player.name,player.symbol);
	//Display column letter
	printf("   \t");
	for(k=0;k<grid_width;k++)
		printf(" %c\t",'A'+k);
	printf("\n");

	//First horizontal line of the grid
	printf("   \t");
	for(k=0;k<grid_width;k++)
		printf("+----\t");
	printf("+\n");


	for(i=0;i<grid_height;i++){
		//Display row number
		printf(" %c \t",'A'+i);
		for(j=0;j<grid_width;j++){
			//Display value
			if(player.grid[i][j]==0&&opponent.grid[i][j]==0)
				printf("|%d\t",get_value_cell(player,opponent,i,j));
			else{
				if(player.grid[i][j]==0)
					printf("|%c\t",opponent.symbol);
				else
					printf("|%c\t",player.symbol);
			}
		}
		printf("|\n");

		//Horizontal lines
		printf("   \t");
		for(k=0;k<grid_width;k++)
			printf("+----\t");
		printf("+\n");

	}
	printf("\n");

}

int main()
{
	// turn 1 means AI turn, turn 0 means Player turn
	int turn=0,nb_turn=0;
	/* char pause; */
	Player player1;
	Player ai;
	clock_t start, end;
	double cpu_time_used;

	//Initialize
	printf("Player 1\n");
	initialize_player(&player1);
	printf("Player 2\n");
	initialize_player(&ai);

	//Start of the game
	display_player(player1);
	display_player(ai);
	display_grid(player1,ai);

	//Loop until end of game
	while(!check_end(player1)&&!check_end(ai)&&get_nb_moves(player1,ai)>0){
		if(turn==0){
			//display_value_grid(player1,ai);
			display_player(player1);
			//start = clock();
			add_symbol(&player1,ai);
			/*end = clock();
			cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
			printf("Nb leafs %d\n",nb_leaf);
			printf("Time used : %.3fsec\n",cpu_time_used);
			scanf("%c",&pause);*/
			nb_leaf=0;
			turn=1;
		}
		//Ai's turn
		else{
			//add_symbol(&ai,player1);
			//display_value_grid(player1,ai);
			display_player(ai);
			start = clock();
			add_symbol_ai(&ai,player1);
			end = clock();
			cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
			printf("Nb leafs %d\n",nb_leaf);
			printf("Time used : %.3fsec\n",cpu_time_used);
			//scanf("%c",&pause);
			nb_leaf=0;
			turn=0;
		}
		display_grid(player1,ai);
		nb_turn++;
	}

	printf("End of the game.\n");
	printf("Nb turns : %d\n",nb_turn);
	//Check who is the winner
	if(check_end(player1)||check_end(ai)){
		if(turn==1)
			printf("%s wins.\n",player1.name);
		else
			printf("%s wins.\n",ai.name);
	}
	else
		printf("Full grid, it's a tie.\n");

	//Free memory allocated by players
	free_player(&player1);
	free_player(&ai);
	return 0;
}
