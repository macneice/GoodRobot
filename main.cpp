#include "XMLManip.h"

#include <filesystem>
#include <iostream>
#include <random>
#include <fstream>
int main( int argc, char *argv[] )
{
    xml::XMLManip xml;
    std::filesystem::path imageRootPath = "D:/custom_data/images";
    std::filesystem::path trainTestOutputPath = "D:/custom_data";

	if ( argc > 1 )
	{
		imageRootPath = argv[1];
	}
	if ( argc > 2 )
	{
		trainTestOutputPath = argv[2];
	}
     for (const std::filesystem::directory_entry& dir_entry : 
         std::filesystem::recursive_directory_iterator(imageRootPath.make_preferred()))
    {
        if(dir_entry.path().extension() == ".xml")
        {
            std::filesystem::path path = imageRootPath;
            path /= dir_entry.path().filename();
            xml.ParseDoc(imageRootPath.make_preferred(), path.make_preferred());
        }
     }
     std::random_device rd;
     std::mt19937 generator( rd() );
     std::uniform_int_distribution<int> uniform;
     std::bernoulli_distribution bernoulli( 0.8 ); // 80% train ; 20% test
     

     std::ofstream trainFile;
     std::ofstream testFile;
     std::filesystem::path trainPath = trainTestOutputPath / "train.txt";
     std::filesystem::path testPath = trainTestOutputPath / "test.txt";
     trainFile.open( trainPath.make_preferred() );
     testFile.open( testPath.make_preferred() );

     for( const std::filesystem::directory_entry& dir_entry :
         std::filesystem::recursive_directory_iterator( imageRootPath.make_preferred() ) )
     {
         if( dir_entry.path().extension() == ".jpg" )
         {
             const int product = bernoulli( generator );
             std::filesystem::path path = imageRootPath;
             path /= dir_entry.path().filename();
             if( product )
             {
                 trainFile << path.string() << "\n";
             }
             else
             {
                 testFile << path.string() << "\n";
             }
         }
     }
     trainFile.close();
     testFile.close();
}