#include "stdio.h"
#include "stdlib.h"
#include "GfxRenderer.h"


static GLenum StringToFrontFace(const char *szString)
{
	if (szString) {
		if (!stricmp(szString, "GL_CW")) return GL_CW;
		if (!stricmp(szString, "GL_CCW")) return GL_CCW;
	}

	return GL_CCW;
}

static GLenum StringToDepthFunc(const char *szString)
{
	if (szString) {
		if (!stricmp(szString, "GL_NEVER")) return GL_NEVER;
		if (!stricmp(szString, "GL_LESS")) return GL_LESS;
		if (!stricmp(szString, "GL_EQUAL")) return GL_EQUAL;
		if (!stricmp(szString, "GL_LEQUAL")) return GL_LEQUAL;
		if (!stricmp(szString, "GL_GREATER")) return GL_GREATER;
		if (!stricmp(szString, "GL_NOTEQUAL")) return GL_NOTEQUAL;
		if (!stricmp(szString, "GL_GEQUAL")) return GL_GEQUAL;
	}

	return GL_LESS;
}

static GLenum StringToMinFilter(const char *szString)
{
	if (szString) {
		if (!stricmp(szString, "GL_LINEAR")) return GL_LINEAR;
		if (!stricmp(szString, "GL_LINEAR_MIPMAP_LINEAR")) return GL_LINEAR_MIPMAP_LINEAR;
		if (!stricmp(szString, "GL_LINEAR_MIPMAP_NEAREST")) return GL_LINEAR_MIPMAP_NEAREST;
		if (!stricmp(szString, "GL_NEAREST")) return GL_NEAREST;
		if (!stricmp(szString, "GL_NEAREST_MIPMAP_LINEAR")) return GL_NEAREST_MIPMAP_LINEAR;
		if (!stricmp(szString, "GL_NEAREST_MIPMAP_NEAREST")) return GL_NEAREST_MIPMAP_NEAREST;
	}
	
	return GL_LINEAR_MIPMAP_NEAREST;
}

static GLenum StringToMagFilter(const char *szString)
{
	if (szString) {
		if (!stricmp(szString, "GL_LINEAR")) return GL_LINEAR;
		if (!stricmp(szString, "GL_NEAREST")) return GL_NEAREST;
	}

	return GL_LINEAR;
}

static GLenum StringToAddressMode(const char *szString)
{
	if (szString) {
		if (!stricmp(szString, "GL_REPEAT")) return GL_REPEAT;
		if (!stricmp(szString, "GL_CLAMP_TO_EDGE")) return GL_CLAMP_TO_EDGE;
	}

	return GL_REPEAT;
}

static GLenum StringToBlendSrcFactor(const char *szString)
{
	if (szString) {
		if (!stricmp(szString, "GL_ZERO")) return GL_ZERO;
		if (!stricmp(szString, "GL_ONE")) return GL_ONE;
		if (!stricmp(szString, "GL_SRC_COLOR")) return GL_SRC_COLOR;
		if (!stricmp(szString, "GL_ONE_MINUS_SRC_COLOR")) return GL_ONE_MINUS_SRC_COLOR;
		if (!stricmp(szString, "GL_DST_COLOR")) return GL_DST_COLOR;
		if (!stricmp(szString, "GL_ONE_MINUS_DST_COLOR")) return GL_ONE_MINUS_DST_COLOR;
		if (!stricmp(szString, "GL_SRC_ALPHA")) return GL_SRC_ALPHA;
		if (!stricmp(szString, "GL_ONE_MINUS_SRC_ALPHA")) return GL_ONE_MINUS_SRC_ALPHA;
		if (!stricmp(szString, "GL_DST_ALPHA")) return GL_DST_ALPHA;
		if (!stricmp(szString, "GL_ONE_MINUS_DST_ALPHA")) return GL_ONE_MINUS_DST_ALPHA;
		if (!stricmp(szString, "GL_CONSTANT_COLOR")) return GL_CONSTANT_COLOR;
		if (!stricmp(szString, "GL_ONE_MINUS_CONSTANT_COLOR")) return GL_ONE_MINUS_CONSTANT_COLOR;
		if (!stricmp(szString, "GL_CONSTANT_ALPHA")) return GL_CONSTANT_ALPHA;
		if (!stricmp(szString, "GL_ONE_MINUS_CONSTANT_ALPHA")) return GL_ONE_MINUS_CONSTANT_ALPHA;
		if (!stricmp(szString, "GL_SRC_ALPHA_SATURATE")) return GL_SRC_ALPHA_SATURATE;
	}

	return GL_SRC_ALPHA;
}

static GLenum StringToBlendDstFactor(const char *szString)
{
	if (szString) {
		if (!stricmp(szString, "GL_ZERO")) return GL_ZERO;
		if (!stricmp(szString, "GL_ONE")) return GL_ONE;
		if (!stricmp(szString, "GL_SRC_COLOR")) return GL_SRC_COLOR;
		if (!stricmp(szString, "GL_ONE_MINUS_SRC_COLOR")) return GL_ONE_MINUS_SRC_COLOR;
		if (!stricmp(szString, "GL_DST_COLOR")) return GL_DST_COLOR;
		if (!stricmp(szString, "GL_ONE_MINUS_DST_COLOR")) return GL_ONE_MINUS_DST_COLOR;
		if (!stricmp(szString, "GL_SRC_ALPHA")) return GL_SRC_ALPHA;
		if (!stricmp(szString, "GL_ONE_MINUS_SRC_ALPHA")) return GL_ONE_MINUS_SRC_ALPHA;
		if (!stricmp(szString, "GL_DST_ALPHA")) return GL_DST_ALPHA;
		if (!stricmp(szString, "GL_ONE_MINUS_DST_ALPHA")) return GL_ONE_MINUS_DST_ALPHA;
		if (!stricmp(szString, "GL_CONSTANT_COLOR")) return GL_CONSTANT_COLOR;
		if (!stricmp(szString, "GL_ONE_MINUS_CONSTANT_COLOR")) return GL_ONE_MINUS_CONSTANT_COLOR;
		if (!stricmp(szString, "GL_CONSTANT_ALPHA")) return GL_CONSTANT_ALPHA;
		if (!stricmp(szString, "GL_ONE_MINUS_CONSTANT_ALPHA")) return GL_ONE_MINUS_CONSTANT_ALPHA;
		if (!stricmp(szString, "GL_SRC_ALPHA_SATURATE")) return GL_SRC_ALPHA_SATURATE;
	}

	return GL_ONE_MINUS_SRC_ALPHA;
}


CGfxMaterial::CGfxMaterial(void)
	: m_pProgram(NULL)

	, m_bEnableCullFace(true)
	, m_bEnableDepthTest(true)
	, m_bEnableDepthWrite(true)
	, m_bEnableBlend(false)
	, m_bEnablePolygonOffset(false)
	, m_bEnableDepthMask(true)
	, m_bEnableColorMaskRed(true)
	, m_bEnableColorMaskGreen(true)
	, m_bEnableColorMaskBlue(true)
	, m_bEnableColorMaskAlpha(true)
	, m_frontFace(GL_CCW)
	, m_depthFunc(GL_LESS)
	, m_srcBlendFactor(GL_SRC_ALPHA)
	, m_dstBlendFactor(GL_ONE_MINUS_SRC_ALPHA)
	, m_polygonOffsetFactor(0.0f)
	, m_polygonOffsetUnits(0.0f)
{

}

CGfxMaterial::~CGfxMaterial(void)
{
	Destroy();
}

void CGfxMaterial::Bind(void) const
{
	if (m_pProgram) {
		m_pProgram->UseProgram();
		BindPipeline();
		BindUniforms(m_pProgram);
		BindTextures(m_pProgram, 0);
	}
}

void CGfxMaterial::BindPipeline(void) const
{
	if (m_bEnableCullFace) {
		glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);
		glFrontFace(m_frontFace);
	}
	else {
		glDisable(GL_CULL_FACE);
	}

	if (m_bEnableDepthTest) {
		glEnable(GL_DEPTH_TEST);
		glDepthFunc(m_depthFunc);
	}
	else {
		glDisable(GL_DEPTH_TEST);
	}

	if (m_bEnableDepthWrite) {
		glDepthMask(GL_TRUE);
	}
	else {
		glDepthMask(GL_FALSE);
	}

	if (m_bEnableBlend) {
		glEnable(GL_BLEND);
		glBlendFunc(m_srcBlendFactor, m_dstBlendFactor);
	}
	else {
		glDisable(GL_BLEND);
	}

	if (m_bEnablePolygonOffset) {
		glEnable(GL_POLYGON_OFFSET_FILL);
		glPolygonOffset(m_polygonOffsetFactor, m_polygonOffsetUnits);
	}
	else {
		glDisable(GL_POLYGON_OFFSET_FILL);
	}

	glDepthMask(m_bEnableDepthMask);
	glColorMask(m_bEnableColorMaskRed, m_bEnableColorMaskGreen, m_bEnableColorMaskBlue, m_bEnableColorMaskAlpha);
}

void CGfxMaterial::BindUniforms(CGfxProgram *pProgram) const
{
	for (const auto &itUniform : m_pUniformVec1s) {
		itUniform.second->Apply();
		pProgram->BindUniformBuffer(itUniform.first, itUniform.second->GetBuffer(), itUniform.second->GetSize());
	}

	for (const auto &itUniform : m_pUniformVec2s) {
		itUniform.second->Apply();
		pProgram->BindUniformBuffer(itUniform.first, itUniform.second->GetBuffer(), itUniform.second->GetSize());
	}

	for (const auto &itUniform : m_pUniformVec3s) {
		itUniform.second->Apply();
		pProgram->BindUniformBuffer(itUniform.first, itUniform.second->GetBuffer(), itUniform.second->GetSize());
	}

	for (const auto &itUniform : m_pUniformVec4s) {
		itUniform.second->Apply();
		pProgram->BindUniformBuffer(itUniform.first, itUniform.second->GetBuffer(), itUniform.second->GetSize());
	}

	for (const auto &itUniform : m_pUniformMat4s) {
		itUniform.second->Apply();
		pProgram->BindUniformBuffer(itUniform.first, itUniform.second->GetBuffer(), itUniform.second->GetSize());
	}
}

void CGfxMaterial::BindTextures(CGfxProgram *pProgram, GLuint indexUnit) const
{
	for (const auto &itTexture : m_pTexture2ds) {
		if (pProgram->BindTexture2D(itTexture.first, itTexture.second->GetTexture(), itTexture.second->GetSampler(), indexUnit)) {
			indexUnit++;
		}
	}

	for (const auto &itTexture : m_pTexture2dArrays) {
		if (pProgram->BindTextureArray(itTexture.first, itTexture.second->GetTexture(), itTexture.second->GetSampler(), indexUnit)) {
			indexUnit++;
		}
	}

	for (const auto &itTexture : m_pTextureCubeMaps) {
		if (pProgram->BindTextureCubeMap(itTexture.first, itTexture.second->GetTexture(), itTexture.second->GetSampler(), indexUnit)) {
			indexUnit++;
		}
	}
}

bool CGfxMaterial::Create(const char *szFileName)
{
	try {
		Destroy();

		printf("LoadMaterial(%s)\n", szFileName);
		{
			if (Load(szFileName) == false) {
				throw 0;
			}
		}
		printf("OK\n");
		return true;
	}
	catch (int err) {
		Destroy();

		printf("Fail(%d)\n", err);
		return false;
	}
}

bool CGfxMaterial::Load(const char *szFileName)
{
	/*
	<Material>
		<Cull enable="" front_face="" />
		<Depth enable_test="" enable_write="" depth_func="" />
		<Blend enable="" src_factor="" dst_factor="" />
		<Offset enable="" factor="" units="" />
		<DepthMask enable="" />
		<ColorMask enable_red="" enable_green="" enable_blue="" enable_alpha="" />

		<Program vertex_file_name="" fragment_file_name="" />

		<Texture2D file_name="" name="" min_filter="" mag_filter="" address_mode="" />
		<Texture2DArray file_name="" name="" min_filter="" mag_filter="" address_mode="" />
		<TextureCubeMap file_name="" name="" min_filter="" mag_filter="" address_mode="" />

		<Uniform1f name="" value="" />
		<Uniform2f name="" value="" />
		<Uniform3f name="" value="" />
		<Uniform4f name="" value="" />
	</Material>
	*/

	char szFullPath[260];
	CGfxRenderer::GetInstance()->GetMaterialFullPath(szFileName, szFullPath);

	TiXmlDocument xmlDoc;
	if (xmlDoc.LoadFile(szFullPath)) {
		if (TiXmlNode *pMaterialNode = xmlDoc.FirstChild("Material")) {
			if (LoadBase(pMaterialNode) == false) return false;
			if (LoadProgram(pMaterialNode) == false) return false;
			if (LoadTexture2D(pMaterialNode) == false) return false;
			if (LoadTexture2DArray(pMaterialNode) == false) return false;
			if (LoadTextureCubeMap(pMaterialNode) == false) return false;
			if (LoadUniformVec1(pMaterialNode) == false) return false;
			if (LoadUniformVec2(pMaterialNode) == false) return false;
			if (LoadUniformVec3(pMaterialNode) == false) return false;
			if (LoadUniformVec4(pMaterialNode) == false) return false;
		}

		return true;
	}

	return false;
}

bool CGfxMaterial::LoadBase(TiXmlNode *pMaterialNode)
{
	try {
		printf("\tLoadBase ... ");
		{
			if (TiXmlNode *pCullNode = pMaterialNode->FirstChild("Cull")) {
				m_bEnableCullFace = pCullNode->ToElement()->AttributeBool("enable");
				m_frontFace = StringToFrontFace(pCullNode->ToElement()->AttributeString("front_face"));
			}

			if (TiXmlNode *pDepthNode = pMaterialNode->FirstChild("Depth")) {
				m_bEnableDepthTest = pDepthNode->ToElement()->AttributeBool("enable_test");
				m_bEnableDepthWrite = pDepthNode->ToElement()->AttributeBool("enable_write");
				m_depthFunc = StringToDepthFunc(pDepthNode->ToElement()->AttributeString("depth_func"));
			}

			if (TiXmlNode *pBlendNode = pMaterialNode->FirstChild("Blend")) {
				m_bEnableBlend = pBlendNode->ToElement()->AttributeBool("enable");
				m_srcBlendFactor = StringToBlendSrcFactor(pBlendNode->ToElement()->AttributeString("src_factor"));
				m_dstBlendFactor = StringToBlendDstFactor(pBlendNode->ToElement()->AttributeString("dst_factor"));
			}

			if (TiXmlNode *pOffsetNode = pMaterialNode->FirstChild("Offset")) {
				m_bEnablePolygonOffset = pOffsetNode->ToElement()->AttributeBool("enable");
				m_polygonOffsetFactor = pOffsetNode->ToElement()->AttributeFloat1("factor");
				m_polygonOffsetUnits = pOffsetNode->ToElement()->AttributeFloat1("units");
			}

			if (TiXmlNode *pDepthMaskNode = pMaterialNode->FirstChild("DepthMask")) {
				m_bEnableDepthMask = pDepthMaskNode->ToElement()->AttributeBool("enable");
			}

			if (TiXmlNode *pColorMaskNode = pMaterialNode->FirstChild("ColorMask")) {
				m_bEnableColorMaskRed = pColorMaskNode->ToElement()->AttributeBool("enable_red");
				m_bEnableColorMaskGreen = pColorMaskNode->ToElement()->AttributeBool("enable_green");
				m_bEnableColorMaskBlue = pColorMaskNode->ToElement()->AttributeBool("enable_blue");
				m_bEnableColorMaskAlpha = pColorMaskNode->ToElement()->AttributeBool("enable_alpha");
			}
		}
		printf("OK\n");
		return true;
	}
	catch (int) {
		printf("Fail\n");
		return false;
	}
}

bool CGfxMaterial::LoadProgram(TiXmlNode *pMaterialNode)
{
	try {
		printf("\tLoadProgram ... \n");
		{
			int err = 0;

			TiXmlNode *pProgramNode = pMaterialNode->FirstChild("Program");
			if (pProgramNode == NULL) throw err++;

			const char *szVertexFileName = pProgramNode->ToElement()->AttributeString("vertex_file_name");
			const char *szFragmentFileName = pProgramNode->ToElement()->AttributeString("fragment_file_name");
			if (szVertexFileName == NULL || szFragmentFileName == NULL) throw err++;

			m_pProgram = new CGfxProgram;
			if (m_pProgram == NULL) throw err++;
			if (m_pProgram->Create(szVertexFileName, szFragmentFileName) == false) throw err++;
		}
		printf("\tOK\n");
		return true;
	}
	catch (int err) {
		printf("\tFail(%d)\n", err);
		return false;
	}
}

bool CGfxMaterial::LoadTexture2D(TiXmlNode *pMaterialNode)
{
	try {
		TiXmlNode *pTextureNode = pMaterialNode->FirstChild("Texture2D");
		if (pTextureNode == NULL) return true;

		printf("\tLoadTexture2D ... \n");
		{
			do {
				int err = 0;

				const char *szFileName = pTextureNode->ToElement()->AttributeString("file_name");
				const char *szName = pTextureNode->ToElement()->AttributeString("name");
				if (szFileName == NULL || szName == NULL) throw err++;

				GLuint name = HashValue(szName);
				GLenum minFilter = StringToMinFilter(pTextureNode->ToElement()->AttributeString("min_filter"));
				GLenum magFilter = StringToMagFilter(pTextureNode->ToElement()->AttributeString("mag_filter"));
				GLenum addressMode = StringToAddressMode(pTextureNode->ToElement()->AttributeString("address_mode"));
				if (minFilter == GL_INVALID_ENUM || magFilter == GL_INVALID_ENUM || addressMode == GL_INVALID_ENUM) throw err++;

				if (m_pTexture2ds.find(name) != m_pTexture2ds.end()) {
					throw err++;
				}

				if (m_pProgram->IsTextureValid(name)) {
					if (m_pTexture2ds[name] = new CGfxTexture2D) {
						if (m_pTexture2ds[name]->Create(szFileName, minFilter, magFilter, addressMode) == false) {
							throw err++;
						}
					}
				}
			} while (pTextureNode = pMaterialNode->IterateChildren("Texture2D", pTextureNode));
		}
		printf("\tOK\n");
		return true;
	}
	catch (int err) {
		printf("\tFail(%d)\n", err);
		return false;
	}
}

bool CGfxMaterial::LoadTexture2DArray(TiXmlNode *pMaterialNode)
{
	try {
		TiXmlNode *pTextureNode = pMaterialNode->FirstChild("Texture2DArray");
		if (pTextureNode == NULL) return true;

		printf("\tLoadTexture2DArray ... \n");
		{
			do {
				int err = 0;

				const char *szFileName = pTextureNode->ToElement()->AttributeString("file_name");
				const char *szName = pTextureNode->ToElement()->AttributeString("name");
				if (szFileName == NULL || szName == NULL) throw err++;

				GLuint name = HashValue(szName);
				GLenum minFilter = StringToMinFilter(pTextureNode->ToElement()->AttributeString("min_filter"));
				GLenum magFilter = StringToMagFilter(pTextureNode->ToElement()->AttributeString("mag_filter"));
				GLenum addressMode = StringToAddressMode(pTextureNode->ToElement()->AttributeString("address_mode"));
				if (minFilter == GL_INVALID_ENUM || magFilter == GL_INVALID_ENUM || addressMode == GL_INVALID_ENUM) throw err++;

				if (m_pTexture2dArrays.find(name) != m_pTexture2dArrays.end()) {
					throw err++;
				}

				if (m_pProgram->IsTextureValid(name)) {
					if (m_pTexture2dArrays[name] = new CGfxTexture2DArray) {
						if (m_pTexture2dArrays[name]->Create(szFileName, minFilter, magFilter, addressMode) == false) {
							throw err++;
						}
					}
				}
			} while (pTextureNode = pMaterialNode->IterateChildren("Texture2DArray", pTextureNode));
		}
		printf("\tOK\n");
		return true;
	}
	catch (int err) {
		printf("\tFail(%d)\n", err);
		return false;
	}
}

bool CGfxMaterial::LoadTextureCubeMap(TiXmlNode *pMaterialNode)
{
	try {
		TiXmlNode *pTextureNode = pMaterialNode->FirstChild("TextureCubeMap");
		if (pTextureNode == NULL) return true;

		printf("\tLoadTextureCubeMap ... \n");
		{
			do {
				int err = 0;

				const char *szFileName = pTextureNode->ToElement()->AttributeString("file_name");
				const char *szName = pTextureNode->ToElement()->AttributeString("name");
				if (szFileName == NULL || szName == NULL) throw err++;

				GLuint name = HashValue(szName);
				GLenum minFilter = StringToMinFilter(pTextureNode->ToElement()->AttributeString("min_filter"));
				GLenum magFilter = StringToMagFilter(pTextureNode->ToElement()->AttributeString("mag_filter"));
				GLenum addressMode = StringToAddressMode(pTextureNode->ToElement()->AttributeString("address_mode"));
				if (minFilter == GL_INVALID_ENUM || magFilter == GL_INVALID_ENUM || addressMode == GL_INVALID_ENUM) throw err++;

				if (m_pTextureCubeMaps.find(name) != m_pTextureCubeMaps.end()) {
					throw err++;
				}

				if (m_pProgram->IsTextureValid(name)) {
					if (m_pTextureCubeMaps[name] = new CGfxTextureCubeMap) {
						if (m_pTextureCubeMaps[name]->Create(szFileName, minFilter, magFilter, addressMode) == false) {
							throw err++;
						}
					}
				}
			} while (pTextureNode = pMaterialNode->IterateChildren("TextureCubeMap", pTextureNode));
		}
		printf("\tOK\n");
		return true;
	}
	catch (int err) {
		printf("\tFail(%d)\n", err);
		return false;
	}
}

bool CGfxMaterial::LoadUniformVec1(TiXmlNode *pMaterialNode)
{
	try {
		TiXmlNode *pUniformNode = pMaterialNode->FirstChild("Uniform1f");
		if (pUniformNode == NULL) return true;

		printf("\tLoadUniformVec1 ... ");
		{
			do {
				int err = 0;

				const char *szName = pUniformNode->ToElement()->AttributeString("name");
				if (szName == NULL) throw err++;

				GLuint name = HashValue(szName);
				GLfloat value = pUniformNode->ToElement()->AttributeFloat1("value");

				if (m_pUniformVec1s.find(name) != m_pUniformVec1s.end()) {
					throw err++;
				}

				if (m_pProgram->IsUniformValid(name)) {
					if (m_pUniformVec1s[name] = new CGfxUniformVec1) {
						m_pUniformVec1s[name]->SetValue(value);
					}
				}
			} while (pUniformNode = pMaterialNode->IterateChildren("Uniform1f", pUniformNode));
		}
		printf("OK\n");
		return true;
	}
	catch (int err) {
		printf("Fail(%d)\n", err);
		return false;
	}
}

bool CGfxMaterial::LoadUniformVec2(TiXmlNode *pMaterialNode)
{
	try {
		TiXmlNode *pUniformNode = pMaterialNode->FirstChild("Uniform2f");
		if (pUniformNode == NULL) return true;

		printf("\tLoadUniformVec2 ... ");
		{
			do {
				int err = 0;

				const char *szName = pUniformNode->ToElement()->AttributeString("name");
				if (szName == NULL) throw err++;

				GLuint name = HashValue(szName);
				GLfloat value[2]; pUniformNode->ToElement()->AttributeFloat2("value", value);

				if (m_pUniformVec2s.find(name) != m_pUniformVec2s.end()) {
					throw err++;
				}

				if (m_pProgram->IsUniformValid(name)) {
					if (m_pUniformVec2s[name] = new CGfxUniformVec2) {
						m_pUniformVec2s[name]->SetValue(value[0], value[1]);
					}
				}
			} while (pUniformNode = pMaterialNode->IterateChildren("Uniform2f", pUniformNode));
		}
		printf("OK\n");
		return true;
	}
	catch (int err) {
		printf("Fail(%d)\n", err);
		return false;
	}
}

bool CGfxMaterial::LoadUniformVec3(TiXmlNode *pMaterialNode)
{
	try {
		TiXmlNode *pUniformNode = pMaterialNode->FirstChild("Uniform3f");
		if (pUniformNode == NULL) return true;

		printf("\tLoadUniformVec3 ... ");
		{
			do {
				int err = 0;

				const char *szName = pUniformNode->ToElement()->AttributeString("name");
				if (szName == NULL) throw err++;

				GLuint name = HashValue(szName);
				GLfloat value[3]; pUniformNode->ToElement()->AttributeFloat3("value", value);

				if (m_pUniformVec3s.find(name) != m_pUniformVec3s.end()) {
					throw err++;
				}

				if (m_pProgram->IsUniformValid(name)) {
					if (m_pUniformVec3s[name] = new CGfxUniformVec3) {
						m_pUniformVec3s[name]->SetValue(value[0], value[1], value[2]);
					}
				}
			} while (pUniformNode = pMaterialNode->IterateChildren("Uniform3f", pUniformNode));
		}
		printf("OK\n");
		return true;
	}
	catch (int err) {
		printf("Fail(%d)\n", err);
		return false;
	}
}

bool CGfxMaterial::LoadUniformVec4(TiXmlNode *pMaterialNode)
{
	try {
		TiXmlNode *pUniformNode = pMaterialNode->FirstChild("Uniform4f");
		if (pUniformNode == NULL) return true;

		printf("\tLoadUniformVec4 ... ");
		{
			do {
				int err = 0;

				const char *szName = pUniformNode->ToElement()->AttributeString("name");
				if (szName == NULL) throw err++;

				GLuint name = HashValue(szName);
				GLfloat value[4]; pUniformNode->ToElement()->AttributeFloat4("value", value);

				if (m_pUniformVec4s.find(name) != m_pUniformVec4s.end()) {
					throw err++;
				}

				if (m_pProgram->IsUniformValid(name)) {
					if (m_pUniformVec4s[name] = new CGfxUniformVec4) {
						m_pUniformVec4s[name]->SetValue(value[0], value[1], value[2], value[3]);
					}
				}
			} while (pUniformNode = pMaterialNode->IterateChildren("Uniform4f", pUniformNode));
		}
		printf("OK\n");
		return true;
	}
	catch (int err) {
		printf("Fail(%d)\n", err);
		return false;
	}
}

void CGfxMaterial::Destroy(void)
{
	if (m_pProgram) {
		delete m_pProgram;
	}

	for (auto &itTexture : m_pTexture2ds) {
		delete itTexture.second;
	}

	for (auto &itTexture : m_pTexture2dArrays) {
		delete itTexture.second;
	}

	for (auto &itTexture : m_pTextureCubeMaps) {
		delete itTexture.second;
	}

	for (auto &itUniform : m_pUniformVec1s) {
		delete itUniform.second;
	}

	for (auto &itUniform : m_pUniformVec2s) {
		delete itUniform.second;
	}

	for (auto &itUniform : m_pUniformVec3s) {
		delete itUniform.second;
	}

	for (auto &itUniform : m_pUniformVec4s) {
		delete itUniform.second;
	}

	for (auto &itUniform : m_pUniformMat4s) {
		delete itUniform.second;
	}

	m_pProgram = NULL;
	m_pTexture2ds.clear();
	m_pTexture2dArrays.clear();
	m_pTextureCubeMaps.clear();
	m_pUniformVec1s.clear();
	m_pUniformVec2s.clear();
	m_pUniformVec3s.clear();
	m_pUniformVec4s.clear();
	m_pUniformMat4s.clear();
}

void CGfxMaterial::SetEnableCullFace(bool bEnable, GLenum frontFace)
{
	m_bEnableCullFace = bEnable;
	m_frontFace = frontFace;
}

void CGfxMaterial::SetEnableDepthTest(bool bEnable, GLenum depthFunc)
{
	m_bEnableDepthTest = bEnable;
	m_depthFunc = depthFunc;
}

void CGfxMaterial::SetEnableDepthWrite(bool bEnable)
{
	m_bEnableDepthWrite = bEnable;
}

void CGfxMaterial::SetEnableBlend(bool bEnable, GLenum srcFactor, GLenum dstFactor)
{
	m_bEnableBlend = bEnable;
	m_srcBlendFactor = srcFactor;
	m_dstBlendFactor = dstFactor;
}

void CGfxMaterial::SetEnablePolygonOffset(bool bEnable, GLfloat factor, GLfloat units)
{
	m_bEnablePolygonOffset = bEnable;
	m_polygonOffsetFactor = factor;
	m_polygonOffsetUnits = units;
}

void CGfxMaterial::SetEnableDepthMask(bool bEnable)
{
	m_bEnableDepthMask = bEnable;
}

void CGfxMaterial::SetEnableColorMask(bool bEnableRed, bool bEnableGreen, bool bEnableBlue, bool bEnableAlpha)
{
	m_bEnableColorMaskRed = bEnableRed;
	m_bEnableColorMaskGreen = bEnableGreen;
	m_bEnableColorMaskBlue = bEnableBlue;
	m_bEnableColorMaskAlpha = bEnableAlpha;
}

CGfxProgram* CGfxMaterial::GetProgram(void)
{
	if (m_pProgram == NULL) {
		m_pProgram = new CGfxProgram;
	}

	return m_pProgram;
}

CGfxTexture2D* CGfxMaterial::GetTexture2D(const char *szName)
{
	GLuint name = HashValue(szName);

	if ((m_pProgram == NULL) || (m_pProgram && m_pProgram->IsTextureValid(name))) {
		if (m_pTexture2ds[name] == NULL) {
			m_pTexture2ds[name] = new CGfxTexture2D;
		}

		return m_pTexture2ds[name];
	}

	return NULL;
}

CGfxTexture2DArray* CGfxMaterial::GetTexture2DArray(const char *szName)
{
	GLuint name = HashValue(szName);

	if ((m_pProgram == NULL) || (m_pProgram && m_pProgram->IsTextureValid(name))) {
		if (m_pTexture2dArrays[name] == NULL) {
			m_pTexture2dArrays[name] = new CGfxTexture2DArray;
		}

		return m_pTexture2dArrays[name];
	}

	return NULL;
}

CGfxTextureCubeMap* CGfxMaterial::GetTextureCubeMap(const char *szName)
{
	GLuint name = HashValue(szName);

	if ((m_pProgram == NULL) || (m_pProgram && m_pProgram->IsTextureValid(name))) {
		if (m_pTextureCubeMaps[name] == NULL) {
			m_pTextureCubeMaps[name] = new CGfxTextureCubeMap;
		}

		return m_pTextureCubeMaps[name];
	}

	return NULL;
}

CGfxUniformVec1* CGfxMaterial::GetUniformVec1(const char *szName)
{
	GLuint name = HashValue(szName);

	if ((m_pProgram == NULL) || (m_pProgram && m_pProgram->IsUniformValid(name))) {
		if (m_pUniformVec1s[name] == NULL) {
			m_pUniformVec1s[name] = new CGfxUniformVec1;
		}

		return m_pUniformVec1s[name];
	}

	return NULL;
}

CGfxUniformVec2* CGfxMaterial::GetUniformVec2(const char *szName)
{
	GLuint name = HashValue(szName);

	if ((m_pProgram == NULL) || (m_pProgram && m_pProgram->IsUniformValid(name))) {
		if (m_pUniformVec2s[name] == NULL) {
			m_pUniformVec2s[name] = new CGfxUniformVec2;
		}

		return m_pUniformVec2s[name];
	}

	return NULL;
}

CGfxUniformVec3* CGfxMaterial::GetUniformVec3(const char *szName)
{
	GLuint name = HashValue(szName);

	if ((m_pProgram == NULL) || (m_pProgram && m_pProgram->IsUniformValid(name))) {
		if (m_pUniformVec3s[name] == NULL) {
			m_pUniformVec3s[name] = new CGfxUniformVec3;
		}

		return m_pUniformVec3s[name];
	}

	return NULL;
}

CGfxUniformVec4* CGfxMaterial::GetUniformVec4(const char *szName)
{
	GLuint name = HashValue(szName);

	if ((m_pProgram == NULL) || (m_pProgram && m_pProgram->IsUniformValid(name))) {
		if (m_pUniformVec4s[name] == NULL) {
			m_pUniformVec4s[name] = new CGfxUniformVec4;
		}

		return m_pUniformVec4s[name];
	}

	return NULL;
}

CGfxUniformMat4* CGfxMaterial::GetUniformMat4(const char *szName)
{
	GLuint name = HashValue(szName);

	if ((m_pProgram == NULL) || (m_pProgram && m_pProgram->IsUniformValid(name))) {
		if (m_pUniformMat4s[name] == NULL) {
			m_pUniformMat4s[name] = new CGfxUniformMat4;
		}

		return m_pUniformMat4s[name];
	}

	return NULL;
}

GLuint CGfxMaterial::GetTextureUnits(void) const
{
	GLuint numTexUnits = 0;

	numTexUnits += m_pTexture2ds.size();
	numTexUnits += m_pTexture2dArrays.size();
	numTexUnits += m_pTextureCubeMaps.size();

	return numTexUnits;
}
