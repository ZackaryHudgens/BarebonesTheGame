#version 330 core

// Input variables
in vec2 texCoords;

// Output variables
out vec4 fragColor;

// Uniform variables
uniform vec4 textColor;
uniform sampler2D texSampler;

void main()
{
  fragColor = vec4(textColor.r, textColor.g, textColor.b, texture(texSampler, texCoords).r);
}
