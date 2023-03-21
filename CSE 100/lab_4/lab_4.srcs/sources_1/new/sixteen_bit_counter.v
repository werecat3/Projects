`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 10/21/2021 12:55:21 PM
// Design Name: 
// Module Name: sixteen_bit_counter
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


module sixteen_bit_counter(
    input clk,
    input UP,
    input Down,
    input LD,
    input [15:0] Din,
    output [15:0] Q,
    output UTC,
    output DTC
    );
    
    wire DTC_1, DTC_2, DTC_3, DTC_4, UTC_1, UTC_2, UTC_3, UTC_4;
    
    counter four_bit_1 (.clk(clk), .UP(UP), .Down(Down), .LD(LD), .Din(Din[3:0]), .Q(Q[3:0]), .UTC(UTC_1), .DTC(DTC_1));
    counter four_bit_2 (.clk(clk), .UP(UP & UTC_1), .Down(Down & DTC_1), .LD(LD), .Din(Din[7:4]), .Q(Q[7:4]), .UTC(UTC_2), .DTC(DTC_2));
    counter four_bit_3 (.clk(clk), .UP(UP & UTC_1 & UTC_2), .Down(Down & DTC_1 & DTC_2), .LD(LD), .Din(Din[11:8]), .Q(Q[11:8]), .UTC(UTC_3), .DTC(DTC_3));
    counter four_bit_4 (.clk(clk), .UP(UP & UTC_1 & UTC_2 & UTC_3), .Down(Down & DTC_1 & DTC_2 &DTC_3), .LD(LD), .Din(Din[15:12]), .Q(Q[15:12]), .UTC(UTC_4), .DTC(DTC_4));
    
    assign UTC = UTC_1 & UTC_2 & UTC_3 & UTC_4;
    assign DTC = DTC_1 & DTC_2 & DTC_3 & DTC_4;
endmodule
