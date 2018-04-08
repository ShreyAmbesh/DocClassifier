#include <stdio.h>


char **voc;
int **freq,size,classSize;
void merge(int a,int b,int c)
{
	int n1=b-a+1,n2=c-b,i,j,k;
	char ar1[n1][30],ar2[n2][30];
	int fr1[n1][classSize],fr2[n2][classSize];
	for (i = 0; i <n1; ++i)
	{
		strcpy(ar1[i],voc[a+i]);
		for (int l = 0; l <classSize; ++l)
		{
			fr1[i][l]=freq[a+i][l];
			
		}
		
	}

	for (j = 0; j <n2; ++j)
	{
		strcpy(ar2[j],voc[b+j+1]);
		for (int l = 0; l < classSize; ++l)
		{
			fr2[j][l]=freq[b+j+1][l];
		}
	}

	
	i=0;
	j=0;
	for (k = a; i<n1 && j<n2; ++k)
	{
		if(strcmp(ar1[i],ar2[j])>0)
		{
			strcpy(voc[k],ar2[j]);
			for (int l = 0; l < classSize; ++l)
			{
				freq[k][l]=fr2[j][l];
			}
			j++;
		}
		else
		{
			strcpy(voc[k],ar1[i]);
			for (int l = 0; l < classSize; ++l)
			{
				freq[k][l]=fr1[i][l];
			}
			i++;
		}
	}
	
    
    while (i < n1)
    {
        strcpy(voc[k],ar1[i]);
        for (int l = 0; l < classSize; ++l)
		{
			freq[k][l]=fr1[i][l];
		}
        i++;
        k++;
    }
 
    
    while (j < n2)
    {
        strcpy(voc[k],ar2[j]);
	    for (int l = 0; l < classSize; ++l)
		{
			freq[k][l]=fr1[j][l];
		}
        j++;
        k++;
    }
	

}


void mergeSortVocabulary(int p,int r)
{
	if (p<r)
	{
		int q=(p+r)/2;
		
		mergeSortVocabulary(p,q);
		mergeSortVocabulary(q+1,r);
		merge(p,q,r);
	}
	
}

void sort(char **tri,int **fr,int sz,int clsz)
{
	voc=tri;
	freq=fr;
	size=sz;
	classSize=clsz;
	mergeSortVocabulary(0,size-1);
}