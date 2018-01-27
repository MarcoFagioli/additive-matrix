/*




*/

#include "additive-matrix.h"

int** matrix_read(char *file, int n_max){
	
	int i, j;
	int *array, **valid_matrix;

	// Allocate space for read value
	array = malloc(pow(n_max, 2) * sizeof(int *));
	if(array == NULL){
		printf("Out of memory\n");
		exit(-1);
	}

	// Open and read file
	FILE *input_file;
	input_file = fopen(file, "r");
	
	if(input_file == NULL){
		printf("Error in file read");
		exit(-1);
	}
	
	int n=0;
	fscanf(input_file, "%d", &n);
	if(n>n_max)
		exit(-1);

	for(i=0; i<pow(n_max, 2); i++)
		fscanf(input_file, "%d", &array[i]);
		
	fflush(input_file);
	fclose(input_file);

	// Allocate space for valid matrix
	valid_matrix = malloc(n * sizeof(int *));
	if(valid_matrix == NULL){
		printf("Out of memory\n");
		exit(-1);
	}
	for(i=0; i<n; i++){
		valid_matrix[i] = malloc(n * sizeof(int));
		if(valid_matrix[i] == NULL){
			printf("Out of memory\n");
			exit(-1);
		}
	}

	// Fill the matrix with only the valid values
	int k=0;
	for(i=0; i<n; i++)
		for(j=0; j<n; j++){
        	valid_matrix[i][j] = array[k];
        	k++;
		}
    
    //Free space used to the array, with extra values
    free(array);

	return valid_matrix;
}

bool simmetric(int **matrix){
	int i, j;

	for(i=0; i<sizeof(matrix); i++)
		for(j=i; j<sizeof(matrix); j++){
			if((i==j)&&(matrix[i][j]!=0))
				return false;
			if((i!=j)&&(matrix[i][j]!=matrix[j][i]))
				return false;
		}

	return true;
}

bool main(int argc, char *argv[]) {
	
	int matrix_dimension = atoi(argv[2]);
	int **valid_matrix = matrix_read(argv[1], matrix_dimension);

	//Check if matrix is simmetric
	bool simm = simmetric(valid_matrix);
	if(simm == false)
		return false;

	//parte di stampa
	int i, j;
	for(i=0; i<sizeof(valid_matrix); i++){
		for(j=0; j<sizeof(valid_matrix); j++)
			printf("%d ", valid_matrix[i][j]);
		printf("\n");
	}

	return true;
}