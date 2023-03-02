#include "tugboat.h"

int main (int argn,char** args) {
    tugboat boats[30]      ;
    int     expected_boats ;
    ocean   osh    = {0}   ;
    range  r ;
    
    osh.distressed     = prompt_coord ("distressed boat loc: ") ;
    osh.harbor         = prompt_coord ("harbor          loc: ") ;
    osh.initial_tboats = boats ;//can assign array variable name to pointer
    
    expected_boats = prompt_int   ("how many tugboats?: ") ;
    
    for (int i = 0;i < expected_boats;i ++) {
        tugboat t ;
        t = prompt_tboat ("tugboat x y name: ",&osh) ;
        addTugBoat (t,boats,osh.total_tugboats,30)   ;
        osh.total_tugboats ++                        ;
    }

    printf ("\n")          ;
    r = ocean_range (&osh) ;
    printf ("ocean range x %d -> %d\n",r.min.x,r.max.x) ;
    printf ("            y %d -> %d\n",r.min.y,r.max.y) ;


    

    
    return 0 ;
}
