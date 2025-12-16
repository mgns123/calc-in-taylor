using namespace std;
#include <iostream>
#include <cmath>
#include <iomanip>

double calculate_ln_taylor(double x, int n_terms) {
	if (x <= -1.0 || x > 1.0) {
		return NAN;
	}

	double result = 0.0; // Переменная для накопления суммы членов ряда
	double term; // Переменная для хранения значения текущего члена ряда

	// Итерируемся по членам ряда от 1 до n_terms
	for (int n = 1; n <= n_terms; ++n) {
		// Вычисляем n-й член ряда: (-1)^(n+1) * x^n / n
		term = pow(-1.0, n + 1) * pow(x, n) / n;
		result += term; // Добавляем вычисленный член к сумме
	}
	return result; // Возвращаем приближенное значение ln(1+x)
}

int main() {
	setlocale(LC_ALL, "");
	double x;
	int n_terms;

	cout << "Введите значение x (где -1 < x <= 1): ";
	cin >> x;

	cout << "Введите количество членов ряда Тейлора для приближения: ";
	cin >> n_terms;

	// Проверка, что количество членов ряда положительное
	if (n_terms <= 0) {
		cerr << "Ошибка: Количество членов ряда должно быть положительным." << endl;
		return 1; // Возвращаем код ошибки
	}

	// Вычисляем приближенное значение ln(1+x) с помощью нашей функции
	double taylor_ln = calculate_ln_taylor(x, n_terms);

	// Проверяем, было ли вычисление успешным (т.е. x находится в области сходимости)
	if (isnan(taylor_ln)) {
		cerr << "Ошибка: Введенное значение x находится вне области сходимости ряда (-1 < x <= 1) или на границе расходимости (x = -1)." << endl;
	}
	else {
		// Для сравнения вычисляем точное значение ln(1+x) с помощью встроенной функции log
		double actual_ln = log(1.0 + x);

		// Устанавливаем формат вывода чисел с плавающей запятой
		cout << fixed << setprecision(8);

		// Выводим результаты
		cout << "Приближенное значение ln(1+" << x << ") с использованием " << n_terms << " членов ряда: " << taylor_ln << endl;
		cout << "Точное значение ln(1+" << x << "): " << actual_ln << endl;
		cout << "Разница: " << abs(taylor_ln - actual_ln) << endl;
	}

	return 0; 
}