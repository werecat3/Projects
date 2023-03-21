`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 11/18/2021 11:06:17 AM
// Design Name: 
// Module Name: state_machine_sim
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


module state_machine_sim();

  reg btnR, btnL, clkin, two_sec, wall_hit, sixteen_f;
  wire idle, two_sec_b, run_game, loss_idle;
 
   
//=======================Start interface your toplevel here =========================   
// TODO: replace "top_lab2" with the name of your top level Lab 2 module.

  state_machine UUT (
    .btnR(btnR), .clk(clkin), .btnL(btnL), .two_sec(two_sec), .wall_hit(wall_hit), .idle(idle), .two_sec_b(two_sec_b), 
    .run_game(run_game), .loss_idle(loss_idle), .sixteen_f(sixteen_f) 
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
    two_sec = 1'b0;
    wall_hit = 1'b0;
    sixteen_f = 1'b0;
    #500;
    btnL = 1'b1;
    #50;
    btnL = 1'b0;
    #50;
    two_sec = 1'b1;
    #100;
    two_sec = 1'b0;
    #100;
    btnL = 1'b1;
    #50;
    #500;
    sixteen_f = 1'b1;
    #200
    wall_hit = 1'b1;
    #50;
    wall_hit = 1'b0;
    
    
    
    end
endmodule
