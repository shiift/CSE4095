#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <errno.h>

#define DEFAULT_HOST "localhost"
#define DEFAULT_PORT 8080

#include "command.h"
void checkError(int status,int line)
{
   if (status < 0) {
      printf("socket error(%d)-%d: [%s]\n",getpid(),line,strerror(errno));
      exit(-1);
   }
}

void doLSCommand(int sid);
void doExitCommand(int sid);
void doGETCommand(int sid);
void doPUTCommand(int sid); 
void doSIZECommand(int sid); 
void doMGETCommand(int sid);
void doMPUTCommand(int sid); 
void doCloseCommand(int sid); 
int doOpenCommand(); 


int main(int argc,char* argv[]) 
{
   char fName[256];
   char* fList;
   char* host = DEFAULT_HOST;
   short int port = DEFAULT_PORT;

   if(argc > 1) { host = argv[1]; }
   if(argc > 2) { port = atoi(argv[2]); }

   // Create a socket
   int sid = socket(PF_INET,SOCK_STREAM,0);
   struct sockaddr_in srv;
   struct hostent *server = gethostbyname(host);
   srv.sin_family = AF_INET;
   srv.sin_port   = htons(port);
   memcpy(&srv.sin_addr.s_addr,server->h_addr,server->h_length);
   int status = connect(sid,(struct sockaddr*)&srv,sizeof(srv));
   checkError(status,__LINE__);
   int done = 0;
   int active = 1;
   do {
      char opcode[32];
      scanf("%s",opcode);
      if (strncmp(opcode,"lsize",5) == 0) {  // check lsize before ls
          printf("Give a local filename: ");
          scanf("%s",fName);
          printf("File size of %s is %d bytes\n", fName, getFileSize(fName) );
      } else if (strncmp(opcode,"open",4)==0) {
         if(active) { doCloseCommand(sid); }
         sid = doOpenCommand();
         active = 1;
      } else if (strncmp(opcode,"exit",4) == 0) {
         doExitCommand(sid);
         done = 1;
      } else if (strncmp(opcode,"lls",3) == 0) {
         printf("[\n%s]\n", fList = makeFileList(".") );
         free(fList);
      } else if (active == 0) { // remaining commands require connection
          printf("Not connected to a remote server!\n");
      } else if (strncmp(opcode,"ls",2) == 0) {
         doLSCommand(sid);
      } else if (strncmp(opcode,"size",4) == 0) {
         doSIZECommand(sid);
      } else if (strncmp(opcode,"get",3)==0) {
         doGETCommand(sid);
      } else if (strncmp(opcode,"put",3)==0) {
         doPUTCommand(sid);
      } else if (strncmp(opcode,"mget",4)==0) {
         doMGETCommand(sid);
      } else if (strncmp(opcode,"mput",4)==0) {
         doMPUTCommand(sid);
      } else if (strncmp(opcode,"close",5)==0) {
         doCloseCommand(sid);
         active = 0;
      }
   } while(!done);

   return 0;
}

void doLSCommand(int sid)
{
   Command c;
   Payload p;
   int status;
   c.code = htonl(CC_LS);
   c.arg[0] = 0;
   status = send(sid,&c,sizeof(c),0);checkError(status,__LINE__);
   status = recv(sid,&p,sizeof(p),0);checkError(status,__LINE__);
   p.code = ntohl(p.code);
   p.length = ntohl(p.length);
   int rec  = 0,rem = p.length;
   char* buf = malloc(sizeof(char)*p.length);
   while (rem != 0) {
      int nbrecv = recv(sid,buf+rec,rem,0);checkError(status,__LINE__);
      rec += nbrecv;
      rem -= nbrecv;
   }
   if(p.code == PL_TXT) 
      printf("Got: [\n%s]\n",buf);
   else { 
      printf("Unexpected payload: %d\n",p.code);
   }
   free(buf);
}

void doGETCommand(int sid) 
{
   Command c;
   Payload p;
   int status;
   c.code = htonl(CC_GET);
   printf("Give a filename:");
   char fName[256];
   scanf("%s",fName);	
   strncpy(c.arg,fName,255);
   c.arg[255] = 0;
   status = send(sid,&c,sizeof(c),0);checkError(status,__LINE__);
   status = recv(sid,&p,sizeof(p),0);checkError(status,__LINE__);
   p.code = ntohl(p.code);
   p.length = ntohl(p.length);
   receiveFileOverSocket(sid,c.arg,".download",p.length);
   printf("transfer done\n");
}

void doPUTCommand(int sid) 
{
   Command c;
   Payload p;
   int status;
   c.code = htonl(CC_PUT);
   printf("Give a local filename:");
   char fName[256];
   scanf("%s",fName);	
   strncpy(c.arg,fName,255);
   c.arg[255] = 0;
   status = send(sid,&c,sizeof(c),0);checkError(status,__LINE__);
   int fs = getFileSize(c.arg);
   p.code   = ntohl(PL_FILE);
   p.length = ntohl(fs);
   status = send(sid,&p,sizeof(p),0);checkError(status,__LINE__);
   sendFileOverSocket(c.arg,sid);
   printf("transfer done\n");
}

void doExitCommand(int sid)
{
   Command c;
   int status;
   c.code = htonl(CC_EXIT);
   c.arg[0] = 0;
   status = send(sid,&c,sizeof(c),0);checkError(status,__LINE__);
}

void doSIZECommand(int sid) 
{
   Command c;
   Payload p;
   int status;
   c.code = htonl(CC_SIZE);
   printf("Give a remote filename: ");
   char fName[256];
   scanf("%s",fName);
   strncpy(c.arg,fName,255);
   c.arg[255] = 0;
   status = send(sid,&c,sizeof(c),0);checkError(status,__LINE__);
   status = recv(sid,&p,sizeof(p),0);checkError(status,__LINE__);
   p.code = ntohl(p.code);
   p.length = ntohl(p.length);
   printf("File size of %s is %d bytes\n", c.arg, p.length );
}

void doMGETCommand(int sid)
{
   Command c;
   Payload p;
   int status;
   char fList[10000];
   char* fName;

   c.code = htonl(CC_GET);
   fgets(fList, 10000, stdin); // clear current line
   printf("Give a list of filenames: ");
   fgets(fList, 10000, stdin);
   fName=strtok(fList, " \n");
   while(fName!=NULL)
   {
     strncpy(c.arg,fName,255);
     c.arg[255] = 0;
     status = send(sid,&c,sizeof(c),0);checkError(status,__LINE__);
     status = recv(sid,&p,sizeof(p),0);checkError(status,__LINE__);
     p.code = ntohl(p.code);
     p.length = ntohl(p.length);
     receiveFileOverSocket(sid,c.arg,".download",p.length);
     fName=strtok(NULL, " \n");
   }
   printf("transfer done\n");
}

void doMPUTCommand(int sid) 
{
   Command c;
   Payload p;
   int status;
   char fList[10000];
   char* fName;

   c.code = htonl(CC_PUT);
   fgets(fList, 10000, stdin); // clear current line
   printf("Give a list of local filenames: ");
   fgets(fList, 10000, stdin);
   fName=strtok(fList, " \n");
   while(fName!=NULL)
   {
     strncpy(c.arg,fName,255);
     c.arg[255] = 0;
     status = send(sid,&c,sizeof(c),0);checkError(status,__LINE__);
     int fs = getFileSize(c.arg);
     p.code   = ntohl(PL_FILE);
     p.length = ntohl(fs);
     status = send(sid,&p,sizeof(p),0);checkError(status,__LINE__);
     sendFileOverSocket(c.arg,sid);
     fName=strtok(NULL, " \n");
   }
   printf("transfer done\n");
}

void doCloseCommand(int sid)
{
   Command c;
   int status;
   c.code = htonl(CC_EXIT);
   c.arg[0] = 0;
   status = send(sid,&c,sizeof(c),0);checkError(status,__LINE__);
}

int doOpenCommand()
{
   int c;
   struct hostent *server;
   char hName[256] = "";
   short int port;

   // Create a socket
   int sid = socket(PF_INET,SOCK_STREAM,0);
   struct sockaddr_in srv;
   srv.sin_family = AF_INET;

   fgets(hName, 256, stdin); // clear current line
   printf("Name of remote host [default: %s]: ", DEFAULT_HOST);
   c=getc(stdin);
   if(c=='\n') {
      server = gethostbyname(DEFAULT_HOST);
   } else {
      ungetc(c,stdin); 
      scanf("%s", hName);
      server = gethostbyname(hName);
      fgets(hName, 256, stdin); // clear current line
   } 

   printf("Enter port number [default %hd]: ", DEFAULT_PORT);
   c=getc(stdin);
   if(c=='\n') {
      srv.sin_port   = htons(DEFAULT_PORT);
   } else {
      ungetc(c,stdin); 
      scanf("%hd",&port);
      srv.sin_port   = htons(port);
   }
   srv.sin_family = AF_INET;
   memcpy(&srv.sin_addr.s_addr,server->h_addr,server->h_length);
   int status = connect(sid,(struct sockaddr*)&srv,sizeof(srv));
   checkError(status,__LINE__);
   return sid;
}
