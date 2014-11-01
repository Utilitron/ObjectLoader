/*
 * file_loader.cc
 *
 *  Created on: Feb 16, 2014
 *      Author: Erik Ashcraft
 */

#include "file_loader.h"

FileLoader::FileLoader() {
}
FileLoader::~FileLoader() {
}

LineReader* FileLoader::loadFile(std::string filepath) {
    std::vector<std::string*>* filebuffer = new std::vector<std::string*>();

    std::ifstream in(filepath.c_str());

    if (!in.is_open()) {
        printf("ERROR: Could not load file.");
    } else {
        char buf[256];
        while (!in.eof()) {
            in.getline(buf, 256);
            std::string* tmp = new std::string(buf);
            filebuffer->push_back(tmp);
        }
    }

    return new LineReader(filebuffer);
}

SDL_Surface* FileLoader::loadBmp(std::string filepath) {
    return SDL_LoadBMP(filepath.c_str());	//load the bmp image;
}

// Define targa header. This is only used locally.
#pragma pack(1)
typedef struct {
        GLbyte identsize;              // Size of ID field that follows header (0)
        GLbyte colorMapType;           // 0 = None, 1 = paletted
        GLbyte imageType;              // 0 = none, 1 = indexed, 2 = rgb, 3 = grey, +8=rle
        unsigned short colorMapStart;          // First colour map entry
        unsigned short colorMapLength;         // Number of colors
        unsigned char colorMapBits;   // bits per palette entry
        unsigned short xstart;                 // image x origin
        unsigned short ystart;                 // image y origin
        unsigned short width;                  // width in pixels
        unsigned short height;                 // height in pixels
        GLbyte bits;                   // bits per pixel (8 16, 24, 32)
        GLbyte descriptor;             // image descriptor
} TGAHEADER;
#pragma pack(8)

GLbyte* FileLoader::loadTGA(std::string filepath, GLint *iWidth, GLint *iHeight, GLint *iComponents, GLenum *eFormat) {
    FILE *pFile;				// File pointer
    TGAHEADER tgaHeader;		// TGA file header
    unsigned long lImageSize;	// Size in bytes of image
    short sDepth;				// Pixel depth;
    GLbyte *pBits = NULL;      // Pointer to bits

    // Default/Failed values
    *iWidth = 0;
    *iHeight = 0;
    *eFormat = GL_BGR_EXT;
    *iComponents = GL_RGB8;

    // Attempt to open the file
    pFile = fopen(filepath.c_str(), "rb");
    if (pFile == NULL) {
        printf("tga is not loaded");
        return NULL;
    } else {
        // Read in header (binary)
        fread(&tgaHeader, 18/* sizeof(TGAHEADER)*/, 1, pFile);

        // Get width, height, and depth of texture
        *iWidth = tgaHeader.width;
        *iHeight = tgaHeader.height;
        sDepth = tgaHeader.bits / 8;

        // Put some validity checks here. Very simply, I only understand
        // or care about 8, 24, or 32 bit targa's.
        if (tgaHeader.bits != 8 && tgaHeader.bits != 24 && tgaHeader.bits != 32) return NULL;

        // Calculate size of image buffer
        lImageSize = tgaHeader.width * tgaHeader.height * sDepth;

        // Allocate memory and check for success
        pBits = (GLbyte*) malloc(lImageSize * sizeof(GLbyte));
        if (pBits == NULL) return NULL;

        // Read in the bits
        // Check for read error. This should catch RLE or other
        // weird formats that I don't want to recognize
        if (fread(pBits, lImageSize, 1, pFile) != 1) {
            free(pBits);
            return NULL;
        }

        // Set OpenGL format expected
        switch (sDepth) {
            case 3:     // Most likely case
                *eFormat = GL_BGR_EXT;
                *iComponents = GL_RGB8;
                break;
            case 4:
                *eFormat = GL_BGRA_EXT;
                *iComponents = GL_RGBA8;
                break;
            case 1:
                *eFormat = GL_LUMINANCE;
                *iComponents = GL_LUMINANCE8;
                break;
        };

        // Done with File
        fclose(pFile);

        // Return pointer to image data
        return pBits;
    }
}

Texture* FileLoader::loadTexture(std::string filepath) {
    GLuint num;	//the id for the texture
    GLbyte *pBytes;
    GLint iWidth, iHeight, iComponents;
    GLenum eFormat;

    glGenTextures(1, &num);	//we generate a unique one
    glBindTexture(GL_TEXTURE_2D, num);	//and use the texture, we have just generated

    pBytes = loadTGA(filepath, &iWidth, &iHeight, &iComponents, &eFormat);
    gluBuild2DMipmaps(GL_TEXTURE_2D, iComponents, iWidth, iHeight, eFormat, GL_UNSIGNED_BYTE, pBytes);
    free(pBytes);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    return new Texture(num, iWidth, iHeight);	//and we return the id
}

Texture* FileLoader::loadParitcleTexture(std::string filepath) {
    GLuint num;	//the id for the texture
    GLbyte *pBytes;
    GLint iWidth, iHeight, iComponents;
    GLenum eFormat;

    glGenTextures(1, &num);	//we generate a unique one
    glBindTexture(GL_TEXTURE_2D, num);	//and use the texture, we have just generated

    pBytes = loadTGA(filepath, &iWidth, &iHeight, &iComponents, &eFormat);
    gluBuild2DMipmaps(GL_TEXTURE_2D, iComponents, iWidth, iHeight, eFormat, GL_UNSIGNED_BYTE, pBytes);
    free(pBytes);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);

    return new Texture(num, iWidth, iHeight);	//and we return the id
}

std::vector<std::vector<float> > FileLoader::loadHeightMap(std::string filepath) {
    std::vector<std::vector<float> > heights;
    SDL_Surface* img = loadBmp(filepath);
    if (!img) {
        printf("image is not loaded");
    } else {
        std::vector<float> tmp;
        for (int i = 0; i < img->h; i++) {
            tmp.clear();
            for (int j = 0; j < img->w; j++) {
                Uint32 pixel = ((Uint32*) img->pixels)[i * img->pitch / 4 + j];
                Uint8 r, g, b;	//unsigned char
                SDL_GetRGB(pixel, img->format, &r, &g, &b);
                tmp.push_back((float) (r / 255.0));	//0.0,1.0
            }
            heights.push_back(tmp);
        }
    }

    return heights;
}

/*
 GLuint FileLoader::loadShader(std::string filepath, GLuint mode) {
 GLuint num = glCreateShader(mode);	//we generate a unique one

 LineReader* file = loadFile(filepath);

 std::string source;
 while (file->hasNextLine()){
 source += *file->getNextLine();
 source += '\n';
 }

 const char* csource = source.c_str();

 glShaderSource(num, file->numLines(), &csource, NULL);
 glCompileShader(num);

 char error[1000];
 glGetShaderInfoLog(num, 1000, NULL, error);
 printf("ERROR:\n %c", error);

 return num;	//and we return the id
 }

 GLuint FileLoader::loadVertexShader(std::string shadername){
 return loadShader(shadername, GL_VERTEX_SHADER);
 }

 GLuint FileLoader::loadFragmentShader(std::string shadername){
 return loadShader(shadername, GL_FRAGMENT_SHADER);
 }

 void FileLoader::load3ds(std::string filepath) {
 FILE* pFile;				// File pointer

 char buf[6] = ".PMF";
 int ver = 0x0002;
 unsigned long sz;
 int st;

 // Attempt to open the fil
 pFile = fopen(filepath.c_str(), "rb");
 if(pFile == NULL) {
 printf("3ds is not loaded");
 } else {
 bin3ds = pFile;
 fseek(bin3ds, 0, SEEK_SET); // Just to make sure
 while (read_primary_chunk()==0);
 // TODO: IMPORTANT!!!!!!
 // Free all the linked list here after u do watever u want to do
 // with the obj data (i.e u could write the data to a custom format file.
 // I use my own mesh format)
 }
 }
 */
