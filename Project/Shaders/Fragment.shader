#version 450

out vec4 FragColour;;

void main()
{
	FragColour = vec4(gl_FragCoord.xy * 0.001,0,1);
}