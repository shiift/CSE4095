#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <pthread.h>
#include "command.h"

void checkError(int status)
{
   if (status < 0) {
      printf("socket error(%d): [%s]\n",getpid(),strerror(errno));
      exit(-1);
   }
}

typedef char* Msg;

typedef struct ChatRoom {
   pthread_t* _workers;
   int        _mxw;
   int        _nbw;
   Msg*       _log;
   int        _mxl;
   int        _nbl;
} ChatRoom;

typedef struct Clerk {
   ChatRoom* _room;   // room the clerk is viewing
   int       _fd;     // file descriptor to talk to client
   int       _upto;   // id of first unseen message.
} Clerk;

ChatRoom* makeRoom();
void addWorker(ChatRoom* room,pthread_t w);
void addMessage(ChatRoom* room,Msg m);

void* handleNewConnection(Clerk* clerk);

int main(int argc,char* argv[]) 
{
   // Create a socket
   int sid = socket(PF_INET,SOCK_STREAM,0);
   // setup our address -- will listen on 8080 --
   struct sockaddr_in addr;
   addr.sin_len    = sizeof(addr);
   addr.sin_family = AF_INET;
   addr.sin_port   = htons(8090);
   addr.sin_addr.s_addr = INADDR_ANY;
   //pairs the newly created socket with the requested address.
   int status = bind(sid,(struct sockaddr*)&addr,sizeof(addr));
   checkError(status);
   // listen on that socket for "Let's talk" message. No more than 10 pending at once
   status = listen(sid,10);
   checkError(status);
   ChatRoom* room = makeRoom();      
   while(1) {
      struct sockaddr_in client;
      socklen_t clientSize;
      int chatSocket = accept(sid,(struct sockaddr*)&client,&clientSize);
      checkError(chatSocket);
      printf("We accepted a socket: %d\n",chatSocket);
      pthread_t wid;
      Clerk* clerk = (Clerk*)malloc(sizeof(Clerk));
      clerk->_room  = room;
      clerk->_fd    = chatSocket;
      clerk->_upto  = 0;
      pthread_create(&wid,NULL,(void*(*)(void*))handleNewConnection,clerk);
   }
   return 0;
}

ChatRoom* makeRoom()
{
   ChatRoom* room = (ChatRoom*)malloc(sizeof(ChatRoom));   
   room->_mxw = 4;
   room->_nbw = 0;
   room->_workers = (pthread_t*)malloc(sizeof(pthread_t)*room->_mxw);
   room->_mxl = 4;
   room->_nbl = 0;
   room->_log = (Msg*)malloc(sizeof(Msg)*room->_mxl);
   return room;
}

void addWorker(ChatRoom* room,pthread_t w)
{
   if (room->_nbw == room->_mxw) {
      room->_workers = realloc(room->_workers,sizeof(pthread_t)* room->_mxw * 2);
      room->_mxw *= 2;
   }
   room->_workers[room->_nbw++] = w;
}

void addMessage(ChatRoom* room,Msg m)
{
   if (room->_mxl == room->_nbl) {
      room->_log = (Msg*)realloc(room->_log,sizeof(Msg) * room->_mxl * 2);
      room->_mxl *= 2;
   }
   room->_log[room->_nbl++] = strdup(m); // make a copy of the message
}

/*
 * Send to the client (fd) all the messages between clerk->_upto and room->_nbl
 * to the client so that he has seen all messages so far. 
 */
void updateClient(Clerk* clerk) 
{
   Payload p;
   p.code = htonl(PL_SZ);
   p.nb   = htonl(clerk->_room->_nbl - clerk->_upto);
   int status = send(clerk->_fd,&p,sizeof(Payload),0);
   int from = clerk->_upto;
   int to   = clerk->_room->_nbl;
   printf("Sending %d - %d\n",from,to);
   int k;
   for(k = from ; k < to ; k++) {
      p.code = htonl(PL_MSG);
      strncpy(p.arg,clerk->_room->_log[k],255);
      status = send(clerk->_fd,&p,sizeof(Payload),0);
      checkError(status);
   }
   clerk->_upto = to;
}

void* handleNewConnection(Clerk* clerk)
{
   int chatSocket = clerk->_fd;
   int done = 0;
   addWorker(clerk->_room,pthread_self());
   do {
      Command c;
      int status = recv(chatSocket,&c,sizeof(Command),0);checkError(status);
      c.code = ntohl(c.code);
      switch(c.code){
         case CC_SEND: {
            printf("Message received [%s]\n",c.arg);
            addMessage(clerk->_room,c.arg);
         }break;
         case CC_GET: { // send the named file back to client			
            printf("get request came in\n");
            updateClient(clerk);
         }break; 
         case CC_EXIT:
            done = 1;
            break;
      }
   } while (!done);
   close(chatSocket);
   return 0;
}
