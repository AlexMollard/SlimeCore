#pragma once
#include "RigidBody.h"

class GameObject2D : public RigidBody
{
public:
	GameObject2D() {};
	~GameObject2D() {};

	struct TwoMesh
	{
		std::vector<glm::vec3> vertices;
		std::vector<glm::vec2> uvs;
		std::vector<unsigned int> indices;
	};

	void Draw();
	void UpdatePos();
	void SetTexture(Texture* texture);
	void Rotate(float rotation);

	unsigned int	vao, vbo, ibo;
	glm::vec3 color = glm::vec3(1);
	TwoMesh twoMesh;
	Texture* tex = nullptr;
	glm::mat4 model = glm::mat4(1);
};
