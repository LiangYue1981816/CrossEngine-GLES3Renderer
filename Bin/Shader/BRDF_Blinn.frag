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
	vec3 specularColor = texture(texSpecular, inTexcoord).rgb;

	float metallic = 0.7;
	float roughness = 0.3;

	vec3 pixelNormal = texture(texNormal, inTexcoord).rgb * 2.0 - 1.0;
	pixelNormal = normalize(inTBN * pixelNormal);

	vec3 envAmbientColor = Ambient_SH9(albedoColor, 0.0, (engineAmbientLight.rotationMatrix * vec4(pixelNormal, 0.0)).xyz, engineAmbientLight.shRed0, engineAmbientLight.shRed1, engineAmbientLight.shRed2, engineAmbientLight.shGreen0, engineAmbientLight.shGreen1, engineAmbientLight.shGreen2, engineAmbientLight.shBlue0, engineAmbientLight.shBlue1, engineAmbientLight.shBlue2);
	vec3 lightColor = BRDF_Blinn(engineDirectionLight.color, engineDirectionLight.direction, inHalfDirection, inViewDirection, pixelNormal, albedoColor, specularColor, metallic, roughness);
	vec3 final = envAmbientColor + lightColor;

	outFragColor.rgb = Linear2Gamma(final);
	outFragColor.a = 1.0;
}
