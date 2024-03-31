#include "Functions.h"
#include <cstdlib>

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

int random_integer(int inclusiveFrom, int exclusiveTo)
{
	return inclusiveFrom + rand() % (exclusiveTo - inclusiveFrom);
	
}

void songchecker(std::vector<Sound> songs, std::vector<std::string> paths,
    Rectangle& button, Sound& current_sound)
{
    for (int i = 0; i < paths.size(); ++i)
    {
        
        if (IsKeyReleased(48 + i))
        {
            
            if (IsSoundPlaying(songs[i]))
            {
                StopSound(songs[i]);
            }
            else
            {





                
                songs[i] = LoadSound(paths[i].c_str());
                songs[i] = current_sound;
                
                PlaySound(current_sound);
                
                if (IsButtonPressed(button, GetMousePosition()) && IsMouseButtonReleased(MOUSE_LEFT_BUTTON) || IsKeyReleased(KEY_SPACE))
                {
                    StopSound(current_sound);
                }
                else
                {
                    ResumeSound(current_sound);

                }

            }
        }
    }
}
