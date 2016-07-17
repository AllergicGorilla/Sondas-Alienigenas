#version 330 core
in vec3 ourColor;
out vec4 color;
in vec3 pos;

void main()
{
	color = vec4(ourColor, 1.0f);
}
