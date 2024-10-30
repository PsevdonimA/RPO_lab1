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

// --- 4 part ---

void print_moda(const int* mass, const int size)
{
    int mass2[size];
    for (int i = 0; i < size; i++)
    {
        mass2[i] = mass[i];
    }
    sort_mass(mass2, size, E_UP);
    int mass_counter[size];
    int cur_val = mass2[0];
    int cur_moda = 0;
    int moda = 0;
    for (int i = 0; i < size; i++)
    {
        if (mass2[i] == cur_val)
        {
            mass_counter[i] = ++cur_moda;
            if (cur_moda > moda)
            {
                moda = cur_moda;
            }
        }
        else
        {
            cur_moda = 1;
            cur_val = mass2[i];
            mass_counter[i] = 1;
        }
    }
    for (int i = 0; i < size; i++)
    {
        if (mass_counter[i] == moda)
        {
            printf("%d ", mass2[i]);
        }
    }
    printf("\n");
}

// --- 5 part ---

float get_average(const int* mass, const int size)
{
    float summ = 0;
    for (int i = 0; i < size; i++)
    {
        summ += (float)(mass[i]);
    }
    return summ/(float)size;
}

// --- 6 part ---

int get_max(const int* mass, const int size)
{
    int m = mass[0];
    for (int i = 0; i < size; i++)
    {
        if (mass[i] > m)
        {
            m = mass[i];
        }
    }
    return m;
}

// --- 7 part ---

int get_min(const int* mass, const int size)
{
    int m = mass[0];
    for (int i = 0; i < size; i++)
    {
        if (mass[i] < m)
        {
            m = mass[i];
        }
    }
    return m;
}

// --- 8 part ---

int get_range(const int* mass, const int size)
{
    return get_max(mass, size) - get_min(mass, size);
}
