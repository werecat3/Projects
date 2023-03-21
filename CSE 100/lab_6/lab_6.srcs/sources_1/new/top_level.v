`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 11/08/2021 01:25:50 PM
// Design Name: 
// Module Name: top_level
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


module top_level(
    input btnU, //global reset
    input btnR,
    input btnL,
    input clkin,
    output led_9,
    output led_15,
    output [3:0] an,
    output [6:0] seg,
    output dp
    );
    wire clk, digsel, qsec;
    wire [3:0] neg;
    wire [3:0] Q_ring;
    wire [7:0] Q_time;
    wire [7:0] Q_timer;
    wire [7:0] Q_turk, inv_Q_turk, signed_turk, pos_turk, neg_turk, final_turk;
    wire [15:0] Q_select;
    wire [3:0] display;
    wire btnL_sync, btnR_sync;
    wire one_sec, sec_15, LTR, RTL, LTR_e, RTL_e, idle, Z; 
    wire [7:0] temp_seg;
    wire time_up;
    
    //need to create my total 16 bit thing to select from later
    //this is the 4 bits for the counter, the thing to create the negative
    //then the right two for the counters
    //assign Q_select = {blah, blah, blah, blah}
    
    //synchronizes the button presses
    FDRE #(.INIT(1'b0) ) btnL_syncs (.C(clk), .R(btnU), .CE(1'b1), .D(btnL), .Q(btnL_sync));
    FDRE #(.INIT(1'b0) ) btnR_syncs (.C(clk), .R(btnU), .CE(1'b1), .D(btnR), .Q(btnR_sync));
    
    //provided clock
    lab6_clks slowit (.clkin(clkin), .greset(btnU), .clk(clk), .digsel(digsel), .qsec(qsec));
    
    //time ocunter in order to create the input of 15 seconds
    time_counter time_count (.clk(clk), .R(btnU | idle), .CE(qsec), .Q(Q_time));
    assign one_sec = Q_time[2];
    
    edge_detector timer (.D(one_sec), .clk(clk), .CE(1'b1), .Q_final(time_up));
    time_counter for_display (.clk(clk), .R(btnU | idle), .CE(time_up & ~sec_15), .Q(Q_timer));
    assign sec_15 = &Q_timer[3:0];
    //Q_timer [0] to [3] are the ones we put into the num for the selector
    
    //my state machine. this one is nicer
    state_machine my_baby (.btnL(btnL), .btnR(btnR), .btnU(btnU), .clk(clk), .sec_15(sec_15), .RTL(RTL), .LTR(LTR),
                           .idle(idle));
    
    edge_detector RTL_edge (.D(RTL), .clk(clk), .CE(1'b1), .Q_final(RTL_e));
    edge_detector LTR_edge (.D(LTR), .clk(clk), .CE(1'b1), .Q_final(LTR_e));
    
    turkey_counter turkey (.clk(clk), .R(btnU), .Q(Q_turk), .UP(RTL_e & ~sec_15), .Down(LTR_e & ~sec_15), .LD(1'b0), .Z(Z));
    assign inv_Q_turk = ~(Q_turk);
    incrementer comp (.a(inv_Q_turk), .s(signed_turk));
    //need two versions of the signed on so i can use mux to choose between two
    m28_1 sign_thing (.in0(Q_turk), .in1(signed_turk), .sel(Q_turk[7]), .o(final_turk));
    
    //just same ring counter as last lab
    ring_counter ring_counter (.clk(clk), .CE(digsel), .Q(Q_ring));
    
    //create the number for the selector here
    //the dash is made by inverting a zero but this needs to be done after the hexseg convert
    assign neg = 1'b0;
    assign Q_select = {Q_timer[3:0], neg, final_turk};
    
    selector selector (.N(Q_select), .sel(Q_ring), .H(display));
    hex7seg segments (.n(display) , .seg(temp_seg)); //try without using the negative sign first. then try to use code
    assign seg[7] = (temp_seg[7] & an[2]) | (~temp_seg[7] & ~an[2]);
    assign seg[6] = (temp_seg[6] & an[2]) | (~temp_seg[6] & ~an[2]);
    assign seg[5] = (temp_seg[5] & an[2]) | (~temp_seg[5] & ~an[2]);
    assign seg[4] = (temp_seg[4] & an[2]) | (~temp_seg[4] & ~an[2]);
    assign seg[3] = (temp_seg[3] & an[2]) | (~temp_seg[3] & ~an[2]);
    assign seg[2] = (temp_seg[2] & an[2]) | (~temp_seg[2] & ~an[2]);
    assign seg[1] = (temp_seg[1] & an[2]) | (~temp_seg[1] & ~an[2]);
    assign seg[0] = (temp_seg[0] & an[2]) | (~temp_seg[0] & ~an[2]);
    
    assign led_9 = ~btnR;
    assign led_15 = ~btnL;
    
    assign an[0] = ~Q_ring[0];
    assign an[1] = ~Q_ring[1];
    assign an[2] = ~(Q_turk[7] & Q_ring[2]);
    assign an[3] = (idle) | ~(~idle & Q_ring[3]); //more to add. this makes it so it is off while in idle
    
    assign dp = 1'b1;
endmodule
