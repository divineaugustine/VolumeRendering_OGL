#include "StdAfx.h"
#include "RawDataProcessor.h"

#include <GL\glew.h>
#include <vector>

CRawDataProcessor::CRawDataProcessor(void) 
{
}


CRawDataProcessor::~CRawDataProcessor(void)
{
    // If not initialized, then this will be zero. So no checking is needed.
    if( 0 != data.texture)
    {
        glDeleteTextures( 1, (GLuint*)&data.texture);
    }
}

bool CRawDataProcessor::LoadFile(LPCTSTR lpDataFile_i, unsigned int nWidth_i, unsigned int nHeight_i, unsigned int nSlices_i )
{
    CFile Medfile;
    if( !Medfile.Open(lpDataFile_i ,CFile::modeRead ))
    {
        return false;
    }

    // File has only image data. The dimension of the data should be known.
    data.dim.z = nSlices_i;
    data.dim.x = nWidth_i;
    data.dim.y = nHeight_i;


    // Holds the luminance buffer
    std::vector<char> buffer(data.dim.size());
    // Holds the RGBA buffer
    std::vector<char> rgbaBuffer(data.dim.size() *4);

    Medfile.Read(buffer.data(), data.dim.size());

    // Convert the data to RGBA data.
    // Here we are simply putting the same value to R, G, B and A channels.
    // Usually for raw data, the alpha value will be constructed by a threshold value given by the user 

    for(unsigned int nIndx = 0; nIndx < (data.dim.size()); ++nIndx )
    {
        rgbaBuffer[nIndx*4] = buffer[nIndx];
        rgbaBuffer[nIndx*4+1] = buffer[nIndx];
        rgbaBuffer[nIndx*4+2] = buffer[nIndx];
        rgbaBuffer[nIndx*4+3] = buffer[nIndx];
    }

    // If this function is getting called again for another data file.
    // Deleting and creating texture is not a good idea, 
    // we can use the glTexSubImage3D for better performance for such scenario.
    // I am not using that now :-)
    if( 0 != data.texture )
    {
        glDeleteTextures( 1, (GLuint*)&data.texture);
    }
    glGenTextures(1,(GLuint*)&data.texture);

    glBindTexture( GL_TEXTURE_3D, data.texture);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
    glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);


    glTexImage3D(GL_TEXTURE_3D, 0, GL_RGBA, data.dim.x, data.dim.y, data.dim.z, 0,
        GL_RGBA, GL_UNSIGNED_BYTE, rgbaBuffer.data() );
    glBindTexture( GL_TEXTURE_3D, 0 );

    return true;
}