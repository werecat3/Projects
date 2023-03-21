`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 10/31/2021 12:12:21 PM
// Design Name: 
// Module Name: LED_shifter
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


module LED_shifter(
    input In,
    input CE,
    input R,
    input clk,
    output [15:0] Q
    );
    //ce is if it is equal
    //in i think is always 1 but who knows
    
    
    FDRE #(.INIT(1'b0) ) bit_0 (.C(clk), .R(R), .CE(CE), .D(In), .Q(Q[0]));
    FDRE #(.INIT(1'b0) ) bit_1 (.C(clk), .R(R), .CE(CE), .D(Q[0]), .Q(Q[1]));
    FDRE #(.INIT(1'b0) ) bit_2 (.C(clk), .R(R), .CE(CE), .D(Q[1]), .Q(Q[2]));
    FDRE #(.INIT(1'b0) ) bit_3 (.C(clk), .R(R), .CE(CE), .D(Q[2]), .Q(Q[3]));
    FDRE #(.INIT(1'b0) ) bit_4 (.C(clk), .R(R), .CE(CE), .D(Q[3]), .Q(Q[4]));
    FDRE #(.INIT(1'b0) ) bit_5 (.C(clk), .R(R), .CE(CE), .D(Q[4]), .Q(Q[5]));
    FDRE #(.INIT(1'b0) ) bit_6 (.C(clk), .R(R), .CE(CE), .D(Q[5]), .Q(Q[6]));
    FDRE #(.INIT(1'b0) ) bit_7 (.C(clk), .R(R), .CE(CE), .D(Q[6]), .Q(Q[7]));
    FDRE #(.INIT(1'b0) ) bit_8 (.C(clk), .R(R), .CE(CE), .D(Q[7]), .Q(Q[8]));
    FDRE #(.INIT(1'b0) ) bit_9 (.C(clk), .R(R), .CE(CE), .D(Q[8]), .Q(Q[9]));
    FDRE #(.INIT(1'b0) ) bit_10 (.C(clk), .R(R), .CE(CE), .D(Q[9]), .Q(Q[10]));
    FDRE #(.INIT(1'b0) ) bit_11 (.C(clk), .R(R), .CE(CE), .D(Q[10]), .Q(Q[11]));
    FDRE #(.INIT(1'b0) ) bit_12 (.C(clk), .R(R), .CE(CE), .D(Q[11]), .Q(Q[12]));
    FDRE #(.INIT(1'b0) ) bit_13 (.C(clk), .R(R), .CE(CE), .D(Q[12]), .Q(Q[13]));
    FDRE #(.INIT(1'b0) ) bit_14 (.C(clk), .R(R), .CE(CE), .D(Q[13]), .Q(Q[14]));
    FDRE #(.INIT(1'b0) ) bit_15 (.C(clk), .R(R), .CE(CE), .D(Q[14]), .Q(Q[15]));
    
    
endmodule
