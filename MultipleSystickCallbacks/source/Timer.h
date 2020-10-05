/***************************************************************************//**
  @file     Timer.h
  @brief    Timer Header
  @author   Grupo 2 - Lab de Micros
 ******************************************************************************/
#ifndef TIMER_H_
#define TIMER_H_

/*******************************************************************************
 * CONSTANT AND MACRO DEFINITIONS USING #DEFINE
 ******************************************************************************/
#define TIMER_ISR_PERIOD 10000000L //100ms
#define INITIAL_TIMER_ELEMENTS_ARRAY_LENGTH	20

/*******************************************************************************
 * ENUMERATIONS AND STRUCTURES AND TYPEDEFS
 ******************************************************************************/
/* Each TimerElement is used to store the callback which Timer needs to call.
 * @variable callbackID. An unique ID of the element.
 * @variable callback. The function to be called.
 * @variable counterLimit.  The quotient between the callback period and the Timer's ISR period.
 * 							Indicates the amount of times the Timer's ISR must occur before calling the callback.
 * @variable counter. Indicates the amount of times the Timer's ISR occurred. It's reestablished when counterLimit is reached.
 * @variable paused. Indicates whether the calling of a callback is paused or not.
 */
typedef struct TimerElement
{
	int callbackID;
	void (*callback)(void);
	int counterLimit;
	int counter;
	bool paused;
} TimerElement;

typedef enum TimerError {TimerNoError = 0, TimerPeriodError = -1, TimerNoIdFound = -2} TimerError;

/*******************************************************************************
 * FUNCTION PROTOTYPES WITH GLOBAL SCOPE
 ******************************************************************************/
/**
 * @brief Initialization of the Timer Driver.
 * @return true if no error occurred.
 */
bool Timer_Init (void);

/**
 * @brief Adds a callback to be periodically called by Timer.
 * @param newCallback The function to be called. Must receive and return void. Usually a PISR.
 * @param period The period (in ms.) with which the callback is called. Must be greater than TIMER_ISR_PERIOD.
 * @return 	An ID to represent the callback element if no error occurred.
 * 			Must use this ID in case the calling needs to be cancelled or the period needs to be changed.
 * 			WARNING: if the returning number is negative it indicates an error and must be interpreted as a TimerError element.
 * WARNING If the quotient between period and TIMER_ISR_PERIOD is not an integer, it will be truncated.
 */
int Timer_AddCallback(void (*newCallback)(void), int period);

/**
 * @brief Cancels the calling of a callback by Timer.
 * @param timerID The callback ID given by Timer_AddCallback.
 * @return A TimerError indicating whether an error occurred (and its type) or not.
 */
TimerError Timer_DeleteCallback(int timerID);

/**
 * @brief Pauses the calling of a callback by Timer.
 * @param timerID The callback ID given by Timer_AddCallback.
 * @return A TimerError indicating whether an error occurred (and its type) or not.
 */
TimerError Timer_PauseCallback(int timerID);

/**
 * @brief Resumes the calling of a callback by Timer following a predefined period (defined in Timer_AddCallback).
 * @param timerID The callback ID given by Timer_AddCallback.
 * @return A TimerError indicating whether an error occurred (and its type) or not.
 */
TimerError Timer_ResumeCallback(int timerID);


/**
 * @brief Changes the period of calling of a callback.
 * @param timerID The callback ID given by Timer_AddCallback.
 * @param newPeriod The new period (in ms.) with which the callback is called. Must be greater than TIMER_ISR_PERIOD.
 * @return A TimerError indicating whether an error occurred (and its type) or not.
 * WARNING If the quotient between newPeriod and TIMER_ISR_PERIOD is not an integer, it will be truncated.
 */
TimerError Timer_ChangeCallbackPeriod(int timerID, int newPeriod);



#endif /* TIMER_H_ */
