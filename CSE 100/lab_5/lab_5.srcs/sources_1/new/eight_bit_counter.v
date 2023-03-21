`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 10/30/2021 08:29:19 PM
// Design Name: 
// Module Name: eight_bit_counter
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


module eight_bit_counter(
    input clk,
    input R,
    input CE,
    output [7:0] Q
    );
    
    wire UTC_1, UTC_2;
    
    counter four_bit_1 (.clk(clk), .R(R), .CE(CE), .Q(Q[3:0]), .UTC(UTC_1));
    counter four_bit_2 (.clk(clk), .R(R), .CE(CE & UTC_1), .Q(Q[7:4]), .UTC(UTC_2));
    
endmodule
