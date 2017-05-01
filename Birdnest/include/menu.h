#ifndef menuh
#define menuh

#include "includes.h"

class Menu {
	std::string title;
	std::vector<std::string> choices;

public:
	void Draw();
	void update();
};

#endif // !menuh
