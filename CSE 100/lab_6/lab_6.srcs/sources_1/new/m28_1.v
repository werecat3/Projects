`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 10/11/2021 06:54:52 PM
// Design Name: 
// Module Name: m2_1x8
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


module m28_1(
    input [7:0] in0,
    input [7:0] in1,
    input sel,
    output [7:0] o
    );
    
    assign o[0] = (in0[0] & ~sel) | (in1[0] & sel);
    assign o[1] = (in0[1] & ~sel) | (in1[1] & sel);
    assign o[2] = (in0[2] & ~sel) | (in1[2] & sel);
    assign o[3] = (in0[3] & ~sel) | (in1[3] & sel);
    assign o[4] = (in0[4] & ~sel) | (in1[4] & sel);
    assign o[5] = (in0[5] & ~sel) | (in1[5] & sel);
    assign o[6] = (in0[6] & ~sel) | (in1[6] & sel);
    assign o[7] = (in0[7] & ~sel) | (in1[7] & sel);
    
    
    
endmodule