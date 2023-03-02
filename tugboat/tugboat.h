#pragma once
#include <stdio.h>
#include <string.h>
#include <stdlib.h>



//? easier assignment, don't need to ALSO deal with memory management
typedef struct {
    char mem[100] ;
} cstring ;

//"hi"      compiler will pass these as (const char*)
//"hello"
int     cstring_cmp (cstring a,cstring b) ;
cstring cstring_    (const char*   cstr ) ; //cstring_ ("michael"),, cstring_ ("jacob")

typedef struct {
    int x ;
    int y ;
} coord ;

int coord_eq (coord a,coord b) ;


typedef coord vec2 ;//just to distinguish concepts

long vec2_magSq (vec2 v) ;

typedef struct {
    coord min,max ;
} range ;

typedef struct {
    int        chosen                            ;//start all at 1
    cstring    name                              ;
    coord      start_pos                         ;
    //coord    route_pos                         ;
    long long  routeposdist_by_harbordist1000000 ; //can use this to compare routepos-dists because harbordist multiplier is the same for every tugboat (long   routepos_dist_to_beginningSq)
    long long  dist_to_boatSq                    ; //when projections are the same, can compare this to effectively compare phantom attribute -> long dist_to_routeSq
} tugboat ;

typedef struct {
    coord     distressed          ;
    coord     harbor              ;
    tugboat*  initial_tboats      ; //point to sorted list to aid debugging
    int       total_tugboats      ;
} ocean ;
//remeber to do ocean ? = {0} ;

int     ocean_tb_index (ocean* osh,coord pos)               ;//return -1 if no tugboat at that exact coordinate
range   ocean_range    (ocean* osh)                         ;
void    ocean_print    (ocean* osh,tugboat* order,int step) ;//pass -1 for step to just print the initial state


//compute the remaining needed information of a tugboat
//given the distressed ship start and the harbor
void tugboat_compute (tugboat* dest,ocean* osh) ;

tugboat tugboat_     (coord pos,cstring name,ocean* osh) ;



//boats is essentially array to store result
//this function keeps the array sorted as it adds new boats
void addTugBoat    (tugboat newBoat,tugboat* boats,int size,int limit) ;
void pruneList     (tugboat* boats,int options)                        ;//total options, narrow down to our choice
int  chooseTugboat (tugboat* boats,int total,int step) ;//return -1 if a step is beyond needed steps, otherwise return address location of next chosen tugboat


int     prompt_int   (const char* prompt_msg)            ;//type 1 number  on a line
coord   prompt_coord (const char* prompt_msg)            ;//type 2 numbers on a line space separated
tugboat prompt_tboat (const char* prompt_msg,ocean* osh) ;//2 numbers then a name


