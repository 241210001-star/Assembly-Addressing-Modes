#include <stdio.h>

int global = 100;   

int main() {
    
    int a = 50;

    
    int b = 20;
    int sum = a + b;

    
    int g = global;


    int *p = &a;
    int x = *p;


    int y = *p;   


    int arr[3] = {1, 2, 3};
    int val = arr[2];


    int *q = arr;
    int first = *q++;   


    int *r = &arr[2];
    int last = *r--;    


    printf("%d %d %d %d %d %d %d %d\n",
           a, sum, g, x, y, val, first, last);


    return 0;
}