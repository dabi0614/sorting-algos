#include <stdlib.h>
#include <stdio.h>

void swap(int *array, int i1, int i2) {
    int tmp = array[i1];
    array[i1] = array[i2];
    array[i2] = tmp;
}

// Perform the swapping based on pivot value.
// Returns the index of the splitting: when the left value crosses the pivot value.
int partition(int *array, int left, int right, int pivot) {
    int pivot_value = array[pivot];
    int right_orig = right;
    // Get pivot out of the way by swapping with right-most value.
    swap(array, pivot, right_orig);
    right--;
    while (left <= right) {
        // Find next item that is greater than the pivot.
        while (array[left] <= pivot_value && left <= right) {
            left++;
        }
        // Find next item that is less than the pivot.
        while (array[right] > pivot_value && left <= right) {
            right--;
        }
        if (left < right) {
            swap(array, left, right);
        }
    }
    // Put pivot back into correct position.
    swap(array, left, right_orig);
    return left;
}

void quicksort(int *array, int left, int right) {
    int i;
    if (left >= right) {
        return;
    }
    /*
     * CHOOSE PIVOT: value of located in the middle of the array.
    */
    int pivot = (left + right) / 2;
    printf("B %d-%d-%d \n[", left, pivot, right);
    for (i = left; i <= right; i++) {
        printf("%d, ", array[i]);
    }
    printf("]\n");
    pivot = partition(array, left, right, pivot);
    printf("A %d-%d-%d \n[", left, pivot, right);
    for (i = left; i <= right; i++) {
        printf("%d, ", array[i]);
    }
    printf("]\n");

    quicksort(array, left, pivot - 1);
    quicksort(array, pivot + 1, right);
}

int main (int argc, char** argv) {
    int i;
    int length = argc - 1;
    int *array = malloc(sizeof(int) * length);
    for (i = 0; i < length; i++) {
        array[i] = atoi(argv[i + 1]);
    }
    quicksort(array, 0, length - 1);
    printf("final \n[");
    for (i = 0; i < length; i++) {
        printf("%d, ", array[i]);
    }
    printf("]\n");
    return 0;
}

/*
 * Quick sort tips:
 * 1. Chose a pivot located at the middle of the sub-array but get it out of the
 *      way before starting to swap values.
 * 2. The pivot is the first to get in the correct order.
 * 3. Let LEFT to include the pivot value: [0; pivot_value[ c.f. line 20
 * 4. RIGHT cannot include pivot value: ]pivot_value; inf[ c.f. line 24
 * 5. Allow LEFT to overlap RIGHT! Otherwise this can create a corner-case issue
 *      when the sub-array is already ordered. c.f. line 18, 20 & 24
 *
*/

/*
 * SPEED
 * Time complexity      O(N * logN)
 * - Process is repeated N times recursively -> N
 * - At each recurse, the sort space is roughly divided by 2 -> log N
 * Worst case           O(N^2)
 * Each recuse has to sort a space that decrements by 1 every time:
 * N + N-1 + N-2 ... ->  < (N * N) = N^2
 * 
 * SIZE OF THE CALL STACK
 * Space complexity     O(log N)
 * At each recurse, the memory space required to store the sub-array is divided
 *  by 2 -> log N
 * Worst case:          O(N)
 * Each recuse has to sort a space that decrements by 1 every time:
 * N then N-1 then N-2 ... ->  < N 
 * 
 * 
 * https://www.geeksforgeeks.org/time-and-space-complexity-analysis-of-quick-sort/
*/