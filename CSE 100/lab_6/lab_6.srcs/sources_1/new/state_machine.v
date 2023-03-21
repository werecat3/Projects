`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 11/08/2021 02:07:14 PM
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
    input btnU, //global reset
    input btnR,
    input btnL,
    input clk,
    input sec_15,
    output LTR,
    output RTL,
    output idle
    );
    
    wire I; //idle
    wire EL, MFL, RS; //left to right wires
    wire ER, MFR, LS; //right to left wires
    //present states
    wire psI; //idle
    wire psEL, psMFL, psRS; //left to right wires
    wire psER, psMFR, psLS; //right to left wires
    
    //~btnR is when it isn't pressed or is let go
    //btnR is when it is pressed
    
    assign I = ((psI & ~btnR & ~btnL)|(psLS & ~btnL & ~btnR)|(psRS & ~btnR & ~btnL)|(psEL & ~btnL & ~btnR)|(psER & ~btnR & ~btnL));
    assign EL = ((psI & btnL)|(psMFL & btnL & ~btnR)|(psEL & ~btnR & btnL));
    assign MFL = ((psEL & btnR)|(psRS & btnL)|(psMFL & btnL & btnR));
    assign RS = ((psMFL & ~btnL)|(psRS & btnR));
    assign ER = ((psI & btnR)|(psMFR & btnR & ~btnL)|(psER & ~btnL & btnR));
    assign MFR = ((psER & btnL)|(psLS & btnR)|(psMFR & btnL & btnR));
    assign LS = ((psMFR & ~btnR)|(psLS & btnL));
    
    //states
    FDRE #(.INIT(1'b1) ) idle_state (.C(clk), .R(btnU), .CE(1'b1), .D(I), .Q(psI));
    FDRE #(.INIT(1'b0) ) enter_left (.C(clk), .R(btnU), .CE(1'b1), .D(EL), .Q(psEL));
    FDRE #(.INIT(1'b0) ) middle_f_left (.C(clk), .R(btnU), .CE(1'b1), .D(MFL), .Q(psMFL));
    FDRE #(.INIT(1'b0) ) right_side (.C(clk), .R(btnU), .CE(1'b1), .D(RS), .Q(psRS));
    FDRE #(.INIT(1'b0) ) enter_right (.C(clk), .R(btnU), .CE(1'b1), .D(ER), .Q(psER));
    FDRE #(.INIT(1'b0) ) middle_f_right (.C(clk), .R(btnU), .CE(1'b1), .D(MFR), .Q(psMFR));
    FDRE #(.INIT(1'b0) ) left_side (.C(clk), .R(btnU), .CE(1'b1), .D(LS), .Q(psLS));
    
    assign RTL = psLS & ~btnL & ~btnR;
    assign LTR = psRS & ~btnR & ~btnL;
    assign idle = psI;
    
endmodule
