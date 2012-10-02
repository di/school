.text
	.globl  main
main:
	sub	$sp,$sp,12	# push stack
	sw	$ra,0($sp)	# save return address
	sw	$s0,4($sp)	# save registers
	sw	$s1,8($sp)

# Enable the processor to accept interrupt requests from the
# receiver.
	la	$s1,MASK	# MASK is used to enable interrupts from
				# level 0.
	lwc0	$12,0($s1)	# coprocessor register 12 is the status
				# register.
	la	$s1,0xffff0000	# Address of the receiver control
	li	$s0,2		# Set interrupt enable for the receiver
	sw	$s0,0($s1)
	add	$t0,$zero,$zero	# initialize $t0 to 0.
				# Infinite loop.
Loop:	add	$t0,$t0,$zero	# repeatedly add 0 to $t0
	beq	$t0,$zero,Loop
		
	
	lw	$ra,0($sp)	# restore return address and registers
	lw	$s0,4($sp)
	lw	$s1,8($sp)
	add	$sp,$sp,12	# pop stack
	jr	$ra

.data
MASK:		.word 0x101

# Interrupt handler
	
	.ktext 0x80000080	# address of interrupt handler

				# check cause of exception
	mfc0	$k0,$13		# get cause register
	la	$k1,INT
	lw	$k1,0($k1)	# code for ext. interrupt from level 0
	bne	$k1,$k0,Other

	sw	$s0,save0	# save registers s0,s1
	sw	$s1,save1
	
				# read character
	li	$s0,0xffff0000	# address if receiver control
	lw	$s1,0($s0)	# verify that ready bit is set
	andi	$s1,$s1,1
	beq	$s1,$zero,NotReady
	lb	$k0,4($s0)	# read character from receiver reg

				# check for termination
	li	$k1,113		# ascii value for 'q'
	bne	$k0,$k1,Echo
	li	$v0,10		# exit
	syscall
	
	
Echo:				# echo character read
	li	$s0,0xffff0008	# address of transmitter control
Wait:	lw	$s1,0($s0)	# Read transmitter control reg
	andi	$s1,$s1,1	# get ready bit
	beq	$s1,$zero,Wait	# Wait until ready
	sb	$k0,4($s0)	# write character to terminal

				# return from exception handler
	lw	$s0,save0	# restore registers
	lw	$s1,save1
	mfc0	$k0,$14		# get EPC
	rfe			# restore interrupt state
	jr	$k0		# resume execution prior to interrupt
	
Other:	
	li	$v0,4
	la	$a0,error1
	syscall
	li	$v0,1
	move	$a0,$k0
	syscall
	li	$v0,10
	syscall
NotReady:
	li	$v0,4
	la	$a0,error2
	syscall
	li	$v0,10
	syscall
.data
INT:	.word	256
error1:
	.asciiz "Interrupt encountered:	 "
error2:
	.asciiz "Receiver not ready"
save0:	.word	0
save1:	.word	0


	.text		
	.globl main
main:
	li $v0, 4		# syscall 4 (print_str)
	la $a0, greeting
	syscall
	
	li $s0, 0		#s0 is used for the dummy output
	
	########################################################
	# Use $s4 to hold the current timer value
	########################################################
	li $s4, 0		#initialize timer to zero
	
startUseless:
	lw $t0,LOOPDELAY	#load the delay constant

delay:			#use a busy-wait loop for delay
	sub $t0,$t0,1
	bgtz $t0,delay
		
writePollingMessage:		#write the polling message
	add $s0,$s0,1
	
	li $v0,1		# syscall 1 (print_int)
	move $a0,$s0
	syscall

	li $v0, 4		# syscall 4 (print_str)
	la $a0, waitLabel
	syscall
		
	###########################################
	# FOR POLLING VERSION WRITE A CALL TO A
	# SUBROUTINE TO CHECK IF THERE IS PENDING
	# INPUT, HANDLE IT, AND THEN ECHO RESULTS
	# TO THE CONSOLE
	#
	#
	# jal	checkForTimerCommand
	# 
	# if(pendingTimerCommand == true)
	#    processTimerCommand();
	#    echoNewTimerValueToConsole();
	# }
	##########################################
	
	
	
	j startUseless		# Infinite loop
	


#---------------------
#	Data Segment
#---------------------
	.data

LOOPDELAY: .word 1000000

waitLabel:
	.asciiz ". Just did another wait loop!\n"

greeting:
	.asciiz	"Hello, I like to do useless things.\n"
