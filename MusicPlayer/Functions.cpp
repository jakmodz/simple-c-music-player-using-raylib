#include "Functions.h"

bool IsButtonPressed(Rectangle button, Vector2 point)
{
	if (point.x >= button.x && point.x <= button.x+button.width&&
		point.y >= button.y && point.y <= button.y+button.height
		&&
		IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
	{
		return true;
	}
    return false;
}
