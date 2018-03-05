/**
 * cardtest4.c
 *
 * Card under test: council room
 * 
 * What it does: 
 *  +4 Cards
 *  +1 Buy
 *
 *  Each other player draws a
 *  card.
 *
 * What to test:
 *  4 cards are drawn from the player's deck
 *  The player gains 1 Buy
 *  The council room card is discarded
 *  For each other player, the top card in that player's deck
 *   is moved to his hand
 *  No additional game state is modified
 *
 * Include the following line in your makefile:
 * 
 * cardtest4: cardtest4.c dominion.o rngs.o testHelpers.o
 * gcc -o cardtest4 -g cardtest4.c dominion.o rngs.o testHelpers.o $(CFLAGS)
 */
#include "dominion.h"
#include "testHelpers_mcginnit.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void testCouncilRoom () {
    printf("----- TESTING COUNCIL ROOM -----\n");
    struct gameState G;
    int player = 0;
    int numPlayers = 2;
    int councilRoomPos = setUp(&G, council_room, player, numPlayers); 
 
    // make a copy of the game state before testing
    struct gameState G_copy;
    memcpy(&G_copy, &G, sizeof(struct gameState));

    int numBuys = G.numBuys;
    int originalDeckCount = G.deckCount[player];

    // get the top card for each other player
    int i;
    int nextCardOtherPlayers[numPlayers];
    for (i = 1; i < G.numPlayers; i++) {
        nextCardOtherPlayers[i] = G.deck[i][G.deckCount[i] - 1];        
    }

    playCard(councilRoomPos, -1, -1, -1, &G);

    // It draws 4 cards from the player's deck
    int numDrawn = originalDeckCount - G.deckCount[player];
    test(numDrawn == 4, "council room", "it draws 4 cards from the player's deck"); 
    
    // The player gains 1 Buy
    test(G.numBuys == numBuys + 1, "council room", "it increases numBuys by 1"); 

    // The council room card is discarded
    test(G.hand[player][councilRoomPos] != council_room, "council room", "it discards the council room card");

    // For each other player,
    // the top card in player's deck is moved to player's hand
    int misses = 0;
    for (i = 1; i < G.numPlayers; i++) {
        if (G.hand[i][G.handCount[i] - 1] != nextCardOtherPlayers[i])
            misses++;
    }
    test(!misses, "council room", "it draws a card for each other player");

    cleanUp(&G, &G_copy, 0);
 
    // Since council_room discarded, need to reset playedCardCount and playedCards
    G.playedCardCount = G_copy.playedCardCount;
    for (i = 0; i < MAX_DECK; i++) {
        G.playedCards[i] = G_copy.playedCards[i];
    }

    // Also need to reset numBuys
    G.numBuys = G_copy.numBuys;

    // Also need to reset other players' hand and deck
    int j;
    for (i = 0; i < G.numPlayers; i++) {
        G.handCount[i] = G_copy.handCount[i];
        for (j = 0; j < MAX_HAND; j++) {
            G.hand[i][j] = G_copy.hand[i][j];
        }

        G.deckCount[i] = G_copy.deckCount[i];
        for (j = 0; j < MAX_DECK; j++) {
            G.deck[i][j] = G_copy.deck[i][j];
        }
    }
 
    // No additional game state is modified
    test(checkIdenticalGameStates(&G, &G_copy), "council room", "it does not modify unrelated game state");
}

int main (int argc, char** argv) {
    testCouncilRoom();
    return 0;
}
