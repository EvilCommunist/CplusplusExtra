#include <iostream>
//#include<math.h>
using namespace std;
int main()
{
	setlocale(LC_CTYPE, "Russian");
	double i, a, b, c, step1, step2, step3, aend, bend, cend, check, e, ans, ans1, h, prom, chet, nechet, nechet1;
	int n;
	check = 3;
	ans = ans1 = prom = chet= nechet = nechet1 = 0;
	std :: cout << "Вычислим интегал несколькими методами" << endl;
	/* cout << "" << endl;
	cin >> e;*/
	e = 0.001;
	/* cout << "" << endl;
	cin >> a >> b;*/
	a = 0.5;
	b = 1.5;
	/* cout << "" << endl;
	cin >> h;*/
	h = 0.5;
	// Рассчёт значений функции в заданных точках
	step1 = pow(a - 4, 1/3);
	step2 = pow(sqrt(a), step1);
	aend = pow(sin(a * a), step2);
	step1 = pow(b - 4, 1/3);
	step2 = pow(sqrt(b), step1);
	bend = pow(sin(b * b), step2);
	c = a;
	// Метод левых прямоугольников
	while (check>=e)
	{
		for (i = a; i < b; i += h)
		{
			step1 = pow(c - 4, 1/3);
			step2 = pow(sqrt(c), step1);
			cend = pow(sin(c * c), step2);
			ans += h * cend;
			c += h;
		}
		check = abs(ans - ans1);
		ans1 = ans;
//		cout << ans << endl;
		ans = 0;
		h = h / 2;
		c = a;
	}
	std :: cout << "Метод левых прямоугольников: " << ans1 << endl;
	// Метод правых прямоугольников
	h = 0.5;
	c = a+h;
	check = 3;
	ans1 = 0;
	ans = 0;
	while (check >= e)
	{
		for (i = a+h; i <= b; i += h)
		{
			step1 = pow(c - 4, 1/3);
			step2 = pow(sqrt(c), step1);
			cend = pow(sin(c * c), step2);
			ans += h * cend;
			c += h;
		}
		check = abs(ans - ans1);
		ans1 = ans;
//		cout << ans << endl;
		ans = 0;
		h = h / 2;
		c = a;
	}
	std :: cout << "Метод правых прямоугольников: " << ans1 << endl;
	// Метод серединных прямоугольников
	h = 0.5;
	c = a;
	check = 3;
	ans1 = 0;
	ans = 0;
	while (check >= e)
	{
		for (i = a + h; i <= b; i += h)
		{
			step1 = pow(c - 4 +h/2, 1 / 3);
			step2 = pow(sqrt(c+h/2), step1);
			cend = pow(sin((c+h/2) * (c+h/2)), step2);
			ans += h * cend;
			c += h;
		}
		check = abs(ans - ans1);
		ans1 = ans;
//		cout << ans << endl;
		ans = 0;
		h = h / 2;
		c = a+h;
	}
	std :: cout << "Метод серединных прямоугольников: " << ans1 << endl;
	// Метод трапеций
	h = 0.5;
	c = a+h;
	check = 3;
	ans1 = 0;
	ans = 0;
	while (check >= e)
	{
		for (i = a + h; i < b; i += h)
		{
			step1 = pow(c - 4, 1 / 3);
			step2 = pow(sqrt(c), step1);
			cend = pow(sin(c * c), step2);
			prom += cend;
			c += h;
		}
		ans = h/2 * ((aend + bend)/2 + prom); // В отличие от формулы из методички берём сумму высоту трапеции делённую пополам, иначе ответ получается примерно вдвое больше
		check = abs(ans - ans1);
		ans1 = ans;
//		cout << ans << endl;
		ans = 0;
		h = h / 2;
		c = a+h;
	}
	std :: cout << "Метод трапеций: " << ans1 << endl;
	// Метод Симпсона
	h = 0.5;
	c = a + h;
	check = 3;
	ans1 = 0;
	ans = 0;
	while (check >= e)
	{
		for (i = a + h; i <= (b+a)/2; i += h)
		{
			step1 = pow(c - 4, 1 / 3);
			step2 = pow(sqrt(c), step1);
			cend = pow(sin(c * c), step2);
			chet += cend;
			c += 2*h;
		}
		c = a + 2 * h;
		for (i = a + h; i <= (b + a) / 2; i += h)
		{
			step1 = pow(c - 4, 1 / 3);
			step2 = pow(sqrt(c), step1);
			cend = pow(sin(c * c), step2);
			nechet += cend;
			c += 2 * h;
		}
		ans = h / 6*(aend-bend+4*nechet+2*chet);
		check = abs(ans - ans1);
		ans1 = ans;
//		cout << ans << endl;
		ans = 0;
		h = h / 2;
		c = a + h;
	}
	std :: cout << "Метод Симпсона: " << ans1 << endl;
	// Метод Ньютона
	h = 0.5;
	c = a +h;
	prom = ans1;
	check = 3;
	ans1 = 0;
	ans = 0;
	while (check >= e)
	{
		for (i = a + h; i <= (b + a) / 3; i += h)
		{
			step1 = pow(c - 4, 1 / 3);
			step2 = pow(sqrt(c), step1);
			cend = pow(sin(c * c), step2);
			chet += cend;
			c += 3 * h;
		}
		c = a + 2 * h;
		for (i = a + h; i <= (b + a) / 3; i += h)
		{
			step1 = pow(c - 4, 1 / 3);
			step2 = pow(sqrt(c), step1);
			cend = pow(sin(c * c), step2);
			nechet += cend;
			c += 3 * h;
		}
		c = a + 3 * h;
		for (i = a + h; i <= (b + a) / 3; i += h)
		{
			step1 = pow(c - 4, 1 / 3);
			step2 = pow(sqrt(c), step1);
			cend = pow(sin(c * c), step2);
			nechet1 += cend;
			c += 3 * h;
		}
		ans = h / 8 * (aend - bend + 3 * (chet+nechet) + 2 * nechet1);
		check = abs(ans - ans1);
		ans1 = ans;
		if (ans < prom + e)
			break;
		ans = 0;
		h = h / 2;
		c = a + h;
	}
	std :: cout << "Метод Ньютона: " << ans1 << endl;
}