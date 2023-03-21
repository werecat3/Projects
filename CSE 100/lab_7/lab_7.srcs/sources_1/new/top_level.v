`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 11/15/2021 07:53:16 AM
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
    input btnL,
    input btnR,
    input clkin,
    input twos,
    input thrfourth,
    output [3:0] an,
    output dp,
    output [6:0] seg,
    output [3:0] vgaGreen,
    output [3:0] vgaBlue,
    output [3:0] vgaRed,
    output Hsync,
    output Vsync,
    output [15:0] led
    );
    //for clock
    wire clk, digsel;
    
    //for displaying and the counter itself
    wire [15:0] Q_counter, Q_time;
    wire gate_passed1, gate_passed2, gate_passed3, gate_passed4;
    wire [3:0] Q_ring;
    wire [3:0] H;
    
    //for state machine
    wire idle, two_sec_b, run_game, loss_idle, going_up, dropping;
    wire two_sec, one_sec, three_fourth_sec, wall_hit, sixteen_f;
    
    //for vga controller and colored spaces
    wire active_h, active_v, hsync, vsync;
    wire [15:0] Q_H, Q_V, Q_bot, Q_top;
    //wire [15:0] Q_wall_L1, Q_wall_L2, Q_wall_L3, Q_wall_L4, Q_wall_R1, Q_wall_R2, Q_wall_R3, Q_wall_4;
    wire width_cube, height_cube, start_cube, point_1, point_2, point_3, point_4;
    wire [15:0] top_cube, bottom_cube, ls_wall_1, rs_wall_1, ls_wall_2, rs_wall_2, ls_wall_3, rs_wall_3, ls_wall_4, rs_wall_4;
    wire [15:0] ls_wall_1I, rs_wall_1I, ls_wall_2I, rs_wall_2I, ls_wall_3I, rs_wall_3I, ls_wall_4I, rs_wall_4I;
    wire [15:0] wall_1_rand, wall_2_rand, wall_3_rand, wall_4_rand;
    //wire [15:0] ost_1, osb_1, ost_2, osb_2, ost_3, osb_3, ost_4, osb_4; 
    wire [15:0] Din_L_1, Din_L_2, Din_L_3, Din_L_4, Din_R_1, Din_R_2, Din_R_3, Din_R_4;
    wire [15:0] ls_reset, rs_reset;
    wire [15:0] gap_1, gap_2, gap_3, gap_4, gap_1I, gap_2I, gap_3I, gap_4I;
    wire [11:0] total_vga, white, turquoise, yellow;
    wire frame_2, frame_4, active_zone;
    wire left_screen, wall_1_res, wall_2_res, wall_3_res, wall_4_res;
    wire wall_1, wall_2, wall_3, wall_4, wall_1og, wall_2og, wall_3og, wall_4og, any_wall, wall_1_gap, wall_2_gap, wall_3_gap, wall_4_gap, any_gap;
    wire ost_1, osb_1, ost_2, osb_2, ost_3, osb_3, ost_4, osb_4, any_o;
    wire [7:0] Q_rand;
    wire [11:0] rand_selected;
    
    //edge detected vsync for time counter
    wire e_vsync, e_btnL, e_gate_passed1, e_gate_passed2, e_gate_passed3, e_gate_passed4;
    
    //clock
    lab7_clks not_so_slow (.clkin(clkin), .greset(btnR), .clk(clk), .digsel(digsel));
    
    //edge detected btnl so that holding the button doesn't keep increasing
    edge_detector btnl_edge (.D(btnL), .clk(clk), .CE(1'b1), .Q_final(e_btnL));
    
    //edge detected vsync to use as qsec
    edge_detector vsync_edge (.D(~vsync), .clk(clk), .CE(1'b1), .Q_final(e_vsync));
    //the time counter used to get different times
    sixteen_bit_counter time_counter (.clk(clk), .R(btnR | idle | btnL), .UP(e_vsync), .Down(1'b0), .LD(1'b0), .Din(16'b0), .Q(Q_time));
    assign two_sec = Q_time[7];
    assign one_sec = Q_time[6];
    assign three_fourth_sec = Q_time[5] & Q_time[4];
    assign sixteen_f = Q_time[4];
    //my state machine used for obvious purposes
    state_machine my_baby (.clk(clk), .btnL(e_btnL), .btnR(btnR), .two_sec(two_sec), .sixteen_f(sixteen_f), .wall_hit(wall_hit),
    .idle(idle), .two_sec_b(two_sec_b), .run_game(run_game), .loss_idle(loss_idle), .going_up(going_up), .dropping(dropping)
    );
    
    vga_controller controller (.clk(clk), .btnR(btnR), .Hsync(Hsync), .Vsync(Vsync), .active_h(active_h),
    .active_v(active_v), .Q_H(Q_H), .Q_V(Q_V), .hsync(hsync), .vsync(vsync)
    );
    
  
    
    //starting position for the cube
    assign width_cube = (Q_H > 12'b000010100000 & Q_H < 12'b000010110000);
    //use counter to adjust the cube place or maybe just add shit
    assign top_cube = 12'b000100000000;
    assign bottom_cube = 12'b000011110000;
    assign height_cube = (Q_V > Q_top & Q_V < Q_bot);
    assign start_cube = width_cube & height_cube;
    assign point_1 = (Q_V == 12'b000000000001) && (Q_H == 12'b000000000001);
    assign point_2 = (Q_V == 12'b000000010000) && (Q_H == 12'b000000010000);
    assign point_3 = (Q_V == 12'b000010000000) && (Q_H == 12'b000010000000);
    assign point_4 = (Q_V == 12'b010000000000) && (Q_H == 12'b010000000000);
    assign frame_2 = point_1 | point_2;
    assign frame_4 = point_1 | point_2 | point_3 | point_4;
    assign active_zone = active_h & active_v;
    
    
    //randomly select one of the wall options whenever it reaches the left wall
    //each wall is 160 px from the left side of one wall to the left of another
    assign ls_wall_1I = (12'b000100000100);
    assign rs_wall_1I = (12'b000100110100);
    assign wall_1 = (Q_H > ls_wall_1 & Q_H < rs_wall_1) & ~wall_1_gap & ~ost_1 & ~osb_1;
    assign wall_1og = (Q_H > ls_wall_1 & Q_H < rs_wall_1);
    assign wall_1_gap = ((Q_V > (wall_1_rand - 16'b0000000000111100)) & (Q_V < (wall_1_rand + 16'b0000000000111100))) & wall_1og;
    assign ost_1 = ((Q_V >= (wall_1_rand - 16'b0000000001101100)) & (Q_V <= (wall_1_rand - 16'b0000000000111100)))& wall_1og;
    assign osb_1 = ((Q_V <= (wall_1_rand + 16'b0000000001101100)) & (Q_V >= (wall_1_rand + 16'b0000000000111100)))& wall_1og;
    assign ls_wall_2I = (12'b000110100100);
    assign rs_wall_2I = (12'b000111010100);
    assign wall_2 = (Q_H > ls_wall_2 & Q_H < rs_wall_2) & ~wall_2_gap & ~ost_2 & ~osb_2;
    assign wall_2og = (Q_H > ls_wall_2 & Q_H < rs_wall_2);
    assign wall_2_gap = ((Q_V > (wall_2_rand - 16'b0000000000111100)) & (Q_V < (wall_2_rand + 16'b0000000000111100))) & wall_2og;
    assign ost_2 = ((Q_V >= (wall_2_rand - 16'b0000000001101100)) & (Q_V <= (wall_2_rand - 16'b0000000000111100)))& wall_2og;
    assign osb_2 = ((Q_V <= (wall_2_rand + 16'b0000000001101100)) & (Q_V >= (wall_2_rand + 16'b0000000000111100)))& wall_2og;
    assign ls_wall_3I = (12'b001001000100);
    assign rs_wall_3I = (12'b001001110100);
    assign wall_3 = (Q_H > ls_wall_3 & Q_H < rs_wall_3) & ~wall_3_gap & ~ost_3 & ~osb_3;
    assign wall_3og = (Q_H > ls_wall_3 & Q_H < rs_wall_3);
    assign wall_3_gap = ((Q_V > (wall_3_rand - 16'b0000000000111100)) & (Q_V < (wall_3_rand + 16'b0000000000111100))) & wall_3og;
    assign ost_3 = ((Q_V >= (wall_3_rand - 16'b0000000001101100)) & (Q_V <= (wall_3_rand - 16'b0000000000111100)))& wall_3og;
    assign osb_3 = ((Q_V <= (wall_3_rand + 16'b0000000001101100)) & (Q_V >= (wall_3_rand + 16'b0000000000111100)))& wall_3og;
    assign ls_wall_4I = (12'b001011100100);
    assign rs_wall_4I = (12'b001100010100);
    assign wall_4 = (Q_H > ls_wall_4 & Q_H < rs_wall_4) & ~wall_4_gap & ~ost_4 & ~osb_4;
    assign wall_4og = (Q_H > ls_wall_4 & Q_H < rs_wall_4);
    assign wall_4_gap = ((Q_V > (wall_4_rand - 16'b0000000000111100)) & (Q_V < (wall_4_rand + 16'b0000000000111100))) & wall_4og;
    assign ost_4 = ((Q_V >= (wall_4_rand - 16'b0000000001101100)) & (Q_V <= (wall_4_rand - 16'b0000000000111100)))& wall_4og;
    assign osb_4 = ((Q_V <= (wall_4_rand + 16'b0000000001101100)) & (Q_V >= (wall_4_rand + 16'b0000000000111100)))& wall_4og;
    assign any_gap = wall_1_gap | wall_2_gap | wall_3_gap | wall_4_gap;
    assign any_wall = wall_1 | wall_2 | wall_3 | wall_4;
    assign any_o = ost_1 | osb_1 | ost_2 | osb_2 | ost_3 | osb_3 | ost_4 | osb_4;
    
    
    //assing block =(start_cube & idle ? white[11:8] : 4'b0)
    assign white = 12'hfff;
    assign turquoise = 12'h0ff;
    assign yellow = 12'hff0;
    assign total_vga = 12'h00f;
    assign vgaBlue = (start_cube & ~any_o & ~any_wall & idle & active_zone ? white[3:0] : 4'b0) | ((two_sec_b | loss_idle) & ~any_o & ~any_wall & start_cube & three_fourth_sec ? white[3:0] : 4'b0) | 
    (start_cube & ~any_o & ~any_wall & active_zone & (run_game | going_up) ? white[3:0] : 4'b0) | (any_wall & ~start_cube & ~any_o & active_zone ? turquoise[3:0] : 4'b0)
    | (any_o & ~any_wall & ~start_cube & active_zone ? yellow[3:0] : 4'b0);
    assign vgaGreen = (start_cube & ~any_o & ~any_wall & idle & active_zone ? white[7:4] : 4'b0) | ((two_sec_b | loss_idle) & ~any_o & ~any_wall & start_cube & three_fourth_sec ? white[7:4] : 4'b0) | 
    (start_cube & ~any_o & ~any_wall & active_zone & (run_game | going_up) ? white[7:4] : 4'b0) | (any_wall & ~start_cube & ~any_o & active_zone ? turquoise[7:4] : 4'b0)
    | (any_o & ~any_wall & ~start_cube & active_zone ? yellow[7:4] : 4'b0);
    assign vgaRed = (start_cube & ~any_o & ~any_wall & idle & active_zone ? white[11:8] : 4'b0) | ((two_sec_b | loss_idle) & ~any_o & ~any_wall & start_cube & three_fourth_sec ? white[11:8] : 4'b0) | 
    (start_cube & ~any_o & ~any_wall & active_zone & (run_game | going_up) ? white[11:8] : 4'b0) | (any_wall & ~start_cube & ~any_o & active_zone ? turquoise[11:8] : 4'b0)
    | (any_o & ~any_wall & ~start_cube & active_zone ? yellow[11:8] : 4'b0);
    
    //& (~any_gap | ~any_o) for up above
    
    
    
    
    
    //control ball going up using a counter. use the down and making it go down once every 4 frames 
    sixteen_bit_counter top_block (.clk(clk), .R(1'b0), .UP(run_game & (frame_2)), .Down(going_up & (frame_4)), .LD(idle | two_sec_b), .Din(16'b0000000011110000), .Q(Q_top));
    sixteen_bit_counter bot_block (.clk(clk), .R(1'b0), .UP(run_game & (frame_2)), .Down(going_up & (frame_4)), .LD(idle | two_sec_b), .Din(16'b0000000100000000), .Q(Q_bot));
    
    //walls counters
    sixteen_bit_counter Ls_wall_1 (.clk(clk), .R(1'b0), .UP(1'b0), .Down((run_game | going_up) & (frame_2)), .LD(wall_1_res | idle | two_sec_b), .Din(Din_L_1), .Q(ls_wall_1));
    sixteen_bit_counter Rs_wall_1 (.clk(clk), .R(1'b0), .UP(1'b0), .Down((run_game | going_up) & (frame_2)), .LD(wall_1_res | idle | two_sec_b), .Din(Din_R_1), .Q(rs_wall_1));
    sixteen_bit_counter Ls_wall_2 (.clk(clk), .R(1'b0), .UP(1'b0), .Down((run_game | going_up) & (frame_2)), .LD(wall_2_res | idle | two_sec_b), .Din(Din_L_2), .Q(ls_wall_2));
    sixteen_bit_counter Rs_wall_2 (.clk(clk), .R(1'b0), .UP(1'b0), .Down((run_game | going_up) & (frame_2)), .LD(wall_2_res | idle | two_sec_b), .Din(Din_R_2), .Q(rs_wall_2));
    sixteen_bit_counter Ls_wall_3 (.clk(clk), .R(1'b0), .UP(1'b0), .Down((run_game | going_up) & (frame_2)), .LD(wall_3_res | idle | two_sec_b), .Din(Din_L_3), .Q(ls_wall_3));
    sixteen_bit_counter Rs_wall_3 (.clk(clk), .R(1'b0), .UP(1'b0), .Down((run_game | going_up) & (frame_2)), .LD(wall_3_res | idle | two_sec_b), .Din(Din_R_3), .Q(rs_wall_3));
    sixteen_bit_counter Ls_wall_4 (.clk(clk), .R(1'b0), .UP(1'b0), .Down((run_game | going_up) & (frame_2)), .LD(wall_4_res | idle | two_sec_b), .Din(Din_L_4), .Q(ls_wall_4));
    sixteen_bit_counter Rs_wall_4 (.clk(clk), .R(1'b0), .UP(1'b0), .Down((run_game | going_up) & (frame_2)), .LD(wall_4_res | idle | two_sec_b), .Din(Din_R_4), .Q(rs_wall_4));
    
    
    assign wall_1_res = (ls_wall_1 == 16'b0000000000000000);
    assign wall_2_res = (ls_wall_2 == 16'b0000000000000000);
    assign wall_3_res = (ls_wall_3 == 16'b0000000000000000);
    assign wall_4_res = (ls_wall_4 == 16'b0000000000000000);
    
    //hard code to where i want them to reset to
    assign ls_reset = 16'b0000001010000000;
    assign rs_reset = 16'b0000001010110000;
    
    //mux to control current load
    assign Din_L_1 = idle | two_sec_b ? ls_wall_1I : ls_reset;
    assign Din_R_1 = idle | two_sec_b ? rs_wall_1I : rs_reset;
    assign Din_L_2 = idle | two_sec_b ? ls_wall_2I : ls_reset;
    assign Din_R_2 = idle | two_sec_b ? rs_wall_2I : rs_reset;
    assign Din_L_3 = idle | two_sec_b ? ls_wall_3I : ls_reset;
    assign Din_R_3 = idle | two_sec_b ? rs_wall_3I : rs_reset;
    assign Din_L_4 = idle | two_sec_b ? ls_wall_4I : ls_reset;
    assign Din_R_4 = idle | two_sec_b ? rs_wall_4I : rs_reset;
    
    //random number for holes
    random_number_gen random_gap (.clk(clk), .reset(btnR), .CE(run_game), .Q(Q_rand));
    //use the right 4 bits of lsfr. use that to select between -112, -96, -80, -64, -48, -32, -16, 0, 16, 32, 48, 64, 80, 96, 112
    mux_15to1_8 gap_selector (.sel(Q_rand[3:0]), .o(rand_selected));
    //3 to 1 mux with the output being a 7 bit bus. us two to 1 8 bit bus but add third selector.
    //have lsfr constantly running then whenever wall resets it loads the value into the counter for each gap
    //each gap will have 16 bit counter that only uses load. this will save the gap for the entire screen until it resets again
    sixteen_bit_counter Gap_1 (.clk(clk), .R(1'b0), .UP(1'b0), .Down(1'b0), .LD(wall_1_res | idle | two_sec_b), .Din(gap_1), .Q(wall_1_rand));
    sixteen_bit_counter Gap_2 (.clk(clk), .R(1'b0), .UP(1'b0), .Down(1'b0), .LD(wall_2_res | idle | two_sec_b), .Din(gap_2), .Q(wall_2_rand));
    sixteen_bit_counter Gap_3 (.clk(clk), .R(1'b0), .UP(1'b0), .Down(1'b0), .LD(wall_3_res | idle | two_sec_b), .Din(gap_3), .Q(wall_3_rand));
    sixteen_bit_counter Gap_4 (.clk(clk), .R(1'b0), .UP(1'b0), .Down(1'b0), .LD(wall_4_res | idle | two_sec_b), .Din(gap_4), .Q(wall_4_rand));
    
    assign gap_1 = idle | two_sec_b ? gap_1I : {4'b0000, rand_selected};
    assign gap_2 = idle | two_sec_b ? gap_2I : {4'b0000, rand_selected};
    assign gap_3 = idle | two_sec_b ? gap_3I : {4'b0000, rand_selected};
    assign gap_4 = idle | two_sec_b ? gap_4I : {4'b0000, rand_selected};
    
    assign gap_1I = 16'b0000000100001110;
    assign gap_2I = 16'b0000000011110100;
    assign gap_3I = 16'b0000000011001011;
    assign gap_4I = 16'b0000000011010111;
    
    //the wall hit maybe
    assign wall_hit = (start_cube & (any_wall | any_o)) | (start_cube & (Q_V == 12'b000000000000)) | (start_cube & (Q_V == 12'b000111100000));
    
    //assign gate_passed = (((Q_V == 12'b000100000000) && (Q_H == 12'b000010100000)) & (Q_H == (rs_wall_1 | rs_wall_2  | rs_wall_3 | rs_wall_4))); //
    assign gate_passed1 = (rs_wall_1 <= 12'b000010100000) & (rs_wall_1 >= 12'b000010011100);
    assign gate_passed2 = (rs_wall_2 <= 12'b000010100000) & (rs_wall_2 >= 12'b000010011100);
    assign gate_passed3 = (rs_wall_3 <= 12'b000010100000) & (rs_wall_3 >= 12'b000010011100);
    assign gate_passed4 = (rs_wall_4 <= 12'b000010100000) & (rs_wall_4 >= 12'b000010011100);
    edge_detector gate_passing0 (.D(gate_passed1), .clk(clk), .CE(1'b1), .Q_final(e_gate_passed1));
    edge_detector gate_passing1 (.D(gate_passed2), .clk(clk), .CE(1'b1), .Q_final(e_gate_passed2)); 
    edge_detector gate_passing2 (.D(gate_passed3), .clk(clk), .CE(1'b1), .Q_final(e_gate_passed3)); 
    edge_detector gate_passing3 (.D(gate_passed4), .clk(clk), .CE(1'b1), .Q_final(e_gate_passed4));  
    
    //counter 
    sixteen_bit_counter score (.clk(clk), .UP((e_gate_passed1 | e_gate_passed2 | e_gate_passed3 | e_gate_passed4) & (run_game | going_up)), .LD(1'b0), .Down(1'b0), .R(btnR), .Din(1'b0), .Q(Q_counter)); 
    
    //ring counter for anodes
    ring_counter ring_counter (.clk(clk), .CE(digsel), .Q(Q_ring));
    
    //displaying stuff
    selector selector (.N(Q_counter), .sel(Q_ring), .H(H));
    hex7seg segment (.n(H), .seg(seg));
    assign an[0] = ~((Q_ring[0] & ~loss_idle) | (Q_ring[0] & loss_idle & three_fourth_sec));
    assign an[1] = ~((Q_ring[1] & ~loss_idle) | (Q_ring[1] & loss_idle & three_fourth_sec));
    assign an[2] = ~((Q_ring[2] & ~loss_idle) | (Q_ring[2] & loss_idle & three_fourth_sec));
    assign an[3] = ~((Q_ring[3] & ~loss_idle) | (Q_ring[3] & loss_idle & three_fourth_sec));
    assign dp = 1'b1;
    assign led[0] = idle;
    assign led[1] = two_sec_b;
    assign led[2] = run_game;
    assign led[3] = loss_idle;
    assign led[6] = going_up;
    assign led[7] = e_btnL;
    
    
    
endmodule
