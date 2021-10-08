#include <stdio.h>

int main()
{
    // 1. Writing on screen
    double pi = 3.14159265358;
    puts("Hello, World!");
    printf("Text no %d with some formatted float %.2f\n", 2, pi);

    // 2. String reading
    char imie[50];
    printf("Your name: ");
    scanf("%s", imie);
    printf("Hello, %s!\n", imie);

    // 3. Numbers
    double a, b;
    printf("Enter two numbers: ");
    scanf("%lf %lf", &a, &b);
    printf("You've entered: %f and %f\n", a, b);
}