`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 10/30/2021 09:07:57 PM
// Design Name: 
// Module Name: state_machine
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


module state_machine(
    input btnC,
    input btnU,
    input R,
    input foursecs,
    input twosecs,
    input [7:0] lb,
    input [7:0] rb,
    input clk,
    output resettimer,
    output shownum,
    output rungame,
    output scored,
    output flashboth,
    output waiting,
    output flashalt
    );
    //these are my states
    wire w, delay, count, diff, same;
    wire psw, psd, psc, psdif, pss; //psw = present state w and so forth
    
    assign w = ((psw & ~btnC) | (pss & foursecs) | (psdif & foursecs));
    assign delay = ((psd & ~twosecs) | (psw & btnC));
    assign count = ((psc & ~btnU) | (psd & twosecs));
    assign diff = ((psdif &~foursecs)|(psc &(btnU &((lb[0] ^ rb[0])|(lb[1] ^ rb[1])|(lb[2] ^ rb[2])|(lb[3] ^ rb[3])|(lb[4] ^ rb[4])|(lb[5] ^ rb[5])))));
    assign same = ((pss &~foursecs)|(psc &(btnU &~((lb[0] ^ rb[0])|(lb[1] ^ rb[1])|(lb[2] ^ rb[2])|(lb[3] ^ rb[3])|(lb[4] ^ rb[4])|(lb[5] ^ rb[5])))));
    
    FDRE #(.INIT(1'b1) ) state_wait (.C(clk), .R(R), .CE(1'b1), .D(w), .Q(psw));
    FDRE #(.INIT(1'b0) ) state_delay (.C(clk), .R(R), .CE(1'b1), .D(delay), .Q(psd));
    FDRE #(.INIT(1'b0) ) state_count (.C(clk), .R(R), .CE(1'b1), .D(count), .Q(psc));
    FDRE #(.INIT(1'b0) ) state_diff (.C(clk), .R(R), .CE(1'b1), .D(diff), .Q(psdif));
    FDRE #(.INIT(1'b0) ) state_same (.C(clk), .R(R), .CE(1'b1), .D(same), .Q(pss));
    
    assign resettimer = ~psc;
    assign shownum = psd;
    assign rungame = psc;
    assign scored = pss;
    assign flashboth = pss;
    assign flashalt = psdif;
    assign waiting = psw;
    
    
endmodule




