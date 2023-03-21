############################################################################
# Created by: Schlosser, Jerret
#	          Jrschlos
#	          2 February 2021	      
#
# Assignment: Lab 3: ACSII-risks
#	          CSE 12
#	          UC Santa Cruz, Winter 2020
#
# Description: This program will print a funny pyramid based off 
#	           The number entered by the user
#
# Notes:       This program is run in the Mars IDE
#	           Side notes I didn't really know what to put here
#
# Register usage: t0 - the value of the number entered
#				  t1 - used for keeping track of counting based off input
#				  t2 - used for a loop to make the * and tab before number
#				  t3 - used for a loop to make the * and tab after number
#				  v0 - changes what type of sycall will happen next 
# 			   
###########################################################################
#
# This code will make a pyramid off input of user
# -----------------------------------------------
# print(prompt)
# input ()
# t = input 
# if input <= 0
# print error
# for x in range t
# 	t - 1
#   print *
#   print tab
#   loop back up if t > 0
#   print number
#   loop printing * and tab again
# end program
############################################################################

.data
prompt: .asciiz "Enter the height of the pattern (must be greater than 0):	"
error: .asciiz "Invalid Entry!\n"

.text
start: 		   #start of code so if error I can jump back here to restart
li $t1 1       #sets the value of t1 to 1 as a constant for the loop later
li $v0, 4      #prompt user to enter their number.
la $a0, prompt #calls the sentence related to prompt
syscall 	   #prints the prompt
li $v0, 5      #get the user's number
syscall 	   #sets up the area to enter the user's number
move $t0, $v0  #moves the value from the entry to t0

blez  $t0, printLoopError    #creates error message if zero or smaller is entered

loopstart:					  #start of the loop of adding up to the entered number
	bgt $t1, $t0 printLoopEnd #while less than user number, will loop until greater than user number, then go to end
	move $t2, $t1			  #sets the value of t2 equal to t1 used for as t1 is increased 
	move $t3, $t1			  #sets the value of t3 eqaul to t1 used for as t1 is increased 

asteriksLoop:			  #this loop creates a number of asterisks and tabs equal to the entered number
	
	subi $t2, $t2, 1	  #this takes the number entered and subtracts it by one so the loop knows how many to make
	beqz $t2, printNumber #if the t2 gets subtracted down to 0 it will go to print the number
	li $v0 11			  #set v0 to 11 so sycall 11 happens
	la $a0 42			  #sets a0 to 42 which is the decimal for *
	syscall				  #prints the asterisks
	li $v0 11			  #sets v0 to 11 so sycall works
	la $a0 9			  #sets a0 to 9 whihc is the decimal for tab
	syscall				  #prints the tab
	j asteriksLoop		  #jumps back to the top of this loop so that it can make as many objects as needed
	nop					  #hillal said to do this just in case
	
printNumber:	
	move $a0 $t1   			 #moving the wanted number from $t1 into a0
	li $v0 1       			 #puts it into v0 and gets it ready to print 
	syscall        			 #will look at v0 and then print it as an integer because it is syscall 1
	j astericksLoop2	     #jumps to the second loop so it can print out the second half of the objects
	nop						 #hilla said to do this
	
continuation:				 #this is a label so that I could have a break in the loop so it could leave and then comeback
	addi $t1 $t1 1 			 #increment of t1. syntax set $t1 to $t1 and add by 1
	li $v0 11	  			 #sets $v0 to 11 so that syscall 11 occurs
	li $a0 10				 #makes new lines
	syscall 			 	 #prints out the new line
	j loopstart				 #restarts the entire thing
	nop						 #hillal said to
	
astericksLoop2:			   #this loop creates the second half of objects on the right side of the number
	subi $t3, $t3, 1       #subtracts just like above
	beqz $t3, continuation #once it equals zero and is done making all of the objects it goes back to the counting up loop
	li $v0 11			   #sets syscall to 11
	la $a0 9			   #gets ready to print tab first since it happens first here
	syscall				   #prints the tab
	li $v0 11			   #sets syscall to 11
	la $a0 42			   #gets ready to print the *
	syscall				   #prints the *
	j astericksLoop2       #restarts this loop to create everything needed
	nop  				   #hillal said to


printLoopError:   #where you go if enter an incorrect number
	li $v0, 4     #sets v0 to 4 so it can print string
	la $a0, error #sets the address equal to error 
	syscall       #prints out the error message
	j start    	  #jumps back to top of code
	nop 		  #here to ensure no errors - suggest by hillal
	
printLoopEnd: 	  #where it jumps when the number reaches the entered number
	li $v0 10     #sets v0 to 10 so the sycall 10 can happen
	syscall 	  #makes the program end peacefully




