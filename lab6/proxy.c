#include <stdio.h>
#include <string.h>
#include "csapp.h"

/* Recommended max cache and object sizes */
#define MAX_CACHE_SIZE 1049000
#define MAX_OBJECT_SIZE 102400
// define port range
#define MIN_PORT 4500
#define MAX_PORT 65000
/* You won't lose style points for including this long line in your code */
static const char *user_agent_hdr = "User-Agent: Mozilla/5.0 (X11; Linux x86_64; rv:10.0.3) Gecko/20120305 Firefox/10.0.3\r\n";

// method list
void client_accept(int *arg);

int main(int argc, char **argv)
{
    int port;
    int *connfd, listenfd;

    struct sockaddr c_addr;
    socklen_t c_len;
    pthread_t t_id;

    printf("%s", user_agent_hdr);
    // get port from argument
    port = atoi(argv[1]);
    // port must be selected any non-previleged listening port
    // greater than 4500 and less than 65000
    if( port <= MIN_PORT || port >= MAX_PORT)
    {
      printf("[ERROR] port number %d is out of range.\n", port);
      return;
    }
    // open listenfd
    // use Wrapper function in csapp
    listenfd = Open_listenfd(port);
    while(1){
      connfd = Malloc(sizeof(int));
      // int Accept(int s, struct sockaddr *addr, socklen_t *addrlen);
      *connfd = Accept(listenfd, (SA *) &c_addr, &c_len);
      // create thread
      // void Pthread_create(pthread_t *tidp, pthread_attr_t *attrp, void * (*routine)(void *), void *argp);
      Pthread_create(&t_id, NULL, (void *) client_accept,connfd);
    }
    Free(connfd);
    return 0;
}
void client_accept(int *arg){
  int fd = (int)(*arg);
  return;
}
