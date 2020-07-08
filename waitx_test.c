#include "types.h"
#include "stat.h"
#include "user.h"

int main(void)
{
	int rtime = 0;
	int wtime = 0;
	int rc = fork();  

	if (rc < 0) {
        exit();
    } else if (rc == 0) {
	    for (int i = 0; i < 600; i++)
	    {
	      printf(1,"%s\n"," (o_o) " );
	    }
	    exit();
    }
    int id =waitx(&wtime,&rtime);
	printf(1,"pid:%d rtime:%d wtime:%d\n",id,rtime,wtime);
	exit();
	return 0;
}
