#include "StdAfx.h"
#include "TranformationMgr.h"
#include <GL/GL.h>

CTranformationMgr::CTranformationMgr(void) 
{
    mdRotation[0]=mdRotation[5]=mdRotation[10]=mdRotation[15] = 1.0f;
    mdRotation[1]=mdRotation[2]=mdRotation[3]=mdRotation[4] = 0.0f;
    mdRotation[6]=mdRotation[7]=mdRotation[8]=mdRotation[9] = 0.0f;
    mdRotation[11]=mdRotation[12]=mdRotation[13]=mdRotation[14] = 0.0f;

    mfRot[0]=mfRot[1]=mfRot[2]=0.0f;
}


CTranformationMgr::~CTranformationMgr(void)
{
}

void CTranformationMgr::Rotate(float fx_i, float fy_i, float fz_i )
{
     mfRot[0] = fx_i;
     mfRot[1] = fy_i;
     mfRot[2] = fz_i;

     glMatrixMode( GL_MODELVIEW );
     glLoadMatrixd( mdRotation );
     glRotated( mfRot[0], 1.0f, 0,0 );
     glRotated( mfRot[1], 0, 1.0f,0 );
     glRotated( mfRot[2], 0, 0,1.0f );

     glGetDoublev( GL_MODELVIEW_MATRIX, mdRotation );
     glLoadIdentity();
}

void CTranformationMgr::ResetRotation()
{
    mdRotation[0]=mdRotation[5]=mdRotation[10]=mdRotation[15] = 1.0f;
    mdRotation[1]=mdRotation[2]=mdRotation[3]=mdRotation[4] = 0.0f;
    mdRotation[6]=mdRotation[7]=mdRotation[8]=mdRotation[9] = 0.0f;
    mdRotation[11]=mdRotation[12]=mdRotation[13]=mdRotation[14] = 0.0f;
}