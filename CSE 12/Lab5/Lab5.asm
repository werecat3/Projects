#######################################################
# Created by : Schlosser, Jerret
#			   Jrschlos
#			   9 March 2021
#
# Assignment: Lab 5: Function and Graphics
#			  Cse 12, Computer systems and assembly language
#			  UC Santa Cruz, Winter 2021
#
# Description: This program will take the colors a person wants and 
#			   will print out the picture based off the location and
# 			   color that the user inputs
#
# Notes: This program runs in mars, also my coding might be unconventional
#        but it matched the hex dump so I don't know how to figure out
#		 if it is broken at all.
######################################################
# Psuedocode:
#
# takes a coord
#	breaks the coord into x and y
#	does math to figure out where that coordinate is if its a memory address
#   does whatever is needed with that address whether store color 
#   or find the color and save it for later
#
#
######################################################
# Macros for instructor use (you shouldn't need these)
######################################################

# Macro that stores the value in %reg on the stack 
#	and moves the stack pointer.
.macro push(%reg)
	subi $sp $sp 4
	sw %reg 0($sp)
.end_macro 

# Macro takes the value on the top of the stack and 
#	loads it into %reg then moves the stack pointer.
.macro pop(%reg)
	lw %reg 0($sp)
	addi $sp $sp 4	
.end_macro

#################################################
# Macros for you to fill in (you will need these)
#################################################

# Macro that takes as input coordinates in the format
#	(0x00XX00YY) and returns x and y separately.
# args: 
#	%input: register containing 0x00XX00YY
#	%x: register to store 0x000000XX in
#	%y: register to store 0x000000YY in
.macro getCoordinates(%input, %x, %y)
	li $t7, 0x7ffff120 #my favorite memory slot that i use to break up the coords into two parts
					   #it is way out of the way in the memory so it doesn't accidentally break stuff
	sw %input, ($t7)   #this stores the input, the coordinate, and stores it in the memory slot 
	lh %y, 0($t7)      #this takes the first half of the coordinate and stores it into the wanted slot
	lh %x, 2($t7)	   #this takes the second half of the coordiante and stores it into the wanted slot
.end_macro

# Macro that takes Coordinates in (%x,%y) where
#	%x = 0x000000XX and %y= 0x000000YY and
#	returns %output = (0x00XX00YY)
# args: 
#	%x: register containing 0x000000XX
#	%y: register containing 0x000000YY
#	%output: register to store 0x00XX00YY in
.macro formatCoordinates(%output %x %y)
	#I didn't end up using this at all
.end_macro 

# Macro that converts pixel coordinate to address
# 	output = origin + 4 * (x + 128 * y)
# args: 
#	%x: register containing 0x000000XX
#	%y: register containing 0x000000YY
#	%origin: register containing address of (0, 0)
#	%output: register to store memory address in
.macro getPixelAddress(%output %x %y %origin) 
	lw %output, %origin         #set the output at the origin for the map, a little redudent but ya
	mul %y, %y, 128 			#multiplies the y value by 128
	addu %x, %x, %y				#adds the value of x and y together
	mul %x, %x, 4			    #multiplies the x value by 4
	addu %output, %output, %x	#add the x onto the origin so it is now the coordinate we want in (x, y)
.end_macro

#macro that converts a pixel coordinate that just has a X into an address
.macro getPixelAddressVertical(%output %x %origin)
	#origin + 4 * (x + 128 * y)
	lw %output, %origin		   #set the output at the origin for the map, a little redudent but ya
	mul %x, %x, 4			   #multiplies the x value by 4
	addu %output, %output, %x  #add the x with the origin, so now we have the x coordinate
.end_macro

#macro that converts a pixel coordinate that just has a Y into an address
.macro getPixelAddressHorizontal(%output %y %origin)
	#origin + 4 * (x + 128 * y)
	lw %output, %origin		   #set the output at the origin for the map, a little redudent but ya
	mul %y, %y, 512			   #multiplies the y value by 512
	addu %output, %output, %y  #adds the y with the origin, so now we have the y coordinate
.end_macro

.data
originAddress: .word 0xFFFF0000 #this is the address of (0,0) on the bitmap display

.text
# prevent this file from being run as main
li $v0 10 
syscall

#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#  Subroutines defined below
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#*****************************************************
# Clear_bitmap: Given a color, will fill the bitmap 
#	display with that color.
# -----------------------------------------------------
# Inputs:
#	$a0 = Color in format (0x00RRGGBB) 
# Outputs:
#	No register outputs
#*****************************************************
clear_bitmap: nop
	li $t1, 0xFFFF0000	   #stores the origin address in $t1, this was a rudimentory way to achieve my goals
	smallloop:			   #this is so I can repeatedly paint the bits
	sw $a0, ($t1)		   #this stores the color into a memory slot in order for it to be on the map
	beq $t1, -4, smalljump #this will make it stop paiting once it reaches (128,128) so no error occurs
	addi $t1, $t1, 4	   #this moves to the next address so it can be painted
	j smallloop			   #this repeats the paiting loop
	smalljump:			   #this is where it goes to leave the loop in order continue on
 	jr $ra

#*****************************************************
# draw_pixel: Given a coordinate in $a0, sets corresponding 
#	value in memory to the color given by $a1
# -----------------------------------------------------
#	Inputs:
#		$a0 = coordinates of pixel in format (0x00XX00YY)
#		$a1 = color of pixel in format (0x00RRGGBB)
#	Outputs:
#		No register outputs
#*****************************************************
draw_pixel: nop

	getCoordinates($a0, $t2, $t1)				  #calls the macro getCoordinates, it takes whats in a0 and splits it into t2 and t1
	getPixelAddress($t6, $t2, $t1, originAddress) #takes t2 and t1 and does the math in order to find the coordinate
	sw $a1, ($t6)								  #takes the given color and paints it onto the coordinate found
	jr $ra
	
#*****************************************************
# get_pixel:
#  Given a coordinate, returns the color of that pixel	
#-----------------------------------------------------
#	Inputs:
#		$a0 = coordinates of pixel in format (0x00XX00YY)
#	Outputs:
#		Returns pixel color in $v0 in format (0x00RRGGBB)
#*****************************************************
get_pixel: nop
	getCoordinates($a0, $t2, $t1)				  #calls the macro getCoordinates, it takes whats in a0 and splits it into t2 and t1
	getPixelAddress($t6, $t2, $t1, originAddress) #takes t2 and t1 and does the math in order to find the coordinate
	lw $v0, ($t6)								  #saves the value of the memory, so the color there, for later on.
	jr $ra

#*****************************************************
# draw_horizontal_line: Draws a horizontal line
# ----------------------------------------------------
# Inputs:
#	$a0 = y-coordinate in format (0x000000YY)
#	$a1 = color in format (0x00RRGGBB) 
# Outputs:
#	No register outputs
#*****************************************************
draw_horizontal_line: nop
	getPixelAddressHorizontal($t6, $a0, originAddress) #this will find the y coordinate to start the line from the left side
	li $t1, 0										   #sets t1 to 0 so I can use it to count
	loop1:											   #lets me repeat a loop to keep painting
	beq $t1, 128, smalljump2					       #once it goes 128 spaces the line is complete so it continues down
	sw $a1, ($t6)									   #stores the color into the memory slot in order to paint
	addi $t6, $t6, 4								   #moves to the next address
	addi $t1, $t1, 1								   #ticks up my counter to keep track of how far it went
	j loop1											   #repeats my loop to keep making colors
	smalljump2:										   #an exit route for the loop
 	jr $ra


#*****************************************************
# draw_vertical_line: Draws a vertical line
# ----------------------------------------------------
# Inputs:
#	$a0 = x-coordinate in format (0x000000XX)
#	$a1 = color in format (0x00RRGGBB) 
# Outputs:
#	No register outputs
#*****************************************************
draw_vertical_line: nop

getPixelAddressVertical($t6, $a0, originAddress)  #finds the x coordinate in order to find where to draw the vertical line from
	li $t1, 0									  #sets t1 to 0 so it can be a counter
	loop2:									  	  #let's me repeat a loop to keep painting
	beq $t1, 128, smalljump3					  #will leave the loop once it goes down 128 spaces or the full map
	sw $a1, ($t6)								  #stores the color to the address in order to paint the square
	addi $t6, $t6, 512							  #it needs to go down an entire line so it is increased by 512
	addi $t1, $t1, 1							  #increases counter by 1 each time around
	j loop2										  #restarts the loop all over
smalljump3:										  #the exit route for the loop

 	jr $ra

#*****************************************************
# draw_crosshair: Draws a horizontal and a vertical 
#	line of given color which intersect at given (x, y).
#	The pixel at (x, y) should be the same color before 
#	and after running this function.
# -----------------------------------------------------
# Inputs:
#	$a0 = (x, y) coords of intersection in format (0x00XX00YY)
#	$a1 = color in format (0x00RRGGBB) 
# Outputs:
#	No register outputs
#*****************************************************
draw_crosshair: nop
	push($ra)
	push($s0)
	push($s1)
	push($s2)
	push($s3)
	push($s4)
	push($s5)
	move $s5 $sp

	move $s0 $a0  # store 0x00XX00YY in s0
	move $s1 $a1  # store 0x00RRGGBB in s1
	getCoordinates($a0 $s2 $s3)  # store x and y in s2 and s3 respectively
	
	#I couldn't figure out exactly how to use the $s0 -$s4 registers. I am using t registers in order to save directly
	#to memory so it feels the same and it works so yaaaaaa
	getCoordinates($a0, $t2, $t1)					   #finds the coordinates based off what is in a0
	getPixelAddress($t6, $t2, $t1, originAddress)	   #finds the exact coordinate of the center of the cross hair
	lw $t3, ($t6)									   #stores the color of the of the center dot
	
	getCoordinates($a0, $t2, $t1)					   #finds the coordinates again just to make sure there is no incorrect values

	getPixelAddressHorizontal($t5, $t1, originAddress) #finds teh y coord so it can figure out where to draw the horizontal 
	li $t7, 0										   #sets t7 to 0 so it can be a counter
	loop4:											   #loops like before
	beq $t7, 128, smalljump4						   #once it travels to the other side it leaves the loop
	sw $a1, ($t5)									   #stores the color into the memory address for the color to be painted
	addi $t5, $t5, 4								   #moves over the address to the next one
	addi $t7, $t7, 1								   #increases the counter
	j loop4											   #restarts the loop
	smalljump4:										   #the exit to continue on
		
	getPixelAddressVertical($t4, $t2, originAddress)   #finds the x coord so it can drop down the line from that point
	li $t7, 0										   #sets t7 to 0 so it can be a counter
	loop5:											   #loop again
	beq $t7, 128, smalljump5						   #once it travels to the other side it leaves the loop
	sw $a1, ($t4)									   #saves the color to effective memory address
	addi $t4, $t4, 512								   #moves to the whole next line 
	addi $t7, $t7, 1								   #increases the counter
	j loop5											   #restarts the loop
	smalljump5:										   #the exit route
		
	sw $t3, ($t6)									   #stores the center dot at the original color so there it the hole in the middle

	move $sp $s5
	pop($s5)
	pop($s4)
	pop($s3)
	pop($s2)
	pop($s1)
	pop($s0)
	pop($ra)
	jr $ra
