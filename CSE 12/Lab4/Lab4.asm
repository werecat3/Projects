###########################################################################################################
# Created by:  Schlosser, Jerret
# 			   Jrschlos
#			   22 February 2021
#
# Assignment:  Lab 4: Syntax checker
#			   CSE 12, computer systems and assembly
#			   UC Santa Cruz, winter 2020
#
# Description: This program will take a use input from the 
#			   program argument, then check to see if it is
#			   in the correct format. Then it will read 
#			   the file and check if all of the braces have
#			   a closing brace.
#
# Notes: 	   This program will run in the MARS IDE
#
# Registers:   a0: changed frequently to whatever is needed there
#			   a1: is where the program argument is first kept
#			   a2-a3: used as counters later on in the code
#  			   v0: used just to get the syscall ready
#			   t2 - t7: I set this to all the types of braces so I could do logic with them
#
##########################################################################################################
# Psuedocode
#	Gets user input for file name
#	checks to see if it is a valid input
#		if bad input, will jump to input error
#	finds the file in computer, opens it
#	reads the inside of the file and stores all the braces on the stack
#	scans through the stack and compares the last entered brace to see if it has an equal and opposit
#		if it finds equal and opposite, it deletes both off stack and then restarts checking
#	counts to see how much stuff is left on the stack and what it is
#		if it is empty it jumps to printing success
#		if it has only 1 brace left it is a mismatch error
#		if it has more than one, then there are many left on the stack
#	after it check to see which it will just to its place to print out the conclusion
#	prints what is needed
#	closes the file
#	end program
##########################################################################################################


.data 
																#all of these will be to print out the words at the end
prompt: .asciiz "You entered the file: \n" 						#the saved string for the intial prompt
errorArgument: .asciiz "ERROR: Invalid program argument. \n "   #the saved string for an error from user input
errorBrace: .asciiz "ERROR - There is a brace mismatch: "		#the saved string for if a mismatch error occurs
indexwords: .asciiz "at index "									#the saved string to insert halfway through the mismatch error
success: .asciiz "SUCCESS: There are "							#the saved string for the beginning of the success print
restofsuccess: .asciiz "pairs of braces."						#the saved string for the middle of the success print
errorLeftover: .asciiz "Error - Brace(s) still on stack: "		#the saved string for the leftovers on stack error

fileName: .word 0												#to make the name of the file an accessible address
buffer: .space 128												#creating the buffer

.text 

promptPrinting:#area of code that sets up the prompts and gets the output window in the correct order
li $v0, 4      #sets v0 to 4 for the syscall
la $a0, prompt #loads the prompt into the adress a0
syscall 	   #prints out the prompt

li $v0 4   	   #sets the v0 to 4 for syscall
lw $a0, ($a1)  #this is getting the word from program arguments
syscall		   #prints out the program argument

li $v0, 11 	   #sets the v0 to 11 for character syscall
la $a0, 10	   #sets the a0 to the character I want which is a \n
syscall		   #prints out a newline
li $v0, 11 	   #sets the v0 to 11 for character syscall
la $a0, 10	   #sets the a0 to the character I want which is a \n
syscall		   #prints out a newline

FirstCharacterValues: #code to set all of the registers to needed values
li $t7, '@'		#sets $t7 to be used for a greater than later on
li $t6, '`'		#sets $t6 to be used for a greater than later on
li $t5, '{'		#sets $t5 to be used for a less than later on
li $t4, '['		#sets $t4 to be used for a less than later on. 
#all of these to say if A < byte < Z or a < byte < z then it is a good input

lw $a0, ($a1)	#loads the input from the program argument into $a0

firstCharacter: 				  #chunk of code that checks the first character
	lb $t1, ($a0)  				  #loads the first byte from the input into $t1
	bgt $t1, $t6, possibleLower   #if the first byte is greater than a, then it might be a lower case letter so jumps to possible lower to check
	bgt $t1, $t7, possibleCapital #if the first byte is greater than A, then it might be a capital letter so jumps to possible capital to check
	j errorMessageInput 		  #if it is less than A, then it will just jump right to the error mesage
	nop 						  #I think you guys know this one so I'm not gonna comment on anymore after this

possibleCapital: 			     #code to see if it is a capital letter
	blt $t1, $t4, checkingLength #if it is less than Z then that means the first byte is between A and Z so a capital letter and that is good
	j errorMessageInput 		 #if it isn't in between that then it is one of the few points in between Z and a which all aren't letters, so it jumps to error
	nop

possibleLower: 					 #code to see if it is a lower case letter
	blt $t1, $t5, checkingLength #if it is less than z then it is in between a and z, thus it is a letter
	j errorMessageInput 	     #if it isn't less than z, then it is one of the few symbols after z, that aren't letters
	nop

checkingLength:   #title just to sort the workspace
	li $t0, 0     # initialize loop-counter
	lw $a0, ($a1) #load the address of the 1st byte

loopToCount:
	lb $t1, ($a0) 					 # load the content of the address stored in $a0
	beq $t1, $zero, nextStep    	 # exit the program if $t0 == null 
	beq $t0, 20, errorMessageInput   # go to error message if the number of character >20    
        
	addi $t0, $t0, 1 				 # increment the loop counter
	addi $a0, $a0, 1 				 # go to next byte      
	j loopToCount   				 #goes back to the top of loop to keep counting until end
	nop
        
errorMessageInput:  		 #jumps here if there is an error message from an input error
	li $v0, 4				 #sets v0 to 4 to print a string
	la $a0, errorArgument 	 #sets a0 to the string errorArgument so it is printed out
	syscall 				 #prints out the string

	li $v0, 10			     #since it is an error it ends here so sets v0 to 10 to end program gracefully
	syscall					 #ends the program
 
nextStep: #this is where the code will jump to in order to get to the code to check the insides of the file

readingFile:       #the beginning of the code for all of the reading of files
lw $a3, ($a1)      #loads the program argument into the a3

li   $v0, 13       # system call for open file
la   $a0, ($a3)    # a0 needs to have the file name so we load a3 into a0
li   $a1, 0        # loads 0 into a1 because that means it will read the file
li   $a2, 0		   # loads 0 into a2 to set the mode, but this doesn't matter here
syscall            # open the file entered in program arguments (file descriptor returned in $v0)
move $s0, $v0      # save the file descriptor 


#this section reads through the file and stores it to the buffer
li   $v0, 14       # system call for read from file
move $a0, $s0      # file descriptor 
la   $a1, buffer   # address of buffer to which to read
li   $a2, 128      # hardcoded buffer length
syscall            # read from file

#but i want to cycle through it so I need to be able to interact with the contents
la $a1, buffer #sets the info in buffer to $a1

loop: #this loops cycles through the contents and adds all braces to the stack and then continues on
li $t7, '['			#
li $t6, '('			#
li $t5, '{'			#all of these are just setting the differ t's to a brace
li $t4, ']'			#so that I can use them for true or falses.
li $t3, ')'			#
li $t2, '}'			#

lb $t1, ($a1)		#loads the first character from the contents of the file into t1

beq $t1, $zero, deletingOffStack   #once it cycles through the entire word from file it leaves
beq $t1, $t7, returnBracket		   #checks if the character is a '[' and if so will add it to the stack
beq $t1, $t6, returnParenthesis    #checks if the character is a '(' and if so will add it to the stack
beq $t1, $t5, returnCurly		   #checks if the character is a '{' and if so will add it to the stack
beq $t1, $t4, returnBracketEnd	   #checks if the character is a ']' and if so will add it to the stack
beq $t1, $t3, returnParenthesisEnd #checks if the character is a ')' and if so will add it to the stack
beq $t1, $t2, returnCurlyEnd	   #checks if the character is a '}' and if so will add it to the stack
j increment						   #if the character is anything other than a brace it will just go to the next byte
nop

increment: 		 	 #this is a place for it to go in order to go to the next byte
	addi $a1, $a1, 1 #increases a1 by one so it is now the next byte
	j loop 			 #jumps back to the top to keep storing braces.
	nop

returnBracket:        #if a '[' is found it will come here to store it
	sw $t1, ($sp)     #stores the byte to the current slot of the stack
	addi $sp, $sp, -4 #moves the pointer to the left one so it is ready for the next byte
	j increment		  #jumps to the increment step to go to the next character
	nop

returnParenthesis: 	  #if a '(' is found it will come here to store it
	sw $t1, ($sp)	  #stores the byte to the current slot of the stack
	addi $sp, $sp, -4 #moves the pointer to the left one so it is ready for the next byte
	j increment 	  #jumps to the increment step to go to the next character
	nop

returnCurly: 	      #if a '{' is found it will come here to store it
	sw $t1, ($sp) 	  #stores the byte to the current slot of the stack
	addi $sp, $sp, -4 #moves the pointer to the left one so it is ready for the next byte
	j increment 	  #jumps to the increment step to go to the next character
	nop

returnBracketEnd: 	  #if a ']' is found it will come here to store it
	sw $t1, ($sp) 	  #stores the byte to the current slot of the stack
	addi $sp, $sp, -4 #moves the pointer to the left one so it is ready for the next byte
	j increment 	  #jumps to the increment step to go to the next character
	nop

returnParenthesisEnd: #if a ')' is found it will come here to store it
	sw $t1, ($sp)	  #stores the byte to the current slot of the stack
	addi $sp, $sp, -4 #moves the pointer to the left one so it is ready for the next byte
	j increment		  #jumps to the increment step to go to the next character
	nop

returnCurlyEnd: 	  #if a '}' is found it will come here to store it
	sw $t1, ($sp)	  #stores the byte to the current slot of the stack
	addi $sp, $sp, -4 #moves the pointer to the left one so it is ready for the next byte
	j increment	      #jumps to the increment step to go to the next character
	nop

deletingOffStack:	  #this is the beginning of a loop that will pop stuff off the stack
	li $a2, -1		  #sets a2 to -1, this number will keep track of the index for any future mismatches
	li $a3, 0  		  #keeps count of braces being broken for if it is a success

smallLoop:		  	  #this is a checkpoint that I can jump to without resetting all of my counters
	addi $sp, $sp, 4  #the sp is currently down really low on the stack so I move it over to get (continues next line)
				   	  #to the first address with stuff in it
	lw $a1, ($sp)	  #loads the word from wherever the pointer is, so I can do logic with the value


	beq $a1, $t4, popBracketEnd     #if the word that's loaded is a ] it will go find a [ to prove it is closed
	beq $a1, $t3, popParenthesisEnd #if the word that's loaded is a ) it will go find a ( to prove it is closed
	beq $a1, $t2, popCurlyEnd       #if the word that's loaded is a } it will go find a { to prove it is closed
	li $t1, '~'						#sets t1 to a very high number that is above all character because it will eventuall count up to
									#a number that is really big that came from storing the buffer awhile ago, it is used as an end point
	bge $a1, $t1, testingMemories   #after it scrolls through the whole stack and sees that everything is popped, it will jump here 
									#in order to see if there is any leftovers and how many leftovers there might be
	j smallLoop						#jumps back up to get to the next slot in the stack and to test it
	nop
popBracketEnd:					     #loop to pop off the full brace pairs
	lw $a1, ($sp)					 #sets a1 to the current slot of the stack
#it will scroll through the stack until it find the next opening brace that it matches
	beq $a1, $t7, deleteBracketStart #once it finds the matching brace it will jump to delete it
	li $t1, '~'						 #sets t1 to really high number so it will stop while going up the stack
	bge $a1, $t1, findError          #once it reaches the top of the stack it will go to a loop to find any errors
	addi $sp, $sp, 4				 #increments the sp so we look through the stack				
	j popBracketEnd					 #jumps back to the top of this loop to keep searching for an opening brace
	nop

deleteBracketStart: 			#this is where the popping occurs
	li $t1, 0       			#sets t1 to zero
	sw $t1, ($sp)   			#stores t1 into the current spot on the stack and thus popping it

deleteBracketEnd:   			#now it need to go back and delete the end brace that we started our search with
addi $sp, $sp, -4   			#used to move back down the stack again
lw $a1, ($sp) 					#stores the current place on the stack to a1
beq $a1, $t4, deleteBracketEnd2 #when it finds the initial end brace, it will jump to delete it
j deleteBracketEnd  			#jumps to the top of this loop to keep searching for the brace
nop

deleteBracketEnd2: 				#this is where the popping occurs again
sw $t1, ($sp)	   				#stores t1 into the current spot on the stack and thus popping it
j count			  			    #jumps to count in order to keep track of the amount of full brace pairs
nop

#----------------------------I started to have large loops so I started using these lines to see the seperation

popParenthesisEnd: 						 #loop to pop off the full brace pairs
	lw $a1, ($sp) 						 #sets a1 to the current slot of the stack
#it will scroll through the stack until it find the next opening brace that it matches
	beq $a1, $t6, deleteParenthesisStart #once it finds the matching brace it will jump to delete it
	li $t1, '~' 						 #sets t1 to really high number so it will stop while going up the stack
	bge $a1, $t1, findError				 #once it reaches the top of the stack it will go to a loop to find any errors
	addi $sp, $sp, 4 					 #increments the sp so we look through the stack
	j popParenthesisEnd					 #jumps back to the top of this loop to keep searching for an opening brace
	nop

deleteParenthesisStart: 				 #this is where the popping occurs
	li $t1, 0 							 #sets t1 to zero
	sw $t1, ($sp) 						 #stores t1 into the current spot on the stack and thus popping it

deleteParenthesisEnd: 					 #now it need to go back and delete the end brace that we started our search with
	addi $sp, $sp, -4 					 #used to move back down the stack again
	lw $a1, ($sp) 	 					 #stores the current place on the stack to a1
	beq $a1, $t3, deleteParenthesisEnd2  #when it finds the initial end brace, it will jump to delete it
	j deleteParenthesisEnd 				 #jumps to the top of this loop to keep searching for the brace
	nop

deleteParenthesisEnd2: 					 #this is where the popping occurs again
	sw $t1, ($sp) 						 #stores t1 into the current spot on the stack and thus popping it
	j count 							 #jumps to count in order to keep track of the amount of full brace pairs

#---------------------------------

popCurlyEnd: 					   #loop to pop off the full brace pairs
	lw $a1, ($sp) 				   #sets a1 to the current slot of the stack
#it will scroll through the stack until it find the next opening brace that it matches
	beq $a1, $t5, deleteCurlyStart #once it finds the matching brace it will jump to delete it
	li $t1, '~' 				   #sets t1 to really high number so it will stop while going up the stack
	bge $a1, $t1, findError 	   #once it reaches the top of the stack it will go to a loop to find any errors
	addi $sp, $sp, 4 			   #increments the sp so we look through the stack
	j popCurlyEnd 				   #jumps back to the top of this loop to keep searching for an opening brace
	nop

deleteCurlyStart: 				   #this is where the popping occurs
	li $t1, 0 					   #sets t1 to zero
	sw $t1, ($sp)    			   #stores t1 into the current spot on the stack and thus popping it

deleteCurlyEnd: 				   #now it need to go back and delete the end brace that we started our search with
	addi $sp, $sp, -4 			   #used to move back down the stack again
	lw $a1, ($sp) 				   #stores the current place on the stack to a1
	beq $a1, $t2, deleteCurlyEnd2  #when it finds the initial end brace, it will jump to delete it
	j deleteCurlyEnd 			   #jumps to the top of this loop to keep searching for the brace
	nop

deleteCurlyEnd2:  #this is where the popping occurs again
	sw $t1, ($sp) #stores t1 into the current spot on the stack and thus popping it
	j count	      #jumps to count in order to keep track of the amount of full brace pairs
	nop

#------------------------------------

count: 			    	#this loop is where everything goes after it is popped and is used to count the number of brace pairs
	addi $a3, $a3, 1    #increments the a3 for each pair
reset: 					#this is a loop to bring the sp back to the top of the stack
	addi $sp, $sp, -4   #repeatedly will add -4 in order to bring it up the stack
	lw $a1, ($sp) 	    #loads the word into a1 to check where it is at
	beqz $a1, smallLoop #once it reaches a slot with zero in it it will restart the popping loop
	j reset             #jump to the top of this loop to keep increasing
	nop


#-------------------------------------

testingMemories: 			      #this tests each memory slot in order to see if any of them have left over stuff in them and 
								  #then decides where to go based off the count
#this part specifically just resets the stack to the top so I can count down from the top
li $t1, 0 						  #sets t1 to zero so that I can count the number of stuff still on the stack
li $t0, '~' 					  #sets t0 to a real high number again for a sort of ceiling
lw $a1, ($sp) 					  #stores the word from memory to a1
bgt $a1, $t0, testingMemoriesLoop #once it reaches the top of the stack it jumps
addi $sp, $sp, 4 				  #increases the sp so I can look at the next slot of memory
j testingMemories 				  #restarts this loop to make sure it goes to the end
nop

testingMemoriesLoop: 			  #this will check if stuff is still on the stack 
addi $sp, $sp, -4 				  #this moves it to the next slot
lw $a1, ($sp) 					  #sets a1 equal to sp
beqz $a1, checkCount 		      #once it reaches a zero which is at the bottom of the stack it jumps
bgtz $a1, addstep 				  #if it is anything other than zero it will move to count it

j testingMemoriesLoop 			  #restarts this loop to keep it moving
nop
 
addstep: 						  #this step adds to the count to figure out how much stuff is left over on the stack
addi $t1, $t1, 1 				  #increases the number to the accurate space
j testingMemoriesLoop 			  #goes back to the top of entire loop
nop

checkCount: 					  #this will check the number of stuff leftover and decide what to do
li $t0, 1 						  #sets t0 to one just for some logic checks
beq $t1, $t0, findError 		  #if it is equal to 1, then there is a mismatch so it goes to find error in order to find the index and what it it
bgt $t1, $t0, printLeftovers 	  #it there is more than 1, then that means there is left overs unmatched, so it goes to print the leftovers
blt $t1, $t0, printSuccess        #if there is nothing left then it is a success so it moves to print that

#-------------------------------------

findError: 			#this will check the entire memory area for any last brace
addi $sp, $sp, -512 #moves the sp down to the very bottom of our memory

searching: 						 	#this will cycle through the whole memory to find the last brace
lw $a1, ($sp)   					#sets a1 = sp for logic
beq $a1, $t7, bracketStartError     #if a [ is found it will see that that one is a mismatch and go print it
beq $a1, $t6, parenthesisStartErorr #if a ( is found it will see that that one is a mismatch and go print it
beq $a1, $t5, curlyStartError       #if a { is found it will see that that one is a mismatch and go print it
beq $a1, $t4, bracketEndError       #if a ] is found it will see that that one is a mismatch and go print it
beq $a1, $t3, parenthesisEndError   #if a ) is found it will see that that one is a mismatch and go print it
beq $a1, $t2, curlyEndError 		#if a } is found it will see that that one is a mismatch and go print it
li $t0, '~'  					    #sets t0 to a real high ceiling
bge $a1, $t0, printSuccess 			#if the ceiling is reached then there actually isn't an error so goes to succeed

addi $sp, $sp, 4					#moves up through the stack one by one
j searching 						#restarts the loop to keep looking
nop

################################################################################################
#comment block for this next part
#after it finds one of the braces left over it will come to one of the related error sections
#it will then count how far from the ceiling the character is in order to find the index.
#then it will move to print out the error for mismatching
################################################################################################

bracketStartError:
resetStepBracketStart:
li $t0, '~'
lw $a1, ($sp)
addi $sp, $sp, 4
bge $a1, $t0, findIndexBracketStart

j resetStepBracketStart
nop

findIndexBracketStart:
addi $sp, $sp, -4
lw $a1, ($sp)
beq $a1, $t7, printIndex

addi $a2, $a2, 1
j findIndexBracketStart
nop

#------------------------------
parenthesisStartErorr:
resetStepParenthesisStart:
li $t0, '~'
lw $a1, ($sp)
addi $sp, $sp, 4
bge $a1, $t0, findIndexParenthesisStart

j resetStepParenthesisStart
nop

findIndexParenthesisStart:
addi $sp, $sp, -4
lw $a1, ($sp)
beq $a1, $t6, printIndex

addi $a2, $a2, 1
j findIndexParenthesisStart
nop

#----------------------------
curlyStartError:
resetStepCurlyStart:
li $t0, '~'
lw $a1, ($sp)
addi $sp, $sp, 4
bge $a1, $t0, findIndexCurlyStart

j resetStepCurlyStart
nop

findIndexCurlyStart:
addi $sp, $sp, -4
lw $a1, ($sp)
beq $a1, $t5, printIndex

addi $a2, $a2, 1
j findIndexCurlyStart
nop
#----------------------------------
bracketEndError:
resetStepBracketEnd:
li $t0, '~'
lw $a1, ($sp)
addi $sp, $sp, 4
bge $a1, $t0, findIndexBracketEnd

j resetStepBracketEnd
nop

findIndexBracketEnd:
addi $sp, $sp, -4
lw $a1, ($sp)
beq $a1, $t4, printIndex

addi $a2, $a2, 1
j findIndexBracketEnd
nop

#----------------------------
parenthesisEndError:
resetStepParenthesisEnd:
li $t0, '~'
lw $a1, ($sp)
addi $sp, $sp, 4
bge $a1, $t0, findIndexParenthesisEnd

j resetStepParenthesisEnd
nop

findIndexParenthesisEnd:
addi $sp, $sp, -4
lw $a1, ($sp)
beq $a1, $t3, printIndex

addi $a2, $a2, 1
j findIndexParenthesisEnd
nop
#----------------------------
curlyEndError:
resetStepCurlyEnd:
li $t0, '~'
lw $a1, ($sp)
addi $sp, $sp, 4
bge $a1, $t0, findIndexCurlyEnd

j resetStepCurlyEnd
nop

findIndexCurlyEnd:
addi $sp, $sp, -4
lw $a1, ($sp)
beq $a1, $t2, printIndex

addi $a2, $a2, 1
j findIndexCurlyEnd
nop

##############################################################################################
#this next section is all of the prints. 
#each one is related to one of the three option of success, error from mismatch, error from leftovers
#there are lines to print out the pre written statements
#then some syscalls to add the necessary spaces in between. 
#then it will jump to close the file and end the program safely
##############################################################################################


#--------------------
printIndex:
li $v0, 4
la $a0, errorBrace
syscall
li $v0, 11
lw $a0, ($sp)
syscall
la $a0, 32
syscall
li $v0, 4
la $a0, indexwords
syscall
li $v0, 1
add $a2, $a2, $a2
la $a0, ($a2)
syscall
li $v0, 11
la $a0, 10
syscall
j exit
nop
#----------------
printLeftovers:
li $v0, 4
la $a0, errorLeftover
syscall


printLeftoversLoop:
li $t1, '~'
lw $a1, ($sp)
beqz $a1, continue
bge $a1, $t1, close

li $v0, 11
la $a0, ($a1)
syscall
continue:
addi $sp, $sp, 4
j printLeftoversLoop
nop

#-------------------
printSuccess:
li $v0, 4
la $a0, success
syscall

li $v0, 1
la $a0, ($a3)
syscall

li $v0, 11
la $a0, 32
syscall

li $v0, 4
la $a0, restofsuccess
syscall

li $v0, 11
li $a0, 10
syscall

exit: 
li $v0, 10
syscall
j close
nop

# Close the file"
close: 
li   $v0, 16       # system call for close file
move $a0, $s0      # file descriptor to close
syscall            # close file

li $v0, 11 	   #sets the v0 to 11 for character syscall
la $a0, 10	   #sets the a0 to the character I want which is a \n
syscall		   #prints out a newline

li $v0, 10     #set to end the program
syscall        #ends it safely







