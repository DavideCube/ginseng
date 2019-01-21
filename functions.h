/**
* Power function implemented with exp by squaring (shift in binaries).
* Runs in log2(n), where n is the exponent.
*/
float myPow(float base, int exp){

	int result = 1;
	for (;;){

        if (exp & 1)
            result *= base;
        exp >>= 1;
        if (!exp)
            break;
        base *= base;
    }

    return result;

}
