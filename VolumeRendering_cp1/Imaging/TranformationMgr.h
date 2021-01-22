#pragma once
class CTranformationMgr
{
public:

    class Matrix
    {
    public:

        Matrix()
        {
            LoadIdentity();
        }

        Matrix( const Matrix& in )
        {
            memcpy(mdRotation, in.mdRotation, sizeof(mdRotation));
        }

        Matrix& operator=(const Matrix& in)
        {
            if (this != &in)
            {
                memcpy(mdRotation, in.mdRotation, sizeof(mdRotation));
            }
            return *this;
        }

        void LoadIdentity()
        {
            mdRotation[0] = mdRotation[5] = mdRotation[10] = mdRotation[15] = 1.0f;
            mdRotation[1] = mdRotation[2] = mdRotation[3] = mdRotation[4] = 0.0f;
            mdRotation[6] = mdRotation[7] = mdRotation[8] = mdRotation[9] = 0.0f;
            mdRotation[11] = mdRotation[12] = mdRotation[13] = mdRotation[14] = 0.0f;
        }

        double* ptr()
        {
            return mdRotation;
        }

    private:
        double mdRotation[16];
    };

    CTranformationMgr(void);
    virtual ~CTranformationMgr(void);

    const Matrix& GetMatrix()
    {
        return mdRotation;
    }
    // Call this only after the open gl is initialized.
    void Rotate(float fx_i, float fy_i, float fz_i );
    void ResetRotation();

private:

    Matrix mdRotation;
    float mfRot[3] = {0.0f};
    
};

