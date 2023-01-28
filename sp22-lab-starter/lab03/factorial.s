.globl factorial

.data
n: .word 8

.text
main:
    la t0, n
    lw a0, 0(t0)
    jal ra, factorial

    addi a1, a0, 0
    addi a0, x0, 1
    ecall # Print Result

    addi a1, x0, '\n'
    addi a0, x0, 11
    ecall # Print newline

    addi a0, x0, 10
    ecall # Exit
    
inside_loop:
    add t0, a0, x0
    add t1, a1, x0
    mul t1, t1, t0
    addi t0, t0, -1
    add a0, t0, x0
    add a1, t1, x0
    jalr x0, ra, 0
    
factorial:
    # YOUR CODE HERE
    add s0, a0, x0 # s0 is n
    addi s1, x0, 1 # s1 for result
    loop:
    beq s0, x0, exit
    add a0, s0, x0
    add a1, s1, x0
    addi sp, sp, -4
    sw ra, 0(sp)
#     mul s1, s1, s0
#     addi s0, s0,-1
    jal ra, inside_loop
    lw ra, 0(sp)
    addi sp, sp, 4
    add s0, a0, x0
    add s1, a1, x0
    jal x0, loop
    exit:
    add a0, s1, x0
    jalr x0, ra, 0
