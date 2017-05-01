#ifndef stringslisth
#define stringslisth

#include "includes.h"

class StringsList {
	std::vector<std::string> strings;

	std::map<GLint, std::string*> mapstring;

public:
	std::string* Get(GLint ID) { return mapstring.find(ID)->second; }

	GLuint GetSize() { return this->mapstring.size(); }

	void BindString(GLint ID) { this->mapstring.insert(std::make_pair(ID, &this->strings.at(ID))); }
	void UnBindString(GLint ID) { this->mapstring.erase(mapstring.find(ID)->first); }
	void Load(std::string str) { this->strings.push_back(str); }
	void LoadString(GLchar* source, GLint row) {
		//Load string from file from row...
		std::cout << "Reading string from row not implemented yet!\n";
	}

	//Requires Text temporary class to draw text!

};

#endif // ! stringslisth
