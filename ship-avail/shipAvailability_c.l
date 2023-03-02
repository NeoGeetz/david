#include <stdio.h>
#include <string.h>
//total length of boat names in a line
#define MAX_BOATS 20

int main(void)
{
    //int to store total number of lines
    int l;
    scanf("%d\n", &l);
    //contains the string that is a line of boat names
    //char lineOfBoats[MAX_BOATS];
    char lineOfBoats[512];
    //list of all boat names in each line
    char allBoats[MAX_BOATS*l]; //multiplies string by number of batallions
    //contains how many boats are in each line
    int boatsPerLine[l];//size for each batallion

    for(int i = 0; i < l; i++)
    {
        //gets user input for boat line
        //fgets(lineOfBoats, MAX_BOATS+2, stdin);
        fgets(lineOfBoats, 512, stdin);

        int count = 0;
        //counts how many spaces in user input to determine number of boats
        for(int j = 0; lineOfBoats[j] != '\0'; j++)
        {
            if(lineOfBoats[j] == ' ')
            {
                count++;
            }
        }

        boatsPerLine[i] = count + 1;

        //creates the list containing all boat names
        if(i == 0)
        {
            strcpy(allBoats, lineOfBoats);
            strcat(allBoats, " ");
        }
        else
        {
            strcat(allBoats, lineOfBoats);
            strcat(allBoats, " ");
        }

    }
    //checker to see if all boat names are in list
    printf("%s\n", allBoats);
    //checker to see if number of boats in each line is correct
    for(int p = 0; p < l; p++)
    {
        printf("%d ", boatsPerLine[p]);

    }
    printf("\n");

    //user input on total number of customers
    int c;
    scanf("%d\n", &c);
    int w;

    char boatEachWeek[l];

    for(int q = 0; q < c; q++)
    {
        scanf("%d\n", &w);

        for(int p = 0; p < l; p++)
        {
            //int chosenBoat = w%boatsPerLine[p];
            int chosenBoat = (w - 1) %boatsPerLine[p];
            if(p == 0)
            {
                boatEachWeek[p] = allBoats[chosenBoat];
            }
            else
            {
                boatEachWeek[p] = allBoats[chosenBoat+boatsPerLine[p-1]];
            }
        }
        for(int r = 0; r < l; r++)
        {
            printf("%s ", boatEachWeek[r]);
        }
        printf("\n");
    }
}

