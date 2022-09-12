#include "XMLManip.h"

#include <filesystem>
#include <iostream>
#include <random>
#include <fstream>
int main()
{
    xml::XMLManip xml;
    std::filesystem::path root = "D:/darknet/custom_data/images";
     for (const std::filesystem::directory_entry& dir_entry : 
         std::filesystem::recursive_directory_iterator(root))
    {
        if(dir_entry.path().extension() == ".xml")
        {
            std::filesystem::path path = root;
            path /= dir_entry.path().filename();
            xml.ParseDoc(root.make_preferred(), path.make_preferred());
        }
     }
     std::random_device rd;
     std::mt19937 generator( rd() );
     std::uniform_int_distribution<int> uniform;
     std::bernoulli_distribution bernoulli( 0.8 ); // 90% 1 ; 10% 0
     

     std::ofstream trainFile;
     std::ofstream testFile;
     trainFile.open( "D:/darknet/custom_data/train.txt" );
     testFile.open( "D:/darknet/custom_data/test.txt" );

     for( const std::filesystem::directory_entry& dir_entry :
         std::filesystem::recursive_directory_iterator( root ) )
     {
         if( dir_entry.path().extension() == ".jpg" )
         {
             const int product = bernoulli( generator );
             std::filesystem::path path = root;
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