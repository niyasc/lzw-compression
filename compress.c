#include<stdio.h>
#include<string.h>
#include<stdbool.h>
struct term
{
	char sequence[10];
	int code;
}words[100];
int n=0;
bool isin(char word[],char c)
{
	char temp[10];
	strcpy(temp,word);
	int k=strlen(temp);
	temp[k]=c;
	temp[k+1]=0;
	int i;
	for(i=0;i<n;i++)
	{
		if(strcmp(temp,words[i].sequence)==0)
		{
			return true;
		}
	}
	return false;
}
int getcode(char word[])
{
	int i;
	for(i=0;i<n;i++)
	{
		if(strcmp(word,words[i].sequence)==0)
			return words[i].code;
	}
	printf("\nSomething went wrong\n");
}
int main(int argc,char *argv[])
{
	if(argc!=3)
	{
		printf("Syntax : <executable> <input file> <output file>\n");
		return 1;
	}
	char string[1024];
	FILE *ptr=fopen(argv[1],"r");
	if(ptr==NULL)
	{
		printf("Could not open file\n");
		return 1;
	}
	int op[1024],op_count=0;
	bool op_bin[12288];
	int i=0;
	while(!feof(ptr))
	{
		fscanf(ptr,"%c",&string[i++]);
	}
	string[--i]=0;
	fclose(ptr);
	char word[10];
	int cur_code;
	word[0]=string[0];
	word[1]=0;
	int code_base=256;
	for(i=1;string[i]!=0;i++)
	{
		if(isin(word,string[i]))
		{
			int k=strlen(word);
			word[k]=string[i];
			word[k+1]=0;
		}
		else
		{
			//int cur_code;
			if(strlen(word)==1)
				cur_code=string[i-1];
			else
				cur_code=getcode(word);
			op[op_count++]=cur_code;
			int k=strlen(word);
			word[k]=string[i];
			word[k+1]=0;
			strcpy(words[n].sequence,word);
			words[n].code=code_base++;
			n++;
			word[0]=string[i];
			word[1]=0;
		}
	}
	if(strlen(word)==1)
		cur_code=string[i-1];
	else
		cur_code=getcode(word);
	op[op_count++]=cur_code;
	for(i=0;i<op_count;i++)
	{
		//print sequence
		if(op[i]<256)
			printf("%c",op[i]);
		else
			printf("%d",op[i]);
		int t=op[i];
		int j;
		for(j=i*12;j<(i+1)*12;j++)
			op_bin[j]=0;
		j=(i+1)*12-1;
		while(t)
		{
			op_bin[j]=t%2;
			t=t/2;
			j--;
		}
	}
	int len=op_count*12;
	if(len%8!=0)
	{
		while(len%8!=0)
		{
			op_bin[len]=0;
			len++;
		}
	}
	ptr=fopen(argv[2],"w");
	for(i=0;i<len/8;i++)
	{
		unsigned c=0;
		int j;
		for(j=i*8;j<(i+1)*8;j++)
			c=c*2+op_bin[j];
		fprintf(ptr,"%c",c);
	}
	printf("\n");
	fclose(ptr);
		
		
	return 0;
}
