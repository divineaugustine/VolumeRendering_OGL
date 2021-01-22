#pragma once


#include <GL\glew.h>
#include <GL\GL.h>
#include "TranformationMgr.h"
#include "RawDataProcessor.h"


class CRendererHelper
{
public:
    CRendererHelper(void);
    virtual ~CRendererHelper(void);

    bool Initialize( HDC hContext_i );

    void Resize(unsigned int nWidth_i, unsigned int nHeight_i );
    void SetRotation(const CTranformationMgr::Matrix& matrix)
    {
        rotationMatrix = matrix;
    }

    void SetImage(const CRawDataProcessor::Data& img)
    {
        data = img;
    }
    void Render();

private:

    CTranformationMgr::Matrix rotationMatrix;
    CRawDataProcessor::Data   data;
    HGLRC m_hglContext;
};

