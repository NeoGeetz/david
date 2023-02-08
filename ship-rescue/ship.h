#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>


enum {RESCUE_START=0} ;
enum {NO_WAKE='-',WAKE='^',BOAT='X'} ;
enum {QUERY,SEND_BOAT}               ;

typedef struct {
    int mode     ;
    int location ;
} action ;

typedef struct {
    int value    ;//NO_WAKE,WAKE,BOAT
    int location ;
} response ;


typedef struct { //possibility
    char* the_water ;
    int   size      ; //how vast is our ocean
} ocean ;

void ocean_init        (ocean* osh)              ;
void ocean_format      (ocean* osh,int size)     ;
void ocean_destroy     (ocean* osh)              ;
int  ocean_first_still (ocean* osh)              ;
void ocean_add_wake    (ocean* osh,int location) ;

//prints an ascii representation of our 1-dimensional "ocean" on a single line
void ocean_print   (ocean*) ;

//max location ~= max_startpos + 24 * max_shipspeed  (just to know how much memory to allocate, maybe + 1 or something, will refine later)


void   adjust_information (ocean* osh,int ship_speed,response resp) ;
action work               (ocean* osh,int ship_speed,response resp) ;


//QUERY first, then response
