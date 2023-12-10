#pragma once
#include <span>
struct DynamicArray
{
    size_t capacity=1;
    size_t length;
    int *arr;
};

DynamicArray createDynamicArray();
DynamicArray createDynamicArrayWCapacity(size_t capacity);
int getElementAtIndex(DynamicArray *array, int index);
void addElementToArray(DynamicArray *array, int num);
std::span<int> getCurrSpan(DynamicArray *array);