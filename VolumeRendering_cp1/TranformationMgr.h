#pragma once
class CTranformationMgr
{
public:
    CTranformationMgr(void);
    virtual ~CTranformationMgr(void);
    const double* GetMatrix()
    {
        return mdRotation;
    }
    // Call this only after the open gl is initialized.
    void Rotate(float fx_i, float fy_i, float fz_i );
    void ResetRotation();

private:

    float mfRot[3];
    double mdRotation[16];
};

