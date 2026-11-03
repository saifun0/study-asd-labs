// Лабораторная работа №3 (1 семестр). Вариант 1, средний уровень.
// Заголовочный файл: объявление класса Date (дата: день, месяц, год).

#pragma once            // защита от повторного включения этого файла

#include <string>

class Date {
private:
    // Закрытые поля: изменить их снаружи можно только через сеттеры
    int day;
    int month;
    int year;

    // Вспомогательные методы, нужны только внутри класса
    bool isLeap(int y) const;                   // високосный ли год y
    int daysInMonth(int m, int y) const;        // сколько дней в месяце m года y
    bool isValid(int d, int m, int y) const;    // существует ли такая дата

public:
    // Конструкторы
    Date();                                 // по умолчанию: 01.01.2000
    Date(int day, int month, int year);     // с параметрами
    Date(const Date& other);                // копирования

    // Деструктор (выводит сообщение об уничтожении объекта)
    ~Date();

    // Геттеры: возвращают значения полей и не меняют объект (поэтому const)
    int getDay() const;
    int getMonth() const;
    int getYear() const;

    // Сеттеры: меняют поля, но только если дата останется правильной
    void setDay(int day);
    void setMonth(int month);
    void setYear(int year);

    // Функция обработки 1: определить, является ли год високосным
    bool isLeapYear() const;

    // Функция обработки 2: увеличить дату на 5 дней
    void addFiveDays();

    // Увеличить дату на произвольное количество дней (используется в addFiveDays)
    void addDays(int count);

    // Строка с информацией об объекте в виде ДД.ММ.ГГГГ
    std::string toString() const;
};
