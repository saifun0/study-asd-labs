// Лабораторная работа №3 (1 семестр)
// Создание простых классов. Методы-аксессоры (геттеры/сеттеры).
// Вариант 1, средний уровень: класс Date (день, месяц, год).
// Функция 1: определить, является ли год високосным.
// Функция 2: увеличить дату на 5 дней.
// Демонстрационная программа.

#define NOMINMAX        // чтобы windows.h не подменял std::min и std::max своими макросами
#include <windows.h>    // SetConsoleCP, SetConsoleOutputCP: русский язык в консоли

#include <cstdlib>
#include <iostream>
#include <string>

#include "Date.h"

using namespace std;

// Запрашивает целое число, пока пользователь не введет его правильно
int readInt(const string& prompt) {
    while (true) {
        cout << prompt;
        int value;
        if (cin >> value) {
            return value;
        }
        if (cin.eof()) {                // ввод закрыт (например, нажали Ctrl+Z)
            cout << endl << "Ввод завершен." << endl;
            exit(0);
        }
        cout << "Ошибка: нужно ввести целое число." << endl;
        cin.clear();
        cin.ignore(10000, '\n');
    }
}

// Печатает сведения о дате: саму дату и високосный ли год
void printInfo(const string& title, const Date& date) {
    cout << title << ": " << date.toString();
    if (date.isLeapYear()) {
        cout << " (год високосный)" << endl;
    }
    else {
        cout << " (год не високосный)" << endl;
    }
}

int main() {
    // русские буквы в консоли: и вывод, и ввод в кодировке Windows-1251
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    cout << "=== Демонстрация работы с классом Date ===" << endl;

    // 1. Конструктор по умолчанию
    cout << endl << "--- 1. Объект, созданный конструктором по умолчанию ---" << endl;
    Date date1;
    printInfo("date1", date1);

    // 2. Сеттеры и геттеры
    cout << endl << "--- 2. Изменение даты через сеттеры, чтение через геттеры ---" << endl;
    date1.setYear(2023);
    date1.setMonth(12);
    date1.setDay(27);
    cout << "День: " << date1.getDay() << ", месяц: " << date1.getMonth()
         << ", год: " << date1.getYear() << endl;
    printInfo("date1", date1);

    // 3. Параметризованный конструктор (объект с константными значениями)
    cout << endl << "--- 3. Объект, созданный параметризованным конструктором ---" << endl;
    Date date2(28, 2, 2024);
    printInfo("date2", date2);

    // 4. Конструктор копирования
    cout << endl << "--- 4. Объект, созданный конструктором копирования ---" << endl;
    Date date3 = date2;                 // то же самое, что Date date3(date2);
    printInfo("date3", date3);

    // 5. Функция обработки 2: увеличить дату на 5 дней
    cout << endl << "--- 5. Увеличение даты на 5 дней ---" << endl;
    date2.addFiveDays();                // переход через 29 февраля високосного года
    printInfo("date2 после увеличения", date2);
    printInfo("date3 (копия не изменилась)", date3);
    date1.addFiveDays();                // переход через конец года
    printInfo("date1 после увеличения", date1);

    // 6. Проверки в сеттерах и в конструкторе
    cout << endl << "--- 6. Проверка корректности данных ---" << endl;
    date3.setDay(31);                   // в феврале нет 31 числа
    date3.setMonth(13);                 // месяца 13 не бывает
    date3.setYear(0);                   // год вне допустимых границ
    Date leapDay(29, 2, 2024);
    leapDay.setYear(2023);              // в 2023 году нет 29 февраля
    Date wrong(31, 4, 2024);            // в апреле 30 дней
    printInfo("date3", date3);
    printInfo("leapDay", leapDay);
    printInfo("wrong", wrong);

    // 7. Объект со значениями, введенными с клавиатуры
    cout << endl << "--- 7. Дата, введенная с клавиатуры ---" << endl;
    int day = readInt("Введите день: ");
    int month = readInt("Введите месяц: ");
    int year = readInt("Введите год: ");
    Date userDate(day, month, year);
    printInfo("Ваша дата", userDate);
    userDate.addFiveDays();
    printInfo("Через 5 дней", userDate);

    cout << endl << "=== Завершение программы (сейчас сработают деструкторы) ===" << endl;
    return 0;
}
