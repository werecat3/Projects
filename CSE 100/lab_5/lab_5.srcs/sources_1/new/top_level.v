`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 10/30/2021 09:08:41 PM
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
    input btnU,
    input btnC,
    input clkin,
    input btnR,
    output [15:0] led,
    output [3:0] an,
    output dp,
    output [6:0] seg
    );
    
    wire digsel, qsec, clk;
    wire btnU_sync, btnC_sync;
    wire [3:0] Q_ring;
    wire [7:0] Q_game;
    wire [7:0] Q_time;
    wire [7:0] Q_rand;
    wire [15:0] led;
    wire foursecs, twosecs, resettimer, shownum, rungame, scored, edgescored, flashboth, flashalt, waiting;
    wire [5:0] lb;
    wire [5:0] rb;
    wire [3:0] display;
    
    wire [7:0] Q_rand8;
    wire [7:0] Q_game8;
    wire [15:0] Q_select;
    
    //counter which constantly counts up while in count state
    eight_bit_counter game_counter (.clk(clk), .R(btnR | btnC), .CE(rungame & qsec), .Q(Q_game));
    assign rb[5:0] = Q_game[5:0];
    assign Q_game8 = {1'b0, 1'b0, rb};
    //shifter which will keep making random numbers until it leaves the waiting stage
    //then it stops on a number in order to be used
    random_number_gen rand (.clk(clk), .reset(btnR), .CE(waiting), .Q(Q_rand));
    //takes the random number and cuts off the left most 2 bits
    assign lb[5:0] = Q_rand[5:0];
    //puts back into an 8 bit number with the left two bits being zero
    assign Q_rand8 = {1'b0, 1'b0, lb};
    //puts two 8 bits into a 16 bit for the selector
    assign Q_select = {Q_rand8, Q_game8};
    
    //idea to synchronize the btnc and u inputs
    FDRE #(.INIT(1'b0) ) btnU_synchronizer (.C(clk), .R(btnR), .CE(1'b1), .D(btnU), .Q(btnU_sync));
    FDRE #(.INIT(1'b0) ) btnC_synchronizer (.C(clk), .R(btnR), .CE(1'b1), .D(btnC), .Q(btnC_sync));
    
    //this mess is my state machine I am sorry
    state_machine my_baby (.btnC(btnC_sync), .btnU(btnU_sync), .R(btnR), .foursecs(foursecs), .twosecs(twosecs),
    .lb(lb), .rb(rb), .clk(clk), .resettimer(resettimer), .shownum(shownum), .rungame(rungame), .scored(scored), 
    .flashboth(flashboth), .flashalt(flashalt), .waiting(waiting)
    );
    
    //this is a counter which creates the 2 second and 4 second input. it is reset each time
    //the seconds is needed so there is no confusion in the machine
    eight_bit_counter time_counter (.clk(clk), .R(btnR | btnC | btnU), .CE(qsec), .Q(Q_time));
    assign foursecs = Q_time[4];
    assign twosecs = Q_time[3];
    
    //just same ring counter as last lab
    ring_counter ring_counter (.clk(clk), .CE(digsel), .Q(Q_ring));
    
    //will shift in a 1 everytime that scored is 1
    edge_detector scored_detect (.D(scored), .clk(clk), .CE(1'b1), .Q_final(edgescored));
    LED_shifter leds (.In(1'b1), .CE(edgescored), .R(btnR), .clk(clk), .Q(led));
    
    //um the clock lol
    lab5_clks slowit (.clkin(clkin), .greset(btnR), .clk(clk), .digsel(digsel), .qsec(qsec));
    
    //selector 
    selector selector (.N(Q_select), .sel(Q_ring), .H(display));
    hex7seg segments (.n(display) , .seg(seg));
    
    //this changes based off if it won or not
    assign an[0] = (~Q_ring[0]) | (Q_ring[0] & Q_time[0] & flashboth) | (Q_ring[0] & ~Q_time[0] & flashalt);
    assign an[1] = (~Q_ring[1]) | (Q_ring[1] & Q_time[0] & flashboth) | (Q_ring[1] & ~Q_time[0] & flashalt);
    assign an[2] = (waiting | ~(~waiting & Q_ring[2])) | (Q_ring[2] & Q_time[0] & flashboth) | (Q_ring[2] & Q_time[0] & flashalt);
    assign an[3] = (waiting | ~(~waiting & Q_ring[3])) | (Q_ring[3] & Q_time[0] & flashboth) | (Q_ring[3] & Q_time[0] & flashalt);
    assign dp = 1'b1;
endmodule
