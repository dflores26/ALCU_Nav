/*---------------------------------------------------------------------------*/
/*                                                                           */
/* WARN: Please don't modify this default file!!!                            */
/*                                                                           */
/*---------------------------------------------------------------------------*/
#include <tinyara/config.h>
#include <stdio.h>
#include <unistd.h>


#ifndef APP_PRIORITY
#define APP_PRIORITY 100
#endif

#ifndef APP_STACKSIZE
#define APP_STACKSIZE 2048
#endif

extern int main(int argc, char *argv[]);

int _main(int argc, char *argv[])
{
	int pid;

	/*
	 * Create Task For async job
	 */
	pid = task_create("artik-sdk-examples", APP_PRIORITY, APP_STACKSIZE, main, argv);
	if (pid < 0) {
		/*
		 * Error : Can't Create task
		 */
		printf("artik-sdk-examples is not started, err = %d\n", pid);
	}

	return 0;
}

