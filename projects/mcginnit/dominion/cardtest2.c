/**
 * cardtest2.c
 *
 * Card under test: adventurer 
 * 
 * What it does:
 *  Reveal cards from your deck
 *  until you reveal 2 Treasure cards.
 *  Put those Treasure cards into your hand
 *  and discard the other revealed cards.
 * 
 * What to test:
 *  The player's hand gains two cards
 *  The two cards gained are Treasure cards
 *  The number of cards in the discard pile increases by (NUM_CARDS_DRAWN - 2)
 *  numActions is decremented by 1
 *  No additional game state is modified
 *
 * Include the following line in your makefile:
 * 
 * cardtest2: cardtest2.c dominion.o rngs.o testHelpers.o
 * gcc -o cardtest2 -g cardtest2.c dominion.o rngs.o testHelpers.o $(CFLAGS)
 */
#include "dominion.h"
#include "testHelpers.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void testAdventurer () {
    printf("----- TESTING ADVENTURER -----\n");
    struct gameState G;
    int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
           sea_hag, tribute, smithy};
    initializeGame(2, k, 10, &G);

    int i;
    int player = 0;
 
    // add adventurer to the player's deck
    G.deck[player][G.deckCount[player]] = adventurer;
    G.deckCount[player]++;

    // set up a hand for the player
    G.handCount[player] = 0;
    G.discardCount[player] = 0;

    int adventurerPos = 0;
    G.hand[player][adventurerPos] = adventurer;
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

    int originalDeckCount = G.deckCount[player];
    int originalHandCount = G.handCount[player];
    int originalDiscardCount = G.discardCount[player];
    int expectedNumActions = G.numActions - 1;

    // make a copy of the game state before testing
    struct gameState G_copy;
    memcpy(&G_copy, &G, sizeof(struct gameState));

    playCard(adventurerPos, -1, -1, -1, &G);

    int numCardsDrawn = originalDeckCount - G.deckCount[player];
    
    //  The player's hand gains two cards
    //  **NOTE: This should fail due to bug introduced in week 2
    test(G.handCount[player] == (originalHandCount + 2), "adventurer", "it adds two cards to the hand");

    //  The two cards gained are Treasure cards (has value between 4 and 6)
    int gainedCard1 = G.hand[player][G.handCount[player] - 1];
    int isTreasure = (gainedCard1 >= 4) && (gainedCard1 <= 6);
    test(isTreasure, "adventurer", "it gained one treasure card");
    int gainedCard2 = G.hand[player][G.handCount[player] - 2];
    isTreasure = (gainedCard2 >= 4) && (gainedCard2 <= 6);
    test(isTreasure, "adventurer", "it gained two treasure cards");

    //  The number of cards in the discard pile increases by (NUM_CARDS_DRAWN - 2)
    //  **NOTE: This should fail due to bug introduced in week 2
    int expectedDiscardCount = originalDiscardCount + (numCardsDrawn - 2);
    test(G.discardCount[player] == expectedDiscardCount, "adventurer", "it increases the discard pile by the correct amount");

    //  numActions is decremented by 1
    test(G.numActions == expectedNumActions, "adventurer", "it decrements numActions by 1");

    cleanUp(&G, &G_copy, player);

    //  No additional game state is modified
    test(checkIdenticalGameStates(&G, &G_copy), "adventurer", "it does not modify unrelated game state");

}

int main (int argc, char** argv) {
    testAdventurer();
    return 0;
}
