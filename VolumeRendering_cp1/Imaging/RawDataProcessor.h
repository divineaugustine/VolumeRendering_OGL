#pragma once
class CRawDataProcessor
{
public:

    struct Dimension
    {
        unsigned int x = {0};
        unsigned int y = {0};
        unsigned int z = {0};

        unsigned int size()
        {
            return x*y*z;
        }
    };

    struct Data
    {
        Dimension dim;
        unsigned int texture = {0};
    };

    CRawDataProcessor(void);
    virtual ~CRawDataProcessor(void);
    // Call this only after the open gl is initialized.
    bool LoadFile(LPCTSTR lpDataFile_i, unsigned int nWidth_i, unsigned int nHeight_i, unsigned int nSlices_i );

    const Data& getData()
    {
        return data;
    }

private:

    Data data;
};

