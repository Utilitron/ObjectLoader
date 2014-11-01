/*
 * engine.cc
 *
 *  Created on: Feb 08, 2014
 *	  Author: Erik Ashcraft
 */

#include "engine.h"

/**
 * Constructor
 **/
Engine::Engine(int width, int height) :
        wireframe(false), fullscreen(false), WIDTH(width), HEIGHT(height), lastTime(glutGet(GLUT_ELAPSED_TIME)), frames(0), fps(0), map(), camera() {

    // Display settings
    aspect = (float) WIDTH / (float) HEIGHT;

    // Mouse Info
    lastx = WIDTH / 2;
    lasty = HEIGHT / 2;
}

/**
 * Deconstructor
 **/
Engine::~Engine() {
}

/**
 * reshape( width, height )
 * called, behind the scenes, to ensure new window width/height
 * accurately display the graphics.
 *
 * @width	new width of the window
 * @height	 new height of the window
 **/
void Engine::reshape(int width, int height) {
    // Set the aspect ratio
    aspect = (float) width / (float) height;

    // Set up the vewport, and matrix mode
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    // Set the perspective (field of view, aspect ratio, near, far)
    gluPerspective(60.0f, aspect, 1.0f, 256.0f);

    // Reset modelview matrix
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

/**
 * render()
 * called behind the scenes to redraw everything
 **/
void Engine::render() {
    // Clear the window with current clearing color
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

    // Set up the matrix mode
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    // Set the perspective (field of view, aspect ratio, near, far)
    gluPerspective(60.0f, aspect, 1.0f, 256.0f);

    // Reset modelview matrix
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glPushMatrix();
        // Move the camera back
        glTranslatef(0.0f, 0.0f, -camera.getRadius());
        // Rotate the camera
        glRotatef(camera.getXrot(), 1.0, 0.0, 0.0);
        glRotatef(camera.getYrot(), 0.0f, 1.0f, 0.0f);

        // Set the height of the cammera to include the height of the terrain
        //camera->setYpos(world->getYforPos(camera->getXpos(),camera->getZpos()));

        // Translate the screen to the position of the camera
        glTranslated((double) -camera.getXpos(), (double) -camera.getYpos(), (double) -camera.getZpos());

        // Draw the map
        map.draw();
        camera.move();

    glPopMatrix();

    // Update the tick
    updateTick();

    // Trap the mouse at center position
    glutWarpPointer(lastx, lasty);

    // Do the buffer Swap
    glutSwapBuffers();
}

/**
 * updateTick()
 * called to update everything
 **/
void Engine::updateTick() {
    // Measure speed
    long currentTime = glutGet(GLUT_ELAPSED_TIME);
    long delta = currentTime - lastTime;

    // Increase the frame count
    frames++;

    // Set up the FPS output string
    char cBuffer[64];
    if (delta >= 1000) {
        // Calculate the FPS
        fps = (double) frames / ((double) delta / (double) 1000);

        // Change the window title to include the FPS
        sprintf(cBuffer, "Open GL - FPS %.1f", fps);
        glutSetWindowTitle(cBuffer);

        // Update the FPS info
        lastTime = currentTime;
        frames = 0;

    }
}

/**
 * run()
 *  - Starts the engine
 **/
void Engine::run() {
    // Clear stencil buffer with zero, increment by one whenever anybody
    // draws into it. When stencil function is enabled, only write where
    // stencil value is zero. This prevents the transparent shadow from drawing
    // over itself
    glStencilOp(GL_INCR, GL_INCR, GL_INCR);
    glClearStencil(0);
    glStencilFunc(GL_EQUAL, 0x0, 0x01);

    // Cull backs of polygons
    glCullFace(GL_BACK);
    glFrontFace(GL_CCW);
    glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_MULTISAMPLE_ARB);

    // Set up lighting
    GLfloat fAmbLight[] = { 0.075f, 0.075f, 0.075f, 0.0f };
    GLfloat fDiffLight[] = { 1.0f, 1.0f, 1.0f, 0.0f };
    GLfloat fSpecLight[] = { 0.25f, 0.25f, 0.25f, 0.0f };
    GLfloat lightPos[] = { -50.0f, 100.0f, 100.0f, 1.0f };

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
    glMaterialfv(GL_FRONT, GL_SPECULAR, fDiffLight);
    glMateriali(GL_FRONT, GL_SHININESS, 128);

    glLightfv(GL_LIGHT0, GL_AMBIENT, fAmbLight);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, fDiffLight);
    glLightfv(GL_LIGHT0, GL_SPECULAR, fSpecLight);
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, fAmbLight);
    glLightModeli(GL_LIGHT_MODEL_COLOR_CONTROL, GL_SEPARATE_SPECULAR_COLOR);

    // Light never changes, put it here
    glLightfv(GL_LIGHT0, GL_POSITION, lightPos);

    glLightModeli(GL_LIGHT_MODEL_COLOR_CONTROL, GL_SEPARATE_SPECULAR_COLOR);

    glutMainLoop();
}

/**
 * stop()
 *  - Stops the engine
 **/
void Engine::stop() {
    exit(0);
}

//Handle user input
void Engine::handleMouseMovement(int x, int y) {
    float diffx = ((float) x - lastx);
    float diffy = ((float) y - lasty);

    camera.setYrot(camera.getYrot() + diffx / 25.0f);
}

void Engine::handleMouseClick(int button, int state, int x, int y) {

}

void Engine::handleKeydown(unsigned char key, int x, int y) {
    if (key == 'w' || key == 'W') {
        camera.setMoveForward(true);
    }

    if (key == 's' || key == 'S') {
        camera.setMoveBackward(true);
    }

    if (key == 'd' || key == 'D') {
        camera.setMoveRight(true);
    }

    if (key == 'a' || key == 'A') {
        camera.setMoveLeft(true);
    }

    if (key == '1') {
        wireframe = !wireframe;

        if (wireframe) glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        else glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }

    if (key == '2') {
        fullscreen = !fullscreen;

        if (fullscreen) glutFullScreen();
        else {
            glutReshapeWindow(WIDTH, HEIGHT);
            glutPositionWindow(0, 0);
        }
    }

    if (key == 27) stop();
}

void Engine::handleKeyup(unsigned char key, int x, int y) {

    if (key == 'w' || key == 'W') {
        camera.setMoveForward(false);
    }

    if (key == 's' || key == 'S') {
        camera.setMoveBackward(false);
    }

    if (key == 'd' || key == 'D') {
        camera.setMoveRight(false);
    }

    if (key == 'a' || key == 'A') {
        camera.setMoveLeft(false);
    }
}

void Engine::handleSpecialKey(int key, int x, int y) {
}
