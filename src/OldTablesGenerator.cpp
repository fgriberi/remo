/**
 *  @file:      OldTablesGenerator.cpp
 *  @details    Generator tables.\n
 *              System: R-emo \n
 *              Language: C++\n
 *
 *  @author     Franco Riberi
 *  @email      fgriberi AT gmail.com
 *
 *  @date       October 2012
 *  @version    1.0
 *
 * This file is part of R-emo.
 *
 * Copyright (C) 2012 - Franco Riberi, FuDePAN.
 *
 * R-emo is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * R-emo is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with R-emo. If not, see <http:www.gnu.org/licenses/>.
 *
 */

#include <memory>
#include <mili/mili.h>
#include "fideo/fideo.h"
#include "remo/Definitions.h"
#include "remo/Exceptions.h"
#include "remo/TablesGenerator.h"

using namespace RemoTools;
using namespace biopp;
using namespace std;
using namespace mili;
using namespace biopp;

class OldTablesGenerator : public TablesGenerator
{
    /**
     * Enumerated type representing unions
     */
    enum PairedType
    {
        Unpaired, auType, cgType, guType, othersType, typeCount
    };

    /**
    * Method that determines the type of union considering secondary structure
    * @param index in the sequence
    * @param secondary structure of sequence
    * @param sequence
    * @return type of union
    */
    static PairedType get_pairedType(biopp::SeqIndex i, const biopp::SecStructure& structure, const biopp::NucSequence& sequence);

    /**
    * Method that determines the type of union between two nucleotidados
    * @param nucleotide
    * @param nucleotide
    * @return type of union
    */
    static PairedType get_ComplementType(const biopp::Nucleotide n1, const biopp::Nucleotide n2);

    typedef size_t PairedTypeArray[typeCount];

    /**
    * Method that determines the amount of paired
    * @param secondary structure of messenger ARN
    * @param sequence of ARN
    * @param index in the sequence
    * @param
    * @return
    */
    static void countPaired(const biopp::SecStructure& structure, const biopp::NucSequence& sequence, size_t microStart, size_t microRnaLength, PairedTypeArray& pCount);

    /**
    * Method that determines the amount of paired
    * @param sequence of messenger ARN
    * @param sequence of microARN
    * @param index in the sequence
    * @param
    * @return
    */
    static void countPaired(const biopp::NucSequence& rnamSequence, const biopp::NucSequence& microSequence, size_t microStart, PairedTypeArray& pCount);

    void fold(const biopp::NucSequence& seqRnaM, const biopp::NucSequence& seqHumRnaM);

    /**
     * Allows comparison between two nucleotides
     */
    struct Comp
    {
        const biopp::Nucleotide nuc1;
        const biopp::Nucleotide nuc2;

        Comp(biopp::Nucleotide n1, biopp::Nucleotide n2) : nuc1(n1), nuc2(n2) {}

        bool compare(biopp::Nucleotide c1, biopp::Nucleotide c2) const
        {
            return ((nuc1 == c1 && nuc2 == c2) || (nuc1 == c2 && nuc2 == c1));
        }
    };

    class IndexConverter
    {
        const size_t seqRNAmSize;
        const bool circ;
        const size_t microRNASize;

    public:
        /**
         * Class constructor
         */
        IndexConverter(const size_t seqSize, bool isCirc, size_t mirnaSize)
            : seqRNAmSize(seqSize), circ(isCirc), microRNASize(mirnaSize)
        {}

        /**
         * Method that calculates the maximum position to move into messenger RNA
         * @return Maximum index possible in the messenger RNA sequence
         */
        inline size_t getMaxPos() const;

        /**
         * Converting index depending on whether the sequence is circular or not.
         * @param index in the sequence
         * @return idx if less than the size of the sequence, otherwise, if is circula, idx - size of the sequence
         */
        inline size_t convertIndex(size_t idx) const;
    };

    IFold* folderImpl;

    biopp::NucSequence rnaM;
    biopp::NucSequence rnaMHum;
    biopp::SecStructure structRNAm;
    biopp::SecStructure structHumanized;
    bool isCirc;

public:
    std::ofstream oFile;

    /*
     * Destructor of class. Delete all pointers
     */
    ~OldTablesGenerator();

    virtual void initialize(GetOpt_pp& args);

    /**
     * Method that populates a file by rows
     */
    virtual void generate(const std::string& tableName, const biopp::NucSequence& rnaMsg, const biopp::NucSequence& rnaMHumanized, bool circ);

    /**
     * Method that append one sequence of miRNA in table. For position.
     */
    virtual void appendMicro(const biopp::NucSequence& miRna, const std::string& nameMicro);

    /**
     * Method that prints the header files
     */
    void generateHeader();

    /**
     * Method that generates a full row for a file
     * @param sequence of original messenger ARN
     * @param sequence of humanized messenger ARN
     * @param sequence of microRNA
     * @param secondary structure of original messenger ARN
     * @param secondary structure of humanized messenger ARN
     * @param
     * @param index in the sequence
     * @return
     */
    void generateTableRow(const std::string nameMicro, const biopp::NucSequence& RNAm, const biopp::NucSequence& rnaHumanized, const biopp::NucSequence& miRNA, const biopp::SecStructure& secondaryStructureRNAm, const biopp::SecStructure& secondaryStructureHum, IndexConverter& idxConvert, const size_t miRnaStart);

    /**
     * Method that generates a row with the desired sequences 3
     * @param sequence of messenger ARN
     * @param sequence of microRNA
     * @param secondary structure of messenger ARN
     * @param
     * @param index in the sequence
     * @return
     */
    void generateSequencesGroupRow(const biopp::NucSequence& sequenceRNA, const biopp::NucSequence& miRNA, const biopp::SecStructure& secondaryStructure, const IndexConverter& converter, const size_t miRnaStart);

    /**
     * Method that shows in uppercase one nucleotide as appropriate.
     * @param nucleotide of microARN
     * @param nucleotide of messenger ARN
     * @return uppercase, if matching nucleotides, otherwise lowercase
     */
    static char column1Seq(const biopp::Nucleotide nucMiRNA, const biopp::Nucleotide nucRNAm);

    /**
     * Method masking a nucleotide
     * @param nucleotide of microARN
     * @param nucleotide of messenger ARN
     * @param is paired nucleotide of messenger ARN in the secondary structure
     * @return 'M' if matching nucleotides and the nucleotide of rnam. is paired
     */
    static char column2Seq(const biopp::Nucleotide nucMiRNA, const biopp::Nucleotide nucRNAm, bool isMsgPaired);

    /**
     * Method that shows the nucleotide not available through XYZ from type of union
     * @param index in sequence
     * @param secondary structure of sequence
     * @param sequence of messenger ARN
     * @return 'X' if A=U; 'Y' if G=C; 'Z' if G=C; otherwise '?' (A=G,C=T, A=C)
     */
    static char column3Seq(size_t index, const biopp::SecStructure& structure, const biopp::NucSequence& sequence);

    /**
     * Method that generate score using zuker values
     * @param secundary structure of messenger ARN
     * @param sequence of messenger ARN
     * @param sequence of microARN
     * @param position where begin the comparison
     * @return
     */
    void generateScoreColumn(const biopp::SecStructure& structure, const biopp::NucSequence& seqRna, const biopp::NucSequence& microRna, const size_t microStart);

};

//Zuker const
static const DeltaG ZUKER_AU = -2;
static const DeltaG ZUKER_GC = -3;

REGISTER_FACTORIZABLE_CLASS(TablesGenerator, OldTablesGenerator, std::string, "OldTablesGenerator");

OldTablesGenerator::~OldTablesGenerator()
{
    delete folderImpl;
}

void OldTablesGenerator::initialize(GetOpt_pp& args) {
    string folder;
    args >> Option('f', "folder", folder);
    folderImpl = (FactoryRegistry<IFold, string>::new_class(folder));
    if (folderImpl == NULL)
        throw InvalidFolder();
}

inline size_t OldTablesGenerator::IndexConverter::getMaxPos() const
{
    return circ ? seqRNAmSize - 1 :  seqRNAmSize - microRNASize;
}

inline size_t OldTablesGenerator::IndexConverter::convertIndex(size_t idx) const
{
    size_t ret;
    if (idx < seqRNAmSize)
        ret = idx;
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
    oFile << "ScoreZukHum" << endl;
}

void OldTablesGenerator::generateSequencesGroupRow(const NucSequence& sequenceRNA, const NucSequence& miRNA, const SecStructure& secondaryStructure, const IndexConverter& converter, const size_t miRnaStart)
{
    string col1;
    string col2;
    string col3;
    char col1Char;
    char col2Char;
    size_t uppercaseCount = 0;
    size_t mCount = 0;
    for (size_t i = 0; i < miRNA.length(); ++i)
    {
        const size_t idx = converter.convertIndex(i + miRnaStart);
        col1Char = column1Seq(miRNA[idx], sequenceRNA[idx]);
        if (col1Char == toupper(col1Char))
            uppercaseCount++;
        col1 += col1Char;

        col2Char = column2Seq(miRNA[idx], sequenceRNA[idx], secondaryStructure.is_paired(i));
        if (col2Char == 'M')
            mCount++;
        col2 += col2Char;

        col3 += column3Seq(idx, secondaryStructure, sequenceRNA);
    }
    oFile << col1 << "," << col2 << "," << col3 << "," << uppercaseCount << "," << mCount;
}

void OldTablesGenerator::generateScoreColumn(const SecStructure& structureRNA, const NucSequence& seqRna, const NucSequence& microRna, const size_t microStart)
{
    PairedTypeArray counterMsgMsg;
    PairedTypeArray counterMsgMicro;

    countPaired(structureRNA, seqRna, microStart, microRna.length(), counterMsgMsg);
    countPaired(seqRna, microRna, microStart, counterMsgMicro);

    DeltaG col =  ZUKER_AU * (DeltaG(counterMsgMicro[auType]) - DeltaG(counterMsgMsg[auType])) +  ZUKER_GC * (DeltaG(counterMsgMicro[cgType]) - DeltaG(counterMsgMsg[cgType]));

    if (col != -0.0)
        oFile << col;
    else
        oFile << 0;
}

void OldTablesGenerator::generateTableRow(const string nameMicro, const NucSequence& RNAm, const NucSequence& rnaHumanized, const NucSequence& miRNA, const SecStructure& secondaryStructureRNAm, const SecStructure& secondaryStructureHum, IndexConverter& idxConvert, const size_t miRnaStart)
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
    oFile << endl;
}

char OldTablesGenerator::column1Seq(const Nucleotide nucMiRNA, const Nucleotide nucRNAm)
{
    char ret;
    if (nucMiRNA == nucRNAm)
        ret = toupper(nucRNAm.as_char());
    else
        ret = tolower(nucRNAm.as_char());
    return ret;
}

char OldTablesGenerator::column2Seq(const Nucleotide nucMiRNA, const Nucleotide nucRNAm, bool isMsgPaired)
{
    char ret;
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
        ret = tolower(nucRNAm.as_char());
    return ret;
}

OldTablesGenerator::PairedType OldTablesGenerator::get_pairedType(SeqIndex i, const biopp::SecStructure& structure, const biopp::NucSequence& sequence)
{
    PairedType ret;
    if (!structure.is_paired(i))
        ret = Unpaired;
    else
    {
        Comp c(sequence[i], sequence[structure.paired_with(i)]);
        if (c.compare(Nucleotide(Nucleotide::A), Nucleotide(Nucleotide::U)))
            ret = auType;
        else if (c.compare(Nucleotide(Nucleotide::C), Nucleotide(Nucleotide::G)))
            ret = cgType;
        else if (c.compare(Nucleotide(Nucleotide::G), Nucleotide(Nucleotide::U)))
            ret = guType;
        else
            ret = othersType;
    }
    return ret;
}

OldTablesGenerator::PairedType OldTablesGenerator::get_ComplementType(const biopp::Nucleotide n1, const biopp::Nucleotide n2)
{
    PairedType ret;
    Comp c(n1, n2);
    if (c.compare(Nucleotide(Nucleotide::A), Nucleotide(Nucleotide::U)))
        ret = auType;
    else if (c.compare(Nucleotide(Nucleotide::C), Nucleotide(Nucleotide::G)))
        ret = cgType;
    else if (c.compare(Nucleotide(Nucleotide::G), Nucleotide(Nucleotide::U)))
        ret = guType;
    else
        ret = Unpaired;
    return ret;
}

char OldTablesGenerator::column3Seq(size_t index, const SecStructure& structure, const NucSequence& sequence)
{
    const PairedType pType = get_pairedType(index, structure, sequence);
    char ret;
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

void OldTablesGenerator::countPaired(const SecStructure& structure, const NucSequence& sequence, size_t microStart, size_t microRnaLength, PairedTypeArray& pCount)
{
    for (size_t i = 0; i < typeCount; ++i)
    {
        pCount[i] = 0;
    }
    for (size_t i = 0; i < microRnaLength; ++i)
    {
        pCount[get_pairedType(i + microStart, structure, sequence)]++;
    }
}

//Should disappear in iteracion4. The hybridization provides structure between mRNA and microRNA
void OldTablesGenerator::countPaired(const NucSequence& rnamSequence, const NucSequence& microSequence, size_t microStart, PairedTypeArray& pCount)
{
    for (size_t i = 0; i < typeCount; ++i)
    {
        pCount[i] = 0;
    }
    const size_t indexMax = microSequence.length();
    Nucleotide nucComp;
    for (size_t i = 0; i < indexMax; ++i)
    {
        nucComp = microSequence[i];
        nucComp.complement();
        pCount[get_ComplementType(nucComp, rnamSequence[i + microStart])]++;
    }
}

void OldTablesGenerator::fold(const NucSequence& seqRnaM, const NucSequence& seqHumRnaM) {
    folderImpl->fold(seqRnaM, structRNAm, isCirc);
    folderImpl->fold(seqHumRnaM, structHumanized, isCirc);
}

void OldTablesGenerator::generate(const std::string& tableName, const NucSequence& rnaMsg, const NucSequence& rnaMHumanized, bool circ)
{
    rnaM = rnaMsg;
    rnaMHum = rnaMHumanized;
    isCirc = circ;
    fold(rnaM,rnaMHum);
    if (oFile.is_open())
        oFile.close();
    oFile.open(tableName.c_str());
    if (!oFile)
        throw FileNotCreate();
    generateHeader();
}

void OldTablesGenerator::appendMicro(const NucSequence& miRna, const string& nameMicro)
{
    assert(rnaM.length() == rnaMHum.length());
    assert(structRNAm.size() == structHumanized.size());

    IndexConverter cIndex(rnaM.length(), isCirc, miRna.length());
    NucSequence mirnaCompl(miRna);
    mirnaCompl.complement();
    const size_t maxIndex = cIndex.getMaxPos();
    for (size_t i = 0; i < maxIndex ; ++i)
    {
        generateTableRow(nameMicro, rnaM, rnaMHum, mirnaCompl, structRNAm, structHumanized, cIndex, i);
    }
}
