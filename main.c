#include <stdbool.h>
#include <stdint.h>

struct gpio {
  volatile uint32_t MODER, OTYPER, OSPEEDR, PUPDR, IDR, ODR, BSRR, LCKR, AFR[2];
};

#define GPIO(bank) ((struct gpio *) (0x40020000 + 0x400 * (bank)))

struct rcc {
  volatile uint32_t CR, PLLCFGR, CFGR, CIR, AHB1RSTR, AHB2RSTR, AHB3RSTR,
      RESERVED0, APB1RSTR, APB2RSTR, RESERVED1[2], AHB1ENR, AHB2ENR, AHB3ENR,
      RESERVED2, APB1ENR, APB2ENR, RESERVED3[2], AHB1LPENR, AHB2LPENR,
      AHB3LPENR, RESERVED4, APB1LPENR, APB2LPENR, RESERVED5[2], BDCR, CSR,
      RESERVED6[2], SSCGR, PLLI2SCFGR;
};
#define RCC ((struct rcc *) 0x40023800)

static inline void spin(volatile uint32_t count) {
  while (count--) (void) 0;
}

int main(void) {
    struct gpio *gpioa = GPIO(0);

    //Enable the GPIO Clock
    RCC->AHB1ENR |= 1; 

    //Set the Correct Port for output
    gpioa->MODER &= ~(uint32_t)0x00000C00;
    gpioa->MODER |= 0x00000400;

    while(1)
    {
        //Switch the output pin on and off
        gpioa->BSRR = 0x00000020;
        spin(333333);
        gpioa->BSRR = 0x00200000;
        spin(333333);
    }
    return -1;

}

// Startup code
__attribute__((naked, noreturn)) void _reset(void) {
    // memset .bss to zero, and copy .data section to RAM region
    extern long _sbss, _ebss, _sdata, _edata, _sidata;
    for (long *dst = &_sbss; dst < &_ebss; dst++) *dst = 0;
    for (long *dst = &_sdata, *src = &_sidata; dst < &_edata;) *dst++ = *src++;

    main();             // Call main()
    for (;;) (void) 0;  // Infinite loop
}

extern void _estack(void);  // Defined in link.ld

// 16 standard and 97 STM32-specific handlers
__attribute__((section(".vectors"))) void (*const tab[16 + 97])(void) = {
    _estack, _reset
};
