#version 330 core

// Input variables
in vec3 vertexColor;

// Output variables
out vec4 fragColor;

void main()
{
  fragColor = vec4(vertexColor, 1.0);
}
