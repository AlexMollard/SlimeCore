#version 450

out vec4 FragColour;

in vec3 FragPos;
in vec2 texCoord;

uniform sampler2D texture1;
uniform vec3 lightPos;
uniform vec3 viewPos;

float near = 0.1;
float far = 100.0;

float LinearizeDepth(float depth)
{
    float z = depth * 2.0 - 1.0; // back to NDC 
    return (2.0 * near * far) / (far + near - z * (far - near));
}

void main()
{
	float depth = LinearizeDepth(gl_FragCoord.z) / far; // divide by far for demonstration
	FragColour = vec4(vec3(depth), 1.0);
}