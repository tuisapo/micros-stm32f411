#include "stm32f4xx.h"


void t(void) {
	for (int i=0; i != 5000; i++);  // espera ~100ms
}

int main(void)
{
  RCC->AHB1ENR=0x00000087;  // habilita o clock de todas as GPIOs
  GPIOA->MODER=0x28000000;  // inicializa o modo debugger para a interface do ARM
  GPIOB->MODER=0x55000454;  // configura os pinos B1, B2, B3, B5, B12, B13, B14 e B15 com a função de saída
  GPIOC->MODER=0x00000000;  // configura os pinos C como entrada

  int p1, p2, p3, total;

  while (1)
  {
	  GPIOB->ODR=0x00000000;  // reset;

	  // testagem das entradas

	  if((GPIOC->IDR&=0x1)==0x1){
		p1 = 1;
	  } else p1 = 0;

	  if((GPIOC->IDR&=0x2)==0x2){
		p2 = 1;
	  } else p2 = 0;

	  if((GPIOC->IDR&=0x4)==0x4){
		p3 = 1;
	  } else p3 = 0;

	  total = p1*1 + p2*2 + p3*4;

	  switch(8-total){
	  case 1:
		  GPIOB->ODR|=0x00004000;  // liga o pino 14;
	  case 2:
		  GPIOB->ODR|=0x00002000;  // liga o pino 13;
	  case 3:
		  GPIOB->ODR|=0x00001000;  // liga o pino 12;
	  case 4:
		  GPIOB->ODR|=0x00000020;  // liga o pino 5;
	  case 5:
		  GPIOB->ODR|=0x00000008;  // liga o pino 3;
	  case 6:
		  GPIOB->ODR|=0x00000004;  // liga o pino 2;
	  case 7:
		  GPIOB->ODR|=0x00000002;  // liga o pino 1;
	  }

	  t();

  }
}
