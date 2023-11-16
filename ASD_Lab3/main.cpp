#include <iostream>
using namespace std;

// int func(int x);

int func(int x) 
{
    return x+=x;   
}

//int hello(int num) 
//{
//    return num;
//}

int main()
{
    cout << func(5);
    // ошибка компиляции не возникает после определения функции,
    // но без определения - ошибка линкера
}