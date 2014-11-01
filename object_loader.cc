/*
 * object_loader.cc
 *
 *  Created on: Feb 9, 2014
 *      Author: Erik Ashcraft
 */

#include <sstream>
#include <string>
#include <algorithm>
#include <vector>
#include <fstream>

#include "object_loader.h"
#include "face.h"
#include "glm/glm.hpp"
#include "material.h"
#include "line_reader.h"
#include "string_tokenizer.h"
#include "texture.h"

ObjectLoader::ObjectLoader(Loadable target, std::string filepath) :
        obj(target) {
    loadObject(filepath);
}

void ObjectLoader::loadObject(std::string filepath) {
    LineReader* objfile = loadFile(filepath);
    std::string usemtl = "";

    while (objfile->hasNextLine()) {
        std::string* objline = objfile->getNextLine();

        StringTokenizer* line = new StringTokenizer(objline, ' ');
        if (line->hasNextToken()) {
            std::string* token = line->getNextToken();

            if (token->compare("mtllib") == 0) {
                LineReader* matfile = loadFile((*line->getNextToken()));

                while (matfile->hasNextLine()) {
                    std::string* matline = matfile->getNextLine();

                    StringTokenizer* mat = new StringTokenizer(matline, ' ');
                    if (mat->hasNextToken()) {
                        std::string* mattoken = mat->getNextToken();

                        if (mattoken->compare("newmtl") == 0) {
                            std::string newmtl = *mat->getNextToken();
                            float Kd[3];
                            float Ka[3];
                            float Ks[3];
                            float Ns;
                            float d;
                            float Ni;
                            int illum;
                            char cBuffer[] = "";

                            if (matfile->hasNextLine()) {
                                bool parsemat = true;
                                while (parsemat) {
                                    matline = matfile->getNextLine();
                                    mat = new StringTokenizer(matline, ' ');
                                    //printf("%s\n", matline->c_str());
                                    if (mat->hasNextToken()) {
                                        mattoken = mat->getNextToken();

                                        if (mattoken->compare("Kd") == 0) sscanf(matline->c_str(), "Kd %f %f %f", &Kd[0], &Kd[1], &Kd[2]);

                                        else if (mattoken->compare("Ka") == 0) sscanf(matline->c_str(), "Ka %f %f %f", &Ka[0], &Ka[1], &Ka[2]);

                                        else if (mattoken->compare("Ks") == 0) sscanf(matline->c_str(), "Ks %f %f %f", &Ks[0], &Ks[1], &Ks[2]);

                                        else if (mattoken->compare("Ns") == 0) sscanf(matline->c_str(), "Ns %f", &Ns);

                                        else if (mattoken->compare("d") == 0) sscanf(matline->c_str(), "d %f", &d);

                                        else if (mattoken->compare("Ni") == 0) sscanf(matline->c_str(), "Ni %f", &Ni);

                                        else if (mattoken->compare("illum") == 0) sscanf(matline->c_str(), "illum %i", &illum);

                                        else if (mattoken->compare("map_Kd") == 0) {
                                            sscanf(matline->c_str(), "map_Kd %s", &cBuffer);
                                        }
                                    } else parsemat = false;

                                    if (!matfile->hasNextLine() || mattoken->compare("") == 0) parsemat = false;
                                }
                            }

                            if (strlen(cBuffer) == 0) obj.materials.push_back(new Material(newmtl, Kd, Ka, Ks, Ns, d, Ni, illum));
                            else {
                                Texture* texture = loadTexture(std::string(cBuffer));
                                obj.materials.push_back(new Material(newmtl, Kd, Ka, Ks, Ns, d, Ni, illum));
                            }
                        }
                    }
                }
            } else if (token->compare("usemtl") == 0) {
                usemtl = *line->getNextToken();

            } else if (token->compare("vn") == 0) {
                float tmpx, tmpy, tmpz;
                sscanf(objline->c_str(), "vn %f %f %f", &tmpx, &tmpy, &tmpz);
                obj.normals.push_back(new glm::vec3(tmpx, tmpy, tmpz));
            } else if (token->compare("vt") == 0) {
                float tmpu, tmpv;
                sscanf(objline->c_str(), "vt %f %f", &tmpu, &tmpv);
                obj.coordinates.push_back(new glm::vec2(tmpu, 1 - tmpv));
            } else if (token->compare("v") == 0) {
                float tmpx, tmpy, tmpz;
                sscanf(objline->c_str(), "v %f %f %f", &tmpx, &tmpy, &tmpz);
                obj.vertices.push_back(new glm::vec3(tmpx, tmpy, tmpz));
            } else if (token->compare("f") == 0) {
                std::vector<int> vertices;
                std::vector<int> coordinates;
                std::vector<int> normals;
                while (line->hasNextToken()) {
                    token = line->getNextToken();
                    std::size_t pos = objline->find("/");
                    if (pos != std::string::npos) {
                        std::istringstream buff(token->c_str());
                        int count = 0;
                        for (std::string subtoken; getline(buff, subtoken, '/');) {
                            if (count == 0) vertices.push_back(std::atoi(subtoken.c_str()));
                            if (count == 1) coordinates.push_back(std::atoi(subtoken.c_str()));
                            if (count == 2) normals.push_back(std::atoi(subtoken.c_str()));

                            count++;
                        }
                    } else vertices.push_back(std::atoi(token->c_str()));

                    if (usemtl.compare("") == 0) obj.faces.push_back(new Face(vertices, normals));
                    else obj.faces.push_back(new Face(vertices, coordinates, normals, usemtl));
                }
            }
        }
    }
}
