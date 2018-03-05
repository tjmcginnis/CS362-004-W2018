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
#include <assert.h>
#include <math.h>
#include <stdlib.h>
#include "rngs.h"

struct countFails
{
    int handCountFail; // number of times handCount has not properly increased
    int deckCountFail; // number of times the deck count has not been updated correctly
    int drawCardFail; // number of times draw card has failed
    int returnFail; // number of times cardEffect Return value failed
    int discardFail;
    int actionFail;
};

struct countFails ftracker;


// Fills out the hand with at least 1 village
// other random cards
int addAtLeast1Village(int p, int handCount, struct gameState* G)
{
    int i;
    int villPos= -1;
    int card;
    while(inHandCount(p, handCount, *G, 14) == 0)
    {
        for(i = 0; i < handCount; i++)
        {
            card = floor(Random() * 16);
            G->hand[p][i] = card;
            if(card == 14)
            {
                villPos = i;
            }

        }
    }
    return villPos;
}


void checkVillage(int p, struct gameState* G)
{
    // copy state
    struct gameState pG;
    int villageCount, d, returnVal, handPos;
    int i = 0;
    // add at least one village to players hand and fill out
    // other cards for the hand count size
    // handPos contains the index value of the village card)
    handPos = addAtLeast1Village(p, G->handCount[p], G);
    // get village count before;
    villageCount = inHandCount(p, G->handCount[p], *G, 14);

    // copy state
    memcpy(&pG, G, sizeof(struct gameState));

    // manually draw card for copy and get the return value
    d = drawCard(p, &pG);
    // increment return failure if value does not indicate fail
    ftracker.drawCardFail += (d== -1 && pG.deckCount[p]!=0);

    // add actions
    pG.numActions += 2;

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

    // check village Discarded in both cases is the same
    if(inHandCount(p, G->handCount[p], *G, 13) != inHandCount(p, pG.handCount[p], pG, 13)){
        ftracker.discardFail++;
    }
    // check num of village is actually 1 less
    if(inHandCount(p, G->handCount[p], *G, 13) != villageCount - 1)
    {
        ftracker.discardFail++;
    }

    // check deckCount no difference
    if(G->deckCount[p] != pG.deckCount[p])
    {
        ftracker.deckCountFail++;
    }

    // check handCount no difference
    if(G->handCount[p] != pG.handCount[p])
    {
        ftracker.handCountFail++;
    }

    if(G->numActions!= 2)
    {
        ftracker.actionFail++;
    }
}

int main()
{
    printf("Testing Village:\n");
    SelectStream(2);
    PutSeed(3);

    int n, i, p;
    struct gameState G;
    ftracker.deckCountFail = 0;
    ftracker.drawCardFail= 0;
    ftracker.handCountFail =0;
    ftracker.discardFail = 0;
    ftracker.returnFail = 0;
    ftracker.actionFail = 0;

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
        G.handCount[p] = floor(Random() * (MAX_HAND - 1) )+ 1; // insure handCount is never 0
        // smithy cannot be played by a hand that has 0 cards

        checkVillage(p, &G);
    }

    printf("Village return value failed: %d/20000\n", ftracker.returnFail);
    printf("Village hand count failed: %d/20000\n", ftracker.handCountFail);
    printf("Village deck count failed: %d/2000\n", ftracker.deckCountFail);
    printf("Village discard() failed: %d/20000\n", ftracker.discardFail);
    printf("Village drawCard() failed: %d/20000\n", ftracker.drawCardFail);
    printf("Village action +2 failed: %d/20000\n\n", ftracker.actionFail);

    return 0;
}
