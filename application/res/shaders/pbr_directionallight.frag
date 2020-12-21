#version 300 es

precision mediump float;

in vec3 vViewSpaceNormal;
in vec3 vViewSpacePosition;
in vec2 vTexCoords;

uniform vec3 uLightDirection;
uniform vec3 uLightIntensity;
uniform vec4 uBaseColorFactor;
uniform sampler2D uBaseColorTexture;
uniform float uMetallicFactor;
uniform float uRoughnessFactor;
uniform sampler2D uMetallicRoughnessTexture;
uniform sampler2D uEmissiveTexture;
uniform vec3 uEmissiveFactor;
uniform sampler2D uOcclusionTexture;
uniform float uOcclusionStrength;

out vec3 fColor;

const float GAMMA = 2.2;
const float INV_GAMMA = 1. / GAMMA;
const float M_PI = 3.141592653589793;
const float M_1_PI = 1.0 / M_PI;
const vec3 black = vec3(0, 0, 0);
const vec3 dielectricSpecular = vec3(0.04f, 0.04f, 0.04f);

vec3 LINEARtoSRGB(vec3 color)
{
  return pow(color, vec3(INV_GAMMA));
}

vec4 SRGBtoLINEAR(vec4 srgbIn)
{
  return vec4(pow(srgbIn.xyz, vec3(GAMMA)), srgbIn.w);
}

void main()
{
  vec3 N = normalize(vViewSpaceNormal);
  vec3 L = uLightDirection;
  vec3 V = normalize(-vViewSpacePosition);
  vec3 H = normalize(L + V);

  float NdotL = clamp(dot(N, L), 0.0, 1.0);
  float NdotH = clamp(dot(N, H), 0.0, 1.0);
  float VdotH = clamp(dot(V, H), 0.0, 1.0);
  float NdotV = clamp(dot(N, V), 0.0, 1.0);

  vec4 baseColorFromTexture = SRGBtoLINEAR(texture(uBaseColorTexture, vTexCoords));
  vec4 baseColor = baseColorFromTexture * uBaseColorFactor;

  // Metallic / Roughness
  float metallic = texture(uMetallicRoughnessTexture, vTexCoords).b * uMetallicFactor;
  float roughness = texture(uMetallicRoughnessTexture, vTexCoords).g * uRoughnessFactor;

  // Emissive
  vec3 emissive = SRGBtoLINEAR(texture(uEmissiveTexture, vTexCoords)).rgb * uEmissiveFactor;

  // Occlusion
  float occlusion = texture(uOcclusionTexture, vTexCoords).r;

  float alpha = roughness * roughness;
  float alpha_squared = alpha * alpha;

  // Microfacet Distribution (D)
  // Trowbridge-Reitz
  float D = (M_PI * ((NdotH*NdotH * (alpha_squared - 1.0) + 1.0) * (NdotH*NdotH * (alpha_squared - 1.0) + 1.0)));

  // Surface Reflection Ratio (F)
  // Fresnel Schlick
  vec3 F0 = mix(dielectricSpecular, baseColor.rgb, metallic);
  float baseShlickFactor = (1.0 - VdotH);
  float shlickFactor = baseShlickFactor * baseShlickFactor; // power 2
  shlickFactor *= shlickFactor; // power 4
  shlickFactor *= baseShlickFactor; // power 5
  vec3 F = F0 + (1.0 - F0) * shlickFactor;

  // Geometric Occlusion (G)
  // Smith Joint GGX
  float visDenominator = NdotL * sqrt(NdotV*NdotV * (1.0-alpha_squared) + alpha_squared) + NdotV * sqrt(NdotL*NdotL * (1.0-alpha_squared) + alpha_squared);
  float Vis;
  if (visDenominator > 0.0) {
    Vis = .5f / visDenominator;
  } else {
    Vis = 0.f;
  }

  vec3 c_diff = mix(baseColor.rgb * (1.0 - dielectricSpecular.r), black, metallic);
  vec3 diffuse = c_diff * M_1_PI;
  vec3 f_diffuse = (1.0 - F) * diffuse;
  vec3 f_specular = F * Vis * D;

  vec3 nonOccludedColor = (f_diffuse + f_specular) * uLightIntensity * NdotL;
  vec3 occludedColor = mix(nonOccludedColor, nonOccludedColor * occlusion, uOcclusionStrength);

  fColor = LINEARtoSRGB(occludedColor + emissive);
}