#ifndef LAB1_H
#define LAB1_H

extern const enum ESort
{
    E_UP = 0,
    E_DOWN
}ESort;
void sort_mass(int* mass, const int size, const enum ESort eSort);
void print(const int* mass, const int size, const unsigned int column);
float get_median(const int* mass, const int size);

#endif
