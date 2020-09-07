#include <stdio.h>
#include <stdlib.h>

/*
 * Function, that concatenates two array with floating point values,
 * arr1 with n1 items, and arr2 with n2 items. The needed memory for the
 * resulting array needs to be dynamically allocated.
 * Note: you don't need to free the memory for arr1 or arr2.
 */
double* doublecat(const double* arr1, unsigned int n1,
                  const double* arr2, unsigned int n2) {
    double *cat = malloc(sizeof(double)*(n1+n2+1));
    unsigned i = 0,j=0;
    for(; i < n1; i++){
        cat[i]=arr1[i];
    }
    for(;i<(n1+n2);i++,j++){
        cat[i]=arr2[j];
    }
    cat[i++] = 0;
    return cat;
}

void my_tests(void)
{
    double arr1[] = {1,2,3,4};
    double arr2[] = {5,6,7,8,9};
    double *arr;
    arr = doublecat(arr1, 4, arr2, 4);
    for(int i = 0; i<9; i++){
        printf("%0.2f ", arr[i]);
    }
}

int main(void)
{
    /* You may implement your own tests in my_tests function */
    my_tests();

    /* To enable automatic grading, uncomment the below
    function call for hidden function grading_tests */
    //grading_tests();
}