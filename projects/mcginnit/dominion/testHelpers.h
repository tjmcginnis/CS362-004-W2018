#include "dominion.h"

#ifndef _TEST_HELPERS_H
#define _TEST_HELPERS_H

void test(int result, char* test, char* description);
int checkIdenticalGameStates (struct gameState *first, struct gameState *second);

#endif
