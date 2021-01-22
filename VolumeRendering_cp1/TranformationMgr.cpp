#include "StdAfx.h"
#include "TranformationMgr.h"
#include <GL/GL.h>

CTranformationMgr::CTranformationMgr(void) 
{
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
     glLoadMatrixd(mdRotation.ptr());
     glRotated( mfRot[0], 1.0f, 0,0 );
     glRotated( mfRot[1], 0, 1.0f,0 );
     glRotated( mfRot[2], 0, 0,1.0f );

     glGetDoublev( GL_MODELVIEW_MATRIX, mdRotation.ptr());
     glLoadIdentity();
}

void CTranformationMgr::ResetRotation()
{
    mdRotation.LoadIdentity();
}