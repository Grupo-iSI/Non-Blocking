#ifndef Non_Blocking_h
#define Non_Blocking_h 

#include <Arduino.h>

#if !defined(dtDEBOUNCE_THERESHOLD)
#define dtDEBOUNCE_THERESHOLD 20 /** el tiempo de rebote de un pulsador */
#endif
#if !defined(dtTIME_THERESHOLD)
#define dtTIME_THERESHOLD 1000 /** el timpo que se considera una nueva pulsacion */
#endif

typedef enum Input_type {
    PULL_UP,
    PULL_DOWN
} dtInput_t;

enum Delay  {
    VERY_SHORT_DELAY  = 10UL,
    MS50_DELAY  = 50UL,
    SHORT_DELAY = 100UL,
    SEC_DELAY = 1000UL,
    LONG_DELAY = 5000UL,
    VERY_LONG_DELAY = 10000UL
};

typedef void (*Callback_ulong_t)(unsigned long param);
typedef void (*Callback_bool_t)(boolean param);
typedef void (*Callback_uint_t)(int param);
typedef void (*Callback_t)();


/**
 * Para llamar a una función de manera repetitiva entre intervalos de timepo constantes.
 * \param ms Cantidad de microsegundos entre llamadas a la función.
 * \param callBackHandler Función asociada al evento repetitivo.
 * \returns 
 * \b true si ha llamado a la funcion porque se ha cumplido el tiempo de espera.  
*/
boolean Every(unsigned long ms, Callback_t callBackHandler);

/**
 * Utilidad para obtener el tiempo en milisegundos que un botón es pulsado, o una enrtada 
 * se mantiene en el mismo nivel lógico.
 * \param inputPin Pin a atender como entrada.
 * \param inputType Si la entrada usa PULL_UP o PULL_DOWN
 * \returns El tiempo que el pin de entrada se mantuvo en el mimso estado.
*/
unsigned long switchTime(uint8_t inputPin, dtInput_t inputType);

/**
 * Utilidad para obtener el tiempo en milisegundos que un botón es pulsado, o una enrtada 
 * se mantiene en el mismo nivel lógico.
 * \param inputPin Pin a atender como entrada.
 * \param inputType Si la entrada usa PULL_UP o PULL_DOWN.
 * \param timeThreshold El timepo que hay que esperar mintras la entrada no ha
 *  halla cambiado de estado antes de llamar a la función.
 * \param callBackHandler Función asociada al evento.
 * \returns El tiempo que el pin de entrada se mantuvo en el mimso estado.
*/
unsigned long switchTime(uint8_t inputPin, dtInput_t inputType, unsigned long timeThreshold, Callback_t callBackHandler);

/** 
 * Atención a una entrada con debounce
 * \param inputPin Pin a atender como entrada.
 * \param inputType Si la entrada usa PULL_UP o PULL_DOWN.
 * \returns \b true si la entrada se ha stabilizado y ya no existe rebote.
*/
boolean digitalReadDebounce(uint8_t inputPin, dtInput_t inputType);

/** 
 * Atención a una entrada con debounce
 * \param inputPin Pin a atender como entrada.
 * \param inputType Si la entrada usa PULL_UP o PULL_DOWN.
 * \param callBackHandler Función asociada al evento, se llama cuando la entrada se estabiliza.
 * \returns \b true si el entrada se ha estabilizado y ya no existe rebote.
*/
boolean digitalReadDebounce(uint8_t inputPin, dtInput_t inputType, Callback_t callBackHandler);

/** 
 * Atención especializada en botones con debounce
 * \param inputPin Pin a atender como entrada.
 * \param inputType Si la entrada usa PULL_UP o PULL_DOWN.
 * \returns \b true si el entrada se ha estabilizado y ya no existe rebote.
*/
boolean digitalReadBtn(uint8_t inputPin, dtInput_t inputType); 

/** 
 * Atención a una entrada con debounce
 * \param inputPin Pin a atender como entrada.
 * \param inputType Si la entrada usa PULL_UP o PULL_DOWN.
 * \param callBackHandler Función asociada al evento, se llama cuando la entrada se estabiliza.
 * \returns \b true si el entrada se ha estabilizado y ya no existe rebote depués de llamar al método especifeicado.
*/
boolean digitalReadBtn(uint8_t inputPin, dtInput_t inputType, Callback_t callBackHandler);

/**
 * Sobrecarga a la funión de delay() de arduino que permite llamar a un método 
 * dentro del delay.
 * \param inputPin Pin a atender como entrada.
 * \param inputType Si la entrada usa PULL_UP o PULL_DOWN
 * \returns void
*/
void delay(unsigned long ms, Callback_t callBackHandeler);

/** MCROS: */
#define overFlow(t)  ((millis()) < (t))  

#endif /* Non_Blocking_h */