`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 10/19/2021 10:31:09 AM
// Design Name: 
// Module Name: edge_detector
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


module edge_detector(
    input D,
    input clk,
    input CE,
    output Q_final
    );
    
    wire q_1, q_2;
    
    FDRE #(.INIT(1'b0) ) bit1 (.C(clk), .R(1'b0), .CE(CE), .D(D), .Q(q_1));
    FDRE #(.INIT(1'b0) ) bit2 (.C(clk), .R(1'b0), .CE(CE), .D(q_1), .Q(q_2));
    
    assign Q_final = q_1 & ~q_2;
    
    
endmodule
