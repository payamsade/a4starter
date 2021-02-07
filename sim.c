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
static void doRow(belem *dest, belem *srcStart, belem * srcEnd, uint32_t cols){

	int reqNum;
	int q;
	int w;
	w = (int16_t) cols;
	q = 0;
	reqNum = 0;
	for (; q < w-1; q++) {
		reqNum = 0;

		if ((*(srcStart-cols-1)) == 1) {
			reqNum++;
		}
		if ((*(srcStart-cols)) == 1) {
			reqNum++;
		}
		if ((*(srcStart-cols+1)) == 1) {
			reqNum++;
		}
		if (( *(srcStart-1)) == 1) {
			reqNum++;
		}
		if ((*(srcStart+1)) == 1) {
			reqNum++;
		}
		if ((*(srcStart+cols-1)) == 1) {
			reqNum++;
		}
		if ((*(srcStart+cols)) == 1) {
			reqNum++;
		}
		if ((*(srcStart+cols+1)) == 1) {
			reqNum++;
		}

		//add case for alive and dead cells


		if( *srcStart == 1) {


			if ( reqNum == 2 || reqNum == 3) {
				*dest = 1;
			}
			else {
				*dest = 0;
			}

			if ( *srcStart == 0) {
				if (reqNum == 3) {
					*dest = 1;
				}
				else {
					*dest = 0;
				}

				*dest = *dest + 1;
				*srcStart = *srcStart + 1;

			}
		}
		//fprintf(stderr, "loop variable = %d", q);
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

	uint32_t j;
	uint32_t g;
	int start;
	int end;
	j = 0;
	g = 1;
	start = 0;
	end = 0;
	for (; j < steps; j++) {



		for(; g < self->numRows-1; g++) {
			start = getIndex(self, 1, g);
			end = getIndex(self, self->numCols-1, g);
			doRow(&(self->nextBuffer[start]),&(self->currentBuffer[start]), &(self->currentBuffer[end]), self->numCols);
		}
		swapBuffers(self);
		//fprintf(stderr, "loop variable = %d", g);
	}
	self->gen = self->gen + 1;
	//fprint(stderr, "loop variable = %d", j);
}
