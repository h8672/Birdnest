#ifndef meshh
#define meshh

#include "includes.h"
#include "shader.h"




// Need to add shader program!!! before going further into meshes
class Mesh {
public:
	//Mesh data
	std::vector<Vertex> vertices;	//Vertexes
	std::vector<GLuint> indices;	//Indices
	std::vector<Texture> textures;	//Textures
	//Functions
	Mesh(std::vector<Vertex> vertices, std::vector<GLuint> indices, std::vector<Texture> textures);
	void Draw(Shader* shader);
private:
	//Render data
	GLuint VAO, VBO, EBO;
	//Functions
	void setupMesh();
};

/* infoa structeista
http://learnopengl.com/#!Model-Loading/Mesh
kertoo ett‰ struct tieto s‰ilyy seuraavassa muodossa...
Vertex vertex;
vertex.Position = glm::vec3(0.2f, 0.4f, 0.6f);
vertex.Normal = glm::vec3(0.0f, 1.0f, 0.0f);
vertex.TexCoords = glm::vec2(1.0f, 0.0f);
// = [0.2f, 0.4f, 0.6f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f];
eli se on suoraan taulukko muodossa ja koska kaikki ovat float
niin sen voi suoraan tulkita float taulukkona.
ensimm‰isen alkion muistipaikan voi suoraan linkitt‰‰
float taulukkooon pointterina.
GLfloat* taulukko = &vertex[0];
*/

#endif // !meshh