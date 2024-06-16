#include <stdio.h>
#include <iostream>
#include <vector>
#include "raylib.h"
#include "rcamera.h"
#include "CustomCameraModule.h"


int main()
{
    // Init
    const int screenWidth = 1280;
    const int screenHeight = 720;

    InitWindow(screenWidth, screenHeight, "Eg by Ribx8 and kiryD");

    // Camera position
    Camera3D camera = { 0 };
    camera.position = Vector3{ 0.0f, 2.0f, 4.0f };
    camera.target = Vector3{ 0.0f, 2.0f, 0.0f };
    camera.up = Vector3{ 0.0f, 1.0f, 0.0f };
    camera.fovy = 90.0f;
    camera.projection = CAMERA_PERSPECTIVE;
    BoundingBox camera_rect;
    BoundingBox cube;
    camera_rect.min = Vector3{ 0.0f, 0.0f, 0.0f };
    camera_rect.max = Vector3{ 1.0f, 2.0f, 1.0f };
    // Это сами рамки, min это 1 точка и max это 2 точка и вместе куб
    cube.min = Vector3{ -6.0f, 0.0f, -6.0f };
    cube.max = Vector3{ 6.0f, 5.0f, 6.0f };
    
    bool crack = false;
    bool collision = true;

    int cameraMode = CAMERA_FIRST_PERSON;
    // Making THE EGG and stand for it
    Model egg_model = LoadModel("egg.obj");
    Model stand_model = LoadModel("stand.obj");
    Model chick_model = LoadModel("chick.gltf");
    BoundingBox bounds = GetMeshBoundingBox(egg_model.meshes[0]);
    Vector3 position = { 0.0f, 1.0f, 0.0f };                    // Set models position
    Vector3 rotation = { 0.0f, 1.0f, 0.0f };
    float rotation2 = 10.0f;

    DisableCursor();

    SetTargetFPS(60);
    
    while (!WindowShouldClose())
    {
        rotation2 += .80f;
        camera_rect.min = Vector3{ camera.position.x - 1.0f, camera.position.y - 2.0f, camera.position.z - 1.0f };
        camera_rect.max = Vector3{ camera.position.x + 1.0f, camera.position.y + 2.0f, camera.position.z + 1.0f };
        DrawText(CheckCollisionBoxes(camera_rect, cube) ? "collide" : "not collide", screenWidth / 2, 5, 14, BLACK);
        collision = CheckCollisionBoxes(camera_rect, cube);
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT) and CheckCollisionBoxes(camera_rect, bounds))
        {
            crack = true;
        }
        if (IsKeyPressed(KEY_R))
        {
            cameraMode = CAMERA_FIRST_PERSON;
            camera.up = Vector3{ 0.0f, 1.0f, 0.0f };
        }
        if (IsKeyDown(KEY_LEFT_SHIFT)) {
            camera.position.y = 1.0f;
            camera.target.y = 1.0f;
        }
        if (IsKeyReleased(KEY_LEFT_SHIFT)) {
            camera.position.y = 2.0f;
            camera.target.y = 2.0f;
        }
        custom::UpdateCamera(&camera, cameraMode, collision);          // Update camera
        BeginDrawing();
        
        ClearBackground(RAYWHITE);

        BeginMode3D(camera);

        // Draw egg and stand

        if (!crack) DrawModel(egg_model, position, 0.3f, Fade(WHITE, 2.0f));
        DrawModelEx(chick_model, position, rotation, rotation2, Vector3{ 0.8f, 0.8f, 0.8f }, YELLOW);
        DrawModel(stand_model, position, 0.3f, BLACK);
        
        //DrawGrid(100, 0.5); <- это можешь разкоментить и там будет показана сетка
        
        DrawPlane(Vector3{ 0.0f, 0.0f, 0.0f }, Vector2{ 32.0f, 32.0f }, LIGHTGRAY); // Draw ground
        //                 позиция                    размер         цвет
        /*
        DrawCube(Vector3{ -16.0f, 2.5f, 0.0f }, 1.0f, 5.0f, 32.0f, SKYBLUE);     // Draw a blue wall
        DrawCube(Vector3{ 16.0f, 2.5f, 0.0f }, 1.0f, 5.0f, 32.0f, LIME);      // Draw a green wall
        DrawCube(Vector3{ 0.0f, 2.5f, 16.0f }, 32.0f, 5.0f, 1.0f, GOLD);      // Draw a yellow wall
        DrawCube(Vector3{ 0.0f, 2.5f, -16.0f }, 32.0f, 5.0f, 1.0f, RED);      // Draw a red wall
        */
        DrawPlane(Vector3{ 0.0f, 0.0f, 0.0f }, Vector2{ 32.0f, 32.0f }, LIGHTGRAY); // Draw ground
        DrawCube(Vector3{ -8.0f, 2.5f, 0.0f }, 1.0f, 5.0f, 20.0f, SKYBLUE);     // Draw a blue wall
        DrawCube(Vector3{ 8.0f, 2.5f, 0.0f }, 1.0f, 5.0f, 20.0f, LIME);      // Draw a green wall
        DrawCube(Vector3{ 0.0f, 2.5f, 8.0f }, 20.0f, 5.0f, 1.0f, GOLD);      // Draw a yellow wall
        DrawCube(Vector3{ 0.0f, 2.5f, -8.0f }, 20.0f, 5.0f, 1.0f, RED);      // Draw a red wall
        DrawBoundingBox(cube, RED);
        DrawCube(Vector3{ 0.0f, 0.1f, 0.0f }, 1.0f, 1.0f, 1.0f, Fade(GREEN, 0.5f));
        
        //DrawBoundingBox(camera_rect, RED);
        EndMode3D();

        // Draw info boxes
        DrawRectangle(5, 5, 205, 55, Fade(SKYBLUE, 0.5f));
        DrawRectangleLines(5, 5, 205, 55, BLUE);

        DrawText("Controls:", 15, 15, 10, BLACK);
        DrawText("- Move keys: W, A, S, D, Shift", 15, 30, 10, BLACK);
        DrawText("- Look around: arrow keys or mouse", 15, 45, 10, BLACK);
        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    UnloadModel(egg_model);
    UnloadModel(stand_model);
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}

