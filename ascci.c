#include<stdio.h>
int main()
{
	int i;
	for(i=0;i<256;i++)
	{
		printf("%d\t%c\n",i,(unsigned char)i);
	}
	return 0;
}
