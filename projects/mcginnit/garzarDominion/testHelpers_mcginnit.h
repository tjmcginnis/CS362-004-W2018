#include "dominion.h"

#ifndef _TEST_HELPERS_H
#define _TEST_HELPERS_H

void test(int result, char* test, char* description);
int setUp(struct gameState *state, int cardUnderTest, int player, int numPlayers);
void cleanUp (struct gameState *original, struct gameState *copy, int player);
int checkIdenticalGameStates (struct gameState *first, struct gameState *second);

#endif
