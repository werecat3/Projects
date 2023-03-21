`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 10/29/2021 08:50:15 PM
// Design Name: 
// Module Name: random_number_gen
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


module random_number_gen(
    input clk,
    input reset,
    input CE,
    output [7:0] Q
    );
    
    //ire [7:0] rnd;
    
    //use first 6 bits. 2 are for the left number 4 are for the first number
    
    FDRE #(.INIT(1'b0) ) bit_1 (.C(clk), .R(reset), .CE(CE), .D(Q[0] ^ Q[5] ^ Q[6] ^ Q[7]), .Q(Q[0]));
    FDRE #(.INIT(1'b0) ) bit_2 (.C(clk), .R(reset), .CE(CE), .D(Q[0]), .Q(Q[1]));
    FDRE #(.INIT(1'b0) ) bit_3 (.C(clk), .R(reset), .CE(CE), .D(Q[1]), .Q(Q[2]));
    FDRE #(.INIT(1'b0) ) bit_4 (.C(clk), .R(reset), .CE(CE), .D(Q[2]), .Q(Q[3]));
    FDRE #(.INIT(1'b0) ) bit_5 (.C(clk), .R(reset), .CE(CE), .D(Q[3]), .Q(Q[4]));
    FDRE #(.INIT(1'b0) ) bit_6 (.C(clk), .R(reset), .CE(CE), .D(Q[4]), .Q(Q[5]));
    FDRE #(.INIT(1'b0) ) bit_7 (.C(clk), .R(reset), .CE(CE), .D(Q[5]), .Q(Q[6]));
    FDRE #(.INIT(1'b1) ) bit_8 (.C(clk), .R(reset), .CE(CE), .D(Q[6]), .Q(Q[7]));
    
endmodule
