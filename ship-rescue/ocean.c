#include "ship.h"


void ocean_init    (ocean* osh)          { osh->the_water = NULL, osh->size = 0 ;}
//it is safe to call ocean_format() twice in a row, because we call the free () function on the "the_water" field before assigning it to new allocated memory (therefore, we are taking care to avoid a "memory leak")
void ocean_format  (ocean* osh,int size) { free (osh->the_water) ; osh->the_water = (char*)malloc (size)  ; osh->size = size ; for (int i = 0;i < size;i ++) osh->the_water[i] = NO_WAKE ; }
void ocean_destroy (ocean* osh)          { free (osh->the_water) ; osh->the_water = NULL ; osh->size = 0  ; }

int  ocean_first_still (ocean* osh) {
    int i ;
    for (i = 0;i < osh->size;i ++) if (osh->the_water[i] == NO_WAKE) return i ;
    return i ; //if i == osh->size, no still spots of water
}

void ocean_add_wake (ocean* osh,int location) {
    //- - - - - - - 
    //add_wake (4) ....
    //^ ^ ^ ^ ^ - -
    for (int i =0;i <= location;i ++) osh->the_water[i] = WAKE ;
}

void ocean_print   (ocean* osh) {
    //assume not less than 0
    printf ("called\n") ;
    if (osh->size < 60) {
        for (int i =0;i < osh->size;i ++)
            printf ("%c ",osh->the_water[i]) ;
        printf ("\n") ;
    }
    else {
        for (int i = 0;i < 28;i++)
            printf ("%c ",osh->the_water[i]) ;
        printf (". . . . ") ;
        for (int i = 0;i < 28;i++) {
            //already know that i will unwrap to 0 .. 27
            //for example, if the size was 198, we would want 170 .. 197
            int tail_start = osh->size - 28               ;
            printf ("%c ",osh->the_water[tail_start + i]) ;
        }

        printf ("\n") ;
    }
}

