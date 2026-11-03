// Лабораторная работа №4 (1 семестр). Вариант 1, средний уровень.
// Заголовочный файл: объявление класса IntVector
// (динамический массив целых чисел).

#pragma once            // защита от повторного включения этого файла

class IntVector {
private:
    int* data;          // указатель на массив в динамической памяти (куче)
    int size;           // сколько элементов сейчас хранится
    int capacity;       // на сколько элементов выделена память

    // Вспомогательные методы, нужны только внутри класса
    void checkIndex(int index) const;       // бросает исключение, если индекс неправильный
    void reallocate(int newCapacity);       // переносит элементы в новый массив другой ёмкости

public:
    // Конструкторы
    IntVector();                            // по умолчанию: пустой вектор
    explicit IntVector(int n);              // n элементов, заполненных нулями
    IntVector(int n, int value);            // n элементов, заполненных значением value
    IntVector(const IntVector& other);      // копирования (глубокая копия)

    // Деструктор: освобождает память
    ~IntVector();

    // Оператор присваивания (вместе с деструктором и конструктором копирования
    // составляет "правило трёх")
    IntVector& operator=(const IntVector& other);

    // Доступ к элементу по индексу с проверкой границ
    int& operator[](int index);                 // для чтения и записи
    const int& operator[](int index) const;     // для константных объектов (только чтение)

    // Методы доступа
    int getSize() const;
    int getCapacity() const;
    bool isEmpty() const;

    // Методы изменения
    void pushBack(int value);               // добавить в конец
    void popBack();                         // удалить последний элемент
    void insert(int index, int value);      // вставить value на позицию index
    void remove(int index);                 // удалить элемент с позиции index
    void clear();                           // удалить все элементы
    void resize(int newSize);               // изменить размер (новые элементы равны 0)

    // Дополнительная функциональность по варианту 1
    void reserve(int newCapacity);          // зарезервировать память заранее
    void shrinkToFit();                     // уменьшить ёмкость до размера

    // Поиск и вывод
    int find(int value) const;              // индекс первого вхождения или -1
    void print() const;
};
