#include "dominion.h"
#include <stdio.h>
#include <stdlib.h>


// Run a test
void test (int result, char* test, char* description) {
    if (result)
        printf("%s: PASS -- %s\n", test, description);
    else
        printf("%s: FAIL -- %s\n", test, description);
}

// Resets the deck, hand, discard pile, numActions, and coins
void cleanUp (struct gameState *original, struct gameState *copy, int player) {
    int i;

    // Reset the deck
    for (i = 0; i < original->deckCount[player]; i++) {
        original->deck[player][i] = copy->deck[player][i];
    } 
    original->deckCount[player] = copy->deckCount[player];

    // Reset the hand
    for (i = 0; i < original->handCount[player]; i++) {
        original->hand[player][i] = copy->hand[player][i];
    }
    original->handCount[player] = copy->handCount[player];

    // Reset the discard pile
    for (i = 0; i < original->discardCount[player]; i++) {
        original->discard[player][i] = copy->discard[player][i];
    }
    original->discardCount[player] = copy->discardCount[player];
    
    // Reset numActions
    original->numActions = copy->numActions;

    // Reset coins
    original->coins = copy->coins;
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

