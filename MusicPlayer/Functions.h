#pragma once
#include <raylib.h>
#include <string>
#include <vector>
bool IsButtonPressed(Rectangle button, Vector2 point);
int random_integer(int inclusiveFrom, int exclusiveTo);
void songchecker(std::vector<Sound>& songs, std::vector<std::string>& paths, std::vector<std::string>& names,
    Rectangle& button, Sound& current_sound, std::string& currentfilename);
void DrawVolumeLevels();
void PlayStopEvent (Sound& currentSound,Rectangle& stop_start_button);
void DropingFiles(Sound& currentSound, std::vector<Sound>& songs, std::vector<std::string>& names, std::vector<std::string>& paths,
    std::string& currentFileName, FilePathList& droppedFiles);
