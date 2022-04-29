#version 330 core

// Input variables
in vec2 texCoords;

// Output variables
out vec4 fragColor;

// Uniform variables
uniform vec4 textColor;
uniform vec4 outlineColor;
uniform float outlineWidth;
uniform sampler2D texSampler;

void main()
{
  vec4 fragment = vec4(textColor.r, textColor.g, textColor.b, texture(texSampler, texCoords).r);

  vec2 outlineBorder = outlineWidth / textureSize(texSampler, 0);

  vec4 northFragment = vec4(1.0, 1.0, 1.0, texture(texSampler, vec2(texCoords.x, texCoords.y - outlineBorder.y)));
  vec4 northEastFragment = vec4(1.0, 1.0, 1.0, texture(texSampler, vec2(texCoords.x - outlineBorder.x, texCoords.y - outlineBorder.y)));
  vec4 northWestFragment = vec4(1.0, 1.0, 1.0, texture(texSampler, vec2(texCoords.x + outlineBorder.x, texCoords.y - outlineBorder.y)));
  vec4 southFragment = vec4(1.0, 1.0, 1.0, texture(texSampler, vec2(texCoords.x, texCoords.y + outlineBorder.y)));
  vec4 southEastFragment = vec4(1.0, 1.0, 1.0, texture(texSampler, vec2(texCoords.x - outlineBorder.x, texCoords.y + outlineBorder.y)));
  vec4 southWestFragment = vec4(1.0, 1.0, 1.0, texture(texSampler, vec2(texCoords.x + outlineBorder.x, texCoords.y + outlineBorder.y)));
  vec4 eastFragment = vec4(1.0, 1.0, 1.0, texture(texSampler, vec2(texCoords.x - outlineBorder.x, texCoords.y)));
  vec4 westFragment = vec4(1.0, 1.0, 1.0, texture(texSampler, vec2(texCoords.x + outlineBorder.x, texCoords.y)));

  float outlineAlpha = fragment.a;
  outlineAlpha = mix(outlineAlpha, 1.0, northFragment.a);
  outlineAlpha = mix(outlineAlpha, 1.0, northEastFragment.a);
  outlineAlpha = mix(outlineAlpha, 1.0, northWestFragment.a);
  outlineAlpha = mix(outlineAlpha, 1.0, southFragment.a);
  outlineAlpha = mix(outlineAlpha, 1.0, southEastFragment.a);
  outlineAlpha = mix(outlineAlpha, 1.0, southWestFragment.a);
  outlineAlpha = mix(outlineAlpha, 1.0, eastFragment.a);
  outlineAlpha = mix(outlineAlpha, 1.0, westFragment.a);
  vec4 outlineColorWithAlpha = vec4(outlineColor.r, outlineColor.g, outlineColor.b, outlineAlpha);

  fragColor = mix(outlineColorWithAlpha, fragment, fragment.a);
}
