/*
 * object_loader.h
 *
 *  Created on: Feb 9, 2014
 *      Author: Erik Ashcraft
 */

#ifndef OBJECT_LOADER_H
#define OBJECT_LOADER_H

#include <string>

#include "file_loader.h"
#include "loadable.h"

class ObjectLoader: public FileLoader {
    private:
        void loadObject(std::string filename);

    public:
        ObjectLoader(Loadable target, std::string filename);
        ~ObjectLoader();

        Loadable obj;
};

#endif
