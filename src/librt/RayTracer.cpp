//------------------------------------------------------------------------------
// Copyright 2015 Corey Toler-Franklin, University of Florida
// RayTracer.h
// Shades the objects in the scene based on information gathered by bouncing
// a ray in the scene and computing ray/surface intersections
//------------------------------------------------------------------------------

#include "RayTracer.h"
#include <assert.h>
#include <stdio.h>
#include <string>
#include "utilities.h"
#include "STImage.h"
#include "Shader.h"
#include "STColor4ub.h"
#include "STVector2.h"

RayTracer::RayTracer(void)
: m_maxLevel(20),
m_intensityThreshold(0.001) {
    pShader = new Shader();
}

RayTracer::~RayTracer() {

}





//------------------------------------------------
// Main raytracing algorithm
// Cast Ray, Compute Intersections, Shade pixel
//-----------------------------------------------

void RayTracer::Run(Scene *pScene, std::string fName, RenderMode mode) {
    // begin 
    std::cout << "Running... " << std::endl;

    // set the shader's render mode
    pShader->SetMode(mode);

    STVector3 lightDir = (300, 300, 150);

    int width = 320;
    int height = 400;
    RGBR_f bkground = pScene->GetBackgroundColor();
    STImage *pImg = new STImage(width, height, STImage::Pixel(bkground.r * 255, bkground.g * 255, bkground.b * 255, bkground.a * 255));

    Ray ray = Ray();

    // TO DO: Proj2 raytracer
    // CAP5705 - Implement the ray tracing algorithm.
    // 1. Cast a ray from the camera into the scene
    // 2. For every object in the scene compute intersections
    // 3. Compute shading for the closest intersections
    //       - no interection means shade to the background color
    //       - one intersection - great compute shading
    //       - otherwise implement any special handling resolve
    //         ambiguities (determine the best choice or throw an exception)
    // 4. Save the output image
    // NOTE: STImage stores colors in pixels in the range 0-255
    // If you compute color channels in a range 0-1 you must convert
    //------------------------------------------------

    ///-----------------------------------------------

    STVector3 rayOrigin = (0, 0, 0);

    //The ray direction is -z
    STVector3 rayDirection = (0, 0, -1);

    Intersection* intersectionPoint = new Intersection();


    //Shader object to compute shading
    Shader* shader = new Shader();

    //Intializing final pixel colors
    RGBR_f shading;

    
    //making a reflective surface
    RGBR_f colorShading = (RGBR_f(0.4, 0.4, 0.4, 1));
    for (int x = 0; x < width; x++) {
        for (int y = 0; y < height; y++) {
            pImg->SetPixel(x, y, STImage::Pixel(colorShading.r * 255, colorShading.g * 255, colorShading.b * 255));
        }
    }
     

    STVector3 startingPoint = (0, 0, 0);
    for (int i = 0; i < width; i++) {
        rayOrigin.x = i;
        rayDirection.x = i;
        for (int j = 0; j < height; j++) {

            startingPoint.x = i;
            startingPoint.y = j;
            intersectionPoint = new Intersection();
            rayOrigin.y = j;
            rayDirection.y = j;
            ray.SetDirection(rayDirection);
            ray.SetOrigin(rayOrigin);

            //this below function call is for special effects of mirror reflection. Uncomment to run mirror reflectance
            //mirrorReflection(lightDir, startingPoint, pImg, pScene);

            if (pScene->FindIntersection(ray, intersectionPoint, true) > 0) {
                shader->SetMode(mode);
                shading = shader->Run(intersectionPoint, pScene->GetLightDirection());
                pImg->SetPixel(i, j, STImage::Pixel(shading.r * 255, shading.g * 255, shading.b * 255));
            }

        }
    }

    // end
    std::cout << "DONE... " << std::endl;

    // save
    pImg->Save(fName);
    std::cout << "saved file " << fName.c_str() << std::endl;
}


//this method checks of the ray from looking direction intersects with mirror surface
STVector3 RayTracer::mirrorIntersect(STVector3 entry, STVector3 dir, STVector3 normal, STVector3 point) {

    STVector3 p1 = (320 + 1, 0, 0);
    STVector3 vector = (point.x - entry.x, point.y - entry.y, point.z - entry.z);
    float n = vector.Dot(vector, normal);
    float d = dir.Dot(dir, normal);
    if (d == 0)
        return p1;
    float t = n / d;
    if (t >= 0) {
        p1.x = entry.x + (t * dir.x);
        p1.y = entry.y + (t * dir.y);
        p1.z = entry.z + (t * dir.z);
    }
    return p1;
}

//this method finds the reflected vector
//i am using the formula r = d - 2(d.n)n

STVector3 RayTracer::findReflectedRay(STVector3 incomingRay, STVector3 normal) {
    STVector3 d = incomingRay;
    STVector3 n = normal;
    d.Normalize();
    n.Normalize();
    float temp = -2 * d.Dot(d, n);
    n.x = n.x*temp;
    n.y = n.y*temp;
    n.z = n.z*temp;
    STVector3 reflectedRay = incomingRay - n;
    return reflectedRay;
}

//this method finds normal of the reflective surface

STVector3 RayTracer::findNormal(STVector3 p1, STVector3 p2, STVector3 p3) {
    STVector3 x1 = p2 - p1;
    STVector3 x2 = p3 - p1;
    x1 = x2.Cross(x1, x2);
    return x1;
}


//This method draws the reflection
void RayTracer::mirrorReflection(STVector3 incomingRay,
        STVector3 initialPoint, STImage *pImg, Scene *pScene) {

    STVector3 lookAtDirection = STVector3(0, 0, -50);
    STVector3 directionVec=STVector3(300,300,0);
    STVector3 reflectiveSurfPoint1 = STVector3(0, 0, -100);
    STVector3 reflectiveSurfPoint2 = STVector3(100, 0, -100);
    STVector3 reflectiveSurfPoint3 = STVector3(100, 100, -100);
    STVector3 surfaceNormal = findNormal(reflectiveSurfPoint1, reflectiveSurfPoint2, reflectiveSurfPoint3);
    Ray ray = Ray();
    STVector3 startPoint = mirrorIntersect(initialPoint, lookAtDirection, surfaceNormal, reflectiveSurfPoint1);
    STVector3 direction = findReflectedRay(incomingRay, surfaceNormal);
    direction.x = directionVec.x;
    direction.y = directionVec.y;
    Intersection *list = new Intersection();
    ray.SetOrigin(startPoint);
    ray.SetDirection(direction);
    Intersection *intersection = new Intersection();
    if (pScene->FindIntersection(ray, intersection, true) > 0) {
        //getting the color of sphere
        RGBR_f color = intersection->color;
        
        //Drawing reflection
        pImg->SetPixel(startPoint.x, startPoint.y, STImage::Pixel(color.r * 255, color.g * 255, color.b * 255));
    }
}
