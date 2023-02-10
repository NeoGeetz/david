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


//first call ... unwrap_permutation (N,actions,1)
int unwrap_permutation_ (int N,array11 reference,array11 accumulated,int depth) {
    enum {USED=-1} ;

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

    //deepest level, end recursion
    if (depth == N) {
        //[X X X X X 8 X]
        //[X X 3 X X X X]
        for (int i = 0;i < N;i ++) 
            if (reference.elements[i] != USED) 
                accumulated.elements[depth-1] = reference.elements[i] ;
    
        printf ("[") ;
        for (int i = 0;i < depth;i ++) printf ("%-4d ",accumulated.elements[i]) ;
        printf ("]\n") ;
    }
    //continue to deepest 
    else for (int i = 0;i < N;i ++) {
        if (reference.elements[i] != USED) {
            int saved = reference.elements[i]                       ;
            reference.elements[i]         = USED                    ;
            accumulated.elements[depth-1] = saved                   ;//building up our choice
            unwrap_permutation_ (N,reference,accumulated,depth + 1) ;
            reference.elements[i] = saved                           ;
        }
    }
    return 0 ;
}



//A B X Y

//A B X Y
//A B Y X
//....
int unwrap_permutation (int N,array11 set) {
    array11 accumulate ;
    if (N == 0) N = 1  ;//0! is considered to return 1
    return unwrap_permutation_ (N,set,accumulate,1) ;
}

//simulation best_simulation
//int        best_temp_change

simulation bestTemperatureReductionScenario (deltaTable* characteristics,int actionRange) {
    int possibleSimulations = fact (actionRange) ;

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















