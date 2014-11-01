/*
 * engine.h
 *
 *  Created on: Feb 08, 2014
 *      Author: Erik Ashcraft
 */

#ifndef ENGINE_H
#define ENGINE_H

#include <stdio.h>
#include <string.h>

#include "camera.h"
#include "map.h"

/**
 * Engine
 *
 */
class Engine {

    private:
        // Display settings
        bool wireframe;
        bool fullscreen;
        int WIDTH;
        int HEIGHT;
        float aspect;

        // Mouse Info
        float lastx, lasty;
        bool isTargetMode;

        // FPS Info
        long lastTime;
        int frames;
        double fps;

        // Game Data
        Map map;
        Camera camera;

    public:
        /**
         * Engine( width, height )
         * the constructor
         *
         * @width    width of the window
         * @height   height of the window
         **/
        Engine(int width, int height);
        ~Engine();

        /**
         * run()
         *  - Starts the engine
         **/
        void run();

        /**
         * stop()
         *  - Stops the engine
         **/
        void stop();

        /**
         * reshape( width, height )
         * called, behind the scenes, to ensure new window width/height
         * accurately display the graphics.
         *
         * @width    new width of the window
         * @height   new height of the window
         **/
        void reshape(int width, int height);

        /**
         * render()
         * called behind the scenes to redraw everything
         **/
        void render();

        /**
         * updateTick()
         * called to update everything
         **/
        void updateTick();

        //Handle user input
        void handleMouseMovement(int x, int y);
        void handleMouseClick(int button, int state, int x, int y);
        void handleKeydown(unsigned char key, int x, int y);
        void handleKeyup(unsigned char key, int x, int y);
        void handleSpecialKey(int key, int x, int y);
};

#endif
