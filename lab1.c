#include "lab1.h"
#include <stdio.h>

// --- 1 part ---

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

// --- 2 part ---

int get_column_len(const int* mass, const int size, const unsigned int column, int numb)
{
    int len = 0;
    int cur_len = 0;
    int k = 0; // buffer
    for (int i = numb; i < size; i += column)
    {
        cur_len = 1;
        k = mass[i] / 10;
        while (k > 0)
        {
            cur_len++;
            k /= 10;
        }
        if (cur_len > len)
        {
            len = cur_len;
        }
    }
    return len;
}

void print(const int* mass, const int size, const unsigned int column)
{
    int column_len[column];
    for (int i = 0; i < (int)column; i++)
    {
        column_len[i] = get_column_len(mass, size, column, i);
    }
    for (int i = 0; i < size; i++)
    {
        printf("%+-*d ", column_len[i % column] + 1, mass[i]);
        if ((i % column == column - 1) || (i == size - 1))
        {
            printf("\n");
        }
    }
}

// --- 3 part ---

float get_median(const int* mass, const int size)
{
    int mass2[size];
    for (int i = 0; i < size; i++)
    {
        mass2[i] = mass[i];
    }
    sort_mass(mass2, size, E_UP);
    if (size % 2 == 1)
    {
        return (float)mass2[size/2];
    }
    else
    {
        return (float)(((float)(mass2[size/2-1]) + (float)(mass2[size/2]))/2);
    }
}
