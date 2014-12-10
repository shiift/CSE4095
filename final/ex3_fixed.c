#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct ThreadArg_tag {
   int i;
   char* fileName;
} ThreadArg;

void* doWork(ThreadArg* arg)
{
   free(arg->fileName);
   free(arg);
   return NULL;
}

void readString(char* buf,size_t sz)
{
   char* end = buf + sz;
   char ch;
   while((ch=getchar()) != EOF && ch != '\n' && buf < end)
      *buf++ = ch;
   *buf = 0;   
}

int main(int argc,char* argv[])
{
   int i;
   int nbThreads = atoi(argv[1]);
   char buf[128];
   pthread_t minion[nbThreads];
   for(i=0;i < nbThreads;i++) {
      printf("give a filename: ");
      readString(buf,sizeof(buf)-1);
      printf("Got [%s]\n",buf);
      ThreadArg* arg = calloc(1, sizeof(ThreadArg));
      arg->i = i;
      arg->fileName = calloc(128, sizeof(char));
      strncpy(arg->fileName,buf,sizeof(buf)-1);
      pthread_create(minion+i,NULL,(void*(*)(void*))doWork,arg);
   }
   for(i=0;i < nbThreads;i++)
      pthread_join(minion[i],NULL);
   return 0;
}
