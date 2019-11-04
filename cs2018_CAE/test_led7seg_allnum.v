module test_led7seg9;
reg i1, i2, i3, i4;
wire [7:0]led;
wire [3:0]sa;

led7seg9 led7seg91(.I1(i1), .I2(i2), .I3(i3), .I4(i4), .LED(led), .SA(sa));

initial begin
    $monitor("%t: i1 = %b, i2 = %b, i3 = %b, i4 = %b, sa = %b, led=\n  %b\n %b %b\n  %b\n %b %b\n  %b %b", $time, i1, i2, i3, i4, sa, led[0], led[5], led[1], led[6], led[4], led[2], led[3], led[7]);
    i1= 1; i2= 1; i3= 1; i4= 1;
    #10
    i1= 0;
    #10
    i1= 1; i2= 0;
    #10
    i1= 0;i2= 0;
    #10
    i1= 1; i2= 1; i3= 0;
    #10;
    i1= 0;
    #10
    i1=1; i2= 0;
    #10
    i1= 0;
    #10
    i1= 1; i2= 1; i3= 1; i4= 0;
    #10
    i1= 0;
    $finish;
end
endmodule