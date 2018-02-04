#include "dominion.h"
#include "testHelpers.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * Function under test: whoseTurn
 * 
 * What it does:
 *  Returns the number of the player whose turn it is 
 * 
 * Side effects:
 *  None
 *
 * Test Cases:
 *  whoseTurn returns the correct value
 *  whoseTurn makes no changes are made to the game state
 */

void testWhoseTurn () {
    struct gameState G;
    int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
           sea_hag, tribute, smithy};

    // Again, not ideal since we haven't tested initializeGame,
    // but makes it so we can check game relevant data on the
    // game state 
    initializeGame(2, k, 10, &G);

    // Make a copy of the game state  that we can use later to
    // verify isGameOver committed no side effects
    struct gameState G_copy = G;

    int failures = 0;

    // On initialization, it should be player 1's turn
    // Player 1 is represented by index 0
    if (whoseTurn(&G) == 0) {
        printf("whoseTurn(): PASS returns 0 when no turns have been taken\n");
    } else {
        printf("whoseTurn(): FAIL returns 0 when no turns have been taken\n");
        failures++;
    }

    G.whoseTurn = 1;

    // whoseTurn modified, should return 1 now
    if (whoseTurn(&G) == 1) {
        printf("whoseTurn(): PASS returns 1 when whoseTurn set to 1\n");
    } else {
        printf("whoseTurn(): FAIL returns 1 when whoseTurn set to 1\n");
        failures++;
    }

    // Set whoseTurn back to 0 before comparing original game state
    G.whoseTurn = 0;

    // check that G was not mutated
    if (checkIdenticalGameStates(&G, &G_copy)) {
        printf("whoseTurn(): PASS no game state modified\n");
    } else {
        printf("whoseTurn(): FAIL game state modified\n");
        failures++;
    }

    if (!failures)
        printf("whoseTurn(): STATUS: Green... all tests passed\n");

    if (failures)
        printf("whoseTurn(): STATUS: RED... 1 or more tests failed\n");
}

int main (int argc, char** argv) {
    testWhoseTurn();
    return 0;
}
