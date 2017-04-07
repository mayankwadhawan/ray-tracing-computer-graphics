//------------------------------------------------------------------------------------------------
// Corey Toler-Franklin
// 10 February 2006
// Copyright 2006
//
// Shader.cpp
// Shader class - computes shading functions
//------------------------------------------------------------------------------------------------

#include "Shader.h"
#include <assert.h>
#include "Intersection.h"
#include "STVector2.h"

Shader::Shader(void)
: m_mode(LAMBERTIAN) {
}

void Shader::SetMode(RenderMode mode) {
    m_mode = mode;
}


// Runs the shader according to the specified render mode

RGBR_f Shader::Run(Intersection *pIntersection, STVector3 lightDirection) {
    RGBR_f color;
    switch (m_mode) {
        case LAMBERTIAN:
            color = Lambertian(pIntersection, lightDirection);
            break;
        case PHONG:
            color = Phong(pIntersection, lightDirection);
            break;
        default:
            color = Lambertian(pIntersection, lightDirection);
            break;
    }

    // TO DO: Proj2 raytracer
    // CAP5705 - Add special effects.
    // 1. Add calls to your new special effects function to the switch statement
    // 2. Update the RenderMode structure in def.h to flag these
    //---------------------------------------------------------
    //---------------------------------------------------------

    return (color);
}


// Implements diffuse shading using the lambertian lighting model

RGBR_f Shader::Lambertian(Intersection *pIntersection, STVector3 lightDirection) {
    assert(pIntersection);
    // assert(lightDirection);
    // TO DO: Proj2 raytracer
    // CAP5705 - Add shading lambertian shading.
    // 1. Lambertian shading is the dot product of the the
    //    normal and light direction
    // 2. Do not forget the multiply your albedo by the result
    //---------------------------------------------------------

    //---------------------------------------------------------

    /* I have used the formula L = Ka * Ia + Kd * I * max(0,n.l)
     * L is final pixel color
     * ka is surface ambient coefficient
     * Ia is ambient light
     * kd is diffuse coefficient or surface color
     * I is Light Intensity
     * n is unit vector of surface normal
     * l is light directions
     * 
     * Also, I have included some ambient light to remove black shading.
     * There is always ambient life in real world situations. Sphere would
     * appear more realistic.
     * 
     * */

    //Initializing Ia
    RGBR_f Ia = RGBR_f(0.25, 0.25, 0.25, 1);
    //Initializing final pixel color
    RGBR_f color;

    //Getting sphere color from intersection
    RGBR_f kd = pIntersection->color;

    //getting normal vector of intersection point
    STVector3 normalVector = pIntersection->normal;

    //Computing dot product of n and l -> (n.l))
    float dotproduct = normalVector.Dot(normalVector, lightDirection);
   
    //finding max(0,n.l)
    float max;
    if (dotproduct > 0) {
        max = dotproduct;
    } else {
        max = 0;
    }

    //finding final color (includes ambient light)
    color.r = kd.r * Ia.r + kd.r*max;
    color.g = kd.g * Ia.g + kd.g*max;
    color.b = kd.b * Ia.b + kd.b*max;

    //value of final color should not be greater than 1
    //These conditions will set it to 1 if they are greater
    if (color.r > 1) {
        color.r = 1;
    }
    if (color.g > 1) {
        color.g = 1;
    }
    if (color.b > 1) {
        color.b = 1;
    }
    return (color);
}


// Implements diffuse shading using the lambertian lighting model

RGBR_f Shader::Phong(Intersection *pIntersection, STVector3 lightDirection) {

    assert(pIntersection);
    //assert(lightDirection);

    // TO DO: Proj2 raytracer
    // CAP5705 - Add Phong shading.
    // 1. Implement the phong shading equation here
    // 2. Remember to add any attributes you might need for shading to 
    //    your surface objects as they are passed in with the pIntersection
    //---------------------------------------------------------
    //---------------------------------------------------------

    /* I have used the formula L = Ka * Ia + kd * I * max(0,n·l) + ks * I * max(0, n·h)^p
     * ka is surface ambient coefficient
     * Ia is ambient light
     * kd is diffuse coefficient or surface color
     * I is Light Intensity
     * n is unit vector of surface normal
     * l is light directions
     * ks is specular coefficient
     * h is half vector. This is bisector of angle between light direction and view direction
     * p is Phong exponent. p>1 will make specular term decrease faster.
     * 
     * Also, I have included some ambient light to remove black shading.
     * There is always ambient life in real world situations. Sphere would
     * appear more realistic.
     * 
     * */

    
    
    //Final pixel color
    RGBR_f result;
    
    //Light intensity
    RGBR_f I = RGBR_f(0.9, 0.9, 0.9, 1);

    //view direction
    STVector3 v = STVector3(0.0, 0.0, -1);

    //Initializing Ia or Ambient light
    RGBR_f Ia = RGBR_f(0.25, 0.25, 0.25, 1);

    //Getting sphere color from intersection
    RGBR_f kd = pIntersection->color;

    //Initilizing lambertian and specular part
    RGBR_f lambPartColor, specTerm;

    //Phong exponent
    int power = 50;
    
    //Initializing specular light color
    RGBR_f ks = RGBR_f(1, 1, 1, 1);

    //normaliing light vector
    lightDirection.Normalize();
    
    //normalizing view vector
    v.Normalize();
    
    //fetching normal vector of intersection point
    STVector3 normalVector = pIntersection->normal;


    //computing dot product of n and l -> (n.l)
    float dotproduct = normalVector.Dot(normalVector, lightDirection);

    float max;

    //determining max(0,n.l)
    if (dotproduct > 0) {
        max = dotproduct;
    } else {
        max = 0;
    }

    //setting the lambertian shading part
    lambPartColor.r = kd.r*max;
    lambPartColor.g = kd.g*max;
    lambPartColor.b = kd.b*max;

    //Computing half vector
    STVector3 h = lightDirection - v;

    //normalizing half vector
    h.Normalize();
    
    //computing dot product of n and h - > (n.h)
    float dp = normalVector.Dot(normalVector, h);

    //computing max(0, n·h)^p
    float dpNew = pow((dp > 0 ? dp : 0), power);
    
    //determining ks * I * max(0, n·h)^p
    specTerm.r = I.r * ks.r*dpNew;
    specTerm.g = I.g * ks.g*dpNew;
    specTerm.b = I.b * ks.b*dpNew;

    //Computing final pixel color
    result.r = kd.r * Ia.r + lambPartColor.r + specTerm.r;
    result.g = kd.g * Ia.g + lambPartColor.g + specTerm.g;
    result.b = kd.b * Ia.b + lambPartColor.b + specTerm.b;
    
    //value of final color should not be greater than 1
    //These conditions will set it to 1 if they are greater
    if (result.r > 1) {
        result.r = 1;
    }
    if (result.g > 1) {
        result.g = 1;
    }
    if (result.b > 1) {
        result.b = 1;
    }
    return result;
}

Shader::~Shader() {
}


// TO DO: Proj2 raytracer
// CAP5705 - Add shading functions for special effects.
// 1. Declare functions for your special effects in the .h file
// 2. See the Run function to see when each shading function is called
//---------------------------------------------------------
//---------------------------------------------------------

//reflection function code present in RayTracer.cpp
