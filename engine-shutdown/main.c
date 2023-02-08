//- something that outputs assembly with an easy dependent function to modify
//- the dependent function has more than one instruction to step through
//- the output prints to terminal for feedback
//- the result of the program cannot be predicted from analysis of the source code alone
#include <stdio.h>
#include <stdlib.h>

int transform (int a,int b) {
    return a + b * 2 ;
}

int main (int argn,char** args) {
    int v ;
    v = (argn > 1) ? atol (args[1]) : 0 ;
    
    v = transform (v,v) ;
    
    printf ("-- test %d --\n",v) ;
    return 0                     ;
}
