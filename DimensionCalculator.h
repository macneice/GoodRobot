#pragma once
#include "BBox.h"
namespace dimension
{
    class DimensionCalculator
    {
    public:
        DimensionCalculator() = default;
        DimensionCalculator(
            int imageWidth,
            int imageHeight,
            const dimension::BBox& bbox )
        {
            float xBoxCentre = ( ( bbox.m_Xmax + bbox.m_Xmin ) / 2 );
            float yBoxCentre = ( ( bbox.m_Ymax + bbox.m_Ymin ) / 2 );
            float boxWidth = ( bbox.m_Xmax - bbox.m_Xmin );
            float boxHeight = ( bbox.m_Ymax - bbox.m_Ymin );

            m_XCenter = xBoxCentre / imageWidth;
            m_YCenter = yBoxCentre / imageHeight;
            m_Width = boxWidth / imageWidth;
            m_Height = boxHeight / imageHeight;
        }
        float GetXCentre() const { return m_XCenter; }
        float GetYCentre() const { return m_YCenter; }
        float GetWidth() const { return m_Width; }
        float GetHeight() const { return m_Height; }


    private:
        float m_XCenter = 0;
        float m_YCenter = 0;
        float m_Width = 0;
        float m_Height = 0;
    };
}