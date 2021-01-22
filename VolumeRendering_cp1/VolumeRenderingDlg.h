// VolumeRenderingDlg.h : header file
//

#pragma once

#include "Imaging/RendererHelper.h"
#include "Imaging/TranformationMgr.h"
#include "Imaging/RawDataProcessor.h"


// CVolumeRenderingDlg dialog
class CVolumeRenderingDlg : public CDialogEx
{
// Construction
public:
    CVolumeRenderingDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
    enum { IDD = IDD_VOLUMERENDERING_CP1_DIALOG };

    protected:
    virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
    HICON m_hIcon;

    // Generated message map functions
    virtual BOOL OnInitDialog();
    afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
    afx_msg void OnPaint();
    afx_msg HCURSOR OnQueryDragIcon();
    DECLARE_MESSAGE_MAP()

private:

    HDC mhContext;
    CRendererHelper m_Renderer;
    CPoint mRotReference;
    CRawDataProcessor m_RawDataProc;
    CTranformationMgr m_Transformation;

public:
    afx_msg void OnSize(UINT nType, int cx, int cy);
    afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
    afx_msg void OnTimer(UINT_PTR nIDEvent);
    afx_msg void OnMouseMove(UINT nFlags, CPoint point);
    afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
    afx_msg BOOL OnEraseBkgnd(CDC* pDC);
};
