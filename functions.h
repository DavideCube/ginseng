float myPow(float p, int exponent){
	int res = 1;
	for(int i = 0; i < exponent; i++)
		res *= p; 
		
	return res;
}
