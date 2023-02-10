//- something that outputs assembly with an easy dependent function to modify
//- the dependent function has more than one instruction to step through
//- the output prints to terminal for feedback
//- the result of the program cannot be predicted from analysis of the source code alone
#include "engine.h"


int main (int argn,char** args) {
    int     v   ;
    array11 set ;
    
    set.elements[0] = 1 ;
    set.elements[1] = 2 ;
    set.elements[2] = 3 ;

    unwrap_permutation (3,set) ;

    
    return 0 ;
}
