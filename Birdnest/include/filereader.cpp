#include "filereader.h"


std::string strarray;
namespace FileReader {
	GLchar * readfile(const char * filename) {
		strarray.clear();
		std::fstream* file;
		GLchar buffer[2] = { '\0', '\0' };
		file = new std::fstream();
		//std::fstream file;//create filestream
		file->open(filename, std::ios::in);//open filestream to file
		if (file->is_open()) {//while filestream is open...
			std::cout << "Reading file " << filename << " right now." << std::endl;
			//sarray.clear();
			while (!file->eof()) {
				//add buffer behind string, before reading so it doesn't multiply last letter
				strarray.append(buffer);
				//need a buffer from file!
				file->read(buffer, 1);
			}
			std::cout << "No longer reading file." << std::endl;
		}
		file->close();//close filestream
		return (GLchar*)strarray.c_str();//return data
	}
	//read normal image file...
	GLuint read2Dtexture(const char * filename) {
		//inside copied from tutorial... works well tho...
		// Load and create a texture 
		GLuint textures;
		glGenTextures(1, &textures);
		glBindTexture(GL_TEXTURE_2D, textures);// All upcoming GL_TEXTURE_2D operations now have effect on this texture object
											   // Set the texture wrapping parameters
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);// Set texture wrapping to GL_REPEAT (usually basic wrapping method)
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		// Set texture filtering parameters
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		// Load image, create texture and generate mipmaps
		int width, height;
		unsigned char* image = SOIL_load_image(filename, &width, &height, 0, SOIL_LOAD_RGB);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
		glGenerateMipmap(GL_TEXTURE_2D);
		SOIL_free_image_data(image);
		glBindTexture(GL_TEXTURE_2D, 0); // Unbind texture when done, so we won't accidentily mess up our texture.

		return textures;
	}
	//read normal image file...
	GLuint read2Dfont(const char * filename) {
		//inside copied from tutorial... works well tho...
		// Load and create a texture 
		GLuint textures;
		glGenTextures(1, &textures);
		// All upcoming GL_TEXTURE_2D operations now have effect on this texture object
		glBindTexture(GL_TEXTURE_2D, textures);


		// Set the texture wrapping parameters
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
		// Set texture filtering parameters
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		// Load image, create texture and generate mipmaps
		int width, height;
		unsigned char* image = SOIL_load_image(filename, &width, &height, 0, SOIL_LOAD_RGBA);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB | GL_ALPHA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
		
		glGenerateMipmap(GL_TEXTURE_2D);
		SOIL_free_image_data(image);
		glBindTexture(GL_TEXTURE_2D, 0); // Unbind texture when done, so we won't accidentily mess up our texture.

		return textures;
	}

	GLint TextureFromFile(const char * path, std::string directory) {
		//Generate texture ID and load texture data 
		std::string filename = std::string(path);
		filename = directory + '/' + filename;
		GLuint textureID;
		glGenTextures(1, &textureID);
		int width, height;
		unsigned char* image = SOIL_load_image(filename.c_str(), &width, &height, 0, SOIL_LOAD_RGB);
		// Assign texture to ID
		glBindTexture(GL_TEXTURE_2D, textureID);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
		glGenerateMipmap(GL_TEXTURE_2D);

		// Parameters
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glBindTexture(GL_TEXTURE_2D, 0);
		SOIL_free_image_data(image);
		return textureID;
	}

	//read .obj file export from blender and place data to 4 strings
	GLvoid read3Dfile(const char * filename, std::string* objects, std::string* vertices, std::string* normals, std::string* elements) {

		//Clearing data from strings...
		objects->clear();
		vertices->clear();
		normals->clear();
		elements->clear();
		
		//Open filestream
		std::ifstream in(filename, std::ios::in);
		if (!in) {
			std::cout << "Cannot open " << filename << std::endl; exit(1);
		}


		//Reading file, done!!!
		std::string line;
		while (std::getline(in, line)) {
			//Object done!
			if (line.substr(0, 2) == "o ") {
				for (int i = 2; i < (int)line.length(); i++)
					objects->push_back(line.at(i));
				objects->push_back('/');
			}
			//Vertices done!
			else if (line.substr(0, 2) == "v ") {
				for (int i = 2; i < (int)line.length(); i++) {
					vertices->push_back(line.at(i));
				}
				vertices->push_back(' ');
			}
			//Elements
			else if (line.substr(0, 2) == "f ") {
				for (int i = 2; i < (int)line.length(); i++) {
					//instead of space, place '/'
					if (line.at(i) == ' ')
						elements->push_back('/');
					//skip once, then '/' between
					else if (line.at(i) == '/' && line.at(i+1) == '/');
					//get char
					else elements->push_back(line.at(i));
				}
				elements->push_back('/');
			}
			//Normals
			else if (line.substr(0, 3) == "vn ") {
				for (int i = 2; i < (int)line.length(); i++) {
					normals->push_back(line.at(i));
				}
				normals->push_back(' ');
			}
			//skip
			else if (line.substr(0, 6) == "mtllib") {
				//library filename
			}
			//skip
			else if (line.substr(0, 6) == "usemtl") {
				//Material
			}
			//skip
			else if (line[0] == '#') {
				/* ignoring this line */
			}
			//skip
			else {
				/* ignoring this line */
			}
		}
		//Converting data...
		//Objects
		//Vertices done! long...
		std::string dvertices;
		GLfloat number = 0, kerroin = 10;;
		//read from end to 1st, so ve get correct decimals
		//Actually, this might work straight away...
		//std::cout << "1st vertices: " << (GLfloat*)vertices->c_str() << std::endl;
		/* //Should be enough, decoding outside...
		std::cout << "Reading vertices...\n";
		for (int i = vertices->length() -2; i > -1 && i > 2; i--) {
			if (0x47 < vertices->at(i) && vertices->at(i) < 0x58) {//between 0 and 9
				for (;vertices->at(i) != ' ';i--) {
					//aiempi luku jaetaan 10, siten aina jälkeen jää pienempi desimaali
					if(vertices->at(i) != '.')
						number = number + ((vertices->at(i) - 0x48) / kerroin);
					else kerroin = 1;//piste, ei enään desimaaleja
				}
			}
			//Kyseessä väliviiva
			else if (vertices->at(i) == '-') number = -1 * number;
			//Kyseessä väli
			else if (vertices->at(i) == ' ') {
					dvertices.push_back((GLchar)number);
					std::cout << number << std::endl;
					number = 0;
				}
			//tekee tämän silti vaikka vaihtoehto löytyi, wow!
			//Johtuu varmaan ekasta siinä katotaan 2:hta kirjainta
			else std::cout << "Problem or number!\n";
			kerroin = 10;
		}
		std::cout << "... ended\n";
		std::cout << "2nd vertices: " << (GLfloat*)vertices->c_str() << std::endl;
		//Transforming text to double and that to float and it to char
		std::string numbertext;
		double temp;
		std::cout << "Numbers:\n";
		for (int i = 0, y = 0; i < (int)vertices->length(); i++) {
			numbertext.clear();
			for (;vertices->at(i) != ' ';i++)//character count
				numbertext.push_back(vertices->at(i));
			temp = ::atof(numbertext.c_str());
			y++;//number count//skips ' '
			std::cout << numbertext;
			dvertices.push_back((GLchar)temp);
		}
		//Why this is different? memory location?
		std::cout << "\ndvertices: " << (GLfloat*)dvertices.c_str() << std::endl;
		std::cout << "\ndvertices in string: " << dvertices.c_str() << std::endl;
		//Placing data to vertices string
		vertices->clear();
		vertices->append(dvertices);
		std::string testt(*vertices);
		std::cout << "\ntestt: " << (GLfloat*)testt.c_str() << std::endl;
		//dvertices.clear();
		*/
		
	}

	GLvoid writetofile(const char * filename,  std::string * sarray) {
		std::fstream* file;
		file = new std::fstream();
		//std::fstream file;//create filestream
		file->open(filename, std::ios::out | std::ios::app);//open filestream to file
		if (file->is_open()) {//while filestream is open...
			std::cout << "Writing file " << filename << " right now." << std::endl;
			//Writing to file
			file->write(sarray->c_str(), sarray->length());
			std::cout << "No longer writing file." << std::endl;
		}
		file->close();//close filestream

	}
};