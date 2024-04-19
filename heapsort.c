#include <stdio.h>
#include <stdlib.h>

void print_heap(int *array, int length) {
    int i = 0, l = 0;
    while (i < length) {
        int count = 1 << l;
        count = (count < length - i) ? count : length - i;
//        printf("l = %d, count = %d\n", l, count);
        while (count) {
            printf("%d, ", array[i++]);
            if (i % 2) {
                printf("\t");
            }
            count--;
        }
        printf("\n");
        l++;
    }
}

void swap(int *array, int i1, int i2) {
    int tmp = array[i1];
    array[i1] = array[i2];
    array[i2] = tmp;
}

void heapify(int *array, int base, int length) {
    int left = 2 * base  + 1;   // Tip: 0 points to 1 and 2.
    int right = 2 * base + 2;

    // Optional: exit early if this is a leaf.
    /*
    if (left >= length) {
        return;
    }
    */

    int max = base;
    if (left < length && array[left] > array[max]) {
        max = left;
    }
    if (right < length && array[right] > array[max]) {
        max = right;
    }

    // Swap has occurred: update sub-tree to make it a heap.
    if (max != base) {
        swap(array, max, base);
        heapify(array, max, length);    // Update tree all the way down.
    }
}

void build_max_heap(int *array, int length) {
    int i;
    for (i = length / 2; i >= 0; i--) {
        heapify(array, i, length);
    }
}

void heapsort(int *array, int length) {
    int i;
    build_max_heap(array, length);
    printf("build_max_heap \n[");
    print_heap(array, length);
    printf("]\n");
    for (i = length; i >= 0; i--) {
        swap(array, 0, i - 1);
        length--;
        heapify(array, 0, length);
    }
}

int main (int argc, char** argv) {
    int i;
    int length = argc - 1;
    int *array = malloc(sizeof(int) * length);
    for (i = 0; i < length; i++) {
        array[i] = atoi(argv[i + 1]);
    }
    print_heap(array, length);
    heapsort(array, length);
    printf("final \n[");
    print_heap(array, length);
    printf("]\n");
    return 0;
}

/*
    Max heap definition:
    - It us a binary tree.
    - Children are less than or equal to their parent.

    Heap sort implementation:
    1. Implement recursive method for heapify:
        - takes an origin point in the array and the length of said array.
        - perform swap so that the 3 node tree represents a max heap - the max
            value is placed as parent.
            CAREFUL: check that the children IDs lay within array boundaries!
        - if swap did occur, recurse heapify using the swapped child node as
            origin -> exit base condition in recursion calls of heapify.
    2. Build_max_heap: Reorder the array to obtain a max heap.
        - For each node located at middle of the array, all the way to the
            first node, perform heapify.
    3. Heap sort:
        1. Run build_max_heap.
        2. For each node, start from last to first:
            - swap last and first: max value is placed at the end of the array.
                -> last is now in its ORDERED spot and can be ignored.
            - decrement length to ignore last value.
            - run heapify on new tree with misplaced root (since swapped with
                previous root/max value)
                -> we are back to a max heap.
            - REPEAT!
    

    Heap sort tips:
    1. During Build_max_heap, skip all the leaves by starting heapify from the
        spot located at the middle of the array and roll all the way up to the 
        root index.
*/