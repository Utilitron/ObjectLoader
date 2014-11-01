#include <GL/glew.h>
#include <GL/glut.h>

#include "engine.h"

// The engine class to run the game
Engine* engine;

// Screen dimentions
// TODO: This needs to be set in a config file and loaded
int WIDTH = 1024;
int HEIGHT = 768;

/**
 * handleRender
 *  Passes the render event to the engine
 */
void handleRender() {
    engine->render();
}

/**
 * handleIdle
 *  Passes the idle event to the engine
 */
void  handleIdle() {
    glutPostRedisplay();
}

/**
 * handleReshape
 *  Passes the reshape event to the engine
 */
void handleReshape( int width, int height ) {
    engine->reshape(width, height);
}

/**
 * handleMouseMovement
 *  Passes the mouse movement event to the engine
 */
void handleMouseMovement(int x, int y){
    engine->handleMouseMovement(x, y);
}

/**
 * handleMouseClick
 *  Passes the mouse click event to the engine
 */
void handleMouseClick(int button, int state, int x, int y){
    engine->handleMouseClick(button, state, x, y);
}

/**
 * handleKeydown
 *  Passes the key press event to the engine
 */
void handleKeydown(unsigned char key, int x, int y){
    engine->handleKeydown(key, x, y);
}

/**
 * handleKeydown
 *  Passes the key up event to the engine
 */
void handleKeyup(unsigned char key, int x, int y){
    engine->handleKeyup(key, x, y);
}

/**
 * Main
 */
int main(int argc, char* argv[]) {
	// OpenGL Declarations
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH | GLUT_STENCIL);
    glutInitWindowSize(WIDTH,HEIGHT);
    glutCreateWindow("3dGame");

    // Bind the render/idle/reshape events to their handlers
    glutDisplayFunc( handleRender );
    glutIdleFunc( handleIdle );
    glutReshapeFunc( handleReshape );

    // Bind the mouse events to their handlers
    glutMotionFunc(handleMouseMovement); //check for mouse movement
    glutPassiveMotionFunc(handleMouseMovement); //check for mouse movement
    glutMouseFunc(handleMouseClick);

    // Bind the keybord events to their handlers
    glutKeyboardFunc(handleKeydown);
    glutKeyboardUpFunc(handleKeyup);

	glewInit();

    // Initialize the engine and run
    engine = new Engine(WIDTH,HEIGHT);
    engine->run();

    return 0;
}
