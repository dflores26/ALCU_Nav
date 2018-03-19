/*
 * interrupt_main.c
 *
 *  Created on: Mar 18, 2018
 *      Author: justin
 */

#include <stdio.h>
#include <string.h>
#include <shell/tash.h>
#include <artik_module.h>
#include <artik_gpio.h>

static int gpio_watch(int pin);

struct gpio_node
{
  artik_list node;
  artik_gpio_handle handle;
};

static artik_list *requested_node;

static void gpio_event(void *user_data, int value)
{
  unsigned int id = (unsigned int)user_data;

  fprintf(stdout, "GPIO id %u event: %d\n", id, value);
}

static int gpio_watch(int pin)
{
  artik_gpio_module *gpio = (artik_gpio_module *)artik_request_api_module("gpio");

  artik_gpio_config config;
  artik_gpio_handle handle;

  char name[16] = "";
  int ret = 0;

  memset(&config, 0, sizeof(config));
  snprintf(name, 16, "gpio%d", config.id);

  config.name = name;
  config.id = pin;
  config.dir = GPIO_IN;
  config.edge = GPIO_EDGE_BOTH; // Probably want on the rising edge
  config.initial_value = 0;

  ret = gpio->request(&handle, &config);
  if (ret != S_OK)
  {
    fprintf(stderr, "GPIO id %u already on watching or wrong GPIO id\n", config.id);
    goto exit;
  }

  struct gpio_node *node = (struct gpio_node *)artik_list_add(&requested_node, (ARTIK_LIST_HANDLE)config.id, sizeof(struct gpio_node));

  if (!node)
  {
    return E_NO_MEM;
  }

  node->handle = handle;

  ret = gpio->set_change_callback(handle, gpio_event, (void *)config.id);
  if (ret != S_OK)
  {
    fprintf(stdout, "Failed, could not set GPIO change callback (%d)\n", ret);

    goto exit;
  }

  fprintf(stdout, "GPIO id %u on watching\n", config.id);

exit:

  artik_release_api_module(gpio);

  return ret;
}

int main(void)
{
	gpio_watch(57);
	return 0;
}

