//------------------------------------------------------------------------------
// Copyright 2015 Corey Toler-Franklin, University of Florida
// Camera.cpp
// Camera Object - position, up and lookat
//------------------------------------------------------------------------------

#include "Camera.h"
#include <assert.h>
#include <stdio.h>
#include <string>
#include "STMatrix4.h"



Camera::Camera(void)
{
    Reset();
}


Camera::~Camera()
{

}


void Camera::SetUpAndRight(void)
{
    m_Right = STVector3::Cross(m_LookAt - m_Position, m_Up);
    m_Right.Normalize();
    m_Up = STVector3::Cross(m_Right, m_LookAt - m_Position);
    m_Up.Normalize();
}


void Camera::Reset(void)
{
    m_LookAt=STVector3(0.f,0.f,0.f);
    m_Position=STVector3(0.f,0.f,0.f);
    m_Up=STVector3(0.f,1.f,-1.f);

    SetUpAndRight();
}


void Camera::ResetUp(void)
{
    m_Up = STVector3(0.f,1.f,0.f);
    m_Right = STVector3::Cross(m_LookAt - m_Position, m_Up);
    m_Right.Normalize();
    m_Up = STVector3::Cross(m_Right, m_LookAt - m_Position);
    m_Up.Normalize();
}



void Camera::Rotate(float delta_x, float delta_y)
{
    float yaw_rate=1.f;
    float pitch_rate=1.f;

    m_Position -= m_LookAt;
    STMatrix4 m;
    m.EncodeR(-1*delta_x*yaw_rate, m_Up);
    m_Position = m * m_Position;
    m.EncodeR(-1*delta_y*pitch_rate, m_Right);
    m_Position = m * m_Position;

    m_Position += m_LookAt;
}


void Camera::Zoom(float delta_y)
{
    STVector3 direction = m_LookAt - m_Position;
    float magnitude = direction.Length();
    direction.Normalize();
    float zoom_rate = 0.1f*magnitude < 0.5f ? .1f*magnitude : .5f;
    if(delta_y * zoom_rate + magnitude > 0)
    {
        m_Position += (delta_y * zoom_rate) * direction;
    }
}


void Camera::Strafe(float delta_x, float delta_y)
{
    float strafe_rate = 0.05f;

    m_Position -= strafe_rate * delta_x * m_Right;
    m_LookAt   -= strafe_rate * delta_x * m_Right;
    m_Position += strafe_rate * delta_y * m_Up;
    m_LookAt   += strafe_rate * delta_y * m_Up;
}


STVector3 Camera::Position (void)
{
    return(m_Position);
}


STVector3 Camera::LookAt (void)
{
    return(m_LookAt);
}


STVector3 Camera::Up (void)
{
    return(m_Up);
}
