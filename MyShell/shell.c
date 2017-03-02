/*************************************************************************
	> File Name: shell.c
	> Author: WenQiang
	> Mail: wenqiangw1208@gmail.com
	> Created Time: Wed 22 Feb 2017 11:06:06 AM PST
 ************************************************************************/
#include<string.h>
#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<stdlib.h>
#include<pwd.h>
#include<ctype.h>
void GetLogName()
{
	struct passwd* pass;
	pass = getpwuid(getuid());
	printf("[%s@",pass->pw_name);
}
void GetHostName()
{
	char name[128];
	gethostname(name,sizeof(name)-1);
	printf("%s",name);
}
void GetDir()
{
	char pwd[128];
	getcwd(pwd,sizeof(pwd)-1);
	int len = strlen(pwd);
	char* p = pwd+len-1;
	while(*p != '/' && len--)
	{
		p--;
	}
	p++;
	printf(" %s]@",p);
}
int main()
{
	while(1){
	char cmd[128];
	//printf("[Name@local shell]#:");
	GetLogName();
	GetHostName();
	GetDir();
	fflush(stdout);
	ssize_t _s = read(0, cmd, sizeof(cmd)-1);//read form stdIn 0
	if(_s > 0)//read success, _s is read number
	{
		cmd[_s-1] = '\0'; //tail add \0
	}
	else
	{
		perror("read");
		return 1;
	}

	char* _argv[32]; // save cmd
	_argv[0] = cmd;
	char* start = cmd;// pointer is a falg
	int i =1;
	while(*start)
	{
		if(isspace(*start))
		{
			*start ='\0';
			start++;
			_argv[i] = start;
			i++;
			continue;
		}
		start++;
	}
	_argv[i] = NULL;
	//printf("%s\n",cmd);

	pid_t id =fork();
	if(id <0)
	{
		perror("fork failed\n");
	}else if(id == 0) //child -> run cmd
	{
		execvp(_argv[0],_argv);
		exit(1);
	}
	else //father
	{
		//wait(NULL);
		int status =0;
		pid_t ret = waitpid(id,&status,0);
		if(ret > 0 && WIFEXITED(status))
		{
			printf("exit code: %d\n",WEXITSTATUS(status));
		}
		else
		{
			perror("wait failed");
		}
	}
	}
	
	return 0;
}
