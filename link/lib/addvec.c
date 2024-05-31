/* addvec.c */
/* $begin addvec */
int addcnt = 0;
#include <stdio.h>
void addvec(int *x, int *y,int *z, int n) 
{
    int i;

    addcnt++;
    printf("%p:%d\n",&addcnt,addcnt);
    for (i = 0; i < n; i++)
	z[i] = x[i] + y[i];
}
/* $end addvec */

