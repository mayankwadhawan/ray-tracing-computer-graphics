//--------------------------------------------------------
// CAP5705 Computer Graphics
// University of Florida
// Copyright 2015 Corey Toler-Franklin
//--------------------------------------------------------



// System
#include <string>
#include <algorithm>
using namespace std;

// GLEW
#define GLEW_STATIC
#include "stglew.h"
#include <stdio.h>
#include <string.h>
#include <map>
#include "Scene.h"
#include "RayTracer.h"
#include "Light.h"
#include "Sphere.h"
#include "Triangle.h"
#include "defs.h"


// globals
//---------------------------------
// scene
Scene *pScene = NULL; // scene geometry and lights
RayTracer *pRayTracer = NULL; // runs ray tracing algorithm
RenderMode mode = LAMBERTIAN;

// mouse
int gPreviousMouseX = -1;
int gPreviousMouseY = -1;
int gMouseButton = -1;

// Window size, kept for screenshots
static int gWindowSizeX = 0;
static int gWindowSizeY = 0;


// Function Prototypes
// TO DO: Proj2 raytracer
// Nothing to do here but note:
// These are not actually used in this
// app unless you were to create a glut
// window loop in the main and add a display callback
// You do not need this but it is available
//--------------------------------------
void MouseMotionCallback(int x, int y);
void MouseCallback(int button, int state, int x, int y);
void KeyCallback(unsigned char key, int x, int y);
void SpecialKeyCallback(int key, int x, int y);
void ReshapeCallback(int w, int h);
void Setup(void);
void EnvironmentMapping(void);









//---------------------------------------------------------------------
// Scene functions
//---------------------------------------------------------------------
// Creates the scene
//

void Setup(void) {

    // init the scene
    pScene = new Scene();

    // TO DO: Proj2 raytracer
    // CAP5705 - Set up your scene.
    // Use the variable pScene to set parameters
    // 1. change background color
    // 2. add lights
    // 3. add objects
    // 4. add translation and rotation operations to place objects
    //------------------------------------------------
    //adding background color in scene
    RGBR_f backColor = RGBR_f(0.1, 0.1, 0.1, 1);
    pScene->SetBackgroundColor(backColor);

    //adding light in scene
    RGBR_f lightColor = RGBR_f(0.9, 0.9, 0.9, 1);
    STVector3 lightPosition = STVector3(0, 1.5, 1);

    Light light = Light(lightPosition, lightColor, "1");
    pScene->AddLight(light);

    //Note: since ray direction is -z, therefore objects with higher z values are closer

    //Sphere used for reflectance. Uncomment this to start mirror reflectance
    /*
    STVector3 center = STVector3(175,175, -50);
    float radius = 50;
    RGBR_f color = RGBR_f(0, 0.3, 0.3, 1);
    Surface* surface = new Sphere(center, radius, color);
    pScene->AddSurface(surface);
     */
    
    //comment below 3 spheres and triangle to start reflectance
 
    //Adding a sphere in the scene.(color red) - This sphere is closest
    STVector3 center = STVector3(100, 100, -50);
    float radius = 55;
    RGBR_f color = RGBR_f(0.6, 0, 0, 1);
    Surface* surface = new Sphere(center, radius, color);
    pScene->AddSurface(surface);

    //Adding a sphere in the scene(color green) - this sphere is in between red sphere and blue sphere
    center = STVector3(160, 150, -150);
    radius = 45;
    RGBR_f color2 = RGBR_f(0, 0.6, 0, 1);
    surface = new Sphere(center, radius, color2);
    pScene->AddSurface(surface);

    //Adding a sphere in the scene(color blue) - This sphere is farthest away
    center = STVector3(220, 190, -250);
    radius = 50;
    RGBR_f color3 = RGBR_f(0, 0, 0.6, 1);
    surface = new Sphere(center, radius, color3);
    pScene->AddSurface(surface);

    
    //Adding a triangle to the scene (purple) - This triangle is behind red and ahead of green
     STVector3 vertex1 = STVector3(125, 100, -100);
     STVector3 vertex2 = STVector3(200, 150, -100);
     STVector3 vertex3 = STVector3(225, 50, -100);
     RGBR_f color4 = RGBR_f(1,0.1,1, 1);
     Surface* surface4 = new Triangle(vertex1,vertex2,vertex3,color4);
     pScene->AddSurface(surface4);
    //------------------------------------------------

    // init a ray tracer object
    pRayTracer = new RayTracer();

}


//
// Reshape the window and record the size so
// that we can use it for screenshots.
//

void ReshapeCallback(int w, int h) {
    gWindowSizeX = w;
    gWindowSizeY = h;

    glViewport(0, 0, gWindowSizeX, gWindowSizeY);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    // Set up a perspective projection
    float aspectRatio = (float) gWindowSizeX / (float) gWindowSizeY;
    gluPerspective(30.0f, aspectRatio, .1f, 10000.0f);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void SpecialKeyCallback(int key, int x, int y) {
    switch (key) {
        case GLUT_KEY_LEFT:
            pScene->GetCamera()->Strafe(10, 0);
            break;
        case GLUT_KEY_RIGHT:
            pScene->GetCamera()->Strafe(-10, 0);
            break;
        case GLUT_KEY_DOWN:
            pScene->GetCamera()->Strafe(0, -10);
            break;
        case GLUT_KEY_UP:
            pScene->GetCamera()->Strafe(0, 10);
            break;
        default:
            break;
    }
    glutPostRedisplay();
}

void KeyCallback(unsigned char key, int x, int y) {

    switch (key) {
        case 's':
        {
            //
            // Take a screenshot, and save as screenshot.jpg
            //
            STImage* screenshot = new STImage(gWindowSizeX, gWindowSizeY);
            screenshot->Read(0, 0);
            screenshot->Save("../../data/images/screenshot.jpg");
            delete screenshot;
        }
            break;
        case 'r':
            pScene->GetCamera()->Reset();
            break;
        case 'u':
            pScene->GetCamera()->ResetUp();
            break;
        case 'q':
            exit(0);
        default:
            break;
    }

    glutPostRedisplay();
}

/**
 * Mouse event handler
 */
void MouseCallback(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON
            || button == GLUT_RIGHT_BUTTON
            || button == GLUT_MIDDLE_BUTTON) {
        gMouseButton = button;
    } else {
        gMouseButton = -1;
    }

    if (state == GLUT_UP) {
        gPreviousMouseX = -1;
        gPreviousMouseY = -1;
    }
}

/**
 * Mouse active motion callback (when button is pressed)
 */
void MouseMotionCallback(int x, int y) {
    if (gPreviousMouseX >= 0 && gPreviousMouseY >= 0) {
        //compute delta
        float deltaX = x - gPreviousMouseX;
        float deltaY = y - gPreviousMouseY;
        gPreviousMouseX = x;
        gPreviousMouseY = y;

        //orbit, strafe, or zoom
        if (gMouseButton == GLUT_LEFT_BUTTON) {
            pScene->GetCamera()->Rotate(deltaX, deltaY);
        } else if (gMouseButton == GLUT_MIDDLE_BUTTON) {
            pScene->GetCamera()->Strafe(deltaX, deltaY);
        } else if (gMouseButton == GLUT_RIGHT_BUTTON) {
            pScene->GetCamera()->Zoom(deltaY);
        }

    } else {
        gPreviousMouseX = x;
        gPreviousMouseY = y;
    }

}




//-----------------------------------------------
// Proj2 Ray Tracer
// This function follows the main
// logic of your rendering program.
// No command line inputs are necessary.
//-----------------------------------------------

int main(int argc, char** argv) {

    // TO DO: Proj2 raytracer
    // CAP5705 - Set the render mode.
    // 1. Add a commandline parameter for the render mode
    // 2. Remove the global variable
    //------------------------------------------------
    mode = PHONG;
    //------------------------------------------------

    // Initializes the scene
    Setup();

    // run the ray tracer
    pRayTracer->Run(pScene, "output.png", mode);


    return 0;
}


#pragma endregion