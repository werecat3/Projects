// CSE 100/L Fall 2021
// This is a testbench for the entire Lab 2 Project.
// If the top level module in your Lab 2 project is named "top_lab2"
// and you used the suggested names for its inputs/outputs then
// then it will run without modification.  Otherwise follow the instructions
// in the comments marked "TODO" to modify this testbench to conform to your project.
`timescale 1ns/1ps

module state_machine_testbench();
   
  reg btnC, btnU, foursecs, twosecs, R, clk;
  reg [5:0] lb;
  reg [5:0] rb;
  wire shownum, rungame, scored, flashboth, flashalt; //waits, delays, counts, diffs, sames;
 
 
   
//=======================Start interface your toplevel here =========================   
// TODO: replace "top_lab2" with the name of your top level Lab 2 module.

  state_machine UUT (
    .btnC(btnC), .btnU(btnU), .R(R), .foursecs(foursecs),
    .twosecs(twosecs), .lb(lb), .rb(rb), .clk(clk), .shownum(shownum),
    .rungame(rungame), .scored(scored), .flashboth(flashboth), .flashalt(flashalt)
    //.waits(waits), .delays(delays), .counts(counts), .diffs(diffs), .sames(sames)    
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

    btnC=1'b0;
    btnU=1'b0;
    R =1'b0;
    foursecs=1'b0;
    twosecs=1'b0;
    lb=1'b0;
    rb=1'b0;
  // sum is 0 
	//-------------  Current Time:  0ns
    #100;  //This advances time by 100 units (ns in this case)
  	btnC = 1'b1;
  // sum is 1
  // -------------  Current Time:  100ns
    #100;
    btnC = 1'b0;
    twosecs = 1'b1;
  // sum is 2
  // -------------  Current Time:  200ns
    #100;
    twosecs = 1'b0;
    #300;
    btnU = 1'b1;
  // sum is 3
  // -------------  Current Time:  300ns
    #100;
    //sw0 = 1'b0;
    //sw5 = 1'b1;
  // sum is 4
  // -------------  Current Time:  400ns
    #100;
    //sw0 = 1'b1;
  // sum is 5
  // -------------  Current Time:  500ns
    #100;
    //sw1 = 1'b0;
    //sw2 = 1'b1;
  // sum is 6
  // -------------  Current Time:  600ns
    #200;
    //sw1 = 1'b1;
  // sum is 7
  // -------------  Current Time:  700ns
    #100;
    //sw4 = 1'b0;
    //sw5 = 1'b0;
    //sw6 = 1'b1;
  // sum is 8
  // -------------  Current Time:  800ns
    #100;
    //sw4 = 1'b1;
  // sum is 9
  // -------------  Current Time:  900ns
    #100;
    //sw1 = 1'b0;
    //sw2 = 1'b0;
    //sw3 = 1'b1;
  // sum is 10
  // -------------  Current Time:  1000ns

	// TODO: complete this testbentch so that all 16 hex values are generated
  end
endmodule