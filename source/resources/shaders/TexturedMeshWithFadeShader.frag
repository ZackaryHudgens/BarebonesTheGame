#version 330 core

// Input variables
in vec2 texCoords;

// Output variables
out vec4 fragColor;

// Uniform variables
uniform sampler2D texSampler;

uniform vec4 fadeColor;
uniform float fadeValue;

void main()
{
  vec4 textureColor = texture(texSampler, texCoords);
  fragColor = vec4(mix(textureColor.rgb, fadeColor.rgb, fadeValue), textureColor.a);
}
