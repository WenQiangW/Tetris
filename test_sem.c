#include"comm.h"
#include<stdlib.h>
int main()
{
	int semid = create_sems(1);
	init_sem(semid,0);
	pid_t id = fork();
	if(id < 0)
	{
		perror("fork");
		return -1;
	}
	else if(id == 0)
	{
		while(1)
		{
			int child_id = get_sem();
			P(child_id);
			printf("A");
			usleep(12345);
			fflush(stdout);
			printf("A");
			usleep(35412);
			fflush(stdout);
			V(child_id);
		}
		exit(1);
	}
	else
	{
		while(1)
		{
			P(semid);
			printf("B");
			usleep(32345);
			fflush(stdout);
			printf("B");
			usleep(28712);
			fflush(stdout);
			V(semid);
		}
		wait(NULL);
		destory_sem(semid);
	}
	return 0;
}
