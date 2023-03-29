#include <time.h>
#include <stdio.h>
#include <x86intrin.h>
#include "simd.h"

long long int sum(int vals[NUM_ELEMS]) {
    clock_t start = clock();

    long long int sum = 0;
    for(unsigned int w = 0; w < OUTER_ITERATIONS; w++) {
        for(unsigned int i = 0; i < NUM_ELEMS; i++) {
            if(vals[i] >= 128) {
                sum += vals[i];
            }
        }
    }
    clock_t end = clock();
    printf("Time taken: %Lf s\n", (long double)(end - start) / CLOCKS_PER_SEC);
    return sum;
}

long long int sum_unrolled(int vals[NUM_ELEMS]) {
    clock_t start = clock();
    long long int sum = 0;

    for(unsigned int w = 0; w < OUTER_ITERATIONS; w++) {
        for(unsigned int i = 0; i < NUM_ELEMS / 4 * 4; i += 4) {
            if(vals[i] >= 128) sum += vals[i];
            if(vals[i + 1] >= 128) sum += vals[i + 1];
            if(vals[i + 2] >= 128) sum += vals[i + 2];
            if(vals[i + 3] >= 128) sum += vals[i + 3];
        }

        // TAIL CASE, for when NUM_ELEMS isn't a multiple of 4
        // NUM_ELEMS / 4 * 4 is the largest multiple of 4 less than NUM_ELEMS
        // Order is important, since (NUM_ELEMS / 4) effectively rounds down first
        for(unsigned int i = NUM_ELEMS / 4 * 4; i < NUM_ELEMS; i++) {
            if (vals[i] >= 128) {
                sum += vals[i];
            }
        }
    }
    clock_t end = clock();
    printf("Time taken: %Lf s\n", (long double)(end - start) / CLOCKS_PER_SEC);
    return sum;
}

long long int sum_simd(int vals[NUM_ELEMS]) {
    clock_t start = clock();
    __m128i _127 = _mm_set1_epi32(127); // This is a vector with 127s in it... Why might you need this?
    long long int result = 0; // This is where you should put your final result!
    /* DO NOT MODIFY ANYTHING ABOVE THIS LINE (in this function) */
    for(unsigned int w = 0; w < OUTER_ITERATIONS; w++) {
        /* YOUR CODE GOES HERE */

        // initialize all the values
        __m128i _sum_vector = _mm_setzero_si128();
        __m128i four_ele = _mm_setzero_si128();
        __m128i mask = _mm_setzero_si128();
        __m128i filtered_ele = _mm_setzero_si128();
        int result_arr[4] = {0,0,0,0};
        int sum=0;
        int i = 0;

        // innter loop
        for (; i + 4 <= NUM_ELEMS; i += 4) {
            four_ele = _mm_loadu_si128((__m128i *) (vals + i));
            mask = _mm_cmpgt_epi32(four_ele, _127);
            filtered_ele = _mm_and_si128(mask, four_ele);
            _sum_vector = _mm_add_epi32(_sum_vector, filtered_ele);
        }
        int tmp_arr[4]={0,0,0,0};
        _mm_storeu_si128((__m128i *) tmp_arr, _sum_vector);
        sum = tmp_arr[0] + tmp_arr[1] + tmp_arr[2] + tmp_arr[3];
        for (; i < NUM_ELEMS; i++) {
            sum += vals[i];
        }
        result += sum;

        /* Hint: you'll need a tail case. */

    }

    /* DO NOT MODIFY ANYTHING BELOW THIS LINE (in this function) */
    clock_t end = clock();
    printf("Time taken: %Lf s\n", (long double)(end - start) / CLOCKS_PER_SEC);
    return result;
}

long long int sum_simd_unrolled(int vals[NUM_ELEMS]) {
    clock_t start = clock();
    __m128i _127 = _mm_set1_epi32(127);
    long long int result = 0;
    /* DO NOT MODIFY ANYTHING ABOVE THIS LINE (in this function) */

    for(unsigned int w = 0; w < OUTER_ITERATIONS; w++) {
        /* YOUR CODE GOES HERE */
        __m128i _sum_vector = _mm_setzero_si128();
        __m128i _sum_vector1 = _mm_setzero_si128();
        __m128i _sum_vector2 = _mm_setzero_si128();
        __m128i four_ele = _mm_setzero_si128();
        __m128i mask = _mm_setzero_si128();
        __m128i filtered_ele = _mm_setzero_si128();
        int sum=0;
        int i = 0;

        for (; i + 12 <= NUM_ELEMS; i += 12) {
            four_ele = _mm_loadu_si128((__m128i *) (vals + i));
            mask = _mm_cmpgt_epi32(four_ele, _127);
            filtered_ele = _mm_and_si128(mask, four_ele);
            _sum_vector = _mm_add_epi32(_sum_vector, filtered_ele);

            four_ele = _mm_loadu_si128((__m128i *) (vals + i + 4));
            mask = _mm_cmpgt_epi32(four_ele, _127);
            filtered_ele = _mm_and_si128(mask, four_ele);
            _sum_vector1 = _mm_add_epi32(_sum_vector1, filtered_ele);

            four_ele = _mm_loadu_si128((__m128i *) (vals + i + 4));
            mask = _mm_cmpgt_epi32(four_ele, _127);
            filtered_ele = _mm_and_si128(mask, four_ele);
            _sum_vector2 = _mm_add_epi32(_sum_vector2, filtered_ele);
        }

        int tmp_arr[4]={0,0,0,0};
        _mm_storeu_si128((__m128i *) tmp_arr, _sum_vector);
        sum += tmp_arr[0] + tmp_arr[1] + tmp_arr[2] + tmp_arr[3];

        _mm_storeu_si128((__m128i *) tmp_arr, _sum_vector1);
        sum += tmp_arr[0] + tmp_arr[1] + tmp_arr[2] + tmp_arr[3];

        _mm_storeu_si128((__m128i *) tmp_arr, _sum_vector2);
        sum += tmp_arr[0] + tmp_arr[1] + tmp_arr[2] + tmp_arr[3];

        for (; i < NUM_ELEMS; i++) {
            sum += vals[i];
        }

        result += sum;
        /* Copy your sum_simd() implementation here, and unroll it */

        /* Hint: you'll need 1 or maybe 2 tail cases here. */
    }

    /* DO NOT MODIFY ANYTHING BELOW THIS LINE (in this function) */
    clock_t end = clock();
    printf("Time taken: %Lf s\n", (long double)(end - start) / CLOCKS_PER_SEC);
    return result;
}
