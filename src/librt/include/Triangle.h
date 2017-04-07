//------------------------------------------------------------------------------
// Copyright 2015 Corey Toler-Franklin, University of Florida
// Triangle.h
// Defines a triangle surface enclosed by three points m_a, m_b, m_c
//-----------------------------------------------------------------------------


#ifndef __TRIANGLE_H__
#define __TRIANGLE_H__



#include "Surface.h"
#include "STVector3.h"
#include "Ray.h"
#include "Intersection.h"

class Triangle : public Surface {
public:
    Triangle(void);

    Triangle(STVector3 vertex1, STVector3 vertex2, STVector3 vertex3, RGBR_f color);

    ~Triangle(void);

    bool FindIntersection(Ray ray, Intersection * pIntersection);



private:


    // vertices
    STVector3 m_a;
    STVector3 m_b;
    STVector3 m_c;


    // linear systems
    bool IntersectionSolver(Ray ray, STVector3 A, STVector3 B, STVector3 C, double u, double v, double w);

    STVector3 ComputeNormalVector(void);


    // TO DO: Proj2 raytracer
    // CAP5705 - Add object specific properties.
    // 1. Add any object specific properties you need
    //    to create your special effects
    // 2. Remember to initialize these properties in the .cpp file
    //---------------------------------------------------------
    //---------------------------------------------------------


};


#endif //__TRIANGLE_H__

