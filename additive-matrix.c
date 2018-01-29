/*




*/

#include "additive-matrix.h"

int matrix_read(char *file, int matrix[N_MAX][N_MAX]){
	
	int i=0, j=0;
	char a;

	// Open and read file
	FILE *input_file;
	input_file = fopen(file, "r");
	
	if(input_file == NULL){
		printf("Error in file read");
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
	i++;

	fclose(input_file);

	return i;
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

bool additive(int matrix[N_MAX][N_MAX], int n){

	int i, j, k, l;
	int sum1, sum2, sum3;
	bool four_condition;

	for(i=0; i<n; i++)
		for(j=i+1; j<n; j++)
			for(k=j+1; k<n; k++)
				for(l=k+1; l<n; l++){
					four_condition = false;
					printf("Point (%d,%d,%d,%d)\n", i,j,k,l);
					sum1 = matrix[i][j] + matrix[k][l];
					sum2 = matrix[i][k] + matrix[j][l];
					sum3 = matrix[i][l] + matrix[j][k];
					printf("(%d,%d) (%d,%d) %d + %d Sum 1 = %d\n", i,j,k,l, matrix[i][j], matrix[k][l], sum1);
					printf("(%d,%d) (%d,%d) %d + %d Sum 2 = %d\n", i,k,j,l, matrix[i][k], matrix[j][l], sum2);
					printf("(%d,%d) (%d,%d) %d + %d Sum 3 = %d\n\n", i,l,j,k, matrix[i][l], matrix[j][k], sum3);


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

void main(int argc, char *argv[]) {
	
	int i, j;
	int matrix[N_MAX][N_MAX];

	int n_dimension = matrix_read(argv[1], matrix);
	bool simmetric = matrix_simmetric(matrix, n_dimension);
	printf("Simm = %d\n", simmetric);

	bool add = additive(matrix, n_dimension);
	printf("Add = %d\n", add);

	for(i=0; i<n_dimension; i++){
		for(j=0; j<n_dimension; j++)
			printf("%d\t", matrix[i][j]);
		printf("\n");
	}

}