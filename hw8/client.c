#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <errno.h>
#include <assert.h>
#include "command.h"

void checkError(int status,int line)
{
   if (status < 0) {
      printf("socket error(%d)-%d: [%s]\n",getpid(),line,strerror(errno));
      exit(-1);
   }
}

int main(int argc,char* argv[]) 
{
   // Create a socket
   int sid = socket(PF_INET,SOCK_STREAM,0);
   struct sockaddr_in srv;
   struct hostent *server = gethostbyname("localhost");
   //srv.sin_len    = sizeof(srv);
   srv.sin_family = AF_INET;
   srv.sin_port   = htons(8090);
   memcpy(&srv.sin_addr.s_addr,server->h_addr,server->h_length);
   int status = connect(sid,(struct sockaddr*)&srv,sizeof(srv));
   checkError(status,__LINE__);
   int done = 0;
   FILE* cmds = fopen(argv[1],"r");
   do {
      char opcode[32];
      fscanf(cmds,"%s ",opcode);
      if (strncmp(opcode,"send",4) == 0) {
         Command c;
         fgets(c.arg,sizeof(c.arg)-1,cmds);
         c.arg[strlen(c.arg)-1] = 0; // removes trailing '\n'
         c.code = htonl(CC_SEND);
         printf("Sending command arg [%s]\n",c.arg);
         int status = send(sid,&c,sizeof(c),0);checkError(status,__LINE__);
      } else if (strncmp(opcode,"get",3) == 0) { 
         Command c;
         c.code = htonl(CC_GET);
         int status = send(sid,&c,sizeof(c),0);checkError(status,__LINE__);
         Payload p;
         status = recv(sid,&p,sizeof(p),0);checkError(status,__LINE__);
         p.code = ntohl(p.code);
         if (p.code == PL_SZ) {
            int toRead = ntohl(p.nb);
            int k;
            printf("Expecting: %d\n",toRead);
            for(k=0;k<toRead;k++) {
               status = recv(sid,&p,sizeof(p),0);checkError(status,__LINE__);
               p.code = ntohl(p.code);
               assert(p.code == PL_MSG);
               printf("msg[%d] = %s\n",k,p.arg);
            }
            printf("Got all messages!\n");
         } else printf("Didn't get a size message!\n");
      } else if (strncmp(opcode,"listen",6) == 0) {
          Command c;
          c.code = htonl(CC_LISTEN);
          int status = send(sid,&c,sizeof(c),0);checkError(status,__LINE__);
          while(1){
              Payload p;
              status = recv(sid,&p,sizeof(p),0);checkError(status,__LINE__);
              p.code = ntohl(p.code);
              if (p.code == PL_SZ) {
                int toRead = ntohl(p.nb);
                int k;
                printf("Expecting: %d\n",toRead);
                for(k=0;k<toRead;k++) {
                   status = recv(sid,&p,sizeof(p),0);checkError(status,__LINE__);
                   p.code = ntohl(p.code);
                   assert(p.code == PL_MSG);
                   printf("msg[%d] = %s\n",k,p.arg);
                }
                printf("Got all messages!\n");
              } else printf("Didn't get a size message!\n");
          }
      } else if (strncmp(opcode,"exit",4) == 0) {
         done = 1;
         Command c;
         c.code = htonl(CC_EXIT);
         c.arg[0] = 0;
         int status = send(sid,&c,sizeof(c),0);checkError(status,__LINE__);
      }
   } while (!done);
   fclose(cmds);
   return 0;
}
