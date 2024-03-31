#include <raylib.h>
#include "Functions.h"
#include <iostream>
#include <vector>

Sound currentSound;
using namespace std;

int main()
{
    const int screenWidth = 1200;
    const int screenHeight = 650;
    
    // Initialize audio device
    InitAudioDevice();

    InitWindow(screenWidth, screenHeight, "Music_Player");
   
    SetTargetFPS(60);
    Rectangle stop_start_button;
    stop_start_button.height = 60; stop_start_button.width = 100;
    stop_start_button.x = 650; stop_start_button.y = 570;
    
    int index=0;
    bool soundloaeded = false;
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(BLACK);

        DrawLine(200, 0, 200, 650, WHITE);
        DrawLine(200, 530, 1200, 530, WHITE);
        DrawRectangleRec(stop_start_button, WHITE);
        DrawText("History", 50, 30, 20, RED);
        if (IsFileDropped())
        {
            
            if (!soundloaeded)
            {



                FilePathList droppedFiles = LoadDroppedFiles();

                currentSound = LoadSound(droppedFiles.paths[0]);

                PlaySound(currentSound);
                soundloaeded = true;
            }
            else
            {
                soundloaeded = false;
            }
                
        }
        EndDrawing();
    }
    
    // Close audio device when done
    CloseAudioDevice();

    CloseWindow();

    return 0;
}
