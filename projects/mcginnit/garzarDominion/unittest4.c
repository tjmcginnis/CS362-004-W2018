/*********************************************************************
 ** Author: Romano Garza
 ** Date: 02/22/17
 ** Description: A unit test for getCost()
 *********************************************************************/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

int main () {

    // curse cost = 0
    if(getCost(0) == 0)
    {
        printf("getCost(): PASS when passed curse\n");
    }
    else
    {
        printf("getCost(): FAIL when passed curse\n");
    }
    // estate cost = 2
    if(getCost(1) == 2)
    {
        printf("getCost(): PASS when passed estate\n");
    }
    else
    {
        printf("getCost(): FAIL when passed estate\n");
    }

    // duchy cost = 5
    if(getCost(2) == 5)
    {
        printf("getCost(): PASS when passed duchy\n");
    }
    else
    {
        printf("getCost(): FAIL when passed duchy\n");
    }

    // province cost = 8
    if(getCost(3) == 8)
    {
        printf("getCost(): PASS when passed province\n");
    }
    else
    {
        printf("getCost(): FAIL when passed province\n");
    }


    // copper cost = 0
    if(getCost(4) == 0)
    {
        printf("getCost(): PASS when passed copper\n");
    }
    else
    {
        printf("getCost(): FAIL when passed copper\n");
    }

    // silver cost = 3
    if(getCost(5) == 3)
    {
        printf("getCost(): PASS when passed silver\n");
    }
    else
    {
        printf("getCost(): FAIL when passed silver\n");
    }

    // gold cost = 6
    if(getCost(6) == 6)
    {
        printf("getCost(): PASS when passed gold\n");
    }
    else
    {
        printf("getCost(): FAIL when passed gold\n");
    }

    // adventurer cost = 6
    if(getCost(7) == 6)
    {
        printf("getCost(): PASS when passed adventurer\n");
    }
    else
    {
        printf("getCost(): FAIL when passed adventurer\n");
    }

    // council_room cost = 5
    if(getCost(8) == 5)
    {
        printf("getCost(): PASS when passed council_room\n");
    }
    else
    {
        printf("getCost(): FAIL when passed council_room\n");
    }

    // feast cost = 4
    if(getCost(9) == 4)
    {
        printf("getCost(): PASS when passed feast\n");
    }
    else
    {
        printf("getCost(): FAIL when passed feast\n");
    }

    // gardens cost = 4
    if(getCost(10) == 4)
    {
        printf("getCost(): PASS when passed gardens\n");
    }
    else
    {
        printf("getCost(): FAIL when passed gardens\n");
    }

    // mine cost = 5
    if(getCost(11) == 5)
    {
        printf("getCost(): PASS when passed mine\n");
    }
    else
    {
        printf("getCost(): FAIL when passed mine\n");
    }

    // remodel cost = 4
    if(getCost(12) == 4)
    {
        printf("getCost(): PASS when passed remodel\n");
    }
    else
    {
        printf("getCost(): FAIL when passed remodel\n");
    }

    // smithy cost = 4
    if(getCost(13) == 4)
    {
        printf("getCost(): PASS when passed smithy\n");
    }
    else
    {
        printf("getCost(): FAIL when passed smithy\n");
    }

    // village cost = 3
    if(getCost(14) == 3)
    {
        printf("getCost(): PASS when passed village\n");
    }
    else
    {
        printf("getCost(): FAIL when passed village\n");
    }

    // baron cost = 4
    if(getCost(15) == 4)
    {
        printf("getCost(): PASS when passed baron\n");
    }
    else
    {
        printf("getCost(): FAIL when passed baron\n");
    }

    // great hall cost = 3
    if(getCost(16) == 3)
    {
        printf("getCost(): PASS when passed great_hall\n");
    }
    else
    {
        printf("getCost(): FAIL when passed great_hall\n");
    }

    // minion cost = 5
    if(getCost(17) == 5)
    {
        printf("getCost(): PASS when passed minion\n");
    }
    else
    {
        printf("getCost(): FAIL when passed minion\n");
    }

    // steward cost = 3
    if(getCost(18) == 3)
    {
        printf("getCost(): PASS when passed steward\n");
    }
    else
    {
        printf("getCost(): FAIL when passed steward\n");
    }

    // tribute cost = 5
    if(getCost(19) == 5)
    {
        printf("getCost(): PASS when passed tribute\n");
    }
    else
    {
        printf("getCost(): FAIL when passed tributen");
    }

    // ambassador cost = 3
    if(getCost(20) == 3)
    {
        printf("getCost(): PASS when passed ambassador\n");
    }
    else
    {
        printf("getCost(): FAIL when passed ambassador\n");
    }

    // cutpurse cost = 4
    if(getCost(21) == 4)
    {
        printf("getCost(): PASS when passed cutpurse\n");
    }
    else
    {
        printf("getCost(): FAIL when passed cutpurse\n");
    }

    // embargo cost = 2
    if(getCost(22) == 2)
    {
        printf("getCost(): PASS when passed embargo\n");
    }
    else
    {
        printf("getCost(): FAIL when passed embargo\n");
    }

    // outpost cost = 5
    if(getCost(23) == 5)
    {
        printf("getCost(): PASS when passed outpost\n");
    }
    else
    {
        printf("getCost(): FAIL when passed outpost\n");
    }

    // salvager cost = 4
    if(getCost(24) == 4)
    {
        printf("getCost(): PASS when passed salvager\n");
    }
    else
    {
        printf("getCost(): FAIL when passed salvager\n");
    }

    // sea hag cost = 4
    if(getCost(25) == 4)
    {
        printf("getCost(): PASS when passed sea_hag\n");
    }
    else
    {
        printf("getCost(): FAIL when passed sea_hag\n");
    }

    // treasure map cost = 4
    if(getCost(26) == 4)
    {
        printf("getCost(): PASS when passed treasure_map\n");
    }
    else
    {
        printf("getCost(): FAIL when passed treasure_map\n");
    }
    // treasure map cost = 4
    if(getCost(28) == -1)
    {
        printf("getCost(): PASS when passed out of index vaue\n");
    }
    else
    {
        printf("getCost(): FAIL when passed out of index value\n");
    }
    return 0;
}
