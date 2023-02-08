//- something that outputs assembly with an easy dependent function to modify
//- the dependent function has more than one instruction to step through
//- the output prints to terminal for feedback
//- the result of the program cannot be predicted from analysis of the source code alone
#include "ship.h"

//if we passed in the null string, this function would fail, possibly segfault or something like that.
//str == 0 this would be dangerous
//str[0] == 0 this is what we are expecting (getline probably guarantees us this at the least (user just presses enter)
void normalize (char* str) {
    //we are assuming, that str is a valid pointer to at least 1 element
    //while str[0] is *non-zero*
    while (str[0]) {
        str[0] = tolower (str[0]) ;
        str    = str + 1          ;
    }
}

void satellite_comm (action axn) {
    if      (axn.mode == QUERY    ) printf ("? ") ;
    else if (axn.mode == SEND_BOAT) printf ("! ") ;
    else exit(1) ;
    printf ("%d\n",axn.location) ;
}

int main (int argn,char** args) {
    int      bytes_read                             ;
    char     buffer[512]                            ;//line buffer
    char*    input                   =       buffer ;
    size_t   limit                   =       512    ;
    int      QUIT                    =       0      ;//don't quit by default
    int      max_speed,max_startpos                 ;
    int      speed                                  ;
    action   axn                                    ;
    response resp                                   ;
    
    ocean  test        ;
    ocean_init (&test) ;

    //we will replace this with some call to gettimeofday() later
    srand (bytes_read) ;

    //first input line, sets up the parameters of our this mission
    scanf   ("%d %d",&max_speed,&max_startpos) ;
    printf  (">>> max speed, max_start_pos %d %d\n",max_speed,max_startpos) ;

    // sequence of numbers
    // 0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23
    // sequence /10
    // 0 0 0 0 0 0 0 0 0 0 1  1  1  1  1  1  1  1  1  1  2  2  2  2 
    // sequence %10
    // 0 1 2 3 4 5 6 7 8 9 0  1  2  3  4  5  6  7  8  9  0  1  2  3 

    // any_number % 2 (== 0 for all even numbers)
    // 0 1 2 3 4 5 6 => 0 1 0 1 0 1 0
    // any_number % 17 (== 0 for all multiples of 17)
    
    //I want a number from 0 ... 10

    //(uint)rand() => 1209 123 0192 00 124 1029 912 39 1294 912 99124 0921 
    //0 ... 10 0 1 2 3 ... 10
    //assigning the boat a random speed for now
    speed = ((unsigned int)rand ()) % (max_speed + 1) ;


    resp.value    = RESCUE_START          ;
    resp.location = -1                    ;//not using this field yet inside work()


    //max location ~= max_startpos + 24 * max_shipspeed  (just to know how much memory to allocate, maybe + 1 or something, will refine later)
    //size accommodates max location (+1)
    ocean_format (&test,max_startpos + 24 * max_speed + 1) ;
    printf       (">>> initial state: ")                 ;
    ocean_print  (&test)                                   ;

    axn     = work (&test,speed,resp) ;
    satellite_comm (axn)            ;
    
    do {
        getline   (&input,&limit,stdin) ;
        //now have the result string stored in "input" variable
        //note: if we just press enter without typing anything, the string will probably just be the null character '\0'
        normalize (input) ;
        //strcmp ("apple"   ,"banana"  ) => -1
        //strcmp ("velocity","banana"  ) => +1
        //strcmp ("velocity","velocity") =>  0
        //strcmp ("velocity","velocitz") =>  -1
        
        if      (strcmp (input,"wake"   ) == 0) {
            resp.value    = WAKE         ;
            resp.location = axn.location ;
        }
        else if (strcmp (input,"no wake") == 0) {
            resp.value    = NO_WAKE      ;
            resp.location = axn.location ;
        }
        else if (strcmp (input,"boat!"  ) == 0) {
            resp.value    = BOAT         ;
            resp.location = axn.location ;
        }
        else { //invalid input, do nothing ?
        }
        
        adjust_information (&test,speed,resp)      ;
        printf             (">>> current state: ") ;
        ocean_print        (&test)                 ;
        
        axn = work     (&test,speed,resp) ;
        satellite_comm (axn)              ;
    }
    while (axn.mode != SEND_BOAT) ;

    //response was boat!, begin the rescue
    printf (">>> begin boat rescue !\n") ;
    printf ("....\n") ;
    printf ("....\n") ;
    printf ("....\n") ;
    printf ("....\n") ;
    ocean_destroy (&test) ;
    printf (">>> finished\n") ;
    return 0                  ;
}
