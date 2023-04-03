#include <stdio.h>
#include <assert.h>
#define TRUE 1
#define FALSE 0

struct state_elements_D16_78005_79_obf{
unsigned short int out;
unsigned short int out2;
unsigned short int out3;
};

void D16_78005_79_obf(_Bool clk, unsigned short int *out, unsigned char addr, unsigned __int128 extract_locking_key)
{
  struct state_elements_D16_78005_79_obf  sD16_78005_79_obf;
  unsigned short int out_old;
  unsigned short int out2_old;
  unsigned short int out3_old;
  out2_old = sD16_78005_79_obf.out2;
  out_old = sD16_78005_79_obf.out;
  out3_old = sD16_78005_79_obf.out3;
  sD16_78005_79_obf.out2 = out3_old;
  sD16_78005_79_obf.out = out2_old;
  {
    if((unsigned int)addr == 0)
      sD16_78005_79_obf.out3 = extract_locking_key[15, 0]; // 65535

    else
      if((unsigned int)addr == 1)
        sD16_78005_79_obf.out3 = extract_locking_key[31, 16]; //  4294901760

      else
        if((unsigned int)addr == 2)
          sD16_78005_79_obf.out3 = extract_locking_key[47, 32]; // 281470681808895

        else
          if((unsigned int)addr == 3)
            sD16_78005_79_obf.out3 = extract_locking_key[63, 48]; // 18446462603027742720

          else
            if(TRUE)
              sD16_78005_79_obf.out3 = extract_locking_key[79, 64]; // 1208907373152026146963455

  }
}
void main() {
_Bool clk;
unsigned short int out;
unsigned char addr;
unsigned __int128 extract_locking_key;
while(1) {
D16_78005_79_obf(clk, &out, addr, extract_locking_key);
}
}
