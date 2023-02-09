#include "engine.h"


//two ways of doing this,
//    -the memory expensive way that is probably easier to implement (caches simulation results)
//     simulation possibilities[11*10*9*8*7*6*5*4*3*2*1] (would take up at LEAST 152MB)
//     could still get away with it if all we cared about was finishing the assignment fast
//    -the memory cheap  way, that re-simulates the possibility using a permutation code
//     a little more to keep track of
//     identify each possibility starting from 0, 1, 2, ... -> 11!


//say 3 options

int fact (int N) {
    int product = 1 ;
    while (N > 1) {
        product = product * N ;
        N --                  ;
    }
    return product ;
}


//gives us end result of ONE simulation
long try_ (simulation event,deltaTable* characteristics,int actionRange) {
    long deltaSum = 0 ;
    int  lastAction   ;

    //N = 4
    //event.actions[] => 2 0 1 3

    //event.actions[] => *0 3  1  2
    //event.actions[] => 0  *3 1  2
    //event.actions[] => 0  3  *1 2
    //event.actions[] => 0  3  1  *2

    //event.actions[] => *FOAM LEMON  AIR  DISCONN
    //event.actions[] => FOAM  *LEMON AIR  DISCONN
    //event.actions[] => FOAM  LEMON  *AIR DISCONN
    //event.actions[] => FOAM  LEMON  AIR  *DISCONN

    deltaSum   = characteristics->initial_deltas[event.actions[0]] ;
    lastAction = event.actions[0]                                  ;
    for (int i = 1;i < actionRange;i ++) {
        lastAction = event.actions[i-1]                                                  ;
        deltaSum   = deltaSum + characteristics->dependent[event.actions[i]][lastAction] ;
    }
    
    return deltaSum ;//want negative, could be positive (end result raise temperature)
}

//probably needs more parameters, at least 1
//buffer with marking out used will probably help
int unwrap_permutation (int N) {
    //0 1 2
    // 0 2...

    // //
    // //[0 1 2]

    // //[X 1 2]
    //     //[X 1 2]

    //     //[X X 2]
    //         //[* * *]
    //         ^^^
    //     ---
    //     //[X 1 X]
    //         //[* * *]
    //         ^^^
    //     ---
    //     ^^^
    // ---

    // //[0 X 2]
    //     //[0 X 2]

    //     //[X X 2]
    //         //[* * *]
    //         ^^^
    //     ---
    //     //[0 X X]
    //         //[* * *]
    //         ^^^
    //     ---
    //     ^^^
    // ---
    // 
    // ...
    
    //unwrap_perm
}

simulation bestTemperatureReductionScenario (deltaTable* characteristics,int actionRange) {
    int possibleSimulations = fact (actionRange) ;

    // //
    // //[0 1 2]

    // //[X 1 2]
    //     //[X 1 2]

    //     //[X X 2]
    //         //[* * *]
    //         ^^^
    //     ---
    //     //[X 1 X]
    //         //[* * *]
    //         ^^^
    //     ---
    //     ^^^
    // ---

    // //[0 X 2]
    //     //[0 X 2]

    //     //[X X 2]
    //         //[* * *]
    //         ^^^
    //     ---
    //     //[0 X X]
    //         //[* * *]
    //         ^^^
    //     ---
    //     ^^^
    // ---
    // 
    // ...


    //example of 3 possible actions
    //[0] [1] [2]
    //[0] [2] [1]
    //[1] [0] [2]
    //[1] [2] [0]
    //[2] [0] [1]
    //[2] [1] [0]

    //[0] [1] [2]
    //[1] [0] [2]
    //[2] [0] [1]
    //[0] [2] [1]
    //[1] [2] [0]
    //[2] [1] [0]

}















