
module addfxp_20_obf
(
  a,
  b,
  q,
  clk,
  working_locking_key
);

  parameter width = 16;
  parameter cycles = 1;
  input signed [width-1:0] a;
  input signed [width-1:0] b;
  input clk;
  output signed [width-1:0] q;
  reg signed [width-1:0] res [cycles-1:0];
  integer i;
  input [0:0] working_locking_key;
  assign q = res[cycles - 1];

  always @(posedge clk) begin
    res[0] <= (working_locking_key[0])? a + b : a - b;
    for(i=1; i<cycles; i=i+1) res[i] <= res[i - 1];
  end


endmodule

