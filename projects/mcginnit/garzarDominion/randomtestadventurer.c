/*********************************************************************
 ** Author: Romano Garza
 ** Date: 02/22/17
 ** Description: An automated random tester for adventurer
 *********************************************************************/

#include "cardtesthelper.h"
#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <math.h>
#include "rngs.h"

struct countFails
{
    int returnFail; // num of times cardEffect Return value failed
    int handCountFail; // num of times hand count was not increased by 2
    int drawTreasuresFail; // num of times hand was not increased by 2 treasure cards
    int drawCardFail;
    int shuffleFail;
};

struct countFails ftracker;

void randomlyInitHand(int p, struct gameState* G, struct gameState* pG)
{
    int i, card;
    int handCount = G->handCount[p];
    for(i = 0; i < handCount; i++)
    {
        card = floor(Random() * 14);
        G->hand[p][i] = card;
    }
}
// This function randomly initializes the deck and discard pile
// with cards (the, discard pile always contains at least
// enough treasure cards
void randomlyInitDeckDiscard(int player, struct gameState* G, struct gameState* pG)
{
    // store the deck count and discard counts
    int deckCount = G->deckCount[player];
    int discCount = G->discardCount[player];
    // init added values to 0
    int addedToDeck = 0;
    int addedToDisc = 0;
    // grab a random card to fill the players deck with
    int randomCard = floor(Random()*10);
    while(addedToDeck < deckCount)
    {
        // add to deck
        G->deck[player][addedToDeck] = randomCard;
        pG->deck[player][addedToDeck] = G->deck[player][addedToDeck];
        // get another random card
        addedToDeck++;
        randomCard = floor(Random()*3);
    }

    // do the same for the players discard pile
    while(addedToDisc < discCount)
    {
        G->discard[player][addedToDisc] = randomCard;
        pG->discard[player][addedToDisc] = G->discard[player][addedToDisc];
        randomCard = floor(Random()*3);
        addedToDisc++;
    }

}

void checkAdv(int p, struct gameState* G, struct gameState pG)
{
    int returnVal, oldTCC, newTCC;

    oldTCC = getTreasureyCardCount(p, pG.handCount[p], pG);
    G->hand[p][0] = 7;
    printf("Starting call to cardEffect!\n", oldTCC);
    returnVal = cardEffect(7, -1, -1, -1, G, -1, 0);
    printf("Finished \n");
    // if error, increment return fail
    if(returnVal == -1)
    {
        ftracker.returnFail++;
    }

    // check no differences in final handCount values
    if(G->handCount[p] != pG.handCount[p] + 2)
    {
        ftracker.handCountFail++;
    }

    // check that treasure was properly drawn
    newTCC = getTreasureyCardCount(p, G->handCount[p], *G);
    if(oldTCC + 2 != newTCC)
    {
        ftracker.drawTreasuresFail++;
    }
    printf("end\n\n");

}

int main()
{
    printf("Testing Adventurer:\n");
    SelectStream(2);
    PutSeed(3);

    int n, i, p, randomCard, deckCount, discCount;
    int addedToDeck = 0;
    int addedToDisc = 0;
    struct gameState G;
    struct gameState pG;
    ftracker.returnFail = 0;
    ftracker.handCountFail =0;
    ftracker.drawTreasuresFail = 0;
    ftracker.drawCardFail = 0;
    ftracker.shuffleFail = 0;

    for (n = 0; n < 20000; n++) {
        for (i = 0; i < sizeof(struct gameState); i++) {
            ((char*)&G)[i] = floor(Random() * 256);
        }
        memcpy(&pG, &G, sizeof(struct gameState));
        p = floor(Random() * MAX_PLAYERS);
        //printf("%d ", p);
        G.whoseTurn = p;
        pG.whoseTurn = p;
        G.playedCardCount = floor(Random() * (MAX_DECK - 1)) + 1;
        pG.playedCardCount = G.playedCardCount;

        G.deckCount[p] = floor(Random() * (MAX_DECK - 1)) + 1;
        pG.deckCount[p] = G.deckCount[p];
        deckCount = G.deckCount[p];

        G.discardCount[p] = floor(Random() * (MAX_DECK - 1))+1; // insure both discard and deck are never empty
        pG.discardCount[p] = G.discardCount[p];
        discCount = pG.discardCount[p];

        G.handCount[p] = floor(Random() * (MAX_HAND - 1)) + 1; // insure handCount is never 1
        pG.handCount[p] = G.handCount[p];

        addedToDeck = 0;
        addedToDisc = 0;
        randomCard = floor(Random()*2);
        while(addedToDeck < deckCount)
        {
            // add to deck
            G.deck[p][addedToDeck] = randomCard;
            pG.deck[p][addedToDeck] = G.deck[p][addedToDeck];
            // get another random card
            addedToDeck++;
            randomCard = 1;
        }

        printf("deckCount = %d\n", deckCount);
        printf("discCount = %d\n", discCount);
        // do the same for the players discard pile
        while(addedToDisc < discCount)
        {
            G.discard[p][addedToDisc] = randomCard;
            pG.discard[p][addedToDisc] = G.discard[p][addedToDisc];
            randomCard = 1;
            addedToDisc++;
        }

        randomlyInitHand(p, &pG, &G);
        checkAdv(p, &G, pG);
    }

    printf("Adventurer return value failed: %d/20000\n", ftracker.returnFail);
    printf("Adventurer hand count failed: %d/20000\n", ftracker.handCountFail);
    printf("Adventurer draw treasures failed: %d/2000\n", ftracker.drawTreasuresFail);
    printf("Adventurer draw card failed: %d/2000\n", ftracker.drawCardFail);
    printf("Adventurer shuffle failed: %d/2000\n", ftracker.shuffleFail);

    return 0;
}
