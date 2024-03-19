/*
    Step to develop Pong
    1. Create a blank screen & gme loop
    2. Draw the paddles and the ball
    3. Move the ball ảound
    4. Check for a collision with all edges
    5. Move the player's páddle
    6. Move the CPU paddle with AI
    7. Check for a collision with the paddles
    8. Add scoring
*/

#include <iostream>
#include <raylib.h>
#include <cmath>
using namespace std;

class Ball
{
public:
    float x, y;
    int speed_x, speed_y;
    int radius;

    void Draw()
    {
        DrawCircle(x, y, radius, WHITE);
    }

    void Move()
    {
        x += speed_x;
        y += speed_y;

        if (y >= GetScreenHeight() || y <= 0)
        {
            speed_y = -speed_y;
        }
        if (x >= GetScreenWidth() || x <= 0)
        {
            speed_x = -speed_x;
        }
    }
};

class Paddle
{
public:
    float x, y;
    int width, height;
    int speed;

    void Draw()
    {
        DrawRectangle(x, y, width, height, WHITE);
    }

    void Move()
    {
        if (IsKeyDown(KEY_UP))
        {
            y -= speed;
        }
        if (IsKeyDown(KEY_DOWN))
        {
            y += speed;
        }
    }
};

Ball ball;
Paddle player;

int main()
{

    cout << "Starting the game" << endl;
    const int screenWidth = 1200;
    const int screenHeight = 800;
    InitWindow(screenWidth, screenHeight, "Starting the gameStarting the game");
    SetTargetFPS(60);
    ball.x = screenWidth / 2;
    ball.y = screenHeight / 2;
    ball.speed_x = 5;
    ball.speed_y = 5;
    ball.radius = 20;

    // Player
    player.width = 20;
    player.height = 100;
    player.x = screenWidth - player.width - 20;
    player.y = screenHeight / 2 - player.height / 2;
    player.speed = 5;

    while (!WindowShouldClose())
    {
        BeginDrawing();

        // Move
        ball.Move();
        player.Move(); // Corrected from player.Update()

        ClearBackground(BLACK);
        DrawLine(screenWidth / 2, 0, screenWidth / 2, screenHeight, WHITE);
        DrawRectangle(10, screenHeight / 2 - 60, 25, 120, WHITE);

        ball.Draw();
        player.Draw();

        EndDrawing();
    }

    return 0;
    CloseWindow();
}
