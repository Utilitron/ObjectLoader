/*
 * material.h
 *
 *  Created on: Feb 15, 2014
 *      Author: Erik Ashcraft
 *
 *  diffuse  				= Kd	float float float
 *  ambient  				= Ka	float float float
 *  specular 				= Ks	float float float
 *  specular_coefficient 	= Ns 	float
 *  opacity 				= d		float
 *  optical_density			= Ni	float
 *  illumination			= illum	int
 */

#ifndef MATERIAL_H
#define MATERIAL_H

#include <string>
#include <vector>
#include "texture.h"

class Material {
    public:
        Material(std::string newmtl, float Kd[3], float Ka[3], float Ks[3], float Ns, float d, float Ni, int illum) {
            name = newmtl;
            diffuse[3] = Kd[3];
            ambient[3] = Ka[3];
            specular[3] = Ks[3];
            specular_coefficient = Ns;
            opacity = d;
            optical_density = Ni;
            illumination = illum;
            hasTexture = false;
        }
        Material(std::string newmtl, float Kd[3], float Ka[3], float Ks[3], float Ns, float d, float Ni, int illum, Texture* tex) {
            name = newmtl;
            diffuse[3] = Kd[3];
            ambient[3] = Ka[3];
            specular[3] = Ks[3];
            specular_coefficient = Ns;
            opacity = d;
            optical_density = Ni;
            illumination = illum;

            texture = tex;
            hasTexture = true;
        }
        ~Material();

        std::string name;

        float opacity, optical_density, specular_coefficient;
        float diffuse[3], ambient[3], specular[3];
        int illumination;
        Texture* texture;
        bool hasTexture;
};

#endif
