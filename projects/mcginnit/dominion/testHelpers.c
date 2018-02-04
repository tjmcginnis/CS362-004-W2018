#include "dominion.h"
#include <stdio.h>
#include <stdlib.h>


// Run a test
void test(int result, char* test, char* description) {
    if (result)
        printf("%s: PASS -- %s\n", test, description);
    else
        printf("%s: FAIL -- %s\n", test, description);
}

// Check two game states are identical
int checkIdenticalGameStates (struct gameState *first, struct gameState *second) {
    if (first->numPlayers != second->numPlayers) return 0;
    // printf("Pass\n");
    if (first->outpostPlayed != second->outpostPlayed) return 0;
    // printf("Pass\n");
    if (first->outpostTurn != second->outpostTurn) return 0;
    // printf("Pass\n");
    if (first->whoseTurn != second->whoseTurn) return 0;
    // printf("Pass\n");
    if (first->phase != second->phase) return 0;
    // printf("Pass\n");
    if (first->numActions != second->numActions) return 0;
    // printf("Pass\n");
    if (first->coins != second->coins) return 0;
    // printf("Pass\n");
    if (first->numBuys != second->numBuys) return 0;
    // printf("Pass\n");
    if (first->playedCardCount != second->playedCardCount) return 0;
    // printf("Pass\n");

    int i;
    for (i = 0; i < treasure_map+1; i++) {
        if (first->supplyCount[i] != second->supplyCount[i])
            return 0;
    }
    // printf("Pass\n");

    for (i = 0; i < treasure_map+1; i++) {
        if (first->embargoTokens[i] != second->embargoTokens[i])
            return 0;
    }
    // printf("Pass\n");

    int j;
    for (i = 0; i < MAX_PLAYERS; i++) {
        for (j = 0; j < MAX_HAND; j++) {
            if (first->hand[i][j] != second->hand[i][j])
                return 0;
      }
    }
    // printf("Pass\n");

    for (i = 0; i < MAX_PLAYERS; i++) {
        if (first->handCount[i] != second->handCount[i])
            return 0; 
    }
    // printf("Pass\n");

    for (i = 0; i < MAX_PLAYERS; i++) {
        for (j = 0; j < MAX_DECK; j++) {
            if (first->deck[i][j] != second->deck[i][j])
                return 0;
      }
    }
    // printf("Pass\n");

    for (i = 0; i < MAX_PLAYERS; i++) {
        if (first->deckCount[i] != second->deckCount[i])
            return 0;
    }
    // printf("Pass\n");

    for (i = 0; i < MAX_PLAYERS; i++) {
        for (j = 0; j < MAX_DECK; j++) {
            if (first->discard[i][j] != second->discard[i][j])
                return 0;
      }
    }
    // printf("Pass\n");

    for (i = 0; i < MAX_PLAYERS; i++) {
        if (first->discardCount[i] != second->discardCount[i]) {
            return 0;
        }
    }
    // printf("Pass\n");

    for (i = 0; i < MAX_DECK; i++) {
        if (first->playedCards[i] != second->playedCards[i]) {
            return 0;
        }
    }
    // printf("Pass\n");

    return 1;
}

// set up only whats needed for all tests
void makeTestGameState (struct gameState *state) {
    int numPlayers = 2;
    state->numPlayers = numPlayers;
 
    // set up player decks
    int i, j;
    for (i = 0; i < numPlayers; i++) {
        state->deckCount[i] = 0;
        for (j = 0; j < 3; j++) {
            state->deck[i][j] = estate;
            state->deckCount[i]++;
        }
        for (j = 3; j < 10; j++) {
            state->deck[i][j] = copper;
            state->deckCount[i]++;
        }
    }

    // set current phase to the action phase
    state->phase = 0;
    state->numActions = 1;
}
