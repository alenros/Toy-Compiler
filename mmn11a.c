#include <stdio.h>

#define SIZEOFVECTICE 4 //size of each vector

int scalar_product(int u[],int v[],int size);
void main()
{
	int u[SIZEOFVECTICE],v[SIZEOFVECTICE];
	printf("Enter int elements for 1st vector, seperated by CR\n");
	for(int i=0;i<SIZEOFVECTICE;i++)
		scanf("%d",&u[i]);
	printf("Enter int elements for 2nd vector, same trick..\n");
	for(int i=0;i<SIZEOFVECTICE;i++)
		scanf("%d",&v[i]);
	printf("your result sir: %d\n",scalar_product(u,v,SIZEOFVECTICE));
}

int scalar_product(int u[],int v[],int size)		//return scalar product of two vectice, both the size of "size"
{
	int scalarProduct=0;	//initialize result of the scalar product
	for (int i=0;i<size;i++)
		scalarProduct+=u[i]*v[i];	//u*v=u1*v1+u2*v2+..+un*vn
	return (scalarProduct);
}
