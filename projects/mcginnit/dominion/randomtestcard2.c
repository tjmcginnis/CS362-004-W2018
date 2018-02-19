/**
 * randomtestcard2.c
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
 *  Include the following lines in your makefile:
 *
 *  randomtestcard2: randomtestcard2.c dominion.o rngs.o
 *  gcc -o randomtestcard2 -g randomtestcard2.c dominion.o rngs.o $(CFLAGS)
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <math.h>
#include "rngs.h"
#include "dominion.h"


int assert_safe(int condition, char* message) {
    if (!condition) {
        printf("Failing: %s\n", message);
    }
    return 0;
}

int checkCardEffect(struct gameState* post, int p) {
    struct gameState pre;
    memcpy(&pre, post, sizeof(struct gameState));

    int r = playCard(0, -1, -1, -1, post);

    //printf("playCard PRE: p %d DC %d HC %d DiC %d nB %d\n",
    //          p, pre.handCount[p], pre.deckCount[p], pre.discardCount[p], pre.numBuys);

    //printf("playCard POST: p %d DC %d HC %d DiC %d nB %d\n",
    //          p, post->handCount[p], post->deckCount[p], post->discardCount[p], post->numBuys);

    assert_safe(r == 0, "playCard returned 0");
    // +3 because council room should be discarded
    assert_safe(pre.handCount[p]+3 == post->handCount[p], "4 cards drawn");
    assert_safe(pre.numBuys+1 == post->numBuys, "1 buy gained");
    assert_safe(post->hand[p][0] != council_room, "council room discarded");

    int i;
    for (i = 0; i < post->numPlayers; i++) {
        if (i != p) {
            assert_safe(pre.handCount[i]+1 == post->handCount[i], "1 card drawn for each other player");
        }
    }

    return 0;
}

int main(int argc, char** argv) {
    int p;
    struct gameState G;

    printf("randomtestcard2: RUNNING\n");

    SelectStream(0);
    PutSeed(1);

    int n, i;
    int numPlayers;
    int deckCount;
    int handCount;
    int discardCount;

    for (n = 0; n < 10000; n++) {
        for (i = 0; i < sizeof(struct gameState); i++) {
            ((char*)&G)[i] = floor(Random() * 256);
        }

        do {
            numPlayers = floor(Random() * MAX_PLAYERS);
        } while (numPlayers == 0);

        G.numPlayers = numPlayers;

        for (i = 0; i < numPlayers; i++) {
            deckCount = floor(Random() * MAX_DECK);
            G.deckCount[i] = deckCount;

            discardCount = floor(Random() * MAX_DECK);
            G.discardCount[i] = discardCount;

            handCount = floor(Random() * MAX_HAND);
            G.handCount[i] = handCount;
        }

        p = floor(Random() * numPlayers);
        G.hand[p][0] = council_room;
        G.playedCardCount = floor(Random() * MAX_HAND);

        G.whoseTurn = p;
        G.phase = 0;
        G.numActions = 1;
        checkCardEffect(&G, p);
    }

    printf("randomtestcard2: ENDING\n");
    
    return 0;
}

