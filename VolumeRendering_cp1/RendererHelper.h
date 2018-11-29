
#include <GL\glew.h>
#include <GL\GL.h>
class CRawDataProcessor;
class CTranformationMgr;

#pragma once
class CRendererHelper
{
public:
    CRendererHelper(void);
    virtual ~CRendererHelper(void);

    bool Initialize( HDC hContext_i, CRawDataProcessor* pRawDataProc_i, CTranformationMgr* pTransformationMgr_i );
    void Resize( int nWidth_i, int nHeight_i );
    void Render();

private:

    HGLRC m_hglContext;
    CRawDataProcessor* m_pRawDataProc;
    CTranformationMgr* m_pTransformMgr;
};

