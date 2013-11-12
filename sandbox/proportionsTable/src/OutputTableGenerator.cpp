#include <iostream>
#include "proportionsTable/OutputTableGenerator.h"

namespace NSBuildFile
{

OutputTableGenerator::OutputTableGenerator(const File& name)
{
    if (_outFile)
    {
        _outFile.close();
    }
    _outFile.open(name.c_str());
    if(!_outFile)
        std::cout << "File not created " << std::endl;
    generateHeader();
}

void OutputTableGenerator::generateHeader()
{ 
    _outFile << "RNAm,";    
    _outFile << " , , , Original , , , ,";    
    _outFile << " , , , Humanized, , , ";    
    _outFile << std::endl;

    //subheader    
    _outFile << ", G, C, G/C, A, T, A/T , AmountNucl";    
    _outFile << ", G, C, G/C, A, T, A/T, AmountNucl";    
    _outFile << std::endl;

}

static const size_t A = 65;
static const size_t C = 67;
static const size_t G = 71;
static const size_t U = 85;

void OutputTableGenerator::fillColumn(const Result& res)
{
    Result::const_iterator it;    
    float amountG, amountC, amountA, amountU;
    for (it = res.begin(); it != res.end(); ++it)
    {
        switch(it->first)
        {
            case G:
                amountG = it->second;
                break;
            case C:
                amountC = it->second;;
                break;
            case A:
                amountA = it->second;;
                break;
            case U:
                amountU = it->second;;
                break;
        }        
    }
    _outFile << amountG;
    _outFile << ", ";
    _outFile << amountC;
    _outFile << ", ";
    _outFile << amountG / amountC;
    _outFile << ", ";
    _outFile << amountA;
    _outFile << ", ";
    _outFile << amountU;
    _outFile << ", ";
    _outFile << amountA / amountU;
}

void OutputTableGenerator::save(const std::string& name, const Result& origRes, const Result& humRes, const size_t sizeOrig, const size_t sizeHum)
{
    _outFile << name;
    _outFile << ", ";
    fillColumn(origRes);
    _outFile << ", ";
    _outFile << sizeOrig;
    _outFile << ", ";
    fillColumn(humRes);  
    _outFile << ", ";
    _outFile << sizeHum;
    _outFile << std::endl;
}

} // end namespace