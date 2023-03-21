`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 11/16/2021 11:36:16 AM
// Design Name: 
// Module Name: controller_sim
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


module controller_sim();

  reg btnR, clkin;
  wire Hsync, Vsync; //waits, delays, counts, diffs, sames;
  wire [3:0] vgaGreen, vgaBlue, vgaRed;
 
   
//=======================Start interface your toplevel here =========================   
// TODO: replace "top_lab2" with the name of your top level Lab 2 module.

  vga_controller UUT (
    .btnR(btnR), .clkin(clkin), .Hsync(Hsync), .Vsync(Vsync), .vgaGreen(vgaGreen), .vgaBlue(vgaBlue), .vgaRed(vgaRed) 
  );
// TODO: In the three lines above, make sure the pin names match the names
// used for the inputs/outputs of your top level module.   For example, if you
// used "cin" rather than "sw0" in yout top level module, then replace ".sw0(sw0)" with ".cin(sw0)" 
 
//=======================Stop interface your toplevel here =========================   

    parameter PERIOD = 10;
    parameter real DUTY_CYCLE = 0.5;
    parameter OFFSET = 2;

    initial    // Clock process for clkin
    begin
        #OFFSET
		  clkin = 1'b1;
        forever
        begin
            #(PERIOD-(PERIOD*DUTY_CYCLE)) clkin = ~clkin;
        end
    end 

  // Start sequential portion
  initial
  begin
    btnR =1'b0;
    #500;
    
    
    
    
    end
endmodule
