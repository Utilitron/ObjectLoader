/*
 * face.h
 *
 *  Created on: Feb 15, 2014
 *      Author: Erik Ashcraft
 */

#ifndef FACE_H
#define FACE_H

#include <string>
#include <vector>

class Face {
    public:
        Face(std::vector<int> v, std::vector<int> n) {
            vertices = v;
            normals = n;
            material = "";
        };

        Face(std::vector<int> v, std::vector<int> c, std::vector<int> n, std::string m) {
            vertices = v;
            coordinates = c;
            normals = n;
            material = m;
        }
        ;
        ~Face();

        std::vector<int> vertices;
        std::vector<int> coordinates;
        std::vector<int> normals;
        std::string material;
};

#endif
