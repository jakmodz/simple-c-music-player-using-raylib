#include "Functions.h"
#include <cstdlib>

bool IsButtonPressed(Rectangle button, Vector2 point)
{
    if (point.x >= button.x && point.x <= button.x + button.width &&
        point.y >= button.y && point.y <= button.y + button.height
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

void DrawVolumeLevels()
{


    int volume = 10;
    int x_pos = 750;

    std::string VolumeString;
    for (size_t i = 0; i < 10; ++i)
    {
        VolumeString = std::to_string(volume);
        DrawText(VolumeString.c_str(), x_pos, 515, 15, PURPLE);
        volume += 10;
        x_pos += 50;

    }


}

void PlayStopEvent(Sound& currentSound, Rectangle& stop_start_button)
{
    if (IsButtonPressed(stop_start_button, GetMousePosition()) && IsMouseButtonReleased(MOUSE_LEFT_BUTTON) || IsKeyReleased(KEY_SPACE)) {
        if (IsSoundPlaying(currentSound)) {
            PauseSound(currentSound);

        }
        else {
            ResumeSound(currentSound);

        }
    }
}

void DropingFiles(Sound& currentSound, std::vector<Sound>& songs, std::vector<std::string>& names, std::vector<std::string>& paths,std::string& currentFileName,FilePathList& droppedFiles)
{
    if (IsFileDropped()) {
        currentFileName = GetFileName(droppedFiles.paths[0]);
        StopSound(currentSound);
        UnloadSound(currentSound);
        currentSound = LoadSound(droppedFiles.paths[0]);
        PlaySound(currentSound);

        paths.push_back(droppedFiles.paths[0]);
        names.push_back(currentFileName);
        songs.push_back(currentSound);
    }

}




void songchecker(std::vector<Sound>& songs, std::vector<std::string>& paths, std::vector<std::string>& names,
    Rectangle& button, Sound& current_sound, std::string& currentfilename)
{
   
    for (int i = 0; i < paths.size(); ++i)
    {
        
        if (IsKeyReleased(48 + i))
        {
            StopSound(current_sound);
            current_sound = songs[i];
            currentfilename = names[i];
            current_sound = LoadSound(paths[i].c_str());

            
            PlaySound(current_sound);
        }
    }
}