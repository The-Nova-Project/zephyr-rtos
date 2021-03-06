/*
 * Copyright (c) 2019 Linaro Ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr/drivers/gpio.h>
#include <zephyr/init.h>

static int rf_init(const struct device *dev)
{
	const struct gpio_dt_spec rf1 =
		GPIO_DT_SPEC_GET(DT_NODELABEL(rf_switch), rf1_gpios);
	const struct gpio_dt_spec rf2 =
		GPIO_DT_SPEC_GET(DT_NODELABEL(rf_switch), rf2_gpios);
	const struct gpio_dt_spec rf3 =
		GPIO_DT_SPEC_GET(DT_NODELABEL(rf_switch), rf3_gpios);

	ARG_UNUSED(dev);

	/* configure RFSW8001 GPIOs (110: RF1/RF2 coexistence mode) */
	if (!device_is_ready(rf1.port) ||
	    !device_is_ready(rf2.port) ||
	    !device_is_ready(rf3.port)) {
		return -ENODEV;
	}

	(void)gpio_pin_configure_dt(&rf1, GPIO_OUTPUT_INIT_HIGH);
	(void)gpio_pin_configure_dt(&rf2, GPIO_OUTPUT_INIT_HIGH);
	(void)gpio_pin_configure_dt(&rf3, GPIO_OUTPUT_INIT_LOW);

	return 0;
}

/* Need to be initialised after GPIO driver */
SYS_INIT(rf_init, POST_KERNEL, CONFIG_KERNEL_INIT_PRIORITY_DEVICE);
