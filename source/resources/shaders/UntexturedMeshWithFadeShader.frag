#version 330 core

// Input variables
in vec3 vertexColor;

// Output variables
out vec4 fragColor;

// Uniform variables
uniform float fadeValue;
uniform vec4 fadeColor;

void main()
{
  fragColor = mix(vec4(vertexColor, 0.0), fadeColor, fadeValue);
}
