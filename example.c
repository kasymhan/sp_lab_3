#include <stdio.h>
#include <stdlib.h> 
 
int main(){
    // переменые
	int a;
    asm(
            "mov %%eax, %1\n"
            "movl %0, %%eax\n"
            :"=r"(a) 
            :"r"(a)
            :"%eax"
            );
    // Получившая матрица 
    printf("%d\n",a);
    return 0;
}
