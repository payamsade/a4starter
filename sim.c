/**
 * Assignment: life
 * Name: Payam Sadeghian
 * PID: A13654507
 * Class: UCSD CSE30-WI21
 *
 */
#include "sim.h"

#define CIMP
extern void asm_doRow(belem *, belem *, belem *, uint32_t);

/**
 * process one row of the board
 */
static void doRow(belem *dest, belem *srcStart, belem * srcEnd, uint32_t cols) {

	int reqNum = 0;
	while(srcStart != srcEnd+1) {
		reqNum = 0;

		if( *(srcStart - cols - 1) == 1) { //NW
			reqNum++; }
		if( *(srcStart - cols) == 1) { //N 
			reqNum++; }

		if (*(srcStart - cols + 1) == 1) { //NE
			reqNum++;}

		if (*(srcStart - 1) == 1) {//W
			reqNum++;}

		if (*(srcStart + 1) == 1) {//E
			reqNum++;
		}

		if (*(srcStart + cols - 1) == 1) {//SW
			reqNum++;}

		if (*(srcStart + cols) == 1) {//S
			reqNum++;}

		if (*(srcStart + cols + 1) == 1) {//SE
			reqNum++;}

		//reqNum += (int) *(srcStart-cols-1);
		//reqNum += (int) *(srcStart-cols);
		//reqNum += (int) *(srcStart-cols+1);
		//reqNum += (int) *(srcStart-1);
		//reqNum += (int) *(srcStart+1);
		//reqNum += (int) *(srcStart+cols-1);
		//reqNum += (int) *(srcStart+cols);
		//reqNum += (int) *(srcStart+cols+1);

		if(* srcStart == 1) {


			if ( reqNum == 2 || reqNum == 3) {
				*dest = 1;
			}
			else {
				*dest = 0;
			}
		}

		if ( *srcStart == 0) {
			if (reqNum == 3) {
				*dest = 1;
			}
			else {
				*dest = 0;
			}

		}
		dest++;
		srcStart++;
		//printf("loop variable = %d", q);
		//printf("%c ", *srcStart);

		//fprintf(stdout, "loop variable = %d ", q);
	}
}


/**
 * perform a simulation for "steps" generations
 *
 * for steps
 *   calculate the next board
 *   swap current and next
 */
void simLoop(boards_t *self, uint32_t steps){
	//
	//Can add the getIndex method
	//
	//write all the values beforehand.

	uint32_t j = 0; //increment for firt loop
	uint32_t g = 1; //increment for sencond loop, the first row variable
	int start = 0; //start point
	int end = 0; //end point
	uint32_t rows = self->numRows; //number of rows
	uint32_t columns = self->numCols; //number of columns
	for (; j < steps; j++) { //loop per step
		for(; g < rows-2; g++) { //loop per amount of rows on the board -1 since we want proper amount of rows
			start = getIndex(self, g, 1); //return the value of the location in terms of 2D array
			end = getIndex(self, g, columns-2); //end is the value of the location in terms of the 2d array
			doRow(&(self->nextBuffer[start]),&(self->currentBuffer[start]),&(self->currentBuffer[end]), columns);
		}
		swapBuffers(self);
		//fprintf(stderr, "loop variable = %d", g);
		self->gen = self->gen + 1;
	}
	//fprint(stderr, "loop variable = %d", j);
}
