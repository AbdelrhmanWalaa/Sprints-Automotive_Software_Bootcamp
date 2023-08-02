#ifndef REGISTERS_H_
#define REGISTERS_H_

#define GPIO_APB
#ifdef 	GPIO_APB
#define GPIO_OFFEST(x)	((x<4) ? ((0x40004000)+((x)*(0x1000))) : ((0x40024000)+ ((x-4)*(0x1000))))
#elif 	GPIO_AHB
#error "Not supported"
#else
#error "please select GPIO BUS"
#endif

//GPIO registers
#define GPIODATA(x)		(*((volatile unsigned long *)(GPIO_OFFEST(x)+ 0x3FC)))
#define GPIODIR(x)		(*((volatile unsigned long *)(GPIO_OFFEST(x)+ 0x400)))
#define GPIOIS(x)			(*((volatile unsigned long *)(GPIO_OFFEST(x)+ 0x404)))
#define GPIOIBE(x)		(*((volatile unsigned long *)(GPIO_OFFEST(x)+ 0x408)))
#define GPIOIEV(x)		(*((volatile unsigned long *)(GPIO_OFFEST(x)+ 0x40C)))
#define GPIOIM(x)			(*((volatile unsigned long *)(GPIO_OFFEST(x)+ 0x410)))
#define GPIORIS(x)		(*((volatile unsigned long *)(GPIO_OFFEST(x)+ 0x414)))
#define GPIOMIS(x)		(*((volatile unsigned long *)(GPIO_OFFEST(x)+ 0x418)))
#define GPIOICR(x)		(*((volatile unsigned long *)(GPIO_OFFEST(x)+ 0x41C)))
#define GPIOAFSEL(x)	(*((volatile unsigned long *)(GPIO_OFFEST(x)+ 0x420)))
#define GPIODR2R(x)		(*((volatile unsigned long *)(GPIO_OFFEST(x)+ 0x500)))
#define GPIODR4R(x)		(*((volatile unsigned long *)(GPIO_OFFEST(x)+ 0x504)))
#define GPIODR8R(x)		(*((volatile unsigned long *)(GPIO_OFFEST(x)+ 0x508)))
#define GPIOODR(x)		(*((volatile unsigned long *)(GPIO_OFFEST(x)+ 0x50C)))
#define GPIOPUR(x)		(*((volatile unsigned long *)(GPIO_OFFEST(x)+ 0x510)))
#define GPIOPDR(x)		(*((volatile unsigned long *)(GPIO_OFFEST(x)+ 0x514)))
#define GPIOSLR(x)		(*((volatile unsigned long *)(GPIO_OFFEST(x)+ 0x518)))
#define GPIODEN(x)		(*((volatile unsigned long *)(GPIO_OFFEST(x)+ 0x51C)))
#define GPIOLOCK(x)		(*((volatile unsigned long *)(GPIO_OFFEST(x)+ 0x520)))
#define GPIOCR(x)			(*((volatile unsigned long *)(GPIO_OFFEST(x)+ 0x524)))
#define GPIOAMSEL(x)	(*((volatile unsigned long *)(GPIO_OFFEST(x)+ 0x528)))
#define GPIOPCTL(x)		(*((volatile unsigned long *)(GPIO_OFFEST(x)+ 0x52C)))
#define RCGC2GPIO     (*((volatile unsigned long *)0x400FE108))
	
//systick registers
#define STCTRL				(*((volatile unsigned long *)0xE000E010))
#define STRELOAD			(*((volatile unsigned long *)0xE000E014))
#define STCURRENT     (*((volatile unsigned long *)0xE000E018))
//systick bit nameing
#define STCTRL_ENABLE			0
#define STCTRL_INTEN			1
#define STCTRL_CLK_SRC		2
#define STCTRL_COUNT			16


//GPT registers
#define GPT_OFFSET(x)         (x<8?((0x40030000)+((x)*0x1000)):((0x4004C000)+((x-8)*0x1000)))
#define GPTMCFG(x)            (*(volatile unsigned long*)(GPT_OFFSET(x)+(0x000)))
#define GPTMTAMR(x)           (*(volatile unsigned long*)(GPT_OFFSET(x)+(0x004)))
#define GPTMTBMR(x)           (*(volatile unsigned long*)(GPT_OFFSET(x)+(0x008)))
#define GPTMCTL(x)            (*(volatile unsigned long*)(GPT_OFFSET(x)+(0x00C)))
#define GPTMSYNC(x)           (*(volatile unsigned long*)(GPT_OFFSET(x)+(0x010)))
#define GPTMIMR(x)            (*(volatile unsigned long*)(GPT_OFFSET(x)+(0x018)))
#define GPTMRIS(x)            (*(volatile unsigned long*)(GPT_OFFSET(x)+(0x01C)))
#define GPTMMIS(x)            (*(volatile unsigned long*)(GPT_OFFSET(x)+(0x020)))
#define GPTMICR(x)            (*(volatile unsigned long*)(GPT_OFFSET(x)+(0x024)))
#define GPTMTAILR(x)          (*(volatile unsigned long*)(GPT_OFFSET(x)+(0x028)))
#define GPTMTBILR(x)          (*(volatile unsigned long*)(GPT_OFFSET(x)+(0x02C)))
#define GPTMTAMATCHR(x)       (*(volatile unsigned long*)(GPT_OFFSET(x)+(0x030)))
#define GPTMTBMATCHR(x)       (*(volatile unsigned long*)(GPT_OFFSET(x)+(0x034)))
#define GPTMTAPR(x)           (*(volatile unsigned long*)(GPT_OFFSET(x)+(0x038)))
#define GPTMTBPR(x)           (*(volatile unsigned long*)(GPT_OFFSET(x)+(0x03C)))
#define GPTMTAPMR(x)          (*(volatile unsigned long*)(GPT_OFFSET(x)+(0x040)))
#define GPTMTBPMR(x)          (*(volatile unsigned long*)(GPT_OFFSET(x)+(0x044)))	
#define GPTMTAR(x)            (*(volatile unsigned long*)(GPT_OFFSET(x)+(0x048)))
#define GPTMTBR(x)            (*(volatile unsigned long*)(GPT_OFFSET(x)+(0x04C)))		
#define GPTMTAV(x)            (*(volatile unsigned long*)(GPT_OFFSET(x)+(0x050)))
#define GPTMTBV(x)            (*(volatile unsigned long*)(GPT_OFFSET(x)+(0x054)))		
#define GPTMRTCPD(x)          (*(volatile unsigned long*)(GPT_OFFSET(x)+(0x058)))	
#define GPTMTAPS(x)           (*(volatile unsigned long*)(GPT_OFFSET(x)+(0x05C)))	
#define GPTMTBPS(x)           (*(volatile unsigned long*)(GPT_OFFSET(x)+(0x060)))	
#define GPTMTAPV(x)           (*(volatile unsigned long*)(GPT_OFFSET(x)+(0x064)))
#define GPTMTBPV(x)           (*(volatile unsigned long*)(GPT_OFFSET(x)+(0x068)))
#define GPTMPP(x)             (*(volatile unsigned long*)(GPT_OFFSET(x)+(0xFC0)))
#define RCGCTIMER_REG         (*(volatile uint32_t*)(0x400FE604))
#define RCGCWTIMER_REG        (*(volatile uint32_t*)(0x400FE65C))
//GPT bit nameing



#endif /* REGISTERS_H_ */

