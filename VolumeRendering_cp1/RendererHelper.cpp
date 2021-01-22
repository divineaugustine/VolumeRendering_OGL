#include "StdAfx.h"
#include "RendererHelper.h"

#pragma comment ( lib, "OpenGL32.lib" )
#pragma comment ( lib, "glew32.lib" )


GLfloat dOrthoSize = 1.0f;

CRendererHelper::CRendererHelper(void)
{
}


CRendererHelper::~CRendererHelper(void)
{
}


bool CRendererHelper::Initialize( HDC hContext_i )
{
    //Setting up the dialog to support the OpenGL.
    PIXELFORMATDESCRIPTOR stPixelFormatDescriptor;
    memset( &stPixelFormatDescriptor, 0, sizeof( PIXELFORMATDESCRIPTOR ));
    stPixelFormatDescriptor.nSize = sizeof( PIXELFORMATDESCRIPTOR );
    stPixelFormatDescriptor.nVersion = 1;
    stPixelFormatDescriptor.dwFlags = PFD_DOUBLEBUFFER | PFD_SUPPORT_OPENGL | PFD_DRAW_TO_WINDOW ;
    stPixelFormatDescriptor.iPixelType = PFD_TYPE_RGBA;
    stPixelFormatDescriptor.cColorBits = 24;
    stPixelFormatDescriptor.cDepthBits = 32;
    stPixelFormatDescriptor.cStencilBits = 8;
    stPixelFormatDescriptor.iLayerType = PFD_MAIN_PLANE ;
    int nPixelFormat = ChoosePixelFormat( hContext_i, &stPixelFormatDescriptor ); //Collect the pixel format.

    if( nPixelFormat == 0 )
    {
        AfxMessageBox( _T( "Error while Choosing Pixel format" ));
        return false;
    }
    //Set the pixel format to the current dialog.
    if( !SetPixelFormat( hContext_i, nPixelFormat, &stPixelFormatDescriptor ))
    {
        AfxMessageBox( _T( "Error while setting pixel format" ));
        return false;
    }

    //Create a device context.
    m_hglContext = wglCreateContext( hContext_i );
    if( !m_hglContext )
    {
        AfxMessageBox( _T( "Rendering Context Creation Failed" ));
        return false;
    }
    //Make the created device context as the current device context.
    BOOL bResult = wglMakeCurrent( hContext_i, m_hglContext );
    if( !bResult )
    {
        AfxMessageBox( _T( "wglMakeCurrent Failed" ));
        return false;
    }

    glClearColor( 0.0f,0.0f, 0.0f, 0.0f );

    glewInit();
    if(GL_TRUE != glewGetExtension("GL_EXT_texture3D"))
    {
        AfxMessageBox( _T( "3D texture is not supported !" ));
        return false;
    }

    return true;
}


 void CRendererHelper::Resize(unsigned int nWidth_i, unsigned int nHeight_i )
 {
     //Find the aspect ratio of the window.
     GLdouble AspectRatio = ( GLdouble )(nWidth_i) / ( GLdouble )(nHeight_i ); 
     //glViewport( 0, 0, cx , cy );
     glViewport( 0, 0, nWidth_i, nHeight_i );
     glMatrixMode( GL_PROJECTION );
     glLoadIdentity();

     //Set the orthographic projection.
     if( nWidth_i <= nHeight_i )
     {
         glOrtho( -dOrthoSize, dOrthoSize, -( dOrthoSize / AspectRatio ) ,
             dOrthoSize / AspectRatio, 2.0f*-dOrthoSize, 2.0f*dOrthoSize );
     }
     else
     {
         glOrtho( -dOrthoSize * AspectRatio, dOrthoSize * AspectRatio, 
             -dOrthoSize, dOrthoSize, 2.0f*-dOrthoSize, 2.0f*dOrthoSize );
     }

     glMatrixMode( GL_MODELVIEW );
     glLoadIdentity();
 }


 // Macro to draw the quad.
 // Performance can be achieved by making a call list.
 // To make it simple i am not using that now :-)
  #define MAP_3DTEXT( TexIndex ) \
            glTexCoord3f(0.0f, 0.0f, ((float)TexIndex+1.0f)/2.0f);  \
        glVertex3f(-dOrthoSize,-dOrthoSize,TexIndex);\
        glTexCoord3f(1.0f, 0.0f, ((float)TexIndex+1.0f)/2.0f);  \
        glVertex3f(dOrthoSize,-dOrthoSize,TexIndex);\
        glTexCoord3f(1.0f, 1.0f, ((float)TexIndex+1.0f)/2.0f);  \
        glVertex3f(dOrthoSize,dOrthoSize,TexIndex);\
        glTexCoord3f(0.0f, 1.0f, ((float)TexIndex+1.0f)/2.0f);  \
        glVertex3f(-dOrthoSize,dOrthoSize,TexIndex);

void CRendererHelper::Render()
{
    float fFrameCount = (float)data.dim.z;
    glClear( GL_COLOR_BUFFER_BIT  | GL_DEPTH_BUFFER_BIT );

    glEnable( GL_ALPHA_TEST );
    glAlphaFunc( GL_GREATER, 0.05f );

    glEnable(GL_BLEND);
    glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );

    glMatrixMode( GL_TEXTURE );
    glLoadIdentity();

    // Translate and make 0.5f as the center 
    // (texture co ordinate is from 0 to 1. so center of rotation has to be 0.5f)
    glTranslatef( 0.5f, 0.5f, 0.5f );

    // A scaling applied to normalize the axis 
    // (Usually the number of slices will be less so if this is not - 
    // normalized then the z axis will look bulky)
    // Flipping of the y axis is done by giving a negative value in y axis.
    // This can be achieved either by changing the y co ordinates in -
    // texture mapping or by negative scaling of y axis
    glScaled( (float)data.dim.x /(float)data.dim.x,
        -1.0f*(float)data.dim.x /(float)(float)data.dim.y,
        (float)data.dim.x /(float)data.dim.z);

    // Apply the user provided transformations
    glMultMatrixd(rotationMatrix.ptr());
    
    glTranslatef( -0.5f,-0.5f, -0.5f );

    glEnable(GL_TEXTURE_3D);
    glBindTexture( GL_TEXTURE_3D, data.texture);
    for ( float fIndx = -1.0f; fIndx <= 1.0f; fIndx+=0.01f )
    {
        glBegin(GL_QUADS);
            MAP_3DTEXT( fIndx );
        glEnd();
     }
}