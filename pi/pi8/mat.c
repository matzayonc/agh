#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>

#define TAB_SIZE  1000
#define BUF_SIZE  1000

double get(int cols, int row, int col, const double *A);

void set(int cols, int row, int col, double *A, double value);

void prod_mat(int rowsA, int colsA, int colsB, double *A, double *B, double *AB);

void read_mat(int rows, int cols, double *t) {
	for(int i = 0; i < rows; i++)
		for(int j = 0; j < cols; j++)
			scanf("%ld", &t[i*cols + j]);
}

void print_mat(int rows, int cols, double *t) {
	printf("%ld - %ld - %ld - %ld", t[0], t[1], t[2], t[3]);
	for(int i = 0; i < rows; i++)
		for(int j = 0; j < cols; j++)
			printf("%ld, ", t[i*cols + j]);
}

int read_char_lines(char *tab[]) {
	char line[BUF_SIZE];
	int d = 0;
	char c = '\n';

	while(c == '\n') {
		int n = 0;

		while((c = fgetc(stdin)) != '\n' && c != EOF)
			line[n++] = c;

		tab[d] = malloc(n * sizeof(++n));
		tab[d][n] = '\0';
		for(int i = 0; i < n; i++)
			tab[d][i] = line[i];

		d++;
	}

	return d;
	
}

void write_char_line(char *tab[], int n) {
	printf("%s", tab[n]);
}

void delete_lines(char *tab[], int line_count) {
	for(int i = 0; i < line_count; i++) 
		free(tab[i]);
}

int read_dbl_lines_v1(double *ptr_tab[]);

void write_dbl_line_v1(double *ptr_tab[], int n);

int main(void) {
	int to_do;

	scanf ("%d", &to_do);

	double A[TAB_SIZE], B[TAB_SIZE], C[TAB_SIZE];
	int n, lines_counter, rowsA,colsA,rowsB,colsB;
	char *char_lines_table[TAB_SIZE];
	double series_table[TAB_SIZE];
	double *ptr_table[TAB_SIZE];

	switch (to_do) {
		case 1:
			scanf("%d %d",&rowsA,&colsA);
			read_mat(rowsA, colsA, A);
			/**/print_mat(rowsA, colsA, A);
			// scanf("%d %d",&rowsB,&colsB);
			// read_mat(rowsB, colsB, B);
			// prod_mat(rowsA,colsA,colsB,A,B,C);
			// print_mat(rowsA,colsB,C);
			break;
		// case 2:
		// 	scanf("%d",&n);
		// 	ptr_table[0] = series_table;
		// 	lines_counter = read_dbl_lines_v1(ptr_table);
		// 	write_dbl_line_v1(ptr_table,n);
		// 	break;
		case 3:
			scanf("%d", &n);
			lines_counter = read_char_lines(char_lines_table);
			write_char_line(char_lines_table,n);
			delete_lines(char_lines_table,lines_counter);
			break;
		default:
			printf("NOTHING TO DO FOR %d\n", to_do);
	}
	return 0;
}
