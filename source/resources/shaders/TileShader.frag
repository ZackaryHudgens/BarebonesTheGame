#version 330 core

// Input variables
in vec3 vertexColor;
in vec2 texCoords;

// Output variables
out vec4 fragColor;

// Uniform variables
uniform sampler2D texSampler;
uniform vec4 highlightColor;
uniform vec4 hoverColor;

void main()
{
  fragColor = hoverColor * highlightColor * texture(texSampler, texCoords);//vec4(vertexColor, 1.0);
}
