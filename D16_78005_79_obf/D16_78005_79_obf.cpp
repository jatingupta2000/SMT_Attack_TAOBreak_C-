#include <stdio.h>
#include <assert.h>
#include <stdbool.h>
#include <bits/stdc++.h>
#define TRUE 1
#define FALSE 0
using namespace std;

unsigned int out;
unsigned int out2;
unsigned int out3;

void D16_78005_79_obf(bool clk, unsigned int *out, unsigned int addr, unsigned __int128 extract_locking_key)
{
  unsigned int out_old;
  unsigned int out2_old;
  unsigned int out3_old;
  out2_old = out2;
  out_old = out;
  out3_old = out3;
  out2 = out3_old;
  out = out2_old;
  {
    if((unsigned int)addr == 0)
      out3 = extract_locking_key ^ 65535;

    else
      if((unsigned int)addr == 1)
        out3 = extract_locking_key ^ 4294901760;

      else
        if((unsigned int)addr == 2)
          out3 = extract_locking_key ^ 281470681808895;

        else
          if((unsigned int)addr == 3)
            out3 = extract_locking_key[63, 48] ^ 18446462603027742720;

          else
            if(TRUE)
              out3 = extract_locking_key[79, 64] ^ 1208907373152026146963455;

  }
}
int main() {
	bool clk = 1;
	unsigned int out;
	unsigned int addr = 3;
	unsigned __int128 extract_locking_key;
	D16_78005_79_obf(clk, &out, addr, extract_locking_key);
	cout<<out<<endl;
	return 0;
}

