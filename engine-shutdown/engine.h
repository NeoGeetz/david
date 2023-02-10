#include <stdio.h>
#include <stdlib.h>

//int is a number that can at LEAST be in the range -32768 => +32767

//int is guaranteed to at least be int16
//however, it could be int32, could be int64, could even be int128

//long is guranteed => -2bil ... +2bil

typedef struct {
    //N could be 1..11, let's just allocate the max memory we'd need and play with the sub
    //matrices for the actual use case
    long initial_deltas [11]     ;
    long dependent      [11][11] ;//row is the "i" corresponding with nomenclature professsor uses
} deltaTable ;

typedef struct {
    int actions[11] ;//just to make sure we have enough space, might only be 3 for example
} simulation ;

typedef struct {
    int elements[11] ;
} array11 ;


//nextDelta = deltaTable.dependent[current][previous]

//function only safe if we guarantee that we are passing it buffer of at least 11 elements
void scanfN             (int N,long* buf11) ;

int  unwrap_permutation (int N,array11 set) ;
