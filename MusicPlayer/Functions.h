#pragma once
#include <raylib.h>
#include <string>
#include <vector>
bool IsButtonPressed(Rectangle button, Vector2 point);
int random_integer(int inclusiveFrom, int exclusiveTo);
void songchecker(std::vector<Sound> songs, std::vector<std::string> paths,
    Rectangle& button, Sound& current_sound);

