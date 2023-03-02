#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int a,b,c,d ;
} quad ;

//only safe if we are confident that we are pointing somewhere that has at least 4 things

typedef struct {
    int dings[100] ; //at the beach, dividided the beach into 100 20-meter regions, and keeping track of where we found maybe gold
    int start_time ;
    int end_time   ;
} metal_detect_stats  ;

typedef struct {
    int* dings_ptr  ; //points somewhere else, possibly connecting different ideas/structs in a kind of "web" of information
    int  start_time ;
    int  end_time   ;
} mdet_stats_linked ;

void print_unsafe (int* ints) {
    printf ("ints[0] => %d\n",ints[0]) ;
    printf ("ints[1] => %d\n",ints[1]) ;
    printf ("ints[2] => %d\n",ints[2]) ;
    printf ("ints[3] => %d\n",ints[3]) ;
    printf ("ints[4] => %d\n",ints[4]) ;
    printf ("ints[5] => %d\n",ints[5]) ;
    printf ("ints[6] => %d\n",ints[6]) ;
    printf ("ints[7] => %d\n",ints[7]) ;
    printf ("ints in this context is naming just a pointer, size in memory => %lu\n",sizeof (ints)) ;

}


int main (int argn,char** args) {
    metal_detect_stats mstats ;
    int  ints[8] = {1,3,10,30,9,20,9,9000} ;//puts 100 ints right on the "stack" (stack memory section), same effect on memory as 4 ints in a row
    int  index                             ; //keep track of which element we want to read from or write to
    int* ptr                               ;
    //"pointer" is just a fancy term for an absolute location to something ie the base location is PROGRAM MEMORY "0"
    //"pointer"s tend to be large values because of OS stuff, ie 0x293420
    //but pointers are still just numbers
    //what makes them special, is their intended purpose

    //just like this "index" variable inside this function has a meta-purpose, we're not directly using it's value
    //but using the value of something it helps us get to
    
    //we would be justified in talking about this variable "index" as a kind of "pointer" because 
    //it's "pointing" to some location inside of a list of elements


    ptr = (ints) + 0 ; //
    ptr = ints + 0 ; //when you take the name of an array (even a static one) alone without derefencing one of its elements
                     //the expression is implicitly evaluated as (type*) ie
                     //for ints, the "ints" alone without [] notation, can be used in contexts that expect "int*"
                    
    unsigned long mstats_sz = sizeof (mstats ) ;
    unsigned long mlnkd_sz  = sizeof (mdet_stats_linked ) ;

    printf ("mstats struct  is %lu bytes of memory\n",mstats_sz) ;
    printf ("linked sturct  is %lu bytes of memory\n",mlnkd_sz ) ;


    


    //sizeof static array works, don't expect sizeof (pointer) to ever give you the amount of elements it points
    
    
    
    return 0                  ;
}
