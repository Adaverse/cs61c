# sp22-lab

## lab-03

In exercise 5, need to make sure to save the value of s0 accross function calls of ```map``` since it is being used by ```print_list``` later which is being called in ```main```.
```
main:
  # some code
  # Print the squared list
  add a0, s0, x0
  jal ra, print_list
  
  # some code 
  # Print decremented list
  add a0, s0, x0
  jal ra, print_list
  jal ra, print_newline
  
map:
  # Prologue
  addi sp, sp, -8
  sw ra, 0(sp)
  sw s0, 4(sp)
  
  # some code
  
  # Epilogue
  lw ra, 0(sp)
  lw s0, 4(sp)
  addi sp, sp, 8
  
  jalr x0, ra, 0
```
