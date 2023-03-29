# sp22-lab

## lab - 03

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

## lab - 04
Make sure you have prologue and epilogue of each function since the registers are used later in the main function which expect the states of the registers to be the same.

## lab - 05
For excercise 2, here is the truth table for 4-select MUX
```
S1 S2 O
0  0  A    
0  1  C
1  0  B
1  1  D
```
For excersise 4, implement all the shifters using splitters, then use MUX to in the main cercuit to parse AMOUNT for each bit and rotate

## lab - 08

For excercise 3, we can follow the following step inside the inner loop
```
/* Loading four elements of arr into __m128i type */
loaded_arr = _mm_loadu_si128((__m128i *) (arr + i))
/* Comparing the four elements against the condition */
mask = __mm_cmpgt_epi32(loaded_arr, _127)
/* Applying above mask over the loaded arr */
filtered_arr = _mm_and_si128(mask, loaded_arr)
/* Summing the above with prev rolling sum */
sum_arr = _mm_add_epi32(sum_arr, filtered_arr)
```
Also, noting that degree of loop unrolling reduces the amount of time program takes!
