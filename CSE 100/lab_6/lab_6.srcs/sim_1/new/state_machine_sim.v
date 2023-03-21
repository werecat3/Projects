module state_machine_sim();
   
  reg btnL, btnU, btnR, sec_15, clk;
  wire LTR, RTL, idle; //waits, delays, counts, diffs, sames;
 
 
   
//=======================Start interface your toplevel here =========================   
// TODO: replace "top_lab2" with the name of your top level Lab 2 module.

  state_machine UUT (
    .btnL(btnL), .btnU(btnU), .btnR(btnR),
    .sec_15(sec_15), .LTR(LTR), .RTL(RTL), .clk(clk), .idle(idle)  
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

    btnL=1'b0;
    btnU=1'b0;
    btnR =1'b0;
    sec_15=1'b0;
  // sum is 0 
	//-------------  Current Time:  0ns
    #1000;  //This advances time by 100 units (ns in this case)
  	btnL = 1'b1;
  // sum is 1
  // -------------  Current Time:  100ns
    #100;
    btnR = 1'b1;
  // sum is 2
  // -------------  Current Time:  200ns
    #100;
    btnR = 1'b0;
    #100;
    btnR = 1'b1;
  // sum is 3
  // -------------  Current Time:  300ns
    #100;
    btnL = 1'b0;
    //sw0 = 1'b0;
    //sw5 = 1'b1;
  // sum is 4
  // -------------  Current Time:  400ns
    #100;
    btnR = 1'b0;
    //sw0 = 1'b1;
  // sum is 5
  // -------------  Current Time:  500ns
    #1000;
    btnR = 1'b1;
    #100;
    btnL = 1'b1;
    #100
    btnL = 1'b0;
    #100
    btnL = 1'b1;
    #100
    btnR = 1'b0;
    #100
    btnL = 1'b0;
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