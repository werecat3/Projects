`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 10/19/2021 10:15:54 AM
// Design Name: 
// Module Name: counter
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


module counter(
    input clk,
    input R,
    input CE,
    output [3:0] Q,
    output UTC
    );
    //equations for the next state.
    
    
    // &(~Q[2:0]) lets you and all instances of Q  
    wire [3:0] D; // assign up and down logic in terms of Q
    wire [3:0] U;
    
    assign U[0] = ~Q[0];
    assign U[1] = Q[1] ^ Q[0];
    assign U[2] = Q[2] ^ (Q[1] & Q[0]);
    assign U[3] = Q[3] ^ (Q[2] & Q[1] & Q[0]);
    
    
    FDRE #(.INIT(1'b0) ) bit0 (.C(clk), .R(R), .CE(CE), .D(U[0]), .Q(Q[0]));
    FDRE #(.INIT(1'b0) ) bit1 (.C(clk), .R(R), .CE(CE), .D(U[1]), .Q(Q[1]));
    FDRE #(.INIT(1'b0) ) bit2 (.C(clk), .R(R), .CE(CE), .D(U[2]), .Q(Q[2]));
    FDRE #(.INIT(1'b0) ) bit3 (.C(clk), .R(R), .CE(CE), .D(U[3]), .Q(Q[3]));
    
    
    assign UTC = Q[3] & Q[2] & Q[1] & Q[0];
    
endmodule
