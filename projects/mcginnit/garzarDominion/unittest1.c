/*********************************************************************
 ** Author: Romano Garza
 ** Date: 02/22/17
 ** Description: A unit test for isGameOver
 *********************************************************************/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"



int main () {


    int k[10] = {adventurer, council_room, feast, gardens, mine,
	       remodel, smithy, village, baron, great_hall};

    struct gameState G;

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
    G.supplyCount[minion] = -1;
    G.supplyCount[steward] = -1;
    G.supplyCount[tribute] = -1;
    G.supplyCount[ambassador] = -1;
    G.supplyCount[cutpurse] = -1;
    G.supplyCount[embargo] = -1;
    G.supplyCount[outpost] = -1;
    G.supplyCount[salvager] = -1;
    G.supplyCount[sea_hag] = -1;
    G.supplyCount[treasure_map] = -1;


    /* These tests involve the supply count of Province
        3 conditions are tested province >0, =0, province <0
     */
    if(isGameOver(&G)==0)
    {
        printf("isGameOver(): PASS when stack of Province cards is not empty\n");
    }
    else
    {
        printf("isGameOver(): FAIL when stack of Provice cards is not empty\n");
    }

    G.supplyCount[province] = 0;
    if(isGameOver(&G))
    {
        printf("isGameOver(): PASS when stack of Province cards is empty\n");
    }
    else
    {
        printf("isGameOver(): FAIL when stack of Provice cards is empty\n");
    }

    G.supplyCount[province] = -1;
    if(isGameOver(&G))
    {
        printf("isGameOver(): PASS when stack of Province cards is negative\n\n");
    }
    else
    {
        printf("isGameOver(): FAIL when stack of Provice cards is negative\n\n");
    }


    G.supplyCount[province] = 10;
    G.supplyCount[adventurer] = 0;
    if(!isGameOver(&G))
    {
        printf("isGameOver(): PASS when 1 stack of kingdom cards is empty\n");
    }
    else
    {
        printf("isGameOver(): PASS when 1 stack of kingdom cards is empty\n");
    }

    G.supplyCount[council_room] = 0;
    if(isGameOver(&G)==0)
    {
        printf("isGameOver(): PASS when 2 stacks of kingdom cards are empty\n");
    }
    else
    {
        printf("isGameOver(): PASS when 2 stacks of kingdom cards are empty\n");
    }

    G.supplyCount[feast] = 0;
    if(isGameOver(&G))
    {
        printf("isGameOver(): PASS when 3 stacks of kingdom cards are empty\n\n");
    }
    else
    {
        printf("isGameOver(): FAIL when 3 stacks of kingdom cards are empty\n\n");
    }


    G.supplyCount[adventurer] = 10;
    G.supplyCount[council_room] = 10;
    G.supplyCount[feast] = 10;

    G.supplyCount[salvager] = 0;
    if(!isGameOver(&G))
    {
        printf("isGameOver(): PASS when 1 stack of Non-Play cards at edge is empty\n");
    }
    else
    {
        printf("isGameOver(): PASS when 1 stack of Non-Play cards at edge is empty\n");
    }

    G.supplyCount[sea_hag] = 0;
    if(!isGameOver(&G))
    {
        printf("isGameOver(): PASS when 2 stacks of Non-Play cards at edge are empty\n");
    }
    else
    {
        printf("isGameOver(): PASS when 2 stacks of Non-Play cards at edge are empty\n");
    }

    G.supplyCount[treasure_map] = 0;
    if(isGameOver(&G))
    {
        printf("isGameOver(): PASS when 3 stacks of Non-Play cards at edge are empty\n\n");
    }
    else
    {
        printf("isGameOver(): FAIL when 3 stacks of Non-Play cards at edge are empty\n\n");
    }


    return 0;
}
