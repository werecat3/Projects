`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 10/13/2021 05:50:32 PM
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
    input [7:0] sw,
    input btnL,
    input btnC,
    input btnR,
    input clkin,
    output [6:0] seg,
    output dp,
    output [3:0] an
    );
    
    wire s0, s1, s2, s3, s4, s5, s6, s7, dig_sel, carry;
    wire o0, o1, o2, o3, o4, o5, o6, o7, o8, o9, oa, ob, oc, od, oe;
    
    assign dp = 1'b1;
    assign an[0] = dig_sel;
    assign an[1] = ~dig_sel;
    assign an[2] = 1'b1;
    assign an[3] = 1'b1;
    
    incrementer inc (.a(sw), .b({btnL, btnC}), .s({s7, s6, s5, s4, s3, s2, s1, s0}));
    hex7seg hex_1 (.n({s7, s6, s5, s4}), .seg({oe, od, oc, ob, oa, o8, o7}));
    hex7seg hex_2 (.n({s3, s2, s1, s0}), .seg({o6, o5, o4, o3, o2, o1, o0}));
    m2_1x8 twotoone (.in0({1'b0, o6, o5, o4, o3, o2, o1, o0}), .in1({1'b0, oe, od, oc, ob, oa, o8, o7}), .sel(dig_sel), .o(seg));
    lab3_digsel my_digsel (.clkin(clkin), .greset(btnR), .digsel(dig_sel));
    
endmodule
