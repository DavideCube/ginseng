#include "functions.h"
/**
* Power function implemented with exp by squaring (shift in binaries).
* Runs in log2(n), where n is the exponent.
*/
float myPow(float base, int exp){
	int res = 1;
	for (;;){

        if (exp & 1)
            res *= base;
        exp >>= 1;
        if (!exp)
            break;
        base *= base;
    }

    return res;
}



float mod(float a, float b){
    return a%b;
}
