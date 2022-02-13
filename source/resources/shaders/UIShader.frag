#version 330 core

// Input variables
in vec3 vertexColor;

// Output variables
out vec4 fragColor;

// Uniform variables
uniform float opacity;

void main()
{
  fragColor = vec4(vertexColor, opacity);
}
