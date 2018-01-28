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

void main(int argc, char *argv[]) {
	
	int i, j;
	int matrix[N_MAX][N_MAX];

	int n_dimension = matrix_read(argv[1], matrix);
	bool simmetric = matrix_simmetric(matrix, n_dimension);
	printf("%d\n", simmetric);

	for(i=0; i<n_dimension; i++){
		for(j=0; j<n_dimension; j++)
			printf("%d ", matrix[i][j]);
		printf("\n");
	}

}