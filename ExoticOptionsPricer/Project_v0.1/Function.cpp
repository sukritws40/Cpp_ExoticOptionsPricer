#include "Function.h"

//Cholesky
vector<vector<double> > cholesky(vector<vector<double> > A)
{
	unsigned int n = A.size();
	double sum1 = 0.0;
	double sum2 = 0.0;
	double sum3 = 0.0;
	vector<vector<double> > result(n, vector<double>(n));
	result[0][0] = sqrt(A[0][0]);
	for (unsigned int j = 1; j <= n - 1; j++)
	{
		result[j][0] = A[j][0] / result[0][0];
	}

	for (unsigned int i = 1; i <= (n - 2); i++)
	{
		for (unsigned int k = 0; k <= (i - 1); k++)
		{
			sum1 += pow(result[i][k], 2);
			result[i][i] = sqrt(A[i][i] - sum1);
		}
		for (unsigned int j = (i + 1); j <= (n - 1); j++)
		{
			for (unsigned int k = 0; k <= (i - 1); k++)
			{
				sum2 += result[j][k] * result[i][k];
				result[j][i] = (A[j][i] - sum2) / result[i][i];
			}
		}
	}
	for (unsigned int k = 0; k <= (n - 2); k++)
	{
		sum3 += pow(result[n - 1][k], 2);
		result[n - 1][n - 1] = sqrt(A[n - 1][n - 1] - sum3);
	}
	return result;
}

//Matrix Multiplication
vector<double> MatrixMultiply(vector<vector<double> > A, vector<double> B)
{
	vector<double> result(B.size());

	for (unsigned int i = 0; i < B.size(); i++)
	{
		for (unsigned int j = 0; j < B.size(); j++)
		{
			result[i] += A[i][j] * B[j];
		}
	}
	return result;
}