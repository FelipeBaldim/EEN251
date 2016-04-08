	/**
 * @file pio_maua.h
 * @author Grupo 6 Noturno
 * @date 31/3/2016
 * @brief Fun��es para configurar os PIOs do SAM4S
 */


/**
 * inclui o head do pio
 */

#include "pio_maua.h"

/**
 * \brief Configure one or more pin(s) of a PIO controller as outputs, with
 * the given default value. 
 * 
 * \param p_pio Pointer to a PIO instance.
 * \param ul_mask Bitmask indicating which pin(s) to configure.
 * \param ul_default_level Default level on the pin(s).
 * \param ul_pull_up_enable Indicates if the pin shall have its pull-up
 * activated.
 */
void _pio_set_output(	Pio *p_pio, const uint32_t ul_mask,	const uint32_t ul_default_level, const uint32_t ul_pull_up_enable)
{
	if( ((PIO_PULLUP) & (ul_attribute)) > 0 )
	p_pio->PIO_PUER = ul_mask;
	
	if( ((PIO_DEGLITCH) & (ul_attribute)) > 0 )
	{
		p_pio->PIO_IFER = ul_mask;
		p_pio->PIO_IFSCDR = ul_mask;
	}
	
	if( ((PIO_DEBOUNCE) & (ul_attribute)) > 0 )
	{
		p_pio->PIO_IFER = ul_mask;
		p_pio->PIO_IFSCER = ul_mask;
	}
	p_pio->PIO_PER = ul_mask;
	p_pio->PIO_OER = ul_mask;
	
}




/**
 * \brief Configure one or more pin(s) or a PIO controller as inputs.
 * Optionally, the corresponding internal pull-up(s) and glitch filter(s) can
 * be enabled.
 *
 * \param p_pio Pointer to a PIO instance.
 * \param ul_mask Bitmask indicating which pin(s) to configure as input(s).
 * \param ul_attribute PIO attribute(s).
 */
void _pio_set_input( 	Pio *p_pio, const uint32_t ul_mask,	const uint32_t ul_attribute)
{
	if( ((PIO_PULLUP) & (ul_attribute)) > 0 )
		p_pio->PIO_PUER = ul_mask;
	
	if( ((PIO_DEGLITCH) & (ul_attribute)) > 0 )
	{
		p_pio->PIO_IFER = ul_mask;
		p_pio->PIO_IFSCDR = ul_mask;
	}
	
	if( ((PIO_DEBOUNCE) & (ul_attribute)) > 0 )
	{
		p_pio->PIO_IFER = ul_mask;
		p_pio->PIO_IFSCER = ul_mask;
	}
	p_pio->PIO_PER = ul_mask;
	p_pio->PIO_ODR = ul_mask;
	
}

void _pio_set_div_debounce(	Pio *p_pio, const uint32_t ul_mask, int valor){
	
}
/**
 * \brief Configure PIO internal pull-up.
 *
 * \param p_pio Pointer to a PIO instance.
 * \param ul_mask Bitmask of one or more pin(s) to configure.
 * \param ul_pull_up_enable Indicates if the pin(s) internal pull-up shall be
 * configured.
 */
void _pio_pull_up(	Pio *p_pio, const uint32_t ul_mask,	const uint32_t ul_pull_up_enable)
{
	if (ul_pull_up_enable)
		p_pio->PIO_PUER = ul_mask ;
	else
		p_pio->PIO_PUDR = ul_mask ;
	
}
	


/**
 * \brief Configure PIO pin internal pull-down.
 *
 * \param p_pio Pointer to a PIO instance.
 * \param ul_mask Bitmask of one or more pin(s) to configure.
 * \param ul_pull_down_enable Indicates if the pin(s) internal pull-down shall
 * be configured.
 */
void _pio_pull_down( Pio *p_pio, const uint32_t ul_mask, const uint32_t ul_pull_down_enable)

{
	if(ul_pull_down_enable)
		p_pio->PIO_PPDER = ul_mask;
	else
		p_pio->PIO_PPDDR = ul_mask;
}

/**
 * \brief Set a high output level on all the PIOs defined in ul_mask.
 * This has no immediate effects on PIOs that are not output, but the PIO
 * controller will save the value if they are changed to outputs.
 *
 * \param p_pio Pointer to a PIO instance.
 * \param ul_mask Bitmask of one or more pin(s) to configure.
 */
void _pio_set(   Pio *p_pio, const uint32_t ul_mask)
{

	p_pio->PIO_SODR = ul_mask;	

}

/**
 * \brief Set a low output level on all the PIOs defined in ul_mask.
 * This has no immediate effects on PIOs that are not output, but the PIO
 * controller will save the value if they are changed to outputs.
 *
 * \param p_pio Pointer to a PIO instance.
 * \param ul_mask Bitmask of one or more pin(s) to configure.
 */
void _pio_clear( Pio *p_pio, const uint32_t ul_mask)
{

	p_pio->PIO_CODR = ul_mask;	

}


/**
 * \brief Return 1 if one or more PIOs of the given Pin are configured to
 * output a high level (even if they are not output).
 * To get the actual value of the pin, use PIO_Get() instead.
 *
 * \param p_pio Pointer to a PIO instance.
 * \param ul_mask Bitmask of one or more pin(s).
 *
 * \retval 1 At least one PIO is configured to output a high level.
 * \retval 0 All PIOs are configured to output a low level.
 */
uint32_t _pio_get_output_data_status(const Pio *p_pio, const uint32_t ul_mask);






