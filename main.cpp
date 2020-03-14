#include "Matrix.h"

void main()
{
	int m = 4;
	int n = 6;
	double **s;
	s = new double*[m];
	for (int i = 0; i < m; i++)
	{
		s[i] = new double[n];
	}
	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < n; j++)
		{
			s[i][j] = i * n + j + 1;
		}
	}
	s[0][1] = 2;
	s[1][2] = 1;
	s[2][3] = 1;
	s[3][4] = 6;
	Matrix<double> test1(m, n, s);
	Matrix<double> test2, test3, test4, test5, test6;

	test1.show_matrix();
	test2 = test1.transpose();
	test2.show_matrix();

	test3 = test1 * test2;
	test3.show_matrix();
	cout << test3.det(test3) << endl;
	test4 = test3.adjugate();
	test4.show_matrix();
	test5 = test3.inverse();
	test5.show_matrix();
	test6 = test3 * test5;
	test6.show_matrix();
	system("pause");
}