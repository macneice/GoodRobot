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
            const dimension::DimensionCalculator& dimCalc,
            const std::filesystem::path& filePath )
        {
            std::ofstream myfile;
            myfile.open( filePath.string() );
            myfile << dimCalc.GetXCentre() << " " << dimCalc.GetYCentre() << " " << dimCalc.GetWidth() << " " << dimCalc.GetHeight();
            myfile.close();
        }
    };
}