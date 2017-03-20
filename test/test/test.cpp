// test.cpp: определяет точку входа для консольного приложения.
//

#include <cstdlib>
#include <iostream>


using namespace std;

double func(double x)
{
	//1 - 3x + 3x2 - x3;
	//x3 - 3x4 + 3x5 - x6;
	//x4 / 4 - 3x5 / 5 + x6 / 2 - x7 / 7;

	//1 - 4x + 6x2 - 4x3 + x4;
	//x4 - 4x5 + 6x6 - 4x7 + x8;
	//x5 / 5 - 2x6 / 3 + 6x7 / 7 - x8 / 2 + x9 / 9;

	return (126 * pow(x, 5)) - (420 * pow(x, 6)) + (540 * pow(x, 7)) - (315 * pow(x, 8)) + (70 * pow(x, 9));

}

int main()
{
	cout << func(2.0 / 3.0) - func(1.0 / 3.0) << endl;
	system("pause");
    return 0;
}

