`timescale 100ns / 100ps
`include "my_cpu16.v"
`include "led7seg.v"

module cpu16controller(Clk, LED, SA);
input Clk;
output [7:0] LED;
output [3:0] SA;
wire [15:0] OUT;
wire I1,I2;


assign I1 = ~OUT[0];
assign I2 = ~OUT[1];

led7seg myled7seg(.I1(I1),.I2(I2),.LED(LED),.SA(SA));
my_CPU16v2 cpu1( ~Clk, OUT);

endmodule