`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 11/18/2021 12:20:42 PM
// Design Name: 
// Module Name: top_level_sim
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


module top_level_sim();
  reg btnR, btnL, clkin, twos, thrfourth;
 
   
//=======================Start interface your toplevel here =========================   
// TODO: replace "top_lab2" with the name of your top level Lab 2 module.

  top_level UUT (
    .btnR(btnR), .clkin(clkin), .btnL(btnL), .twos(twos), .thrfourth(thrfourth)
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
    btnL = 1'b0;
    twos = 1'b0;
    thrfourth = 1'b0;
    #1000;
    btnL = 1'b1;
    #100;
    btnL = 1'b0;
    #200;
    thrfourth = 1'b1;
    #100;
    thrfourth = 1'b0;
    #200
    twos = 1'b1;
    
    
    
    end
endmodule
