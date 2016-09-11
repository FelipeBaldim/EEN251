/**
*	20-UART
* Prof. Rafael Corsi
*
*    (e.g., HyperTerminal on Microsoft Windows) with these settings:
*   - 115200 bauds
*   - 8 bits of data
*   - No parity
*   - 1 stop bit
*   - No flow control
*/

#include "asf.h"
#include <string.h>
#include "conf_board.h"
#include "conf_clock.h"

/************************************************************************/
/* Configurações                                                        */
/************************************************************************/

#define STRING_EOL    "\r"
#define STRING_VERSAO "-- "BOARD_NAME" --\r\n" \
"-- Compiled: "__DATE__" "__TIME__" --"STRING_EOL

#define CONF_UART_BAUDRATE 115200
#define CONF_UART          CONSOLE_UART

/**
* LEDs
*/
#define PIN_LED_BLUE			19
#define PIN_LED_GREEN_RED		20
#define PORT_LED_BLUE_GREEN		PIOA
#define ID_LED_BLUE_GREEN		ID_PIOA
#define PORT_LED_RED			PIOC
#define ID_LED_RED				ID_PIOC
#define MASK_LED_BLUE			(1u << PIN_LED_BLUE)
#define MASK_LED_GREEN_RED		(1u << PIN_LED_GREEN_RED)

uint8_t i = 0;
uint8_t str[32];
bool freq = false;

/************************************************************************/
/* Configura UART                                                       */
/************************************************************************/
void config_uart(void){
	
	/* configura pinos */
	gpio_configure_group(PINS_UART0_PIO, PINS_UART0, PINS_UART0_FLAGS);
	
	/* ativa clock */
	sysclk_enable_peripheral_clock(CONSOLE_UART_ID);
	
	/* Configuração UART */
	const usart_serial_options_t uart_serial_options = {
		.baudrate   = CONF_UART_BAUDRATE,
		.paritytype = UART_MR_PAR_NO,
		.stopbits   = 0
	};
	
	stdio_serial_init((Usart *)CONF_UART, &uart_serial_options);
}

/************************************************************************/
/* Display Menu                                                         */
/************************************************************************/
static void display_menu(void)
{
	puts(" 1 : exibe novamente esse menu \n\r"
	" 2 : Ativa o LED  \n\r"
	" 3 : Desliga o LED \n\r ");
}

void cria_buffer(uint8_t *str_){
	i = 0;
	uint8_t aux;
	while(1){
		if(freq)
		{
			usart_serial_getchar((Usart *)CONSOLE_UART, (aux));
			if(!(aux <30 || aux >39))
			{
				*(str_+i) = aux;
				i++;
				if( *(str_+i-1) == '\n' )
				puts(*(str_));
				break;
			}
		}
		else
		{
			usart_serial_getchar((Usart *)CONSOLE_UART, (str_+i));
			i++;
			if( *(str_+i-1) == '\n' )
			break;
		}

	}
}

void Verifica_Comando(uint8_t *str_)
{
	uint8_t aux[i-2];
	for(int j =0; j<=i-2;j++)
	{
		*(aux+j)=*(str_+j);
	}
	if(strcmp("BLON",aux)==0)
	{
		puts("Insira a frequência da viadagem do GUI:");
		freq = true;
		pio_clear(PORT_LED_BLUE_GREEN, MASK_LED_BLUE);
		puts("Led ON \n\r");
		cria_buffer(&str[0]);
	}
}

/************************************************************************/
/* cria buffer                                                          */
/************************************************************************/



/************************************************************************/
/* Main                                                                 */
/************************************************************************/
int main(void)
{
	uint8_t uc_key;
	
	/* Initialize the system */
	sysclk_init();
	board_init();

	/* Configure LED 1 */
	pmc_enable_periph_clk(ID_LED_BLUE_GREEN);
	pio_set_output(PORT_LED_BLUE_GREEN  , MASK_LED_BLUE	,1,0,0);
	pmc_enable_periph_clk(ID_LED_RED);
	pio_set_output(PORT_LED_RED  , MASK_LED_GREEN_RED	,1,0,0);

	/* Initialize debug console */
	config_uart();
	
	/* frase de boas vindas */
	puts(" ---------------------------- \n\r"
	" Bem vindo terraquio !		\n\r"
	" ---------------------------- \n\r");
	
	/* display main menu */
	display_menu();
	
	while (1) {
		
	cria_buffer(&str[0]);
	Verifica_Comando(str);
		//usart_serial_getchar((Usart *)CONSOLE_UART, &uc_key);
		//Recebe_Byte(uc_key);
		
		puts(str);
		switch (uc_key) {
			case '1':
			display_menu();
			break;
			case '2':
			pio_clear(PORT_LED_BLUE_GREEN, MASK_LED_BLUE);
			puts("Led ON \n\r");
			break;
			case '3' :
			pio_set(PORT_LED_BLUE_GREEN, MASK_LED_BLUE);
			puts("Led OFF \n\r");
			break;
			case '4':
			pio_clear(PORT_LED_BLUE_GREEN, MASK_LED_GREEN_RED);
			puts("Led ON \n\r");
			break;
			case '5' :
			pio_set(PORT_LED_BLUE_GREEN, MASK_LED_GREEN_RED);
			puts("Led OFF \n\r");
			break;
			case '6':
			pio_clear(PORT_LED_RED, MASK_LED_GREEN_RED);
			puts("Led ON \n\r");
			break;
			case '7' :
			pio_set(PORT_LED_RED, MASK_LED_GREEN_RED);
			puts("Led OFF \n\r");
			break;
			default:
			printf("Opcao nao definida: %d \n\r", uc_key);
		}
	}
}
