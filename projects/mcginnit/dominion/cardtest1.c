/**
 * cardtest1.c
 *
 * Card under test: smithy
 * 
 * What it does:
 *  +3 Cards
 * 
 * What to test:
 *  When smithy is played, the top 3 cards are moved from
 *   the player's deck to the player's hand
 *  When smithy is played, it is removed from the
 *   player's hand
 *  When smithy is played, the current number of actions
 *   the player has is decreased by 1
 *  When smithy is played, no additional game state (the
 *   above two cases being the exception) is modified.
 *
 * Include the following line in your makefile:
 * 
 * cardtest1: cardtest1.c dominion.o rngs.o testHelpers.o
 * gcc -o cardtest1 -g cardtest1.c dominion.o rngs.o testHelpers.o $(CFLAGS)
 */
#include "dominion.h"
#include "testHelpers.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

void testSmithy () {
    printf("----- TESTING SMITHY -----\n");
    struct gameState G;
    int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
           sea_hag, tribute, smithy};
    initializeGame(2, k, 10, &G);

    int i;
    int player = 0;

    // add smithy to the player's deck
    G.deck[player][G.deckCount[player]] = smithy;
    G.deckCount[player]++;

    // set up a hand for the player
    G.handCount[player] = 0;
    G.discardCount[player] = 0;

    int smithyPos = 0;
    G.hand[player][smithyPos] = smithy;
    G.handCount[player]++;
    G.deckCount[player]--;

    // take the top 4 cards from the player's deck and
    // fill out the player's hand
    for (i = 1; i < 5; i++) {
        G.hand[player][i] = G.deck[player][G.deckCount[player]]; 
        G.handCount[player]++;
        G.deckCount[player]--;
    }

    G.whoseTurn = 0;

    int deckCount = G.deckCount[player];
    int nextCard1 = G.deck[player][G.deckCount[player]];
    int nextCard2 = G.deck[player][G.deckCount[player] - 1];
    int nextCard3 = G.deck[player][G.deckCount[player] - 2];

    // make a copy of the state before testing
    struct gameState G_copy;
    memcpy(&G_copy, &G, sizeof(struct gameState));

    // play smithy 
    playCard(smithyPos, -1, -1, -1, &G);

    // Check top 3 cards moved from deck to hand
    int handCount = G.handCount[player];
    test(G.deckCount[player] == (deckCount - 3), "smithy", "it has 3 less cards in the deck");
    test(G.hand[player][handCount - 3] == nextCard1, "smithy", "it moves the first card in the deck to the hand");
    test(G.hand[player][handCount - 2] == nextCard2, "smithy", "it moves the second card in the deck to the hand");
    test(G.hand[player][handCount - 1] == nextCard3, "smithy", "it moves the third card in the deck to the hand");

    // Check smithy removed from the player's hand
    // **NOTE: These should fail due to bug introduced in week 2
    int discardCount = G.discardCount[player];
    test(G.hand[player][smithyPos] != smithy, "smithy", "it discards smithy from the hand");
    test(G.discard[player][discardCount - 1] == smithy, "smithy", "it moves smithy to the discard pile");

    // Check numActions decremented
    test(G.numActions == G_copy.numActions - 1, "smithy", "it decrements numActions by 1");

    // Reset the deck
    for (i = 0; i < G.deckCount[player]; i++) {
        G.deck[player][i] = G_copy.deck[player][i];
    } 
    G.deckCount[player] = G_copy.deckCount[player];

    // Reset the hand
    for (i = 0; i < G.handCount[player]; i++) {
        G.hand[player][i] = G_copy.hand[player][i];
    }
    G.handCount[player] = G_copy.handCount[player];

    // Reset the discard pile
    for (i = 0; i < G.discardCount[player]; i++) {
        G.discard[player][i] = G_copy.discard[player][i];
    }
    G.discardCount[player] = G_copy.discardCount[player];
    
    // Reset numActions
    G.numActions = G_copy.numActions;

    // Reset coins
    G.coins = G_copy.coins;

    // Check no additional game state modified
    test(checkIdenticalGameStates(&G, &G_copy), "smithy", "it does not modify unrelated game state");
}

int main (int argc, char** argv) {
    testSmithy();
    return 0;
}
