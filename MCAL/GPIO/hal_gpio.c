/* 
 * File:   hal_gpio.c
 * Author: ahmed radwan
 *
 * Created on June 28, 2022, 4:24 AM
 */
#include "hal_gpio.h"

/*reference to the data direction control registers*/
volatile   uint8 *tris_registers[]={&TRISA,&TRISB,&TRISC,&TRISD,&TRISE};
/*reference to the data latch registers (Read&Write to data latch)*/
volatile uint8 *lat_registers[]={&LATA,&LATB,&LATC,&LATD,&LATE};
/*reference to the port status  registers*/
volatile uint8 *port_registers[]={&PORTA,&PORTB,&PORTC,&PORTD,&PORTE};

/**
 * @brief initialize the direction to specific pin (INPUT OR OUTPUT) @ref direction_t 
 * @param _pin_config pointer to the configuration @ref pin_config_t
 * @return Status of the function
 *         (E_OK) : the function done successfully
 *         (E_NOK): the function has issue to preform this action
 */
#if GPIO_PORT_PIN_CONFIGURATION == CONFIG_ENABLE
Std_returnType gpio_pin_direction_initialize  (const pin_config_t * _pin_config)
{
    Std_returnType ERRORSTATUS =E_OK;
    if ( NULL==_pin_config||_pin_config->pin> PORT_PIN_MAX_NUMBER -1)
    {
        ERRORSTATUS=E_NOK;
    }
    else
    {
    switch(_pin_config->direction)
    {
        case GPIO_DIRECTION_OUTPUT:
         CLEAR_BIT(*tris_registers[_pin_config->port],_pin_config->pin);
            break;
        case GPIO_DIRECTION_INPUT:
          SET_BIT(*tris_registers[_pin_config->port],_pin_config->pin);
            break;
        
        default:ERRORSTATUS=E_NOK;
            
    }
     }
    return ERRORSTATUS;
}
#endif

/**
 * @bref get the direction of specific pin (INPUT OR OUTPUT) @ref direction_t 
 * @param _pin_config pointer to the configuration @ref pin_config_t
 * @param direction_status pointer to the status of the specific pin
 * @return Status of the function
 *         (E_OK) : the function done successfully
 *         (E_NOK): the function has issue to preform this action
 */
#if GPIO_PORT_PIN_CONFIGURATION == CONFIG_ENABLE
Std_returnType gpio_pin_get_direction_status (const pin_config_t * _pin_config, direction_t *direction_status)
{
     Std_returnType ERRORSTATUS =E_OK;
     if ( NULL==_pin_config||NULL==direction_status||_pin_config->pin> PORT_PIN_MAX_NUMBER -1)
    {
        ERRORSTATUS=E_NOK;
    }
    else
    {
       *direction_status= READ_BIT(*tris_registers[_pin_config->port],_pin_config->pin);
         
    }
     return ERRORSTATUS;
    
}
#endif

/**
  * write logic(0/1) on gpio pin
  * @param _pin_config pointer to the configuration @ref pin_config_t
  * @param logic
 * @return Status of the function
 *         (E_OK) : the function done successfully
 *         (E_NOK): the function has issue to preform this action
  */
#if GPIO_PORT_PIN_CONFIGURATION == CONFIG_ENABLE
Std_returnType gpio_pin_write_logic  (const pin_config_t * _pin_config,logic_t logic)
{
      Std_returnType ERRORSTATUS =E_OK;
     if ( NULL==_pin_config||_pin_config->pin> PORT_PIN_MAX_NUMBER -1)
    {
        ERRORSTATUS=E_NOK;
    }
    else
    {
         switch(logic)
    {
        case GPIO_LOW:
         CLEAR_BIT(*lat_registers[_pin_config->port],_pin_config->pin);
            break;
        case GPIO_HIGH:
          SET_BIT(*lat_registers[_pin_config->port],_pin_config->pin);
            break;
        
        default:ERRORSTATUS=E_NOK;
     }   
         
    }
     return ERRORSTATUS;   
}
#endif

/**
 * 
 * @param _pin_config pointer to the configuration @ref pin_config_t
 * @param logic -> its var passed by refrance to get the logic value 
 * @return Status of the function
 *         (E_OK) : the function done successfully
 *         (E_NOK): the function has issue to preform this action
 */
#if GPIO_PORT_PIN_CONFIGURATION == CONFIG_ENABLE
Std_returnType gpio_pin_read_logic   (const pin_config_t * _pin_config,logic_t *logic)
{
      Std_returnType ERRORSTATUS =E_OK;
          if ( NULL==_pin_config||NULL==logic||_pin_config->pin> PORT_PIN_MAX_NUMBER -1)
    {
        ERRORSTATUS=E_NOK;
    }
    else
    {
         *logic= READ_BIT(*port_registers[_pin_config->port],_pin_config->pin);
    }
     return ERRORSTATUS;   
}
#endif

/**
 * 
 * @param _pin_config pointer to the configuration @ref pin_config_t
 * @return Status of the function
 *         (E_OK) : the function done successfully
 *         (E_NOK): the function has issue to preform this action
 */
#if GPIO_PORT_PIN_CONFIGURATION == CONFIG_ENABLE
Std_returnType gpio_pin_toggle_logic  (const pin_config_t * _pin_config)
{
     Std_returnType ERRORSTATUS =E_OK;
          if ( NULL==_pin_config)
    {
        ERRORSTATUS=E_NOK;
    }
    else
    {
      TOGGLE_BIT(*lat_registers[_pin_config->port],_pin_config->pin);
    }
     return ERRORSTATUS;    
}
#endif


#if GPIO_PORT_PIN_CONFIGURATION == CONFIG_ENABLE
/**
 * 
 * @param _pin_config pointer to the configuration @ref pin_config_t
 * @return Status of the function
 *         (E_OK) : the function done successfully
 *         (E_NOK): the function has issue to preform this action
 */
Std_returnType gpio_pin_initialize(const pin_config_t * _pin_config)
{
     Std_returnType ERRORSTATUS =E_OK;
          if ( NULL==_pin_config)
    {
        ERRORSTATUS=E_NOK;
    }
    else
    {
         ERRORSTATUS=gpio_pin_direction_initialize(_pin_config);
         ERRORSTATUS=gpio_pin_write_logic(_pin_config,_pin_config->logic);
        
    }
     return ERRORSTATUS;   
}
#endif

/******************************************port configurations*********************************************************/

/**
 * 
 * @param port
 * @param direction
 * @return Status of the function
 *         (E_OK) : the function done successfully
 *         (E_NOK): the function has issue to preform this action
 */
#if GPIO_PORT_CONFIGURATION == CONFIG_ENABLE
Std_returnType gpio_port_direction_initialize(port_index_t port , uint8 direction)
{
     Std_returnType ERRORSTATUS =E_OK;
     if ( PORT_MAX_NUMBER-1<port)
    {
        ERRORSTATUS=E_NOK;
    }
     else
     {
         *tris_registers[port]=direction;
     }
     return ERRORSTATUS;   
}
#endif
/**
 * 
 * @param port
 * @param direction_status
 * @return Status of the function
 *         (E_OK) : the function done successfully
 *         (E_NOK): the function has issue to preform this action
 */
#if GPIO_PORT_CONFIGURATION == CONFIG_ENABLE

Std_returnType gpio_port_get_direction_status (port_index_t port, uint8 *direction_status)
{
     Std_returnType ERRORSTATUS =E_OK;
          if ((PORT_MAX_NUMBER-1<port)||( NULL==direction_status))
    {
        ERRORSTATUS=E_NOK;
    }
    else
    {
       *direction_status=*tris_registers[port];
    }
     
     return ERRORSTATUS;
}
#endif

/**
 * 
 * @param port
 * @param logic
 * @return Status of the function
 *         (E_OK) : the function done successfully
 *         (E_NOK): the function has issue to preform this action
 */
#if GPIO_PORT_CONFIGURATION == CONFIG_ENABLE
Std_returnType gpio_port_write_logic (port_index_t port,uint8 logic)
{
       Std_returnType ERRORSTATUS =E_OK;
          if ((PORT_MAX_NUMBER-1<port))
         {
              ERRORSTATUS=E_NOK;
         }
          else
          {
              *lat_registers[port]=logic;
          }
     return ERRORSTATUS;  
}
#endif

/**
 * 
 * @param port
 * @param logic
 * @return Status of the function
 *         (E_OK) : the function done successfully
 *         (E_NOK): the function has issue to preform this action
 */
#if GPIO_PORT_CONFIGURATION == CONFIG_ENABLE
Std_returnType gpio_port_read_logic (port_index_t port,uint8 *logic)
{
     Std_returnType ERRORSTATUS =E_OK;
          if (( NULL==logic)||(PORT_MAX_NUMBER-1<port))
    {
        ERRORSTATUS=E_NOK;
    }
    else
    {
          *logic=*port_registers[port]; 
    }     
     return ERRORSTATUS;    
}
#endif

/**
 * 
 * @param port
 * @return Status of the function
 *         (E_OK) : the function done successfully
 *         (E_NOK): the function has issue to preform this action 
 */

#if GPIO_PORT_CONFIGURATION == CONFIG_ENABLE

Std_returnType gpio_port_toggle_logic (port_index_t port)
{
       Std_returnType ERRORSTATUS =E_OK;
          if (PORT_MAX_NUMBER-1<port)
    {
        ERRORSTATUS=E_NOK;
    }
    else
    {
          *lat_registers[port]^=PORTMASK; 
    }     
     return ERRORSTATUS;     
}
#endif
