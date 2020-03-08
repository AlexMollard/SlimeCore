#pragma once
#include "gl_core_4_5.h"
#include "glm.hpp"
#include "glfw3.h"
#include "ext.hpp"
#include "Primitives.h"
#include "objLoader.h"

// a vertex structure for obj files
struct Vertex {
	glm::vec3 position; // added to attrib location 0
	glm::vec3 normal;	// added to attrib location 1
	glm::vec2 texcoord;	// added to attrib location 2

						// normal-mapping data
	glm::vec4 tangent;	// added to attrib location 3
	glm::vec3 bitangent;	// added to attrib location 4
};

class Mesh
{
public:
	Mesh(const char* name, const char* dir = nullptr);
	~Mesh();

	void create(Primitives::TYPE type = Primitives::TYPE::Cube, float radius = 0.5f, float halfLength = 0.5f, int slices = 10);
	bool load(const char* filename, bool loadTextures = true, bool flipTextureV = false);
	virtual void draw(bool usePatches = false);
	std::string GetName() { return name; };

	struct MeshChunk {
		unsigned int	vao, vbo, ibo;
		unsigned int	indexCount;
		int				materialID;
	};
protected:
	std::vector<MeshChunk>	m_meshChunks;
	std::string name;
	std::string fileName;
	Primitives prim;
	bool hasIBO = false;

	void calculateTangents(std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices);
};

