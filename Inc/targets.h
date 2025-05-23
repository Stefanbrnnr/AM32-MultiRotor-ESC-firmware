

#ifndef USE_MAKE

//GLOBAL
//#define USE_ADC_INPUT
//#define USE_ALKAS_DEBUG_LED

#define FILE_NAME		"BSTUDIO_2025_G071"
//Name, der im ESC-Tool angezeigt wird, wenn man mit dem ESC verbunden ist.
#define FIRMWARE_NAME  	        "BSTUDIO_V1.0_G071 "
//Totzeit (in Nanosekunden) zwischen dem Ausschalten der einen MOSFET-Seite und Einschalten der anderen, um Kurzschlüsse (“Shoot-through”) zu vermeiden. 
#define DEAD_TIME               60 
//Angabe, wie viel mV pro Ampere dein Stromsensor (Shunt + Verstärker) ausgibt. Diese Zahl dient zur Kalibrierung der Strommessung.
#define MILLIVOLT_PER_AMP       45
//Offset zum Kalibrieren des Stromsensors – muss empirisch bestimmt oder aus Datenblatt übernommen werden.
#define CURRENT_OFFSET          515
//Der Faktor deines Spannungsteilers, mit dem die Betriebsspannung (z. B. 12 V – 24 V) auf einen messbaren Bereich (z. B. <3.3 V) reduziert wird. Wird benutzt, um die Batteriespannung zu berechnen.
#define TARGET_VOLTAGE_DIVIDER  110

//Aktiviert serielle Telemetrie (über UART) mit Flight Controller
#define USE_SERIAL_TELEMETRY

#endif



//Setzt intern passende Einstellungen und Treiber für STM32G071.
#define    MCU_G071
//Gibt an, welcher Timer für das PWM-Steuersignal verwendet wird. Hier: TIM3, Channel 1.
#define    USE_TIMER_3_CHANNEL_1
//Pin, an dem das Steuersignal vom Flight Controller (PWM/DSHOT) empfangen wird.
#define    INPUT_PIN               LL_GPIO_PIN_4
#define    INPUT_PIN_PORT              GPIOB
// Input-Capture-Konfiguration:
//	•	TIM3, Channel 1 wird für PWM-Empfang verwendet
//	•	htim3 ist die Referenz für HAL/LL-Treiber
#define    IC_TIMER_CHANNEL         LL_TIM_CHANNEL_CH1
#define    IC_TIMER_REGISTER          TIM3
#define    IC_TIMER_POINTER           htim3
//DMA-Einstellungen für TIM3 Capture – für effizienten Datenfluss, ohne CPU-Last.
//Das ermöglicht präzise PWM- bzw. DSHOT-Analyse.
#define    INPUT_DMA_CHANNEL       LL_DMA_CHANNEL_1
#define    DMA_HANDLE_TYPE_DEF     hdma_tim3_ch1
#define    IC_DMA_IRQ_NAME         DMA1_Channel1_IRQn
// Motorphasenausgänge:
//Diese Pins steuern die Gate-Treiber für die MOSFETs jeder Motorphase (A, B, C). Sie müssen PWM-Ausgangsfähig sein (via Timer).

// PHASE A
#define PHASE_A_GPIO_LOW          LL_GPIO_PIN_1
#define PHASE_A_GPIO_PORT_LOW         GPIOB
#define PHASE_A_GPIO_HIGH          LL_GPIO_PIN_10
#define PHASE_A_GPIO_PORT_HIGH         GPIOA
// PHASE B
#define PHASE_B_GPIO_LOW          LL_GPIO_PIN_0
#define PHASE_B_GPIO_PORT_LOW         GPIOB
#define PHASE_B_GPIO_HIGH          LL_GPIO_PIN_9
#define PHASE_B_GPIO_PORT_HIGH         GPIOA
// PHASE C
#define PHASE_C_GPIO_LOW          LL_GPIO_PIN_7
#define PHASE_C_GPIO_PORT_LOW         GPIOA
#define PHASE_C_GPIO_HIGH          LL_GPIO_PIN_8
#define PHASE_C_GPIO_PORT_HIGH         GPIOA

//Komparator-Eingänge (für sensorloses BEMF)
//Diese Pins sind die Back-EMF-Komparator-Eingänge (für sensorlose Kommutierung).
//Sie messen das Moment, wenn eine Phase den Neutralpunkt kreuzt (Zero-Crossing).

#define PHASE_A_COMP  LL_COMP_INPUT_MINUS_IO1  // pb3
#define PHASE_B_COMP  LL_COMP_INPUT_MINUS_IO2  // pb7
#define PHASE_C_COMP  LL_COMP_INPUT_MINUS_IO3  // pa2
/*********** Spannungsmessung ***********/
/* Pin/ADC-Kanal für Batteriespannung (über Spannungsteiler).
Wird u. a. für Low Voltage Cutoff verwendet. */
	
#define VOLTAGE_ADC_PIN     LL_GPIO_PIN_1
#define VOLTAGE_ADC_CHANNEL LL_ADC_CHANNEL_1
//Strommessung:
// Pin/ADC-Kanal für Strommessung (über Shunt + Verstärker).
// Wird verwendet für Strombegrenzung, Logging, Telemetrie usw.
#define CURRENT_ADC_PIN     LL_GPIO_PIN_5
#define CURRENT_ADC_CHANNEL  LL_ADC_CHANNEL_5




#define CPU_FREQUENCY_MHZ   64
//Der STM32G071 läuft typischerweise mit 64 MHz.
	
/*********** EEPROM (Flash-Speicherbereich für Konfigurationsdaten) ***********/
#define EEPROM_START_ADD  (uint32_t)0x0800F800
//•64KB MCUs: letzter 2KB-Sektor beginnt bei 0x0800F800

/*********** Timer-Zuweisung für verschiedene Aufgaben ***********/
#define INTERVAL_TIMER     TIM2
// Für Zeitmessung, PWM-Decoding etc

#define TEN_KHZ_TIMER      TIM6 
// Wird für periodische Tasks benutzt

#define UTILITY_TIMER      TIM17
// Hilfstimer für diverse Aufgaben

#define COM_TIMER          TIM14
// Zur synchronen Kommutierung mit PWM


/*********** PWM Frequenz Konfiguration ***********/
#define TIM1_AUTORELOAD    2667
// Das ist der Wert des Auto-Reload-Registers (ARR) für TIM1, das den PWM-Takt bestimmt.


/*********** Flash Startadresse für Anwendung ***********/
#define APPLICATION_ADDRESS 0x08001000
// Das ist der Ort im Flash, wo die eigentliche ESC-Firmware startet.
// 0x08000000 ist normalerweise der Bootloader → Firmware wird bei 0x08001000 geladen. 


/*********** Komperator Konfiguration ***********/
#define MAIN_COMP	COMP2
// Der Komparator COMP2 wird verwendet, um BEMF-Zero-Crossings zu erkennen (bei sensorlosen ESCs).

#define EXTI_LINE   LL_EXTI_LINE_18
// EXTI_LINE_18 ist die zugehörige Interrupt-Leitung, wenn ein Komparator-Event erkannt wird.


/*********** BEMF Zähler ***********/
#define TARGET_MIN_BEMF_COUNTS 8
// Gibt an, wie viele gültige BEMF-Events pro Umdrehung mindestens erkannt werden müssen, um die Motorlage zu bestimmen.
// Kleinere Werte = empfindlicher, aber störanfälliger.

/*********** ADCs aktivieren + Fallback-Werte ***********/
#define USE_ADC
// Aktiviert die analoge Strom- und Spannungsmessung.


//Die folgenden #ifndef-Blöcke sorgen dafür, dass ein Default-Pin/-Kanal gesetzt wird, wenn der Benutzer es nicht anderswo definiert hat:
#ifndef CURRENT_ADC_CHANNEL
	#define CURRENT_ADC_CHANNEL LL_ADC_CHANNEL_5
#endif
#ifndef VOLTAGE_ADC_CHANNEL
	#define VOLTAGE_ADC_CHANNEL LL_ADC_CHANNEL_6
#endif
#ifndef CURRENT_ADC_PIN
	#define CURRENT_ADC_PIN LL_GPIO_PIN_5
#endif
#ifndef VOLTAGE_ADC_PIN
	#define VOLTAGE_ADC_PIN LL_GPIO_PIN_6
#endif
#endif












