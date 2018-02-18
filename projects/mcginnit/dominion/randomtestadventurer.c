#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <math.h>
#include "rngs.h"
#include "dominion.h"


int assert_safe(int a, int b, char* message) {
    if (a != b) {
        printf("Failing: %s\n", message);
    }
    return 0;
}


int checkCardEffect(struct gameState* post, int p) {
    struct gameState pre;
    memcpy(&pre, post, sizeof(struct gameState));

    int i;
    int card;
    int preHandTreasureCount = 0;
    int postHandTreasureCount = 0;

    int r = playCard(0, -1, -1, -1, post);

    for (i = 0; i < pre.handCount[p]; i++) {
        card = pre.hand[p][i]; 
        if (card == copper || card == silver || card == gold) {
            preHandTreasureCount++;
        }
    }

    for (i = 0; i < post->handCount[p]; i++) {
        card = post->hand[p][i]; 
        if (card == copper || card == silver || card == gold) {
            postHandTreasureCount++;
        }
    }

    //printf("playCard PRE: p %d HC %d DiC %d nA %d hT %d\n",
    //          p, pre.handCount[p], pre.discardCount[p], pre.numActions, preHandTreasureCount);

    //printf("playCard POST: p %d HC %d DiC %d nA %d ht %d\n",
    //          p, post->handCount[p], post->discardCount[p], post->numActions, postHandTreasureCount);


    assert_safe(r, 0, "playCard returned 0");
    assert_safe(postHandTreasureCount, preHandTreasureCount + 2, "two treasure cards added to the hand");

    return 0;
}

int main(int argc, char** argv) {
    int p;
    struct gameState G;

    printf("randomTestAdventurer: RUNNING\n");

    SelectStream(0);
    PutSeed(1);

    int n, i, j, pos;
    int deckCount;
    int handCount;
    int discardCount;
    int numTreasureDeck;
    int numTreasureHand;
    int numTreasureDiscard;

    for (n = 0; n < 10000; n++) {
        for (i = 0; i < sizeof(struct gameState); i++) {
            ((char*)&G)[i] = floor(Random() * 256);
        }

        p = floor(Random() * 2);

        deckCount = floor(Random() * MAX_DECK);
        G.deckCount[p] = deckCount;

        // put a random number of treasure cards in the deck
        numTreasureDeck = floor(Random() * deckCount);
        for (j = 0; j < numTreasureDeck; j++) {
            pos = floor(Random() * deckCount);
            G.deck[p][pos] = copper;  
        }

        discardCount = floor(Random() * MAX_DECK);
        G.discardCount[p] = discardCount;

        // put a random number of treasure cards in the discard pile
        numTreasureDiscard = floor(Random() * discardCount);
        for (j = 0; j < numTreasureDiscard; j++) {
            pos = floor(Random() * discardCount);
            G.discard[p][pos] = copper;
        }

        handCount = floor(Random() * MAX_HAND);
        G.handCount[p] = handCount;

        // put adventurer in player's hand as first card
        G.hand[p][0] = adventurer;

        // put a random number of treasure cards in the hand
        // note, this is a work around for bug introduced in wk2
        // otherwise, adventurerCard will produce a segmentation
        // fault
        // comment the below 10 lines out to produce bug
        numTreasureHand = floor(Random() * handCount);

        if (numTreasureHand < 3) {
            numTreasureHand = 3;
        }

        for (j = 2; j < numTreasureHand; j++) {
            pos = floor(Random() * handCount);
            G.hand[p][pos] = copper;
        }
        // comment the above 10 lines out to produce bug

        G.whoseTurn = p;
        G.phase = 0;
        G.numActions = 1;
        checkCardEffect(&G, p);
    }

    printf("randomTestAdventurer: ENDING\n");
    
    return 0;
}

