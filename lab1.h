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
void print_moda(const int* mass, const int size);
float get_average(const int* mass, const int size);
int get_max(const int* mass, const int size);
int get_min(const int* mass, const int size);
int get_range(const int* mass, const int size);
float get_dispersion(const int* mass, const int size);
float get_st_deviation(const int* mass, const int size);

#endif
