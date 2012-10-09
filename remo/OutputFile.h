/**
 *  @file:      OutputFile.h
 *  @details    System: R-emo \n
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
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with R-emo .  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#ifndef OUTPUT_FILE_H
#define OUTPUT_FILE_H

#include "mili/mili.h"

class OutputFile
{
public:
    struct score
    {
        double PercentageMatching;
        double ZukerMatching;
        double PercentageMasked;
        double ZukerMasked;    
    };

    struct  
    {
        //RNAm original
        std::string seqComplementRNAmOrig;
        std::string seqMaskedRNAmOrig;
        std::string seqXYZRNAmOrig;       
        struct score scoresRNAmOrig;

        //RNAm humanizado
        std::string seqComplementRNAmHumanized;
        std::string seqMaskedRNAmHumanized;
        std::string seqXYZRNAmHumanized;                                    
        struct score scoresRNAmHumanized;
    }dataToFile;

    OutputFile();        
    OutputFile(const std::string& fileName);        
    ~OutputFile(){}
       
};
#endif /* OUTPUT_FILE_H */
