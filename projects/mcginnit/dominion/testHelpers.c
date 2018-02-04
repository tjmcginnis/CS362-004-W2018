#include "dominion.h"
#include <stdio.h>
#include <stdlib.h>

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
