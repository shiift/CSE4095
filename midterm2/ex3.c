#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main()
{
  int count;
  char string[] = "hello world!";
  int to_parent[2], to_child[2];
  char buf[256];
  pipe(to_parent);
  pipe(to_child);
  if (fork() == 0) {
    close(0);
    dup(to_child[0]);
    close(1);
    dup(to_parent[1]);
    close(to_parent[1]);
    close(to_child[0]);
    close(to_parent[0]);
    close(to_child[1]);

    while( (count=read(0, buf, sizeof(buf))) > 1 ) {
      write (1, buf, count-1);
    }
    exit(0);
  }
  close(1);
  dup(to_child[1]);
  close(0);
  dup(to_parent[0]);
  close(to_child[1]) ;
  close(to_parent[0]);
  close(to_child[0]);
  close(to_parent[1]);

  write(1, string, strlen(string));
  while( (count = read(0, buf, sizeof(buf))) > 1) {
    write(1, buf, count-1);
  }
  exit(0);
}

