`timescale 1ns/1ps

module top_level_testbench();
   
  wire [15:0] led;
  wire [6:0] seg;
  wire [3:0] an;
  wire dp;
  reg [15:0] sw;
  reg clk, btnR, btnU, btnD, btnC, btnL; 
 
 
   
//=======================Start interface your toplevel here =========================   
// TODO: replace "top_lab2" with the name of your top level Lab 2 module.

  top_level UUT (
    .sw(sw), .btnR(btnR), .btnU(btnU), .btnD(btnD), .btnC(btnC), .btnL(btnL), .clkin(clk),
    .dp(dp), .led(led), .seg(seg), .an(an)
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
    
    sw[0]=1'b0;
    sw[1]=1'b0;
    sw[2]=1'b0;
    sw[3]=1'b0;
    sw[4]=1'b0;
    sw[5]=1'b0;
    sw[6]=1'b0;
    sw[7]=1'b0;
    sw[8]=1'b0;
    sw[9]=1'b0;
    sw[10]=1'b0;
    sw[11]=1'b0;
    sw[12]=1'b0;
    sw[13]=1'b0;
    sw[14]=1'b0;
    sw[15]=1'b0;
    btnR =1'b0;
    btnU =1'b0;
    btnC =1'b0;
    btnL =1'b0;
    btnD =1'b0;
  // sum is 0 
	//-------------  Current Time:  0ns
    #1000;  //This advances time by 100 units (ns in this case)
    //Din[0] = 1'b1;
    sw[0] = 1'b0;
  	btnL = 1'b1;
  // sum is 1
  // -------------  Current Time:  100ns
    #100;
    #100;
    btnL =1'b0;
    btnU = 1'b1;
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

