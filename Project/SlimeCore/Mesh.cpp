#include "Mesh.h"

Mesh::Mesh()
{
}

Mesh::~Mesh()
{
	for (auto& c : m_meshChunks) {
		glDeleteVertexArrays(1, &c.vao);
		glDeleteBuffers(1, &c.vbo);
		glDeleteBuffers(1, &c.ibo);
	}
}

void Mesh::create(Primitives::TYPE type, float argOne, float argTwo, int argThree)
{
	switch (type)
	{
	case Primitives::Plane:
		prim = Plane::Create();
		hasIBO = true;
		break;
	case Primitives::Cube:
		prim = Cube::Create();
		hasIBO = true;
		break;
	case Primitives::Cylinder:
		prim = Cylinder::Create(argOne, argTwo, argThree);
		hasIBO = true;
		break;
	case Primitives::Sphere:
		prim = Sphere::Create(argOne, argTwo, argThree);
		hasIBO = true;
		break;
	case Primitives::Torus:
		prim = Torus::Create(argOne, argTwo, argThree, 10);
		hasIBO = true;
		break;
	case Primitives::SkyBox:
		prim = SkyBox::Create();
		hasIBO = false;
		break;
	default:
		break;
	}
	
	MeshChunk chunk;

	if (hasIBO)
	{
		// generate buffers
		glGenBuffers(1, &chunk.vbo);
		glGenBuffers(1, &chunk.ibo);
		glGenVertexArrays(1, &chunk.vao);

		// bind vertex array aka a mesh wrapper
		glBindVertexArray(chunk.vao);

		std::vector<float> newvertices;
		for (int i = 0; i < prim.vertices.size(); i++)
		{
			// Postitions
			newvertices.push_back(prim.vertices[i].x);
			newvertices.push_back(prim.vertices[i].y);
			newvertices.push_back(prim.vertices[i].z);

			// Normals
			if (prim.normals.size() < 1)
			{
				newvertices.push_back(1);
				newvertices.push_back(1);
				newvertices.push_back(1);
			}
			else
			{
				newvertices.push_back(prim.normals[i].x);
				newvertices.push_back(prim.normals[i].y);
				newvertices.push_back(prim.normals[i].z);
			}

			if (prim.uvs.size() < 1)
			{
				newvertices.push_back(0.5);
				newvertices.push_back(0.5);

			}
			else
			{
				// UVS
				newvertices.push_back(prim.uvs[i].x);
				newvertices.push_back(prim.uvs[i].y);
			}
		}

		// store index count for rendering
		chunk.indexCount = (unsigned int)prim.indices.size();

		// Fill vertex Buffer
		glBindBuffer(GL_ARRAY_BUFFER, chunk.vbo);
		glBufferData(GL_ARRAY_BUFFER, newvertices.size() * sizeof(float), newvertices.data(), GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, chunk.ibo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, prim.indices.size() * sizeof(unsigned int), prim.indices.data(), GL_STATIC_DRAW);

		// Enable first element as position
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);

		// Enable second element as normals
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(1);

		// Enable third element as UVS
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
		glEnableVertexAttribArray(2);

		// Unbind buffer
		glBindVertexArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		m_meshChunks.push_back(chunk);

		return (void)0;
	}

	isSkyBox = true;

	// skybox VAO
	glGenVertexArrays(1, &chunk.vao);
	glGenBuffers(1, &chunk.vbo);
	glBindVertexArray(chunk.vao);
	glBindBuffer(GL_ARRAY_BUFFER, chunk.vbo);

	glBufferData(GL_ARRAY_BUFFER, sizeof(prim.vertices), &prim.vertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

	m_meshChunks.push_back(chunk);
}

bool Mesh::load(const char* filename, bool loadTextures, bool flipTextureV)
{
	std::vector<tinyobj::shape_t> shapes;
	std::vector<tinyobj::material_t> materials;
	std::string error = "";

	std::string file = filename;
	std::string folder = file.substr(0, file.find_last_of('/') + 1);

	bool success = tinyobj::LoadObj(shapes, materials, error,
		filename, folder.c_str());

	if (success == false) {
		printf("%s\n", error.c_str());
		return false;
	}

	fileName = filename;


	// copy shapes
	m_meshChunks.reserve(shapes.size());

	for (auto& s : shapes) {

		MeshChunk chunk;

		// generate buffers
		glGenBuffers(1, &chunk.vbo);
		glGenBuffers(1, &chunk.ibo);
		glGenVertexArrays(1, &chunk.vao);

		// bind vertex array aka a mesh wrapper
		glBindVertexArray(chunk.vao);

		// set the index buffer data
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, chunk.ibo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER,
			s.mesh.indices.size() * sizeof(unsigned int),
			s.mesh.indices.data(), GL_STATIC_DRAW);

		// store index count for rendering
		chunk.indexCount = (unsigned int)s.mesh.indices.size();

		// create vertex data
		std::vector<Vertex> vertices;
		vertices.resize(s.mesh.positions.size() / 3);
		size_t vertCount = vertices.size();

		bool hasPosition = s.mesh.positions.empty() == false;
		bool hasNormal = s.mesh.normals.empty() == false;
		bool hasTexture = s.mesh.texcoords.empty() == false;

		for (size_t i = 0; i < vertCount; ++i) {
			if (hasPosition)
				vertices[i].position = glm::vec3(s.mesh.positions[i * 3 + 0], s.mesh.positions[i * 3 + 1], s.mesh.positions[i * 3 + 2]);
			if (hasNormal)
				vertices[i].normal = glm::vec3(s.mesh.normals[i * 3 + 0], s.mesh.normals[i * 3 + 1], s.mesh.normals[i * 3 + 2]);

			// flip the T / V (might not always be needed, depends on how mesh was made)
			if (hasTexture)
				vertices[i].texcoord = glm::vec2(s.mesh.texcoords[i * 2 + 0], flipTextureV ? 1.0f - s.mesh.texcoords[i * 2 + 1] : s.mesh.texcoords[i * 2 + 1]);
		}

		// calculate for normal mapping
		if (hasNormal && hasTexture)
			calculateTangents(vertices, s.mesh.indices);

		// bind vertex buffer
		glBindBuffer(GL_ARRAY_BUFFER, chunk.vbo);

		// fill vertex buffer
		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);

		// enable first element as positions
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);

		// enable normals
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 4, GL_FLOAT, GL_TRUE, sizeof(Vertex), (void*)(sizeof(glm::vec3) * 1));

		// enable texture coords
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(glm::vec3) * 2));

		// bind 0 for safety
		glBindVertexArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

		// set chunk material
		chunk.materialID = s.mesh.material_ids.empty() ? -1 : s.mesh.material_ids[0];

		m_meshChunks.push_back(chunk);
	}

	// load obj
	return true;
}

void Mesh::draw(bool usePatches /* = false */) {

		int program = -1;
		glGetIntegerv(GL_CURRENT_PROGRAM, &program);

		if (program == -1) {
			printf("No shader bound!\n");
			return;
		}
		int currentMaterial = -1;

	if (!isSkyBox)
	{
		// draw the mesh chunks
		for (auto& c : m_meshChunks) {
			// bind and draw geometry
			glBindVertexArray(c.vao);
			if (usePatches)
				glDrawElements(GL_PATCHES, c.indexCount, GL_UNSIGNED_INT, 0);
			else
				glDrawElements(GL_TRIANGLES, c.indexCount, GL_UNSIGNED_INT, 0);
		}
		return (void)0;
	}

	glDrawArrays(GL_TRIANGLES, 0, 36);
	glBindVertexArray(0);
}

void Mesh::calculateTangents(std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices) {
	unsigned int vertexCount = (unsigned int)vertices.size();
	glm::vec4* tan1 = new glm::vec4[vertexCount * 2];
	glm::vec4* tan2 = tan1 + vertexCount;
	memset(tan1, 0, vertexCount * sizeof(glm::vec4) * 2);

	unsigned int indexCount = (unsigned int)indices.size();
	for (unsigned int a = 0; a < indexCount; a += 3) {
		long i1 = indices[a];
		long i2 = indices[a + 1];
		long i3 = indices[a + 2];

		const glm::vec3& v1 = vertices[i1].position;
		const glm::vec3& v2 = vertices[i2].position;
		const glm::vec3& v3 = vertices[i3].position;

		const glm::vec2& w1 = vertices[i1].texcoord;
		const glm::vec2& w2 = vertices[i2].texcoord;
		const glm::vec2& w3 = vertices[i3].texcoord;

		float x1 = v2.x - v1.x;
		float x2 = v3.x - v1.x;
		float y1 = v2.y - v1.y;
		float y2 = v3.y - v1.y;
		float z1 = v2.z - v1.z;
		float z2 = v3.z - v1.z;

		float s1 = w2.x - w1.x;
		float s2 = w3.x - w1.x;
		float t1 = w2.y - w1.y;
		float t2 = w3.y - w1.y;

		float r = 1.0F / (s1 * t2 - s2 * t1);
		glm::vec4 sdir((t2 * x1 - t1 * x2) * r, (t2 * y1 - t1 * y2) * r,
			(t2 * z1 - t1 * z2) * r, 0);
		glm::vec4 tdir((s1 * x2 - s2 * x1) * r, (s1 * y2 - s2 * y1) * r,
			(s1 * z2 - s2 * z1) * r, 0);

		tan1[i1] += sdir;
		tan1[i2] += sdir;
		tan1[i3] += sdir;

		tan2[i1] += tdir;
		tan2[i2] += tdir;
		tan2[i3] += tdir;
	}

	for (unsigned int a = 0; a < vertexCount; a++) {
		const glm::vec3& n = glm::vec3(vertices[a].normal);
		const glm::vec3& t = glm::vec3(tan1[a]);

		// Gram-Schmidt orthogonalize
		vertices[a].tangent = glm::vec4(glm::normalize(t - n * glm::dot(n, t)), 0);

		// Calculate handedness (direction of bitangent)
		vertices[a].tangent.w = (glm::dot(glm::cross(glm::vec3(n), glm::vec3(t)), glm::vec3(tan2[a])) < 0.0F) ? 1.0F : -1.0F;
	}

	delete[] tan1;
}