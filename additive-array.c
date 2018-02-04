/*
	Marco Fagioli, mat. 808176

	Additive Matrix Project:
		given a matrix in input verify if it is additive.

		File.c with alghoritms using array approach to simulate matrix.
		Static use of data structure, with max dimension of array.

*/

#include "additive-matrix.h"

int matrix_conversion(int matrix[ARRAY_MAX], int i, int j, int n){

	return matrix[i*n+j];
}

int sum_first_i(int i){

	int c;
	int sum=0;
	for(c=1; c<=i;c++)
		sum+=c;

	return sum;
}

void matrix_triangolar_fix(int array[ARRAY_MAX], int matrix_dimension, int index_element){

	int i, j;

	for(i=matrix_dimension-1; i>0; i--)
		for(j=matrix_dimension-1; j>=i; j--){
			array[i*matrix_dimension+j] = array[index_element];
			index_element--;
		}

	for(i=0; i<matrix_dimension; i++)
		for(j=i; j<matrix_dimension; j++)
			array[j*matrix_dimension+i] = matrix_conversion(array, i, j, matrix_dimension);
}

int input_read(char *in_file, int array[ARRAY_MAX]){
	
	int i=0, n=0;

	char a;

	FILE *input_file;
	input_file = fopen(in_file, "r");
	
	if(input_file == NULL){
		printf("Error in input file open");
		exit(-1);
	}
	
	while(! feof(input_file)){
		fscanf(input_file, "%d", &array[i]);
		i++;
		if(! feof(input_file)){
			fscanf(input_file, "%c", &a);
			if(a == '\n')
				n++;
		}
	}
	n++;

	fclose(input_file);

	if(i==sum_first_i(n))
		matrix_triangolar_fix(array, n, i-1);

	return n;
}

bool matrix_positive(int array[ARRAY_MAX], int matrix_dimension){
	
	int i, j;

	for(i=0; i<matrix_dimension; i++)
		for(j=i; j<matrix_dimension; j++)
			if(matrix_conversion(array, i, j, matrix_dimension)<0)
				return false;

	return true;
}

bool matrix_simmetric(int array[ARRAY_MAX], int matrix_dimension){
	
	int i, j;

	for(i=0; i<matrix_dimension; i++)
		for(j=i; j<matrix_dimension; j++){
			if((i==j)&&(matrix_conversion(array, i, j, matrix_dimension)!=0))
				return false;
			if((i!=j)&&(matrix_conversion(array, i, j, matrix_dimension)!=matrix_conversion(array, j, i, matrix_dimension)))
				return false;
		}

	return true;
}

bool matrix_additive(int array[ARRAY_MAX], int matrix_dimension){

	int i, j, k, l;

	int sum1, sum2, sum3;
	bool four_condition;

	for(i=0; i<matrix_dimension; i++)
		for(j=i+1; j<matrix_dimension; j++)
			for(k=j+1; k<matrix_dimension; k++)
				for(l=k+1; l<matrix_dimension; l++){
					four_condition = false;
					#ifdef DEBUG
						printf("Point (%d,%d,%d,%d)\n", i, j, k, l);
					#endif
					sum1 = matrix_conversion(array, i, j, matrix_dimension) + matrix_conversion(array, k, l, matrix_dimension);
					sum2 = matrix_conversion(array, i, k, matrix_dimension) + matrix_conversion(array, j, l, matrix_dimension);
					sum3 = matrix_conversion(array, i, l, matrix_dimension) + matrix_conversion(array, j, k, matrix_dimension);
					#ifdef DEBUG
						printf("(%d,%d) (%d,%d) %d + %d Sum 1 = %d\n", i, j, k, l, matrix_conversion(array, i, j, matrix_dimension), matrix_conversion(array, k, l, matrix_dimension), sum1);
						printf("(%d,%d) (%d,%d) %d + %d Sum 2 = %d\n", i, k, j, l, matrix_conversion(array, i, k, matrix_dimension), matrix_conversion(array, j, l, matrix_dimension), sum2);
						printf("(%d,%d) (%d,%d) %d + %d Sum 3 = %d\n\n", i, l, j, k, matrix_conversion(array, i, l, matrix_dimension), matrix_conversion(array, j, k, matrix_dimension), sum3);
					#endif

					if(sum1 < sum2)
						if(sum2 == sum3)
							four_condition = true;

					if(sum1 == sum2)
						if(sum2 > sum3)
							four_condition = true;

					if(sum1 > sum2)
						if(sum1 == sum3)
							four_condition = true;

					if(four_condition == false)
						return false;
				}

	return true;
}

void output_print(int array[ARRAY_MAX], int matrix_dimension){

	int i, j;

	FILE *output_file;
	output_file = fopen("result.txt", "w");
	
	if(output_file == NULL){
		printf("Error in output file open");
		exit(-1);
	}

	fprintf(output_file, "Matrix is additive.\n");

	for(i=0; i<matrix_dimension; i++)
		for(j=0; j<matrix_dimension; j++){
			if(j==matrix_dimension-1)
				fprintf(output_file, "%d\n", matrix_conversion(array, i, j, matrix_dimension));
			else
				fprintf(output_file, "%d\t", matrix_conversion(array, i, j, matrix_dimension));
		}

	fclose(output_file);
}

void output_error(char *error){

	FILE *output_file;
	output_file = fopen("result.txt", "w");
	
	if(output_file == NULL){
		printf("Error in output file open");
		exit(-1);
	}
	
	fprintf(output_file, "%s", error);

	fclose(output_file);
	exit(-1);
}

void main(int argc, char *argv[]) {
	
	int i, j;
	int array[ARRAY_MAX];

	int matrix_dimension = input_read(argv[1], array);
	if(matrix_dimension>MATRIX_MAX)
		output_error("Matrix is too big, there is no space to save it.\nInput matrix is not valid.");


	bool positive = matrix_positive(array, matrix_dimension);
	#ifdef DEBUG
		printf("Positive = %d\n", positive);
	#endif
	if(positive!=true)
		output_error("Some element of the matrix is not positive.\nInput matrix is not valid.");


	bool simmetric = matrix_simmetric(array, matrix_dimension);
	#ifdef DEBUG
		printf("Simmetric = %d\n", simmetric);
	#endif
	if(simmetric!=true)
		output_error("The matrix is not simmetric.\nThe matrix is not additive.");


	bool additive = matrix_additive(array, matrix_dimension);
	#ifdef DEBUG
		printf("Additive = %d\n", additive);
	#endif
	if(additive!=true)
		output_error("The matrix is not additive.");

	output_print(array, matrix_dimension);
}