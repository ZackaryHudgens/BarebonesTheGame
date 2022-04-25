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
uniform vec4 fadeInColor;

uniform float fadeValue;

void main()
{
  vec4 textureColor = hoverColor * highlightColor * texture(texSampler, texCoords);
  vec4 testColor = vec4(0.89, 0.93, 0.75, 1.0);

  fragColor = mix(fadeInColor, textureColor, fadeValue);
}
