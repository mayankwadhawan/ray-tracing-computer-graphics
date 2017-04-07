//----------------------------------------------------------------
// Triangle.cpp
// Copyright: Corey Toler-Franklin, University of Florida
// 
// Triangle surface class
// This class is represented by the surface enclosed by 3 points:m_a, m_b, m_c
//----------------------------------------------------------------
#include "Triangle.h"
#include "LinearSolver.h"
#include "defs.h"



// contructor
Triangle::Triangle(void)
        : Surface()
{

}
// creating a new constructor to initialize the vertices

Triangle::Triangle(STVector3 vertex1, STVector3 vertex2, STVector3 vertex3,RGBR_f color)
: Surface() {

    m_a = vertex1;
    m_b = vertex2;
    m_c = vertex3;
    m_color = color;
}


// clean up
Triangle::~Triangle()
{

}



//-----------------------------------------------------------------
// Uses barycentric coordinates to solve for the interscetion
// of the Ray ray with the surface in the plane of A, B, C
// Updates the variables u, v, and w with the solution if found
// Returns true if found, otherwise false
//-----------------------------------------------------------------
bool Triangle::IntersectionSolver(Ray ray, STVector3 A, STVector3 B, STVector3 C, double u, double v, double w)
{
    LinearSolver L;
    bool bFoundSolution = false;
    
    // TO DO: Proj2 raytracer
    // CAP5705 - Solve for intersections.
    // 1. Use barycentric coordinates and linear equations to solve for intersections
    // 2. If a solution is found return true, otherwise, return false
    // 3. If a solution is found, u, v and w are updated; otherwise they are useless
    //------------------------------------------------

    //------------------------------------------------------

    return(bFoundSolution);
}



//----------------------------------------------------------------------------
// Compute the closest intersection point with the ray
// If an intersection exist, return true; otherwise false
// return the intersection point information in pIntersection
//-----------------------------------------------------------------------------
bool Triangle::FindIntersection (Ray ray, Intersection *pIntersection)
{
    bool bFound = false;
    // TO DO: Proj2 raytracer
    // CAP5705 - Find Intersections.
    // 1. Find intersections with this object along the Ray ray
    //    Use barycentric coordinates and linear equations
    // 2. Store the results of the intersection 
    // 3. If found return true, otherwise, return false
    // NOTE: The Intersection pIntersection should store:
    // hit point, surface normal, the time t of the ray at the hit point
    // and the surface being hit
    //------------------------------------------------

    //------------------------------------------------------
    STVector3 normal=ComputeNormalVector();
    STVector3 directionRay = ray.Direction();
    STVector3 a = m_a;
    STVector3 point1 = a - ray.Origin();
    double term2 = point1.Dot(point1, normal);
    double term3 = directionRay.Dot(directionRay, normal);
    double term4 = term2 / term3;
    STVector3 var1;
    var1 = ray.Origin();
    var1.z = ray.Origin().z + directionRay.z*term4;
    STVector3 vector21 = m_b - m_a;
    STVector3 var2 = var1 - m_a;
    STVector3 cProduct = vector21.Cross(vector21, var2);
    float cDot1 = cProduct.Dot(cProduct, normal);

    STVector3 vector32 = m_c - m_b;
    STVector3 diff12 = var1 - m_b;
    STVector3 cross2 = vector32.Cross(vector32, diff12);
    float var3 = cross2.Dot(cross2, normal);

    STVector3 verctor13 = m_a - m_c;
    STVector3 vectorVar13 = var1 - m_c;
    STVector3 cross3 = verctor13.Cross(verctor13, vectorVar13);
    float var4 = cross3.Dot(cross3, normal);
    pIntersection->normal = normal;
    if (cDot1 > 0 && var3 > 0 && var4 > 0) {
        pIntersection->point = var1;
        pIntersection->color=m_color;
        return true;
    } else {
        return false;
    }
    //------------------------------------------------------

    return(bFound);
}

//-------------------------------------------------
// Computes the normal vector
//-------------------------------------------------
STVector3 Triangle::ComputeNormalVector(void)
{
    STVector3 normal(0,0,1);

    // TO DO: Proj2 raytracer
    // CAP5705 - Compute the surface normal.
    // 1. Compute the surface surface normal to the
    // plane whose points are m_a, m_b, and m_c
    //------------------------------------------------

    //---------------------------------------------------
    STVector3 c1 = m_b - m_a;
    STVector3 c2 = m_c - m_a;
    normal = c1.Cross(c1, c2);
    normal.Normalize();
    return normal;
}


// TO DO: Proj2 raytracer
// CAP5705 - Add object specific properties.
// 1. Add any object specific properties you need
//    to create your special effects (e.g. specularity, transparency...)
// 2. Remember to declare these in your .h file
// 
//---------------------------------------------------------
//---------------------------------------------------------