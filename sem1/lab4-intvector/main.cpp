// Лабораторная работа №4 (1 семестр)
// Реализация класса "Динамический массив целых чисел" с конструкторами,
// деструктором и основными операциями.
// Вариант 1, средний уровень: полное "правило трёх", все основные методы,
// дополнительно reserve(int newCapacity) и shrinkToFit().
// Демонстрационная программа.

#define NOMINMAX        // чтобы windows.h не подменял std::min и std::max своими макросами
#include <windows.h>    // SetConsoleCP, SetConsoleOutputCP: русский язык в консоли

#include <iostream>
#include <stdexcept>

#include "IntVector.h"

using namespace std;

// Печатает название вектора, его размер, ёмкость и содержимое
void show(const char* name, const IntVector& v) {
    cout << name << ": размер = " << v.getSize() << ", ёмкость = " << v.getCapacity() << ", элементы = ";
    v.print();
}

int main() {
    // русские буквы в консоли: и вывод, и ввод в кодировке Windows-1251
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    cout << "=== Демонстрация работы класса IntVector ===" << endl;

    // 1. Конструкторы
    cout << endl << "--- 1. Конструкторы ---" << endl;
    IntVector v1;               // по умолчанию
    IntVector v2(5);            // 5 нулей
    IntVector v3(4, 7);         // 4 семерки
    show("v1 (по умолчанию)", v1);
    show("v2 (размер 5)", v2);
    show("v3 (размер 4, значение 7)", v3);
    cout << "v1 пуст? " << (v1.isEmpty() ? "да" : "нет") << endl;

    // 2. Добавление в конец и автоматическое расширение
    cout << endl << "--- 2. pushBack: ёмкость удваивается, когда место заканчивается ---" << endl;
    for (int i = 1; i <= 9; ++i) {
        v1.pushBack(i * 10);
        cout << "pushBack(" << i * 10 << "): размер = " << v1.getSize()
             << ", ёмкость = " << v1.getCapacity() << endl;
    }
    show("v1", v1);

    // 3. Доступ по индексу
    cout << endl << "--- 3. Доступ по индексу ---" << endl;
    cout << "v1[0] = " << v1[0] << ", v1[8] = " << v1[8] << endl;
    v1[0] = 11;                 // запись через operator[]
    cout << "После v1[0] = 11: ";
    v1.print();

    // 4. Вставка, удаление, поиск
    cout << endl << "--- 4. insert, remove, popBack, find ---" << endl;
    v1.insert(2, 25);
    cout << "insert(2, 25):  ";
    v1.print();
    v1.remove(0);
    cout << "remove(0):      ";
    v1.print();
    v1.popBack();
    cout << "popBack():      ";
    v1.print();
    cout << "find(50) = " << v1.find(50) << " (индекс элемента)" << endl;
    cout << "find(999) = " << v1.find(999) << " (такого элемента нет)" << endl;

    // 5. Дополнительная функциональность: reserve
    cout << endl << "--- 5. reserve: резервирование памяти ---" << endl;
    show("v1 до reserve(50)", v1);
    v1.reserve(50);
    show("v1 после reserve(50)", v1);
    v1.reserve(10);             // меньше текущей ёмкости: ничего не меняется
    show("v1 после reserve(10)", v1);
    for (int i = 0; i < 5; ++i) {
        v1.pushBack(100 + i);   // память уже есть, перевыделений не происходит
    }
    show("v1 после пяти pushBack", v1);

    // 6. Дополнительная функциональность: shrinkToFit
    cout << endl << "--- 6. shrinkToFit: уменьшение ёмкости до размера ---" << endl;
    v1.shrinkToFit();
    show("v1 после shrinkToFit", v1);

    // 7. Изменение размера и очистка
    cout << endl << "--- 7. resize и clear ---" << endl;
    v3.resize(6);               // новые элементы равны нулю
    show("v3 после resize(6)", v3);
    v3.resize(2);
    show("v3 после resize(2)", v3);
    v3.clear();
    show("v3 после clear", v3);
    v3.shrinkToFit();           // после clear память еще занята, shrinkToFit ее освобождает
    show("v3 после shrinkToFit", v3);

    // 8. Правило трёх: конструктор копирования и оператор присваивания
    cout << endl << "--- 8. Глубокое копирование ---" << endl;
    IntVector copy = v1;        // конструктор копирования
    copy[0] = 999;              // меняем копию
    show("v1 (оригинал не изменился)", v1);
    show("copy", copy);

    IntVector assigned;
    assigned = v1;              // оператор присваивания
    assigned.pushBack(-1);
    show("v1 (оригинал не изменился)", v1);
    show("assigned", assigned);

    IntVector& sameVector = v1;
    v1 = sameVector;            // самоприсваивание: объект не должен испортиться
    show("v1 после самоприсваивания", v1);

    // 9. Обработка ошибок с помощью исключений
    cout << endl << "--- 9. Обработка ошибок ---" << endl;
    try {
        cout << "Обращение к v1[100]: ";
        cout << v1[100] << endl;
    }
    catch (const out_of_range& e) {
        cout << "исключение out_of_range: " << e.what() << endl;
    }
    try {
        cout << "popBack для пустого вектора: ";
        IntVector empty;
        empty.popBack();
    }
    catch (const underflow_error& e) {
        cout << "исключение underflow_error: " << e.what() << endl;
    }
    try {
        cout << "Создание вектора размера -3: ";
        IntVector bad(-3);
    }
    catch (const invalid_argument& e) {
        cout << "исключение invalid_argument: " << e.what() << endl;
    }
    try {
        cout << "insert(50, 1) при размере " << v1.getSize() << ": ";
        v1.insert(50, 1);
    }
    catch (const out_of_range& e) {
        cout << "исключение out_of_range: " << e.what() << endl;
    }
    try {
        cout << "reserve(-5): ";
        v1.reserve(-5);
    }
    catch (const invalid_argument& e) {
        cout << "исключение invalid_argument: " << e.what() << endl;
    }

    cout << endl << "=== Завершение программы ===" << endl;
    return 0;
}
