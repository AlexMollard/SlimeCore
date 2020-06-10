#version 450

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aNormal;
layout(location = 2) in vec2 aTexCoord;
layout(location = 3) in vec3 aTangent;
layout(location = 4) in vec3 aBiTangent;
layout(location = 5) in vec3 aColor;

out vec2 TexCoord;
out vec3 WorldPos;
out vec3 Normal;
out vec3 Tangent;
out vec3 BiTangent;
out vec4 FragPosLightSpace;;
out vec3 TerrainColor;

uniform mat4 ProjectionView;
uniform mat4 Model;
uniform mat4 lightSpaceMatrix;

uniform vec3 dirtColor;
uniform vec3 grassColor;


void main()
{
	TexCoord = aTexCoord;
	TexCoord.y = -1 * TexCoord.y;
	WorldPos = vec3(Model * vec4(aPos, 1.0));
	Normal = mat3(Model) * aNormal;

	Tangent = normalize(Tangent);
	BiTangent = normalize(BiTangent);

	Tangent = aTangent;
	BiTangent = aBiTangent;
	
	TerrainColor = aColor;

	FragPosLightSpace = lightSpaceMatrix * vec4(WorldPos, 1.0);

	gl_Position = ProjectionView * vec4(WorldPos, 1.0);
}