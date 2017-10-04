extern int mcd(int, int);

int mcm(int a, int b){
	return ( (a * b) / mcd(a, b) );
}
