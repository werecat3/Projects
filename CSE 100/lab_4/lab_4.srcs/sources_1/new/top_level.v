`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 10/19/2021 10:32:11 AM
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
    input clkin,
    input btnR,
    input btnU,
    input btnD,
    input btnC,
    input btnL,
    input [15:0] sw,
    output [6:0] seg,
    output dp,
    output [3:0] an,
    output [15:0] led
    );
    
    wire [15:0] Q_counter;
    wire [3:0] Q_ring;
    wire [3:0] H;
    wire DTC, UTC, clk, digsel;
    wire btnc_input;
    wire up_detector_output, down_detector_output;
    
    edge_detector detector_up (.D(btnU), .clk(clk), .CE(1'b1), .Q_final(up_detector_output));
    edge_detector detector_down (.D(btnD), .clk(clk), .CE(1'b1), .Q_final(down_detector_output));
    ring_counter ring_counter (.clk(clk), .CE(digsel), .Q(Q_ring));
    sixteen_bit_counter big_counter (.clk(clk), .UP(up_detector_output | btnc_input), .Down(down_detector_output), .LD(btnL), .Din(sw), .Q(Q_counter), .DTC(DTC), .UTC(UTC));
    selector selector (.N(Q_counter), .sel(Q_ring), .H(H));
    hex7seg segment (.n(H), .seg(seg));
    
    lab4_clks slowit (.clkin(clkin), .greset(btnR), .clk(clk), .digsel(digsel));
    
    assign btnc_input = ~&Q_counter[15:2] & btnC;
    
    //assign led = sw;
    assign led[0] = UTC;
    assign led[15] = DTC;
    assign an[0] = ~Q_ring[0];
    assign an[1] = ~Q_ring[1];
    assign an[2] = ~Q_ring[2];
    assign an[3] = ~Q_ring[3];
    assign dp = (( ~Q_ring[2] & ~DTC) | (~Q_ring[1] & ~UTC));
    
endmodule
