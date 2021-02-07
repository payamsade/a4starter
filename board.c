/**
 * Assignment: life
 * Name :Payam Sadeghian
 * PID: A13654507
 * Class: UCSD CSE30-WI21
 *
 */
#include "cse30life.h"
#include "board.h"


/**
 * create a new board
 *
 * - malloc a boards structure
 * - set the generation to 0
 * - open the file (if it doesn't exist, return a NULL pointer
 * - read the first line which is the number of rows
 * - read the second line which is the number of cols
 * - set the # of rows and # of cols in the boards structure
 * - malloc bufferA and bufferB 
 * - Set currentBuffer and nextBuffer
 * - clear both board buffers
 * - read the file until done.  each row contains a row and a columns separted by
 *   white space
 *     for each line, set the cell in the current buffer
 * - ensure that no border cells are set to alive
 * - close the file
 * - return the boards pointer if successfull or NULL ptr otherwise
 */
boards_t * createBoard(char *initFileName){

	boards_t *new_board=(boards_t*) malloc(sizeof(boards_t));
	new_board->gen = 0;



	FILE *fp; // a pointer to a file stream
// Attempt to open the file for reading and assign
// the file stream to fp.
	if ((fp = fopen(initFileName, "r")) == NULL) {
		free(new_board);
		return NULL;
	}

	int num;
	int numTwo;
	int rowValue;
	int colValue;
	int area;
	int locA;

	fscanf(fp, "%d", &rowValue);
	if (rowValue < 3) {
		free(new_board);
		return NULL;
	}
	new_board->numRows = rowValue;

	fscanf(fp, "%d", &colValue);
	if (colValue < 3) {
		free(new_board);
		return NULL;
	}
	new_board->numCols = colValue;

	area = colValue * rowValue;


	new_board->bufferA =(belem*) malloc(sizeof(belem)*area);
	new_board->bufferB =(belem*) malloc(sizeof(belem)*area);

	new_board->currentBuffer = new_board->bufferA;
	new_board->nextBuffer = new_board->bufferB;
	clearBoards(new_board);
	

	while(fscanf(fp, "%d %d", &num, &numTwo) > 0) {
		//Do things with num, numTwo here

		locA = getIndex(new_board, num, numTwo);
		new_board->currentBuffer[locA] = 1;
	}
	//set the top edge to 0
	int i;
	i = 0;
	for (; i < colValue; i++) {
		new_board->currentBuffer[i] = 0;
	}

	//set the bottom edge to 0
	i=0;
	locA = colValue * (rowValue -1);
	for(; i < colValue; i++) {
		new_board->currentBuffer[(locA+i)] = 0;
	}

	//set the left edge to 0
	i = 0;
	for(; i < rowValue; i++) {
		new_board->currentBuffer[(colValue*i)] = 0;
	}

	//set the right edge to 0
	i = 1;
	for(; i < rowValue+1; i++) {
	       new_board->currentBuffer[((colValue*i)-1)] = 0;
	}	       

	fclose(fp); // remember to close your filestream

	return(new_board);

	//return Null otherwise
}



/**
 * delete a board
 */
void deleteBoard(boards_t **bptrPtr){

	free((*bptrPtr)->bufferA);
	free((*bptrPtr)->bufferB);
	free(*bptrPtr);
	*bptrPtr = NULL;


	//Make sure to free all the struct components
}

/**
 * set all the belems in both buffers to 0
 */
void clearBoards(boards_t *self){
	int n;
	n = (self->numRows) * (self->numCols);
	memset(self->bufferA, 0, n*sizeof(belem));
	memset(self->bufferB, 0, n*sizeof(belem));
}

/**
 * swap the current and next buffers
 */
void swapBuffers(boards_t *self){
	self->currentBuffer = self->bufferB;
	self->nextBuffer = self->bufferA;
}


/**
 * get a cell index
 */
int getIndex(boards_t *self, int row, int col){
	int index;
	int numC;
	int numR;

	numC = self->numCols;
	numR = self->numRows;

	if (row > numR) {
		exit(1);
	}
	if (col > numC) {
		exit(1);
	}
	index = (row * numC) + col;
	return(index);
} 
