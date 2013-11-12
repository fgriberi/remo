#include <memory>
#include <mili/mili.h>
#include "proportionsTable/BuildFile.h"
#include "proportionsTable/OutputTableGenerator.h"
#include "proportionsTable/Types.h"
#include "proportionsTable/CodingSectionObtainer.h"

acuoso::ICodonUsageModifier* getDerivedHumanizerBackend(const std::string& derivedKey);

namespace NSBuildFile
{

static const std::string FILE_NAME = "/tmp/analisisProporciones.csv";

void BuildFile::clearResultMap(Result& result)
{
	result.clear();
}

void BuildFile::startBuild(const Arguments& argument)
{
	bioppFiler::FastaParser<biopp::NucSequence> fileMsg(argument.fileNameRNAm);

    //humanizer
    std::auto_ptr<acuoso::ICodonUsageModifier> humanizerImpl(getDerivedHumanizerBackend(argument.humanizer));
    
    //set organism
    humanizerImpl->setOrganism(acuoso::ICodonUsageModifier::Organism(argument.organism));   
    
    countBases(fileMsg, humanizerImpl.get());   
}

void BuildFile::replaceHumanizedSection(const biopp::NucSequence& originalSeq, const biopp::NucSequence& humanizedSeq,
        const size_t initNucIndex, biopp::NucSequence& toFoldSeq)
{
    toFoldSeq = originalSeq;
    for (size_t i = 0; i < humanizedSeq.length(); i++)
    {
        toFoldSeq[i + initNucIndex] = humanizedSeq[i];
    }
}

void BuildFile::getHumanizedSequence(biopp::NucSequence& origSeq, const acuoso::ICodonUsageModifier* humanizer,
                                     biopp::NucSequence& humanizedSeq)
{
    biopp::AminoSequence aminoSequenceRNAm;
    biopp::NucSequence humRnaM;
    size_t initIndex;
    CodingSectionObtainer helper;
    helper.getCodingSection(origSeq, aminoSequenceRNAm, initIndex);
    humanizer->changeCodonUsage(aminoSequenceRNAm, humRnaM);
    replaceHumanizedSection(origSeq, humRnaM, initIndex, humanizedSeq);
}

void BuildFile::parseFileName(const std::string& fileName, std::string& name)
{
    std::stringstream ss(fileName);
    SplitString result;
    ss >> mili::Separator(result, '|');
    result.size() > 3 ? name = result[3] : name = fileName;
}

void BuildFile::addBase(char base, Result& result)
{
	const Nucleotides nucl = Nucleotides(base);
	const Result::const_iterator it = result.find(nucl);
	if (it != result.end())
    {
    	result[nucl]++;
	}
	else
	{
        result[nucl] = 1;
	}
}

void BuildFile::processSequence(const biopp::NucSequence& seq, Result& result)
{
	std::string sequence = seq.getString();
	for(size_t i(0); i < sequence.size(); ++i)
	{
		addBase(sequence[i], result);
	}	
}

bool BuildFile::checkNucleotidAmount(const Result& res, const std::string& seq)
{
	Result::const_iterator it;        
	size_t nucleotidesAmount;
    for (it = res.begin(); it != res.end(); ++it)
    {
    	nucleotidesAmount += it->second;
    }
    return (nucleotidesAmount == seq.size());
}

void BuildFile::countBases(bioppFiler::FastaParser<biopp::NucSequence>& file, const acuoso::ICodonUsageModifier* humanizer)
{
	std::string description;
	biopp::NucSequence origSeq;
	biopp::NucSequence humSeq;
	OutputTableGenerator output(FILE_NAME.c_str());
	Result resultOrig;
	Result resultHum;
	std::string seqName;
	while (file.getNextSequence(description, origSeq))
	{
		parseFileName(description, seqName);		

		//humanized
		getHumanizedSequence(origSeq, humanizer, humSeq);

		processSequence(origSeq, resultOrig);
		assert(checkNucleotidAmount(resultOrig, origSeq.getString()));

		processSequence(humSeq, resultHum);	
		std::cout << humSeq.getString() << std::endl;
		assert(checkNucleotidAmount(resultHum, origSeq.getString()));

		const size_t sizeOrig = (origSeq.getString()).size();
		const size_t sizeHum = (humSeq.getString()).size();

		output.save(seqName, resultOrig, resultHum, sizeOrig, sizeHum);		
		seqName.clear();
		resultOrig.clear();
		resultHum.clear();
	}
}

} //end namespace
