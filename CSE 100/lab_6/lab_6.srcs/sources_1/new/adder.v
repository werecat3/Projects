`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 10/12/2021 12:34:07 PM
// Design Name: 
// Module Name: full_adder
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


module full_adder(
    input c_in,
    input [1:0] sel,
    output s,
    output c
    );
    
    m4_1 c_out (.in({1'b1, c_in, c_in, 1'b0}), .sel({sel[1], sel[0]}), .o(c));
    m4_1 sum (.in({c_in, ~c_in, ~c_in, c_in}), .sel({sel[1], sel[0]}), .o(s));
    
endmodule
