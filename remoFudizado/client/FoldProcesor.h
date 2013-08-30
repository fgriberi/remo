/**
 * @file     FoldProcessor.h
 * @details  FoldProcessor provides the interface for remo client (folding)
 *
 * @author   Franco Riberi
 * @email    fgriberi AT gmail.com
 *
 * Contents: Header file for FoldProcessor interface.
 *
 * System:   remo: RNAemo - RNA research project
 * Language: C++
 *
 * @date    March 26, 2013
 *
 * This file is part of R-emo.
 *
 * Copyright (C) 2013 - Franco Riberi, FuDePAN.
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
 * along with R-emo. If not, see <http://www.gnu.org/licenses/>.
 *
 */

#ifndef FOLD_PROCESSOR_H
#define FOLD_PROCESSOR_H

#include <vector>
#include <fideo/fideo.h>
#include <fud/fud.h>

namespace fud
{
typedef std::vector<std::string> ResultLine;

/**
 * Provides the interface for remo client (folding)
 */
class FoldProcessor : ClientProcessor
{
public:
    FoldProcessor();

    virtual bool process(InputMessage& input, OutputMessage& output);

private:

    /**
    * Destructor of class
    */
    ~FoldProcessor();

    /** @brief Parse the input data coming from the server
     *
     * @param input: input data
     * @param result: to fill with the result of the parse
     * @return void
     */
    void parseInput(const std::string& input, ResultLine& result);

    /** @brief Build the result to send to the server
     *
     * @param nameSeq: sequence name
     * @param nameFile: name file
     * @param output: to fill with the result obtained by the current client
     * @return void
     */
    void buildOutput(const std::string& nameSeq, const std::string& nameFile, std::string& output);

    /** @brief Process a current sequence (folding)
     *
     * @param sequence: sequence to process
     * @param nameOutputFile: generated name file
     * @return void
     */
    void processSequence(const std::string& sequence, fideo::FilePath& nameOutputFile);

    /** @brief Copy contents of a file into a string
     *
     * @param nameFile: input name file
     * @param outputData: to fill with contents of file
     * @return void
     */
    void fileToString(const std::string& nameFile, std::string& outputData);

    /** @brief Specific backend to folding
     *
     */
    static const std::string _backend;

    /** @brief File extension
     *
     */
    static const std::string _det;

    /**
     * Specific backend to folder
     */
    fideo::IFold* _folder;
};
}

#endif /* FOLD_PROCESSOR_H */