/*	rowreduction.c
	Simple implementation of a row reduction algorithm
	Intended to aid in solving linear equations.
*/

#include <stdio.h>

// M x N matrix, with rightmost column RHS of eqn

#define M 3
#define N 4

// API

void row_add(int m_source, int m_destination, int n, float scalar, float x[M][N]);	// adds a multiple of a row to another row
void row_scale(int m, int n, float scalar, float x[M][N]);							// multiplies a row by a scalar quantity
void row_swap(int m1, int m2, int n, float x[M][N]);								// swaps two rows completely
void print_matrix(int m, int n, float x[M][N]);										// prints the matrix to the terminal
void print_solution(int m, int n, float x[M][N]);									// prints the solution in terms of x0, x1, ... x{n-1}
void print_tex_solution(int m, int n, float x[M][N]);								// format solution output as TeX/Markdown

void main() {
	int pivot;
	float matrix[M][N] = {
		{1, 2, 3, 6},
		{0, 1, 2, 4},
		{0, 0, 10, 30}
	};
}



















void print_matrix(int m, int n, float x[M][N]) {
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n - 1; j++) {
			printf(" %.2f ", x[i][j]);
		}
		printf(" |  %.2f\n", x[i][n-1]);
	}
}

void row_add(int m_source, int m_destination, int n, float scalar, float x[M][N]) {
	for (int i = 0; i < n; i++) {
		x[m_destination][i] += scalar * x[m_source][i];
	}
}

void row_scale(int m, int n, float scalar, float x[M][N]) {
	for (int i = 0; i < n; i++) {
		x[m][i] *= scalar;
	}
}

void row_swap(int m1, int m2, int n, float x[M][N]) {
	float swap;
	for (int i = 0; i < n; i++) {
		swap = x[m1][i];
		x[m1][i] = x[m2][i];
		x[m2][i] = swap;
	}
}