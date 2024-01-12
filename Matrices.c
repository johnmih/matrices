#include <math.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

//clear console function
void clrscr(){
	
	system("@cls||clear");
}

void create_matrix() {

	//Initialisation
	char selection, invalid, //used for saving user input and continuing from an invalid state respectively
	matname[51], filename[56]; //will be storing the designated name and that plus .txt/0 respectively
	int n, m; //variables for the dimentions of the matrix
	bool loop = 1;  // a boolian used for returning the previous state after an invalid selection
	FILE *matrix_file; //setting the name of the file for the purposes of this program

	//Obtaining the desired name for the Matrix
	printf ("Please name your matrix (use one word):\n");
	scanf("%s", matname);

	//Creating a file for the matrix
	sprintf(filename, "%s.txt", matname);
	matrix_file = fopen(filename, "w"); // "w" defines "writing mode"

	//Asking for the desired size of the matrix and making one accordingly
	do{
		
		clrscr();
		printf ("Matrix: %s\n\nGive the desired number of rows (preferably less than 10 for formatting purposes):", matname);
		scanf("%d", &n);
		printf ("Give the desired number of columns (preferably less than 8 for formatting purposes):");
		scanf("%d", &m);
		clrscr();
		
		printf ("You opted for %d rows and %d columns\n\n", n, m);
		double (*A)[m] = malloc(n*m*sizeof(double));
		
	

		//Asking for the desired way of loading data
		printf("Would you like to fill the matrix with pseudorandom numbers or by yourself? (select from below)\n");
		printf("1.With pseudorandom numbers\n");
		printf("2.By myself\n");
		printf("Or type 'b' to go back to the rows and colums selection screan\n");
		
		scanf(" %c",&selection);
		switch(selection){
			
			case '1':
				
				clrscr();
				fprintf(matrix_file,"Dimensions\nrows:%d\ncolumns:%d\n" , n, m);
				printf("You opted to fill the matrix with pseudorandom numbers\n\n");
				//writing (automatic)
				for(int i=0; i<n; i++){
					
					for(int j=0 ; j<m; j++){
						
						printf( "%s[%d][%d]=", matname, i+1, j+1);
						A[i][j] = rand();
						printf("%.3lf\t", A[i][j]);
						fprintf(matrix_file,"%.3lf\t" , A[i][j]);
					}
					putchar ('\n');
					fprintf(matrix_file, "\n");
				}
				fclose(matrix_file);
				printf ("You successfully created a matrix\n");
				loop = 0; //stopping the loop
				break;
				
			case '2':
			
				fprintf(matrix_file,"Dimensions\nrows:%d\ncolumns:%d\n" , n, m);	
				clrscr();
				printf("You opted to fill the matrix manually\n\n");
				//writing (manual)
				for(int i=0; i<n; i++){
					
					for(int j=0; j<m; j++){

                        printf("%s[%d][%d]=", matname, i+1, j+1);
                        scanf( "%lf", &A[i][j]);
                        fprintf(matrix_file,"%.3lf\t", A[i][j]);
                    }
					putchar ('\n');
					fprintf(matrix_file, "\n");
				}
				fclose(matrix_file);
				printf ("You successfully created a matrix\n");
				loop = 0; //stopping the loop
				break;
			case 'b':
				break;//going back up
			default:
				fflush(stdin);
				printf ("Your selection was invalid.\n");
				printf ("Press anything to try again.\n");
				scanf("%c", &invalid);
				break;
		}
		free(A);
		
	}while(loop); //the loop will stop if the matrix has been created successfully
}

void print_mat(int rows, int cols, double mat[rows][cols], FILE * output){
	
	if(output==stdout)
		printf("This is your matrix:\n\n");
	
	for(int i=0; i<rows; i++){
		
		for(int j=0; j<cols; j++)
			fprintf(output, "%lf ", mat[i][j]);	
		
		fprintf(output, "\n");
	}
}

void get_mat(int rows, int cols, double mat[rows][cols], FILE * input, char name){
	
	if(input==stdin)
		printf("Fill in matrix %c:\n", name);
		
	for (int i=0; i<rows; i++)
    	for (int j=0; j<cols; j++){
    		
    		if(input==stdin)
    			printf("%c[%d][%d]=", name, i+1, j+1);
            fscanf(input, "%lf", &mat[i][j]);
        }
    /*Παρά το γεγονός ότι στον προγραμματισμό η αρίθμιση των δισδιάστατων πινάκων ξεκινάει 
	απο το 0, επιθυμώ ο χρήστης του λογισμικού να αλληλεπιδρά με τη μαθηματική προσέγγιση
	της αρίθμισης που θέλει την αρίθμιση να ξεκινάει απο το 1.*/
}

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

void product_matrix(int n, int m, int o, double A[n][m], double B[m][o], double C[n][o]){
					
	for(int i=0; i<n; i++)
		for(int j=0; j<o; j++)
				for(int k=0; k<m; k++)
					C[i][j] += A[i][k]*B[k][j];
}

void print_vec(double* v, int n){
	
	printf("This is your vector: v={");
	
	for(int i=0; i<n-1; i++)
		printf("%lf, ",v[i]);
	printf("%lf}",v[n-1]);	
}

void get_vec(double* v, int n){
	
	for(int i=0; i<n; i++){
						
		printf("Element no. %d:",i+1);
		scanf("%lf",&v[i]);
	}
}

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


double dot(double* v1, double* v2, int n){
	
	double dp = 0;
	for(int i=0; i<n; i++)
		dp += v1[i]*v2[i];
	
	return dp;
}

void cross(double v1[3], double v2[3], double result[3]){
		
	result[0] = v1[1]*v2[2]-v1[2]*v2[1];
	result[1] = v1[2]*v2[0]-v1[0]*v2[2];
	result[2] = v1[0]*v2[1]-v1[1]*v2[0];
}

double mix(double v1[3], double v2[3], double v3[3]){
	
	double CrossResult[3];
	cross(v2, v3, CrossResult);
	return dot(v1, CrossResult, 3);
}

void transpose(int n, int m, double A[n][m], double AT[m][n]){
	
	for(int i=0; i<n; i++)
		for(int j=0; j<m; j++)
	        AT[j][i] = A[i][j];
		
}

int ltrian(int n, double A[n][n]){
	
	double ratio=0; //Ο αριθμός με τον οποίο πολλαπλασιάζουμε την εκάστοτε γραμμή πριν κάνουμε την γραμμοπράξη.
	int i,j,k; //Μετρητές.

	// Χρησιμοποώντας την απαλοιφή Gauss μετατρέπω τον πίνακα σε κάτω τριγωνικό.
	 
	for(i=0; i<n; i++){
		
		//Αν κάποιο στοιχείο της κύριας διαγωνίου είναι μηδενικό ο πίνακας δεν έχει τριγωνικό ισοδύναμο πίνακα.		
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

double det(int n, double A[n][n]){
	
	double minor[100][100];
	double d=0; //determinant
	int i, j, k; //Μετρητές.
	int mini, minj; //Δείκτες των υποπινάκων.
    
    //Αν πρόκειται για πίνακα στοιχείο η ορίζουσα ταυτίζεται με το μοναδικό στοιχείο.
	if(n==1)
    	d = A[0][0];
	//Απλός υπολογισμός ορίζουσας πίνακα 2x2.
	if(n==2)
		d = A[0][0]*A[1][1]-A[0][1]*A[1][0];
	//Yπολογισμός ορίζουσας πίνακα 3x3 με τον κανόνα του Sarrus.
	else if(n==3)
		d = A[0][0]*A[1][1]*A[2][2] + A[0][1]*A[1][2]*A[2][0] + A[0][2]*A[1][0]*A[2][1] - A[2][0]*A[1][1]*A[0][2] - A[2][1]*A[1][2]*A[0][0] - A[2][2]*A[1][0]*A[0][1];
	//Γενική περίπτωση ορίζουσας nxn.
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

//time delay function
void delay(float number_of_seconds){
    float milli_seconds = 1000 * number_of_seconds;
  
    // Storing start time
    clock_t start_time = clock();
  
    // looping till required time is not achieved
    while (clock() < start_time + milli_seconds);
}

//title screen fuction
void fake_loading_screen(){

	float x=.5;
	printf(" Welcome to our application!\n Press anhything to start.");
	getch();
	clrscr();
	printf("This will only take a few seconds...");
	printf("\n\n\n\n                         ...............");
	for (int i=0; i<15; i++){
		printf("\b");
		}
	for (int i=0; i<2; i++){
		delay(x);
	putchar('#');
		}
	delay(0.5*x);
	for (int i=0; i<3; i++){
		delay(0.5*x);
	putchar('#');
		}
	delay(0.5*x);
	for (int i=0; i<2; i++){
		delay(x);
	putchar('#');
		}
	delay(x);
	for (int i=0; i<4; i++){
		delay(0.75*x);
	putchar('#');
		}
	for (int i=0; i<3; i++){
		delay(x);
	putchar('#');
		}
	delay (1.5*x);
	putchar('#');	
	delay(0.25*x);
	clrscr();
}

int main() {
	
	
	
	while(1){ //Δημιουργώ εκ προθέσεως έναν ατέρμονα βρόγχο. 
		
		// fake_loading_screen();
		printf("Choose one of the following options by pressing the corresponding key, ranging from 1 to 5:\n\n");
		printf("1. Create Matrix\n");
		printf("2. Load Matrix\n");
		printf("3. View Available Matrices\n");
		printf("4. Delete Matrix\n");
		printf("5. Calculations\n");
		
		char a;
		scanf(" %c",&a);
		while(a!='1' && a!='2' && a!='3' && a!='4' && a!='5'){ 
			
			printf("\n '%c' was not a valid choice", a);
			//Δεκτές μόνο οι τιμές: 1, 2, 3, 4, 5.
			a=getchar();
		}
		clrscr();
		
		if(a=='1'){	
			
			printf("You have chosen to create a new matrix.\n");
			printf("Please insert the dimensions of the new matrix.\n");
			
			int n, m;
			printf("rows:");
			scanf("%d",&n);
			printf("columns:");
			scanf("%d",&m);
		
			double (*mat)[m] = malloc(n*m*sizeof(double));
			
			get_mat(n, m, mat, stdin, 'A');
					
			print_mat(n, m, mat, stdin);
			FILE * output = fopen("pinakas.txt", "w");
			print_mat(n, m, mat, output);	
			
			free(mat);
		}
		else if(a=='2'){
		
			printf("You have chosen to load a matrix.\n");		
		}
		else if(a=='3'){
			
			printf("You have chosen to view the available matrices.\n");	
		}
		else if(a=='4'){
		
			printf("You have chosen to delete a matrix.\n");
		}
		else if(a=='5'){
		
			printf("You have chosen to do Calculations.\nChoose one of the following options by pressing the corresponding key, ranging from 1 to 3:\n");
			printf("1. Vector Operations\n");
			printf("2. Matrix Info\n");
			printf("3. Matrix Operations\n");
			char b;
			scanf(" %c",&b);
			while(b!='1' && b!='2' && b!='3'){ 
			
				printf("\n '%c' was not a valid choice", b);
				//Δεκτές μόνο οι τιμές: 1, 2, 3.
				b=getchar();
			}
			clrscr(); //Δεκτές μόνο οι τιμές: 1, 2, 3.
			
			if(b=='1'){
							
				printf("You have chosen to do vector operations.\n\n");
				printf("Choose one of the following options by pressing the corresponding key, ranging from 1 to 5:\n");
				printf("1. Add/Substract Vectors\n");
				printf("2. Multiply Vector With Number\n");
				printf("3. Dot Product\n");
				printf("4. Cross Product\n");
				printf("5. Mix Product\n");
				
				char c1;
				scanf(" %c",&c1);
				while(c1!='1' && c1!='2' && c1!='3' && c1!='4' && c1!='5'){ 
			
					printf("\n '%c' was not a valid choice", c1);
					//Δεκτές μόνο οι τιμές: 1, 2, 3, 4, 5.
					c1=getchar();
				}
				clrscr();
				
				if(c1=='1'){
					
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
							printf("Invalid imput!");
								
					} while(sel!='a' && sel!='s');
					clrscr();
					
					double* v3 = (double*) malloc(n*sizeof(double));
				
					if(sel=='a')
						for(i=0; i<n; i++)
							v3[i] = v1[i]+v2[i];		
					else if(sel=='s')
						for(i=0; i<n; i++)
							v3[i] = v1[i]-v2[i];		
				
					print_vec(v3, n);
				
					free(v1);
					free(v2);
					free(v3);					
				}
				else if(c1=='2'){
					
					printf("You have chosen to multiply vector with number.\n");
					
					int n, i;
					printf("Insert the dimension of the vector:");
					scanf("%d",&n);
					
					double* v1 = (double*) malloc(n*sizeof(double));
					double* v2 = (double*) malloc(n*sizeof(double));
					double l;
					printf("Imput the real number with which you want to multiply the vector:");
					scanf("%lf",&l);
										
					get_vec(v1, n);
					for(i=0; i<n; i++)
						v2[i] = v1[i]*l;
										
					print_vec(v2, n);
					
					free(v1);
					free(v2);						
				}
				else if(c1=='3'){
					
					printf("You have chosen dot product.\n");
										
					int n=dim_vec();
					double* v1 = malloc(n*sizeof(double));
					double* v2 = malloc(n*sizeof(double));
					
					get_vec(v1, n);
					get_vec(v2, n);				
					
					printf("This is the dot product: %lf\n\n", dot(v1, v2, n));
					free(v1);
					free(v2);
					//Αποφεύγω το memory leak					
				}
				else if(c1=='4'){
					
					printf("You have chosen cross product.\nNote: cross product is defined only for 3-D vectors.\n");
					
					double v1[3], v2[3], v3[3];					
					get_vec(v1, 3);
					get_vec(v2, 3);
					clrscr();
					
					cross(v1, v2, v3);
					print_vec(v3, 3);	
				}
				else if(c1=='5'){
					
					printf("You have chosen mixed product.\nNote: mixed product is defined only for 3-D vectors.\n");
					
					double v1[3], v2[3], v3[3];					
					get_vec(v1, 3);
					get_vec(v2, 3);
					get_vec(v3, 3);
					
					printf("Mixed product is %lf", mix(v1, v2, v3));					
				}
			}
			else if(b=='2'){
			
				printf("You have chosen matrix info.\nInsert a matrix to receive general information about it.\n");
								
				
				
				if(n==m){
					
					printf("Matrix determinant: det(%s)=%lf\n", matname, det(n, A));
											
					if(det(n, A)!=0){
						
						printf("Matrix A is invertible.\n");
					
						double (*adj)[n] = malloc(n*n*sizeof(double));
						double (*inv)[n] = malloc(n*n*sizeof(double));
						
						inverse(n, A, adj, inv);
						printf("This is the adjacency matrix of A:\n");
						print_mat(n, n, adj, stdout);
						printf("This is the inverse matrix of A:\n");
						print_mat(n, n, inv, stdout);
						
						free(adj);
						free(inv);			
					}
					
					double trace = 0;
					for(i=0; i<n; i++)
						for(j=0; j<n; j++)
							if(i==j)
								trace += A[i][j];
					printf("Matrix trace: tr(A)=%lf", trace);
										
					bool id=1, ut=1, lt=1;
					for(i=0; i<n; i++){
						
						for(j=0; j<n; j++){
						
							if(A[i][i]!=1)
								id = 0;								
							if(i!=j)
								if(A[i][j]!=0)
									id = 0;
							
							if(i>j)
								if(A[i][j]!=0)
									ut = 0;							
							if(i<j)
								if(A[i][j]!=0)
									lt = 0;	
									
							if(!id && !ut && !ut)
								break;	
						}
						if(!id && !ut && !ut)
							break;
					}				
					if(id)
						printf("Matrix A is identity matrix.\n");					
					else if(ut && lt)
						printf("Matrix A is diagonal.\n");
					else if(ut)
						printf("Matrix A is upper triangular.\n");
					else if(lt)
						printf("Matrix A is lower triangular.\n");
					else
						printf("Matrix A is a square matrix.\n");
					
					double (*AT)[n] = malloc(n*n*sizeof(double));
					transpose(n, n, A, AT);
					bool sym=1, antisym=1;					
					for(i=0; i<n; i++)
						for(j=0; j<n; j++){
						
							if(A[i][j]!=AT[j][i])
								sym = 0;
							if(A[i][j]!=-AT[j][i])
								antisym = 0;
								
							if(sym==0 && antisym==0)
								break;	
						}
					printf("This is the traspose matrix of A:\n");
					print_mat(n, n, AT, stdout);
					free(AT);				
					if(sym)
						printf("Matrix A is symmetric.\n");
					else if(antisym)
						printf("Matrix A is antisymmetric.\n");
					
					double (*A2)[n] = calloc(n*n, n*n*sizeof(double));	
					product_matrix(n, n, n, A, A, A2);
					bool involutory = 1;
					
					for(i=0; i<n; i++){
						
						for(j=0; j<m; j++)							
							if(A[i][j]!=A2[j][i]){
								
								involutory = 0;
								break;
							}
							
						if(A[i][j]!=A2[j][i])
							break;
					}
					free(A2);						
					if(involutory)
						printf("Matrix A is involutory.\n");		
				}
							
				free(A);				
			}
			else if(b=='3'){
			
				\nChoose one of the following options by pressing the corresponding key, ranging from 1 to 5:\n1. Determinant Calculation\n2. Transpose Matrix\n\n5. Multiply Matrices\n--------------------\n");
				int c2;
				do scanf("%d",&c2); while(c2!=1 && c2!=2 && c2!=3 && c2!=4 && c2!=5); //Δεκτές μόνο οι τιμές: 1, 2, 3, 4, 5.
			
				if(c2==1){
				
					printf("Determinant Calculation\n");
					
					int n = sqr_mat();					
					double (*A)[n] = malloc(n*n*sizeof(double));
					get_mat(n, n, A, stdin, 'A');	
						
					printf("det(A)=%lf", det(n, A));	
				}
				if(c2==2){
				
					printf("Transpose Matrix\n");
					printf("Please insert the dimensions of the matrix.\n");
					int n, m;
					printf("rows:");
					scanf("%d",&n);
					printf("columns:");
					scanf("%d",&m);
				
					double (*A)[m] = malloc(n*m*sizeof(double));
					double (*AT)[n] = malloc(m*n*sizeof(double));
					get_mat(n, n, A, stdin, 'A');
					transpose(n, m, A, AT);
					
					printf("This is the transpose matrix of A, AT:\n");			
					print_mat(m, n, AT, stdout);					
					
					free(A);
					free(AT);
				}
				if(c2==3){
				
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
					
					int i, j, n=n1, m=m1;
					double (*A)[m] = malloc(n*m*sizeof(double));
					double (*B)[m] = malloc(n*m*sizeof(double));
					
					get_mat(n, m, A, stdin, 'A');
					get_mat(n, m, B, stdin, 'B');
					
					char sel;
					do{
						
						printf("Press 'a' to add or 's' to substract.\n");
						scanf("%c",&sel);
						
						if(sel!='a' && sel!='s')
							printf("Invalid input!");
								
					} while(sel!='a' && sel!='s');
									
					if(sel=='a'){
						
						printf("This is the matrix C=A+B:\n");
						for(i=0; i<n; i++){						
							
							for(j=0; j<m; j++)
								printf("%lf ",A[i][j]+B[i][j]);
							
							printf("\n");
						}
					}
					else if(sel=='s'){
						
						printf("This is the matrix C=A-B:\n");
						for(i=0; i<n; i++){
							
							for(j=0; j<m; j++)
								printf("%lf ",A[i][j]-B[i][j]);
							
							printf("\n");
						}
					}					
				}
				if(c2==4){
				
					printf("Multiply Matrix With Number\nEnter a real number:");
					int n, m;
					double (*A)[m] = malloc(n*m*sizeof(double));
					double l;
					scanf("%lf",&l);
					scanf("%d %d",&n,&m);
					
					get_mat(n, m, A, stdin, 'A');	
					
					for(int i=0; i<n; i++)
						for(int j=0; j<m; j++)
							A[i][j] *= l;
										
					printf("This is the matrix C=l*A:\n");
					print_mat(n, m, A, stdout);		
					free(A);					
				}
				if(c2==5){
				
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
							printf("Matrix A needs to have as much columns as matrix B has rows!\n");
													
					} while(m1!=n2);
					
					double (*A)[m1] = malloc(n1*m1*sizeof(double));
					double (*B)[m2] = malloc(n2*m2*sizeof(double));
					double (*C)[m2] = calloc(n1*m2, n1*m2*sizeof(double));
					get_mat(n1, m1, A, stdin, 'A');
					get_mat(n2, m2, B, stdin, 'B');
					
					product_matrix(n1, m1, m2, A, B, C);
					printf("This is the matrix C=A*B::\n");
					print_mat(n1, m2, C, stdout);
					
					free(A);
					free(B);
					free(C);		
				}
			}
		}
				
		printf("Press 'e' to exit.\n Press any other key to continue.\n");
		char term;
		scanf(" %c",&term);
		if(term='e')
			break;
		clrscr();	
		//Το πρόγραμμα θα σταματήσει μόνο αν πατηθεί το γράμμα e στο πληκτρολόγιο του χρήστη
	}
	return 0;	
}
