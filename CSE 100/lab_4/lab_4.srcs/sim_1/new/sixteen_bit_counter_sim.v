// CSE 100/L Fall 2021
// This is a testbench for the entire Lab 2 Project.
// If the top level module in your Lab 2 project is named "top_lab2"
// and you used the suggested names for its inputs/outputs then
// then it will run without modification.  Otherwise follow the instructions
// in the comments marked "TODO" to modify this testbench to conform to your project.
`timescale 1ns/1ps

module counter_testbench();
   
  wire [15:0] Q;
  reg [15:0] Din;
  reg clk, UP, Down, LD; 
  wire UTC, DTC;
 
 
   
//=======================Start interface your toplevel here =========================   
// TODO: replace "top_lab2" with the name of your top level Lab 2 module.

  sixteen_bit_counter UUT (
    .Q(Q), .Din(Din), .clk(clk), .UP(UP), .Down(Down), .LD(LD), .UTC(UTC), .DTC(DTC)
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
		  clk = 1'b1;
        forever
        begin
            #(PERIOD-(PERIOD*DUTY_CYCLE)) clk = ~clk;
        end
    end
  
  // Start sequential portion
  initial
  begin
    
    Din[0]=1'b0;
    Din[1]=1'b0;
    Din[2]=1'b0;
    Din[3]=1'b0;
    Din[4]=1'b0;
    Din[5]=1'b0;
    Din[6]=1'b0;
    Din[7]=1'b0;
    Din[8]=1'b0;
    Din[9]=1'b0;
    Din[10]=1'b0;
    Din[11]=1'b0;
    Din[12]=1'b0;
    Din[13]=1'b0;
    Din[14]=1'b0;
    Din[15]=1'b0;
    UP =1'b0;
    Down =1'b0;
    LD =1'b0;
  // sum is 0 
	//-------------  Current Time:  0ns
    #100;  //This advances time by 100 units (ns in this case)
    //Din[0] = 1'b1;
    Din[0] = 1'b1;
  	LD = 1'b1;
  // sum is 1
  // -------------  Current Time:  100ns
    #100;
    #100;
    LD =1'b0;
    UP = 1'b1;
    #100;
  // sum is 2
  // -------------  Current Time:  200ns
    #100;
  // sum is 3
  // -------------  Current Time:  300ns
    #100;
    #100;
    #100;
    #100;
    #100;
    #100;
    #100;
    #1000;
  // sum is 4
  // -------------  Current Time:  400ns
    

	// TODO: complete this testbentch so that all 16 hex values are generated
  end
endmodule
