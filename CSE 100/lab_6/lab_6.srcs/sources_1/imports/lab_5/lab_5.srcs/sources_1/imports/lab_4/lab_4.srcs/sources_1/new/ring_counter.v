`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 10/19/2021 10:30:33 AM
// Design Name: 
// Module Name: ring_counter
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


module ring_counter(
    input clk,
    input CE,
    //input reset,
    output [3:0] Q
    );
    
    wire C1, C2, C3, C4;
    
    FDRE #(.INIT(1'b1) ) bit0 (.C(clk), .R(1'b0), .CE(CE), .D(C4), .Q(C1));
    FDRE #(.INIT(1'b0) ) bit1 (.C(clk), .R(1'b0), .CE(CE), .D(C1), .Q(C2));
    FDRE #(.INIT(1'b0) ) bit2 (.C(clk), .R(1'b0), .CE(CE), .D(C2), .Q(C3));
    FDRE #(.INIT(1'b0) ) bit3 (.C(clk), .R(1'b0), .CE(CE), .D(C3), .Q(C4));
    
    assign Q[0] = C1;
    assign Q[1] = C2;
    assign Q[2] = C3;
    assign Q[3] = C4;
    
endmodule
