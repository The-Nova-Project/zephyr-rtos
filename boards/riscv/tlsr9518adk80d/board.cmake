# SPDX-License-Identifier: Apache-2.0

board_runner_args(spi_burn --addr 0x0)
include(${ZEPHYR_BASE}/boards/common/spi_burn.board.cmake)
