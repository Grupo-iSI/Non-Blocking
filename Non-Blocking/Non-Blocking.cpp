#include "Non-Blocking.h"






boolean Every(unsigned long ms, Callback_t callBackHandler)
{
	boolean called;
	static unsigned long lastTick = 0;
	if(overFlow(lastTick)){lastTick = 0;	return false;}
	if((millis() - lastTick) >= ms || lastTick == 0UL)
	{
		lastTick = millis();
		if(callBackHandler != NULL)
		{
			(*callBackHandler)();
			called = true;
		}
	}
	else called = false;
	return called;
}

unsigned long switchTime(uint8_t inputPin, dtInput_t inputType)
{
	static unsigned long startTime = 0;
	//if(overFlow(startTime)){startTime = 0;	return 0;}
	static boolean state;
	if(digitalRead(inputPin) != state)
	{
		state = !state;
		startTime = millis();
	}
	if(inputType == PULL_UP)
	{
		if(state == LOW)    return millis() - startTime;
		else    return 0;
	}
	else if(inputType == PULL_DOWN)
	{
		if(state == HIGH)    return millis() - startTime;
		else    return 0;
	}
	else return 0;
}

unsigned long switchTime(uint8_t inputPin, dtInput_t inputType, unsigned long timeThreshold, Callback_t callBackHandler)
{
	static unsigned long startTime;
	//if(overFlow(startTime)){startTime = 0;	return 0;}
	static boolean state;
	if(digitalRead(inputPin) != state)
	{
		state = !state;
		startTime = millis();
	}
	if(inputType == PULL_UP)
	{
		if(state == LOW && (millis() - startTime) >= timeThreshold)
		{
			if(callBackHandler != NULL)
			{
				(*callBackHandler)();
				startTime = millis();
			}
			return millis() - startTime;
		}
		else    return 0;
	}
	else if(inputType == PULL_DOWN)
	{
		if(state == HIGH && (millis() - startTime) >= timeThreshold)
		{
			if(callBackHandler != NULL)
			{
				(*callBackHandler)();
				startTime = millis();
			}
			return millis() - startTime;
		}
		else    return 0;
	}
	else return 0;
}

boolean digitalReadDebounce(uint8_t inputPin, dtInput_t inputType)
{
	static unsigned long lastCall = 0;
	if(overFlow(lastCall)){lastCall = 0;	return false;}
	if(switchTime(inputPin, inputType) >= dtDEBOUNCE_THERESHOLD && dtTIME_THERESHOLD <= millis() - lastCall)
	{
		lastCall = millis();
		return true;
	}
	else    return false;
}

boolean digitalReadDebounce(uint8_t inputPin, dtInput_t inputType, Callback_t callBackHandler)
{
	static unsigned long lastCall = 0;
	if(overFlow(lastCall)){lastCall = 0;	return false;}
	if(switchTime(inputPin, inputType) >= dtDEBOUNCE_THERESHOLD)
	{
		if(callBackHandler != NULL && dtTIME_THERESHOLD <= millis() - lastCall)
		{
			(*callBackHandler)();
			lastCall = millis();
			return true; 
		}
		else return false;
	}
	else    return false;
}

boolean digitalReadBtn(uint8_t inputPin, dtInput_t inputType)
{
	if(inputType == PULL_UP)
	{
		static boolean lastState;
		if(switchTime(inputPin, inputType) >= dtDEBOUNCE_THERESHOLD)
		{
			if(lastState == HIGH && digitalRead(inputPin) == LOW)
			{
				lastState = LOW;
				return true;
			}
			else return false;
		}
		else if(lastState == LOW && digitalRead(inputPin) == LOW)
		{
			lastState = LOW;
			return false;
		}
		else
		{
			lastState = HIGH;
			return false;
		}
    }
	else if(inputPin == PULL_DOWN)
	{
		static boolean lastState;
		if(switchTime(inputPin, inputType) >= dtDEBOUNCE_THERESHOLD )
		{
			if(lastState == LOW && digitalRead(inputPin) == HIGH)
			{
				lastState = HIGH;
				return true;
			}
			else return false;
		}
		else if(lastState == HIGH && digitalRead(inputPin) == HIGH)
		{
			lastState = HIGH;
			return false;
		}
		else
		{
			lastState = LOW;
			return false;
		}
	}
	else return false;
}

boolean digitalReadBtn(uint8_t inputPin, dtInput_t inputType, Callback_t callBackHandler)
{
    if(digitalReadBtn(inputPin, inputType) && callBackHandler != NULL)  (*callBackHandler)();
    else return false;
    return true;
}

void delay(unsigned long ms, Callback_t callBackHandler)
{
    unsigned long startTime = millis();	
    do
    {
        if(callBackHandler != NULL) (*callBackHandler)();
    }   while(millis() - startTime <= ms);
} 