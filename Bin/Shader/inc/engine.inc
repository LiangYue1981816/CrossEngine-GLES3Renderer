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
		mat4 transformMatrix;                                                      \
	} engineTransform

#define USE_ENGINE_AMBIENT_LIGHT                                               \
	uniform AmbientLight                                                         \
	{                                                                            \
		vec3 shRed0;                                                               \
		vec3 shRed1;                                                               \
		vec3 shRed2;                                                               \
		                                                                           \
		vec3 shGreen0;                                                             \
		vec3 shGreen1;                                                             \
		vec3 shGreen2;                                                             \
		                                                                           \
		vec3 shBlue0;                                                              \
		vec3 shBlue1;                                                              \
		vec3 shBlue2;                                                              \
		                                                                           \
		mat4 rotationMatrix;                                                       \
	} engineAmbientLight

#define USE_ENGINE_POINT_LIGHT                                                 \
	uniform PointLight                                                           \
	{                                                                            \
		vec3 color;                                                                \
		vec3 position;                                                             \
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
