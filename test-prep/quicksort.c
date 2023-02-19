//- something that outputs assembly with an easy dependent function to modify
//- the dependent function has more than one instruction to step through
//- the output prints to terminal for feedback
//- the result of the program cannot be predicted from analysis of the source code alone
#include <stdio.h>
#include <stdlib.h>

void print     (int* a,int sz,int low,int high,int i_,int j_) {
    int inside = 0 ;
    if (low  == -1) low  = 0      ;
    if (high == -1) high = sz - 1 ;
    printf ("[") ;
    for (int i = 0;i < sz;i ++) {
        printf ("%-4d ",a[i]) ;
    }
    printf ("]\n") ;

    printf ("#") ;
    for (int i = 0;i < sz;i ++) {
        if (i == low) inside = 1 ;

        if (inside) {
            if (i == i_ && i == j_)     printf ("mmmm ") ;
            else
            if (i == i_)                printf ("rrrr ") ;
            else
            if (i == j_)                printf ("gggg ") ;
            else                        printf ("bbbb ") ;
        }
        else                            printf ("#### ") ;

        if (i == high) inside = 0 ;
    }
    printf ("# #%%#\n") ;
}

void swap (int* a,int i0,int i1) {
    int tmp = a[i0] ;
    a[i0]   = a[i1] ;
    a[i1]   = tmp   ;
}

int quicksort_size = 0 ;

//high is *at least* low + 1
int partition (int* a,int low_idx,int high_idx) {
    int pivot_value ;
    int i ;
    //could be any index, as long as its between low_idx  & high_idx
    //pivot_value = a[(low_idx + high_idx) /2] ;
    pivot_value = a[high_idx ] ;
    i           = low_idx - 1  ;//seems to be safe because even when low is 0, -1 is always added 1 before actually being used

    printf ("############# PIVOT (%4d) ################\n",pivot_value)  ;
    
    for (int j = low_idx;j <= high_idx - 1;j ++) {
        //[3 4 9 8 *5]
        
        if (a[j] < pivot_value) {
            printf ("\t([%d %d] swap {%4d}&{%4d})\n",i,j,a[i+1],a[j])  ;
            print  (a,quicksort_size,low_idx,high_idx,i,j) ;

            i = i + 1      ;
            swap   (a,i,j) ;
        }
        else {
            printf ("\t(no-swap           )\n") ;
            print  (a,quicksort_size,low_idx,high_idx,i,j) ;
        }
    }
    //at end of loop, i + 1 is .. the index of a slot

    printf ("\t([%d %d] eswp {%4d}&{%4d})\n",i,high_idx,a[i + 1] ,a[high_idx]) ;
    print  (a,quicksort_size,low_idx,high_idx,i,-1)      ;
    swap   (a,i + 1,high_idx)                            ;



    print  (a,quicksort_size,low_idx,high_idx,-1,-1) ;
    printf ("--- partitioned -- \n\n")               ;
    return i + 1                                     ;
}


void quicksort_ (int* a,int low_idx,int high_idx) {
    if (low_idx < high_idx) {
        int partition_idx ;
        partition_idx = partition (a,low_idx,high_idx) ;
        
        quicksort_ (a,low_idx,partition_idx - 1 ) ;
        quicksort_ (a,partition_idx + 1,high_idx) ;
    }
}

//assuming at least 1 element
void quicksort (int* a,int sz) {
    quicksort_size = sz     ;
    quicksort_ (a,0,sz - 1) ;
}


int main (int argn,char** args) {
    int arr[256]    ;
    int sz      = 0 ;
    int end     = 0 ;
    int matches = 1 ;
    
    while (matches == 1) {
        matches = scanf ("%d",arr + sz) ;
        if (matches != 1) continue      ;
        sz = sz + 1                     ;
    }

    printf ("got  array:       \n") ;
    print  (arr,sz,-1,-1,-1,-1)     ;
    
    quicksort (arr,sz)              ;

    printf ("sort array:       \n") ;
    print  (arr,sz,-1,-1,-1,-1)     ;
    return 0                        ;
}


#if 0
/* This function takes last element as pivot, places the pivot element at its correct position in sorted array, and places all smaller (smaller than pivot) to left of pivot and all greater elements to right of pivot */
partition (arr[], low, high)
{
    // pivot (Element to be placed at right position)
    pivot = arr[high];  
    i = (low – 1)  // Index of smaller element and indicates the 
    // right position of pivot found so far

    for (j = low; j <= high- 1; j++){
        // If current element is smaller than the pivot
        if (arr[j] < pivot){
            i++;    // increment index of smaller element
            swap arr[i] and arr[j]
        }
    }
    swap arr[i + 1] and arr[high])
    return (i + 1)
}
quickSort(arr[], low, high) {
    if (low < high) {
        /* pi is partitioning index, arr[pi] is now at right place */
        pi = partition(arr, low, high);
        quickSort(arr, low, pi – 1);  // Before pi
        quickSort(arr, pi + 1, high); // After pi
    }
}
#endif
