#include <raylib.h>
#include <iostream>
#include <vector>
#include <string>
#include "Functions.h"

using namespace std;

Sound currentSound;
int volume_level = 100;
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
    Rectangle pseudo_slider;
    pseudo_slider.height = 7;
    pseudo_slider.width = 510;
    pseudo_slider.x = 700;
    pseudo_slider.y = 510;
    Rectangle clearHistory;
    clearHistory.height = 50;
    clearHistory.width = 409;
    clearHistory.x = 0;
    clearHistory.y = 600;

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
        DrawRectangleRec(clearHistory, ORANGE);
        DrawRectangleRec(pseudo_slider, MAROON);
        DrawText("Volume: ", 850, 460, 50, BLUE);
        std::string temporaly_string = std::to_string(volume_level);
        DrawText(temporaly_string.c_str(), 1035, 460, 50, ORANGE);
        DrawText("you can play the tracks from the history :) PS: 0 is first and 9 is the last", 420, 60, 28, BLUE);
        DrawText("maximal number of songs in history is 10 if you go out of this range the data will erase ", 420, 120, 28, GREEN);
        DrawText("Play/Stop", 460, 590, 25, BLACK);
        DrawText("Clear History", 130, 615, 20, RED);
        DrawVolumeLevels();



        int yPos = 50;
        for (const auto& name : names) {
            DrawText(name.c_str(), 0, yPos, 20, ORANGE);
            yPos += itemSpacing;
        }
        if (IsSoundPlaying(currentSound)) {
            DrawText(currentFileName.c_str(), 830, 585, 25, WHITE);
        }
        if (IsButtonPressed(pseudo_slider, GetMousePosition()) && IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
        {
            Vector2 mouse_position = GetMousePosition();
            int mouse_position_x = mouse_position.x;

            volume_level = mouse_position_x - 700;
            volume_level = volume_level / 5;
            if (volume_level > 100)
            {
                volume_level = 100;
            }
            SetMasterVolume(volume_level);

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

        songchecker(songs, paths, names, stop_start_button, currentSound, currentFileName);
        if (IsButtonPressed(stop_start_button, GetMousePosition()) && IsMouseButtonReleased(MOUSE_LEFT_BUTTON) || IsKeyReleased(KEY_SPACE)) {
            if (IsSoundPlaying(currentSound)) {
                PauseSound(currentSound);

            }
            else {
                ResumeSound(currentSound);

            }
        }



        if (paths.size() > 10 || IsButtonPressed(clearHistory, GetMousePosition()))
        {
            paths.clear();
            songs.clear();
            names.clear();
        }

        EndDrawing();
        UnloadDroppedFiles(droppedFiles);

    }

    CloseAudioDevice();
    CloseWindow();

    return 0;
}
