/*
 * map.cc
 *
 *  Created on: May 25, 2014
 *      Author: erik
 */

#include "map.h"

Map::Map(): xpos(0), ypos(0), zpos(0) {
	addTexture(fileloader.loadTexture("src/resources/grass.tga"));
	addTexture(fileloader.loadTexture("src/resources/rock.tga"));

	load();
}

Map::~Map(){

}

void Map::draw(){
	// Set the default draw color to white
	glColor3f(1.0f, 1.0f, 1.0f);

	glEnable(GL_TEXTURE_2D);

	float yrotrad = (yrot / 180 * 3.141592654f);

	float xposoffset = xpos + float(sin(yrotrad)) * 64.0;
	float zposoffset = zpos - float(cos(yrotrad)) * 64.0;

	int x = ((int)floor(xposoffset) + 512)/2;
	int z = ((int)floor(zposoffset) + 512)/2;

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	for (int i = 0; i < 6561; i++){
		int xIndex = x + displayGrid.grid[i][0];
		int zIndex = z + displayGrid.grid[i][1];

		// We need to project tiles out of bounds as if they are infront of us
		float xoffset = 0.0f, zoffset = 0.0f;

		// Make sure the indecies don't go out of bounds!
		// wrap them to the begining!
		if (xIndex >= (int)tiles.size()){
			xIndex -= (int)tiles.size();
			xoffset += (float)tiles.size() * 2;
		}

		if (xIndex <= -1){
			xIndex += (int)tiles.size();
			xoffset -= (float)tiles.size() * 2;
		}

		if (zIndex >= (int)tiles[0].size()){
			zIndex -= (int)tiles[0].size();
			zoffset += (float)tiles[0].size() * 2;
		}

		if (zIndex <= -1){
			zIndex += (int)tiles[0].size();
			zoffset -= (float)tiles[0].size() * 2;
		}

		Tile* tile = tiles[xIndex][zIndex];
		int texnum = 0;
		if (tile->vertices[0]->y >= 12.0f)
			texnum = 1;

		glBindTexture(GL_TEXTURE_2D, textures[texnum]->num);
		int s = 0,t = 0;
		glBegin(GL_QUADS);
			for (int j = 0; j < 4; j++){
				glTexCoord2f(s, t);
				glVertex3f(tile->vertices[j]->x + xoffset,
						    tile->vertices[j]->y,
							tile->vertices[j]->z + zoffset);

				if (t == 0) t = 1;
				else s = 1, t = 0;
			}
		glEnd();
	}

	glDisable(GL_TEXTURE_2D);
}

void Map::update(){}

void Map::load(){
	heights = fileloader.loadHeightMap("src/resources/heightmap.bmp");
	mapSizeX = heights.size();
	mapSizeZ = heights[0].size();

	std::vector<Tile*> tmp;
	for (int i = 0; i < mapSizeX; i++){
		tmp.clear();
		for (int j = 0; j < mapSizeZ; j++){
			std::vector<glm::vec3*> vertices;
			float x = (i*2)-mapSizeX;
			float z = (j*2)-mapSizeZ;
			float nextX = x + 2;
			float nextZ = z + 2;

			vertices.push_back(new glm::vec3(x, getYforPos(x,z) - 1.0, z));
			vertices.push_back(new glm::vec3(x, getYforPos(x,nextZ) - 1.0, nextZ));
			vertices.push_back(new glm::vec3(nextX, getYforPos(nextX,nextZ) - 1.0, nextZ));
			vertices.push_back(new glm::vec3(nextX, getYforPos(nextX,z) - 1.0, z));
			tmp.push_back(new Tile(vertices));
		}
		tiles.push_back(tmp);
	}
}

float Map::getYforPos(float xpos, float zpos){
	int x = ((int)floor(xpos) + 512)/2;
	int z = ((int)floor(zpos) + 512)/2;

	// Make sure the indecies don't go out of bounds!
	// wrap them to the begining!
	if (x >= (int)heights.size())
		x -= (int)heights.size();
	if (x <= -1)
		x += (int)heights.size();

	if (z >= (int)heights[0].size())
		z -= (int)heights[0].size();
	if (z <= -1)
		z += (int)heights[0].size();

	return heights[x][z] * 64;
}

void Map::setPos(float x, float z){
	this->xpos = x;
	this->zpos = z;
}

void Map::setYrot(float yrot){
	this->yrot = yrot;
}
