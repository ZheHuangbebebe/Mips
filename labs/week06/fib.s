# MIPS assembler to compute Fibonacci numbers

   .data
msg1:
   .asciiz "n = "
msg2:
   .asciiz "fib(n) = "
msg3:
   .asciiz "n must be > 0"
msg4:
   .asciiz "\n"

   .text

# int main(void)
# {
#    int n;
#    printf("n = ");
#    scanf("%d", &n);
#    if (n >= 1)
#       printf("fib(n) = %d\n", fib(n));
#    else {
#       printf("n must be > 0\n");
#       exit(1);
#    }
#    return 0;
# }

   .globl main
main:
   # prologue
   addi $sp, $sp, -4
   sw   $fp, ($sp)
   move $fp, $sp
   addi $sp, $sp, -4
   sw   $ra, ($sp)

   # function body
   la   $a0, msg1       # printf("n = ");
   li   $v0, 4
   syscall

   li   $v0, 5          # scanf("%d", &n);
   syscall
   move $a0, $v0

   # ... add code to check (n >= 1)
   # ... print an error message, if needed
   # ... and return a suitable value from main()
	li $t9, 1
	bgt $t9, $a0, return

   jal  fib             # $s0 = fib(n);
   nop
   move $s0, $v0

   la   $a0, msg2       # printf((fib(n) = ");
   li   $v0, 4
   syscall

   move $a0, $s0        # printf("%d", $s0);
   li   $v0, 1
   syscall

   la   $a0, msg4
   li   $v0, 4
   syscall

   # epilogue
   lw   $ra, ($sp)
   addi $sp, $sp, 4
   lw   $fp, ($sp)
   addi $sp, $sp, 4
   jr   $ra
return:
	la $a0, msg3
	li $v0, 4
	syscall

	la $a0, msg4
	li $v0, 4
	syscall

   lw   $ra, ($sp)
   addi $sp, $sp, 4
   lw   $fp, ($sp)
   addi $sp, $sp, 4
   jr   $ra

# int fib(int n)
# {
#    if (n < 1)
#       return 0;
#    else if (n == 1)
#       return 1;
#    else
#       return fib(n-1) + fib(n-2);
# }

fib:
	sw $fp, -4($sp)
	sw $ra,-8($sp)
	sw $s0,-12($sp)
	sw $s1,-16($sp)
	la $fp, -4($sp)
	addi $sp,$sp,-16

	move $s0, $a0

	li $t1, 1
	blez $s0, Cond2
	beq $s0,$t1,Cond1

	addi $a0,$s0,-1

	jal fib

	move $s1, $v0

	addi $a0,$s0,-2

	jal fib

	add $v0,$v0,$s1
	exit:

	lw $ra,-4($fp)
	lw $s0,-8($fp)
	lw $s1,-12($fp)
	la $sp, 4($fp)
	lw $fp, ($fp)
	jr $ra

Cond1:
	 li $v0,1
	 j exit
Cond2 :    
	 li $v0,0
	 j exit
