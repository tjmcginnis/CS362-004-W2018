/**
 * cardtest3.c
 *
 * Card under test: village
 * 
 * What it does: 
 *  +1 Card
 *  +2 Actions
 * 
 * What to test:
 *  The top card from the player's deck is added to the player's hand
 *  The player gains two actions
 *  The village card is discarded
 *  No additional game state modified
 *
 * Include the following line in your makefile:
 * 
 * cardtest3: cardtest3.c dominion.o rngs.o testHelpers.o
 * gcc -o cardtest3 -g cardtest3.c dominion.o rngs.o testHelpers.o $(CFLAGS)
 */
#include "dominion.h"
#include "testHelpers.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void testVillage () {
    printf("----- TESTING VILLAGE -----\n");
    struct gameState G;
    int player = 0;
    int villagePos = setUp(&G, village, player, 2); 
 
    // make a copy of the game state before testing
    struct gameState G_copy;
    memcpy(&G_copy, &G, sizeof(struct gameState));

    int top = G.deck[player][G.deckCount[player - 1]];
    int numActions = G.numActions;

    playCard(villagePos, -1, -1, -1, &G);

    test(G.hand[player][G.handCount[player] - 1] == top, "village", "it draws the top card from the player's hand");
    test(G.numActions == (numActions + 1), "village", "it adds two actions");
    test(G.hand[player][villagePos] != village, "village", "it discards the village card");

    cleanUp(&G, &G_copy, 0);

    // Since village discarded, need to reset playedCardCount and playedCards
    G.playedCardCount = G_copy.playedCardCount;
    int i;
    for (i = 0; i < MAX_DECK; i++) {
        G.playedCards[i] = G_copy.playedCards[i];
    }

    // No additional game state modified
    test(checkIdenticalGameStates(&G, &G_copy), "village", "it does not modify unrelated game state");
}

int main (int argc, char** argv) {
    testVillage();
    return 0;
}
