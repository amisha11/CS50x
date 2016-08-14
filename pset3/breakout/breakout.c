//
// breakout.c
//
// Computer Science 50
// Problem Set 3
//

// standard libraries
#define _XOPEN_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Stanford Portable Library
#include <spl/gevents.h>
#include <spl/gobjects.h>
#include <spl/gwindow.h>

// height and width of game's window in pixels
#define HEIGHT 600
#define WIDTH 400

//Dimensions of the brick
#define B_HEIGHT 10
#define B_WIDTH 75

//height and width of paddle
#define P_HEIGHT 15
#define P_WIDTH 70

// number of rows of bricks
#define ROWS 5

// number of columns of bricks
#define COLS 10

// radius of ball in pixels
#define RADIUS 10

// lives
#define LIVES 3

// prototypes
void initBricks(GWindow window);
GOval initBall(GWindow window);
GRect initPaddle(GWindow window);
GLabel initScoreboard(GWindow window);
void updateScoreboard(GWindow window, GLabel label, int points);
GObject detectCollision(GWindow window, GOval ball);

int main(void)
{
    // seed pseudorandom number generator
    srand48(time(NULL));

    // instantiate window
    GWindow window = newGWindow(WIDTH, HEIGHT);

    // instantiate bricks
    initBricks(window);

    // instantiate ball, centered in middle of window
    GOval ball = initBall(window);

    // instantiate paddle, centered at bottom of window
    GRect paddle = initPaddle(window);

    // instantiate scoreboard, centered in middle of window, just above ball
    GLabel label = initScoreboard(window);

    // number of bricks initially
    int bricks = COLS * ROWS;

    // number of lives initially
    int lives = LIVES;

    // number of points initially
    int points = 0;

    // keep playing until game over
    waitForClick();
    
    while (lives > 0 && bricks > 0)
    {
        double velocity_x = drand48() + 1;
        double velocity_y = 2;
    
    
        while (true)
        {
            move(ball, velocity_x, velocity_y);
        
            GEvent event = getNextEvent(MOUSE_EVENT);
            if (event != NULL)
            {
                if (getEventType(event) == MOUSE_MOVED)
                {
                    double x;
                    if ((getX(event) + P_WIDTH) <= getWidth(window))
                        x = getX(event);
                    else
                        x = getWidth(window) - P_WIDTH;
                    double y =(getHeight(window) - P_HEIGHT - 25);
                    setLocation(paddle, x, y);
                }
            }

            // linger before moving again
            pause(10);
        
            GObject object = detectCollision(window, ball);
            if (object != NULL)
            {
                if (object == paddle)
                {
                    velocity_y = -velocity_y;
                }
                else if (strcmp(getType(object), "GRect") == 0)
                {
                    removeGWindow(window, object);
                    velocity_y = -(velocity_y + drand48());
                    velocity_x = -(velocity_x + 1);
                    points++;
                    updateScoreboard(window, label, points);
                    bricks--;
                    if (bricks == 0)
                    {
                        printf("You Won\n");
                        return 0;
                    }
                    break;
                }
            }
            
            // bounce off right edge of window
            if (getX(ball) + getWidth(ball) >= getWidth(window))
            {
                velocity_x = -(velocity_x + 0.5);
            }

            // bounce off left edge of window
            else if (getX(ball) <= 0)
            {
                velocity_x = -velocity_x;
            }
            // top of the window
            if (getY(ball) <= 0)
            {
                velocity_y = -(velocity_y + 0.5);
            }
        
            else if (getY(ball) + getHeight(ball) >= getHeight(window))
            {
                lives--;
                if (lives == 0)
                {
                    printf("You Lost \n");
                    return 0;
                }
                pause(100);    
                setLocation(ball, getWidth(window) / 2 - RADIUS, getHeight(window) / 2 - RADIUS);
                break;
            }
            
        }
    }
    
    

    // wait for click before exiting
    waitForClick();

    // game over
    closeGWindow(window);
    return 0;
}

/**
 * Initializes window with a grid of bricks.
 */
void initBricks(GWindow window)
{
    string array[] = { "GREEN", "RED", "YELLOW" };
    string color;
    for (int i = 0; i < COLS; i++)
    {   color = array[i % 3];
        for (int j = 0; j < ROWS; j++)
        {
            GRect rect = newGRect(0 + (j * (B_WIDTH + 7)), 0 + (i * (B_HEIGHT + 7)), B_WIDTH, B_HEIGHT);
            setColor(rect, color);
            setFilled(rect, true);
            add(window, rect);
        }
    }
    return;
}

/**
 * Instantiates ball in center of window.  Returns ball.
 */
GOval initBall(GWindow window)
{
    double x = getWidth(window)/2 - RADIUS;
    double y = getHeight(window)/2 - RADIUS;
    
    GOval circle = newGOval(x, y, 2 * RADIUS, 2 * RADIUS);
    setFilled(circle, true);
    add(window, circle);
    
    return circle;
}

/**
 * Instantiates paddle in bottom-middle of window.
 */
GRect initPaddle(GWindow window)
{
    double x = (getWidth(window) - P_WIDTH) / 2;
    double y = (getHeight(window) - P_HEIGHT - 25);
    
    GRect rect = newGRect(x, y, P_WIDTH, P_HEIGHT);
    setColor(rect, "BLACK");
    setFilled(rect, true);
    add(window, rect);
    
    return rect;
}

/**
 * Instantiates, configures, and returns label for scoreboard.
 */
GLabel initScoreboard(GWindow window)
{
    GLabel label = newGLabel("0");
    setFont(label, "SansSerif-36");
    add(window, label);
    
    double x = (getWidth(window) - getWidth(label)) / 2;
    double y = (getHeight(window) - getHeight(label)) / 2;
    setLocation(label, x, y);
    
    return label;
}

/**
 * Updates scoreboard's label, keeping it centered in window.
 */
void updateScoreboard(GWindow window, GLabel label, int points)
{
    // update label
    char s[12];
    sprintf(s, "%i", points);
    setLabel(label, s);

    // center label in window
    double x = (getWidth(window) - getWidth(label)) / 2;
    double y = (getHeight(window) - getHeight(label)) / 2;
    setLocation(label, x, y);
}

/**
 * Detects whether ball has collided with some object in window
 * by checking the four corners of its bounding box (which are
 * outside the ball's GOval, and so the ball can't collide with
 * itself).  Returns object if so, else NULL.
 */
GObject detectCollision(GWindow window, GOval ball)
{
    // ball's location
    double x = getX(ball);
    double y = getY(ball);

    // for checking for collisions
    GObject object;

    // check for collision at ball's top-left corner
    object = getGObjectAt(window, x, y);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's top-right corner
    object = getGObjectAt(window, x + 2 * RADIUS, y);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's bottom-left corner
    object = getGObjectAt(window, x, y + 2 * RADIUS);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's bottom-right corner
    object = getGObjectAt(window, x + 2 * RADIUS, y + 2 * RADIUS);
    if (object != NULL)
    {
        return object;
    }

    // no collision
    return NULL;
}
