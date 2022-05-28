#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<arpa/inet.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<netdb.h>


int
main (int ac, char **av)
{
  struct sockaddr_in sad, cad;
  int cid, i, j, l, n;
  char sip_addr[32], cip_addr[32], msg[32], t;

  if (ac == 1)
    {
      strcpy (sip_addr, "127.0.0.1");
      strcpy (cip_addr, "127.0.0.1");
    }
  else
    {
      strcpy (sip_addr, av[1]);
      strcpy (cip_addr, av[2]);
    }
  cid = socket (AF_INET, SOCK_DGRAM, 0);
  // Setting up client address
  cad.sin_family = AF_INET;
  cad.sin_addr.s_addr = inet_addr (cip_addr);
  cad.sin_port = htons(0);
  bind (cid, (struct sockaddr *) &cad, sizeof (cad));
  // Setting up server address
  sad.sin_family = AF_INET;
  sad.sin_addr.s_addr = inet_addr (sip_addr);
  sad.sin_port = htons(1234);
  l = sizeof (sad);
  while (1)
    {
      fprintf (stdout, "Enter message to send: ");
      fgets (msg,sizeof msg,stdin);
      sendto (cid, (void *) msg, strlen (msg) + 1, 0,
	      (struct sockaddr *) &sad, sizeof (sad));
      if (!strcmp (msg, "EXIT"))
	break;
      recvfrom (cid, (void *) msg, sizeof (msg), 0, (struct sockaddr *) &sad,
		&l);
      fprintf (stdout, "Received message: %s\n", msg);
    }
  close (cid);
  return 0;
}

