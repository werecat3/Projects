`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 10/14/2021 12:01:13 PM
// Design Name: 
// Module Name: simulation
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


module simulation(

    
    );
    
    reg [7:0] sw;
    reg clkin, btnL, btnR, btnC;
    wire [3:0] an;
    wire dp;
    wire [6:0] seg;
    
    top_level UUT (.sw(sw), .clkin(clkin), .btnL(btnL), .btnC(btnC),
        .seg(seg), .dp(dp), .an(an)
    );
    
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
	
   initial
   begin
	 // add your (input) stimuli here
	 // to set signal foo to value 0 use
	 // foo = 1'b0;
	 // to set signal foo to value 1 use
	 // foo = 1'b1;
	 //always advance time my multiples of 100ns
	 // to advance time by 100ns use the following line
	sw[0]=1'b0;
    sw[1]=1'b0;
    sw[2]=1'b0;
    sw[3]=1'b0;
    sw[4]=1'b0;
    sw[5]=1'b0;
    sw[6]=1'b0;
    sw[7]=1'b0;
    btnL = 1'b0;
    btnC = 1'b0;
    btnR = 1'b0;
	 #2000;  //This advances time by 100 units (ns in this case)
  	sw[0] = 1'b1;
  	
  	#100;
  	sw[0] = 1'b0;
  	sw[1] = 1'b1;
  	
  	#100;
  	sw[0] = 1'b1;
  	
  	#100;
  	sw[2] = 1'b1;
  	sw[1] = 1'b0;
  	sw[0] = 1'b0;
  	
  	#100;
  	sw[0] = 1'b1;
  	
  	#100;
  	sw[1] = 1'b1;
  	sw[0] = 1'b0;
  	
  	#100;
  	sw[0] = 1'b1;
  	
  	#100;
  	sw[3] = 1'b1;
  	sw[2] = 1'b0;
  	sw[1] = 1'b0;
  	sw[0] = 1'b0;
  	
  	#100;
  	sw[0] = 1'b1;
  	
  	#100;
  	sw[1] = 1'b1;
  	sw[0] = 1'b0;
  	
  	#100;
  	sw[0] = 1'b1;
  	
  	#100;
  	sw[2] = 1'b1;
  	sw[1] = 1'b0;
  	sw[0] = 1'b0;
  	
  	#100;
  	sw[0] = 1'b1;
  	
  	#100;
  	sw[1] = 1'b1;
  	sw[0] = 1'b0;
  	
  	#100;
  	sw[0] = 1'b1;
   
  	#100;
  	sw[3] = 1'b0;
  	sw[2] = 1'b0;
  	sw[1] = 1'b0;
  	btnC = 1'b1;
  	//expected to equal 1
  	#100;
  	sw[1] = 1'b1;
  	btnL = 1'b1;
  	//expected to be 6
 
    
   end
   
endmodule
