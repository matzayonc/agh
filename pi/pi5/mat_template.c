#include <math.h>
#include <stdio.h>
#include <stdbool.h>

#define SIZE 40

void read_vector(double x[], int n)
{
	for (int i = 0; i < n; ++i)
	{
		scanf("%lf", x++);
	}
}

void print_vector(double x[], int n)
{
	for (int i = 0; i < n; ++i)
	{
		printf("%.4f ", x[i]);
	}
	printf("\n");
}

void read_mat(double A[][SIZE], int m, int n)
{
	for (int i = 0; i < m; ++i)
	{
		for (int j = 0; j < n; ++j)
		{
			scanf("%lf", &A[i][j]);
		}
	}
}

void print_mat(double A[][SIZE], int m, int n)
{
	for (int i = 0; i < m; ++i)
	{
		for (int j = 0; j < n; ++j)
		{
			printf("%.4f ", A[i][j]);
		}
		printf("\n");
	}
}

void print_mat_ind(double A[][SIZE], int m, int n, const int indices[]);

// 5.1
// Calculate matrix product, AB = A X B
// A[m][p], B[p][n]
void mat_product(double A[][SIZE], double B[][SIZE], double AB[][SIZE], int m,
				 int p, int n)
{
	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < n; j++)
		{
			AB[i][j] = 0;
			double sum = 0;
			for (int u = 0; u < p; u++)
			{
				;
				sum += A[i][u] * B[u][p];
				AB[i][j] = AB[i][j] + A[i][u] * B[u][j];
			}
		}
	}
}

// Calculate matrix - vector product
void mat_vec_product(double A[][SIZE], const double b[], double Ab[], int m, int n);

void backward_substit(double A[][SIZE], double x[], int n);

void backward_substitution_index(double A[][SIZE], const int indices[], double x[], int n);

// 5.2
// Matrix triangulation and determinant calculation - simplified version
// (no rows' swaps). If A[i][i] == 0, function returns NAN.
// Function may change A matrix elements.
double gauss_simplified(double A[][SIZE], int n)
{
	int i, j, k;

	for (i = 0; i < n - 1; i++)
	{
		for (k = i + 1; k < n; k++)
		{
			double m = A[k][i] / A[i][i];
			for (j = 0; j < n; j++)
			{
				A[k][j] = A[k][j] - m * A[i][j];
			}
		}
	}

	double count = A[0][0];

	if (count == 0.0)
		return NAN;

	for (int i = 1; i < n; i++)
	{
		if (A[i][i] == 0.0)
			return NAN;
		count *= A[i][i];
	}

	return count;
}

// 5.3
// Matrix triangulation, determinant calculation, and Ax = b solving - extended
// version (Swap the rows so that the row with the largest, leftmost nonzero
// entry is on top. While swapping the rows use index vector - do not copy
// entire rows.) If max A[i][i] < eps, function returns 0. If det != 0 && b !=
// NULL && x != NULL then vector x should contain solution of Ax = b.

int swap_indices(double A[][SIZE], int swap[], const int n)
{
	for (int i = 0; i < n; i++)
		if (A[swap[i]][swap[i]] == 0)
			for (int j = i + 1; j < n; j++) {
				int rj = swap[j];
				if (A[rj][i] != 0)
				{
					swap[j] = swap[i];
					swap[i] = rj;
					return 1;
				}
			}
	return 0;
}

double gauss(double A[][SIZE], const double b[], double x[], const int n,
			 const double eps)
{
	double values[SIZE];
	int indices[SIZE];
	int crosses = 0;

	for (int i = 0; i < n; i++) {
		values[i] = b[i];
		indices[i] = i;
	}

	for (int i = 0; i < n - 1; i++)
		for (int j = i + 1; j < n; j++)
		{
			if (A[indices[i]][i] == 0) {
				double m = 0;
				crosses += swap_indices(A, indices, n);
				for (int i = 0; i < n; i++)
					if (A[i][i] > m)
						m = A[i][i];
				if (m < eps)
					return 0;
			}

			double m = -A[indices[j]][i] / A[indices[i]][i];

			for (int c = i; c < n; c++)
				A[indices[j]][c] += m * A[indices[i]][c];

			values[indices[j]] += m * values[indices[i]];
		}

	crosses += swap_indices(A, indices, n);

	double m = 0;
	for (int i = 0; i < n; i++)
		if (A[indices[i]][i] > m)
			m = A[indices[i]][i];
	if (m < eps) return 0;

	double det = A[0][0];
	for (int i = 1; i < n; i++)
		det *= A[indices[i]][i];

	det *= crosses % 2 ? -1 : 1;

	if (det == 0) return det;

	double s;
	for (int i = n - 1; i >= 0; i--) {
		s = values[indices[i]];
		for (int j = n - 1; j > i; j--)
			s = s - A[indices[i]][j] * x[j];
		x[i] = s / A[indices[i]][i];
	}

	return det;
}

// 5.4
// Returns the determinant; B contains the inverse of A (if det(A) != 0)
// If max A[i][i] < eps, function returns 0.
double matrix_inv(double A[][SIZE], double B[][SIZE], int n, double eps)
{
	int indices[SIZE];

	for (int i = 0; i < n; i++)
		indices[i] = i;

	int crosses = 0; // every cross of rows is a change of sign

	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			B[i][j] = i == j ? 1 : 0;

	for (int i = 0; i < n - 1; i++)
		for (int r = i + 1; r < n; r++)
		{
			if (A[indices[i]][i] == 0)
			{
				crosses += swap_indices(A, indices, n);

				double m = A[0][0];
				for (int i = 0; i < n; i++)
					if (A[i][i] > m)
						m = A[i][i];
				if (m < eps)
					return 0;
			}

			double m = -A[indices[r]][i] / A[indices[i]][i];

			for (int c = i; c < n; c++)
				A[indices[r]][c] += m * A[indices[i]][c];

			for (int c = 0; c < n; c++)
				B[indices[r]][c] += m * B[indices[i]][c];
		}

	double det = crosses % 2 ? -1 : 1;
	for (int i = 0; i < n; i++)
		det *= A[indices[i]][i];

	if (det == 0) return 0;

	for (int i = n - 1; i >= 0; i--) {
		double m = 1 / A[indices[i]][i];
		A[indices[i]][i] = 1;

		for (int c = 0; c < n; c++)
			B[indices[i]][c] *= m;

		for (int r = i - 1; r >= 0; r--) {
			m = -A[indices[r]][i];
			for (int c = 0; c < n; c++)
			{
				A[indices[r]][c] += A[indices[i]][c] * m;
				B[indices[r]][c] += B[indices[i]][c] * m;
			}
		}
	}

	return det;
}

int main(void) {
	double A[SIZE][SIZE], B[SIZE][SIZE], C[SIZE][SIZE];
	double b[SIZE], x[SIZE], det, eps = 1.e-13;

	int to_do;
	int m, n, p;

	scanf ("%d", &to_do);

	switch (to_do) {
		case 1:
			scanf("%d %d %d", &m, &p, &n);
			read_mat(A, m, p);
			read_mat(B, p, n);
			mat_product(A, B, C, m, p, n);
			print_mat(C, m, n);
			break;
		case 2:
			scanf("%d", &n);
			read_mat(A, n, n);
			printf("%.4f\n", gauss_simplified(A, n));
			break;
		case 3:
			scanf("%d", &n);
			read_mat(A,n, n);
			read_vector(b, n);
			det = gauss(A, b, x, n, eps);
			printf("%.4f\n", det);
			if(det) print_vector(x, n);
			break;
		case 4:
			scanf("%d", &n);
			read_mat(A,n,n);
			printf("%.4f\n",matrix_inv(A, B, n, eps));
			print_mat(B, n, n);
			break;
		default:
			printf("NOTHING TO DO FOR %d\n", to_do);
			break;
	}
	return 0;
}
