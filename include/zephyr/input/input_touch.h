/*
 * Copyright (c) 2024 Antmicro <www.antmicro.com>
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#ifndef ZEPHYR_INCLUDE_INPUT_TOUCH_H_
#define ZEPHYR_INCLUDE_INPUT_TOUCH_H_

/**
 * @brief Touch Events API
 * @defgroup touch_events Touchscreen Event Report API
 * @since 3.7
 * @version 0.1.0
 * @ingroup io_interfaces
 * @{
 */

#include <zephyr/input/input.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Common touchscreen config.
 *
 * This structure **must** be placed first in the driver's config structure.
 *
 * @param screen_width Horizontal resolution of touchscreen
 * @param screen_height Vertical resolution of touchscreen
 * @param inverted_x  X axis is inverted
 * @param inverted_y Y axis is inverted
 * @param swapped_x_y X and Y axes are swapped
 *
 * see touchscreem-common.yaml for more details
 */
struct input_touchscreen_common_config {
	uint32_t screen_width;
	uint32_t screen_height;
	bool inverted_x;
	bool inverted_y;
	bool swapped_x_y;
};

/**
 * @brief Initialize common touchscreen config from devicetree
 *
 * @param node_id The devicetree node identifier.
 */
#define INPUT_TOUCH_DT_COMMON_CONFIG_INIT(node_id)			\
	{								\
		.screen_width = DT_PROP(node_id, screen_width),		\
		.screen_height = DT_PROP(node_id, screen_height),	\
		.inverted_x = DT_PROP(node_id, inverted_x),		\
		.inverted_y = DT_PROP(node_id, inverted_y),		\
		.swapped_x_y = DT_PROP(node_id, swapped_x_y)		\
	}

/**
 * @brief Initialize common touchscreen config from devicetree instance.
 *
 * @param inst Instance.
 */
#define INPUT_TOUCH_DT_INST_COMMON_CONFIG_INIT(inst) \
	INPUT_TOUCH_DT_COMMON_CONFIG_INIT(DT_DRV_INST(inst))

/**
 * @brief Validate the offset of the common config structure.
 *
 * @param config Name of the config structure.
 */
#define INPUT_TOUCH_STRUCT_CHECK(config) \
	BUILD_ASSERT(offsetof(config, common) == 0, \
		     "struct input_touchscreen_common_config must be placed first");

/**
 * @brief Common utility for reporting touchscreen position events.
 *
 * @param dev Touchscreen controller
 * @param x X coordinate as reported by the controller
 * @param y Y coordinate as reported by the controller
 * @param timeout Timeout for reporting the event
 */
void input_touchscreen_report_pos(const struct device *dev,
		uint32_t x, uint32_t y,
		k_timeout_t timeout);

#ifdef __cplusplus
}
#endif

/** @} */

#endif /* ZEPHYR_INCLUDE_INPUT_TOUCH_H_ */
