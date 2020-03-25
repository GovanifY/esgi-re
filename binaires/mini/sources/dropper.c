#include <signal.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/un.h>
#include <unistd.h>

#define MYPORT 443
#define BACKLOG 1

int daily = 1;
FILE *fp = NULL;
FILE *fpc = NULL;

void destroy(int sig)
{
  if (fp != NULL && fpc == NULL)
  {
    if (daily > 1)
      fprintf(fp, "=== TODAY: %d ===\n",daily - 1);

    fflush(fp);
  }

  printf("\n");
  exit(1);
}

int main (int argc, char *argv[])
{
  signal(SIGINT, destroy);

  int port = MYPORT;
  int mday = 0;

  if (argc > 1)
  {
    port = strtol(argv[1], NULL, 10);
  }
  if (argc > 2)
  {
    fp = fopen(argv[2], "a+");
  }
  if (argc > 3)
  {
    fpc = fopen(argv[3], "r");
  }

  if (fpc != NULL)
  {
    char buffer[8];
    if (fgets(buffer, 8, fpc) != NULL)
    {
      daily = strtol(buffer, NULL, 10);
    }
    if (fgets(buffer, 8, fpc) != NULL)
    {
      mday = strtol(buffer, NULL, 10);
    }
    fclose(fpc);
  }

  if (argc > 3)
  {
    fpc = fopen(argv[3], "w");
  }

  int server_sockfd, client_sockfd, client_len;
  struct sockaddr_in addr_s, addr_c;

  server_sockfd = socket (AF_INET, SOCK_STREAM, 0);
  addr_s.sin_family = AF_INET;
  addr_s.sin_addr.s_addr = INADDR_ANY;
  addr_s.sin_port = htons (port);
  bzero (&(addr_s.sin_zero), 8);

  bind(server_sockfd, (struct sockaddr *) &addr_s, sizeof (addr_s));
  listen (server_sockfd, BACKLOG);

  printf("dropped connections on port %d:\n", port);
  fflush(stdout);
  while (daily)
    {
      time_t now;
      time(&now);
      struct tm * ti;
      ti = localtime(&now);

      if (mday == 0)
      {
        if (fp != NULL)
        {
          fprintf(fp, "=== PORT: %d ===\n", port);
          fflush(fp);
        }
        printf("\r%02d.%02d.%04d - %d", ti->tm_mday, ti->tm_mon + 1, ti->tm_year + 1900, 0);
        fflush(stdout);

        mday = ti->tm_mday;
      }

      client_len = sizeof (struct sockaddr);
      client_sockfd = accept (server_sockfd, (struct sockaddr *) &addr_c, &client_len);

      if (mday != ti->tm_mday)
      {
        printf("\n");
        if (fp != NULL)
        {
          fprintf(fp, "=== TODAY: %d ===\n",daily - 1);
          fflush(fp);
        }
        daily = 1;
        mday = ti->tm_mday;
      }

      if (fp != NULL)
      {
        fprintf(fp, "%02d.%02d.%04d %02d:%02d:%02d [%08d] - %s\n", ti->tm_mday, ti->tm_mon + 1, ti->tm_year + 1900, ti->tm_hour, ti->tm_min, ti->tm_sec, daily, inet_ntoa(addr_c.sin_addr));
        fflush(fp);
      }

      close (client_sockfd);

      printf("\r%02d.%02d.%04d - %d", ti->tm_mday, ti->tm_mon + 1, ti->tm_year + 1900, daily);
      fflush(stdout);

      daily++;

      if (fpc != NULL)
      {
        fprintf(fpc,"%d\n%d\n", daily, mday);
        fflush(fpc);
        fseek(fpc, 0, SEEK_SET);
      }
    }
  close(server_sockfd);

  if (fp)
  {
    fclose(fp);
  }

  if (fpc)
  {
    fclose(fpc);
  }
  return 0;
}
