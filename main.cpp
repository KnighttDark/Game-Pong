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

Color Green = Color{38, 185, 154, 255};
Color Dark_Green = Color{20, 160, 133, 255};
Color Light_Green = Color{129, 204, 184, 255};
Color Yellow = Color{243, 213, 91, 255};

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

class ComputerPaddle : public Paddle
{
public:
    void Move(int ball_y)
    {
        if (y + height / 2 > ball_y)
        {
            y -= speed;
        }

        if (y + height / 2 < ball_y)
        {
            y += speed;
        }
    }
};

Ball ball;
Paddle player;
ComputerPaddle computer;

int playerScore = 0;
int computerScore = 0;

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

    // ComputerPaddle

    computer.height = 100;
    computer.width = 20;
    computer.x = 10;
    computer.y = screenHeight / 2 - computer.height / 2;
    computer.speed = 5;

    while (!WindowShouldClose())
    {
        BeginDrawing();

        // Move
        ball.Move();
        player.Move(); // Corrected from player.Update()
        computer.Move(ball.y);

        // Check collision with player paddle
        if (CheckCollisionCircleRec({ball.x, ball.y}, ball.radius, {player.x, player.y, player.width, player.height}))
        {
            ball.speed_x = -ball.speed_x;
        }

        // Check collision with computer paddle
        if (CheckCollisionCircleRec({ball.x, ball.y}, ball.radius, {computer.x, computer.y, computer.width, computer.height}))
        {
            ball.speed_x = -ball.speed_x;
        }

        ClearBackground(Dark_Green);
        DrawCircle(screenWidth / 2, screenHeight / 2, 100, Light_Green);
        DrawLine(screenWidth / 2, 0, screenWidth / 2, screenHeight, WHITE);

        // Check score
        if (ball.x <= 0)
        {
            computerScore++;
            ball.x = screenWidth / 2;
            ball.y = screenHeight / 2;
        }
        else if (ball.x >= screenWidth)
        {
            playerScore++;
            ball.x = screenWidth / 2;
            ball.y = screenHeight / 2;
        }
        DrawText(to_string(playerScore).c_str(), screenWidth / 2 + 50, 20, 20, WHITE);
        DrawText(to_string(computerScore).c_str(), screenWidth / 2 - 50, 20, 20, WHITE);
        // Draw
        ball.Draw();
        player.Draw();
        computer.Draw();

        EndDrawing();
    }

    return 0;
    CloseWindow();
}
