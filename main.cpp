#include <iostream>
#include <raylib.h>

using namespace std; 

Color Purple = Color{207, 159, 255};

int player_score = 0;
int cpu_score = 0;
int player2_score = 0;
bool PVP;

class Ball{ //ball class with all of its attributes
    public:
    float x, y;
    int speed_x, speed_y;
    int radius;

    void Draw() { //to draw game elements that are interchangeable
        DrawCircle(x, y, radius, WHITE);
    }

    void Update() { //updates ball's position
        x += speed_x;
        y += speed_y; //makes x and y go forward

        if (y + radius >= GetScreenHeight() || y - radius <= 0) { //makes ball bounce if it touches border
            speed_y *= -1;
        }
        if (x + radius >= GetScreenWidth()) {
            cpu_score++;
            ResetBall();
        }
        
        
        if (x - radius <= 0) {
            player_score++;
            ResetBall();
        }
    }


void ResetBall() {
    x = GetScreenWidth()/2;
    y = GetScreenHeight()/2;

    int speed_choices[2] = {-1,1};
    speed_x *= speed_choices[GetRandomValue(0,1)];
    speed_y *= speed_choices[GetRandomValue(0,1)];
}

};


class Paddle{
protected:
void LimitMovement() {
    if (y <= 0) {
        y = 0;
    }
    if (y + height >= GetScreenHeight()) {
        y = GetScreenHeight() - height;
    }
}

public:
float x,y;
float width, height;
int speed;

void Draw() {
    DrawRectangle(x, y, width, height, WHITE);
}

void Update(){
    if (IsKeyDown(KEY_UP)) {
        y = y - speed;
    }
    if (IsKeyDown(KEY_DOWN)) {
        y = y + speed;
    }

LimitMovement();

}

};

class CpuPaddle: public Paddle {
public:

void Update(int ball_y) {
    if(y + height/2 > ball_y) {
        y = y - speed;
    }
    if (y + height/2 <= ball_y) {
        y = y + speed;
    }

LimitMovement();
}
};

class Player2Paddle: public Paddle {
    public:
    void Update() {
        if (IsKeyDown(KEY_W)) {
            y = y - speed;
        }
        if (IsKeyDown(KEY_S)) {
            y = y + speed;
        }
    }
};

Ball ball;
Paddle player;
CpuPaddle cpu;
Player2Paddle player2;

int main () {

cout << "Starting the game" << endl; //sends to console
const int screen_width = 1280;
const int screen_height = 800;
InitWindow(screen_width, screen_height, "Michael's first game"); //window size + title

SetTargetFPS(60); // frames per second

ball.radius = 20; //ball class, following with a radius method defined
ball.x = screen_width/2;
ball.y = screen_height/2;
ball.speed_x = 7;
ball.speed_y = 7;

//player paddle draw
player.width = 25;
player.height = 120;
player.x = screen_width - player.width - 10;
player.y = screen_height/2 - player.height/2;
player.speed = 6;


cpu.height = 120;
cpu.width = 25;
cpu.x = 10;
cpu.y = screen_height/2 - player.height/2;
cpu.speed = 6;

//main menu
while (WindowShouldClose() == false || IsKeyPressed(KEY_SPACE) == false) {
BeginDrawing();
DrawText(TextFormat("PRESS SPACE"), 300, screen_height/2, 100, WHITE);
DrawText(TextFormat("MADE BY MICHAEL Z"), 225, 3* screen_height/4, 80, WHITE);

ClearBackground(Purple);
if (IsKeyPressed(KEY_SPACE) == true) {
break;
} 
EndDrawing();
}


//difficulty selection
while (WindowShouldClose() == false || IsKeyPressed(KEY_SPACE) == true) {
BeginDrawing();
DrawText(TextFormat("SELECT DIFFICULTY"), 100, screen_height/2, 100, WHITE);
DrawText(TextFormat("1, 2 or 3"), 450, 3* screen_height/4, 80, WHITE);

ClearBackground(Purple);
if (IsKeyPressed(KEY_ONE) == true) {
ball.speed_x--;
ball.speed_y--;
break;
} 
if (IsKeyPressed(KEY_TWO) == true) {
break;
} 
if (IsKeyPressed(KEY_THREE) == true) {
ball.speed_x++;
ball.speed_y++;
break;
} 

EndDrawing();
}



 
 //main game
while (WindowShouldClose() == false)                //what happens while window is open (WindowShouldClose() is a function that determines if window is closed or not)
{
BeginDrawing();         //creates blank canvas


//updating
ball.Update();
player.Update();

//checking for collisions
if(CheckCollisionCircleRec(Vector2{ball.x, ball.y}, ball.radius, Rectangle{player.x, player.y, player.width, player.height})) {
    ball.speed_x *= -1;
}
if(CheckCollisionCircleRec(Vector2{ball.x, ball.y}, ball.radius, Rectangle{cpu.x, cpu.y, cpu.width, cpu. height} )) {
    ball.speed_x *= -1;
}


ClearBackground(Purple);
DrawLine(screen_width/2, 0, screen_width/2, screen_height, WHITE);
//all the Draw() methods come from their respective classes: Ball, Paddle and CpuPaddle (inherited from Paddle)
ball.Draw(); //draws bouncing ball

    cpu.Draw(); //draws left rectangle (AI)
    cpu.Update(ball.y);



player.Draw(); //draws right rectangle (player)
DrawText(TextFormat("%i", cpu_score), screen_width/4, 20, 80, WHITE);
DrawText(TextFormat("%i", player_score), 3* screen_width/4, 40, 80, WHITE);



EndDrawing();       //ends canvas drawing
}
    
    CloseWindow();
    return 0;
 

}

