#ifndef __COMMAND_H
#define __COMMAND_H

#define CC_SEND	0
#define CC_GET	1
#define CC_EXIT 2
#define CC_LISTEN 3

#define PL_SZ  0
#define PL_MSG 1

typedef struct CommandTag {
   int  code; 
   char arg[256];
} Command;

typedef struct Payload {
   int code;
   union {
      char arg[256];
      int nb;
   };
} Payload;

#endif
