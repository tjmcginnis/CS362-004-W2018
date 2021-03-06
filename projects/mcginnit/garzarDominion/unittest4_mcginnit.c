#include "dominion.h"
#include "testHelpers_mcginnit.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * Function under test: fullDeckCount
 * 
 * What it does:
 *  Counts how many of a given card are in a players
 *   deck, hand, and discard pile
 * 
 * Side effects:
 *  None
 *
 * Test Cases:
 *  None of the given card in player's deck, hand, or discard pile
 *  1 of card in deck, 0 in hand, 0 in discard
 *  1 of card in deck, 1 in hand, 0 in discard
 *  1 of card in deck, 1 in hand, 1 in discard
 *  No game state modified
 *
 */

void testFullDeckCount () {
    printf("----- TESTING fullDeckCount() -----\n");
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

    // None of the given card in player's deck, hand, or discard pile
    if (fullDeckCount(0, adventurer, &G) == 0) {
        printf("fullDeckCount(): PASS adventurer count 0\n");
    } else {
        printf("fullDeckCount(): FAIL adventurer count 0\n");
    }

    // 1 of card in deck, 0 in hand, 0 in discard
    G.deck[0][G.deckCount[0]] = adventurer;
    G.deckCount[0]++;

    if (fullDeckCount(0, adventurer, &G) == 1) {
        printf("fullDeckCount(): PASS adventurer count 1\n");
    } else {
        printf("fullDeckCount(): FAIL adventurer count 1\n");
    }

    // 1 of card in deck, 1 in hand, 0 in discard
    G.hand[0][G.handCount[0]] = adventurer;
    G.handCount[0]++;

    if (fullDeckCount(0, adventurer, &G) == 2) {
        printf("fullDeckCount(): PASS adventurer count 2\n");
    } else {
        printf("fullDeckCount(): FAIL adventurer count 2\n");
    }

    // 1 of card in deck, 1 in hand, 1 in discard
    G.discard[0][G.discardCount[0]] = adventurer;
    G.discardCount[0]++;

    if (fullDeckCount(0, adventurer, &G) == 3) {
        printf("fullDeckCount(): PASS adventurer count 3\n");
    } else {
        printf("fullDeckCount(): FAIL adventurer count 3\n");
    }

    // Undo the changes we made in the tests
    G.deck[0][G.deckCount[0] - 1] = G_copy.deck[0][G.deckCount[0] - 1];
    G.deckCount[0]--;
    G.hand[0][G.handCount[0] - 1] = G_copy.hand[0][G.handCount[0] - 1];
    G.handCount[0]--;
    G.discard[0][G.discardCount[0] - 1] = G_copy.discard[0][G.discardCount[0] - 1];
    G.discardCount[0]--;

    // check that G was not mutated
    if (checkIdenticalGameStates(&G, &G_copy)) {
        printf("fullDeckCount(): PASS no game state modified\n");
    } else {
        printf("fullDeckCount(): FAIL game state modified\n");
    }
}

int main (int argc, char** argv) {
    testFullDeckCount();
    return 0;
}
