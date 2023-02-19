//- something that outputs assembly with an easy dependent function to modify
//- the dependent function has more than one instruction to step through
//- the output prints to terminal for feedback
//- the result of the program cannot be predicted from analysis of the source code alone
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int* data ;
    int  sz   ;
} array ;

void print     (array a,int x,int y) {
    printf ("[") ;
    for (int i = 0;i < a.sz;i ++) {
        printf ("%-8d ",a.data[i]) ;
    }
    printf ("]\n") ;

    printf ("#") ;
    for (int i = 0;i < a.sz;i ++) {
        if (i == x) printf ("rrrrrrrr ") ;
        else
        if (i == y) printf ("gggggggg ") ;
        else        printf ("#        "          ) ;
    }
    printf ("# #%%#\n") ;
}

void merge (array A,array B,array dst) {
    int Ai = 0 ;
    int Bi = 0 ;

    //  D D D D D D
   for (int dest_i = 0;dest_i < A.sz + B.sz;dest_i ++) {
        if (A.data[Ai] < B.data[Bi]) {
            dst.data[dest_i] = A.data[Ai] ;
            Ai ++                         ;//Bi does not move
        }
        else {
            dst.data[dest_i] = B.data[Bi] ;
            Bi ++                         ;//Ai does not move
        }
        //dest_i ++ either way 

        printf ("--> MERGE\n") ;
        dst.sz = dest_i + 1    ;
        print  (dst,Ai,Bi+ 3)     ;
    }

}

void mergesort_ (array A,array B,array dst) {
}

void mergesort (array src,array dst) {
    array dA,dB ;
    
}

int main (int argn,char** args) {
    int   s[256]  ;
    int   d[256]  ;
    array src,dst ;
    
    src.data = s ;
    dst.data = d ;

    int sz      = 0 ;
    int matches = 1 ;
    
    while (matches == 1 && 0) {
        matches = scanf ("%d",src.data + sz) ;
        if (matches != 1) continue           ;
        sz = sz + 1                          ;
    }
    
    src.sz = sz ;
    dst.sz = sz ;

    //printf ("got  array: ") ;
    //print  (src) ;
    //
    //mergesort (src,dst) ;

    //printf ("sort array: ") ;
    //print  (dst)            ;


    s[0] = 1  ;
    s[1] = 9  ;
    s[2] = 79 ;

    s[3] = 10 ;
    s[4] = 15 ;
    s[5] = 77 ;
    
    //expecting 1 9 10 15 77 79
    array A,B  ;
    A.data = s + 0  ;
    A.sz   = 3      ;
    B.data = s + 3  ;
    B.sz   = 3      ;
    dst.sz = 6      ;
    merge (A,B,dst) ;
    
    printf ("merged 2 sorted lists\n") ;
    print  (dst,0,0) ;





    return 0                ;
}
