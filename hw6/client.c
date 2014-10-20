#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <errno.h>

#include "command.h"
void checkError(int status,int line)
{
    if (status < 0) {
        printf("socket error(%d)-%d: [%s]\n",getpid(),line,strerror(errno));
        exit(-1);
    }
}

void doLSCommand(int sid);
void doSIZECommand(int sid);
void doLLSCommand(int sid);
void doLSIZECommand(int sid);
void doExitCommand(int sid);
void doMGETCommand(int sid);
void doMPUTCommand(int sid);
void doGETCommand(int sid);
void doPUTCommand(int sid); 
void doOPENCommand(); 
void doCLOSECommand(int sid); 


int main(int argc,char* argv[]) 
{
    int port = 8080;
    if(argc > 1){
        int p_port = atoi(argv[1]);
        if(p_port > 0){
            port = p_port;
        }else{
            printf("You must enter a valid port number!\n");
            abort();
        }
    }
    // Create a socket
    int sid = socket(PF_INET,SOCK_STREAM,0);
    struct sockaddr_in srv;
    struct hostent *server = gethostbyname("localhost");
    //   srv.sin_len    = sizeof(srv);
    srv.sin_family = AF_INET;
    srv.sin_port   = htons(port);
    memcpy(&srv.sin_addr.s_addr,server->h_addr,server->h_length);
    int status = connect(sid,(struct sockaddr*)&srv,sizeof(srv));
    checkError(status,__LINE__);
    int done = 0;
    do {
        char opcode[32];
        scanf("%s",opcode);
        if (strncmp(opcode,"lsize",5) == 0) {
            doLSIZECommand(sid);
        } else if (strncmp(opcode,"size",4) == 0) {
            doSIZECommand(sid);
        } else if (strncmp(opcode,"lls",3) == 0) {
            doLLSCommand(sid);
        } else if (strncmp(opcode,"ls",5) == 0) {
            doLSCommand(sid);
        } else if (strncmp(opcode,"mget",4) == 0) {
            doMGETCommand(sid);
        } else if (strncmp(opcode,"mput",4) == 0) {
            doMPUTCommand(sid);
        } else if (strncmp(opcode,"get",3)==0) {
            doGETCommand(sid);
        } else if (strncmp(opcode,"put",3)==0) {
            doPUTCommand(sid);
        } else if (strncmp(opcode,"open",4)==0) {
            doOPENCommand();
        } else if (strncmp(opcode,"close",4)==0) {
            doCLOSECommand(sid);
        } else if (strncmp(opcode,"exit",4) == 0) {
            doExitCommand(sid);
            done = 1;
        }
    } while(!done);

    return 0;
}

void doOPENCommand()
{
    int port = 8080;
    // Create a socket
    int sid = socket(PF_INET,SOCK_STREAM,0);
    struct sockaddr_in srv;
    struct hostent *server = gethostbyname("localhost");
    //   srv.sin_len    = sizeof(srv);
    srv.sin_family = AF_INET;
    srv.sin_port   = htons(port);
    memcpy(&srv.sin_addr.s_addr,server->h_addr,server->h_length);
    int status = connect(sid,(struct sockaddr*)&srv,sizeof(srv));
    checkError(status,__LINE__);
}

void doCLOSECommand(int sid)
{
    close(sid);
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

void doSIZECommand(int sid)
{
    Command c;
    Payload p;
    int status;
    c.code = htonl(CC_SIZE);
    printf("Give a filename:");
    char fName[256];
    scanf("%s",fName);
    strncpy(c.arg,fName,255);
    c.arg[255] = 0;
    status = send(sid,&c,sizeof(c),0);checkError(status,__LINE__);
    status = recv(sid,&p,sizeof(p),0);checkError(status,__LINE__);
    p.code = ntohl(p.code);
    p.length = ntohl(p.length);
    int size;
    status = recv(sid,&size,sizeof(size),0);checkError(status,__LINE__);
    printf("Size: [%dB]\n",size);
}

void doLLSCommand(int sid)
{
    printf("Got: [\n%s]\n",makeFileList("."));
}

void doLSIZECommand(int sid)
{
    Command c;
    printf("Give a filename:");
    char fName[256];
    scanf("%s",fName);
    strncpy(c.arg,fName,255);
    c.arg[255] = 0;
    printf("Size: [%dB]\n",getFileSize(c.arg));
}

void doMGETCommand(int sid)
{
    char params[256];
    fgets(params,255,stdin);
    char *file;
    file = strtok(params," \n\r");
    while( file != NULL ) 
    {
        Command c;
        Payload p;
        int status;
        c.code = htonl(CC_GET);
        strncpy(c.arg,file,255);
        c.arg[255] = 0;
        status = send(sid,&c,sizeof(c),0);checkError(status,__LINE__);
        status = recv(sid,&p,sizeof(p),0);checkError(status,__LINE__);
        p.code = ntohl(p.code);
        p.length = ntohl(p.length);
        receiveFileOverSocket(sid,c.arg,".download",p.length);
        file = strtok(NULL," \n\r");
    }
    printf("transfer(s) done\n");
} 

void doMPUTCommand(int sid)
{
    char params[256];
    fgets(params,255,stdin);
    char *file;
    file = strtok(params," \n\r");
    while( file != NULL ) 
    {
        Command c;
        Payload p;
        int status;
        c.code = htonl(CC_PUT);
        strncpy(c.arg,file,255);
        c.arg[255] = 0;
        status = send(sid,&c,sizeof(c),0);checkError(status,__LINE__);
        int fs = getFileSize(c.arg);
        p.code = ntohl(PL_FILE);
        p.length = ntohl(fs);
        status = send(sid,&p,sizeof(p),0);checkError(status,__LINE__);
        sendFileOverSocket(c.arg,sid);
        file = strtok(NULL," \n\r");
    }
    printf("transfer(s) done\n");
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
    Payload p;
    int status;
    c.code = htonl(CC_EXIT);
    c.arg[0] = 0;
    status = send(sid,&c,sizeof(c),0);checkError(status,__LINE__);
}
