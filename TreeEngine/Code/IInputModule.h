#pragma once

class IInputModule
{
public:
	virtual bool GetMouseButton(int ButtonValue);
	virtual bool GetButtonPressed(int ButtonValue);
};