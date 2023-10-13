// вторая часть лабы
#include <stdlib.h>
#include <iostream>

struct TwoInts // определение пользовательского типа данных TwoInts, это что-то очень похожее на record из языка Pascal
{
    int a;
    int b;
};

struct StructWithArray // определение пользовательского типа данных StructWithArray
{
    int arr[4];      // массив размером в 4 элемента
    int *someNumber; // указатель someNumber
};

int main()
{
    TwoInts i2 = {};
    i2.a = 5;
    i2.b = 7;

    std::cout << i2.a << std::endl; // выведет 5
    std::cout << i2.b << std::endl; // выведет 7

    StructWithArray s = {};
    s.arr[0] = 10;

    StructWithArray s1 = {};
    s1.arr[0] = 15;

    StructWithArray *sPointer = &s;
    sPointer->arr[0] = 20; // то же, что и (*sPointer).arr[0] = 20;
                           // то есть переходим к адресу указателя и берём первый элемент массива структуры

    std::cout << s.arr[0] << std::endl; // выведет 20
    s.arr[0] = 25;
    std::cout << s.arr[0] << std::endl; // выведет 25
    sPointer->arr[0] = 30;              // то же, что и (*sPointer).arr[0] = 30;
    std::cout << s.arr[0] << std::endl; // выведет 30

    sPointer = &s1;                      // возвращаем адрес структуры s1
    sPointer->arr[0] = 35;               // то же, что и (*sPointer).arr[0] = 35; только тут уже структура s1
    std::cout << s.arr[0] << std::endl;  // выведет 30, т.к. s.arr[0] последний раз был 30 и не изменялся
    std::cout << s1.arr[0] << std::endl; // выведет 35 т.к. sPointer хранит адрес структуры s1

    StructWithArray structArray[2] = {};
    structArray[0].arr[3] = 77;                         // первый элемент массива structArray имеет значение 3го элемента массива arr = 77
    structArray[1].someNumber = &structArray[0].arr[3]; // второй элемент массива содержит в себе адрес первого элемента массива structArray

    sPointer = &s;                    // возвращаем адрес структуры s
    int *pointer = &sPointer->arr[3]; // определение pointer, адрес значения 3 элемента массива структуры s
    s.arr[3] = 72;                    // инициализация 3 элемента массива = 72
    std::cout << *pointer;            // выведет разыменованный pointer, указывающий на 3й элемент массива структуры s равный 72, то есть просто выведет 72

    StructWithArray memory;
    memset(&memory, 0, sizeof(StructWithArray));
    return 0;
}