#include "tugboat.h"


int cstring_cmp (cstring a,cstring b) {
    return strcmp (a.mem,b.mem) ;
}

//function not safe, but just want to get stuff done
cstring cstring_ (const char*   cstr ) {
    cstring result ;
    int     i      ;
    for (i = 0;cstr[i] != 0;i ++) {
        result.mem[i] = cstr[i] ;
    }
    result.mem[i] = 0 ;
    return result     ;
}


int coord_eq (coord a,coord b) { return a.x == b.x && a.y == b.y ; }

long vec2_magSq (vec2 v) {
    long magSq = v.x * v.x + v.y * v.y ;
    return magSq                       ;
}

void tugboat_compute (tugboat* dest,ocean* osh) {
    vec2 route_v   ;//offset vector describing how to get to ship to harbor
    vec2 tugboat_v ;//offset vector describing how to get to ship to tugboat
    long dot_prod  ;

    route_v.x   = osh->harbor.x          - osh->distressed.x ; //offset, meaning how to get to harbor from ship in x-units
    route_v.y   = osh->harbor.y          - osh->distressed.y ; //offset, meaning how to get to harbor from ship in x-units
    tugboat_v.x = dest->start_pos.x - osh->distressed.x ;
    tugboat_v.y = dest->start_pos.y - osh->distressed.y ; //offset of tugboat relative to distressed ship
    
    //       ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~
    //   ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ + H ~ ~ ~ ~ ~ ~
    //   ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ + + ~ ~ ~ ~ ~ ~ ~ ~
    // ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ + + ~ ~ ~ ~ ~ ~ ~ ~ ~ ~
    // ~ ~ ~ ~ ~ ~ ~ ~ ~ + + ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~
    // ~ ~ ~ ~ ~ ~ ~ S + * * * * T ~ ~ ~ ~ ~ ~ ~ ~ ~
    // ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~
    // ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~  
    // ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~        
    // ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~          
    
    //dot product ? just do it
    dot_prod = route_v.x * tugboat_v.x + route_v.y * tugboat_v.y ;
    //they told us, dot_prod = (mag (route_v) * mag (tugboat_v)) * cos (ANGLE)
    //they told us, dot_prod = (mag (route_v) * mag (tugboat_v)) * (mag (tugboat_v) / mag (proj_v))      
    
    //mag (proj_v) * dot_prod = mag (route_v) * mag   (tugboat_v) * mag (tugboat_v)
    //mag (proj_v) * dot_prod = mag (route_v) * magSq (tugboat_v)
    //mag (proj_v) = mag (route_v) * magSq (tugboat_v) /dot_prod
    //mag (proj_v) * mag (route_v) = mag   (route_v) * mag (route_v) * magSq (tugboat_v) /dot_prod
    //mag (proj_v) * mag (route_v) = magSq (route_v) * magSq (tugboat_v) /dot_prod

    //mag (proj_v) * mag (route_v) = magSq (route_v) * magSq (tugboat_v) /dot_prod
    //               XXXXXXXXXXXXX 

    //mag (proj_v) * mag (route_v) * 1000000 = 1000000 * magSq (route_v) * magSq (tugboat_v) /dot_prod
    //               XXXXXXXXXXXXX 
    
    
    dest->routeposdist_by_harbordist1000000 = 1000000 * vec2_magSq (route_v) * vec2_magSq (tugboat_v) /dot_prod ;
    dest->dist_to_boatSq                    = vec2_magSq (tugboat_v) ;
}

tugboat tugboat_ (coord pos,cstring name,ocean* osh) {
    tugboat t ;
    t.chosen    = 1          ;//start all as chosen, so we "prune" out the ones that don't go
    t.name      = name       ;
    t.start_pos = pos        ;
    tugboat_compute (&t,osh) ;
}


void addTugBoat (tugboat newBoat,tugboat* boats,int size,int limit) {
    if (size == limit) exit (1) ; //abort program, otherwise buffer overrun
    //imagine we already have a sorted list
    //1 4 6 8 9 12 35 68 99
    //1 4 6 8 9 12 35 68 99 *

    //1 4 6 8 9 12 35 68 68 99
    //1 4 6 8 9 12 35 XX 68 99
    //0 1 2 3 4 5  6  7  8  9
    
    //add in 33
    //what do we do first ? => find where new addition belongs
    int i ;
    for (i = 0;i < size;i ++) {
        //actual sort criteria decided in here
        if (newBoat.routeposdist_by_harbordist1000000 < boats[i].routeposdist_by_harbordist1000000) {
            //would have to have a smaller projection => closer on route to the boat
            break ;
        }
        else if (newBoat.routeposdist_by_harbordist1000000 == boats[i].routeposdist_by_harbordist1000000) {
            //tie, use next criteria to break it
            //same dist along the route, but, one tugboat is closer to the route 
            //than the other (can use their distances to the original boat to prove this)
            if (newBoat.dist_to_boatSq < boats[i].dist_to_boatSq) {
                break ;
            }
            else if (newBoat.dist_to_boatSq == boats[i].dist_to_boatSq) {
                //wow ! still a tie !
                //last criteria, just choose the one with the
                //alphabetically sooner name
                int cmpr = cstring_cmp (newBoat.name,boats[i].name) ;
                if (cmpr < 0) {//newBoat .name is lexicographically earlier
                    break ;
                }
                //else, they're the exact same boat ? or maybe same named
                //boats, but can just place it after in the list without
                //issue
            }
        }
    }
    //doing the actual insert, shift top remaining elements up, and
    //shove new entry into the "middle" somewhere

    //i == size if we never broke early
    for (int r = size;r > i;r --) {
        //insert 33 at pos-6

        //0 1 2 3 4 5  6  7  8  9
        //1 4 6 8 9 12 35 68 99 *

        boats[r] = boats[r - 1] ;

        //1 4 6 8 9 12 35 68 99 *
        //1 4 6 8 9 12 35 68 99 99
        //1 4 6 8 9 12 35 68 68 99
        //1 4 6 8 9 12 35 35 68 99
        //1 4 6 8 9 12 !  35 68 99
    }
    boats[i] = newBoat ; //inserted in the right place
}

void pruneList  (tugboat* boats,int options) {
    //possibly come back and prune boats that are known
    //to be beyond the harbor or behind the ship so that
    //they would not be of help
    if (options > 0) {
        long long criteriaSectorKey = boats[0].routeposdist_by_harbordist1000000 ;
        for (int i = 1;i < options;i ++) {
            if (boats[i].routeposdist_by_harbordist1000000 == criteriaSectorKey) {
                boats[i].chosen = 0 ; //multiple boats got to the same
                //position on the route, but we sorted for the closed one and by name to
                //break ties
            }
            else {
                criteriaSectorKey = boats[i].routeposdist_by_harbordist1000000 ;
                //the next one would be de-chosen
            }
        }
    }
}
int chooseTugboat (tugboat* boats,int total,int chosen_number) {
    //  *     *  *     *       *
    // [x  a  b  y  t  m  n  l c]
    //  !
    //  ?+ ?  !
    //  ?+ ?  ?+ !
    //  ?+ ?  ?+ ?+ ?  !
    int chosen_seen  = 0 ;
    for (int i = 0;i < total;i ++) {
        if (boats[i].chosen) {
            if (chosen_seen == chosen_number) return i ;
            chosen_seen ++                             ;
        }
    }
    return -1 ;
}


int     prompt_int   (const char* prompt_msg)            {
    int result ;
    printf (prompt_msg)   ;
    scanf  ("%d",&result) ;
    return result ;
}
coord   prompt_coord (const char* prompt_msg)            {
    coord result                         ;
    printf (prompt_msg)                  ;
    scanf  ("%d %d",&result.x,&result.y) ;
    return result ;
}
tugboat prompt_tboat (const char* prompt_msg,ocean* osh) {
    tugboat tb ;
    printf (prompt_msg)                              ;
    scanf  ("%d %d",&tb.start_pos.x,&tb.start_pos.y) ;
    //not safe, but just using it for a school assignment
    scanf  ("%s"   ,tb.name.mem)                     ;
    tugboat_compute (&tb,osh)                        ;
    return tb ;
}
