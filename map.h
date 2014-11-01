/*
 * map.h
 *
 *  Created on: May 25, 2014
 *      Author: erik
 */

#ifndef MAP_H
#define MAP_H

#include "glm/glm.hpp"
#include <vector>

#include "drawable.h"
#include "file_loader.h"
#include "line_reader.h"
#include "string_tokenizer.h"
#include "texture.h"

struct Tile {
        std::vector<glm::vec3*> vertices;
        Tile(std::vector<glm::vec3*> v) :
                vertices(v) {
        }
        ;
};

struct Cell {
        int size;

        int indicies[9][2];

        Cell(int x, int z) {
            size = 9;
            int offset[9][2] = { { -1, 1 }, { 0, 1 }, { 1, 1 }, { -1, 0 }, { 0, 0 }, { 1, 0 }, { -1, -1 }, { 0, -1 }, { 1, -1 } };

            for (int i = 0; i < size; i++) {
                indicies[i][0] = x + offset[i][0];
                indicies[i][1] = z + offset[i][1];
            }
        }
        ;
};

struct Block {
        int size;

        Cell* cells[9];

        int currentC;

        Block(int x, int z) {
            size = 9;
            int offset[9][2] = { { -3, 3 }, { 0, 3 }, { 3, 3 }, { -3, 0 }, { 0, 0 }, { 3, 0 }, { -3, -3 }, { 0, -3 }, { 3, -3 } };

            currentC = 0;

            for (int i = 0; i < size; i++) {
                cells[i] = new Cell(x + offset[i][0], z + offset[i][1]);
            }
        }

        Cell* getNextCell() {
            Cell* cell = cells[currentC];

            if (currentC < size) currentC++;

            return cell;
        }

        bool hasNextCell() {
            return currentC < size;
        }
};

struct Sector {
        int size;

        Block* blocks[9];

        int currentB;

        Sector(int x, int z) {
            size = 9;
            int offset[9][2] = { { -9, 9 }, { 0, 9 }, { 9, 9 }, { -9, 0 }, { 0, 0 }, { 9, 0 }, { -9, -9 }, { 0, -9 }, { 9, -9 } };

            currentB = 0;

            for (int i = 0; i < size; i++) {
                blocks[i] = new Block(x + offset[i][0], z + offset[i][1]);
            }
        }

        Block* getNextBlock() {
            Block* block = blocks[currentB];

            if (currentB < size) currentB++;

            return block;
        }

        bool hasNextBlock() {
            return currentB < size;
        }
};

struct DisplayGrid {
        int size;
        Sector* sectors[9];
        int grid[6561][2];

        int currentS;

        DisplayGrid() {
            size = 9;
            int offset[9][2] = { { -27, 27 }, { 0, 27 }, { 27, 27 }, { -27, 0 }, { 0, 0 }, { 27, 0 }, { -27, -27 }, { 0, -27 }, { 27, -27 } };

            currentS = 0;

            for (int i = 0; i < size; i++) {
                sectors[i] = new Sector(offset[i][0], offset[i][1]);
            }

            int cellCount = 0;
            while (hasNextSector()) {
                Sector* sector = getNextSector();
                while (sector->hasNextBlock()) {
                    Block* block = sector->getNextBlock();
                    while (block->hasNextCell()) {
                        Cell* cell = block->getNextCell();
                        for (int i = 0; i < cell->size; i++) {
                            grid[cellCount][0] = cell->indicies[i][0];
                            grid[cellCount][1] = cell->indicies[i][1];

                            cellCount++;
                        }
                    }
                }
            }
        }
        ;

        Sector* getNextSector() {
            Sector* sector = sectors[currentS];

            if (currentS < size) currentS++;

            return sector;
        }

        bool hasNextSector() {
            return currentS < size;
        }
};

class Map: public Drawable {
    private:
        float xpos, ypos, zpos, yrot;

        int mapSizeX;
        int mapSizeZ;

        DisplayGrid* displayGrid;

        std::vector<std::vector<float> > heights;
        std::vector<std::vector<Tile*> > tiles;

        FileLoader* fileloader;

        void load();

    public:
        Map();
        ~Map();

        /**
         * draw()
         * inherited from Drawable
         **/
        void draw();

        /**
         * update()
         * inherited from GameObject
         **/
        void update();

        float getYforPos(float xpos, float zpos);
        void setPos(float x, float z);
        void setYrot(float yrot);
};

#endif
