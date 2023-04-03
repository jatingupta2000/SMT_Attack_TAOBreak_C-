#include <stdio.h>
#include <assert.h>
#include <stdbool.h>
#define TRUE 1
#define FALSE 0
int width=16;
int cycles=1;

	int res[1];

void addfxp_20_obf(int a, int b, _Bool clk, int *q, unsigned int working_locking_key)
{
  int res_old[1];
  int i;
  res_old[0] = res[0];
  res[0] = working_locking_key ? a + b : a - b;
  for(i = 1 & 4294967295; (int)i < cycles; i = (int)i + 1 & 4294967295)
    res[(unsigned int)i] = res_old[(unsigned int)((int)i - 1)];
  *q = res[(unsigned int)(cycles - 1)];
}
void main() {
	int a = 1;
	int b = 2;
	_Bool clk = 1;
	int q;
	unsigned int working_locking_key = 1;
	
		addfxp_20_obf(a, b, clk, &q, working_locking_key);
	printf("%d\n", q);	
}
