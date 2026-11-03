// Лабораторная работа №5 (1 семестр). Вариант 1, средний уровень.
// Файл реализации: методы и операторы класса Complex.

#include "Complex.h"

#include <cmath>        // sqrt, atan2, fabs
#include <stdexcept>    // runtime_error

const double PI = 3.14159265358979323846;
const double EPS = 1e-9;    // погрешность: дробные числа нельзя надежно сравнивать через ==

// ------------------------ Конструкторы и деструктор --------------------------

Complex::Complex() : re(0.0), im(0.0) {
}

Complex::Complex(double re, double im) : re(re), im(im) {
}

Complex::Complex(const Complex& other) : re(other.re), im(other.im) {
}

// Класс не выделяет динамическую память, поэтому освобождать в деструкторе нечего
Complex::~Complex() {
}

// --------------------------- Оператор присваивания ---------------------------

Complex& Complex::operator=(const Complex& other) {
    if (this != &other) {       // защита от самоприсваивания
        re = other.re;
        im = other.im;
    }
    return *this;               // чтобы работала цепочка a = b = c
}

// ---------------------------- Геттеры и сеттеры ------------------------------

double Complex::getRe() const {
    return re;
}

double Complex::getIm() const {
    return im;
}

void Complex::setRe(double re) {
    this->re = re;              // this->re это поле, re это параметр
}

void Complex::setIm(double im) {
    this->im = im;
}

// --------------------- Дополнительная функциональность -----------------------

// Модуль: расстояние от точки (re, im) до начала координат
double Complex::abs() const {
    return std::sqrt(re * re + im * im);
}

// Аргумент: угол между положительной действительной осью и направлением на число.
// atan2 сама учитывает, в какой четверти лежит точка. Результат от -PI до PI.
// Для числа 0 аргумент не определен, atan2(0, 0) возвращает 0.
double Complex::arg() const {
    return std::atan2(im, re);
}

double Complex::argDegrees() const {
    return arg() * 180.0 / PI;
}

// ------------------------- Арифметические операторы --------------------------

Complex Complex::operator+(const Complex& other) const {
    return Complex(re + other.re, im + other.im);
}

Complex Complex::operator-(const Complex& other) const {
    return Complex(re - other.re, im - other.im);
}

// (a + bi)(c + di) = (ac - bd) + (ad + bc)i
Complex Complex::operator*(const Complex& other) const {
    return Complex(re * other.re - im * other.im,
                   re * other.im + im * other.re);
}

// (a + bi) / (c + di) = ((ac + bd) + (bc - ad)i) / (c*c + d*d)
Complex Complex::operator/(const Complex& other) const {
    double denominator = other.re * other.re + other.im * other.im;
    if (denominator == 0.0) {
        throw std::runtime_error("Деление на ноль");
    }
    return Complex((re * other.re + im * other.im) / denominator,
                   (im * other.re - re * other.im) / denominator);
}

// -------------------------- Составное присваивание ---------------------------
// Выражены через обычные операторы: считаем результат и записываем его в себя.

Complex& Complex::operator+=(const Complex& other) {
    *this = *this + other;
    return *this;
}

Complex& Complex::operator-=(const Complex& other) {
    *this = *this - other;
    return *this;
}

Complex& Complex::operator*=(const Complex& other) {
    *this = *this * other;
    return *this;
}

Complex& Complex::operator/=(const Complex& other) {
    *this = *this / other;
    return *this;
}

// -------------------------------- Сравнение ----------------------------------

// Числа равны, если совпадают и действительные, и мнимые части (с погрешностью EPS)
bool Complex::operator==(const Complex& other) const {
    return std::fabs(re - other.re) < EPS && std::fabs(im - other.im) < EPS;
}

bool Complex::operator!=(const Complex& other) const {
    return !(*this == other);
}

// Сравнение по модулю. Остальные три оператора выражены через operator<.
bool Complex::operator<(const Complex& other) const {
    return abs() < other.abs();
}

bool Complex::operator>(const Complex& other) const {
    return other < *this;
}

bool Complex::operator<=(const Complex& other) const {
    return !(other < *this);
}

bool Complex::operator>=(const Complex& other) const {
    return !(*this < other);
}

// ------------------------- Инкремент и декремент -----------------------------

// Префиксный ++z: сначала увеличиваем, потом возвращаем уже измененный объект
Complex& Complex::operator++() {
    ++re;
    return *this;
}

// Постфиксный z++: запоминаем старое значение, увеличиваем, возвращаем старое
Complex Complex::operator++(int) {
    Complex old = *this;
    ++re;
    return old;
}

Complex& Complex::operator--() {
    --re;
    return *this;
}

Complex Complex::operator--(int) {
    Complex old = *this;
    --re;
    return old;
}

// ----------------------------- Оператор вызова -------------------------------

// z(n): возведение в целую степень. z(0) = 1, z(3) = z*z*z, z(-2) = 1 / (z*z).
Complex Complex::operator()(int n) const {
    Complex result(1.0, 0.0);
    int count = (n >= 0) ? n : -n;          // сколько раз умножать
    for (int i = 0; i < count; ++i) {
        result *= *this;
    }
    if (n < 0) {
        result = Complex(1.0, 0.0) / result;    // отрицательная степень; для нуля будет исключение
    }
    return result;
}

// ------------------------------ Ввод и вывод ---------------------------------

// Вывод в виде 3+4i или 3-4i
std::ostream& operator<<(std::ostream& out, const Complex& z) {
    out << z.re;
    if (z.im >= 0) {
        out << "+";             // у отрицательной мнимой части минус выведется сам
    }
    out << z.im << "i";
    return out;                 // возвращаем поток, чтобы работала цепочка cout << a << b
}

// Ввод: два числа через пробел, действительная и мнимая части
std::istream& operator>>(std::istream& in, Complex& z) {
    double re, im;
    if (in >> re >> im) {       // меняем объект, только если ввод прошел успешно
        z.re = re;
        z.im = im;
    }
    return in;
}
