#version 310 es
precision mediump float;
#include "engine.inc"
#include "light.inc"


USE_ENGINE_AMBIENT_LIGHT;
USE_ENGINE_DIRECTION_LIGHT;

uniform sampler2D texAlbedo;
uniform sampler2D texNormal;
uniform sampler2D texSpecular;

layout (location = 0) in vec2 inTexcoord;
layout (location = 1) in vec3 inHalfDirection;
layout (location = 2) in vec3 inViewDirection;
layout (location = 3) in mat3 inTBN;

layout (location = 0) out vec4 outFragColor;


void main()
{
	vec3 albedoColor = Gamma2Linear(texture(texAlbedo, inTexcoord).rgb);
	vec4 specularColor = texture(texSpecular, inTexcoord);

	float roughness = specularColor.a;

	vec3 pixelNormal = texture(texNormal, inTexcoord).rgb * 2.0 - 1.0;
	pixelNormal = normalize(inTBN * pixelNormal);

	vec3 envDiffuseColor = Diffuse_SH(albedoColor, 0.0, pixelNormal, engineAmbientLight.rotationMatrix, engineAmbientLight.shRed0, engineAmbientLight.shRed1, engineAmbientLight.shRed2, engineAmbientLight.shGreen0, engineAmbientLight.shGreen1, engineAmbientLight.shGreen2, engineAmbientLight.shBlue0, engineAmbientLight.shBlue1, engineAmbientLight.shBlue2);
//	vec3 lightColor = BRDF_Blinn(engineDirectionLight.color, engineDirectionLight.direction, inHalfDirection, pixelNormal, albedoColor, specularColor.rgb, roughness);
	vec3 lightColor = BRDF_BlinnGGX(engineDirectionLight.color, engineDirectionLight.direction, inHalfDirection, inViewDirection, pixelNormal, albedoColor, specularColor.rgb, roughness);
	vec3 final = envDiffuseColor + lightColor;

	outFragColor.rgb = Linear2Gamma(final);
	outFragColor.a = 1.0;
}
