#version 330 core

// Input variables
in vec3 vertexPosition;
in vec3 vertexColor;

// Output variables
out vec4 fragColor;

// Uniforms
uniform float fillValue;
uniform float leftEdge;

void main()
{
  float transparency = float((vertexPosition.x - leftEdge) < fillValue);
  fragColor = vec4(vertexColor, transparency);
}
