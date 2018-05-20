#version 310 es
precision mediump float;
#include "engine.inc"
#include "light.inc"

USE_VERTEX_ATTRIBUTE_POSITION;
USE_VERTEX_ATTRIBUTE_NORMAL;
USE_VERTEX_ATTRIBUTE_BINORMAL;
USE_VERTEX_ATTRIBUTE_TEXCOORD0;

USE_INSTANCE_ATTRIBUTE_TRANSFORM_MATRIX_COL0;
USE_INSTANCE_ATTRIBUTE_TRANSFORM_MATRIX_COL1;
USE_INSTANCE_ATTRIBUTE_TRANSFORM_MATRIX_COL2;
USE_INSTANCE_ATTRIBUTE_TRANSFORM_MATRIX_COL3;

USE_ENGINE_CAMERA;
USE_ENGINE_DIRECTION_LIGHT;

layout (location = 0) out vec2 outTexcoord;
layout (location = 1) out vec3 outHalfDirection;
layout (location = 2) out vec3 outViewDirection;
layout (location = 3) out vec3 outDirectionLightColor;
layout (location = 4) out vec3 outDirectionLightDirection;
layout (location = 5) out mat3 outTBN;

void main()
{
	mat4 worldMatrix = mat4(inInstanceTransformMatrixCol0, inInstanceTransformMatrixCol1, inInstanceTransformMatrixCol2, inInstanceTransformMatrixCol3);

	vec3 viewNormal;
	viewNormal = (engineCamera.viewInverseTransposeMatrix * worldMatrix * vec4(inNormal, 0.0f)).xyz;
	viewNormal = normalize(viewNormal);

	vec3 viewBinormal;
	viewBinormal = (engineCamera.viewInverseTransposeMatrix * worldMatrix * vec4(inBinormal, 0.0f)).xyz;
	viewBinormal = normalize(viewBinormal);

	vec3 viewDirectionLightDirection;
	viewDirectionLightDirection = (engineCamera.viewInverseTransposeMatrix * vec4(engineDirectionLight.direction, 0.0f)).xyz;
	viewDirectionLightDirection = normalize(viewDirectionLightDirection);

	vec3 viewHalfDirection;
	viewHalfDirection = viewDirectionLightDirection + vec3(0.0, 0.0, 1.0);
	viewHalfDirection = normalize(viewHalfDirection);

	vec3 t = cross(viewBinormal, viewNormal);
	vec3 b = cross(viewNormal, t);
	mat3 tbn = mat3(t, b, viewNormal);
	
	outTBN = tbn;
	outTexcoord = inTexcoord0;
	outHalfDirection = viewHalfDirection * tbn;
	outViewDirection = vec3(0.0, 0.0, 1.0) * tbn;
	outDirectionLightDirection = viewDirectionLightDirection * tbn;
	outDirectionLightColor = engineDirectionLight.color;

	gl_Position = engineCamera.projectionMatrix * engineCamera.viewMatrix * worldMatrix * vec4(inPosition.xyz, 1.0);
}
