#include <stddef.h>
#include <shell/tash.h>
#include <stdio.h>
#include "gpio.h"
#include "sensor_read.h"
#include "distance.h"

int run;
int flag = 0;

extern int sdk_main(int argc, char *argv[]);
extern int cloud_main(int argc, char *argv[]);
extern int gpio_main(int argc, char *argv[]);
extern int pwm_main(int argc, char *argv[]);
extern int adc_main(int argc, char *argv[]);
extern int http_main(int argc, char *argv[]);
extern int wifictl_main(int argc, char *argv[]);
extern int websocket_main(int argc, char *argv[]);
extern int see_main(int argc, char *argv[]);
extern int mqtt_main(int argc, char **argv);

static tash_cmdlist_t atk_cmds[] = {
    {"sdk", sdk_main, TASH_EXECMD_SYNC},
    {"gpio", gpio_main, TASH_EXECMD_SYNC},
    {"pwm", pwm_main, TASH_EXECMD_SYNC},
    {"adc", adc_main, TASH_EXECMD_SYNC},
    {"cloud", cloud_main, TASH_EXECMD_SYNC},
    {"http", http_main, TASH_EXECMD_SYNC},
    {"wifictl", wifictl_main, TASH_EXECMD_SYNC},
    {"websocket", websocket_main, TASH_EXECMD_SYNC},
    {"see", see_main, TASH_EXECMD_SYNC},
    {"mqtt", mqtt_main, TASH_EXECMD_SYNC},
    {NULL, NULL, 0}
};

int main(int argc, char *argv[])
{
#ifdef CONFIG_TASH
    /* add tash command */
		tash_cmdlist_install(atk_cmds);
		printf("Finished Tash Command Install\n");
		//tash_cmd_install("nav", u_sensor_loop, TASH_EXECMD_SYNC);

#endif
    //	u_sensor_loop();

//#ifdef CONFIG_TASH
//	tash_cmd_install("gps", gps_app_main, TASH_EXECMD_SYNC);
//#endif
//	gps_app_main(argc,argv);
//	return 0;



    return 0;
}

