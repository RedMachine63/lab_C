/*Функция возведения числа в степень*/
double RaiseToPow(double x, int power)
{
	double res;
	int i;
	res = 1.0;
	if (power == 0) {
		return 1;
	}
	else if (power == 1) {
		return x;
	}

	else
		for (i = 1; i <= power; i++)
		{
			res = res * x;
		}
	return(res);
}
/* Функция нахождения факториала числа */
double fact(int k) {
	if (k < 2)
		return 1;
	return k * fact(k - 1);
}

/* Функция нахождения модуля числа */
double fabs(double x) {
	if (x > 0)
		return x;
	else return x * -1;
}

/* Функция нахождения экспоненты разложением в ряд Тейлора */
double exponent(double x) {
	int n;
	double exp;
	exp = 0.0;
	for (n = 0; n <= 20; n++)
	{
		exp = exp + (RaiseToPow(x,  n ) / fact(n));
	}

	return(exp);
}

/*Функция для проверки точности вычисления косинуса*/
int test_exp() {
	int r;
	r = 0;

	r = r || (fabs(exponent(0) - 1.0) >= 0.0001);
	r = r || (fabs(exponent(1) - 2.7182) >= 0.0001);
	r = r || (fabs(exponent(-1) - 0.3679) >= 0.0001);
	r = r || (fabs(exponent(5) - 148.4132) >= 0.0001);
	r = r || (fabs(exponent(-3) - 0.0498) >= 0.0001);
	return r;
}

int main(int argc, char** argv) {
	return test_exp();
}