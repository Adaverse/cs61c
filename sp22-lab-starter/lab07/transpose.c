#include "transpose.h"

/* The naive transpose function as a reference. */
void transpose_naive(int n, int blocksize, int *dst, int *src) {
    for (int x = 0; x < n; x++) {
        for (int y = 0; y < n; y++) {
            dst[y + x * n] = src[x + y * n];
        }
    }
}

/* Implement cache blocking below. You should NOT assume that n is a
 * multiple of the block size. */
void transpose_blocking(int n, int blocksize, int *dst, int *src) {
    // transposing a particular block
    int total_blocks = n/blocksize + (n % blocksize != 0);
    for (int i=0; i < total_blocks; i++) {
        for (int j=0; j < total_blocks; j++) {
            for (int x=0; x < blocksize; x++) {
                for (int y=0; y < blocksize; y++) {
                    if (y + j*blocksize < n && x + i*blocksize < n) {
                        dst[(y +  j*blocksize) + (x + i*blocksize)*n] = src[(x + i*blocksize) + (y + j*blocksize)*n];
                    }
                }
            }
        }
    }
}
