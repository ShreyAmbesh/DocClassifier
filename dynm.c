#include <stdio.h>
#include <string.h>
#include <stdlib.h>


struct class{
  char name[32];
  char **fileList;
};
struct class *classes=NULL;

void main()
{
  char **stopWords = NULL;
  classes=realloc(classes,sizeof(&classes));
  strcpy(classes[0].name,"physics");
  int i = 0;
  classes[0].fileList=realloc(classes[0].fileList,(i+1)*sizeof(char *));
  int k = 0;
  for (i = 0; i < 9; i++)
  {
      printf("%d\n",i);
      stopWords=realloc(stopWords,(i+1) * sizeof(char*));
      stopWords[i] = malloc((k+1)*sizeof(char));
      for (k = 0; k < 5; k++)
      {

          stopWords[i][k] = 'c';
      }
  }
  for (i = 0; i < 9; i++)
  {
    printf("%s\n", stopWords[i]);

  }

  free(stopWords);

}
