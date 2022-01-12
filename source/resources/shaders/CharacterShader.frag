#version 330 core

// Input variables
in vec2 texCoords;

// Output variables
out vec4 fragColor;

// Uniform variables
uniform sampler2D texSampler;
uniform vec4 selectionColor;

void main()
{
  fragColor = selectionColor * texture(texSampler, texCoords);
}
