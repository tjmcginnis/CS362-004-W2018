/*********************************************************************
 ** Author: Romano Garza
 ** Date: 02/22/17
 ** Description: A unit test for smithyEffect()
 *********************************************************************/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include "cardtesthelper.h"

// emptyDeck
void emptyDeck(int player, struct gameState *state)
{
    int i;
    int deckCount = 0;

    for(i = 0; i < state->deckCount[player]; i++)
    {
        state->discard[player][i] = state->deck[player][i];
        state->discardCount[player]++;
    }

    deckCount = state->deckCount[player];
    for(i = 0; i < deckCount; i++)
    {
        state->deck[player][i] = -1;
        state->deckCount[player]--;
    }

    //testEmptyDeck(player, state, deckCount);
}

// test emptyDeck: unit test for emptyDeck method
void testEmptyDeck(int player, struct gameState *state, int previousCount)
{

    if(state->deckCount[player] == 0)
    {
        printf("emptyDeck(): PASS deck count is 0\n");
    }
    else
    {
        printf("emptyDeck(): FAIL deck count is 0\n");
    }

    if(state->discardCount[player] == previousCount)
    {
        printf("emptyDeck(): PASS discard count is same as previous deck count\n");
    }
    else
    {
        printf("emptyDeck(): FAIL discard count is same as previous deck count\n");
    }

    int j;
    int card;
    printf("testEmptyDeck: HERES THE DISCARD: ");
    for(j = 0; j < state->discardCount[player]; j ++)
    {
        card = state->discard[player][j]; // grab card from hand
        printf("%d " , card);
    }
    printf("\n");
}

int inDeck(int player, struct gameState state, int card)
{
    int j;
    // get cards in players hand
    for(j = 0; j < state.handCount[player]; j++){
        if(state.hand[player][j] == card){
            return 1;
        }
    }
    return 0;
}

int inHandCount(int player, int handCount, struct gameState state, int card)
{
    int j;
    int count=0;
    // get cards in players hand
    for(j = 0; j < handCount; j++){
        if(state.hand[player][j] == card){
            count++;
        }
    }
    return count;
}


int getTreasureyCardCount(int player, int handCount, struct gameState state)
{
    int count = 0;
    int j;
    int card;

    for(j = 0; j < handCount; j ++)
    {
        card = state.hand[player][j]; // grab card from hand
        if(card == 4 || card == 5 || card == 6) // if copper, gold or silver
        {
            count++;
        }
    }
    //testGTCC(player, state);
    return count;
}

void testGTCC(int player, struct gameState state)
{
    int j;
    int card;
    printf("testGTCC: HERES THE HAND: ");
    for(j = 0; j < state.handCount[player]; j ++)
    {
        card = state.hand[player][j]; // grab card from hand
        printf("%d " , card);
    }
    printf("\n");
}

void advC3(int player, struct gameState *state)
{
    // first empty the deck into discard so that
    // it contains treasure cards
    emptyDeck( player, state);
    // next fill deck with non treasure cards
    int i;
    for(i = 0; i<5; i++)
    {
        state->deck[player][i] = 8; // deck is now full of council room cards
    }
}
void advC4(int player, struct gameState *state)
{
    // remove treasure cards
    int i;

    for(i = 0; i<state->deckCount[player]; i++)
    {
        state->deck[player][i] = 8; // deck is now full of council room cards
    }
}
struct gameState myInitGame()
{
    struct gameState G;
    int player1 = 0;
    int j = 0;
    int deckCounter = 0;
    // manually set the suply count for all cards
    G.supplyCount[curse] = 8;

    G.supplyCount[estate] = 20;
    G.supplyCount[duchy] = 20;
    G.supplyCount[province] = 8;

    G.supplyCount[copper] = 50;
    G.supplyCount[silver] = 50;
    G.supplyCount[gold] = 50;

    G.supplyCount[adventurer] = 8;
    G.supplyCount[council_room] = 8;
    G.supplyCount[feast] = 8;
    G.supplyCount[gardens] = 8;
    G.supplyCount[mine] = 8;
    G.supplyCount[remodel] = 8;
    G.supplyCount[smithy] = 8;
    G.supplyCount[village] = 8;
    G.supplyCount[baron] = 8;
    G.supplyCount[great_hall] = 8;
    G.supplyCount[minion] = 8;
    G.supplyCount[steward] = 8;
    G.supplyCount[tribute] = 8;
    G.supplyCount[ambassador] = 8;
    G.supplyCount[cutpurse] = 8;
    G.supplyCount[embargo] = 8;
    G.supplyCount[outpost] = -1;
    G.supplyCount[salvager] = -1;
    G.supplyCount[sea_hag] = -1;
    G.supplyCount[treasure_map] = -1;

    // manually set deck count for player
    G.deckCount[player1] = 0;
    // add cards
    for (j = 0; j < 3; j++)
    {
        G.deck[player1][j] = estate;
        G.deckCount[player1]++;
    }
    for (j = 3; j < 10; j++)
    {
        G.deck[player1][j] = copper;
        G.deckCount[player1]++;

    }
    // shuffle the deck
    if(shuffle(player1, &G))
    {
        printf("shuffle(): FAIL\n");
    }

    // manually set players hand
    G.handCount[player1] = 0;
    G.discardCount[player1] = 0;
    // get cards in players hand
    for(j = 0; j < 5; j++){
        deckCounter = G.deckCount[player1];//Create holder for the deck count
        G.hand[player1][G.handCount[player1]] = G.deck[player1][deckCounter - 1];//Add card to the hand
        G.deckCount[player1]--;
        G.handCount[player1]++;//Increment hand count
    }

    // player1s turn
    G.whoseTurn = 0;
    G.outpostPlayed = 0;
    G.phase = 0;
    G.numActions = 0;
    G.numBuys = 1;
    G.playedCardCount = 0;
    return G;
}
