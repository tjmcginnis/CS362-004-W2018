/*********************************************************************
 ** Author: Romano Garza
 ** Date: 02/22/17
 ** Description: An automated random tester for smithy
 *********************************************************************/

#include "cardtesthelper.h"
#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "rngs.h"
#include <math.h>
struct countFails
{
    int handCountFail; // number of times handCount has not properly increased
    int deckCountFail; // number of times the deck count has not been updated correctly
    int drawCardFail; // number of times draw card has failed
    int returnFail; // number of times cardEffect Return value failed
    int discardFail;
};

struct countFails ftracker;


// Fills out the hand with at least 1 smithy and other random
// other random cards
int addAtLeast1Smithy(int p, int handCount, struct gameState* G)
{
    int i;
    int smithyPos= -1;
    int card;

    while(inHandCount(p, G->handCount[p], *G, 13) == 0)
    {
        for(i = 0; i < handCount; i++)
        {
            card = floor(Random() * 15);
            G->hand[p][i] = card;
            if(card == 13)
            {
                smithyPos = i;
            }

        }
    }
    return smithyPos;
}


void checkSmithy(int p, struct gameState* G)
{
    // copy state
    struct gameState pG;
    int smithyCount = 0;
    int d, returnVal, handPos;
    int i = 0;
    // add at least one smithy to players hand
    handPos = 0 ; //addAtLeast1Smithy(p, G->handCount[p], G);
    smithyCount = 1;
    // copy state
    G->hand[p][0] = 1;
    memcpy(&pG, G, sizeof(struct gameState));

    // manually draw card for copy
    while(i < 3)
    {
        // draw a card
        d = drawCard(p, &pG);
        // increment return failure if value does not indicate fail
        ftracker.drawCardFail += (d== -1 && pG.deckCount[p]!=0);
        i++;
    }

    // manually check discard
    returnVal = discardCard(handPos, p, &pG, 0);

    if(returnVal !=0)
    {
        ftracker.discardFail++;
    }

    // call cardEffect on game state
    returnVal = cardEffect(13, -1, -1, -1, G, handPos, 0);

    // check return value
    if(returnVal !=0){
        ftracker.returnFail++;
    }

    // check smithy Discarded in both cases is the same
    if(inHandCount(p, G->handCount[p], *G, 13) != inHandCount(p, pG.handCount[p], pG, 13)){
        ftracker.discardFail++;
    }
    // check num of smithy is actually 1 less
    if(inHandCount(p, G->handCount[p], *G, 13) != smithyCount - 1)
    {
        ftracker.discardFail++;
    }

    // check deckCount no diff
    if(G->deckCount[p] != pG.deckCount[p])
    {
        ftracker.deckCountFail++;
    }

    // check handCount no diff
    if(G->handCount[p] != pG.handCount[p])
    {
        ftracker.handCountFail++;
    }

}

int main()
{
    printf("Testing Smithy:\n");
    SelectStream(2);
    PutSeed(3);

    int n, i, p;
    struct gameState G;
    ftracker.deckCountFail = 0;
    ftracker.drawCardFail= 0;
    ftracker.handCountFail =0;
    ftracker.discardFail = 0;
    ftracker.returnFail = 0;

    // init game state with random vals
    for (n = 0; n < 20000; n++) {
        for (i = 0; i < sizeof(struct gameState); i++) {
            ((char*)&G)[i] = floor(Random() * 256);
        }
        p = floor(Random() * MAX_PLAYERS);
        G.whoseTurn = p;
        G.playedCardCount = floor(Random() * (MAX_DECK - 1));
        G.deckCount[p] = floor(Random() * MAX_DECK);
        G.discardCount[p] = floor(Random() * MAX_DECK);
        G.handCount[p] = floor(Random() * (MAX_HAND - 1)) + 1; // insure handCount is never 0
                                                         // smithy cannot be played by a hand that has 0 cards

        checkSmithy(p, &G);
    }

    printf("Smithy return value failed: %d/20000\n", ftracker.returnFail);
    printf("Smithy hand count failed: %d/20000\n", ftracker.handCountFail);
    printf("Smithy deck count failed: %d/2000\n", ftracker.deckCountFail);
    printf("Smithy discard() failed: %d/20000\n", ftracker.discardFail);
    printf("Smithy drawCard() failed: %d/20000\n\n", ftracker.drawCardFail);


    return 0;
}
