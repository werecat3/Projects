`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 11/08/2021 02:07:14 PM
// Design Name: 
// Module Name: time_counter
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


module time_counter(
    input clk,
    input R,
    input CE,
    output [7:0] Q
    );
    
    wire UTC_1, UTC_2;
    
    counter four_bit_1 (.clk(clk), .R(R), .Din(1'b0), .Down(1'b0), .LD(1'b0), .UP(CE), .Q(Q[3:0]), .UTC(UTC_1));
    counter four_bit_2 (.clk(clk), .R(R), .Din(1'b0), .UP(CE & UTC_1), .Down(1'b0), .LD(1'b0), .Q(Q[7:4]), .UTC(UTC_2));
    
endmodule
