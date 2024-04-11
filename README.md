# stm32-minimal
A minimal firmware build for the STM32 Nucleo F446RE development board

This project was created by learning from [cpq/bare-metal-programming-guide](https://github.com/cpq/bare-metal-programming-guide)

In this project, I use the ideas learned from [cpq/bare-metal-programming-guide](https://github.com/cpq/bare-metal-programming-guide)
to create a minimal bootable firmware for a slightly different STM32 microcontroller.

## Troubleshooting

### I was able to flash the Nucleo board once but now it isn't recognized through st-link.

The SWD pins may have been messed up in the main program. If this is the case, try booting the board in embedded
bootloader mode by connecting the BOOT0 pin high (3.3V) and reconnecting the board. With the board connected in
embedded bootloader mode try running `st-info --probe` to see if the device is now recognized.
