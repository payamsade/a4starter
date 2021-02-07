/**
 * Assignment: life
 * Name: Payam Sadeghian
 * PID: A13654507
 * Class: UCSD CSE30-WI21
 *
 */
#ifndef _SIM_H
#define _SIM_H
#include "board.h"

extern void simLoop(boards_t *self, uint32_t steps); // simulation loop

static void doRow(belem *dest, belem *srcStart, belem *srcEnd, uint32_t cols);

void simLoop(boards_t *self, uint32_t steps);
#endif
