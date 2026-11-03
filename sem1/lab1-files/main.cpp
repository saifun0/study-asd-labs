// Лабораторная работа №1 (1 семестр)
// Файловые потоки ввода-вывода. Работа с текстовыми и бинарными файлами.
// Вариант 1, средний уровень: задания 6, 9 и 10.

#define NOMINMAX        // чтобы windows.h не подменял std::min и std::max своими макросами
#include <windows.h>    // SetConsoleCP, SetConsoleOutputCP: русский язык в консоли

#include <cstdlib>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

// ======================= Общие вспомогательные функции =======================

// Сбрасывает ошибку ввода и выбрасывает остаток неправильно введенной строки
void clearInput() {
    cin.clear();
    cin.ignore(10000, '\n');
}

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
        clearInput();
    }
}

// Запрашивает целое число из отрезка [minValue, maxValue]
int readIntInRange(const string& prompt, int minValue, int maxValue) {
    while (true) {
        int value = readInt(prompt);
        if (value >= minValue && value <= maxValue) {
            return value;
        }
        cout << "Ошибка: число должно быть от " << minValue << " до " << maxValue << "." << endl;
    }
}

// Запрашивает действительное число, пока пользователь не введет его правильно
double readDouble(const string& prompt) {
    while (true) {
        cout << prompt;
        double value;
        if (cin >> value) {
            return value;
        }
        if (cin.eof()) {
            cout << endl << "Ввод завершен." << endl;
            exit(0);
        }
        cout << "Ошибка: нужно ввести число (дробная часть через точку)." << endl;
        clearInput();
    }
}

// ================================ Задание 6 ==================================
// Дан файл f, компоненты которого являются действительными числами.
// Найти произведение компонент файла.
// Файл создается в текстовом редакторе (или из программы), его содержимое
// выводится на экран, результаты сохраняются в новый файл.

const string TEXT_FILE = "f.txt";          // исходный файл с числами
const string RESULT_FILE = "result.txt";   // файл с результатами

// Проверяет, существует ли файл: пробуем открыть его на чтение
bool fileExists(const string& name) {
    ifstream in(name);
    return in.is_open();
}

// Создает текстовый файл с действительными числами, введенными с клавиатуры
void createTextFile(const string& name) {
    int n = readIntInRange("Сколько чисел записать в файл? ", 1, 1000);

    ofstream out(name);                    // старое содержимое файла стирается
    if (!out.is_open()) {
        cout << "Ошибка: не удалось создать файл " << name << endl;
        return;
    }
    out << setprecision(15);               // чтобы не потерять знаки после запятой
    for (int i = 0; i < n; ++i) {
        double x = readDouble("Число " + to_string(i + 1) + ": ");
        out << x << " ";
    }
    cout << "Файл " << name << " создан." << endl;
}   // здесь поток out уничтожается, и файл закрывается автоматически

// Просмотр содержимого текстового файла: выводит его на экран построчно
void showTextFile(const string& name) {
    ifstream in(name);
    if (!in.is_open()) {
        cout << "Ошибка: не удалось открыть файл " << name << endl;
        return;
    }
    cout << "--- Содержимое файла " << name << " ---" << endl;
    string line;
    while (getline(in, line)) {
        cout << line << endl;
    }
    cout << "------------------------------" << endl;
}

void task6() {
    cout << endl << "=== Задание 6. Произведение компонент текстового файла ===" << endl;

    // 1. Готовим исходный файл
    if (!fileExists(TEXT_FILE)) {
        cout << "Файл " << TEXT_FILE << " не найден, создадим его." << endl;
        createTextFile(TEXT_FILE);
    }
    else {
        cout << "Файл " << TEXT_FILE << " найден." << endl;
        int answer = readIntInRange("1 - использовать его, 2 - ввести новые числа: ", 1, 2);
        if (answer == 2) {
            createTextFile(TEXT_FILE);
        }
    }

    // 2. Просмотр содержимого файла
    showTextFile(TEXT_FILE);

    // 3. Читаем числа из файла и считаем произведение
    ifstream in(TEXT_FILE);
    if (!in.is_open()) {
        cout << "Ошибка: не удалось открыть файл " << TEXT_FILE << endl;
        return;
    }
    double product = 1.0;      // произведение начинаем с 1: если начать с 0, получится 0
    int count = 0;             // сколько чисел прочитали
    double x;
    while (in >> x) {          // читаем, пока в файле есть числа
        product *= x;
        ++count;
    }
    bool badData = !in.eof();  // остановились не в конце файла, значит встретилось не число
    in.close();

    if (count == 0) {
        cout << "В файле нет чисел, произведение найти нельзя." << endl;
        return;
    }
    if (badData) {
        cout << "Внимание: в файле встретились данные, которые не являются числом." << endl;
        cout << "Обработаны только числа, стоящие до них." << endl;
    }

    cout << "Количество чисел в файле: " << count << endl;
    cout << "Произведение компонент файла: " << product << endl;

    // 4. Сохраняем результаты в новый файл
    ofstream out(RESULT_FILE);
    if (!out.is_open()) {
        cout << "Ошибка: не удалось создать файл " << RESULT_FILE << endl;
        return;
    }
    out << "Исходный файл: " << TEXT_FILE << endl;
    out << "Количество чисел: " << count << endl;
    out << "Произведение компонент файла: " << product << endl;
    cout << "Результаты сохранены в файл " << RESULT_FILE << endl;
}

// ================================ Задание 9 ==================================
// Ввести некоторое количество целых чисел и записать их в бинарный файл.
// Переписать бинарный файл так, чтобы каждое значение было увеличено в два раза.
// Распечатать числа до и после изменения данных в файле.
// (В методичке числа вводятся в Memo или StringGrid, в консольной программе
// вместо этого используется ввод с клавиатуры.)

const string NUMBERS_FILE = "numbers.bin";

// Записывает целые числа в бинарный файл (старое содержимое стирается)
bool writeNumbers(const string& name, const vector<int>& numbers) {
    ofstream out(name, ios::binary);
    if (!out.is_open()) {
        return false;
    }
    for (int value : numbers) {
        // write получает адрес данных (как указатель на байты) и их размер в байтах,
        // то есть в файл попадают те же 4 байта, которыми число хранится в памяти
        out.write(reinterpret_cast<const char*>(&value), sizeof(value));
    }
    return true;
}

// Читает все целые числа из бинарного файла
vector<int> readNumbers(const string& name) {
    vector<int> numbers;
    ifstream in(name, ios::binary);
    int value;
    // read возвращает поток; когда данные закончатся, условие цикла станет ложным
    while (in.read(reinterpret_cast<char*>(&value), sizeof(value))) {
        numbers.push_back(value);
    }
    return numbers;
}

void printNumbers(const vector<int>& numbers) {
    for (int value : numbers) {
        cout << value << " ";
    }
    cout << endl;
}

void task9() {
    cout << endl << "=== Задание 9. Целые числа в бинарном файле ===" << endl;

    // 1. Ввод чисел с клавиатуры
    int n = readIntInRange("Сколько целых чисел ввести? ", 1, 1000);
    vector<int> numbers(n);
    for (int i = 0; i < n; ++i) {
        numbers[i] = readInt("Число " + to_string(i + 1) + ": ");
    }

    // 2. Запись в бинарный файл
    if (!writeNumbers(NUMBERS_FILE, numbers)) {
        cout << "Ошибка: не удалось создать файл " << NUMBERS_FILE << endl;
        return;
    }
    cout << "Числа записаны в бинарный файл " << NUMBERS_FILE << endl;

    // 3. Читаем числа обратно из файла и печатаем
    vector<int> fromFile = readNumbers(NUMBERS_FILE);
    cout << "Числа в файле до изменения:    ";
    printNumbers(fromFile);

    // 4. Увеличиваем каждое значение в два раза и переписываем файл
    for (int& value : fromFile) {      // ссылка, чтобы менять сами элементы вектора
        value *= 2;
    }
    if (!writeNumbers(NUMBERS_FILE, fromFile)) {
        cout << "Ошибка: не удалось переписать файл " << NUMBERS_FILE << endl;
        return;
    }

    // 5. Снова читаем из файла, чтобы убедиться, что данные в нем изменились
    vector<int> changed = readNumbers(NUMBERS_FILE);
    cout << "Числа в файле после изменения: ";
    printNumbers(changed);
}

// ================================ Задание 10 =================================
// Создать бинарный файл, компонентами которого является структура с полями:
// фамилия и инициалы студента, номер группы, успеваемость (массив из трех
// дисциплин), размер стипендии.
// Переписать бинарный файл так, чтобы для студентов, не имеющих двоек,
// размер стипендии был увеличен на 30%.

const string STUDENTS_FILE = "students.bin";

struct Student {
    char fio[50];       // фамилия и инициалы. Массив char, а не string: string хранит
                        // текст в другом месте памяти, и в файл попал бы только адрес
    int group;          // номер группы
    int marks[3];       // оценки по трем дисциплинам (от 2 до 5)
    double stipend;     // размер стипендии
};

// Записывает всех студентов в бинарный файл (старое содержимое стирается)
bool writeStudents(const string& name, const vector<Student>& students) {
    ofstream out(name, ios::binary);
    if (!out.is_open()) {
        return false;
    }
    for (const Student& s : students) {
        out.write(reinterpret_cast<const char*>(&s), sizeof(Student));   // структура целиком
    }
    return true;
}

// Читает всех студентов из бинарного файла
vector<Student> readStudents(const string& name) {
    vector<Student> students;
    ifstream in(name, ios::binary);
    Student s;
    while (in.read(reinterpret_cast<char*>(&s), sizeof(Student))) {
        students.push_back(s);
    }
    return students;
}

// Печатает список студентов в виде таблицы
void printStudents(const vector<Student>& students) {
    // запоминаем настройки вывода, чтобы потом вернуть их обратно
    ios::fmtflags oldFlags = cout.flags();
    streamsize oldPrecision = cout.precision();

    cout << left << setw(4) << "N" << setw(24) << "Фамилия и инициалы"
         << setw(9) << "Группа" << setw(10) << "Оценки" << "Стипендия" << endl;
    for (size_t i = 0; i < students.size(); ++i) {
        const Student& s = students[i];
        cout << left << setw(4) << (i + 1) << setw(24) << s.fio << setw(9) << s.group
             << s.marks[0] << " " << s.marks[1] << " " << s.marks[2] << "     "
             << fixed << setprecision(2) << s.stipend << endl;
    }

    cout.flags(oldFlags);
    cout.precision(oldPrecision);
}

// true, если у студента нет ни одной двойки
bool hasNoTwos(const Student& s) {
    for (int i = 0; i < 3; ++i) {
        if (s.marks[i] <= 2) {
            return false;
        }
    }
    return true;
}

// Ввод списка студентов с клавиатуры
vector<Student> inputStudents() {
    int n = readIntInRange("Сколько студентов ввести? ", 1, 100);
    vector<Student> students;
    for (int i = 0; i < n; ++i) {
        Student s = {};                         // все поля заполняются нулями
        cout << "Студент " << (i + 1) << ":" << endl;

        cout << "  Фамилия и инициалы: ";
        cin >> ws;                              // пропускаем Enter, оставшийся от прошлого ввода
        cin.getline(s.fio, sizeof(s.fio));      // читаем строку целиком, вместе с пробелами
        if (cin.fail() && !cin.eof()) {         // ввели больше 49 символов: лишнее отбрасываем
            clearInput();
        }

        s.group = readIntInRange("  Номер группы: ", 1, 100000);
        for (int j = 0; j < 3; ++j) {
            s.marks[j] = readIntInRange("  Оценка по дисциплине " + to_string(j + 1) + " (2-5): ", 2, 5);
        }
        s.stipend = readDouble("  Размер стипендии: ");
        while (s.stipend < 0) {
            cout << "Ошибка: стипендия не может быть отрицательной." << endl;
            s.stipend = readDouble("  Размер стипендии: ");
        }
        students.push_back(s);
    }
    return students;
}

// Готовый список студентов, чтобы быстро показать работу программы
vector<Student> sampleStudents() {
    vector<Student> students = {
        { "Иванов И.И.",   101, { 5, 4, 5 }, 3000.0 },
        { "Петров П.П.",   101, { 2, 4, 3 }, 2500.0 },
        { "Сидорова А.А.", 102, { 4, 4, 3 }, 2500.0 },
        { "Кузнецов Д.С.", 102, { 3, 2, 2 }, 2000.0 },
        { "Смирнова Е.В.", 103, { 5, 5, 5 }, 4000.0 }
    };
    return students;
}

void task10() {
    cout << endl << "=== Задание 10. Структуры в бинарном файле ===" << endl;

    // 1. Получаем список студентов
    int answer = readIntInRange("1 - ввести студентов с клавиатуры, 2 - взять готовый пример: ", 1, 2);
    vector<Student> students;
    if (answer == 1) {
        students = inputStudents();
    }
    else {
        students = sampleStudents();
    }

    // 2. Создаем бинарный файл
    if (!writeStudents(STUDENTS_FILE, students)) {
        cout << "Ошибка: не удалось создать файл " << STUDENTS_FILE << endl;
        return;
    }
    cout << "Создан бинарный файл " << STUDENTS_FILE << endl;

    // 3. Читаем файл и показываем его содержимое до изменения
    vector<Student> fromFile = readStudents(STUDENTS_FILE);
    cout << endl << "Содержимое файла до изменения:" << endl;
    printStudents(fromFile);

    // 4. Студентам без двоек увеличиваем стипендию на 30% и переписываем файл
    int changedCount = 0;
    for (Student& s : fromFile) {
        if (hasNoTwos(s)) {
            s.stipend *= 1.3;
            ++changedCount;
        }
    }
    if (!writeStudents(STUDENTS_FILE, fromFile)) {
        cout << "Ошибка: не удалось переписать файл " << STUDENTS_FILE << endl;
        return;
    }

    // 5. Снова читаем файл и показываем результат
    vector<Student> changed = readStudents(STUDENTS_FILE);
    cout << endl << "Содержимое файла после изменения:" << endl;
    printStudents(changed);
    cout << "Стипендия увеличена у студентов: " << changedCount << endl;
}

// ================================== Меню =====================================

int main() {
    // русские буквы в консоли: и вывод, и ввод в кодировке Windows-1251
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    // подсказка, в какой папке искать f.txt, result.txt и бинарные файлы
    char folder[MAX_PATH];
    if (GetCurrentDirectoryA(MAX_PATH, folder) > 0) {
        cout << "Файлы программы лежат в папке: " << folder << endl;
    }

    int choice;
    do {
        cout << endl;
        cout << "===== Лабораторная работа 1. Файлы =====" << endl;
        cout << "1 - Задание 6:  произведение чисел из текстового файла" << endl;
        cout << "2 - Задание 9:  целые числа в бинарном файле (увеличить в 2 раза)" << endl;
        cout << "3 - Задание 10: студенты в бинарном файле (стипендия +30%)" << endl;
        cout << "0 - Выход" << endl;
        choice = readIntInRange("Ваш выбор: ", 0, 3);

        switch (choice) {
        case 1: task6(); break;
        case 2: task9(); break;
        case 3: task10(); break;
        }
    } while (choice != 0);

    return 0;
}
