#include<stdbool.h>
#include <stdio.h>
#include <assert.h>
#define TRUE 1
#define FALSE 0
int width=16;
int cycles=1;
struct state_elements_addfxp_20_obf{
	short int res[1];
};
void addfxp_20_obf(short int a, short int b, _Bool clk, short int *q, unsigned char working_locking_key)
{
  struct state_elements_addfxp_20_obf  saddfxp_20_obf;
  short int res_old[1];
  int i;
  res_old = saddfxp_20_obf.res[0];
  saddfxp_20_obf.res[0] = working_locking_key[0] ? a + b : a - b;
  for(i = 1 & 4294967295; (int)i < cycles; i = (int)i + 1 & 4294967295)
    saddfxp_20_obf.res[(unsigned char)i] = res_old[(unsigned char)((int)i - 1)];
  *q = saddfxp_20_obf.res[(unsigned char)(cycles - 1)];
}
void main() {
	short int a;
	short int b;
	_Bool clk;
	short int q;
	unsigned char working_locking_key;
	 {
		addfxp_20_obf(a, b, clk, &q, working_locking_key);
	}
}
