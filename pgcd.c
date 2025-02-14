#define NDEBUG 1
#include <assert.h>
#include "pgcd.h"

int pgcd_diff(const int A, const int B){
    assert(A != 0 && B != 0);
    
    if(A == 0 || B == 0){
        return -1;
    }
    int a = A;
    int b = B;
    while (a != b)
    {
        if (a > b)
        {
            a = a - b;
        }
        else
        {
            b = b - a;
        }
    }
    int result = a;
    assert(result > 0);
    assert(A % result == 0 && B % result == 0);
    return result;
}

int pgcd_euclide(const int A, const int B){
    assert(A != 0 && B != 0);
    if(A == 0 || B == 0){
        return -1;
    }
    int a, b, c;

    if (A < B)
    {
        a = B;
        b = A;
    }
    else
    {
        a = A;
        b = B;
    }

    while (b != 0)
    {
        c = a % b;
        a = b;
        b = c;

    }
    int result = a;
    assert(result > 0);
    assert(A % result == 0 && B % result == 0);
    return result;
}

int pgcd_liste_diviseur(const int A, const int B)
{   
    assert(A != 0 && B != 0);
    if(A == 0 || B == 0){
        return -1;
    }
    
    int a = A;
    int b = B;
    int pgcd = 1;
    int i = 2;
    while (i <= a && i <= b)
    {
        if (a % i == 0 && b % i == 0)
        {
            pgcd = i;
        }
        i++;
    }
    int result = pgcd;
    assert(result > 0);
    assert(A % result == 0 && B % result == 0);
    return result;
}

    /*
    // Test Manuel
    int tab_a[10] = {24585, 785, 45, 7845, 14268, 65, 741, 123, 456, 789};
    int tab_b[10] = {4000, 5551, 201, 30401, 21, 13, 11589, 9921, 9764, 7955}; 

    for (int i = 0; i < sizeof(tab_a); i++)
    {
        int result = pgcd(tab_a[i], tab_b[i]);
        printf("Result: %d\n", result);
    }
    */