#include <raylib.h>
#include <iostream>
#include <vector>
#include <string>
#include "Functions.h"

using namespace std;

Sound currentSound;

int main() {
    const int screenWidth = 1650;
    const int screenHeight = 650;

    vector<string> paths;
    vector<string> names;
    vector<Sound> songs;
    const int itemSpacing = 50;
    InitAudioDevice();
    Image icon = LoadImage("../icon/icon.png");
   
    InitWindow(screenWidth, screenHeight, "Music Player");
    SetWindowIcon(icon);
    UnloadImage(icon);
    SetTargetFPS(60);
    Rectangle stop_start_button;
    stop_start_button.height = 60;
    stop_start_button.width = 200;
    stop_start_button.x = 430;
    stop_start_button.y = 570;

    string currentFileName;

    while (!WindowShouldClose()) {
        FilePathList droppedFiles = LoadDroppedFiles();
        BeginDrawing();
        ClearBackground(BLACK);

        DrawLine(410, 0, 410, 650, WHITE);
        DrawLine(410, 530, 1650, 530, WHITE);
        DrawRectangleRec(stop_start_button, WHITE);
        DrawText("History", 150, 30, 20, RED);
        DrawText("current song: ", 650, 585, 25, RED);
        DrawText("you can play the tracks from the history :) PS: 0 is first and 9 is the last", 420, 60, 28, BLUE);
        DrawText("maximal number of songs in history is 10 if you go out of this range the data will erase ", 420, 120, 28, GREEN);
        DrawText("Play/Stop", 460, 590, 25, BLACK);
        if (paths.size() > 10) 
        {
            paths.clear();
            songs.clear();
            names.clear();
        }
        {

        }
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

        songchecker(songs, paths, stop_start_button, currentSound);
        if (IsButtonPressed(stop_start_button, GetMousePosition()) && IsMouseButtonReleased(MOUSE_LEFT_BUTTON) || IsKeyReleased(KEY_SPACE)) {
            if (IsSoundPlaying(currentSound)) {
                PauseSound(currentSound);
                std::cout << "Sound paused" << std::endl;
            }
            else {
                ResumeSound(currentSound);
                std::cout << "Sound resumed" << std::endl;
            }
        }
        
        if (IsSoundPlaying(currentSound) && !currentFileName.empty()) {
            DrawText(currentFileName.c_str(), 810, 585, 25, WHITE);
        }

        int yPos = 50;
        for (const auto& name : names) {
            DrawText(name.c_str(), 0, yPos, 20, ORANGE);
            yPos += itemSpacing;
        }

        EndDrawing();
        UnloadDroppedFiles(droppedFiles);
        
    }

    CloseAudioDevice();
    CloseWindow();

    return 0;
}
