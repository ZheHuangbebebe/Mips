# board.s ... Game of Life on a 10x10 grid

   .data

N: .word 10  # gives board dimensions

board:
   .byte 1, 0, 0, 0, 0, 0, 0, 0, 0, 0
   .byte 1, 1, 0, 0, 0, 0, 0, 0, 0, 0
   .byte 0, 0, 0, 1, 0, 0, 0, 0, 0, 0
   .byte 0, 0, 1, 0, 1, 0, 0, 0, 0, 0
   .byte 0, 0, 0, 0, 1, 0, 0, 0, 0, 0
   .byte 0, 0, 0, 0, 1, 1, 1, 0, 0, 0
   .byte 0, 0, 0, 1, 0, 0, 1, 0, 0, 0
   .byte 0, 0, 1, 0, 0, 0, 0, 0, 0, 0
   .byte 0, 0, 1, 0, 0, 0, 0, 0, 0, 0
   .byte 0, 0, 1, 0, 0, 0, 0, 0, 0, 0

newBoard: .space 100
# prog.s ... Game of Life on a NxN grid
#
# Needs to be combined with board.s
# The value of N and the board data
# structures come from board.s
#
# Written by <<YOU>>, August 2017

   .data

msg1:
   .asciiz "#Iterations: "

msg2:
   .asciiz "=== After iteration "

msg3:
   .asciiz " === "

msg4:
   .asciiz "\n"
msg5:
   .asciiz "."
msg6:
   .asciiz "#"


   .text
   .globl main
main:
   sw   $fp, -4($sp)
	sw $ra, -8($sp)
	la $fp, -4($sp)
	addi $sp, $sp, -16


	la $a0, msg1    #printf
	li $v0, 4
	syscall

	li $v0, 5       #scanf maxiters
	syscall
	move $a1, $v0

	li $t0, 1		#n = 1

loop1:				#for(int n = 1; n <= maxiters; n++)
	bgt $t0, $a1, end_main
	li $t1, 0		#i = 0
	lw $s0, N		#s0 = N
loop2:				 #for (int i = 0; i < N; i++)
	beq $t1, $s0, end1
	li $t2, 0		#j = 0
loop3:				#for (int j = 0; j < N; j++)
	beq $t2, $s0, end2
	jal neighbours
	move $s1, $v0		#s1 = nn, nn = neighbours[i][j]
	mul $t4, $s0, $t1
	add $t4, $t4, $t2
	li $t5, 1
	lb $t3, board($t4)		#t3 = board[i][j]
	beq $t5, $t3, Cond1		#if(board[i][j] == 1)
	li $t5, 3
	beq $t5, $s1, One		#else if (nn == 3)
	sb $0, newBoard($t4)	#else
	addi $t2, $t2, 1
	j loop3
Cond1:
	li $t5, 2 
	bgt $t5, $s1, Zero		#if (nn < 2)
	beq $t5, $s1, One		#if (nn == 2)
	li $t5, 3				
	beq $t5, $s1, One		#if (nn == 3)
	sb $0, newBoard($t4)	#else
	addi $t2, $t2, 1
	j loop3
end2:
	addi $t1, $t1, 1
	j loop2
end1:
	la $a0, msg2
	li $v0, 4
	syscall
	move $a0, $t0
	li $v0, 1
	syscall
	la $a0, msg3
	li $v0, 4
	syscall
	la $a0, msg4
	li $v0, 4
	syscall
	jal copyBackAndShow
	addi $t0, $t0, 1
	j loop1
Zero:				#newboard[i][j] = 0
	sb $0, newBoard($t4)
	addi $t2, $t2, 1
	j loop3
One:				#newboard[i][j] = 1
	li $t6, 1
	sb $t6, newBoard($t4)
	addi $t2, $t2, 1
	j loop3

end_main:
   lw   $ra, -4($fp)
	la $sp, 4($fp)
	lw $fp, ($fp)
   jr   $ra


# The other functions go here



neighbours:
	sw $fp, -4($sp)
	sw $ra, -8($sp)
	sw $s1, -12($sp)
	sw $s2, -16($sp)
	sw $s3, -20($sp)
	sw $s4, -24($sp)
	sw $s5, -28($sp)
	sw $s6, -32($sp)
	la $fp, -4($sp)
	addi $sp, $sp,-32
	li $s1, 0		#nn = 0
	li $s2, -1		#x = -1
	li $s6, 1
loop4:
	bgt $s2, $s6, end4		#for (int x = -1; x <= 1; x++) 
	li $s3, -1				#y = -1
loop5:
	bgt $s3, $s6, end5		#for (int y = -1; y <= 1; y++) 
	addi $s7, $s0, -1
	add $s4, $t1, $s2
	add $s5, $t2, $s3
	bgt $0, $s4, Continue		#if (i+x < 0 || i+x > N-1) continue;
	bgt $s4, $s7, Continue
	bgt $0, $s5, Continue		#if (j+y < 0 || j+y > N-1) continue;
	bgt $s5, $s7, Continue
	beq $s2, $0, And			#if (x == 0 && y == 0) continue;
	mul $t7, $s4, $s0
	add $t7, $t7, $s5
	lb $t8, board($t7)
	bnez $t8, nn
	addi $s3, $s3, 1
	j loop5
end5:
	addi $s2, $s2, 1
	j loop4
end4:
	move $v0, $s1
	lw $ra, -4($fp)
	lw $s1, -8($fp)
	lw $s2, -12($fp)
	lw $s3, -16($fp)
	lw $s4, -20($fp)
	lw $s5, -24($fp)
	lw $s6, -28($fp)
	la $sp, 4($fp)
	lw $fp, ($fp)
	jr $ra
Continue:
	addi $s3, $s3, 1
	j loop5
And:
	beq $s3, $0, Continue
	mul $t7, $s4, $s0
	add $t7, $t7, $s5
	lb $t8, board($t7)
	bnez $t8, nn
	addi $s3, $s3, 1
	j loop5
nn:					#nn++
	addi, $s1, $s1, 1
	addi $s3, $s3, 1
	j loop5



copyBackAndShow:
	sw $fp, -4($sp)
	sw $ra, -8($sp)
	sw $s1, -12($sp)
	sw $s2, -16($sp)
	sw $s3, -20($sp)
	sw $s4, -24($sp)
	la $fp, -4($sp)
	addi $sp, $sp, -24
	li $s1, 0		#i=0
loop6:
	beq $s1, $s0, end6
	li $s2, 0		#j=0
loop7:
	beq $s2, $s0, end7
	mul $s3, $s0, $s1
	add $s3, $s3, $s2
	lb $s4, newBoard($s3)
	sb $s4, board($s3)
	beq $0, $s4, Char
	la $a0, msg6
	li $v0, 4
	syscall
	addi $s2, $s2, 1
	j loop7
Char:
	la $a0, msg5
	li $v0, 4
	syscall
	addi $s2, $s2, 1
	j loop7
end7:
	la $a0, msg4
	addi $s1, $s1, 1
	la $a0, msg4
	li $v0, 4
	syscall
	j loop6
end6:
	lw $ra, -4($fp)
	lw $s1, -12($fp)
	lw $s2, -16($fp)
	lw $s3, -20($fp)
	lw $s4, -24($fp)
	la $sp, 4($fp)
	lw $fp, ($fp)
	jr $ra
