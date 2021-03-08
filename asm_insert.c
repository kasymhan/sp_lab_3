#include <stdio.h>
#include <stdlib.h> 
 
int main(){
    // переменые
    int   m,n,t,i,j,k;
    m = 9;
    n = 10;
    int range = 10;
    int  A[m][n];
    int  B[n][1];
    int  C[m][1];
    // Запоkнение переменных матрицы А
    for(int i=0;i<m;i++){
        for(int j=0;j<n;j++){
            A[i][j]= rand() % range+1;
        }
    }
    // Заполнение переменных матрицы B
    for(int i=0;i<n;i++){
        B[i][0]=rand() % range+1;
    }
    
    printf("Матрица А\n");
    for (int i=0; i<m; i++){
    	for(int j=0; j<n; j++){

        	printf("%d\t", A[i][j]);

    	}
    	 printf("\n");
    }
    printf("Матрица B\n");
    for (int i=0;i<n;i++){
        printf("%d\n",B[i][0]);
    }
    int  *ptr_array_a = &A[0][0];
    int  *ptr_array_b = &B[0][0];
    int  *ptr_array_c = &C[0][0];
    int  *end_array_a = &A[m-1][n-1];
    int  *end_array_b = &B[n-1][1];
    int  *end_array_c = &C[m-1][1];
    // Перемножение матриц
    i=0;
    j=0;
    k=0;
    asm(
            "mov %[PTRA], %%ebx\n"
            //Суммирование столбцов по строке
            "loop:\n"
            "mov $4, %%eax\n"
            "mov %[i], %%edx\n"
            "mov %%edx, %%ecx\n"
            "mul %%ecx\n"
            "mov %[PTRB], %%edx\n"
            "add %%eax, %%edx\n"
            "mov (%%edx), %%eax\n"
            "mov (%%ebx), %%ecx\n"
            "mul %%ecx\n"
            "add %%eax, %[k]\n"
            "addl $1,%[i]\n"
            "mov %[i], %%edx\n"
            "mov %[n], %%ecx\n"
            "add $4, %%ebx\n"
            "cmpl %%edx, %%ecx\n"
            "jne loop\n"
            // Переход на следующую строку
            "movl $0,%[i]\n"
            "mov %[j], %%edx\n"
            "movl $4, %%eax\n"
            "mov %%edx, %%ecx\n"
            "mul %%ecx\n"
            "mov %[PTRC],%%edx\n"
            "add %%eax, %%edx\n"
            "mov %[k], %%ecx\n"
            "mov %%ecx, (%%edx)\n"
            "movl $0, %[k]\n"
            "addl $1, %[j]\n"
            "mov %[j], %%edx\n"
            "mov %[m], %%ecx\n"
            "cmpl %%edx, %%ecx\n"
            "jne loop\n"
            :
            : 
            [n]"m"(n),
            [i]"m"(i),
            [j]"m"(j),
            [PTRA]"m"(ptr_array_a),
            [PTRB]"m"(ptr_array_b),
            [PTRC]"m"(ptr_array_c),
            [ENDA]"m"(end_array_a),
            [ENDB]"m"(end_array_b),
            [ENDC]"m"(end_array_c),
            [m]"m"(m),
            [k]"m"(k)
            : "%edx","%ebx","%eax","%ecx"
            );
    // Получившая матрица 
    printf("Новая матрица\n");
    for(int i=0;i<m;i++){
        printf("%d\n",C[i][0]);
    }
    return 0;
}
