#ifndef filereaderh
#define filereaderh
#include "includes.h"

namespace FileReader {

	GLchar * readfile(const char * filename);

	GLuint read2Dtexture(const char * filename);
	GLuint read2Dfont(const char * filename);

	GLint TextureFromFile(const char * path, std::string directory);

	GLvoid read3Dfile(const char * filename, std::string * objects, std::string * vertices, std::string * normals, std::string * elements);

	GLvoid writetofile(const char * filename, std::string * sarray);
};

#endif // !filereaderh