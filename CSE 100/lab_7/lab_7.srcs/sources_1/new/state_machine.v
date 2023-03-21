`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 11/17/2021 09:17:39 PM
// Design Name: 
// Module Name: state_machine
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


module state_machine(
    input btnL,
    input btnR,
    input two_sec,
    input sixteen_f,
    input wall_hit,
    input clk,
    output idle,
    output two_sec_b,
    output run_game,
    output loss_idle,
    output going_up,
    output dropping
    );
    wire I, T, R, L, U;
    wire psI, psT, psR, psL, psU;
    
    assign I = (psI & ~btnL);
    assign T = (psI & btnL) | (psT & ~two_sec) | (psL & btnL);
    assign R = (psT & two_sec) | (psR & ~wall_hit & ~btnL) | (psU & sixteen_f);
    assign U = (psR & btnL) | (psU & ~sixteen_f & ~wall_hit);
    assign L = (psL & ~btnL) | (psR & wall_hit) | (psU & wall_hit);
    
    
    FDRE #(.INIT(1'b1) ) Idle (.C(clk), .R(btnR), .CE(1'b1), .D(I), .Q(psI));
    FDRE #(.INIT(1'b0) ) Two_second (.C(clk), .R(btnR), .CE(1'b1), .D(T), .Q(psT));
    FDRE #(.INIT(1'b0) ) Run_game (.C(clk), .R(btnR), .CE(1'b1), .D(R), .Q(psR));
    FDRE #(.INIT(1'b0) ) Going_up (.C(clk), .R(btnR), .CE(1'b1), .D(U), .Q(psU));
    FDRE #(.INIT(1'b0) ) Loss_idle (.C(clk), .R(btnR), .CE(1'b1), .D(L), .Q(psL));
    
    assign idle = psI;
    assign two_sec_b = psT;
    assign run_game = psR;
    assign loss_idle = psL;
    assign going_up = psU;
    assign dropping = psR;
    
endmodule
