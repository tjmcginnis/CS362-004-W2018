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

    //printf("playCard PRE: p %d DC %d HC %d DiC %d nA %d\n",
    //          p, pre.handCount[p], pre.deckCount[p], pre.discardCount[p], pre.numActions);

    //printf("playCard POST: p %d DC %d HC %d DiC %d nA %d\n",
    //          p, post->handCount[p], post->deckCount[p], post->discardCount[p], post->numActions);

    assert_safe(r == 0, "playCard returned 0");
    // pre and post handCount equal since village discarded
    assert_safe(pre.handCount[p] == post->handCount[p], "draws a card from the deck");
    // +1 action since 1 action used playing village
    assert_safe(pre.numActions+1 == post->numActions, "gain 2 actions");
    assert_safe(post->hand[p][0] != village, "village discarded");

    return 0;
}

int main(int argc, char** argv) {
    int p;
    struct gameState G;

    printf("randomTest: RUNNING\n");

    SelectStream(0);
    PutSeed(1);

    int n, i;
    int deckCount;
    int handCount;
    int discardCount;

    for (n = 0; n < 10000; n++) {
        for (i = 0; i < sizeof(struct gameState); i++) {
            ((char*)&G)[i] = floor(Random() * 256);
        }

        p = floor(Random() * 2);

        deckCount = floor(Random() * MAX_DECK);
        G.deckCount[p] = deckCount;

        discardCount = floor(Random() * MAX_DECK);
        G.discardCount[p] = discardCount;

        handCount = floor(Random() * MAX_HAND);
        G.handCount[p] = handCount;

        G.playedCardCount = floor(Random() * MAX_HAND);

        G.hand[p][0] = village;

        G.whoseTurn = p;
        G.phase = 0;
        G.numActions = 1;
        checkCardEffect(&G, p);
    }

    printf("randomTest: ENDING\n");
    
    return 0;
}

