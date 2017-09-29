// Project 2
#include <unistd.h>  // unistd.h is the name of the header file that provides access to the POSIX operating system API
#include <pthread.h>  // Pthreads are implemented with a pthread.h header and a thread library.
#include <math.h>  // Contains common mathematics functions
#include <stdlib.h>   // Contains general utilities: memory management, program utilities, string conversions, random numbers
#include <stdio.h>

// Unsorted array
int arr[] = {5, 9, 3, 10, 11, 14, 20, 4, 15, 12};

/*
    NOTE:: For the purpose of this Project we use a guaranteed to work implementation
    of MergeSort from http://www.geeksforgeeks.org/merge-sort/
*/

// Merges two subarrays of arr[].
// First subarray is arr[l..m]
// Second subarray is arr[m+1..r]
void merge(int arr[], int l, int m, int r)
{
    int i, j, k;
    int n1 = m - l + 1;
    int n2 =  r - m;

    /* create temp arrays */
    int L[n1], R[n2];

    /* Copy data to temp arrays L[] and R[] */
    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1+ j];

    /* Merge the temp arrays back into arr[l..r]*/
    i = 0; // Initial index of first subarray
    j = 0; // Initial index of second subarray
    k = l; // Initial index of merged subarray
    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j])
        {
            arr[k] = L[i];
            i++;
        }
        else
        {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    /* Copy the remaining elements of L[], if there
     are any */
    while (i < n1)
    {
        arr[k] = L[i];
        i++;
        k++;
    }


    /* Copy the remaining elements of R[], if there
     are any */
    while (j < n2)
    {
        arr[k] = R[j];
        j++;
        k++;
    }

}

/* l is for left index and r is right index of the
 sub-array of arr to be sorted */
void mergeSort(int arr[], int l, int r)
{
    if (l < r)
    {
        // Same as (l+r)/2, but avoids overflow for
        // large l and h
        int m = l+(r-l)/2;

        // Sort first and second halves
        mergeSort(arr, l, m);
        mergeSort(arr, m+1, r);

        merge(arr, l, m, r);
    }
}

/* UTILITY FUNCTIONS */
/* Function to print an array */
void printArray(int A[], int size)
{
    int i;
    for (i=0; i < size; i++)
        printf("%d ", A[i]);
    printf("\n");
}

////////////////////////////////////////////////

void *mergeSortSublistOne(void *params){
    int array_size = (sizeof(arr))/(sizeof(arr[0]));
    int middle = floor(array_size/2.0);
    mergeSort(arr, 0, middle);
}

void *mergeSortSublistTwo(void *params){
    int array_size = (sizeof(arr))/(sizeof(arr[0]));
    int middle = floor(array_size/2.0);
    mergeSort(arr, middle +1, array_size-1);
}

void *mergeWrapper(void *params){
    int array_size = (sizeof(arr))/(sizeof(arr[0]));
    int middle = floor(array_size/2.0);
    merge(arr, 0, middle, (array_size-1));
}

void multiSort(int array1[]){
    pthread_t tid1, tid2, tid3;
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_create(&tid1,&attr,mergeSortSublistOne, NULL);
    pthread_create(&tid2,&attr,mergeSortSublistTwo, NULL);
    pthread_join(tid1,NULL);
    pthread_join(tid2,NULL);
    pthread_create(&tid3,&attr,mergeWrapper,NULL);
    pthread_join(tid3,NULL);
}

int main() {
    int arr_size = (sizeof(arr)) / (sizeof(arr[0]));
    printf("The array is: \n");
    printArray(arr, arr_size);
    // Sort the array
    multiSort(arr);
    printf("\n");
    printf("The sorted array is: \n");
    printArray(arr, arr_size);
    return 0;
}
