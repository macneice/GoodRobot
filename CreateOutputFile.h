#pragma once
#include "DimensionCalculator.h"

#include <filesystem>
#include <fstream>
#include <string>
namespace ml_file
{
    class CreateOutputFile
    {
    public:
        CreateOutputFile() = default;
        CreateOutputFile(
			int classId,
            const dimension::DimensionCalculator& dimCalc,
            const std::filesystem::path& filePath )
        {
            std::ofstream yoloFile;
            yoloFile.open( filePath.string() );
            yoloFile << classId << " "<< dimCalc.GetXCentre() << " " << dimCalc.GetYCentre() << " " << dimCalc.GetWidth() << " " << dimCalc.GetHeight();
            yoloFile.close();
        }
    };
}