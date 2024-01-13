#include <math.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

//clear console function
void clrscr(){
	
	system("@cls||clear");
}

//prints a matrix
void print_mat(int rows, int cols, double mat[rows][cols]){
	

	printf("This is your matrix:\n\n");
	
	for(int i=0; i<rows; i++){
		
		for(int j=0; j<cols; j++)
			printf("%lf ", mat[i][j]);	
		
		printf("\n");
	}
}

//reads a matrix
void get_mat(int rows, int cols, double mat[rows][cols]){
	
	printf("Fill the matrix:\n");
		
	for (int i=0; i<rows; i++)
    	for (int j=0; j<cols; j++){
    		
    		printf("mat[%d][%d]=", i+1, j+1);
            scanf("%lf", &mat[i][j]);
        }
	clrscr();
}

//creates a square marix, returns dimension
int sqr_mat(){
	
	int n, m;
	do {
						
		printf("Please insert the dimensions of the matrix.\n");
		printf("rows:");
		scanf("%d",&n);
		printf("columns:");
		scanf("%d",&m);
		if(n!=m)
			printf("The matrix needs to be square!\n");
							
	} while(n!=m);

	return n;
}

//calculates the product of two matrices
void product_matrix(int n, int m, int o, double A[n][m], double B[m][o], double C[n][o]){
					
	for(int i=0; i<n; i++)
		for(int j=0; j<o; j++)
				for(int k=0; k<m; k++)
					C[i][j] += A[i][k]*B[k][j];
}

//prints a vector
void print_vec(double* v, int n){
	
	printf("This is your vector: v={");
	
	for(int i=0; i<n-1; i++)
		printf("%lf, ",v[i]);
	printf("%lf}",v[n-1]);	
}

//reads a vector
void get_vec(double* v, int n){
	
	for(int i=0; i<n; i++){
						
		printf("Element no. %d:",i+1);
		scanf("%lf",&v[i]);
	}
}

//makes sure two vectors are the same dimention
int dim_vec(){
	
	int n1, n2;
	do {
						
		printf("Please insert the dimension of the first vector.\n");
		scanf("%d",&n1);
		printf("Please insert the dimension of the second vector.\n");
		scanf("%d",&n2);
		if(n1!=n2)
			printf("The two vectors need to have the same dimension!\n");
							
	} while(n1!=n2);
	clrscr();
	
	return n1;
}

//dot product of two vectors
double dot(double* v1, double* v2, int n){
	
	double dp = 0;
	for(int i=0; i<n; i++)
		dp += v1[i]*v2[i];
	
	return dp;
}

//cross product of two vectors
void cross(double v1[3], double v2[3], double result[3]){
		
	result[0] = v1[1]*v2[2]-v1[2]*v2[1];
	result[1] = v1[2]*v2[0]-v1[0]*v2[2];
	result[2] = v1[0]*v2[1]-v1[1]*v2[0];
}

//mixed product of two vectors
double mix(double v1[3], double v2[3], double v3[3]){
	
	double CrossResult[3];
	cross(v2, v3, CrossResult);
	return dot(v1, CrossResult, 3);
}

//calculates transpose of a matrix
void transpose(int n, int m, double A[n][m], double AT[m][n]){
	
	for(int i=0; i<n; i++)
		for(int j=0; j<m; j++)
	        AT[j][i] = A[i][j];
		
}

int ltrian(int n, double A[n][n]){
	
	double ratio=0; 
	int i,j,k; 
	 
	for(i=0; i<n; i++){
			
		if(A[i][i]==0.0)
			return 0;
				
		for(j=i+1; j<=n; j++){
			
			ratio = A[j][i]/A[i][i];
			for(k=0; k<=n; k++)
				A[j][k] -= ratio*A[i][k];	
		}
	}
	return 0;
}

//determinant calculation
double det(int n, double A[n][n]){
	
	double minor[100][100];
	double d=0;
	int i, j, k;
	int mini, minj;

	if(n==1)
    	d = A[0][0];
	if(n==2)
		d = A[0][0]*A[1][1]-A[0][1]*A[1][0];
	else if(n==3)
		d = A[0][0]*A[1][1]*A[2][2] + A[0][1]*A[1][2]*A[2][0] + A[0][2]*A[1][0]*A[2][1] - A[2][0]*A[1][1]*A[0][2] - A[2][1]*A[1][2]*A[0][0] - A[2][2]*A[1][0]*A[0][1];
    else{
        
		for(k=0; k<n; k++){
            
			mini=0;
            for(i=1; i<n; i++){
            	
                minj=0;
                for(j=0; j<n; j++){
                	
                    if (j==k)
                        continue;
                	minor[mini][minj] = A[i][j];
                    minj++;
                }
                mini++;
            }
            d += pow(-1.0, (double)k)*A[0][k]*det(n-1, minor);
        }
    }
    return d;
}

//calculates the inverse of a matrix
void inverse(int n, double A[n][n], double adj[n][n], double inv[n][n]){
	
	double (*minor)[n-1] = malloc((n-1)*(n-1)*sizeof(double));
	int mini, minj;
	int i, j, k, l;
	
	for(l=0; l<n; l++)
		for(k=0; k<n; k++){
			
			mini = 0;
			
			for(i=0; i<n; i++){
				
				minj = 0;
								
				for(j=0; j<n; j++){
				
					if(l==i || k==j)
						continue;
					minor[mini][minj] = A[i][j];
					minj++;
				}
				
				if(l==i || k==j)
					continue;
				mini++;			
			}
			mini = 0;
			minj = 0;
			
			if((l-k)%2==0 || l-k==0){
				
				adj[l][k] = det(n-1, minor);
				inv[l][k] = det(n-1, minor)/det(n, A);	
			}
			else{
				
				adj[l][k] = -det(n-1, minor);
				inv[l][k] = -det(n-1, minor)/det(n, A);
			}
		}
	free(minor);	
}

int main() {
	
	while(1){
	
		printf("Choose one of the following options by pressing the corresponding key, ranging from 1 to 3:\n\n");
		printf("1. Vector Operations\n");
		printf("2. Matrix Info\n");
		printf("3. Matrix Operations\n");

		char a;
		scanf(" %c",&a);
		while(a!='1' && a!='2' && a!='3'){ 
		
			printf("\n '%c' is not a valid choice", a);
			a=getchar();
		} //ensures valid input
		clrscr();
		
		if(a=='1'){
						
			printf("You have chosen to do vector operations.\n\n");
			printf("Choose one of the following options by pressing the corresponding key, ranging from 1 to 5:\n");
			printf("1. Add/Substract Vectors\n");
			printf("2. Multiply Vector With Number\n");
			printf("3. Dot Product\n");
			printf("4. Cross Product\n");
			printf("5. Mix Product\n");
			
			char b1;
			scanf(" %c",&b1);
			while(b1!='1' && b1!='2' && b1!='3' && b1!='4' && b1!='5'){ 
		
				printf("\n '%c' is not a valid choice", b1);
				b1=getchar();
			} //ensures valid input
			clrscr();
			
			if(b1=='1'){
				
				printf("You have chosen to add/substract vectors.\n");
				int n1, n2;
				
				int i, n=dim_vec();
				double* v1 = (double*) malloc(n*sizeof(double));
				double* v2 = (double*) malloc(n*sizeof(double));
				
				get_vec(v1, n);
				get_vec(v2, n);
									
				char sel;
				do{
					
					printf("Press 'a' to add or 's' to substract.\n");
					scanf("%c",&sel);
					
					if(sel!='a' && sel!='s')
						printf("Invalid input!");
							
				} while(sel!='a' && sel!='s');
				clrscr();
				
				double* v3 = (double*) malloc(n*sizeof(double));
			
				if(sel=='a')
					for(i=0; i<n; i++)
						v3[i] = v1[i]+v2[i];		
				else if(sel=='s')
					for(i=0; i<n; i++)
						v3[i] = v1[i]-v2[i];		
				
				printf("This is your vector:\n");
				print_vec(v3, n);
			
				free(v1);
				free(v2);
				free(v3);					
			}
			else if(b1=='2'){
				
				printf("You have chosen to multiply vector with number.\n");
				
				int n, i;
				printf("Insert the dimension of the vector:");
				scanf("%d",&n);
				
				double* v1 = (double*) malloc(n*sizeof(double));
				double* v2 = (double*) malloc(n*sizeof(double));
				double l;
				printf("Input a real number with which you want to multiply the vector:");
				scanf("%lf",&l);
									
				get_vec(v1, n);
				for(i=0; i<n; i++)
					v2[i] = v1[i]*l;
				
				printf("This is your vector:\n");					
				print_vec(v2, n);
				
				free(v1);
				free(v2);						
			}
			else if(b1=='3'){
				
				printf("You have chosen dot product.\n");
									
				int n=dim_vec();
				double* v1 = malloc(n*sizeof(double));
				double* v2 = malloc(n*sizeof(double));
				
				get_vec(v1, n);
				get_vec(v2, n);				
				
				printf("This is the dot product: %lf\n\n", dot(v1, v2, n));
				free(v1);
				free(v2);				
			}
			else if(b1=='4'){
				
				printf("You have chosen cross product.\nNote: cross product is defined only for 3-D vectors.\n");
				
				double v1[3], v2[3], v3[3];					
				get_vec(v1, 3);
				get_vec(v2, 3);
				clrscr();
				
				cross(v1, v2, v3);
				printf("This is your vector:\n");
				print_vec(v3, 3);	
			}
			else if(b1=='5'){
				
				printf("You have chosen mixed product.\nNote: mixed product is defined only for 3-D vectors.\n");
				
				double v1[3], v2[3], v3[3];					
				get_vec(v1, 3);
				get_vec(v2, 3);
				get_vec(v3, 3);
				
				printf("Mixed product is %lf", mix(v1, v2, v3));					
			}
		}
		else if(a=='2'){
		
			printf("You have chosen matrix info.\nInput a matrix to receive general information about it.\n\n");
			
			int n, m;
			printf("How many rows would you like?\n");
			scanf("%d", &n);
			printf("How many columns would you like?\n");
			scanf("%d", &m);
			double (*mat)[n] = malloc(n*m*sizeof(double));
			get_mat(n, m, mat);		
			
			if(n==m){
				
				printf("Matrix determinant: det(mat)=%lf\n", det(n, mat));
										
				if(det(n, mat)!=0){
					
					printf("Matrix is invertible.\n");
				
					double (*adj)[n] = malloc(n*n*sizeof(double));
					double (*inv)[n] = malloc(n*n*sizeof(double));
					
					inverse(n, mat, adj, inv);
					printf("This is the adjacency matrix:\n");
					print_mat(n, n, adj);
					printf("This is the inverse matrix:\n");
					print_mat(n, n, inv);
					
					free(adj);
					free(inv);
					free(mat);			
				}
				
				double trace = 0;
				for(int i=0; i<n; i++)
					for(int j=0; j<n; j++)
						if(i==j)
							trace += mat[i][j];
				printf("Matrix trace: tr(mat)=%lf", trace);
									
				bool id=1, ut=1, lt=1;
				for(int i=0; i<n; i++){				
					for(int j=0; j<n; j++){
					
						if(mat[i][i]!=1)
							id = 0;								
						if(i!=j)
							if(mat[i][j]!=0)
								id = 0;	
						if(i>j)
							if(mat[i][j]!=0)
								ut = 0;							
						if(i<j)
							if(mat[i][j]!=0)
								lt = 0;	
								
						if(!id && !ut && !ut)
							break;	
					}
					if(!id && !ut && !ut)
						break;
				}
				
				printf("Matrix is a square matrix.\n");				
				if(id)
					printf("Matrix is identity matrix.\n");					
				else if(ut && lt)
					printf("Matrix is diagonal.\n");
				else if(ut)
					printf("Matrix is upper triangular.\n");
				else if(lt)
					printf("Matrix is lower triangular.\n");
				
				double (*T)[n] = malloc(n*n*sizeof(double));
				transpose(n, n, mat, T);
				bool sym=1, antisym=1;					
				for(int i=0; i<n; i++)
					for(int j=0; j<n; j++){
					
						if(mat[i][j]!=T[j][i])
							sym = 0;
						if(mat[i][j]!=-T[j][i])
							antisym = 0;
							
						if(sym==0 && antisym==0)
							break;	
					}
				printf("This is the traspose matrix:\n");
				print_mat(n, n, T);
				free(T);				
				if(sym)
					printf("Matrix is symmetric.\n");
				else if(antisym)
					printf("Matrix is antisymmetric.\n");
				
				double (*A)[n] = calloc(n*n, n*n*sizeof(double));	
				product_matrix(n, n, n, mat, mat, A);
				bool involutory = 1;
				
				int i=0;
				int j=0;
				for(i=0; i<n; i++){				
					for(j=0; j<m; j++)							
						if(mat[i][j]!=A[j][i]){
							
							involutory = 0;
							break;
						}
						
					if(mat[i][j]!=A[j][i])
						break;
				}
				free(A);						
				if(involutory)
					printf("Matrix A is involutory.\n");		
			}
						
			free(mat);				
		}
		else if(a=='3'){
				
				printf("You have chosen to do matrix operations.\n\n");
				printf("\nChoose one of the following options by pressing the corresponding key, ranging from 1 to 4:\n");
				printf("1. Determinant Calculation\n");
				printf("2. Add/Substract matrices\n");
				printf("3. Multiply matrix with a number\n");
				printf("4. Multiply Matrices\n");
				
				char b2;
				scanf(" %c",&b2);
				while(b2!='1' && b2!='2' && b2!='3' && b2!='4'){ 
			
					printf("\n '%c' is not a valid choice", b2);
					b2=getchar();
				} //ensures valid input
				clrscr();
			
				if(b2==1){
				
					printf("Determinant Calculation\n");
					
					int n = sqr_mat();					
					double (*mat)[n] = malloc(n*n*sizeof(double));
					get_mat(n, n, mat);	
						
					printf("det(mat)=%lf", det(n, mat));	
				}
				if(b2==2){
				
					printf("Add/Substract Matrices\n");
					int n1, m1, n2, m2;
					do{
						
						printf("Please insert the dimensions of the first matrix.\n");
						printf("rows:");
						scanf("%d",&n1);
						printf("columns:");
						scanf("%d",&m1);
						
						printf("Please insert the dimensions of the second matrix.\n");
						printf("rows:");
						scanf("%d",&n2);
						printf("columns:");
						scanf("%d",&m2);
												
						if(n1!=n2 || m1!=m2)
							printf("The two matrices need to have the same dimensions!\n");
													
					} while(n1!=n2 || m1!=m2);
					
					int n=n1, m=m1;
					double (*A)[m] = malloc(n*m*sizeof(double));
					double (*B)[m] = malloc(n*m*sizeof(double));
					
					get_mat(n, m, A);
					get_mat(n, m, B);
					
					char sel;
					do{
						
						printf("Press 'a' to add or 's' to substract.\n");
						scanf("%c",&sel);
						
						if(sel!='a' && sel!='s')
							printf("Invalid input!");
								
					} while(sel!='a' && sel!='s');
									
					if(sel=='a'){
						
						printf("This is the matrix A+B:\n");
						for(int i=0; i<n; i++){												
							for(int j=0; j<m; j++)
								printf("%lf ",A[i][j]+B[i][j]);
							
							printf("\n");
						}
					}
					else if(sel=='s'){
						
						printf("This is the matrix A-B:\n");
						for(int i=0; i<n; i++){						
							for(int j=0; j<m; j++)
								printf("%lf ",A[i][j]-B[i][j]);
							
							printf("\n");
						}
					}					
				}
				if(b2==3){
				
					printf("Multiply Matrix With Number\nEnter a real number:");
					double l;
					scanf("%lf",&l);
					
					int n, m;
					printf("Please insert the dimensions of the first matrix.\n");
					printf("rows:");
					scanf("%d",&n);
					printf("columns:");
					scanf("%d",&m);
					double (*mat)[m] = malloc(n*m*sizeof(double));
					
					get_mat(n, m, mat);	
					
					for(int i=0; i<n; i++)
						for(int j=0; j<m; j++)
							mat[i][j] *= l;
										
					printf("This is the matrix C=l*A:\n");
					print_mat(n, m, mat);		
					free(mat);					
				}
				if(b2==4){
				
					printf("Multiply Matrices\n");
					int n1, m1, n2, m2;
					do{
						
						printf("Please insert the dimensions of the first matrix.\n");
						printf("rows:");
						scanf("%d",&n1);
						printf("columns:");
						scanf("%d",&m1);
						
						printf("Please insert the dimensions of the second matrix.\n");
						printf("rows:");
						scanf("%d",&n2);
						printf("columns:");
						scanf("%d",&m2);
												
						if(m1!=n2)
							printf("Matrix A needs to have as many columns as matrix B has rows!\n");
													
					} while(m1!=n2);
					
					double (*A)[m1] = malloc(n1*m1*sizeof(double));
					double (*B)[m2] = malloc(n2*m2*sizeof(double));
					double (*C)[m2] = calloc(n1*m2, n1*m2*sizeof(double));
					get_mat(n1, m1, A);
					get_mat(n2, m2, B);
					
					product_matrix(n1, m1, m2, A, B, C);
					printf("This is the matrix C=A*B::\n");
					print_mat(n1, m2, C);
					
					free(A);
					free(B);
					free(C);		
				}
			}
		
		printf("\nPress 'e' to exit.\nPress any other key to continue.\n");
		char term;
		scanf(" %c",&term);
		if(term=='e')
			break;
		clrscr();	
	}
	return 0;	
}
