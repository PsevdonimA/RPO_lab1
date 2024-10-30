#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "lab1.h"

const int size = 100;
const unsigned int column = 10;

int main()
{
    int a = 0; // the lowest possible value in array
    int b = 0; // the highest possible value in array
    printf("Массив будет сгенерирован в интервале [a, b]\nВведите a: ");
    scanf("%d", &a);
    printf("Введите b: ");
    scanf("%d", &b);
    if (a > b)
    {
        printf("Invalid values!");
        return 1;
    }
    int mass[size];
    srand(time(0));
    for (int i = 0; i < size; i++)
    {
        mass[i] = (rand()%(b-a+1))+a;
    }
    print(mass, size, column);
    sort_mass(mass, size, E_UP);
    print(mass, size, column);
    return 0;
}
