/*




*/

#include "additive-matrix.h"

int input_read(char *in_file, int matrix[N_MAX][N_MAX]){
	
	int i=0, j=0;
	char a;

	FILE *input_file;
	input_file = fopen(in_file, "r");
	
	if(input_file == NULL){
		printf("Error in input file open");
		exit(-1);
	}
	
	while(! feof(input_file)){
		fscanf(input_file, "%d", &matrix[i][j]);
		j++;
		fscanf(input_file, "%c", &a);
		if(a == '\n'){
			i++;
			j=0;
		}	
	}

	fclose(input_file);
	return ++i;
}

bool matrix_positive(int matrix[N_MAX][N_MAX], int matrix_dimension){
	
	int i, j;

	for(i=0; i<matrix_dimension; i++)
		for(j=i; j<matrix_dimension; j++)
			if(matrix[i][j]<0)
				return false;

	return true;
}

bool matrix_simmetric(int matrix[N_MAX][N_MAX], int matrix_dimension){
	
	int i, j;

	for(i=0; i<matrix_dimension; i++)
		for(j=i; j<matrix_dimension; j++){
			if((i==j)&&(matrix[i][j]!=0))
				return false;
			if((i!=j)&&(matrix[i][j]!=matrix[j][i]))
				return false;
		}

	return true;
}

bool matrix_additive(int matrix[N_MAX][N_MAX], int matrix_dimension){

	int i, j, k, l;
	int sum1, sum2, sum3;
	bool four_condition;

	for(i=0; i<matrix_dimension; i++)
		for(j=i+1; j<matrix_dimension; j++)
			for(k=j+1; k<matrix_dimension; k++)
				for(l=k+1; l<matrix_dimension; l++){
					four_condition = false;
					#ifdef DEBUG
						printf("Point (%d,%d,%d,%d)\n", i,j,k,l);
					#endif
					sum1 = matrix[i][j] + matrix[k][l];
					sum2 = matrix[i][k] + matrix[j][l];
					sum3 = matrix[i][l] + matrix[j][k];
					#ifdef DEBUG
						printf("(%d,%d) (%d,%d) %d + %d Sum 1 = %d\n", i,j,k,l, matrix[i][j], matrix[k][l], sum1);
						printf("(%d,%d) (%d,%d) %d + %d Sum 2 = %d\n", i,k,j,l, matrix[i][k], matrix[j][l], sum2);
						printf("(%d,%d) (%d,%d) %d + %d Sum 3 = %d\n\n", i,l,j,k, matrix[i][l], matrix[j][k], sum3);
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

void output_print(int matrix[N_MAX][N_MAX], int matrix_dimension){

	int i, j;
	FILE *output_file;
	output_file = fopen("result.txt", "w");
	
	if(output_file == NULL){
		printf("Error in output file open");
		exit(-1);
	}

	for(i=0; i<matrix_dimension; i++){
		for(j=0; j<matrix_dimension; j++)
			fprintf(output_file, "%d\t", matrix[i][j]);
		fprintf(output_file, "\n");
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
}

void main(int argc, char *argv[]) {
	
	int i, j;
	int matrix[N_MAX][N_MAX];

	int matrix_dimension = input_read(argv[1], matrix);

	bool positive = matrix_positive(matrix, matrix_dimension);
	#ifdef DEBUG
		printf("Positive = %d\n", positive);
	#endif
	if(positive!=true){
		output_error("Some element of the matrix is not positive.\nInput matrix is not valid.");
		exit(-1);
	}

	bool simmetric = matrix_simmetric(matrix, matrix_dimension);
	#ifdef DEBUG
		printf("Simmetric = %d\n", simmetric);
	#endif
	if(simmetric!=true){
		output_error("The matrix is not simmetric.\nThe matrix is not additive.");
		exit(-1);
	}

	bool additive = matrix_additive(matrix, matrix_dimension);
	#ifdef DEBUG
		printf("Additive = %d\n", additive);
	#endif
	if(additive!=true){
		output_error("The matrix is not additive.");
		exit(-1);
	}

	output_print(matrix, matrix_dimension);
}