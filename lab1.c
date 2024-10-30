#include "lab1.h"
#include <stdio.h>

void recursiv_sort(int* mass, int low, int high);
void reverse_mass(int* mass, int size);

void swap(int* a, int* b)
{
    *a += *b;
    *b = *a - *b;
    *a = *a - *b;
}

void sort_mass(int* mass, const int size, const enum ESort eSort)
{
    recursiv_sort(mass, 0, size-1);
    if (eSort)
    {
        reverse_mass(mass, size);
    }
}

void recursiv_sort(int* mass, int low, int high)
{
    if (high - low < 1)
    {
        return;
    }
    else if (high - low == 1)
    {
        if (mass[low] > mass[high])
        {
            swap(&mass[low], &mass[high]);
        }
        return;
    }
    int central = high;
    int pointer = low;
    while (pointer < central)
    {
        if (mass[pointer] > mass[central])
        {
            swap(&mass[central], &mass[central-1]);
            swap(&mass[central], &mass[pointer]);
            central--;
        }
        else
        {
            pointer++;
        }
    }
    recursiv_sort(mass, low, pointer-1);
    recursiv_sort(mass, pointer, high);
}

void reverse_mass(int* mass, int size)
{
    for (int i = 0; i < size/2; i++)
    {
        swap(&mass[i], &mass[size-i-1]);
    }
}
