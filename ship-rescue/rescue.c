#include "ship.h"

//- - - - - - - - - - - - - - -
//^ ^ ^ ^ ^ - - - - - - - - - -


void  adjust_information (ocean* osh,int ship_speed,response resp) {
    if (resp.value == WAKE) ocean_add_wake (osh,resp.location) ;//will modify current known state of the ocean
}

action work (ocean* osh,int ship_speed,response resp) {
    action axn                                      ;
    int    first_still    = ocean_first_still (osh) ;
    int    sub_ocean_size = osh->size - first_still ;
    
    switch (resp.value) {
        case RESCUE_START:
        case WAKE        :
            axn.mode     = QUERY                           ;
            axn.location = sub_ocean_size /2 + first_still ;
        break ;
        case NO_WAKE     ://considering this as temporary information
            //^ ^ ^ ^ ^ ^ ^ ^ - - - - - - - - - - - - - - (0..21, size == 22, subsz == 14)
            //^ ^ ^ ^ ^ ^ ^ ^ - - - - - - - - - - - - - -
            //^ ^ ^ ^ ^ ^ ^ ^ - - - - - - - - - - - ~ ~ ~
            sub_ocean_size = sub_ocean_size - (osh->size - resp.location) ;
        
            axn.mode       = QUERY                           ;
            axn.location   = sub_ocean_size /2 + first_still ;
        break ;
        case BOAT        :
            axn.mode     = SEND_BOAT     ;
            axn.location = resp.location ;
        break ;
        default: 
            printf ("ERROR: unexpected response code %d\n",resp.value) ;
            exit   (1)                                                 ;//whole program stops, returns error
    }

    
    return axn ;
}
