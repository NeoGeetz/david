//- something that outputs assembly with an easy dependent function to modify
//- the dependent function has more than one instruction to step through
//- the output prints to terminal for feedback
//- the result of the program cannot be predicted from analysis of the source code alone
#include "engine.h"


int main (int argn,char** args) {
    int  v               ;
    long input[11] = {0} ;
    

    scanfN (8,input) ;
    for (int i = 0;i < 11;i ++) {
        printf ("input[%d] = %ld\n",i,input[i]) ;
    }
    

    
    return 0 ;
}
