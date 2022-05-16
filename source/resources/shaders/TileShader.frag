#version 330 core

// Input variables
in vec2 texCoords;

// Output variables
out vec4 fragColor;

// Uniform variables
uniform sampler2D texSampler;

uniform vec4 highlightColor;
uniform float highlightIntensity;

void main()
{
  vec4 textureColor = texture(texSampler, texCoords);
  fragColor = mix(textureColor, highlightColor, highlightIntensity);
}
