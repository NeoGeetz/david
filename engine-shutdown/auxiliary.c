#include "engine.h"

void scanfN (int N,long* buf11) {
    for (int i = 0;i < N;i ++) {
        if (i < N - 1) scanf ("%ld ",buf11 + i) ;
        else           scanf ("%ld" ,buf11 + i) ;
    }
}
