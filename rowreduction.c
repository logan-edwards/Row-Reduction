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

int make_row_echelon(int m, int n, float x[M][N]);
int reduce_row_echelon(int m, int n, int pivot, float x[M][N]);						// return 1 

void main() {

	/* Objective: get matrix into row-echelon form, then worry about reduced row echelon.
	Possible: put RE form reducer into function which returns pivot,
	then we work up from pivot as we reverse.
	Also: perform test for inconsistency (bottom row gives 0 0 0 ... 0 0 1),
	we could possibly sum up to N-1, if sum=0 then we have 0
	Otherwise we could simply use if statements.
	*/
	int pivot;
	float matrix[M][N] = {
		{0, 1, 2, 4},
		{1, 2, 3, 6},
		{0, 0, 10, 30}
	};
	// Working on row-echelon here
	// Implement check for matrix[0][0] == 0. If this is case, swap, and continue swapping until matrix[0][0] != 0 (or for any initial point)
	pivot = make_row_echelon(M, N, matrix);
	printf("\Final:\n");
	print_matrix(M, N, matrix);
	printf("\npivot=%d", pivot);
}

int reduce_row_echelon(int m, int n, int pivot, float x[M][N]) {

}

int make_row_echelon(int m, int n, float x[M][N]) {
	int pivot;
	pivot = 0;

	int swapcount;

	for (int i = 0; i < m; i++) {
		printf("\nIteration %d:\n", i);
		print_matrix(m, n, x);

		// Check if x[i][pivot] = 0; If it is, swap with the next value and see if that's still the case.

		swapcount = 0;
		while (x[i][pivot] == 0) {
			swapcount++;
			row_swap(i, i + swapcount, N, x);
		}
		row_scale(i, n, 1 / x[i][pivot], x);
		for (int j = i + 1; j < m; j++) {
			row_add(i, j, n, -1 * x[j][pivot], x);	// check this line if there are problems
		}
		pivot++;
	}
	return pivot - 1;
}












/*
* 
* less old version w/ checking
* however, lacks checking for if a pivot is skipped (one column is all zeroes),
* and lacks checking for inconsistent equation (all zeroes LHS and 1 RHS for last row)
* 
int make_row_echelon(int m, int n, float x[M][N]) {
	int pivot;
	pivot = 0;

	int swapcount;

	for (int i = 0; i < m; i++) {
		printf("\nIteration %d:\n", i);
		print_matrix(m, n, x);

		// Check if x[i][pivot] = 0; If it is, swap with the next value and see if that's still the case.

		swapcount = 0;
		while (x[i][pivot] == 0) {
			swapcount++;
			row_swap(i, i + swapcount, N, x);
		}
		row_scale(i, n, 1 / x[i][pivot], x);
		for (int j = i + 1; j < m; j++) {
			row_add(i, j, n, -1 * x[j][pivot], x);	// check this line if there are problems
		}
		pivot++;
	}
	return pivot - 1;
}
* 
* 
* 
* 
* old version w/o checking
* 
int make_row_echelon(int m, int n, float x[M][N]) {
	int pivot;
	pivot = 0;
	for (int i = 0; i < m; i++) {
		printf("\nIteration %d:\n", i);
		print_matrix(m, n, x);
		row_scale(i, n, 1 / x[i][pivot], x);
		for (int j = i + 1; j < m; j++) {
			row_add(i, j, n, -1 * x[j][pivot], x);	// check this line if there are problems
		}
		pivot++;
	}
	return pivot - 1;
}
*/

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
