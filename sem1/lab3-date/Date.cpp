// Лабораторная работа №3 (1 семестр). Вариант 1, средний уровень.
// Файл реализации: методы класса Date.

#include "Date.h"

#include <iostream>

// Границы допустимых значений года
const int MIN_YEAR = 1;
const int MAX_YEAR = 9999;

// ------------------------- Вспомогательные методы ----------------------------

// Год високосный, если делится на 4, но не на 100, либо делится на 400
bool Date::isLeap(int y) const {
    return (y % 4 == 0 && y % 100 != 0) || (y % 400 == 0);
}

// Количество дней в месяце m года y (в феврале високосного года 29 дней)
int Date::daysInMonth(int m, int y) const {
    const int days[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    if (m == 2 && isLeap(y)) {
        return 29;
    }
    return days[m - 1];         // месяцы считаются с 1, а индексы массива с 0
}

// Проверяет, существует ли дата d.m.y
bool Date::isValid(int d, int m, int y) const {
    if (y < MIN_YEAR || y > MAX_YEAR) {
        return false;
    }
    if (m < 1 || m > 12) {
        return false;
    }
    return d >= 1 && d <= daysInMonth(m, y);
}

// ------------------------------ Конструкторы ---------------------------------

// Конструктор по умолчанию. Поля инициализируются в списке инициализации.
Date::Date() : day(1), month(1), year(2000) {
    std::cout << "Вызван конструктор по умолчанию: " << toString() << std::endl;
}

// Параметризованный конструктор. Если дата неправильная, остается дата по умолчанию.
Date::Date(int day, int month, int year) : day(1), month(1), year(2000) {
    if (isValid(day, month, year)) {
        this->day = day;        // this->day это поле объекта, day это параметр
        this->month = month;
        this->year = year;
    }
    else {
        std::cout << "Ошибка: даты " << day << "." << month << "." << year
                  << " не существует, установлена дата по умолчанию." << std::endl;
    }
    std::cout << "Вызван параметризованный конструктор: " << toString() << std::endl;
}

// Конструктор копирования: новый объект получает те же значения полей
Date::Date(const Date& other) : day(other.day), month(other.month), year(other.year) {
    std::cout << "Вызван конструктор копирования: " << toString() << std::endl;
}

// -------------------------------- Деструктор ---------------------------------

Date::~Date() {
    std::cout << "Вызван деструктор для даты " << toString() << std::endl;
}

// --------------------------------- Геттеры -----------------------------------

int Date::getDay() const {
    return day;
}

int Date::getMonth() const {
    return month;
}

int Date::getYear() const {
    return year;
}

// --------------------------------- Сеттеры -----------------------------------
// Каждый сеттер проверяет, что после изменения дата останется существующей.

void Date::setDay(int day) {
    if (isValid(day, month, year)) {
        this->day = day;
    }
    else {
        std::cout << "Ошибка: в этом месяце нет дня с номером " << day << "." << std::endl;
    }
}

void Date::setMonth(int month) {
    if (month < 1 || month > 12) {
        std::cout << "Ошибка: месяц должен быть от 1 до 12." << std::endl;
    }
    else if (!isValid(day, month, year)) {
        // например, было 31 января, а месяц пытаются заменить на апрель (в нем 30 дней)
        std::cout << "Ошибка: в месяце " << month << " нет дня с номером " << day << "." << std::endl;
    }
    else {
        this->month = month;
    }
}

void Date::setYear(int year) {
    if (year < MIN_YEAR || year > MAX_YEAR) {
        std::cout << "Ошибка: год должен быть от " << MIN_YEAR << " до " << MAX_YEAR << "." << std::endl;
    }
    else if (!isValid(day, month, year)) {
        // единственный такой случай: 29 февраля, а новый год не високосный
        std::cout << "Ошибка: в " << year << " году нет 29 февраля." << std::endl;
    }
    else {
        this->year = year;
    }
}

// ---------------------------- Функции обработки ------------------------------

// Функция 1: является ли год этой даты високосным
bool Date::isLeapYear() const {
    return isLeap(year);
}

// Увеличивает дату на count дней. Прибавляем по одному дню: так проще всего
// правильно перейти через конец месяца и конец года.
void Date::addDays(int count) {
    if (count < 0) {
        std::cout << "Ошибка: количество дней не может быть отрицательным." << std::endl;
        return;
    }
    for (int i = 0; i < count; ++i) {
        ++day;
        if (day > daysInMonth(month, year)) {   // месяц закончился
            day = 1;
            ++month;
            if (month > 12) {                   // год закончился
                month = 1;
                ++year;
            }
        }
    }
}

// Функция 2: увеличить дату на 5 дней
void Date::addFiveDays() {
    addDays(5);
}

// ------------------------- Строка с информацией ------------------------------

// Формирует строку вида ДД.ММ.ГГГГ (с нулем перед однозначным днем и месяцем)
std::string Date::toString() const {
    std::string result;
    if (day < 10) {
        result += "0";
    }
    result += std::to_string(day) + ".";
    if (month < 10) {
        result += "0";
    }
    result += std::to_string(month) + ".";
    result += std::to_string(year);
    return result;
}
