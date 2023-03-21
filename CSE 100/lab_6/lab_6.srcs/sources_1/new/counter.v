`timescale 1ns / 1ps


module counter(
    input clk,
    input UP,
    input Down,
    input LD,
    input R,
    input [3:0] Din,
    output [3:0] Q,
    output UTC,
    output DTC
    );
    //equations for the next state.
    
    
    // &(~Q[2:0]) lets you and all instances of Q  
    wire [3:0] D; // assign up and down logic in terms of Q
    wire [3:0] U;
    
    assign U[0] = ~Q[0];
    assign U[1] = Q[1] ^ Q[0];
    assign U[2] = Q[2] ^ (Q[1] & Q[0]);
    assign U[3] = Q[3] ^ (Q[2] & Q[1] & Q[0]);
    assign D[0] = ~Q[0];
    assign D[1] = ~(Q[1] ^ Q[0]);
    assign D[2] = Q[2] ^ (~Q[1] & ~Q[0]);
    assign D[3] = Q[3] ^ (~Q[2] & ~Q[1] & ~Q[0]);
    
    
    FDRE #(.INIT(1'b0) ) bit0 (.C(clk), .R(R), .CE(LD | UP ^ Down), .D((LD & Din[0]) | (~LD & UP & U[0] & ~Down) | (~LD & Down & D[0] & ~UP)), .Q(Q[0]));
    FDRE #(.INIT(1'b0) ) bit1 (.C(clk), .R(R), .CE(LD | UP ^ Down), .D((LD & Din[1]) | (~LD & UP & U[1] & ~Down) | (~LD & Down & D[1] & ~UP)), .Q(Q[1]));
    FDRE #(.INIT(1'b0) ) bit2 (.C(clk), .R(R), .CE(LD | UP ^ Down), .D((LD & Din[2]) | (~LD & UP & U[2] & ~Down) | (~LD & Down & D[2] & ~UP)), .Q(Q[2]));
    FDRE #(.INIT(1'b0) ) bit3 (.C(clk), .R(R), .CE(LD | UP ^ Down), .D((LD & Din[3]) | (~LD & UP & U[3] & ~Down) | (~LD & Down & D[3] & ~UP)), .Q(Q[3]));
    
    
    assign UTC = Q[3] & Q[2] & Q[1] & Q[0];
    assign DTC = ~Q[3] & ~Q[2] & ~Q[1] & ~Q[0];
    
endmodule