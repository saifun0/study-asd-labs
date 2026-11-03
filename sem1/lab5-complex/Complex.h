// Лабораторная работа №5 (1 семестр). Вариант 1, средний уровень.
// Заголовочный файл: объявление класса Complex (комплексное число re + im*i).

#pragma once            // защита от повторного включения этого файла

#include <iostream>

class Complex {
private:
    double re;          // действительная часть
    double im;          // мнимая часть

public:
    // Конструкторы и деструктор
    Complex();                              // по умолчанию: 0 + 0i
    Complex(double re, double im);          // с параметрами
    Complex(const Complex& other);          // копирования
    ~Complex();

    // Оператор присваивания
    Complex& operator=(const Complex& other);

    // Геттеры и сеттеры
    double getRe() const;
    double getIm() const;
    void setRe(double re);
    void setIm(double im);

    // Дополнительная функциональность
    double abs() const;                     // модуль числа (базовый уровень)
    double arg() const;                     // аргумент числа в радианах (средний уровень)
    double argDegrees() const;              // аргумент числа в градусах

    // Арифметические операторы: возвращают новое число, сами операнды не меняются
    Complex operator+(const Complex& other) const;
    Complex operator-(const Complex& other) const;
    Complex operator*(const Complex& other) const;
    Complex operator/(const Complex& other) const;

    // Составное присваивание: меняют левый операнд и возвращают ссылку на него
    Complex& operator+=(const Complex& other);
    Complex& operator-=(const Complex& other);
    Complex& operator*=(const Complex& other);
    Complex& operator/=(const Complex& other);

    // Сравнение на равенство
    bool operator==(const Complex& other) const;
    bool operator!=(const Complex& other) const;

    // Сравнение "больше-меньше". Для комплексных чисел порядка нет,
    // поэтому числа сравниваются по модулю.
    bool operator<(const Complex& other) const;
    bool operator>(const Complex& other) const;
    bool operator<=(const Complex& other) const;
    bool operator>=(const Complex& other) const;

    // Инкремент и декремент: изменяют действительную часть на 1
    Complex& operator++();                  // префиксный ++z
    Complex operator++(int);                // постфиксный z++ (int нужен только для различия)
    Complex& operator--();                  // префиксный --z
    Complex operator--(int);                // постфиксный z--

    // Оператор вызова (функтор): z(n) возвращает число z в целой степени n
    Complex operator()(int n) const;

    // Ввод и вывод. Это дружественные функции, а не методы: слева от << и >>
    // стоит поток, а не объект Complex. Слово friend дает им доступ к re и im.
    friend std::ostream& operator<<(std::ostream& out, const Complex& z);
    friend std::istream& operator>>(std::istream& in, Complex& z);
};
