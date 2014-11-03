#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

char* md5sum(char* payload,size_t sz);

int main(int argc,char* argv[])
{
   char* fName = argv[1];
   FILE* src = fopen(fName,"r");
   fseek(src,0,SEEK_END);
   long sz = ftell(src);
   fseek(src,0,SEEK_SET);
   char* payload = malloc(sizeof(char)*sz);
   fread(payload,sizeof(char),sz,src);
   fclose(src);
   char* rv = md5sum(payload,sz);
   printf("Got md5 [%s]\n",rv);
   free(rv);
   return 0;
}

void sendPayload(int fd,char* payload,size_t sz) {
   int sent=0,rem = sz;
   while(sent != sz) {
      int nbSent = write(fd,payload+sent,rem);
      sent += nbSent;
      rem  -= nbSent;
   }
}

char* readResponse(int fd) {
   int sz = 8;
   char* buf = malloc(sz);
   int ttl = 0,at = 0;
   int recvd;
   do {
      recvd = read(fd,buf+at,sz - at);
      ttl += recvd;
      at  += recvd;
      if (recvd > 0 && ttl == sz) {
         buf = realloc(buf,sz*2);
         sz *= 2;
      }
   } while (recvd > 0);
   char* final = malloc(ttl+1);
   memcpy(final,buf,ttl);
   final[ttl] = 0;
   free(buf);
   return final;
}

char* md5sum(char* payload,size_t sz)
{
   // Implement your solution here
   return NULL;
}
