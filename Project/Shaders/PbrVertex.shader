#version 450

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aNormal;
layout(location = 2) in vec2 aTexCoord;
layout(location = 3) in vec3 aTangent;
layout(location = 4) in vec3 aBiTangent;

out vec2 TexCoord;
out vec3 WorldPos;
out vec3 Normal;
out vec3 Tangent;
out vec3 BiTangent;

uniform mat4 ProjectionView;
uniform mat4 Model; 

uniform sampler2D diffuseTexture;
uniform sampler2D specularTexture;
uniform sampler2D normalTexture;
uniform sampler2D ambientTexture;
uniform sampler2D roughTexture;
uniform sampler2D displacementTexture;

uniform float diffuseStrength;
uniform float specularStrength;
uniform float normalStrength;
uniform float ambientStrength;
uniform float roughStrength;
uniform float displacementStrength;

void main() 
{ 

    TexCoord = aTexCoord;
    TexCoord.y = -1 * TexCoord.y;
    WorldPos = vec3(Model * vec4(aPos, 1.0));
    Normal = mat3(Model) * aNormal;

    Tangent = normalize(mat3(Model) * Tangent);
    BiTangent = normalize(mat3(Model) * BiTangent);

    Tangent = aTangent;
    BiTangent = aBiTangent;

    float p = texture(displacementTexture, TexCoord).a * displacementStrength;
    
    gl_Position = ProjectionView * vec4(WorldPos + (aNormal * p), 1.0);
}