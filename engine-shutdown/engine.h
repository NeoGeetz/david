#pragma once
#include <stdio.h>
#include <stdlib.h>

//int is a number that can at LEAST be in the range -32768 => +32767

//int is guaranteed to at least be int16
//however, it could be int32, could be int64, could even be int128

//long is guranteed => -2bil ... +2bil


//enum {FOAM=12,AIR=14,DISCONN=20,LEMON=100} ;
//
//typedef struct {
//    int table[1000] ;
//    int hash_to_index (const char*) ;
//} dictionary ;
//
//typedef struct {
//    dictionary after_FOAM    ; //after_FOAM[FOAM] not allowed, after_FOAM[AIR] is a valid temp-change constant
//    dictionary after_AIR     ;
//    dictionary after_DISCONN ;
//    dictionary after_LEMON   ;
//    
//    //after_FOAM["air"]
//} deltaOptions ;

//typedef struct {
//    enum {FOAM=0,AIR=1,DISCONN=2,LEMON=3} ;
//    long FOAM_after_FOAM  ; //temp change
//    long  AIR_after_FOAM  ;
//    long LEMN_after_FOAM  ;
//    long DCON_after_FOAM  ;
//    long FOAM_after_AIR   ;
//    long  AIR_after_AIR   ;
//    long LEMN_after_AIR   ;
//    long DCON_after_AIR   ;
//    //...
//} deltaOptions ;
//switch (currentAction) {
//    case FOAM:
//        switch (lastAction) {
//            case FOAM:   
//            case AIR : tempChange = characteristics.FOAM_AFTER_AIR ;   
//        }
//    case AIR :
//}


//typedef struct {
//    enum {FOAM=0,AIR=1,DISCONN=2,LEMON=3} ;
//    long after_FOAM   [4] ; //after_FOAM[FOAM] not allowed, after_FOAM[AIR] is a valid temp-change constant
//    long after_AIR    [4] ;
//    long after_DISCONN[4] ;
//    long after_LEMON  [4] ; => long after_X[4][4]

//} deltaList ;
//switch (lastAction) {
//    case FOAM: tempChange = characteristics.after_FOAM   [currentAction_idx] ;
//    case AIR : tempChange = characteristics.after_AIR    [currentAction_idx] ;
//    case DCON: tempChange = characteristics.after_DISCONN[currentAction_idx] ;
//    case LEMN: tempChange = characteristics.after_LEMON  [currentAction_idx] ;
//}

//    long after_1st[4] ; //after_FOAM[FOAM] not allowed, after_FOAM[AIR] is a valid temp-change constant
//    long after_2nd[4] ;
//    long after_3rd[4] ;
//    long after_4th[4] ; => long after_X[4][4]

//tempChange = characteristicts.actions[currentAction][lastAction]

typedef struct {
    //N could be 1..11, let's just allocate the max memory we'd need and play with the sub
    //matrices for the actual use case
    long initial_deltas [11]     ;
    long dependent      [11][11] ;//row is the "i" corresponding with nomenclature professsor uses

    //dependent[3][4] => temperature change when performing "3" right after "4" happened
    //dependent[3][5] => temperature change when performing "3" right after "5" happened
} deltaTable ;

typedef struct {
    int actions[11] ;//just to make sure we have enough space, might only be 3 for example
} simulation ;

typedef struct {
    char a,b,c ;
} thing ; 
//&thing          SAME "ADDRESS" AS               &thing.a
//(&thing +1)     not the same "next address" as (&thing.a) + 1
//(char*)(&thing) SAME EXACT     THING AS         &thing.a

typedef struct {
    int elements[11] ;
} array11 ;


//nextDelta = deltaTable.dependent[current][previous]

//function only safe if we guarantee that we are passing it buffer of at least 11 elements
void       scanfN                           (int N,long* buf11)   ;
int        unwrap_permutation               (int N,array11 set)   ;
void       printi_arr                       (void* array_,int sz) ;
void       printl_arr                       (void* array_,int sz) ;
void       printl_mat                       (void* m,int rows,int cols) ;
simulation bestTemperatureReductionScenario (int maxActions,deltaTable* characteristics ,array11 possibilities,int currentAction,simulation accumulated,int netTempChange) ;

