/**
 * @file     HumanizedJobDistributable.h
 * @brief    Interface that allows distribute the folding of humanized sequence.
 *
 * @author Franco Riberi
 * @email  fgriberi AT gmail.com
 *
 * Contents:  Header file for remo server providing HumanizedJobDistributable interface.
 *
 * System:    remo: RNAemo - RNA research project
 * Language:  C++
 *
 * @date      August 2013
 *
 * This file is part of remo.
 *
 * Copyright (C) 2013 - Franco Riberi, FuDePAN.
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
 * along with Remo. If not, see <http://www.gnu.org/licenses/>.
 *
 */

#ifndef HUMANIZED_JOB_DISTRIBUTABLE_H
#define HUMANIZED_JOB_DISTRIBUTABLE_H

#include <vector>
#include <fstream>
#include <string>
#include <biopp-filer/bioppFiler.h>
#include <biopp/biopp.h>
#include <acuoso/acuoso.h>
#include <fud/fud_server.h>

using namespace fud;

typedef std::vector<std::string> ResultLine;
class HumanizedJobDistributable : public DistributableJobImplementation
{
    public:
        
        HumanizedJobDistributable(const std::string& nameFile, const acuoso::ICodonUsageModifier* humanizer);
        virtual ~HumanizedJobDistributable(){};

    private:
        
        virtual void handle_results (JobUnitID id, InputMessage& input);
        virtual DistributableJobStatus get_status() const;
        virtual const char* get_name() const;
        virtual JobUnit* produce_next_job_unit(JobUnitSize size);

        class HumJobDistributableJobUnit : public JobUnit
        {
            public:

                HumJobDistributableJobUnit(char* message, JobUnitSize size);

            private:
                virtual const char*  method_name_required() const; 
                virtual ~HumJobDistributableJobUnit(){};
                virtual const std::string& get_message()    const;
                std::string _message;
        };

        void parseInput(const std::string& input, ResultLine& output);
        void stringToFile(const std::string& inputLine, const std::string& nameOutputFile);
        void generateFiles(const ResultLine& data);
        void getNameSequence(const std::string& lineToParse, std::string& nameSeq);
        void getHumanizedSequence(const biopp::NucSequence& origSeq, biopp::NucSequence& humanizedSeq);
        void replaceHumanizedSection(const biopp::NucSequence& originalSeq, const biopp::NucSequence& humanizedSeq,
                                     const size_t initNucIndex, biopp::NucSequence& toFoldSeq);

        bioppFiler::FastaParser<biopp::NucSequence> _fileFasta;      
        bool _nextSequence;
        const acuoso::ICodonUsageModifier* _humanizer;        
};

#endif