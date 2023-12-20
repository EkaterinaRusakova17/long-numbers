/************************************************************
* Русакова Екатерина Алексеевна, ПИ-231                     *
* Поделиться: https://www.onlinegdb.com/online_c++_compiler *
* Дата: 05.12.2023                                          *
*************************************************************/

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

// Функция для добавления двух строк с числами
string addStrings(const string number1, const string number2) {
    string result = ""; // Результат сложения
    int carry = 0; // Разряд переноса
    int FirstCurrentIndex = number1.length() - 1; // Индекс текущей цифры в number1
    int secondCurrentIndex = number2.length() - 1; // Индекс текущей цифры в number2

    // Складываем цифры чисел, пока не достигнем конца одного из чисел
    while (FirstCurrentIndex >= 0 || secondCurrentIndex >= 0) {
        int digit1 = (FirstCurrentIndex >= 0) ? number1[FirstCurrentIndex] - '0' : 0; // Текущая цифра number1
        int digit2 = (secondCurrentIndex >= 0) ? number2[secondCurrentIndex] - '0' : 0; // Текущая цифра number2

        // Вычисляем сумму цифр и разряд переноса
        int sum = digit1 + digit2 + carry;
        carry = sum / 10;
        sum %= 10;

        // Добавляем текущую цифру суммы в результат
        result.insert(0, 1, sum + '0');

        // Уменьшаем индексы
        --FirstCurrentIndex;
        --secondCurrentIndex;
    }

    // Если остался разряд переноса, добавляем его в результат
    if (carry > 0) {
        result.insert(0, 1, carry + '0');
    }

    return result;
}

// Функция для вычитания двух строк с числами
string subtractLongNumbers(const string number1, const string number2) {
    vector<int> result; // Результат вычитания
    vector<int> arr1(number1.length()); // Цифры первого числа
    vector<int> arr2(number2.length()); // Цифры второго числа

    // Заполняем массивы цифрами чисел (обратный порядок)
    for (int index = 0; index < number1.length(); ++index) {
        arr1[index] = number1[number1.length() - 1 - index] - '0';
    }
    for (int index = 0; index < number2.length(); ++index) {
        arr2[index] = number2[number2.length() - 1 - index] - '0';
    }

    int borrow = 0; // Разряд заема

    // Выполняем вычитание цифр чисел
    for (int index = 0; index < arr1.size(); ++index) {
        int diff = arr1[index] - borrow;
        if (index < arr2.size()) {
            diff -= arr2[index];
        }
        if (diff < 0) {
            diff += 10;
            borrow = 1;
        }
        else {
            borrow = 0;
        }
        result.push_back(diff);
    }

    // Удаляем ведущие нули в результате
    while (result.size() > 1 && result.back() == 0) {
        result.pop_back();
    }

    // Преобразуем результат обратно в строку
    string resultString = "";
    for (int index = result.size() - 1; index >= 0; --index) {
        resultString += to_string(result[index]);
    }

    return resultString;
}

// Функция для умножения двух строк с числами
string multiplyStrings(const string number1, const string number2) {
    string result = "0"; // Результат умножения

    // Умножаем каждую цифру num1 на num2 и добавляем результаты
    // с учетом позиции цифры в исходном числе
    for (int index = number1.length() - 1; index >= 0; --index) {
        string temporaryResult = ""; // Результат умножения текущей цифры num1 на num2
        int carry = 0; // Разряд переноса

        // Умножаем текущую цифру num1 на num2
        int digit1 = number1[index] - '0';
        for (int ind = number2.length() - 1; ind >= 0; --ind) {
            int digit2 = number2[ind] - '0';

            int product = digit1 * digit2 + carry;
            carry = product / 10;
            product %= 10;

            temporaryResult.insert(0, 1, product + '0');
        }

        // Если остался разряд переноса, добавляем его в результат
        if (carry > 0) {
            temporaryResult.insert(0, 1, carry + '0');
        }

        // Добавляем нули в конец в зависимости от позиции цифры
        for (int indicator = index; indicator < number1.length() - 1; ++indicator) {
            temporaryResult.append("0");
        }

        // Складываем результат текущего умножения с общим результатом
        result = addStrings(result, temporaryResult);
    }

    return result;
}

// Функция для целочисленного деления двух строк с числами
string divideStrings(const string number1, const string number2) {
    string result = ""; // Частное от деления
    string dividend = number1; // Делимое

    // Если делимое меньше делителя, возвращаем 0
    if (dividend.length() < number2.length() ||
        (dividend.length() == number2.length() && dividend < number2)) {
        return "0";
    }

    // Производим деление пока делимое не станет меньше делителя
    while (dividend.length() >= number2.length()) {
        string quotient = ""; // Частное текущего деления
        string temporaryDividend = dividend.substr(0, number2.length()); // Подстрока делимого длины делителя

        // Вычитаем делитель из подстроки делимого
        while (temporaryDividend.length() > 0) {
            string temporaryQuotient = "0"; // Частное текущего вычитания
            string temporarySubtract = "";

            // Увеличиваем частное текущего вычитания на единицу
            while (temporarySubtract.length() < temporaryDividend.length() && temporarySubtract <= temporaryDividend) {
                temporarySubtract = addStrings(temporarySubtract, number2);
                temporaryQuotient = addStrings(temporaryQuotient, "1");
            }

            // Уменьшаем подстроку делимого на указанное число вычитаний
            temporaryDividend = subtractLongNumbers(temporaryDividend, temporarySubtract);

            // Удаляем ведущие нули
            while (temporaryDividend.length() > 1 && temporaryDividend[0] == '0') {
                temporaryDividend.erase(0, 1);
            }

            // Добавляем частное текущего вычитания в общее частное
            quotient.append(temporaryQuotient);
        }

        // Добавляем ведущие нули в частное в зависимости от позиции
        // подстроки делимого в исходном числе
        for (int index = 0; index < dividend.length() - temporaryDividend.length(); ++index) {
            quotient.insert(0, 1, '0');
        }

        // Добавляем текущее частное к общему частному
        result = addStrings(result, quotient);

        // Удаляем подстроку делимого из делимого
        dividend = dividend.substr(temporaryDividend.length(), dividend.length() - temporaryDividend.length());
    }

    return result;
}

// Функция для сравнения двух строк с числами
int compareStrings(const string number1, const string number2) {
    // Если длины чисел разные, меньшее число имеет меньшую длину
    if (number1.length() < number2.length()) {
        return -1;
    }
    else if (number1.length() > number2.length()) {
        return 1;
    }

    // Длины чисел равны, сравниваем цифры по порядку
    for (int index = 0; index < number1.length(); ++index) {
        if (number1[index] < number2[index]) {
            return -1;
        }
        else if (number1[index] > number2[index]) {
            return 1;
        }
    }

    // Числа равны
    return 0;
}

int main() {
    string number1, number2;
    cout << "Введите первое число: ";
    cin >> number1;
    cout << "Введите второе число: ";
    cin >> number2;

    // Сложение
    string sum = addStrings(number1, number2);
    cout << "Сумма: " << sum << endl;

    // Вычитание
    string difference = subtractLongNumbers(number1, number2);
    cout << "Разность: " << difference << endl;

    // Умножение
    string product = multiplyStrings(number1, number2);
    cout << "Произведение: " << product << endl;

    // Целочисленное деление
    string quotient = divideStrings(number1, number2);
    cout << "Частное: " << quotient << endl;

    // Сравнение
    int comparison = compareStrings(number1, number2);
    if (comparison < 0) {
        cout << "Первое число меньше второго" << endl;
    }
    else if (comparison > 0) {
        cout << "Первое число больше второго" << endl;
    }
    else {
        cout << "Числа равны" << endl;
    }

    return 0;
}
