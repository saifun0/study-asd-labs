// Лабораторная работа №5 (1 семестр)
// Перегрузка операторов. Дружественные функции.
// Вариант 1, средний уровень: класс Complex (re, im), дополнительно аргумент числа.
// Демонстрационная программа.

#define NOMINMAX        // чтобы windows.h не подменял std::min и std::max своими макросами
#include <windows.h>    // SetConsoleCP, SetConsoleOutputCP: русский язык в консоли

#include <iostream>
#include <stdexcept>

#include "Complex.h"

using namespace std;

// Для вывода результатов сравнения словами
const char* yesNo(bool value) {
    return value ? "да" : "нет";
}

int main() {
    // русские буквы в консоли: и вывод, и ввод в кодировке Windows-1251
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    cout << "=== Демонстрация работы класса Complex ===" << endl;

    // 1. Конструкторы, геттеры и сеттеры
    cout << endl << "--- 1. Конструкторы, геттеры, сеттеры ---" << endl;
    Complex zero;               // по умолчанию
    Complex a(3, 4);            // с параметрами
    Complex b(1, -2);
    Complex copyOfA = a;        // копирования
    cout << "zero = " << zero << endl;
    cout << "a = " << a << endl;
    cout << "b = " << b << endl;
    cout << "copyOfA = " << copyOfA << endl;
    cout << "a.getRe() = " << a.getRe() << ", a.getIm() = " << a.getIm() << endl;
    zero.setRe(7);
    zero.setIm(-1);
    cout << "zero после setRe(7) и setIm(-1): " << zero << endl;

    // 2. Модуль и аргумент
    cout << endl << "--- 2. Модуль и аргумент ---" << endl;
    cout << "|a| = " << a.abs() << endl;
    cout << "arg(a) = " << a.arg() << " рад = " << a.argDegrees() << " град" << endl;
    cout << "arg(b) = " << b.arg() << " рад = " << b.argDegrees() << " град" << endl;

    // 3. Арифметические операторы
    cout << endl << "--- 3. Арифметические операторы ---" << endl;
    cout << "a + b = " << a + b << endl;
    cout << "a - b = " << a - b << endl;
    cout << "a * b = " << a * b << endl;
    cout << "a / b = " << a / b << endl;

    // 4. Составное присваивание
    cout << endl << "--- 4. Составное присваивание ---" << endl;
    Complex c = a;
    c += b;
    cout << "c = a;  c += b:  " << c << endl;
    c -= b;
    cout << "c -= b:          " << c << endl;
    c *= b;
    cout << "c *= b:          " << c << endl;
    c /= b;
    cout << "c /= b:          " << c << endl;

    // 5. Сравнение
    cout << endl << "--- 5. Сравнение ---" << endl;
    cout << "a == copyOfA? " << yesNo(a == copyOfA) << endl;
    cout << "a != b?       " << yesNo(a != b) << endl;
    cout << "Сравнение по модулю: |a| = " << a.abs() << ", |b| = " << b.abs() << endl;
    cout << "a < b?  " << yesNo(a < b) << endl;
    cout << "a > b?  " << yesNo(a > b) << endl;
    cout << "a <= b? " << yesNo(a <= b) << endl;
    cout << "a >= b? " << yesNo(a >= b) << endl;

    // 6. Инкремент и декремент
    cout << endl << "--- 6. Инкремент и декремент (меняют действительную часть) ---" << endl;
    Complex d(5, 5);
    cout << "d = " << d << endl;
    cout << "++d возвращает " << ++d << ", после этого d = " << d << endl;
    Complex returned = d++;     // постфиксный возвращает старое значение
    cout << "d++ возвращает " << returned << ", после этого d = " << d << endl;
    cout << "--d возвращает " << --d << ", после этого d = " << d << endl;
    returned = d--;
    cout << "d-- возвращает " << returned << ", после этого d = " << d << endl;

    // 7. Оператор вызова (функтор): возведение в целую степень
    cout << endl << "--- 7. Оператор () : z(n) это z в степени n ---" << endl;
    Complex i(0, 1);            // мнимая единица
    cout << "i = " << i << endl;
    cout << "i(2) = " << i(2) << "  (i в квадрате равно -1)" << endl;
    cout << "a(2) = " << a(2) << endl;
    cout << "a(0) = " << a(0) << endl;
    cout << "a(-1) = " << a(-1) << endl;

    // 8. Ввод с клавиатуры (перегруженный оператор >>)
    cout << endl << "--- 8. Ввод с клавиатуры ---" << endl;
    Complex user;
    cout << "Введите комплексное число (действительная и мнимая части через пробел): ";
    while (!(cin >> user)) {
        if (cin.eof()) {        // ввод закрыт (например, нажали Ctrl+Z)
            cout << endl << "Ввод завершен." << endl;
            return 0;
        }
        cout << "Ошибка: нужно ввести два числа. Попробуйте еще раз: ";
        cin.clear();
        cin.ignore(10000, '\n');
    }
    cout << "Вы ввели: " << user << endl;
    cout << "Модуль: " << user.abs() << ", аргумент: " << user.argDegrees() << " град" << endl;
    cout << "user + a = " << user + a << endl;
    cout << "user * a = " << user * a << endl;

    // 9. Обработка ошибки: деление на ноль
    cout << endl << "--- 9. Деление на ноль ---" << endl;
    try {
        Complex nothing;        // 0 + 0i
        cout << "a / 0 = ";
        cout << a / nothing << endl;
    }
    catch (const runtime_error& e) {
        cout << "исключение runtime_error: " << e.what() << endl;
    }

    cout << endl << "=== Завершение программы ===" << endl;
    return 0;
}
