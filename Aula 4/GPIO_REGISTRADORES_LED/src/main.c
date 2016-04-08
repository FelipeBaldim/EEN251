/**
 * IMT - Rafael Corsi
 * 
 * PIO - 07
 *  Configura o PIO do SAM4S (Banco A, pino 19) para operar em
 *  modo de output. Esse pino está conectado a um LED, que em 
 *  lógica alta apaga e lógica baixa acende.
*/

#include <asf.h>

#include "Driver/pmc_maua.h"

#include "Driver/pio_maua.h"

/*
 * Prototypes
 */

/** 
 * Definição dos pinos
 * Pinos do uC referente aos LEDS.
 *
 * O número referente ao pino (PIOAxx), refere-se ao
 * bit que deve ser configurado no registrador para alterar
 * o estado desse bit específico.
 *
 * exe : O pino PIOA_19 é configurado nos registradores pelo bit
 * 19. O registrador PIO_SODR configura se os pinos serão nível alto.
 * Nesse caso o bit 19 desse registrador é referente ao pino PIOA_19
 *
 * ----------------------------------
 * | BIT 19  | BIT 18  | ... |BIT 0 |
 * ----------------------------------
 * | PIOA_19 | PIOA_18 | ... |PIOA_0|
 * ----------------------------------
 */
#define PIN_LED_BLUE 19
#define PIN_LED_GREEN 20
#define PIN_LED_RED 20

/**
 * Main function
 * 1. configura o clock do sistema
 * 2. desabilita wathdog
 * 3. ativa o clock para o PIOA
 * 4. ativa o controle do pino ao PIO
 * 5. desabilita a proteção contra gravações do registradores
 * 6. ativa a o pino como modo output
 * 7. coloca o HIGH no pino
 */

int main (void)
{

	/**
	* Inicializando o clock do uP
	*/
	sysclk_init();
	
	/** 
	*  Desabilitando o WathDog do uP
	*/
	WDT->WDT_MR = WDT_MR_WDDIS;
		
	// 29.17.4 PMC Peripheral Clock Enable Register 0
	// 1: Enables the corresponding peripheral clock.
	// ID_PIOA = 11 - TAB 11-1
	_pmc_enable_clock_periferico(ID_PIOA);
	_pmc_enable_clock_periferico(ID_PIOB);
	_pmc_enable_clock_periferico(ID_PIOC);
	
	 //31.6.1 PIO Enable Register
	// 1: Enables the PIO to control the corresponding pin (disables peripheral control of the pin).	
	PIOA->PIO_PER |= (1 << PIN_LED_BLUE )| (1 << PIN_LED_GREEN);
	PIOB->PIO_PER |= (1 << 3);

	// 31.6.46 PIO Write Protection Mode Register
	// 0: Disables the write protection if WPKEY corresponds to 0x50494F (PIO in ASCII).
	PIOA->PIO_WPMR = 0 ;
	PIOC->PIO_WPMR = 0;
	
	// 31.6.4 PIO Output Enable Register
	// value =
	//	 	1 : Enables the output on the I/O line.
	//	 	0 : do nothing
	PIOA->PIO_OER |=  (1 << PIN_LED_BLUE ) |  (1 << PIN_LED_GREEN ) ;
	PIOC->PIO_OER |=  (1 << PIN_LED_RED );
	

	// 31.6.10 PIO Set Output Data Register
	// value = 
	// 		1 : Sets the data to be driven on the I/O line.
	// 		0 : do nothing
	
	_pio_pull_up(PIOB,(1 << 3),1);
	
	
	
	PIOB->PIO_SCDR |= 50;
	//setando o divisor de clock por 100
	
	
	_pio_set_input(PIOB,(1 << 3),PIO_DEBOUNCE  | PIO_PULLUP);
	
	
	

	/**
	*	Loop infinito
	*/
		while(1)
		{

            /*
             * Utilize a função delay_ms para fazer o led piscar na frequência
             * escolhida por você.
             */
			
			
			if (((PIOB->PIO_PDSR >> 3) & 1) == 0)
			{
			delay_ms(50);
			
			_pio_set(PIOC,  (1 << PIN_LED_RED ));
			_pio_set(PIOA,  (1 << PIN_LED_BLUE ) | (1 << PIN_LED_GREEN ));
		
            delay_ms(50);
			
			_pio_clear(PIOA,  (1 << PIN_LED_BLUE ));
			_pio_clear(PIOC,  (1 << PIN_LED_RED ));
			_pio_set(PIOA,  (1 << PIN_LED_GREEN ));
					
			
			delay_ms(50);
			
			_pio_clear(PIOC,  (1 << PIN_LED_RED ));
			_pio_clear(PIOA,  (1 << PIN_LED_GREEN ));
			_pio_set(PIOA,  (1 << PIN_LED_BLUE ));
					
			delay_ms(50);
			
			_pio_set(PIOA,  (1 << PIN_LED_GREEN ));
			}
			
			
			
			
			
			
	}
}



