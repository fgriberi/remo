/**
 * @file     OriginalJobDistributable.h
 * @brief    Interface that allows distribute the folding of original sequence.
 *
 * @author Franco Riberi
 * @email  fgriberi AT gmail.com
 *
 * Contents:  Header file for remo server providing OriginalJobDistributable interface.
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

#ifndef ORIGINAL_JOB_DISTRIBUTABLE_H
#define ORIGINAL_JOB_DISTRIBUTABLE_H

#include <vector>
#include <fstream>
#include <string>
#include <biopp-filer/bioppFiler.h>
#include <biopp/biopp.h>
#include <fud/fud.h>

using namespace fud;

typedef std::vector<std::string> ResultLine;
class OriginalJobDistributable : public DistributableJobImplementation
{
    public:
        
        OriginalJobDistributable(const std::string& nameFile);
        virtual ~OriginalJobDistributable(){};

    private:
        
        virtual void handle_results (JobUnitID id, InputMessage& input);
        virtual DistributableJobStatus get_status() const;
        virtual const char* get_name() const;
        virtual JobUnit* produce_next_job_unit(JobUnitSize size);

        class OrigJobDistributableJobUnit : public JobUnit
        {
            public:

                OrigJobDistributableJobUnit(char* message, JobUnitSize size);

            private:
                virtual const char*  method_name_required() const; 
                virtual ~OrigJobDistributableJobUnit(){};
                virtual const std::string& get_message()    const;
                std::string _message;
        };

        void parseInput(const std::string& input, ResultLine& output);
        void stringToFile(const std::string& inputLine, const std::string& nameOutputFile);
        void generateFiles(const ResultLine& data);
        void getNameSequence(const std::string& lineToParse, std::string& nameSeq);
        bool nextSequence() const;        

        bioppFiler::FastaParser<biopp::NucSequence> _fileFasta;      
        bool _nextSequence;
};

#endif