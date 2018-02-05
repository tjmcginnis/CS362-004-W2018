#include "dominion.h"
#include "testHelpers.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * Function under test: isGameOver 
 *
 * What it does:
 *  Checks if the game is over, using the following heuristics:
 *    - if the supply count for province cards is 0, the game is over
 *    - if the supply count for three supply piles is 0, the game is over
 *    - if neither of the above are true, the game is not over
 * 
 * Side effects:
 *  None
 *
 * Test Cases:
 *  isGameOver returns 1 if gameState->supplyCount[province] is 0
 *  isGameOver returns 0 if gameState->supplyCount[province] is greater than 0
 *    (and gameState->supplyCount[CARD] is not 0 for 3 or more cards)
 *  isGameOver returns 1 if gameState->supplyCount[CARD] is 0 for 3 cards
 *    (and gameState->supplyCount[province] is greater than 0)
 *  isGameOver returns 1 if gameState->supplyCount[CARD] is 0 for more than 3 cards
 *    (and gameState->supplyCount[province] is greater than 0)
 *  isGameOver returns 0 if gameState->supplyCount[CARD] is 0 for 2 cards
 *    (and gameState->supplyCount[province] is greater than 0)
 *  isGameOver returns 0 if gameState->supplyCount[CARD] is 0 for 1 card
 *    (and gameState->supplyCount[province] is greater than 0)
 *  isGameOver returns 0 if gameState->supplyCount[CARD] is 0 for no cards
 *    (and gameState->supplyCount[province] is greater than 0)
 *  No other properties of the gameState are changed when isGameOver is called
 */

// Set the state's supply count for province
void setProvinceSupplyCount (struct gameState *state, int count) {
    state->supplyCount[province] = count;
}

void testIsGameOver ()
{
    printf("----- TESTING isGameOver() -----\n");
    struct gameState G;
    int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
           sea_hag, tribute, smithy};

    // Maybe not ideal since we haven't tested initializeGame,
    // but this way we can easily check game relevant data
    // on the game state 
    initializeGame(2, k, 10, &G);

    // Make a copy of the game state  that we can use later to
    // verify isGameOver committed no side effects
    struct gameState G_copy = G;

    // Test isGameOver returns 1 if supplyCount[province] is 0
    setProvinceSupplyCount(&G, 0); 
    if (isGameOver(&G)) {
        printf("isGameOver(): PASS returns 1 if supplyCount[province] is 0\n");
    } else {
        printf("isGameOver(): FAIL returns 1 if supplyCount[province] is 0\n");
    }

    // Test isGameOver returns 0 if supplyCount[province] is greater than 0
    setProvinceSupplyCount(&G, 1);
    if (!isGameOver(&G)) {
        printf("isGameOver(): PASS returns 0 if supplyCount[province] is greater than 0\n");
    } else {
        printf("isGameOver(): FAIL returns 0 if supplyCount[province] is greater than 0\n");
    }

    int originalCountAdventurer = G.supplyCount[adventurer];
    int originalCountSmithy = G.supplyCount[smithy];
    int originalCountGardens = G.supplyCount[gardens];

    // empty three supply piles
    G.supplyCount[adventurer] = 0;
    G.supplyCount[smithy] = 0;
    G.supplyCount[gardens] = 0;

    // Test isGameOver returns 1 if there are 3 cards with supplyCount set to 0
    if (isGameOver(&G)) {
        printf("isGameOver(): PASS returns 1 if supplyCount[CARD] is 0 for three cards\n");
    } else {
        printf("isGameOver(): FAIL returns 0 if supplyCount[CARD] is 0 for three cards\n");
    }

    int originalCountEmbargo = G.supplyCount[embargo];

    // Test isGameOver returns 1 if more than 3 cards with supplyCount set to 0
    if (isGameOver(&G)) {
        printf("isGameOver(): PASS returns 1 if supplyCount[CARD] is 0 for more than three cards\n");
    } else {
        printf("isGameOver(): FAIL returns 0 if supplyCount[CARD] is 0 for more than three cards\n");
    }

    G.supplyCount[adventurer] = originalCountAdventurer;
    G.supplyCount[smithy] = originalCountSmithy;

    // Test isGameOver returns 0 if 2 cards with supplyCount set to 0
    if (!isGameOver(&G)) {
        printf("isGameOver(): PASS returns 0 if supplyCount[CARD] is 0 for two cards\n");
    } else {
        printf("isGameOver(): FAIL returns 0 if supplyCount[CARD] is 0 for two cards\n");
    }

    G.supplyCount[gardens] = originalCountGardens;

    // Test isGameOver returns 0 if 1 card with SupplyCount set to 0
    if (!isGameOver(&G)) {
        printf("isGameOver(): PASS returns 0 if supplyCount[CARD] is 0 for one card\n");
    } else {
        printf("isGameOver(): FAIL returns 0 if supplyCount[CARD] is 0 for one card\n");
    }

    G.supplyCount[embargo] = originalCountEmbargo;

    // Test isGameOver returns 0 if no cards with SupplyCount set to 0
    if (!isGameOver(&G)) {
        printf("isGameOver(): PASS returns 0 if supplyCount[CARD] is 0 for no cards\n");
    } else {
        printf("isGameOver(): FAIL returns 0 if supplyCount[CARD] is 0 for no cards\n");
    }

    // Set G's supply count for province back to original value
    G.supplyCount[province] = G_copy.supplyCount[province];

    // Test no side effects
    if (checkIdenticalGameStates(&G, &G_copy)) {
        printf("isGameOver(): PASS no additional game state modified\n");
    } else {
        printf("isGameOver(): FAIL additional game state modified\n");
    }
}

int main (int argc, char** argv) {
    testIsGameOver();
    return 0;
}
