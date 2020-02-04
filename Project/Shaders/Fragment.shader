#version 450

uniform vec4 color = vec4(1,1,1,1);

in vec4 gl_FragCoord;
out vec4 final_color;

void main()
{
	final_color = vec4(gl_FragCoord.xy * 0.001,0,1) + color;
}