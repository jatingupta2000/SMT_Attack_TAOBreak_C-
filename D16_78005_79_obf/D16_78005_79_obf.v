
module D16_78005_79_obf
(
  addr,
  out,
  clk,
  extract_locking_key
);

  input clk;
  output [15:0] out;
  input [1:0] addr;
  reg [15:0] out;
  reg [15:0] out2;
  reg [15:0] out3;
  input [79:0] extract_locking_key;

  always @(posedge clk) begin
    out2 <= out3;
    out <= out2;
    case(addr)
      0: out3 <= extract_locking_key[15:0];
      1: out3 <= extract_locking_key[31:16];
      2: out3 <= extract_locking_key[47:32];
      3: out3 <= extract_locking_key[63:48];
      default: out3 <= extract_locking_key[79:64];
    endcase
  end


endmodule

