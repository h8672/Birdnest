#include "text.h"
#include "filereader.h"

/* Fixed with 20 is better than these optimizations!!!
enum charwidth {//all values have grown by 2... empty space in the edge now, no graphic problems
				//Letters 29			Numbers 10		--> 81 letters!!!
	a = 14,		A = 17,		zero = 13,			//0
	b = 12,		B = 15,		one = 11,			//1
	c = 12,		C = 16,		two = 12,			//2
	d = 13,		D = 16,		three = 13,			//3
	e = 12,		E = 14,		four = 14,			//4
	f = 10,		F = 14,		five = 14,			//5
	g = 12,		G = 17,		six = 14,			//6
	h = 11,		H = 14,		seven = 14,			//7
	i = 9,		I = 6,		eight = 13,			//8
	j = 7,		J = 12,		nine = 14,			//9
	k = 11,		K = 15,		//Specials 14x
	l = 5,		L = 13,		dot = 6,			//.
	m = 17,		M = 17,		colon = 6,			//:
	n = 11,		N = 14,		hdot = 6,			//,
	o = 14,		O = 18,		semicolon = 6,		//;
	p = 12,		P = 15,		plus = 13,			//+
	q = 12,		Q = 18,		minus = 9,			//-
	r = 9,		R = 16,		exclamation = 10,	//!
	s = 12,		S = 15,		question = 12,		//?
	t = 10,		T = 15,		equal = 13,			//=
	u = 11,		U = 14,		slash = 9,			// /
	v = 13,		V = 15,		brackets = 8,		//() <--- x2
	w = 17,		W = 23,		asterisk = 10,		//*
	x = 12,		X = 16,		space = 8,			//' '...
	y = 13,		Y = 16,
	z = 12,		Z = 15,
	å = 12,		Å = 15,
	ä = 12,		Ä = 15,
	ö = 14,		Ö = 18
};*/

//glm::ivec2 getSize(GLfloat height, charwidth width) { return glm::ivec2(height, (GLfloat)width); }

Text::Text(GLchar* font) {
	std::string folder = "fonts/";
	std::string directory = "";
	//29 a to ö, 10 number, 14 specials
	for (int i = 0; i < 82; i++) {
		//Lowercase chars
		for (char c = 'a'; c <= 'z'; c++) {
			directory = folder + font + "/lowercase/" + c + ".PNG";
			chars[i++].TextureID = FileReader::read2Dfont(directory.c_str());
		}
		directory = folder + font + "/lowercase/" + 'å' + ".PNG";
		chars[i++].TextureID = FileReader::read2Dfont(directory.c_str());
		directory = folder + font + "/lowercase/" + 'ä' + ".PNG";
		chars[i++].TextureID = FileReader::read2Dfont(directory.c_str());
		directory = folder + font + "/lowercase/" + 'ö' + ".PNG";
		chars[i++].TextureID = FileReader::read2Dfont(directory.c_str());
		//Uppercase chars
		for (char c = 'A'; c <= 'Z'; c++) {
			directory = folder + font + "/uppercase/" + c + ".PNG";
			chars[i++].TextureID = FileReader::read2Dfont(directory.c_str());
		}
		directory = folder + font + "/uppercase/" + 'Å' + ".PNG";
		chars[i++].TextureID = FileReader::read2Dfont(directory.c_str());
		directory = folder + font + "/uppercase/" + 'Ä' + ".PNG";
		chars[i++].TextureID = FileReader::read2Dfont(directory.c_str());
		directory = folder + font + "/uppercase/" + 'Ö' + ".PNG";
		chars[i++].TextureID = FileReader::read2Dfont(directory.c_str());
		//Number chars
		for (char c = '0'; c <= '9'; c++) {
			directory = folder + font + "/number/" + c + ".PNG";
			chars[i++].TextureID = FileReader::read2Dfont(directory.c_str());
		}
		//Special chars
		directory = folder + font + "/special/dot.PNG";
		chars[i++].TextureID = FileReader::read2Dfont(directory.c_str());
		directory = folder + font + "/special/colon.PNG";
		chars[i++].TextureID = FileReader::read2Dfont(directory.c_str());
		directory = folder + font + "/special/hdot.PNG";
		chars[i++].TextureID = FileReader::read2Dfont(directory.c_str());
		directory = folder + font + "/special/semicolon.PNG";
		chars[i++].TextureID = FileReader::read2Dfont(directory.c_str());
		directory = folder + font + "/special/plus.PNG";
		chars[i++].TextureID = FileReader::read2Dfont(directory.c_str());
		directory = folder + font + "/special/minus.PNG";
		chars[i++].TextureID = FileReader::read2Dfont(directory.c_str());
		directory = folder + font + "/special/exclamation.PNG";
		chars[i++].TextureID = FileReader::read2Dfont(directory.c_str());
		directory = folder + font + "/special/question.PNG";
		chars[i++].TextureID = FileReader::read2Dfont(directory.c_str());
		directory = folder + font + "/special/equal.PNG";
		chars[i++].TextureID = FileReader::read2Dfont(directory.c_str());
		directory = folder + font + "/special/slash.PNG";
		chars[i++].TextureID = FileReader::read2Dfont(directory.c_str());
		directory = folder + font + "/special/lbracket.PNG";
		chars[i++].TextureID = FileReader::read2Dfont(directory.c_str());
		directory = folder + font + "/special/rbracket.PNG";
		chars[i++].TextureID = FileReader::read2Dfont(directory.c_str());
		directory = folder + font + "/special/asterisk.PNG";
		chars[i++].TextureID = FileReader::read2Dfont(directory.c_str());
		directory = folder + font + "/special/space.PNG";
		chars[i++].TextureID = FileReader::read2Dfont(directory.c_str());

	}
	GLfloat width = 23;		//Size varies... no longer!
	GLfloat height = 22;
	GLfloat advance = 0.0f;
	//No bearing offsets

	//It's hell if none is right!!!
	//Should be correct now!!!
	for (int i = 0; i < 82; i++) {
		//Get width for all chars
		/* Nonsense! fixed is better!
		if (i < 10) {
			if (i == 0) width = a;
			if (i == 1) width = b;
			if (i == 2) width = c;
			if (i == 3) width = d;
			if (i == 4) width = e;
			if (i == 5) width = f;
			if (i == 6) width = g;
			if (i == 7) width = h;
			if (i == 8) width = charwidth::i;
			if (i == 9) width = j;
		}
		if (i >= 10 && i < 20) {
			if (i == 10) width = k;
			if (i == 11) width = l;
			if (i == 12) width = m;
			if (i == 13) width = n;
			if (i == 14) width = o;
			if (i == 15) width = p;
			if (i == 16) width = q;
			if (i == 17) width = r;
			if (i == 18) width = s;
			if (i == 19) width = t;
		}
		if (i >= 20 && i < 30) {
			if (i == 20) width = u;
			if (i == 21) width = v;
			if (i == 22) width = w;
			if (i == 23) width = x;
			if (i == 24) width = y;
			if (i == 25) width = z;
			if (i == 26) width = å;
			if (i == 27) width = ä;
			if (i == 28) width = ö;
			if (i == 29) width = A;
		}
		if (i >= 30 && i < 40) {
			if (i == 30) width = B;
			if (i == 31) width = C;
			if (i == 32) width = D;
			if (i == 33) width = E;
			if (i == 34) width = F;
			if (i == 35) width = G;
			if (i == 36) width = H;
			if (i == 37) width = I;
			if (i == 38) width = J;
			if (i == 39) width = K;
		}
		if (i >= 40 && i < 50) {
			if (i == 40) width = L;
			if (i == 41) width = M;
			if (i == 42) width = N;
			if (i == 43) width = O;
			if (i == 44) width = P;
			if (i == 45) width = Q;
			if (i == 46) width = R;
			if (i == 47) width = S;
			if (i == 48) width = T;
			if (i == 49) width = U;
		}
		if (i >= 50 && i < 60) {
			if (i == 50) width = V;
			if (i == 51) width = W;
			if (i == 52) width = X;
			if (i == 53) width = Y;
			if (i == 54) width = Z;
			if (i == 55) width = Å;
			if (i == 56) width = Ä;
			if (i == 57) width = Ö;
			if (i == 58) width = zero;
			if (i == 59) width = one;
		}
		if (i >= 60 && i < 70) {
			if (i == 60) width = two;
			if (i == 61) width = three;
			if (i == 62) width = four;
			if (i == 63) width = five;
			if (i == 64) width = six;
			if (i == 65) width = seven;
			if (i == 66) width = eight;
			if (i == 67) width = nine;
			if (i == 68) width = dot;
			if (i == 69) width = colon;
		}
		if (i >= 70 && i < 80) {
			if (i == 70) width = hdot;
			if (i == 71) width = semicolon;
			if (i == 72) width = plus;
			if (i == 73) width = minus;
			if (i == 74) width = exclamation;
			if (i == 75) width = question;
			if (i == 76) width = equal;
			if (i == 77) width = slash;
			if (i == 78) width = brackets;
			if (i == 79) width = brackets;
		}
		if (i == 80) width = asterisk;
		if (i == 81) width = space;
		if (i == 82) width = 100 ;
		*/
		//width = 23;
		chars[i].Size = glm::vec2(width, height);
		chars[i].Advance = advance;

		GLchar chat;
		//Simple a to z, A to Z and 0 to 9
		if (i > -1 && i < 26)//a to z
			chat = 'a' + i;
		else if (i == 26) chat = 'å';
		else if (i == 27) chat = 'ä';
		else if (i == 28) chat = 'ö';
		else if (i > 28 && i < 55)//A to Z
			chat = 'A' + i - 29;
		else if (i == 55) chat = 'Å';
		else if (i == 56) chat = 'Ä';
		else if (i == 57) chat = 'Ö';
		else if (i > 57 && i < 68)//0 to 9
			chat = '0' + i - 58;
		else if (i == 68) chat = '.';
		else if (i == 69) chat = ':';
		else if (i == 70) chat = ',';
		else if (i == 71) chat = ';';
		else if (i == 72) chat = '+';
		else if (i == 73) chat = '-';
		else if (i == 74) chat = '!';
		else if (i == 75) chat = '?';
		else if (i == 76) chat = '=';
		else if (i == 77) chat = '/';
		else if (i == 78) chat = '(';
		else if (i == 79) chat = ')';
		else if (i == 80) chat = '*';
		else if (i == 81) chat = ' ';
		//Specials... å to ö, Å to Ö, . to space...
		else chat = '^';
		characters.insert(std::pair<GLchar, Character>(chat, chars[i]));
		//std::cout << "Kirjain on:" << chat << std::endl;
	}

	GLfloat code = 0.011f;

	//Gen VAO, VBO, EBO
	glGenVertexArrays(1, &this->VAO);
	glGenBuffers(1, &this->EBO);
	for (int i = 0; i < 82; i++) {
		glGenBuffers(1, &chars[i].VBO);

		glBindVertexArray(VAO);

		GLfloat gwidth = chars[i].Size.x / 2;

		GLfloat vertices[4][8] = {
			// Position						// Colors           // Texture Coords
			 gwidth,	 gwidth, 0.0f,		code, code, code,   1.0f, 0.0f, // Top Right
			 gwidth,	-gwidth, 0.0f,		code, code, code,   1.0f, 1.0f, // Bottom Right
			-gwidth,	-gwidth, 0.0f,		code, code, code,   0.0f, 1.0f, // Bottom Left
			-gwidth,	 gwidth, 0.0f,		code, code, code,   0.0f, 0.0f  // Top Left 
		};
		glBindBuffer(GL_ARRAY_BUFFER, chars[i].VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);


		// Position attribute
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
		glEnableVertexAttribArray(0);
		// Color attribute
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
		glEnableVertexAttribArray(1);
		// TexCoord attribute
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
		glEnableVertexAttribArray(2);

		glBindVertexArray(0);

	}


}

void Text::SetVectors(glm::vec3 Position, glm::vec3 Rotation, bool FaceCamera) {
	this->Position = Position;
	this->Rotation = Rotation;
	this->FaceCamera = FaceCamera;
}

void Text::SetVectors(glm::vec3 Position, glm::vec3 Rotation, glm::vec3 * Target, bool FaceCamera) {
	this->Position = Position;
	this->Rotation = Rotation;
	this->Target = Target;
	this->FaceCamera = FaceCamera;
}

void Text::SetVisuals(glm::vec4 textcolor, glm::vec4 BGcolor, GLfloat scale) {
	this->textcolor = textcolor;
	this->BGcolor = BGcolor;
	this->scale = scale;
}

//Draws a line of 64 letters
void Text::Draw(Shader * shader, std::string text) {
	Draw(shader, text, 1, 24);
}

//Draws a paragraph which column is 64 letters
void Text::Draw(Shader * shader, std::string text, GLuint rows) {
	Draw(shader, text, rows, 24);
}

//Draws custom paragraph
void Text::Draw(Shader * shader, std::string text, GLuint rows, GLuint columns) {
	shader->Use();
	glActiveTexture(GL_TEXTURE0);

	glUniform4f(glGetUniformLocation(shader->Program, "textColor"), textcolor.x, textcolor.y, textcolor.z, textcolor.w);
	glUniform4f(glGetUniformLocation(shader->Program, "textBGColor"), BGcolor.x, BGcolor.y, BGcolor.z, BGcolor.w);
	
	glm::mat4 temp;
    std::string::const_iterator c; //tai auto c;
	//for (c = text.begin(); c != text.end(); c++) {
	//	length += ((characters[*c].Advance + characters[*c].Size.x));
	//}
	/*
	if (!FaceCamera) {//Turn pictures in straight line
		model = glm::rotate(model, glm::radians(Rotation.x), glm::vec3(0, 0, 1));	//Pitch
		model = glm::rotate(model, glm::radians(Rotation.y), glm::vec3(0, 1, 0));	//Yaw
		model = glm::rotate(model, glm::radians(Rotation.z), glm::vec3(1, 0, 0));	//Roll
	}*/
	//std::cout << "Length of string: " << length << std::endl;
	//Kaari, kun sin ja cos mukana...
	//glm::vec3 CurrentPosition = glm::vec3(Position.x - length / 2 * sin(glm::radians(Rotation.x)), Position.y, Position.z);// -length / 2 * cos(glm::radians(Rotation.x)));

	GLfloat fix = 0.05f;
	GLuint currentrow = 0;
	GLdouble width = 23 * scale * fix;
	GLdouble height = 22.0f * rows * scale * fix;
	GLdouble used = 0;
	GLint count = 1;

	if(text.length() > columns) width *= (GLdouble)columns;
	else width *= (GLdouble)text.length();

	glm::vec3 CurrentPosition = Position - glm::vec3(width/2, height/2, 0);
	for (c = text.begin(); c != text.end(); c++) {
		if (count++ > (columns * (currentrow + 1))) {
			currentrow++;
			CurrentPosition = CurrentPosition - glm::vec3(
				width,
				22.0f * currentrow * scale * fix,
				0);
		}
		// Bind Texture
		glBindTexture(GL_TEXTURE_2D, characters[*c].TextureID);
		//Do things to model, translates, rotates and scales
		//Siirtää kirjaimia...		nyk kohta	seuraava kirjain
		used = ((characters[*c].Advance + characters[*c].Size.x));
		CurrentPosition = CurrentPosition + glm::vec3((GLfloat)used * scale * fix, 0, 0);

		glm::mat4 model;
		model = glm::translate(model, CurrentPosition); //Kääntää yksittäin samaan suuntaa
		if (!this->FaceCamera) {//turns characters to face camera always
			glm::vec3 *temprot = Target;

			//model = glm::rotate(model, glm::radians(Target->x), glm::vec3(0, 0, 1));	//Pitch
			model = glm::rotate(model, glm::radians(Target->y), glm::vec3(0, 1, 0));	//Yaw
			model = glm::rotate(model, glm::radians(Target->z), glm::vec3(1, 0, 0));	//Roll
			//FaceCamera = false; //Stops constant rotating, spiraling in other words.
		}
		//model = glm::translate(model, CurrentPosition); //Kääntää kaikkia samassa suunnassa
		//model = glm::scale(model, glm::vec3(characters[*c].Size.x/23, characters[*c].Size.y/22, 1));
		model = glm::scale(model, glm::vec3(scale * fix));
		glUniformMatrix4fv(glGetUniformLocation(shader->Program, "model"), 1, GL_FALSE, glm::value_ptr(model));

		// Draw container
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);

	}

}


