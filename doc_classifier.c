#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include "merge_sort.h"

char **stopWords = NULL;


int stopSize=0,classesSize=0,vocabularySize=0,testSize=0,**frequncy,*testFrequency;
char **classes,**vocab,**test;
double *pClasses,**pVocab;
long double*pTest;


void loadStopWords()
{
  	FILE* inp;
  	inp = fopen("stop_words.lykn","r");//filename of your data file
  	if (inp==NULL)
    {
    	printf("FILE MISSING stop_words.lykn NOT FOUND\n");
    	exit(0);
    }
  	int i = 0;
  	while(1){
      	char r = tolower((char)fgetc(inp));
      	int k = 0;

      	stopWords=realloc(stopWords,(i+1) * sizeof(char*));
      	stopWords[i] = malloc(30*sizeof(char));
      	while(r!=' ' && !feof(inp)){
            //read till , or EOF
          
        	stopWords[i][k++] = r;
              //store in array
        	r = tolower((char)fgetc(inp));
      	}

      	stopWords[i][k]='\0';
          //make last character of string null
      	if(feof(inp)){    //check again for EOF
          break;
      	}
    	i++;
  	}
  	stopSize=i+1;
  	/*for(int j = 0;j<stopSize;j++){
    	printf("%s\n",stopWords[j] ); //print array
  	}*/
  	fclose(inp);

}


void createTestData()
{
	FILE* inp;
  	inp = fopen("test.txt","r");//filename of your data file
  	if (inp==NULL)
    {
    	printf("FILE MISSING test.txt NOT FOUND\n");
    	exit(0);
    }
  	int i = 0,p=0;
  	while(1){
  		char r = tolower((char)fgetc(inp));
        int k = 0,z=0;
        char wrd[30]={};

      	while(r!=' '  && !feof(inp)){

          if(r=='a' || r=='b' || r=='c' || r=='d' || r=='e' || r=='f' || r=='g' || r=='h' || 
             r=='i' || r=='j' || r=='k' || r=='l' || r=='m' || r=='n' || r=='o' || r=='p' || 
             r=='q' || r=='r' || r=='s' || r=='t' || r=='u' || r=='v' || r=='w' || r=='x' || 
             r=='y' || r=='z')
            {
              wrd[k++] = r;
              z=1;
            }
          else if(r!='\'')
          {
            break;
          } 

          r = tolower((char)fgetc(inp));
            
           
        }
        if (z==1)
      {
        wrd[k]='\0';
      int check=0;
      for (int i = 0; i < stopSize; ++i)
      {
        if(strcmp(stopWords[i],wrd)==0)
          {
            check=1;
            break;
          }
        
      }

      for (int i = 0; i < p; ++i)
      {
        if(strcmp(test[i],wrd)==0)
          {
            testFrequency[i]++;
            check=2;
            break;
          }
        
      }
      if(check==0)
      {
        testSize++;
        testFrequency=realloc(testFrequency,testSize*sizeof(int));
        testFrequency[testSize-1]=0;
        testFrequency[testSize-1]++;
        test=realloc(test,(p+1) * sizeof(char *));
        test[p]=malloc(30*sizeof(char));
        strcpy(test[p],wrd);
        
        
        p++;
        
      }
      
      }
        //make last character of string null
        if(feof(inp)){    //check again for EOF
            break;
        }
    	i++;
  	}
  	
  	/*for(int j = 0;j<testSize;j++){
    	printf("%s %d\n",test[j],testFrequency[j] ); //print array
  	}*/
  	fclose(inp);

  
}

void loadModel()
{
	FILE *inp=fopen("info.lykn","r");
    if (inp==NULL)
    {
    	printf("FILE MISSING info.lykn NOT FOUND\n");
    	exit(0);
    }
	while(1)	
	{	char r = tolower((char)fgetc(inp));
      	int k = 0;
      	int chk=0;
      	char *line=NULL;
      	while(r!='\n' && !feof(inp)){
            //read till , or EOF
          	line=realloc(line,(k+1)*sizeof(char));
        	line[k++] = r;
        	r = tolower((char)fgetc(inp));
        	chk=1;
      	}
      	if(chk==1)
      	{line[k]='\0';
      	      	//printf("%s\n", line);
      	
      	      	classes=realloc(classes,(classesSize+1)*sizeof(char *));
      			classes[classesSize]=malloc(30*sizeof(char));
      			pClasses=realloc(pClasses,(classesSize+1)*sizeof(double));
      			sscanf(line,"%s %lf",classes[classesSize],&pClasses[classesSize]);
      			//printf("%s %lf\n",classes[classesSize],pClasses[classesSize]);
      			classesSize++;}
          //make last character of string null
      	if(feof(inp)){    //check again for EOF
          break;
      	}
    	
    }
    fclose(inp);
    //printf("%d\n",classesSize );






    inp=fopen("beast.lykn","r");
    if (inp==NULL)
    {
    	printf("FILE MISSING beast.lykn NOT FOUND\n");
    	exit(0);
    }
	while(1)	
	{	
      	if(feof(inp)){ 
          break;
      	}  	
      	
      	vocab=realloc(vocab,(vocabularySize+1)*sizeof(char *));
		vocab[vocabularySize]=malloc(30*sizeof(char));
		pVocab=realloc(pVocab,(vocabularySize+1)*sizeof(double *));
		pVocab[vocabularySize]=malloc(classesSize*sizeof(double));
		fscanf(inp,"%s",vocab[vocabularySize]);
		//printf("%s",vocab[vocabularySize]);
		for (int i = 0; i < classesSize; ++i)
		{
			fscanf(inp,"%lf",&pVocab[vocabularySize][i]);
			//printf(" %lf",pVocab[vocabularySize][i]);
		}
		//printf("\n");
		vocabularySize++;
        char r = (char)fgetc(inp);

        //printf("%c\n",r);
      	if(feof(inp)){ 
          break;
      	}
    	
    }
    fclose(inp);
    vocabularySize--;

    /*for (int h = 0; h < vocabularySize; ++h)
    {
    
    	printf("%s",vocab[h]);
		for (int i = 0; i < classesSize; ++i)
		{
			
			printf(" %lf",pVocab[h][i]);
		}
		printf("\n");
	}*/
}

int search(char srch[])
{
	int dwn=0,up=vocabularySize,mid;
	while(dwn<up)
	{

		mid=(up+dwn)/2;
		
		if(strcmp(vocab[mid],srch)==0)
		{
			return mid;
		}
		else if(strcmp(vocab[mid],srch)>0)
		{
			up=mid-1;
		}
		else
		{
			dwn=mid+1;
		}
	}
	return -1;
}



void predictClass()
{
	pTest=malloc(classesSize*sizeof(long double));
	for (int i = 0; i < classesSize; ++i)
	{
		pTest[i]=pClasses[i];
	}
	
	for (int i = 0; i < testSize; ++i)
	{	
		int pos=search(test[i]);
		//printf("%s %s  %d %lf %lf %lf \n",test[i],vocab[pos],testFrequency[i],pVocab[pos][0],pVocab[pos][1],pVocab[pos][2]);
		if (pos!=-1)
		{	//printf("%d\n",i);
			for (int j = 0; j < classesSize; ++j)
			{
				pTest[j]=pTest[j]*pow(pVocab[pos][j],testFrequency[i]);
				//printf("%lf\n",pow(pVocab[pos][j],testFrequency[i]));
			}
		}
	}
	int resultPos;
	long double pMax=-1;
	for (int i = 0; i < classesSize; ++i)
	{
		if(pTest[i]>pMax)
		{
			
			pMax=pTest[i];
			resultPos=i;	
		}
	}
	if (pMax<1)
	{
		printf("The Document belongs to none of the class\n");
	}
	else
		printf("The Document is of %s Class\n",classes[resultPos]);

}

void main() 
{
	loadStopWords();
	createTestData();
	loadModel();
	predictClass();

}
