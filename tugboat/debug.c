#include "tugboat.h"

int  ocean_tb_index (ocean* osh,coord pos) {
    for (int i = 0;i < osh->total_tugboats;i ++) {
        coord tb_pos = osh->initial_tboats[i].start_pos ;
        if (coord_eq (tb_pos,pos)) return i             ;
    }
    return -1 ;
}

range ocean_range   (ocean* osh)                             {
    range r ;
    long min_x =  2000000000 ; //close to MAX_INT
    long max_x = -2000000000 ; //close to MIN_INT
    long min_y =  2000000000 ; //close to MAX_INT
    long max_y = -2000000000 ; //close to MIN_INT
    if (osh->distressed.x < min_x) min_x = osh->distressed.x ;
    if (osh->distressed.x > max_x) max_x = osh->distressed.x ;
    if (osh->distressed.y < min_y) min_y = osh->distressed.y ;
    if (osh->distressed.y > max_y) max_y = osh->distressed.y ;
    if (osh->harbor    .x < min_x) min_x = osh->harbor    .x ;
    if (osh->harbor    .x > max_x) max_x = osh->harbor    .x ;
    if (osh->harbor    .y < min_y) min_y = osh->harbor    .y ;
    if (osh->harbor    .y > max_y) max_y = osh->harbor    .y ;
    
    for (int t = 0;t < osh->total_tugboats;t ++) {
        coord tb_pos = osh->initial_tboats[t].start_pos ;
        if (tb_pos.x < min_x) min_x = tb_pos    .x      ;
        if (tb_pos.x > max_x) max_x = tb_pos    .x      ;
        if (tb_pos.y < min_y) min_y = tb_pos    .y      ;
        if (tb_pos.y > max_y) max_y = tb_pos    .y      ;
    }
    //little trick to give some head-space for our ocean
    min_x = min_x - 2 ;
    max_x = max_x + 2 ;
    min_y = min_y - 2 ;
    max_y = max_y + 2 ;
    r.min.x = min_x ;
    r.min.y = min_y ;
    r.max.x = max_x ;
    r.max.y = max_y ;

    return r ;
}
void ocean_print (ocean* osh,tugboat* order,int step) {
    range r = ocean_range (osh) ;
    coord it                    ;
    //use ! for ship, use @ for harbor
    //for tugboats, use first letter of name
    //if a tugboat was chosen to add to the order, "remove" it from the ocean by putting
    //a  "*" where it's name letter used to be
    //~~~~~~~~~~~~~~~~
    //~Q~~~~~~~~~~@~~~
    //~~~~~~m~~~~~~~~~
    //~~~~~~~~~~~~a~~~
    //~~~~~~~~~~n~~~~~
    //~~~!~~~~~~~~~~~~
    //~~~~~~~~z~~~~~~~
    //~~~~~~~~~~~~~~~~
    //_

    //~~~~~~~~~~~~~~~~
    //~Q~~~~~~~~~~@~~~
    //~~~~~~m~~~~~~~~~
    //~~~~~~~~~~~~a~~~
    //~~~~~~~~~~n~~~~~
    //~~~!~~~~~~~~~~~~
    //~~~~~~~~*~~~~~~~
    //~~~~~~~~~~~~~~~~
    //z

    //~~~~~~~~~~~~~~~~
    //~Q~~~~~~~~~~@~~~
    //~~~~~~m~~~~~~~~~
    //~~~~~~~~~~~~a~~~
    //~~~~~~~~~~*~~~~~
    //~~~!~~~~~~~~~~~~
    //~~~~~~~~*~~~~~~~
    //~~~~~~~~~~~~~~~~
    //z -> n
    
    for (it.y = r.min.y;it.y <= r.max.y;it.y ++) {
        for (it.x = r.min.x;it.x <= r.max.x;it.x ++) {
            if      (coord_eq (osh->distressed,it)) { printf ("!") ; }
            else if (coord_eq (osh->harbor    ,it)) { printf ("@") ; }
            else {
                int tb_addr = ocean_tb_index (osh,it) ;
                if (tb_addr >= 0) {
                    char tname0         = osh->initial_tboats[tb_addr].name.mem[0]       ;
                    int  chosen         = osh->initial_tboats[tb_addr].chosen            ;
                    if (step >= 0) {
                        int  chosen_of_step = chooseTugboat (order,osh->total_tugboats,step) ;
                        if (tb_addr > chosen_of_step) printf ("%c",tname0) ; //could not be picked yet
                        else                          {
                            if (!chosen)  printf ("%c",tname0) ;
                            else          printf ("*"        ) ; //tugboat chosen and we are on that step
                        }
                    }
                    else printf ("%c",tname0) ;
                }
                else  printf ("~"         ) ;

            }
        }
        printf ("\n") ;
    }
    
    for (int i = 0;i < step;i ++) {
        int chosen_of_step = chooseTugboat (order,osh->total_tugboats,i) ;
        printf ("%s",order[i].name.mem)    ;
        if (i != step - 1) printf (" -> ") ;
    }
    if (step < 1) printf ("_") ;
    printf ("\n")              ;
    printf ("#%%+%%#\n") ;
}
