// Лабораторная работа №4 (1 семестр). Вариант 1, средний уровень.
// Файл реализации: методы класса IntVector.

#include "IntVector.h"

#include <iostream>
#include <stdexcept>    // стандартные исключения: out_of_range, invalid_argument, underflow_error

// ------------------------- Вспомогательные методы ----------------------------

// Проверяет, что индекс лежит в пределах от 0 до size - 1
void IntVector::checkIndex(int index) const {
    if (index < 0 || index >= size) {
        throw std::out_of_range("Индекс вне диапазона");
    }
}

// Выделяет новый массив на newCapacity элементов, копирует в него все элементы
// и освобождает старый массив. Вызывается только при newCapacity >= size.
void IntVector::reallocate(int newCapacity) {
    int* newData = nullptr;
    if (newCapacity > 0) {
        newData = new int[newCapacity];
    }
    for (int i = 0; i < size; ++i) {
        newData[i] = data[i];
    }
    delete[] data;              // старая память больше не нужна
    data = newData;
    capacity = newCapacity;
}

// ------------------------------ Конструкторы ---------------------------------

// По умолчанию: пустой вектор, память пока не выделена
IntVector::IntVector() : data(nullptr), size(0), capacity(0) {
}

// Вектор из n нулей
IntVector::IntVector(int n) : data(nullptr), size(0), capacity(0) {
    if (n < 0) {
        throw std::invalid_argument("Размер не может быть отрицательным");
    }
    if (n > 0) {
        data = new int[n];
        for (int i = 0; i < n; ++i) {
            data[i] = 0;
        }
    }
    size = n;
    capacity = n;
}

// Вектор из n элементов, равных value
IntVector::IntVector(int n, int value) : data(nullptr), size(0), capacity(0) {
    if (n < 0) {
        throw std::invalid_argument("Размер не может быть отрицательным");
    }
    if (n > 0) {
        data = new int[n];
        for (int i = 0; i < n; ++i) {
            data[i] = value;
        }
    }
    size = n;
    capacity = n;
}

// Конструктор копирования. Делает глубокую копию: выделяет свой массив
// и копирует в него элементы, а не просто копирует указатель.
IntVector::IntVector(const IntVector& other)
    : data(nullptr), size(other.size), capacity(other.capacity) {
    if (capacity > 0) {
        data = new int[capacity];
    }
    for (int i = 0; i < size; ++i) {
        data[i] = other.data[i];
    }
}

// -------------------------------- Деструктор ---------------------------------

IntVector::~IntVector() {
    delete[] data;              // для nullptr оператор delete[] ничего не делает
}

// --------------------------- Оператор присваивания ---------------------------

IntVector& IntVector::operator=(const IntVector& other) {
    if (this != &other) {                   // защита от самоприсваивания (v = v)
        // сначала выделяем новую память и копируем, и только потом удаляем старую:
        // если new не сможет выделить память, наш объект останется целым
        int* newData = nullptr;
        if (other.capacity > 0) {
            newData = new int[other.capacity];
        }
        for (int i = 0; i < other.size; ++i) {
            newData[i] = other.data[i];
        }
        delete[] data;
        data = newData;
        size = other.size;
        capacity = other.capacity;
    }
    return *this;                           // чтобы работала цепочка a = b = c
}

// ---------------------------- Доступ по индексу ------------------------------

int& IntVector::operator[](int index) {
    checkIndex(index);
    return data[index];
}

const int& IntVector::operator[](int index) const {
    checkIndex(index);
    return data[index];
}

// ------------------------------ Методы доступа -------------------------------

int IntVector::getSize() const {
    return size;
}

int IntVector::getCapacity() const {
    return capacity;
}

bool IntVector::isEmpty() const {
    return size == 0;
}

// ----------------------------- Методы изменения ------------------------------

// Добавление в конец. Если место закончилось, ёмкость увеличивается вдвое.
void IntVector::pushBack(int value) {
    if (size == capacity) {
        int newCapacity = (capacity == 0) ? 1 : capacity * 2;
        reallocate(newCapacity);
    }
    data[size] = value;
    ++size;
}

// Удаление последнего элемента. Память не освобождается, уменьшается только размер.
void IntVector::popBack() {
    if (isEmpty()) {
        throw std::underflow_error("Вектор пуст, удалять нечего");
    }
    --size;
}

// Вставка на позицию index. Элементы, начиная с этой позиции, сдвигаются вправо.
// Допустим index == size: это вставка в конец.
void IntVector::insert(int index, int value) {
    if (index < 0 || index > size) {
        throw std::out_of_range("Индекс для вставки вне диапазона");
    }
    if (size == capacity) {
        int newCapacity = (capacity == 0) ? 1 : capacity * 2;
        reallocate(newCapacity);
    }
    for (int i = size; i > index; --i) {    // идем с конца, чтобы не затереть элементы
        data[i] = data[i - 1];
    }
    data[index] = value;
    ++size;
}

// Удаление элемента с позиции index. Элементы правее сдвигаются влево.
void IntVector::remove(int index) {
    checkIndex(index);
    for (int i = index; i < size - 1; ++i) {
        data[i] = data[i + 1];
    }
    --size;
}

// Удаление всех элементов. Ёмкость остается прежней.
void IntVector::clear() {
    size = 0;
}

// Изменение размера. Если вектор растет, новые элементы заполняются нулями.
void IntVector::resize(int newSize) {
    if (newSize < 0) {
        throw std::invalid_argument("Размер не может быть отрицательным");
    }
    if (newSize > capacity) {
        reallocate(newSize);
    }
    for (int i = size; i < newSize; ++i) {
        data[i] = 0;
    }
    size = newSize;
}

// --------------- Дополнительная функциональность (вариант 1) -----------------

// Резервирование памяти: ёмкость становится не меньше newCapacity.
// Размер и сами элементы не меняются. Если памяти уже достаточно, ничего не делает.
void IntVector::reserve(int newCapacity) {
    if (newCapacity < 0) {
        throw std::invalid_argument("Ёмкость не может быть отрицательной");
    }
    if (newCapacity > capacity) {
        reallocate(newCapacity);
    }
}

// Уменьшение ёмкости до размера: освобождает память, которая не используется
void IntVector::shrinkToFit() {
    if (capacity > size) {
        reallocate(size);
    }
}

// ------------------------------ Поиск и вывод --------------------------------

// Линейный поиск: возвращает индекс первого элемента, равного value, или -1
int IntVector::find(int value) const {
    for (int i = 0; i < size; ++i) {
        if (data[i] == value) {
            return i;
        }
    }
    return -1;
}

// Вывод в виде [1, 2, 3]
void IntVector::print() const {
    std::cout << "[";
    for (int i = 0; i < size; ++i) {
        std::cout << data[i];
        if (i < size - 1) {
            std::cout << ", ";
        }
    }
    std::cout << "]" << std::endl;
}
