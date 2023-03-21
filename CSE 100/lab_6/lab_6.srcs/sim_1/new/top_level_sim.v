module top_level_sim();
   
  reg btnL, btnU, btnR, clk;
  wire [3:0] an;
 
 
   
//=======================Start interface your toplevel here =========================   
// TODO: replace "top_lab2" with the name of your top level Lab 2 module.

  top_level UUT (
    .btnL(btnL), .btnU(btnU), .btnR(btnR), .clkin(clk),
    .an(an)
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
  // sum is 0 
	//-------------  Current Time:  0ns
    #2000;  //This advances time by 100 units (ns in this case)
  	btnL = 1'b1;
  	#500
  	btnR = 1'b1;
  	#500
  	btnL = 1'b0;
  	#500
  	btnR = 1'b0;
  	
  	#600;
  	btnL = 1'b1;
  	#500
  	btnR = 1'b1;
  	#500
  	btnL = 1'b0;
  	#500
  	btnR = 1'b0;
  	
  	#600;
  	btnR = 1'b1;
  	#500
  	btnL = 1'b1;
  	#500
  	btnR = 1'b0;
  	#500
  	btnL = 1'b0;
  	
  	#600;
  	btnR = 1'b1;
  	#500
  	btnL = 1'b1;
  	#500
  	btnR = 1'b0;
  	#500
  	btnL = 1'b0;
  	
  	#600;
  	btnR = 1'b1;
  	#500
  	btnL = 1'b1;
  	#500
  	btnR = 1'b0;
  	#500
  	btnL = 1'b0;

  end
endmodule