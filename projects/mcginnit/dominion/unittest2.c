#include "dominion.h"
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

// Check two game states are identical
int checkIdenticalGameStates (struct gameState *first, struct gameState *second) {
    if (first->numPlayers != second->numPlayers) return 0;
    if (first->outpostPlayed != second->outpostPlayed) return 0;
    if (first->outpostTurn != second->outpostTurn) return 0;
    if (first->whoseTurn != second->whoseTurn) return 0;
    if (first->phase != second->phase) return 0;
    if (first->numActions != second->numActions) return 0;
    if (first->coins != second->coins) return 0;
    if (first->numBuys != second->numBuys) return 0;
    if (first->playedCardCount != second->playedCardCount) return 0;

    int i;
    for (i = 0; i < treasure_map+1; i++) {
        if (first->supplyCount[i] != second->supplyCount[i])
            return 0;
    }

    for (i = 0; i < treasure_map+1; i++) {
        if (first->embargoTokens[i] != second->embargoTokens[i])
            return 0;
    }

    int j;
    for (i = 0; i < MAX_PLAYERS; i++) {
        for (j = 0; j < MAX_HAND; j++) {
            if (first->hand[i][j] != second->hand[i][j])
                return 0;
      }
    }

    for (i = 0; i < MAX_PLAYERS; i++) {
        if (first->handCount[i] != second->handCount[i])
            return 0; 
    }

    for (i = 0; i < MAX_PLAYERS; i++) {
        for (j = 0; j < MAX_DECK; j++) {
            if (first->deck[i][j] != second->deck[i][j])
                return 0;
      }
    }

    for (i = 0; i < MAX_PLAYERS; i++) {
        if (first->deckCount[i] != second->deckCount[i])
            return 0;
    }

    for (i = 0; i < MAX_PLAYERS; i++) {
        for (j = 0; j < MAX_DECK; j++) {
            if (first->discard[i][j] != second->discard[i][j])
                return 0;
      }
    }

    for (i = 0; i < MAX_PLAYERS; i++) {
        if (first->discardCount[i] != second->discardCount[i]) {
            return 0;
        }
    }

    for (i = 0; i < MAX_DECK; i++) {
        if (first->playedCards[i] != second->playedCards[i]) {
            return 0;
        }
    }

    return 1;
}

void testIsGameOver ()
{
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

    int failures = 0;

    // Test isGameOver returns 1 if supplyCount[province] is 0
    setProvinceSupplyCount(&G, 0); 
    if (isGameOver(&G)) {
        printf("isGameOver(): PASS returns 1 if supplyCount[province] is 0\n");
    } else {
        printf("isGameOver(): FAIL returns 1 if supplyCount[province] is 0\n");
        failures++;
    }

    // Test isGameOver returns 0 if supplyCount[province] is greater than 0
    setProvinceSupplyCount(&G, 1);
    if (!isGameOver(&G)) {
        printf("isGameOver(): PASS returns 0 if supplyCount[province] is greater than 0\n");
    } else {
        printf("isGameOver(): FAIL returns 0 if supplyCount[province] is greater than 0\n");
        failures++;
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
        failures++;
    }

    int originalCountEmbargo = G.supplyCount[embargo];

    // Test isGameOver returns 1 if more than 3 cards with supplyCount set to 0
    if (isGameOver(&G)) {
        printf("isGameOver(): PASS returns 1 if supplyCount[CARD] is 0 for more than three cards\n");
    } else {
        printf("isGameOver(): FAIL returns 0 if supplyCount[CARD] is 0 for more than three cards\n");
        failures++;
    }

    G.supplyCount[adventurer] = originalCountAdventurer;
    G.supplyCount[smithy] = originalCountSmithy;

    // Test isGameOver returns 0 if 2 cards with supplyCount set to 0
    if (!isGameOver(&G)) {
        printf("isGameOver(): PASS returns 0 if supplyCount[CARD] is 0 for two cards\n");
    } else {
        printf("isGameOver(): FAIL returns 0 if supplyCount[CARD] is 0 for two cards\n");
        failures++;
    }

    G.supplyCount[gardens] = originalCountGardens;

    // Test isGameOver returns 0 if 1 card with SupplyCount set to 0
    if (!isGameOver(&G)) {
        printf("isGameOver(): PASS returns 0 if supplyCount[CARD] is 0 for one card\n");
    } else {
        printf("isGameOver(): FAIL returns 0 if supplyCount[CARD] is 0 for one card\n");
        failures++;
    }

    G.supplyCount[embargo] = originalCountEmbargo;

    // Test isGameOver returns 0 if no cards with SupplyCount set to 0
    if (!isGameOver(&G)) {
        printf("isGameOver(): PASS returns 0 if supplyCount[CARD] is 0 for no cards\n");
    } else {
        printf("isGameOver(): FAIL returns 0 if supplyCount[CARD] is 0 for no cards\n");
        failures++;
    }

    // Set G's supply count for province back to original value
    G.supplyCount[province] = G_copy.supplyCount[province];

    // Test no side effects
    if (checkIdenticalGameStates(&G, &G_copy)) {
        printf("isGameOver(): PASS no additional game state modified\n");
    } else {
        printf("isGameOver(): FAIL additional game state modified\n");
        failures++;
    }

    if (!failures)
        printf("isGameOVER(): STATUS: Green... all tests passed\n");

    if (failures)
        printf("isGameOver(): STATUS: RED... 1 or more tests failed\n");
}

int main (int argc, char** argv) {
    testIsGameOver();
    return 0;
}