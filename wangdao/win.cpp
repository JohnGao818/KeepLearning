#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include <cmath>

void CountSort(int a[], int b[], int n, int k) {
    int c[k];
    for(int i=0; i<k; i++)
        c[i] = 0;
    for(int i=1; i <= n; i++)
        c[a[i]] += 1;
    for(int i=0; i<k-1; i++)
        c[i+1] += c[i];
    for(int i=1; i <= n; i++){
        b[c[a[i]]] = a[i];
        c[a[i]] -= 1;
    }
}

void Print(int a[], int n)
{
    for (int i = 1; i < n + 1; i++)
    {
        printf("%d,", a[i]);
    }
    printf("\n");
}

int main()
{
    int n = 10;
    int a[n] = {0, 3, 9, 1, 2, 6, 8, 4, 5, 7};
    int b[n];
    Print(a, n - 1);
    CountSort(a, b, n - 1, n);
    Print(b, n - 1);
    system("pause");
}