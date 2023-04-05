int get_rel_tag (int offset,int loc,int* journey,int journey_length) { //this function is only implemented because there is no standard return value for an out-of-bounds array element, and it's not built-in anyway
    if (loc + offset >= journey_length) return -1 ;
    if (loc + offset <  0             ) return -1 ; //array bounds safety
    return journey[loc + offset] ;
}

int exact_dist (int d,int reference_tag,int find_tag,int* journey,int journey_length) {
    for (int i = 0;i < journey_length;i ++) {
        if (journey[i] == find_tag) {
            if (get_rel_tag (-d,i,journey,journey_length) == reference_tag) return 1 ;
            if (get_rel_tag (+d,i,journey,journey_length) == reference_tag) return 1 ;
        }
    }
    
    //not done, look for an indirect path
    if (d > 1) {
        //the second attempt only makes sense if we're not asking for direct adjacency or 0-adjacency (self-to-self)
        for (int i = 0;i < journey_length;i ++) {
            if (exact_dist (d - 1,journey[i],find_tag,journey,journey_length)) {
                if (exact_dist (1,reference_tag,journey[i],journey,journey_length)) return 1 ;
            }
        }
    }
    
    return 0 ;
}

int shortest_dist (int reference_tag,int find_tag,int* journey,int journey_length) {
    int max_dist = journey_length ; //just reusing the length of the journey itself as the max distance should satisfy

    for (int d = 0;d < max_dist;d ++) {
        if (exact_dist (d,reference_tag,find_tag,journey,journey_length)) return d ;
    }
    return -1 ; //should never happen
}

/*

example, notice that 9 can get to 1 through 9 -> 4 -> 3 -> 2    ==> 1
                                         or 9 -> 6 -> 3 -> 5    ==> 1

but since 4 is also connected to 1 
directly, 9 could also go through           9 -> 4              ==> 1


just because the interior layout constructing input did not show that
path explicitly doesn't mean it didn't facilitate for its existence.



1
2
4
3
4
1
5
3
6
9
4
3
2
1

scan this, 9 never touches 1, so try again, ask if 9 touches anything that touches 1

1   *, try with 1, but 1 does not "touch" 1, it IS 1, so it is not dist 1 but dist 0 so skipped
2   *, try on 2 (another deep loop), 9 does not touch 2
4   *, try on 4 which we discover touches 1, 9 touches 4, we're done
3
4
1
5
3
6
9
4
3
2
1


*/
