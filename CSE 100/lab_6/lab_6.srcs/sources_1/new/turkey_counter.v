`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 11/08/2021 02:07:14 PM
// Design Name: 
// Module Name: turkey_counter
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


module turkey_counter(
    input clk,
    input R,
    input UP,
    input Down,
    input LD,
    output [7:0] Q,
    output Z //high when all bits are zero
    );
    
    wire UTC_1, UTC_2, DTC_1, DTC_2;
    
    counter four_bit_1 (.clk(clk), .Din(1'b0), .R(R), .LD(LD), .UP(UP), .Down(Down), .Q(Q[3:0]), .UTC(UTC_1), .DTC(DTC_1));
    counter four_bit_2 (.clk(clk), .Din(1'b0), .R(R), .LD(LD), .UP(UP & UTC_1), .Down(Down & DTC_1), .Q(Q[7:4]), .UTC(UTC_2), .DTC(DTC_2));
    
    assign Z = (DTC_1 & DTC_2);
endmodule

