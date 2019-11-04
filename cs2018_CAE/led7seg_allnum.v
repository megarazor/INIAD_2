module led7seg9(I1, I2, I3, I4, SA, LED);
input I1, I2, I3, I4;
output [7:0]LED;
output [3:0]SA;
wire I1,I2,I3,I4;
	assign SA= 4'bZZZ0;
	assign LED[0]= (~I1 & I2 & I3 & I4) | (I1 & I2 & ~I3 & I4) |(I1 & ~I2 & ~I3 & I4);
	assign LED[1]= (~I1 & I2 & ~I3 & I4) | (I1 & ~I2 & ~I3 & I4);
	assign LED[2]= (I1 & ~I2 & I3 & I4);
	assign LED[3]= (~I1 & I2 & I3 & I4) | (I1 & I2 & ~I3 & I4) | (~I1 & ~I2 & ~I3 & I4) | (~I1 & I2 & I3 & ~I4);
	assign LED[4]= (~I1 & I2 & I3 & I4) | (~I1 & ~I2 & I3 & I4) | (I1 & I2 & ~I3 & I4) | (~I1 & I2 & ~I3 & I4) | (~I1 & ~I2 & ~I3 & I4) | (~I1 & I2 & I3 & ~I4);
	assign LED[5]= (~I1 & I2 & I3 & I4) | (I1 & ~I2 & I3 & I4) | (~I1 & ~I2 & I3 & I4) | (~I1 & ~I2 & ~I3 & I4);
	assign LED[6]= (I1 & I2 & I3 & I4) | (~I1 & I2 & I3 & I4) | (~I1 & ~I2 & ~I3 & I4);
	assign LED[7]= 1;
endmodule