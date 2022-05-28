#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<netdb.h>
#include<math.h>
int input[32];
int code[32];

int ham_calc(int pos,int c_l){
	int count=0,i,j;
	i=pos-1;
	while(i<c_l){
		for(j=i;j<i+pos;j++){
			if(code[j]==1){
				count++;
			}
		}
		i=i+2*pos;
	}
	if(count%2==0)
		return 0;
	else
		return 1;
}
double poww(int b,int ex){
	double res=1.0;
	while(ex!=0){
	res*=b;
	--ex;
	}
	return res;
}
	

char* solve(char inp[],int n){
	int pc;
	for(pc=0;pc<n;pc++)
	{
		input[pc]=inp[pc]-'0';
	}
	int i,p_n=0,c_l,j,k;
	i=0;
	while(n>(int)poww(2,i)-(i+1)){
		p_n++;
		i++;
	}
	c_l=p_n+n;
	j=k=0;
	for(i=0;i<c_l;i++){
		if(i==((int)poww(2,k)-1)){
			code[i]=0;
			k++;
		}
		else{
			code[i]=input[j];
			j++;
		}
	}
	for(i=0;i<p_n;i++){
		int pos=(int)poww(2,i);
		int val=ham_calc(pos,c_l);
		code[pos-1]=val;
	}
	char* mmm=(char*)malloc(sizeof(char)*32);
	for(i=0;i<c_l;i++){
		mmm[i]=code[i]+48;
	}
	return mmm;
}
	
int main (int ac, char **av)
{
  int i, j, l, n, sid;
  struct sockaddr_in sad, cad;
	char *mmm;
  char sip_addr[32], msg[32], t;

  if (ac == 1)
    strcpy (sip_addr, "127.0.0.1");
  else
    strcpy (sip_addr, av[1]);
  sid = socket (AF_INET, SOCK_DGRAM, 0);
  sad.sin_family = AF_INET;
  sad.sin_addr.s_addr = inet_addr (sip_addr);
  sad.sin_port = htons(1234);
  bind (sid, (struct sockaddr *) &sad, sizeof (sad));
  l = sizeof (cad);
  while (1)
    {
      recvfrom (sid, (void *) msg, sizeof (msg), 0, (struct sockaddr *) &cad,
		&l);
      if (!strcmp (msg, "EXIT"))
	break;
      n = strlen (msg);
	mmm=solve(msg,n);
      // Reversing and resending the message
     /* for (i = 0, j = n - 1; i < j;
	   t = msg[i], msg[i] = msg[j], msg[j] = t, i++, j--);*/
      sendto (sid, (void *) mmm, strlen (mmm) , 0,
	      (struct sockaddr *) &cad, sizeof (cad));
    }
  return 0;
}

