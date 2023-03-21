`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 10/12/2021 11:58:38 AM
// Design Name: 
// Module Name: incrementer
// Project Name: 
// Target Devices: 
// Tool Versions: 
// Description: 
// 
// Dependencies: 
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
//////////////////////////////////////////////////////////////////////////////////


module incrementer(
    input [7:0] a,
    input [1:0] b,
    output [7:0] s
    );
    
    wire [6:0] carry;
    
    full_adder Add0 (.c_in(1'b0), .sel({a[0] , b[0]}), .c(carry[0]), .s(s[0]));
    full_adder Add1 (.c_in(carry[0]), .sel({a[1] , b[1]}), .c(carry[1]), .s(s[1]));
    full_adder Add2 (.c_in(carry[1]), .sel({a[2] , 1'b0}), .c(carry[2]), .s(s[2]));
    full_adder Add3 (.c_in(carry[2]), .sel({a[3] , 1'b0}), .c(carry[3]), .s(s[3]));
    full_adder Add4 (.c_in(carry[3]), .sel({a[4] , 1'b0}), .c(carry[4]), .s(s[4]));
    full_adder Add5 (.c_in(carry[4]), .sel({a[5] , 1'b0}), .c(carry[5]), .s(s[5]));
    full_adder Add6 (.c_in(carry[5]), .sel({a[6] , 1'b0}), .c(carry[6]), .s(s[6]));
    full_adder Add7 (.c_in(carry[6]), .sel({a[7] , 1'b0}), .s(s[7]));
    
endmodule
