# Analog Devices Driver

Most of the code here within the analogdevicesinc folder is from the
https://github.com/analogdevicesinc/no-OS repository.
Exceptions are this README and the stm32 main.h,
which is WIP to include bits of ST's HAL.

It was retrieved on September 19, 2024 from the latest main branch commit
ba5a22b15efb694fc1b8c758c941f8d0606c2781.

It includes the driver for the ADIN1110 and ADIN2111 from the
`drivers/net/adin1110` folder of the upstream repository.
It also includes the platform-agnostic `no_os` headers and implementations
that the driver depends on,
as well as the stm32 platform implementation and its `no_os` dependencies.

## Platform Implementation

In order to support this driver,
a platform must implement the following 8 functions.

- From `no_os_spi.h`
  - `no_os_spi_init`
  - `no_os_spi_transfer`
  - `no_os_spi_remove`
- From `no_os_gpio.h`
  - `no_os_gpio_set_value`
  - `no_os_gpio_get_optional`
  - `no_os_gpio_direction_output`
  - `no_os_gpio_remove`
- From `no_os_delay.h`
  - `no_os_mdelay`

Analog Devices also provide common platform implementations of these functions
in the `drivers/platform` folder.
