#pragma once

#include "BBox.h"
#include "CreateOutputFile.h"
#include "DimensionCalculator.h"
#include "tinyxml2.h"

#include <iostream>
#include <filesystem>
#include <string>
namespace xml
{
    class XMLManip
    {
    public:
        XMLManip() = default;

        void ParseDoc( 
            const std::filesystem::path& root,
            const std::filesystem::path& filePath )
        {
            tinyxml2::XMLDocument doc;
            doc.LoadFile( filePath.string().c_str() );
            std::string filename = doc.FirstChildElement( "annotation" )->FirstChildElement( "filename" )->GetText();

            m_Name = filename.substr( 0, filename.find( "." ) );

            m_FilePath = root;
            m_FilePath /= m_Name + ".txt";

            tinyxml2::XMLElement* w = doc.FirstChildElement( "annotation" )->FirstChildElement( "size" )->FirstChildElement( "width" );
            tinyxml2::XMLElement* h = doc.FirstChildElement( "annotation" )->FirstChildElement( "size" )->FirstChildElement( "height" );

            int width = 0;
            int height = 0;

            w->QueryIntText( &width );
            h->QueryIntText( &height );

           tinyxml2::XMLElement* bndbox = doc.FirstChildElement( "annotation" )->FirstChildElement( "object" )->FirstChildElement( "bndbox" );
           tinyxml2::XMLElement* xminVal = bndbox->FirstChildElement( "xmin" );
           tinyxml2::XMLElement* xmaxVal = bndbox->FirstChildElement( "xmax" );
           tinyxml2::XMLElement* yminVal = bndbox->FirstChildElement( "ymin" );
           tinyxml2::XMLElement* ymaxVal = bndbox->FirstChildElement( "ymax" );

            int xmin = 0;
            int xmax = 0;
            int ymin = 0;
            int ymax = 0;

            xminVal->QueryIntText( &xmin );
            xmaxVal->QueryIntText( &xmax );
            yminVal->QueryIntText( &ymin );
            ymaxVal->QueryIntText( &ymax );

            dimension::BBox box{ xmin, xmax, ymin, ymax };

            m_DimensionCalculator = dimension::DimensionCalculator( width, height, box );

            m_OutputFileCreator = ml_file::CreateOutputFile( m_DimensionCalculator, m_FilePath );
        }

    private:
        std::string m_Name{};
        std::filesystem::path m_FilePath;
        dimension::DimensionCalculator m_DimensionCalculator;
        ml_file::CreateOutputFile m_OutputFileCreator;
    };
}