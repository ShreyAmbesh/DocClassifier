#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "merge_sort.h"

char **stopWords = NULL;
char **fileList = NULL;
int *fileClass = NULL;

int stopSize=0,classesSize=0,fileListSize=0,vocabularySize=0,**frequncy,*classSz,*classVocabSize;
double **pVocab;
char **classes,**vocab;

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
  for(int j = 0;j<stopSize;j++){
      printf("%s\n",stopWords[j] ); //print array
  }
  fclose(inp);

}


void makeDocList()
{
  DIR *dirF;
  
  struct dirent *entF;
  classSz=malloc(classesSize*sizeof(int));
  for (int i = 0; i < classesSize; ++i)
  {

    printf("\n\n\n%s\n",classes[i]);
    if ((dirF = opendir(classes[i])) != NULL) {
      int p=0;
    while ((entF = readdir(dirF)) != NULL) {


      if (entF->d_type == DT_REG /*&& strcmp(entF->d_name,"mega.txt")!=0*/) {
        fileList=realloc(fileList,(fileListSize+1)*sizeof(char *));
        fileList[fileListSize] = malloc(30*sizeof(char));

        fileClass=realloc(fileClass,(fileListSize+1)*sizeof(int));
        fileClass[fileListSize]=i;
        char nm[80]={};
        strcat(nm,classes[i]);
        strcat(nm,"/");
        strcat(nm,entF->d_name);
        strcpy(fileList[fileListSize],nm);
        printf("%s %d\n",fileList[fileListSize],fileClass[fileListSize]);
        p++;
        fileListSize++;}
       }
       classSz[i]=p;
    closedir(dirF);
  } else{
    printf("File Not Found ");
    exit(0);
  }
  }
}


void makeClassList()
{
  DIR *dir;
  int n=0;
  struct dirent *ent;

  if ((dir = opendir("../C/")) != NULL) {

    while ((ent = readdir(dir)) != NULL) {

      if((ent->d_type != DT_REG) && (!(strcmp(ent->d_name,".") == 0 || strcmp(ent->d_name,"..") == 0)))
      {
        classes=realloc(classes,(n+1)*sizeof(char *));
        classes[n] = malloc(30*sizeof(char));
        strcpy(classes[n],ent->d_name);
        //printf("%s \n",classes[n]);
        n++;
      }

    }
    classesSize=n;
    
    closedir(dir);
  } else{
    printf("ERROR");
    return;
  }
}






void createVocabulary()
{   int p = 0;
    FILE* inp;
    FILE *meg;
    classVocabSize=malloc(classesSize*sizeof(int));
    for (int x = 0; x < classesSize; ++x)
    {
      classVocabSize[x]=0;
    }
  for(int j=0;j<fileListSize;j++)
  {
    printf("%s\n",fileList[j]);
    inp = fopen(fileList[j],"r");//filename of your data file
    
    while(1){
        char r = tolower((char)fgetc(inp));
        int k = 0,z=0;
        char wrd[30]={};

        
        //char wrd[80]={};
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
        if(strcmp(vocab[i],wrd)==0)
          {
            frequncy[i][fileClass[j]]++;
            classVocabSize[fileClass[j]]++;
            check=2;
            break;
          }
        
      }
      if(check==0)
      {
        vocabularySize++;
        frequncy=realloc(frequncy,vocabularySize*sizeof(int *));
        frequncy[vocabularySize-1] = malloc(classesSize*sizeof(int));
        for (int i = 0; i < classesSize; ++i)
        {
          frequncy[vocabularySize-1][i]=0;
        }
        frequncy[vocabularySize-1][fileClass[j]]++;
        classVocabSize[fileClass[j]]++;
        vocab=realloc(vocab,(p+1) * sizeof(char *));
        vocab[p]=malloc(30*sizeof(char));
        strcpy(vocab[p],wrd);
        //printf("%s  %d\n", vocab[p],frequncy[vocabularySize-1][fileClass[j]]);
        
        p++;
        
      }
      
      }
        
        
        
        
        
            //make last character of string null
        if(feof(inp)){    //check again for EOF
            break;
        }
        

    }
    
    fclose(inp);
  }


  sort(vocab,frequncy,vocabularySize,classesSize);
  pVocab=malloc(vocabularySize*sizeof(double*));
  for (int j = 0; j < vocabularySize; ++j)
  {
   pVocab[j] = malloc(classesSize*sizeof(double));
   for (int q = 0; q < classesSize; ++q)
    {
      pVocab[j][q]=1000*((double)(frequncy[j][q]+1))/((double)(classSz[q]+vocabularySize));
    } 
  }
  meg=fopen("beast.lykn","w+");
  for(int j = 0;j<vocabularySize;j++){
    printf("%s", vocab[j]); //print array
      fprintf(meg,"%s", vocab[j]);
    /*for (int i = 0; i < classesSize; ++i)
    {
      printf(" %d",frequncy[j][i]); //print array
        fprintf(meg," %d",frequncy[j][i]);
    }*/
    for (int i = 0; i < classesSize; ++i)
    {
      printf(" %lf",pVocab[j][i]); //print array
        fprintf(meg," %lf",pVocab[j][i]);
    }
    printf("\n"); //print array
        fprintf(meg,"\n");
      
  }
  
  fclose(meg);

  
}
void storeInfo()
{
  FILE *fp=fopen("info.lykn","w+");
  double tsz=0.0;
  for (int j = 0; j < classesSize; ++j)
    {
      tsz=tsz+classSz[j];
    }
  for (int i = 0; i < classesSize; ++i)
  {
    double csz=classSz[i];
    double pClass=100*csz/tsz;
    fprintf(fp, "%s %lf\n",classes[i],pClass);
  }
  fclose(fp);

}

void main() {

  makeClassList();
  makeDocList();
  loadStopWords();
  createVocabulary();
  storeInfo();
  

}
