//------------------------------------------------------------------------------
// Copyright 2015 Corey Toler-Franklin, University of Florida
// Scene.cpp
// Stores all the objects - lights, camera and surfaces for setting up the scene.
//------------------------------------------------------------------------------


#include "Scene.h"
#include <assert.h>
#include <stdio.h>
#include <string>
#include "Intersection.h"
#include "Surface.h"
#include "Light.h"
#include "Sphere.h"

Scene::Scene(void)
: m_background(RGBR_f(0, 0, 0, 1)) {
    // init camera
    m_pCamera = new Camera();

}

Scene::~Scene() {
}

void Scene::SetBackgroundColor(RGBR_f color) {
    m_background = color;
}

RGBR_f Scene::GetBackgroundColor(void) {
    return (m_background);
}

void Scene::AddLight(Light lightin) {
    m_lights.push_back(lightin);
}

void Scene::AddSurface(Surface *pSurfacein) {
    m_surfaceList.push_back(pSurfacein);
}

Camera *Scene::GetCamera(void) {
    return (m_pCamera);
}


// computes the direction of the light in the scene
// and returns it

STVector3 Scene::GetLightDirection(void) {
    STVector3 lightDirection;

    // TO DO: Proj2 raytracer
    // CAP5705 - Compute light direction.
    // 1. Return the direction of the light in the scene
    //---------------------------------------------------------
    //---------------------------------------------------------
    if (!m_lights.empty()) {
        Light light = m_lights[0];
        lightDirection = light.GetPosition();
        lightDirection.Normalize();
    }
    return (lightDirection);
}


// Select the closest intersection and return the number of points
// very close to this one

int Scene::SelectClosest(IntersectionList *pIntersectionList, Intersection *pIntersection) {

    int numPoints = 0;

    // TO DO: Proj2 raytracer
    // CAP5705 - Find the closest intersection.
    // 1. Find the closest (over all objects) intersection and update pIntersection
    // 2. return the number of really close points if there is a cluster
    //---------------------------------------------------------

    //---------------------------------------------------------

    return (numPoints);
}


//-----------------------------------------------------
// Find the intersection of the ray with objects in the scene
// Return the closest intersection
//-----------------------------------------------------

int Scene::FindClosestIntersection(Ray ray, Intersection *pIntersection) {
    int numPoints = 0;
    numPoints = FindIntersection(ray, pIntersection, false);
    return (numPoints);
}


//-----------------------------------------------------
// Find the intersection of the ray with objects in the scene
// Checks for the closest intersections and retuns the number
// of close intersections found
// Updates the pIntersection 
//   -if bAny is true, return the first intersection found
//   - if bAny is false, return the closest intersection
// 
//-----------------------------------------------------

int Scene::FindIntersection(Ray ray, Intersection *pIntersection, bool bAny) {
    int numPoints = 0;



    // SurfaceList::const_iterator iter = m_surfaceList.begin();
    // SurfaceList::const_iterator end  = m_surfaceList.end();

    // for (; iter != end; ++iter) {
    //std::cout<<;
    // TO DO: Proj2 raytracer
    // CAP5705 - Find Intersections.
    // 1. Find intersections with objects in the scene
    // 2. If bAny is true, return as soon as you find one
    //    Do not forget to update the pIntersection before returning
    // 3. Othersize just add to the list of intersections
    //---------------------------------------------------------

    // }

    //flag to check for intersections
    bool intersectionFound = false;

    //I am storing the closest intersection point by determining the point with
    //minimum z index and sending that point back

    //declaring new intersection point
    Intersection* intersectionPoint;


    //Note: please note that ray direction is -z. Therefore, closest objects 
    //in the scene will have highest z value

    //Initializing maxZIndex to minimum integer value. This variable will 
    //help us determining closest intersection point.
    float maxZIndex = -32767;

    //Loop of objects in scene. Also, I will determine closest intersection in case of 
    //multiple intersections.
    for (int i = 0; i < m_surfaceList.size(); i++) {
        intersectionPoint = new Intersection();

        //fetching one object
        Surface* surface = m_surfaceList[i];
         if(i==3){
               // std::cout<<"hello";
            }
        //finding if the input ray intersects this object
        if (surface->FindIntersection(ray, intersectionPoint)) {
            //updating number of intersection points
            numPoints++;
            //this statement will check for multiple intersection.
            //Comparing with maxZIndex will ensure that I have closest intersection
            if (intersectionPoint->point.z > maxZIndex) {
                //intersection found set to true
                intersectionFound = true;
                
                //updating maxZIndex to z index of intersection point
                maxZIndex = intersectionPoint->point.z;
                
                //changing intersection parameters to closest surface
                pIntersection->color = intersectionPoint->color;
                pIntersection->normal = intersectionPoint->normal;
                pIntersection->point = intersectionPoint->point;
            }
        }
    }

    if (intersectionFound) {
        return numPoints;
    }
    // TO DO: Proj2 raytracer
    // CAP5705 - Find Intersections.
    // 1. Find the closest intersection along the ray in the list
    //---------------------------------------------------------
    //---------------------------------------------------------

    return (numPoints);
}


//-----------------------------------------------------
// clear the scene by removing surfaces
//-----------------------------------------------------

void Scene::Clear(void) {
    SurfaceList::iterator iter = m_surfaceList.begin();
    SurfaceList::iterator end = m_surfaceList.end();

    // delete objects
    for (; iter != end; ++iter) {
        delete *iter;
        *iter = NULL;
    }

    // clean up
    m_surfaceList.clear();
}