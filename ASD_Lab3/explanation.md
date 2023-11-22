Объяснения • Lab3 
# 1. Функции и линкер
# Простой пример
```cpp
int func(int x);

int main()
{
    cout << func(5);
}
```
Возникнет ошибка компиляции из-за ошибки линкера - функция объявлена, но не определена.

После определения функции всё заработает:
```cpp
int func(int x) 
{
    return x+=x;   
}

int main()
{
    cout << func(5);
}
```

# Пример с 2 файлами
### Пункты **с 1 по 4**
Оба файла выдадут ошибку компиляции по причине из *Простого примера*, то есть ошибка линкера т.к. функция объявлена, но не определена.
### Пункты **с 5 по 6**
Функция `hello`, будучи определенной, не будет выбивать ошибку в компиляции, так как у линкера не возникнет ошибок.

Сам по себе `main.cpp` не был изменен, т.е. функция по прежнему не определена -> ошибка линкера = ошибка компиляции.
### Пункты **с 7 по 11**
```cpp
static int hello (int num);

int main()
{
    //cout << func(5);
    hello(5);
}
```
Компиляция прервана с последующей ошибкой:
> function 'hello' has internal linkage but is not defined

Проблема с линковкой не возникла - теперь из-за `static` она внутренне линкована, но ошибка вызвана тем, что **функция не определена (is not defined)**.

Следующий код ошибку не выдаст:
```cpp
static int hello (int num)
{
    return num;
};

int main()
{
    //cout << func(5);
    hello(5);
}
```
**Почему работает?** Потому что у линкера не возникает вопросов из-за `static` (internal linkage) и функция определена.

**Сколько копий тела функции `hello` скомипилируется?**
> Две разные статические функции могут быть определены в нескольких компиляционных единицах, и все они окажутся в исполняемом файле, и они будут обрабатываться независимо.

Исходя из этого определения и, учитывая, что в `f.cpp` и `main.cpp` объявлено и определено:
```cpp
static int hello (int num)
{
    return num;
};
```
То будут созданы 2 копии тела функции `hello`.

# 2. Stack, Heap, Static Memory
# 2.1. Объяснение `stack2.cpp`
```cpp
// фрагмент stack2.cpp
#include <stdlib.h>
#include <iostream>

int* stackMemory1() 
{
    int a = 1; //local
    return &a; 
}

int* stackMemory2()
{
    int b = 2; //local
    return &b; //returning pointer on local
}

int main()
{
    int* b = stackMemory1();
    int a1 = *b; // 1
    int* c = stackMemory2();
    int a2 = *c; // 2
    int a3 = *b; // 2

    std::cout << a1 << std::endl; // prints 1
    std::cout << a2 << std::endl; // prints 2
    std::cout << a3 << std::endl; // prints 2
    std::cout << ((std::byte*) b - (std::byte*) c) << std::endl; // prints 0, pointers are equal

    return 0;
}
```
Возвращаемые указатели из функций `stackMemory1` и `stackMemory2` указывают на локальные переменные, которые выходят из области видимости при выполнении соответствующих функций. Это приведет к **неопределенному поведению**, когда указатели разыменуются в `main`.


# 2.2 `a` в `static1.cpp` vs `a` в `static2.cpp`

### Static 1
```cpp
#include <iostream>
// no global variable
void staticMemory()
{
    static int a = 0; //static is a keyword for us
    std::cout << "a: " << a << std::endl;
    a += 1;
}

int main()
{
    staticMemory(); // prints 0
    staticMemory(); // prints 1
    staticMemory(); // prints 2
    return 0;
}
```
### Static 2
```cpp
#include <iostream>

int a = 0; //global variable

void staticMemory()
{
    std::cout << "a: " << a << std::endl;
    a += 1;
}

int main()
{
    staticMemory(); // prints 0
    staticMemory(); // prints 1
    staticMemory(); // prints 2
    return 0;
}
```
Переменная `a` в `static_1` объявлена как статическая переменная внутри функции `staticMemory`.

Чтобы сделать `static_2` эквивалентным `static_1` в плане невозможности импортирования переменной в другом файле, надо использовать `static` при объявлении глобальной переменной:

```cpp
static int a = 0;
```

---