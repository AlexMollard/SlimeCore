#include "GameObject2D.h"

void GameObject2D::Draw()
{
	// bind and draw geometry
	glBindVertexArray(vao);
	glDrawElements(GL_TRIANGLES, twoMesh.indices.size(), GL_UNSIGNED_INT, 0);
}

void GameObject2D::SetPos(glm::vec3 newPos)
{ 
	position = newPos;
	model[3] = glm::vec4(newPos, 1);
}
void GameObject2D::SetTexture(Texture* texture)
{
	tex = texture;
}
void GameObject2D::Rotate(float rotation)
{
	model = glm::rotate(model, rotation, glm::vec3(0.0f, 0.0f, 1.0f)); // Then rotate
}
;
