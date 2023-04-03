#include<stdio.h>
#include<assert.h>

int width = 16;
int cycles = 1;

void addfxp_20_obf(int a, int b, bool clk, int *q, unsigned char working_locking_key){
	int res[1];
	int i;
	res[0] = (working_locking_key & 0x1) ? a + b : a - b;
	for(i = 1; i < cycles; i++){
		res[i] = res[i-1];
	}
	*q = res[cycles-1];
}

int main(int argc, char* argv[]){
	int a;
	sscanf(argv[1], "%d", &a);
	int b;
	sscanf(argv[2], "%d", &b);
	bool clk = 1;
	int q;
	unsigned char working_locking_key = 0;
	addfxp_20_obf(a, b, clk, &q, working_locking_key);
	printf("%d\n", q);
}
