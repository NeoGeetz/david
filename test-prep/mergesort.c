//- something that outputs assembly with an easy dependent function to modify
//- the dependent function has more than one instruction to step through
//- the output prints to terminal for feedback
//- the result of the program cannot be predicted from analysis of the source code alone
#include <stdio.h>
#include <stdlib.h>

void print     (int* a,int sz) {
    printf ("[") ;
    for (int i = 0;i < sz;i ++) {
        printf ("%d ",a[i]) ;
    }
    printf ("]\n") ;
}

void mergesort (int* a,int sz) {

}

int main (int argn,char** args) {
    int arr[256]    ;
    int sz      = 0 ;
    int end     = 0 ;
    int matches = 1 ;
    
    while (matches == 1) {
        matches = scanf ("%d",arr + sz) ;
        if (matches != 1) continue      ;
        sz = sz + 1                     ;
    }

    printf ("got  array: ") ;
    print  (arr,sz)        ;
    
    mergesort (arr,sz) ;

    printf ("sort array: ") ;
    print  (arr,sz        ) ;
    return 0                ;
}
