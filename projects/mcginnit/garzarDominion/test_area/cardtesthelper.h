/*********************************************************************
 ** Author: Romano Garza
 ** Date: 02/22/17
 ** Description: Helper functions for card effect unit tests
 *********************************************************************/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

int inDeck(int player, struct gameState state, int card); // used in smithy test
int inHandCount(int player, int handCount, struct gameState state, int card);
int getTreasureyCardCount(int player, struct gameState state); // used in adventurer test
void emptyDeck(int player, struct gameState *state); // used in adventurer test
void advC3(int player, struct gameState *state); // used to alter state adventurer for case 3
void advC4(int player, struct gameState *state); // used to alter state of adventurer for case 4
void testEmptyDeck(int player, struct gameState *state, int previousCount); // unit test for emptyDeck
void testGTCC(int player, struct gameState state); // unit test for getTreasureyCardCount
struct gameState myInitGame();
