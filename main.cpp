//SFML C++ PACMAN pt 2
//created by Dr. Mo 11/21
//dynamicsofanasteroid.com

#include<iostream>
#include "SFML/Graphics.hpp"
#include"globals.h"
#include"ghost.h"
using namespace std;



int main() {
    //game set up (you'll need these lines in every game)
    sf::RenderWindow screen(sf::VideoMode(800, 800), "pacman"); //set up screen
    sf::Event event; //set up event queue
    sf::Clock clock; //set up the clock (needed for game timing)
    const float FPS = 60.0f; //FPS
    screen.setFramerateLimit(FPS); //set FPS

    //load in images
    sf::Texture brick;
    brick.loadFromFile("brick.png");
    sf::Sprite wall;
    wall.setTexture(brick);
    //ideally you'll load in images for pacman and the ghosts here too!

    int map[10][10] = { //student maps should be much bigger than this
        1,1,1,1,1,1,1,1,1,1,
        1,0,0,0,0,0,0,0,0,1,
        1,1,1,1,1,0,1,1,0,1,
        1,0,1,0,0,0,1,0,0,1,
        1,0,0,0,1,1,0,0,1,1,
        1,1,0,0,0,1,0,0,0,1,
        1,0,0,1,0,0,0,1,0,1,
        1,0,1,1,1,0,1,1,0,1,
        1,0,0,0,0,0,0,0,0,1,
        1,1,1,1,1,1,1,1,1,1
    };

    //player setup
    int xpos = 85;
    int ypos =85;
    int vx = 0;
    int vy = 0;
    sf::CircleShape player(PACSIZE);
    player.setFillColor(sf::Color(250, 250, 0)); //using RGB value for color here (hex also works)
    player.setPosition(xpos, ypos); //top left "corner" of circle (not center!)
    bool keys[] = { false, false, false, false }; //array to hold keyboard input

    //instantiate and initalize ghosts (usually we use a constructor here)
    ghost Blinky;
	Blinky.initGhost(400, 644, 1, 0, 1, 0);

    //################### HOLD ONTO YOUR BUTTS, ITS THE GAME LOOP###############################################################
    while (screen.isOpen()) {//keep window open until user shuts it down

        while (screen.pollEvent(event)) { //look for events-----------------------

            //this checks if the user has clicked the little "x" button in the top right corner
            if (event.type == sf::Event::EventType::Closed)
                screen.close();
            //KEYBOARD INPUT 
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
                keys[LEFT] = true;
            }
            else keys[LEFT] = false;

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
                keys[RIGHT] = true;
            }
            else keys[RIGHT] = false;
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
                keys[UP] = true;
            }
            else keys[UP] = false;
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
                keys[DOWN] = true;
            }
            else keys[DOWN] = false;


        }//end event loop---------------------------------------------------------------

        //SETTING Mr. Pac's velocity
        if (keys[LEFT] == true)
            vx = -5;

        else if (keys[RIGHT] == true)
            vx = 5;

        else vx = 0;
        if (keys[UP] == true)
            vy = -5;

        else if (keys[DOWN] == true)
            vy = 5;

        else vy = 0; // The laws of momentum do not apply to Mr. Pac

        // Collision checking for mr. pac

        // Mr. Pac Moves On Down
        xpos += vx;
        ypos += vy;
        player.setPosition(xpos, ypos);

        //call chaser function for each ghost 
        Blinky.chase1(xpos, ypos, map);

        //render section-----------------------------------------
        screen.clear(); //wipes screen, without this things smear

        //draw map
        for (int rows = 0; rows < 10; rows++)
            for (int cols = 0; cols < 10; cols++) {
                if (map[cols][rows] == 1) {
                    wall.setPosition(cols * 80, rows * 80);
                    screen.draw(wall);
                }
            }
        //draw all the other stuff
        screen.draw(player); //draw player
        Blinky.drawGhost(screen);
        //flip it all onto the screen!
        screen.display(); 

    }//######################## end game loop ###################################################################################

    cout << "goodbye!" << endl;
} //end of main
