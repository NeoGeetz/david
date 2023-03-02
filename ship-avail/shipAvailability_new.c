#include <stdio.h>
#include <string.h>
#include <stdlib.h>
//total length of boat names in a line
#define MAX_BOATS 20


//remember to init to zeros : cstring name = {0} ;

//'d' 'a' 'v' 'i' 'd' 0
//'d' 'a' 'v' 0   'd' 0



//'r' 'e' 'a' 'c' 't' 'o' 'r' 0

//'r' 'e' 'a' 0   't' 'o' 'r' 0

typedef struct {
    char s[256] ;//probably big enough for any boat name expected for this assignment
} cstring;

int  cstring_len (cstring* cstr            ) { return strlen (cstr->s) ; }

void cstring_set (cstring* cstr,char*    start,int length) { //extracting sub-strings out of a bigger string
    if (length < 255) {
        for (int i = 0;i < length;i ++)
            cstr->s[i] = start[i] ;

        cstr->s[length] = 0 ;
    }
    else exit (1) ;
}
void cstring_trunc (cstring* cstr,int reduced_length) {
    //note: unsafe function, just focuses on core logic but skims over error checking
    cstr->s[reduced_length] = 0 ;
}

//allBoats    [0][?]
//boatsPerLine[0]
//allBoats    [1][?]
//boatsPerLine[1]

//batallion[0].numBoats
//batallion[0].boats[?]

//allBoats[batallion][0] ;//first boat
//allBoats[batallion][1] ;//2nd boat
//allBoats[batallion][2] ;

typedef struct { //essentially is the line of boats
    int     numBoats         ;
    cstring boats[MAX_BOATS] ; //list of all boat names in each line
} batallion ;


int main(void)
{
    //int to store total number of lines
    int l           ;
    scanf("%d\n", &l) ;//reads number stopping at whitespace OR newline
    //getline or fgets + atoi
    //atoi (string_) ; //parses out number from a string
    //atoi ("32" ) ; //will return 32
    //atoi ("-32") ; //will return -32

    //contains the string that is a line of boat names
    //char lineOfBoats[MAX_BOATS];
    char inputLineOfBoats[512];//just a string, we need to parse it


    batallion batallions[100] ;//assignment specifies a max of 100 lines

    //assume we trust ourselves to have typed l as no greater than 100 (or less than 1)
    for(int i = 0; i < l; i++)
    {
        //gets user input for boat line
        //fgets(lineOfBoats, MAX_BOATS+2, stdin);
        cstring nextBoat                     ;
        char*   start = inputLineOfBoats     ;
        fgets (inputLineOfBoats, 512, stdin) ;

        int count = 0;
        //counts how many spaces in user input to determine number of boats
        int j ;
        for (j = 0; inputLineOfBoats[j] != '\0'; j++)
        {
            //will mess things up if the input is not strict
            if (inputLineOfBoats[j] == ' ')
            {
                //dearAuntSally dearlyDeported KnotLost
                cstring_set (&nextBoat,start,(inputLineOfBoats + j) - start) ;
                start = inputLineOfBoats + j + 1                             ;
                batallions[i].boats[count] = nextBoat                        ;

                count++;
            }
        }

        cstring_set   (&nextBoat,start,(inputLineOfBoats + j) - start) ;
        cstring_trunc (&nextBoat,cstring_len (&nextBoat) - 1)          ;
        batallions[i].boats[count] = nextBoat                          ;
        batallions[i].numBoats     = count + 1                         ;
    }
    
    //debug printing
    for (int i = 0;i < l; i ++) {
        for (int b = 0;b < batallions[i].numBoats;b ++) {
            printf ("%s : ",batallions[i].boats[b].s) ;
        }
        printf ("\n") ;
    }


    //user input on total number of customers
    int c            ;
    int w            ;
    scanf ("%d", &c) ;
    //cstring boatEachWeek[l] ; //note: bad form, discouraged
    cstring boatEachWeek[100] ;
    
    for (int q =0;q < c;q ++) {
        scanf ("%d",&w) ;//the week of desired travel for each of c customers
        for (int p  = 0;p < l;p ++) {
            int chosenBoat = (w - 1) % batallions[p].numBoats ; 
            boatEachWeek[p] = batallions[p].boats[chosenBoat] ;
        }
        
        for (int r = 0;r < l;r ++) {
            printf ("%s ",boatEachWeek[r].s) ;
        }
        printf ("\n") ;
        

    }

    // ----- char boatEachWeek[l];

    // ----- for(int q = 0; q < c; q++)
    // ----- {
    // -----     scanf("%d\n", &w);

    // -----     for(int p = 0; p < l; p++)
    // -----     {
    // -----         //int chosenBoat = w%boatsPerLine[p];
    // -----         int chosenBoat = (w - 1) %boatsPerLine[p];
    // -----         if(p == 0)
    // -----         {
    // -----             boatEachWeek[p] = allBoats[chosenBoat];
    // -----         }
    // -----         else
    // -----         {
    // -----             boatEachWeek[p] = allBoats[chosenBoat+boatsPerLine[p-1]];
    // -----         }
    // -----     }
    // -----     for(int r = 0; r < l; r++)
    // -----     {
    // -----         printf("%s ", boatEachWeek[r]);
    // -----     }
    // -----     printf("\n");
    // ----- }


    // ----- //checker to see if all boat names are in list
    // ----- printf("%s\n", allBoats);
    // ----- //checker to see if number of boats in each line is correct
    // ----- for(int p = 0; p < l; p++)
    // ----- {
    // -----     printf("%d ", boatsPerLine[p]);

    // ----- }
    // ----- printf("\n");

}

