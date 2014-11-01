/*
 * line_reader.h
 *
 *  Created on: Feb 16, 2014
 *      Author: Erik Ashcraft
 */

#ifndef LINE_READER_H
#define LINE_READER_H

#include <string>
#include <vector>

class LineReader {
    private:
        std::vector<std::string*>* linebuffer;
        int linenum;

    public:
        LineReader(std::vector<std::string*>* buffer) {
            linebuffer = buffer;
            linenum = 0;
        }
        ~LineReader();

        std::string* getNextLine() {
            std::string* line = linebuffer->at(linenum);
            linenum++;
            return line;
        }

        bool hasNextLine() {
            return linenum < linebuffer->size();
        }

        bool numLines() {
            return linebuffer->size();
        }
};

#endif
