//----------------------------------------------------------------
// Sphere.cpp
//----------------------------------------------------------------
#include "Sphere.h"
#include <assert.h>
#include <stdio.h>
#include <string>
#include "defs.h"
#include <cmath>   

// constructor

Sphere::Sphere(void)
: m_radius(0.5) {
    m_center = STVector3(0, 0, 0);
    m_color= RGBR_f(0,0,0,1);
}

//adding a parametric constructor

Sphere::Sphere(STVector3 center, float radius, RGBR_f color) {
    m_radius = radius;
    m_center = center;
    m_color = color;
}


// clean up here

Sphere::~Sphere() {

}


//----------------------------------------------------------------------------
// Compute the closest intersection point with the ray
// if it an intersection exist, return true; otherwise false
// return the intersection point information in pIntersection
//-----------------------------------------------------------------------------

bool Sphere::FindIntersection(Ray ray, Intersection *pIntersection) {
    bool bFound = false;
   // std::cout<<"Sphere color="<<pIntersection->color.b;
    // TO DO: Proj2 raytracer
    // CAP5705 - Find Intersections.
    // 1. Find intersections with this object along the Ray ray
    // 2. Store the results of the intersection 
    // 3. if found and return true, otherwise, return false
    // NOTE: The IntersectionPoint pIntersection should store:
    // hit point, surface normal, the time t of the ray at the hit point
    // and the surface being hit
    //------------------------------------------------

    //------------------------------------------------------
    pIntersection->color=m_color;
    double a2 = ray.Origin().x;
    double b2 = ray.Origin().y;
    double c2 = ray.Origin().z;
    double a1 = m_center.x;
    double b1 = m_center.y;
    double c1 = m_center.z;
    double a3 = ray.Direction().x - a2;
    double b3 = ray.Direction().y - b2;
    double c3 = ray.Direction().z - c2;
    double A = a3 * a3 + b3 * b3 + c3 * c3;
    double B = 2.0 * (a2 * a3 + b2 * b3 + c2 * c3 - a3 * a1 - b3 * b1 - c3 * c1);
    double C = a2 * a2 - 2 * a2 * a1 + a1 * a1 + b2 * b2 - 2 * b2 * b1 + b1 * b1 +
            c2 * c2 - 2 * c2 * c1 + c1 * c1 - m_radius * m_radius;
    double D = B * B - 4 * A * C;
    if (D < 0) {
        return false;
    }
    double t1 = (-B - sqrt(D)) / (2.0 * A);

    STVector3 firstPoint = STVector3(ray.Origin().x * (1 - t1) + t1 * ray.Direction().z,
            ray.Origin().y * (1 - t1) + t1 * ray.Direction().y,
            ray.Origin().z * (1 - t1) + t1 * ray.Direction().z);
    STVector3 normal;
    
    
    if (D == 0) {
        pIntersection->color=m_color;
        pIntersection->point = firstPoint;
        normal = (firstPoint - m_center) / m_radius;
        pIntersection->normal = normal;
    }
    double t2 = (-B + sqrt(D)) / (2.0 * A);
   
    if (std::abs(t1 - 0.5) < std::abs(t2 - 0.5)) {
         pIntersection->color=m_color;
        pIntersection->point = firstPoint;
        normal = (firstPoint - m_center) / m_radius;
        pIntersection->normal = normal;
        return true;
    }
     pIntersection->color=m_color;
    pIntersection->point = firstPoint;
    normal = (firstPoint - m_center) / m_radius;
    pIntersection->normal = normal;
    return true;

    return (bFound);
}

