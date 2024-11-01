#include "lab1.h"
#include <stdio.h>
#include <math.h>

// --- 1 part ---

void recursiv_sort(int* mass, int low, int high);
void reverse_mass(int* mass, size_t size);

void swap(int* a, int* b)
{
    *a += *b;
    *b = *a - *b;
    *a = *a - *b;
}

void sort_mass(int* mass, const size_t size, const enum ESort eSort)
{
    recursiv_sort(mass, 0, (int)size-1);
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

void reverse_mass(int* mass, size_t size)
{
    for (int i = 0; i < (int)size/2; i++)
    {
        swap(&mass[i], &mass[(int)size-i-1]);
    }
}

// --- 2 part ---

int get_column_len(const int* mass, const size_t size, const unsigned int column, int numb)
{
    int len = 0;
    int cur_len = 0;
    int k = 0; // buffer
    for (int i = numb; i < (int)size; i += column)
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

void print(const int* mass, const size_t size, const unsigned int column)
{
    int column_len[column];
    for (int i = 0; i < (int)column; i++)
    {
        column_len[i] = get_column_len(mass, size, column, i);
    }
    for (int i = 0; i < (int)size; i++)
    {
        printf("%+-*d ", column_len[i % column] + 1, mass[i]);
        if ((i % column == column - 1) || (i == (int)size - 1))
        {
            printf("\n");
        }
    }
}

// --- 3 part ---

float get_median(const int* mass, const size_t size)
{
    int mass2[(int)size];
    for (int i = 0; i < (int)size; i++)
    {
        mass2[i] = mass[i];
    }
    sort_mass(mass2, size, E_UP);
    if ((int)size % 2 == 1)
    {
        return (float)mass2[(int)size/2];
    }
    else
    {
        return (float)(((float)(mass2[(int)size/2-1]) + (float)(mass2[(int)size/2]))/2);
    }
}

// --- 4 part ---

void print_moda(const int* mass, const size_t size)
{
    int mass2[(int)size];
    for (int i = 0; i < (int)size; i++)
    {
        mass2[i] = mass[i];
    }
    sort_mass(mass2, size, E_UP);
    int mass_counter[(int)size];
    int cur_val = mass2[0];
    int cur_moda = 0;
    int moda = 0;
    for (int i = 0; i < (int)size; i++)
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
    for (int i = 0; i < (int)size; i++)
    {
        if (mass_counter[i] == moda)
        {
            printf("%d ", mass2[i]);
        }
    }
    printf("\n");
}

// --- 5 part ---

float get_average(const int* mass, const size_t size)
{
    float summ = 0;
    for (int i = 0; i < (int)size; i++)
    {
        summ += (float)(mass[i]);
    }
    return summ/(float)size;
}

// --- 6 part ---

int get_max(const int* mass, const size_t size)
{
    int m = mass[0];
    for (int i = 0; i < (int)size; i++)
    {
        if (mass[i] > m)
        {
            m = mass[i];
        }
    }
    return m;
}

// --- 7 part ---

int get_min(const int* mass, const size_t size)
{
    int m = mass[0];
    for (int i = 0; i < (int)size; i++)
    {
        if (mass[i] < m)
        {
            m = mass[i];
        }
    }
    return m;
}

// --- 8 part ---

int get_range(const int* mass, const size_t size)
{
    return get_max(mass, size) - get_min(mass, size);
}

// --- 9 part ---

float get_dispersion(const int* mass, const size_t size)
{
    float avg = get_average(mass, size);
    float sm = 0;
    for (int i = 0; i < (int)size; i++)
    {
        sm += ((float)mass[i] - avg) * ((float)mass[i] - avg);
    }
    return sm / (float)((int)size - 1);
}

// --- 10 part ---

float get_st_deviation(const int* mass, const size_t size)
{
    return pow(get_dispersion(mass, size), 0.5f);
}

// --- 11 part ---

int count_steps(float a, float step)
{
    int s = 0;
    while (a > step)
    {
        a -= step;
        s++;
    }
    return s;
}

void hist(const int* mass, const size_t size, int* count, const size_t bins)
{
    int mn = get_min(mass, size);
    int mx = get_max(mass, size);
    float step = (float)(mx - mn) / (float)(bins);
    for (int i = 0; i < (int)bins; i++)
    {
        count[i] = 0;
    }
    float k = 0; // buffer
    int c_steps = 0; // buffer
    for (int i = 0; i < (int)size; i++)
    {
        k = (float)(mass[i]) - (float)mn;
        c_steps = count_steps(k, step);
        if (c_steps == (int)bins)
        {
            count[(int)bins - 1] += 1;
        }
        else
        {
            count[c_steps] += 1;
        }
    }
}

// --- 12 part ---

void print_hist(const int* mass, const size_t size, const int* count, const size_t bins)
{
    int mn = get_min(mass, size);
    int mx = get_max(mass, size);
    float step = (float)(mx-mn) / (float)bins;
    int buffer[2] = {mn, mx}; // buffer
    int sdv = get_column_len(buffer, 2, 1, 0) + 8; // column correction
    for (int i = 0; i < (int)bins; i++)
    {
        if (i < (int)bins-1)
        {
            printf("[ %*f, %*f) ", sdv, mn + (step*i), sdv, mn + (step*(i+1)));
        }
        else
        {
            printf("[ %*f, %*f] ", sdv, mn + (step*i), sdv, (float)mx);
        }
        for (int j = 0; j < count[i]; j++)
        {
            printf("#");
        }
        printf("\n");
    }
}
