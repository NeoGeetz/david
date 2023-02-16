//- something that outputs assembly with an easy dependent function to modify
//- the dependent function has more than one instruction to step through
//- the output prints to terminal for feedback
//- the result of the program cannot be predicted from analysis of the source code alone
#include "engine.h"


int main (int argn,char** args) {
    enum {A=1,B,C,D}         ;
    deltaTable dt            ;
    array11    possibilities ;
    simulation best_result  ;
    
    possibilities.elements[0] = A ;
    possibilities.elements[1] = B ;
    possibilities.elements[2] = C ;
    possibilities.elements[3] = D ;
    
    dt.initial_deltas[A-1] = -5 ;
    dt.initial_deltas[B-1] = -4 ;
    dt.initial_deltas[C-1] = -9 ;
    dt.initial_deltas[D-1] = -6 ;
    
    dt.dependent[A-1][A-1] = 999  ;
    dt.dependent[A-1][B-1] = -4   ;
    dt.dependent[A-1][C-1] = -3   ;
    dt.dependent[A-1][D-1] = -14  ;

    dt.dependent[B-1][A-1] = -7   ;
    dt.dependent[B-1][B-1] = 999  ;
    dt.dependent[B-1][C-1] = -9   ;
    dt.dependent[B-1][D-1] = -2   ;

    dt.dependent[C-1][A-1] = -1   ;
    dt.dependent[C-1][B-1] = -20  ;
    dt.dependent[C-1][C-1] = 999  ;
    dt.dependent[C-1][D-1] = +10  ;
    
    dt.dependent[D-1][A-1] = +5   ;
    dt.dependent[D-1][B-1] = -10  ;
    dt.dependent[D-1][C-1] = -5   ;
    dt.dependent[D-1][D-1] = 999  ;

    printf     ("initial-deltas => ")     ;
    printl_arr (&dt.initial_deltas,4)     ;
    printf     ("dep. characteristics\n") ;
    printl_mat (&dt.dependent    ,4,4   );

    printf     ("-----\n") ;
    printf     ("-----\n") ;
    printf     ("-----\n") ;
    
    best_result =
    bestTemperatureReductionScenario (sz,&dt,possibilities) ;
    
    printf     ("-. the best temperation reduction scenario is ._\n") ;
    printi_arr (&best_result,sz) ;

    return 0 ;
}
