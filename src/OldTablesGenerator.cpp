/**
 *  @file     OldTablesGenerator.cpp
 *  @brief    OldTablesGenerator is the implementation of TableGenerator interface
 *
 *  @author   Franco Riberi
 *  @email    fgriberi AT gmail.com
 *
 * Contents:  Source file for remo providing OldTablesGenerator implementation.
 *
 * System:    remo: RNAemo - RNA research project
 * Language:  C++
 *
 * @date       2012
 *
 * This file is part of Remo.
 *
 * Copyright (C) 2012 - Franco Riberi, FuDePAN.
 *
 * Remo is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Remo is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Remo. If not, see <http:www.gnu.org/licenses/>.
 *
 */

#include <memory>
#include <fideo/fideo.h>
#include "remo/Exceptions.h"
#include "remo/TablesGenerator.h"

/** @brief Temporal methods to execute remo
 *
 */
fideo::IFold* getDerivedFold(const std::string& derivedKey);

namespace remo
{

typedef double DeltaG; //to free energy
typedef char ColumnValue;

/** @brief OldTablesGenerator is a implementation of TableGenerator interface
 *
 */
class OldTablesGenerator : public TablesGenerator
{
public:

    /** @brief Convert index
     *
     */
    class IndexConverter
    {
    public:

        /** @brief Constructor of class
         *
         */
        IndexConverter(const size_t seqSize, bool isCirc, size_t mirnaSize);

        /** @brief Method that calculates the maximum position to move into messenger RNA
         *
         * @return Maximum index possible in the messenger RNA sequence
         */
        inline size_t getMaxPos() const;

        /** @brief Converting index depending on whether the sequence is circular or not.
         *
         * @param index in the sequence
         * @return idx if less than the size of the sequence, otherwise, if is circula, idx - size of the sequence
         */
        inline size_t convertIndex(size_t idx) const;

    private:

        const size_t seqRNAmSize;
        const bool circ;
        const size_t microRNASize;
    };

    /* @brief Destructor of class.
     *
     */
    virtual ~OldTablesGenerator();

    /** @brief Create concrete instance
     *
     * @param args: to get specific instance
     * @return void
     */
    virtual void initialize(GetOpt::GetOpt_pp& args);

    /** @brief Method that populates a file by rows
     *
     * @return void
     */
    virtual void generate(const std::string& tableName, const biopp::NucSequence& rnaMsg,
                          const biopp::NucSequence& rnaMHumanized, const bool circ);

    /** @brief Method that append one sequence of miRNA in table. For position.
     *
     * @param miRna
     * @param nameMicro
     * @return void
     */
    virtual void appendMicro(const biopp::NucSequence& miRna, const std::string& nameMicro);

    /** @brief Method that prints the header files
     *
     * @return void
     */
    void generateHeader();

    /** @brief Method that generates a full row for a file
     *
     * @param nameMicro: miRNA name
     * @param RNAm: RNAm original
     * @param rnaHumanized: RNAm humanized sequence
     * @param miRNA: miRNA sequence
     * @param secondaryStructureRNAm: secondary structure of original messenger ARN
     * @param secondaryStructureHum: secondary structure of humanized messenger ARN
     * @param idxConvert: index in the sequence
     * @param miRnaStart: index start
     * @return void
     */
    void generateTableRow(const std::string nameMicro, const biopp::NucSequence& RNAm, const biopp::NucSequence& rnaHumanized,
                          const biopp::NucSequence& miRNA, const biopp::SecStructure& secondaryStructureRNAm,
                          const biopp::SecStructure& secondaryStructureHum, IndexConverter& idxConvert, const size_t miRnaStart);

    /** @brief Method that generates a row with the desired sequences 3
     *
     * @param sequenceRNA: sequence of messenger ARN
     * @param miRNA: sequence of microRNA
     * @param secondaryStructure: secondary structure of messenger ARN
     * @param converter: index convert
     * @param miRnaStart: index in the sequence
     * @return void
     */
    void generateSequencesGroupRow(const biopp::NucSequence& sequenceRNA, const biopp::NucSequence& miRNA,
                                   const biopp::SecStructure& secondaryStructure, const IndexConverter& converter, const size_t miRnaStart);

    /** @brief Method that shows in uppercase one nucleotide as appropriate.
     *
     * @param numMiRNA: nucleotide of microARN
     * @param nucRNAm: nucleotide of messenger ARN
     * @return uppercase, if matching nucleotides, otherwise lowercase
     */
    static ColumnValue column1Seq(const biopp::Nucleotide nucMiRNA, const biopp::Nucleotide nucRNAm);

    /** @brief Method masking a nucleotide
     *
     * @param numMiRNA: nucleotide of microARN
     * @param nucRNAm: nucleotide of messenger ARN
     * @param isMsgPaired: is paired nucleotide of messenger ARN in the secondary structure
     * @return 'M' if matching nucleotides and the nucleotide of rnam. is paired
     */
    static ColumnValue column2Seq(const biopp::Nucleotide nucMiRNA, const biopp::Nucleotide nucRNAm, bool isMsgPaired);

    /** @brief Method that shows the nucleotide not available through XYZ from type of union
     *
     * @param index in sequence
     * @param secondary structure of sequence
     * @param sequence of messenger ARN
     * @return 'X' if A=U; 'Y' if G=C; 'Z' if G=C; otherwise '?' (A=G,C=T, A=C)
     */
    static ColumnValue column3Seq(size_t index, const biopp::SecStructure& structure, const biopp::NucSequence& sequence);

    /** @brief Method that generate score using zuker values
     *
     * @param secundary structure of messenger ARN
     * @param sequence of messenger ARN
     * @param sequence of microARN
     * @param position where begin the comparison
     * @return
     */
    void generateScoreColumn(const biopp::SecStructure& structure, const biopp::NucSequence& seqRna, const biopp::NucSequence& microRna, const size_t microStart);

    /** @brief file to complete
     *
     */
    std::ofstream oFile;

private:
    /**
     * Enumerated type representing unions
     */
    enum PairedType
    {
        Unpaired, auType, cgType, guType, othersType, typeCount
    };

    typedef size_t PairedTypeArray[typeCount];

    /** @brief Method that determines the type of union considering secondary structure
    * 
    * @param index in the sequence
    * @param secondary structure of sequence
    * @param sequence
    * @return type of union
    */
    static PairedType getPairedType(const biopp::SeqIndex i, const biopp::SecStructure& structure, const biopp::NucSequence& sequence);

    /** @brief Method that determines the type of union between two nucleotides
     * 
     * @param nucleotide
     * @param nucleotide
     * @return type of union
     */
    static PairedType getComplementType(const biopp::Nucleotide& n1, const biopp::Nucleotide& n2);

    /** @brief Method that determines the amount of paired
     *
     * @param secondary structure of messenger ARN
     * @param sequence of ARN
     * @param index in the sequence
     * @param
     * @return
     */
    static void countPaired(const biopp::SecStructure& structure, const biopp::NucSequence& sequence,
                            size_t microStart, size_t microRnaLength, PairedTypeArray& pCount);

    /** @brief Method that determines the amount of paired
     *
     * @param sequence of messenger ARN
     * @param sequence of microARN
     * @param index in the sequence    
     * @return 
     */
    static void countPaired(const biopp::NucSequence& rnamSequence, const biopp::NucSequence& microSequence,
                            size_t microStart, PairedTypeArray& pCount);

    /** @brief Fold sequences
     *
     * @param tableName: to get file name
     * @param seqRnaM: original RNA sequence
     * @param seqHumRnaM: humanized RNA sequence
     * @return 
     */
    void fold(const std::string& tableName, const biopp::NucSequence& seqRnaM, const biopp::NucSequence& seqHumRnaM);

    /// Allows comparison between two nucleotides. Interface
    struct Comp
    {
        const biopp::Nucleotide nuc1;
        const biopp::Nucleotide nuc2;

        Comp(biopp::Nucleotide n1, biopp::Nucleotide n2) : nuc1(n1), nuc2(n2) {}

        bool compare(const biopp::Nucleotide c1, const biopp::Nucleotide c2) const;
    };

    fideo::IFold* folderImpl;

    biopp::NucSequence rnaM;
    biopp::NucSequence rnaMHum;
    biopp::SecStructure structRNAm;
    biopp::SecStructure structHumanized;
    bool isCirc;
};

//Zuker const
static const DeltaG ZUKER_AU = -2;
static const DeltaG ZUKER_GC = -3;

REGISTER_FACTORIZABLE_CLASS(TablesGenerator, OldTablesGenerator, std::string, "OldTablesGenerator");

OldTablesGenerator::~OldTablesGenerator()
{
    delete folderImpl;
}

void OldTablesGenerator::initialize(GetOpt::GetOpt_pp& args)
{
    std::string folder;
    args >> GetOpt::Option('f', "folder", folder);    
    folderImpl = getDerivedFold(folder);
}

bool OldTablesGenerator::Comp::compare(const biopp::Nucleotide c1, const biopp::Nucleotide c2) const
{
    return ((nuc1 == c1 && nuc2 == c2) || (nuc1 == c2 && nuc2 == c1));
}

OldTablesGenerator::IndexConverter::IndexConverter(const size_t seqSize, bool isCirc, size_t mirnaSize)
    : seqRNAmSize(seqSize), circ(isCirc), microRNASize(mirnaSize)
{}

inline size_t OldTablesGenerator::IndexConverter::getMaxPos() const
{
    return circ ? seqRNAmSize - 1 :  seqRNAmSize - microRNASize;
}

inline size_t OldTablesGenerator::IndexConverter::convertIndex(size_t idx) const
{
    size_t ret;
    if (idx < seqRNAmSize)
    {
        ret = idx;
    }
    else
    {
        assert(circ);
        assert(idx < seqRNAmSize + microRNASize);
        ret = idx - seqRNAmSize;
    }
    return ret;
}

void OldTablesGenerator::generateHeader()
{
    oFile << "miRNA ," ;
    oFile << "Index ," ;
    oFile << "MatchingOrg ," ;
    oFile << "MaskedOrig ,";
    oFile << "XYZ?Orig ,";
    oFile << "upperCaseCountOrig ,";
    oFile << "mCountOrig ,";
    oFile << "MatchingHum ,";
    oFile << "MaskedHum ,";
    oFile << "XYZ?Hum ,";
    oFile << "upperCaseCountHum ,";
    oFile << "mCountHum ,";
    oFile << "ScoreZukOrig ,";
    oFile << "ScoreZukHum" << std::endl;
}

void OldTablesGenerator::generateSequencesGroupRow(const biopp::NucSequence& sequenceRNA, const biopp::NucSequence& miRNA,
        const biopp::SecStructure& secondaryStructure, const IndexConverter& converter, const size_t miRnaStart)
{
    std::string col1;
    std::string col2;
    std::string col3;
    size_t uppercaseCount = 0;
    size_t mCount = 0;
    for (size_t i = 0; i < miRNA.length(); ++i)
    {
        const size_t idx = converter.convertIndex(i + miRnaStart);
        const char col1Char = column1Seq(miRNA[idx], sequenceRNA[idx]);
        if (col1Char == toupper(col1Char))
        {
            uppercaseCount++;
        }
        col1 += col1Char;

        const char col2Char = column2Seq(miRNA[idx], sequenceRNA[idx], secondaryStructure.is_paired(i));
        if (col2Char == 'M')
        {
            mCount++;
        }
        col2 += col2Char;

        col3 += column3Seq(idx, secondaryStructure, sequenceRNA);
    }
    oFile << col1 << "," << col2 << "," << col3 << "," << uppercaseCount << "," << mCount;
}

void OldTablesGenerator::generateScoreColumn(const biopp::SecStructure& structureRNA, const biopp::NucSequence& seqRna, const biopp::NucSequence& microRna, const size_t microStart)
{
    PairedTypeArray counterMsgMsg;
    PairedTypeArray counterMsgMicro;

    countPaired(structureRNA, seqRna, microStart, microRna.length(), counterMsgMsg);
    countPaired(seqRna, microRna, microStart, counterMsgMicro);

    const DeltaG col =  ZUKER_AU * (DeltaG(counterMsgMicro[auType]) - DeltaG(counterMsgMsg[auType])) +  ZUKER_GC * (DeltaG(counterMsgMicro[cgType]) - DeltaG(counterMsgMsg[cgType]));

    if (col != -0.0)
    {
        oFile << col;
    }
    else
    {
        oFile << 0;
    }
}

void OldTablesGenerator::generateTableRow(const string nameMicro, const biopp::NucSequence& RNAm, const biopp::NucSequence& rnaHumanized,
        const biopp::NucSequence& miRNA, const biopp::SecStructure& secondaryStructureRNAm,
        const biopp::SecStructure& secondaryStructureHum, IndexConverter& idxConvert, const size_t miRnaStart)
{
    oFile << nameMicro;
    oFile << ",";
    oFile << miRnaStart + 1;
    oFile << ",";
    generateSequencesGroupRow(RNAm, miRNA, secondaryStructureRNAm, idxConvert, miRnaStart);
    oFile << ",";
    generateSequencesGroupRow(rnaHumanized, miRNA, secondaryStructureHum, idxConvert, miRnaStart);
    oFile << ",";
    generateScoreColumn(secondaryStructureRNAm, RNAm, miRNA, miRnaStart);
    oFile << ",";
    generateScoreColumn(secondaryStructureHum, rnaHumanized, miRNA, miRnaStart);
    oFile << std::endl;
}

ColumnValue OldTablesGenerator::column1Seq(const biopp::Nucleotide nucMiRNA, const biopp::Nucleotide nucRNAm)
{
    ColumnValue ret;
    if (nucMiRNA == nucRNAm)
    {
        ret = toupper(nucRNAm.as_char());
    }
    else
    {
        ret = tolower(nucRNAm.as_char());
    }
    return ret;
}

ColumnValue OldTablesGenerator::column2Seq(const biopp::Nucleotide nucMiRNA, const biopp::Nucleotide nucRNAm, bool isMsgPaired)
{
    ColumnValue ret;
    if (nucMiRNA == nucRNAm)
    {
        if (isMsgPaired)
        {
            ret = 'M';
        }
        else
        {
            ret = toupper(nucRNAm.as_char());
        }
    }
    else
    {
        ret = tolower(nucRNAm.as_char());
    }
    return ret;
}

OldTablesGenerator::PairedType OldTablesGenerator::getPairedType(const biopp::SeqIndex i, const biopp::SecStructure& structure, const biopp::NucSequence& sequence)
{
    PairedType ret;
    if (!structure.is_paired(i))
    {
        ret = Unpaired;
    }
    else
    {
        Comp c(sequence[i], sequence[structure.paired_with(i)]);
        if (c.compare(biopp::Nucleotide(biopp::Nucleotide::A), biopp::Nucleotide(biopp::Nucleotide::U)))
        {
            ret = auType;
        }
        else if (c.compare(biopp::Nucleotide(biopp::Nucleotide::C), biopp::Nucleotide(biopp::Nucleotide::G)))
        {
            ret = cgType;
        }
        else if (c.compare(biopp::Nucleotide(biopp::Nucleotide::G), biopp::Nucleotide(biopp::Nucleotide::U)))
        {
            ret = guType;
        }
        else
        {
            ret = othersType;
        }
    }
    return ret;
}

OldTablesGenerator::PairedType OldTablesGenerator::getComplementType(const biopp::Nucleotide& n1, const biopp::Nucleotide& n2)
{
    PairedType ret;
    Comp c(n1, n2);
    if (c.compare(biopp::Nucleotide(biopp::Nucleotide::A), biopp::Nucleotide(biopp::Nucleotide::U)))
    {
        ret = auType;
    }
    else if (c.compare(biopp::Nucleotide(biopp::Nucleotide::C), biopp::Nucleotide(biopp::Nucleotide::G)))
    {
        ret = cgType;
    }
    else if (c.compare(biopp::Nucleotide(biopp::Nucleotide::G), biopp::Nucleotide(biopp::Nucleotide::U)))
    {
        ret = guType;
    }
    else
    {
        ret = Unpaired;
    }
    return ret;
}

ColumnValue OldTablesGenerator::column3Seq(size_t index, const biopp::SecStructure& structure, const biopp::NucSequence& sequence)
{
    const PairedType pType = getPairedType(index, structure, sequence);
    ColumnValue ret;
    switch (pType)
    {
        case Unpaired :
            ret = sequence[index].as_char();
            break;
        case auType :
            ret = 'X';
            break;
        case cgType :
            ret = 'Y';
            break;
        case guType :
            ret = 'Z';
            break;
        case othersType :
            ret = '?';
            break;
        default:
            assert(false);
    }
    return ret;
}

void OldTablesGenerator::countPaired(const biopp::SecStructure& structure, const biopp::NucSequence& sequence, size_t microStart,
                                     size_t microRnaLength, PairedTypeArray& pCount)
{
    for (size_t i = 0; i < typeCount; ++i)
    {
        pCount[i] = 0;
    }
    for (size_t i = 0; i < microRnaLength; ++i)
    {
        pCount[getPairedType(i + microStart, structure, sequence)]++;
    }
}

//Should disappear in iteracion4. The hybridization provides structure between mRNA and microRNA
void OldTablesGenerator::countPaired(const biopp::NucSequence& rnamSequence, const biopp::NucSequence& microSequence, size_t microStart, PairedTypeArray& pCount)
{
    for (size_t i = 0; i < typeCount; ++i)
    {
        pCount[i] = 0;
    }
    const size_t indexMax = microSequence.length();
    biopp::Nucleotide nucComp;
    for (size_t i = 0; i < indexMax; ++i)
    {
        nucComp = microSequence[i];
        nucComp.complement();
        pCount[getComplementType(nucComp, rnamSequence[i + microStart])]++;
    }
}

void OldTablesGenerator::fold(const std::string& tableName, const biopp::NucSequence& seqRnaM, const biopp::NucSequence& seqHumRnaM)
{
    const std::string filename = tableName.substr(0, tableName.size() - 4); 
    if (TablesGenerator::dontFold)
    {
        std::ifstream inputFile(filename.c_str());                        
        fideo::FilePath originalSeq = "orig-"+filename;
        fideo::FilePath humSeq = "hum-"+filename;
        if (!inputFile)
        {                                        
            folderImpl->foldTo(seqRnaM, isCirc, structRNAm, originalSeq);   
            folderImpl->foldTo(seqHumRnaM, isCirc, structHumanized, humSeq);            

        }
        folderImpl->foldFrom("orig-"+filename, structRNAm);                    
        folderImpl->foldFrom("hum-"+filename, structHumanized);                    
    }
    else
    {            
        folderImpl->fold(seqRnaM, isCirc, structRNAm);
        folderImpl->fold(seqHumRnaM, isCirc, structHumanized);
    }

    
}

void OldTablesGenerator::generate(const std::string& tableName, const biopp::NucSequence& rnaMsg, const biopp::NucSequence& rnaMHumanized, bool circ)
{
    rnaM = rnaMsg;
    rnaMHum = rnaMHumanized;
    isCirc = circ;
    fold(tableName, rnaM, rnaMHum);
    if (oFile)
    {
        oFile.close();
    }
    oFile.open(("/tmp/" + tableName).c_str());
    mili::assert_throw<FileNotCreated>(!oFile);
    generateHeader();
}

void OldTablesGenerator::appendMicro(const biopp::NucSequence& miRna, const string& nameMicro)
{
    assert(rnaM.length() == rnaMHum.length());
    assert(structRNAm.size() == structHumanized.size());

    IndexConverter cIndex(rnaM.length(), isCirc, miRna.length());
    biopp::NucSequence mirnaCompl(miRna);
    mirnaCompl.complement();
    const size_t maxIndex = cIndex.getMaxPos();
    for (size_t i = 0; i < maxIndex ; ++i)
    {
        generateTableRow(nameMicro, rnaM, rnaMHum, mirnaCompl, structRNAm, structHumanized, cIndex, i);
    }
}

} // namespace remo
