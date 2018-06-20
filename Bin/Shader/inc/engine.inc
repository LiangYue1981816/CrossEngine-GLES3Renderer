#ifndef _ENGINE_INC_
#define _ENGINE_INC_

#define USE_VERTEX_ATTRIBUTE_POSITION  layout (location = 0) in vec3 inPosition
#define USE_VERTEX_ATTRIBUTE_NORMAL    layout (location = 1) in vec3 inNormal
#define USE_VERTEX_ATTRIBUTE_BINORMAL  layout (location = 2) in vec3 inBinormal
#define USE_VERTEX_ATTRIBUTE_COLOR     layout (location = 3) in vec3 inColor
#define USE_VERTEX_ATTRIBUTE_TEXCOORD0 layout (location = 4) in vec2 inTexcoord0
#define USE_VERTEX_ATTRIBUTE_TEXCOORD1 layout (location = 5) in vec2 inTexcoord1

#define USE_INSTANCE_ATTRIBUTE_TRANSFORM_MATRIX_COL0 layout (location = 8)  in vec4 inInstanceTransformMatrixCol0
#define USE_INSTANCE_ATTRIBUTE_TRANSFORM_MATRIX_COL1 layout (location = 9)  in vec4 inInstanceTransformMatrixCol1
#define USE_INSTANCE_ATTRIBUTE_TRANSFORM_MATRIX_COL2 layout (location = 10) in vec4 inInstanceTransformMatrixCol2
#define USE_INSTANCE_ATTRIBUTE_TRANSFORM_MATRIX_COL3 layout (location = 11) in vec4 inInstanceTransformMatrixCol3


#define USE_ENGINE_TIME                                                        \
	uniform Time                                                                 \
	{                                                                            \
		vec4 time;                                                                 \
		vec4 sinTime;                                                              \
		vec4 cosTime;                                                              \
		vec4 deltaTime;                                                            \
	} engineTime

#define USE_ENGINE_SCREEN                                                      \
	uniform Screen                                                               \
	{                                                                            \
		vec4 screen;                                                               \
	} engineScreen

#define USE_ENGINE_ZBUFFER                                                     \
	uniform ZBuffer                                                              \
	{                                                                            \
		vec4 zbuffer;                                                              \
	} engineZBuffer

#define USE_ENGINE_PROJECTION                                                  \
	uniform Projection                                                           \
	{                                                                            \
		vec4 projection;                                                           \
	} engineProjection

#define USE_ENGINE_CAMERA                                                      \
	uniform Camera                                                               \
	{                                                                            \
		mat4 projectionMatrix;                                                     \
		mat4 viewMatrix;                                                           \
		mat4 viewInverseMatrix;                                                    \
		mat4 viewInverseTransposeMatrix;                                           \
	} engineCamera

#define USE_ENGINE_TRANSFORM                                                   \
	uniform Transform                                                            \
	{                                                                            \
		mat4 worldMatrix;                                                          \
		mat4 worldInverseMatrix;                                                   \
		mat4 worldInverseTransposeMatrix;                                          \
	} engineTransform

#define USE_ENGINE_AMBIENT_LIGHT                                               \
	uniform AmbientLight                                                         \
	{                                                                            \
		vec4 shRed0;                                                               \
		vec4 shRed1;                                                               \
		vec4 shRed2;                                                               \
		                                                                           \
		vec4 shGreen0;                                                             \
		vec4 shGreen1;                                                             \
		vec4 shGreen2;                                                             \
		                                                                           \
		vec4 shBlue0;                                                              \
		vec4 shBlue1;                                                              \
		vec4 shBlue2;                                                              \
		                                                                           \
		mat4 rotationMatrix;                                                       \
	} engineAmbientLight

#define USE_ENGINE_POINT_LIGHT                                                 \
	uniform PointLight                                                           \
	{                                                                            \
		vec3 color;                                                                \
		vec3 position;                                                             \
		vec3 attenuation;                                                          \
	} enginePointLight

#define USE_ENGINE_DIRECTION_LIGHT                                             \
	uniform DirectionLight                                                       \
	{                                                                            \
		vec3 color;                                                                \
		vec3 direction;                                                            \
	} engineDirectionLight

#define USE_ENGINE_FOG                                                         \
	uniform Fog                                                                  \
	{                                                                            \
		vec3 color;                                                                \
		vec3 heightDensity;                                                        \
		vec3 distanceDensity;                                                      \
	} engineFog


USE_ENGINE_TIME;
USE_ENGINE_SCREEN;
USE_ENGINE_ZBUFFER;
USE_ENGINE_PROJECTION;

USE_ENGINE_CAMERA;
#define projectionMatrix engineCamera.projectionMatrix
#define viewMatrix engineCamera.viewMatrix
#define viewInverseMatrix engineCamera.viewInverseMatrix
#define viewInverseTransposeMatrix engineCamera.viewInverseTransposeMatrix

/*
USE_ENGINE_TRANSFORM;
#define worldMatrix engineTransform.worldMatrix
#define worldInverseMatrix engineTransform.worldInverseMatrix
#define worldInverseTransposeMatrix engineTransform.worldInverseTransposeMatrix
*/

#endif
