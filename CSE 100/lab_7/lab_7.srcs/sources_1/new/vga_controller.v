`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 11/15/2021 08:52:56 AM
// Design Name: 
// Module Name: vga_controller
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


module vga_controller(
    input clk,
    input btnR, 
    output Hsync,
    output Vsync,
    output active_h,
    output active_v,
    output [15:0] Q_H,
    output [15:0] Q_V,
    output vsync,
    output hsync 
    );
    
    wire [15:0] Q_h, Q_v;
    wire [11:0] total_vga;
    wire reset, reset_2; //this will be what resets them but i gotta figure it out first
    wire complete_row; // this is a standin for i think the hsync until i get it
    
    
    //lab7_clks not_so_slow (.clkin(clkin), .greset(btnR), .clk(clk), .digsel(digsel));
    
    //2 counters hsync and vsync
    //incremented using the clk provided
    
    sixteen_bit_counter Hsync_counter (.clk(clk), .R(1'b0), .UP(1'b1), .Down(1'b0), .LD(reset), .Din(16'b0), .Q(Q_h));
    sixteen_bit_counter Vsync_counter (.clk(clk), .R(1'b0), .UP(complete_row), .Down(1'b0), .LD(reset_2), .Din(16'b0), .Q(Q_v)); //only increments every time an entire row is complete
    
    //this will reset the counter once it reaches the end of a row
    assign reset = (Q_h[9] & Q_h[8] & ~Q_h[7] & ~Q_h[6] & Q_h[5]);
    //this will reset the counter once it reached the very bottom of the screen
    assign reset_2 = (Q_v[9] & ~Q_v[8] & ~Q_v[7] & ~Q_v[6] & ~Q_v[5] & ~Q_v[4] & Q_v[3] & Q_v[2] & ~Q_v[1] & Q_v[0]);
    //this is the value when a row is complete 
    assign complete_row = (Q_h[9] & Q_h[8] & ~Q_h[7] & ~Q_h[6] & Q_h[5]);
    
    
    //need to set hsync anc vsync to low in their respective areas
    assign hsync = ~(Q_h > 12'b001010001111 & Q_h <= 12'b001011101110);
    assign vsync = ~(Q_v > 12'b000111101001 & Q_v <= 12'b000111101010);
    assign active_h = (Q_h < 12'b001010000000);
    assign active_v = (Q_v < 12'b000111100000);
    assign Q_H = Q_h;
    assign Q_V = Q_v;
    assign Hsync = hsync;
    assign Vsync = vsync;
    
    
endmodule
