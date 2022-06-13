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
  vec4 textureColor = texture(texSampler, texCoords);
  fragColor = vec4(textColor.r, textColor.g, textColor.b, textureColor.r);
  fragColor.a = mix(0.0, textColor.a, textureColor.r);
}
