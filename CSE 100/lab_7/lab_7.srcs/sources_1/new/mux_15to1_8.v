`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 11/22/2021 12:45:38 PM
// Design Name: 
// Module Name: mux_15to1_8
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


module mux_15to1_8(
    //input [7:0] in0,
    //input [7:0] in1,
    input [3:0] sel,
    output [11:0] o
    );
    wire [11:0] r1, r2, r3, r4, r5, r6, r7, r8, r9, r10, r11, r12, r13, r14, r15;
    
    assign r1 = 12'b000101100000;
    assign r2 = 12'b000101010000;
    assign r3 = 12'b000101000000;
    assign r4 = 12'b000100110000;
    assign r5 = 12'b000100100000;
    assign r6 = 12'b000100010000;
    assign r7 = 12'b000100000000;
    assign r8 = 12'b000011110000;
    assign r9 = 12'b000011100000;
    assign r10 = 12'b000011010000;
    assign r11 = 12'b000011000000;
    assign r12 = 12'b000010110000;
    assign r13 = 12'b000010100000;
    assign r14 = 12'b000010010000;
    assign r15 = 12'b000010000000;
    
    
    
    assign o[0] = ((r1[0] & ~sel[3] & ~sel[2] & ~sel[1] & ~sel[0])|(r1[0] & sel[3] & sel[2] & sel[1] & sel[0]))|(r2[0] & ~sel[3] & ~sel[2] & ~sel[1] & sel[0])|(r3[0] & ~sel[3] & ~sel[2] & sel[1] & ~sel[0])|(r4[0] & ~sel[3] & ~sel[2] & sel[1] & sel[0])|(r5[0] & ~sel[3] & sel[2] & ~sel[1] & ~sel[0])|(r6[0] & ~sel[3] & sel[2] & ~sel[1] & sel[0])|(r7[0] & ~sel[3] & sel[2] & sel[1] & ~sel[0])|(r8[0] & ~sel[3] & sel[2] & sel[1] & sel[0])|(r9[0] & sel[3] & ~sel[2] & ~sel[1] & ~sel[0])|(r10[0] & sel[3] & ~sel[2] & ~sel[1] & sel[0])|(r11[0] & sel[3] & ~sel[2] & sel[1] & ~sel[0])|(r12[0] & sel[3] & ~sel[2] & sel[1] & sel[0])|(r13[0] & sel[3] & sel[2] & ~sel[1] & ~sel[0])|(r14[0] & sel[3] & sel[2] & ~sel[1] & sel[0])|(r15[0] & sel[3] & sel[2] & sel[1] & ~sel[0]);
    assign o[1] = ((r1[1] & ~sel[3] & ~sel[2] & ~sel[1] & ~sel[0])|(r1[1] & sel[3] & sel[2] & sel[1] & sel[0]))|(r2[1] & ~sel[3] & ~sel[2] & ~sel[1] & sel[0])|(r3[1] & ~sel[3] & ~sel[2] & sel[1] & ~sel[0])|(r4[1] & ~sel[3] & ~sel[2] & sel[1] & sel[0])|(r5[1] & ~sel[3] & sel[2] & ~sel[1] & ~sel[0])|(r6[1] & ~sel[3] & sel[2] & ~sel[1] & sel[0])|(r7[1] & ~sel[3] & sel[2] & sel[1] & ~sel[0])|(r8[1] & ~sel[3] & sel[2] & sel[1] & sel[0])|(r9[1] & sel[3] & ~sel[2] & ~sel[1] & ~sel[0])|(r10[1] & sel[3] & ~sel[2] & ~sel[1] & sel[0])|(r11[1] & sel[3] & ~sel[2] & sel[1] & ~sel[0])|(r12[1] & sel[3] & ~sel[2] & sel[1] & sel[0])|(r13[1] & sel[3] & sel[2] & ~sel[1] & ~sel[0])|(r14[1] & sel[3] & sel[2] & ~sel[1] & sel[0])|(r15[1] & sel[3] & sel[2] & sel[1] & ~sel[0]);
    assign o[2] = ((r1[2] & ~sel[3] & ~sel[2] & ~sel[1] & ~sel[0])|(r1[2] & sel[3] & sel[2] & sel[1] & sel[0]))|(r2[2] & ~sel[3] & ~sel[2] & ~sel[1] & sel[0])|(r3[2] & ~sel[3] & ~sel[2] & sel[1] & ~sel[0])|(r4[2] & ~sel[3] & ~sel[2] & sel[1] & sel[0])|(r5[2] & ~sel[3] & sel[2] & ~sel[1] & ~sel[0])|(r6[2] & ~sel[3] & sel[2] & ~sel[1] & sel[0])|(r7[2] & ~sel[3] & sel[2] & sel[1] & ~sel[0])|(r8[2] & ~sel[3] & sel[2] & sel[1] & sel[0])|(r9[2] & sel[3] & ~sel[2] & ~sel[1] & ~sel[0])|(r10[2] & sel[3] & ~sel[2] & ~sel[1] & sel[0])|(r11[2] & sel[3] & ~sel[2] & sel[1] & ~sel[0])|(r12[2] & sel[3] & ~sel[2] & sel[1] & sel[0])|(r13[2] & sel[3] & sel[2] & ~sel[1] & ~sel[0])|(r14[2] & sel[3] & sel[2] & ~sel[1] & sel[0])|(r15[2] & sel[3] & sel[2] & sel[1] & ~sel[0]);
    assign o[3] = ((r1[3] & ~sel[3] & ~sel[2] & ~sel[1] & ~sel[0])|(r1[3] & sel[3] & sel[2] & sel[1] & sel[0]))|(r2[3] & ~sel[3] & ~sel[2] & ~sel[1] & sel[0])|(r3[3] & ~sel[3] & ~sel[2] & sel[1] & ~sel[0])|(r4[3] & ~sel[3] & ~sel[2] & sel[1] & sel[0])|(r5[3] & ~sel[3] & sel[2] & ~sel[1] & ~sel[0])|(r6[3] & ~sel[3] & sel[2] & ~sel[1] & sel[0])|(r7[3] & ~sel[3] & sel[2] & sel[1] & ~sel[0])|(r8[3] & ~sel[3] & sel[2] & sel[1] & sel[0])|(r9[3] & sel[3] & ~sel[2] & ~sel[1] & ~sel[0])|(r10[3] & sel[3] & ~sel[2] & ~sel[1] & sel[0])|(r11[3] & sel[3] & ~sel[2] & sel[1] & ~sel[0])|(r12[3] & sel[3] & ~sel[2] & sel[1] & sel[0])|(r13[3] & sel[3] & sel[2] & ~sel[1] & ~sel[0])|(r14[3] & sel[3] & sel[2] & ~sel[1] & sel[0])|(r15[3] & sel[3] & sel[2] & sel[1] & ~sel[0]);
    assign o[4] = ((r1[4] & ~sel[3] & ~sel[2] & ~sel[1] & ~sel[0])|(r1[4] & sel[3] & sel[2] & sel[1] & sel[0]))|(r2[4] & ~sel[3] & ~sel[2] & ~sel[1] & sel[0])|(r3[4] & ~sel[3] & ~sel[2] & sel[1] & ~sel[0])|(r4[4] & ~sel[3] & ~sel[2] & sel[1] & sel[0])|(r5[4] & ~sel[3] & sel[2] & ~sel[1] & ~sel[0])|(r6[4] & ~sel[3] & sel[2] & ~sel[1] & sel[0])|(r7[4] & ~sel[3] & sel[2] & sel[1] & ~sel[0])|(r8[4] & ~sel[3] & sel[2] & sel[1] & sel[0])|(r9[4] & sel[3] & ~sel[2] & ~sel[1] & ~sel[0])|(r10[4] & sel[3] & ~sel[2] & ~sel[1] & sel[0])|(r11[4] & sel[3] & ~sel[2] & sel[1] & ~sel[0])|(r12[4] & sel[3] & ~sel[2] & sel[1] & sel[0])|(r13[4] & sel[3] & sel[2] & ~sel[1] & ~sel[0])|(r14[4] & sel[3] & sel[2] & ~sel[1] & sel[0])|(r15[4] & sel[3] & sel[2] & sel[1] & ~sel[0]);
    assign o[5] = ((r1[5] & ~sel[3] & ~sel[2] & ~sel[1] & ~sel[0])|(r1[5] & sel[3] & sel[2] & sel[1] & sel[0]))|(r2[5] & ~sel[3] & ~sel[2] & ~sel[1] & sel[0])|(r3[5] & ~sel[3] & ~sel[2] & sel[1] & ~sel[0])|(r4[5] & ~sel[3] & ~sel[2] & sel[1] & sel[0])|(r5[5] & ~sel[3] & sel[2] & ~sel[1] & ~sel[0])|(r6[5] & ~sel[3] & sel[2] & ~sel[1] & sel[0])|(r7[5] & ~sel[3] & sel[2] & sel[1] & ~sel[0])|(r8[5] & ~sel[3] & sel[2] & sel[1] & sel[0])|(r9[5] & sel[3] & ~sel[2] & ~sel[1] & ~sel[0])|(r10[5] & sel[3] & ~sel[2] & ~sel[1] & sel[0])|(r11[5] & sel[3] & ~sel[2] & sel[1] & ~sel[0])|(r12[5] & sel[3] & ~sel[2] & sel[1] & sel[0])|(r13[5] & sel[3] & sel[2] & ~sel[1] & ~sel[0])|(r14[5] & sel[3] & sel[2] & ~sel[1] & sel[0])|(r15[5] & sel[3] & sel[2] & sel[1] & ~sel[0]);
    assign o[6] = ((r1[6] & ~sel[3] & ~sel[2] & ~sel[1] & ~sel[0])|(r1[6] & sel[3] & sel[2] & sel[1] & sel[0]))|(r2[6] & ~sel[3] & ~sel[2] & ~sel[1] & sel[0])|(r3[6] & ~sel[3] & ~sel[2] & sel[1] & ~sel[0])|(r4[6] & ~sel[3] & ~sel[2] & sel[1] & sel[0])|(r5[6] & ~sel[3] & sel[2] & ~sel[1] & ~sel[0])|(r6[6] & ~sel[3] & sel[2] & ~sel[1] & sel[0])|(r7[6] & ~sel[3] & sel[2] & sel[1] & ~sel[0])|(r8[6] & ~sel[3] & sel[2] & sel[1] & sel[0])|(r9[6] & sel[3] & ~sel[2] & ~sel[1] & ~sel[0])|(r10[6] & sel[3] & ~sel[2] & ~sel[1] & sel[0])|(r11[6] & sel[3] & ~sel[2] & sel[1] & ~sel[0])|(r12[6] & sel[3] & ~sel[2] & sel[1] & sel[0])|(r13[6] & sel[3] & sel[2] & ~sel[1] & ~sel[0])|(r14[6] & sel[3] & sel[2] & ~sel[1] & sel[0])|(r15[6] & sel[3] & sel[2] & sel[1] & ~sel[0]);
    assign o[7] = ((r1[7] & ~sel[3] & ~sel[2] & ~sel[1] & ~sel[0])|(r1[7] & sel[3] & sel[2] & sel[1] & sel[0]))|(r2[7] & ~sel[3] & ~sel[2] & ~sel[1] & sel[0])|(r3[7] & ~sel[3] & ~sel[2] & sel[1] & ~sel[0])|(r4[7] & ~sel[3] & ~sel[2] & sel[1] & sel[0])|(r5[7] & ~sel[3] & sel[2] & ~sel[1] & ~sel[0])|(r6[7] & ~sel[3] & sel[2] & ~sel[1] & sel[0])|(r7[7] & ~sel[3] & sel[2] & sel[1] & ~sel[0])|(r8[7] & ~sel[3] & sel[2] & sel[1] & sel[0])|(r9[7] & sel[3] & ~sel[2] & ~sel[1] & ~sel[0])|(r10[7] & sel[3] & ~sel[2] & ~sel[1] & sel[0])|(r11[7] & sel[3] & ~sel[2] & sel[1] & ~sel[0])|(r12[7] & sel[3] & ~sel[2] & sel[1] & sel[0])|(r13[7] & sel[3] & sel[2] & ~sel[1] & ~sel[0])|(r14[7] & sel[3] & sel[2] & ~sel[1] & sel[0])|(r15[7] & sel[3] & sel[2] & sel[1] & ~sel[0]);
    assign o[8] = ((r1[8] & ~sel[3] & ~sel[2] & ~sel[1] & ~sel[0])|(r1[8] & sel[3] & sel[2] & sel[1] & sel[0]))|(r2[8] & ~sel[3] & ~sel[2] & ~sel[1] & sel[0])|(r3[8] & ~sel[3] & ~sel[2] & sel[1] & ~sel[0])|(r4[8] & ~sel[3] & ~sel[2] & sel[1] & sel[0])|(r5[8] & ~sel[3] & sel[2] & ~sel[1] & ~sel[0])|(r6[8] & ~sel[3] & sel[2] & ~sel[1] & sel[0])|(r7[8] & ~sel[3] & sel[2] & sel[1] & ~sel[0])|(r8[8] & ~sel[3] & sel[2] & sel[1] & sel[0])|(r9[8] & sel[3] & ~sel[2] & ~sel[1] & ~sel[0])|(r10[8] & sel[3] & ~sel[2] & ~sel[1] & sel[0])|(r11[8] & sel[3] & ~sel[2] & sel[1] & ~sel[0])|(r12[8] & sel[3] & ~sel[2] & sel[1] & sel[0])|(r13[8] & sel[3] & sel[2] & ~sel[1] & ~sel[0])|(r14[8] & sel[3] & sel[2] & ~sel[1] & sel[0])|(r15[8] & sel[3] & sel[2] & sel[1] & ~sel[0]);                                                                                                                                     
    assign o[9] = ((r1[9] & ~sel[3] & ~sel[2] & ~sel[1] & ~sel[0])|(r1[9] & sel[3] & sel[2] & sel[1] & sel[0]))|(r2[9] & ~sel[3] & ~sel[2] & ~sel[1] & sel[0])|(r3[9] & ~sel[3] & ~sel[2] & sel[1] & ~sel[0])|(r4[9] & ~sel[3] & ~sel[2] & sel[1] & sel[0])|(r5[9] & ~sel[3] & sel[2] & ~sel[1] & ~sel[0])|(r6[9] & ~sel[3] & sel[2] & ~sel[1] & sel[0])|(r7[9] & ~sel[3] & sel[2] & sel[1] & ~sel[0])|(r8[9] & ~sel[3] & sel[2] & sel[1] & sel[0])|(r9[9] & sel[3] & ~sel[2] & ~sel[1] & ~sel[0])|(r10[9] & sel[3] & ~sel[2] & ~sel[1] & sel[0])|(r11[9] & sel[3] & ~sel[2] & sel[1] & ~sel[0])|(r12[9] & sel[3] & ~sel[2] & sel[1] & sel[0])|(r13[9] & sel[3] & sel[2] & ~sel[1] & ~sel[0])|(r14[9] & sel[3] & sel[2] & ~sel[1] & sel[0])|(r15[9] & sel[3] & sel[2] & sel[1] & ~sel[0]);                               
    assign o[10] = ((r1[10] & ~sel[3] & ~sel[2] & ~sel[1] & ~sel[0])|(r1[10] & sel[3] & sel[2] & sel[1] & sel[0]))|(r2[10] & ~sel[3] & ~sel[2] & ~sel[1] & sel[0])|(r3[10] & ~sel[3] & ~sel[2] & sel[1] & ~sel[0])|(r4[10] & ~sel[3] & ~sel[2] & sel[1] & sel[0])|(r5[10] & ~sel[3] & sel[2] & ~sel[1] & ~sel[0])|(r6[10] & ~sel[3] & sel[2] & ~sel[1] & sel[0])|(r7[10] & ~sel[3] & sel[2] & sel[1] & ~sel[0])|(r8[10] & ~sel[3] & sel[2] & sel[1] & sel[0])|(r9[10] & sel[3] & ~sel[2] & ~sel[1] & ~sel[0])|(r10[10] & sel[3] & ~sel[2] & ~sel[1] & sel[0])|(r11[10] & sel[3] & ~sel[2] & sel[1] & ~sel[0])|(r12[10] & sel[3] & ~sel[2] & sel[1] & sel[0])|(r13[10] & sel[3] & sel[2] & ~sel[1] & ~sel[0])|(r14[10] & sel[3] & sel[2] & ~sel[1] & sel[0])|(r15[10] & sel[3] & sel[2] & sel[1] & ~sel[0]);                               
    assign o[11] = ((r1[11] & ~sel[3] & ~sel[2] & ~sel[1] & ~sel[0])|(r1[11] & sel[3] & sel[2] & sel[1] & sel[0]))|(r2[11] & ~sel[3] & ~sel[2] & ~sel[1] & sel[0])|(r3[11] & ~sel[3] & ~sel[2] & sel[1] & ~sel[0])|(r4[11] & ~sel[3] & ~sel[2] & sel[1] & sel[0])|(r5[11] & ~sel[3] & sel[2] & ~sel[1] & ~sel[0])|(r6[11] & ~sel[3] & sel[2] & ~sel[1] & sel[0])|(r7[11] & ~sel[3] & sel[2] & sel[1] & ~sel[0])|(r8[11] & ~sel[3] & sel[2] & sel[1] & sel[0])|(r9[11] & sel[3] & ~sel[2] & ~sel[1] & ~sel[0])|(r10[11] & sel[3] & ~sel[2] & ~sel[1] & sel[0])|(r11[11] & sel[3] & ~sel[2] & sel[1] & ~sel[0])|(r12[11] & sel[3] & ~sel[2] & sel[1] & sel[0])|(r13[11] & sel[3] & sel[2] & ~sel[1] & ~sel[0])|(r14[11] & sel[3] & sel[2] & ~sel[1] & sel[0])|(r15[11] & sel[3] & sel[2] & sel[1] & ~sel[0]);                               
endmodule