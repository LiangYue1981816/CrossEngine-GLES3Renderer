#version 310 es
precision mediump float;
#include "engine.inc"
#include "light.inc"

USE_ENGINE_AMBIENT_LIGHT;
USE_ENGINE_DIRECTION_LIGHT;

uniform sampler2D texAO;
uniform sampler2D texAlbedo;
uniform sampler2D texNormal;
uniform sampler2D texRoughMetallic;
uniform samplerCube texEnv;

layout (location = 0) in vec2 inTexcoord;
layout (location = 1) in vec3 inHalfDirection;
layout (location = 2) in vec3 inViewDirection;
layout (location = 3) in vec3 inDirectionLightColor;
layout (location = 4) in vec3 inDirectionLightDirection;
layout (location = 5) in mat3 inTBN;

layout (location = 0) out vec4 outFragColor;


void main()
{
	vec3 albedoColor = Gamma2Linear(texture(texAlbedo, inTexcoord).rgb);
	vec3 rough_metallic = texture(texRoughMetallic, inTexcoord).rgb;
	vec3 aoColor = texture(texAO, inTexcoord).rgb;

	float metallic = rough_metallic.b;
	float roughness = rough_metallic.g;

	vec3 pixelNormal;
	pixelNormal = texture(texNormal, inTexcoord).rgb * 2.0 - 1.0;
	pixelNormal = normalize(pixelNormal);

	vec3 pixelNormalWorld;
	pixelNormalWorld = inTBN * pixelNormal;
	pixelNormalWorld = normalize(pixelNormalWorld);

	vec3 viewDirectionWorld;
	viewDirectionWorld = inTBN * inViewDirection;
	viewDirectionWorld = normalize(viewDirectionWorld);

	vec3 envDiffuseColor = Diffuse_SH(albedoColor, metallic, pixelNormalWorld, engineAmbientLight.rotationMatrix, engineAmbientLight.shRed0, engineAmbientLight.shRed1, engineAmbientLight.shRed2, engineAmbientLight.shGreen0, engineAmbientLight.shGreen1, engineAmbientLight.shGreen2, engineAmbientLight.shBlue0, engineAmbientLight.shBlue1, engineAmbientLight.shBlue2);
	vec3 envSpecularColor = BRDF_EnvSpecular(viewDirectionWorld, pixelNormalWorld, albedoColor, metallic, roughness, texEnv);
	vec3 lightColor = BRDF_Pbr(engineDirectionLight.color, inDirectionLightDirection, inHalfDirection, inViewDirection, pixelNormal, albedoColor, metallic, roughness);
	vec3 final = (envDiffuseColor + envSpecularColor + lightColor) * aoColor;

	outFragColor.rgb = Linear2Gamma(final);
	outFragColor.a = 1.0;
}
