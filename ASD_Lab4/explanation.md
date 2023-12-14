# Структура динамического массива
```cpp
struct DynamicArray
{
    size_t capacity=1;
    size_t length;
    int *arr;
};
```

- Поле `capacity` отвечает за длину массива (макс. возм. кол-во элементов)
- Поле `length` отвечает за количество используемых элементов массива
- Указатель `int *arr` т.к. динамический массив создаётся в куче и возвращается указатель на начало этого блока памяти. 

### Функция создания массива с заданным кол-во элементов по умолчанию

```cpp
DynamicArray createDynamicArray()
{
    int *arr = new int[16];
    DynamicArray array;
    array.arr = arr;
    array.length = 0;
    array.capacity = 16;
    return array;
}
```

Создается динамический массив длиною в 16 элементов.

Создается структура `DynamicArray`, в которую вписывается указатель на этот массив в куче. 

Так как массив только создан, количество используемых элементов - 0 => поле `length = 0`, а длина по умолчанию => `capacity = 16`.

Функция возвращает структуру типа `DynamicArray`.

### Функция создания массива с заданным кол-во элементов из параметра.
```cpp
DynamicArray createDynamicArrayWCapacity(size_t capacity)
{
    int *arr = new int[capacity];
    DynamicArray array;
    array.arr = arr;
    array.length = 0;
    array.capacity = capacity;
    return array;
}
```
Всё то же самое, как в предыдущем, только **размер массива задается в качестве параметра функции**.

---

### Добавление элемента в массив
```cpp
void addElementToArray(DynamicArray *array, int num)
{
    if (array->arr == 0)
    {
        int *arr = new int[1];
        array->arr = arr;
    }

    if (array->capacity <= array->length)
    {
        int *arr = new int[array->capacity * 2];
        for (int i = 0; i < array->capacity; i++)
        {
            arr[i] = array->arr[i];
        }
        delete[] array->arr;
        array->arr = arr;
        array->capacity *= 2;
    }

    array->arr[array->length++] = num;
}
```

Происходит проверка на наличие указателя на массив в памяти, если этого массива нет (`nullptr`), тогда создается динамический массив размером 1.

Следующая проверка выявляет превышает ли границы индекс массива, в случае если мы не можем поместить туда новый элемент, мы инициализируем **новый массив** в памяти в 2 раза больше предыдущего и помещаем в новый массив элементы из предыдущего. 

Далее освобождаем память старого массива. в структуре изменяем указатель на массив на новый, увеличив поле `capacity` в 2 раза.

### Обращение к элементу массива по индексу
```cpp
int getElementAtIndex(DynamicArray *array, int index)
{
    assert(index < array->length);
    return array->arr[index];
}
```

`assert()` - assert используется для утверждения, что выражение должно быть `True`.

Таким образом мы проверяем через `assert`, что элемент по нужному индексу - существует и возвращаем элемент по данному индексу.

### Span
```cpp
std::span<int> getCurrSpan(DynamicArray *array)
{
    return {array->arr, array->length};
}
```

`Span` - структура данного контейнера подразумевает, что имеем указатель на массив и его длину, что-то типа вектора.

### Освобождение памяти
```cpp
void free(DynamicArray *array)
{
    array->length = 0;
    delete[] array->arr;
}
```

Длина обнуляется и `delete[]` освобождает память, занятую массивом.