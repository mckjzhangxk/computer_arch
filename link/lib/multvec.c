/* multvec.c */
/* $begin multvec */
int multcnt = 0;
#include <stdio.h>
//gcc -Wall -Og  -c multvec.c
//gcc -Wall -Og  -c multvec.c
//ar rcs libvector.a addvec.o multvec.o
void multvec(int *x, int *y,int *z, int n)
{
    int i;

    multcnt++;
#ifdef MUL
    for (i = 0; i < n; i++)
	z[i] = x[i] * y[i];
    printf("IF\n");
#else
    for (i = 0; i < n; i++)
        z[i] = x[i] - y[i];
    printf("ELSE\n");
#endif
}
/* $end multvec */

