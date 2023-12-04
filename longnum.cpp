/************************************************************
* Русакова Екатерина Алексеевна, ПИ-231                     *
* Поделиться: https://www.onlinegdb.com/online_c++_compiler *
* Дата: 05.12.2023                                          *
*************************************************************/

#include <iostream>
using namespace std;

int main() {
  setlocale(0,"");
  double num1, num2;
  cout << "Введите число: " << endl;
  cin >> num1;
  cout << "Введите число: " << endl;
  cin >> num2;
  cout << (num1 + num2) << endl;
  cout << (num1 * num2) << endl;
  cout << (num1 - num2) << endl;
  cout << (num1 / num2) << endl;
  if (num1 > num2) {
      cout << num1 << ">" << num2 << endl;
  } else if (num1 = num2) {
      cout << num1 << "=" << num2 << endl;
  } else {
      cout << num2 << ">" << num1 << endl;
  }
  system("pause");
  return 0;
}
