#include "stdio.h"
#include "stdlib.h"
#include "Material.h"
#include "Renderer.h"


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


CMaterial::CMaterial(void)
	: m_pProgram(NULL)

	, m_bEnableCullFace(true)
	, m_bEnableDepthTest(true)
	, m_bEnableDepthWrite(true)
	, m_bEnableBlend(false)
	, m_bEnablePolygonOffset(false)
	, m_depthFunc(GL_LESS)
	, m_srcBlendFactor(GL_SRC_ALPHA)
	, m_dstBlendFactor(GL_ONE_MINUS_SRC_ALPHA)
	, m_polygonOffsetFactor(0.0f)
	, m_polygonOffsetUnits(0.0f)
{

}

CMaterial::~CMaterial(void)
{
	Destroy();
}

void CMaterial::Bind(void) const
{
	if (m_pProgram) {
		m_pProgram->UseProgram();
		BindPipeline();
		BindTextures();
		BindUniforms();
	}
}

void CMaterial::BindPipeline(void) const
{
	if (m_bEnableCullFace) {
		glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);
		glFrontFace(GL_CCW);
	}
	else {
		glDisable(GL_CULL_FACE);
	}

	if (m_bEnableDepthTest) {
		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LESS);
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
}

void CMaterial::BindTextures(void) const
{
	GLuint numTexUnits = 0;

	for (const auto &itTexture : m_pTexture2ds) {
		if (m_pProgram->BindTexture2D(itTexture.first, itTexture.second->GetTexture(), itTexture.second->GetSampler(), numTexUnits)) {
			numTexUnits++;
		}
	}

	for (const auto &itTexture : m_pTexture2dArrays) {
		if (m_pProgram->BindTextureArray(itTexture.first, itTexture.second->GetTexture(), itTexture.second->GetSampler(), numTexUnits)) {
			numTexUnits++;
		}
	}

	for (const auto &itTexture : m_pTextureCubeMaps) {
		if (m_pProgram->BindTextureCubeMap(itTexture.first, itTexture.second->GetTexture(), itTexture.second->GetSampler(), numTexUnits)) {
			numTexUnits++;
		}
	}
}

void CMaterial::BindUniforms(void) const
{
	for (const auto &itUniform : m_pUniformVec1s) {
		m_pProgram->BindUniformBuffer(itUniform.first, itUniform.second->GetBuffer(), itUniform.second->GetSize());
	}

	for (const auto &itUniform : m_pUniformVec2s) {
		m_pProgram->BindUniformBuffer(itUniform.first, itUniform.second->GetBuffer(), itUniform.second->GetSize());
	}

	for (const auto &itUniform : m_pUniformVec3s) {
		m_pProgram->BindUniformBuffer(itUniform.first, itUniform.second->GetBuffer(), itUniform.second->GetSize());
	}

	for (const auto &itUniform : m_pUniformVec4s) {
		m_pProgram->BindUniformBuffer(itUniform.first, itUniform.second->GetBuffer(), itUniform.second->GetSize());
	}

	for (const auto &itUniform : m_pUniformMat4s) {
		m_pProgram->BindUniformBuffer(itUniform.first, itUniform.second->GetBuffer(), itUniform.second->GetSize());
	}
}

bool CMaterial::Create(const char *szFileName)
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

bool CMaterial::Load(const char *szFileName)
{
	/*
	<Material>
		<Cull enable="" front_face="" />
		<Depth enable_test="" enable_write="" depth_func="" />
		<Blend enable="" src_factor="" dst_factor="" />
		<Offset enable="" factor="" units="" />

		<Program vertex_file_name="" fragment_file_name="" />

		<Texture2D file_name="" name="" min_filter="" mag_filter="" address_mode="" />
		<Texture2DArray file_name="" name="" min_filter="" mag_filter="" address_mode="" />
		<TextureCubeMap file_name="" name="" min_filter="" mag_filter="" address_mode="" />

		<UniformVec1 name="" value="" />
		<UniformVec2 name="" value="" />
		<UniformVec3 name="" value="" />
		<UniformVec4 name="" value="" />
	</Material>
	*/

	char szFullPath[260];
	CRenderer::GetInstance()->GetMaterialFullPath(szFileName, szFullPath);

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

bool CMaterial::LoadBase(TiXmlNode *pMaterialNode)
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
		}
		printf("OK\n");
		return true;
	}
	catch (int) {
		printf("Fail\n");
		return false;
	}
}

bool CMaterial::LoadProgram(TiXmlNode *pMaterialNode)
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

			m_pProgram = new CProgram;
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

bool CMaterial::LoadTexture2D(TiXmlNode *pMaterialNode)
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
					if (m_pTexture2ds[name] = new CTexture2D) {
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

bool CMaterial::LoadTexture2DArray(TiXmlNode *pMaterialNode)
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
					if (m_pTexture2dArrays[name] = new CTexture2DArray) {
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

bool CMaterial::LoadTextureCubeMap(TiXmlNode *pMaterialNode)
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
					if (m_pTextureCubeMaps[name] = new CTextureCubeMap) {
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

bool CMaterial::LoadUniformVec1(TiXmlNode *pMaterialNode)
{
	try {
		TiXmlNode *pUniformNode = pMaterialNode->FirstChild("UniformVec1");
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
					if (m_pUniformVec1s[name] = new CUniformBufferVec1) {
						m_pUniformVec1s[name]->SetValue(value);
						m_pUniformVec1s[name]->Apply();
					}
				}
			} while (pUniformNode = pMaterialNode->IterateChildren("UniformVec1", pUniformNode));
		}
		printf("OK\n");
		return true;
	}
	catch (int err) {
		printf("Fail(%d)\n", err);
		return false;
	}
}

bool CMaterial::LoadUniformVec2(TiXmlNode *pMaterialNode)
{
	try {
		TiXmlNode *pUniformNode = pMaterialNode->FirstChild("UniformVec2");
		if (pUniformNode == NULL) return true;

		printf("\tLoadUniform2f ... ");
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
					if (m_pUniformVec2s[name] = new CUniformBufferVec2) {
						m_pUniformVec2s[name]->SetValue(value[0], value[1]);
						m_pUniformVec2s[name]->Apply();
					}
				}
			} while (pUniformNode = pMaterialNode->IterateChildren("UniformVec2", pUniformNode));
		}
		printf("OK\n");
		return true;
	}
	catch (int err) {
		printf("Fail(%d)\n", err);
		return false;
	}
}

bool CMaterial::LoadUniformVec3(TiXmlNode *pMaterialNode)
{
	try {
		TiXmlNode *pUniformNode = pMaterialNode->FirstChild("UniformVec3");
		if (pUniformNode == NULL) return true;

		printf("\tLoadUniform3f ... ");
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
					if (m_pUniformVec3s[name] = new CUniformBufferVec3) {
						m_pUniformVec3s[name]->SetValue(value[0], value[1], value[2]);
						m_pUniformVec3s[name]->Apply();
					}
				}
			} while (pUniformNode = pMaterialNode->IterateChildren("UniformVec3", pUniformNode));
		}
		printf("OK\n");
		return true;
	}
	catch (int err) {
		printf("Fail(%d)\n", err);
		return false;
	}
}

bool CMaterial::LoadUniformVec4(TiXmlNode *pMaterialNode)
{
	try {
		TiXmlNode *pUniformNode = pMaterialNode->FirstChild("UniformVec4");
		if (pUniformNode == NULL) return true;

		printf("\tLoadUniform4f ... ");
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
					if (m_pUniformVec4s[name] = new CUniformBufferVec4) {
						m_pUniformVec4s[name]->SetValue(value[0], value[1], value[2], value[3]);
						m_pUniformVec4s[name]->Apply();
					}
				}
			} while (pUniformNode = pMaterialNode->IterateChildren("UniformVec4", pUniformNode));
		}
		printf("OK\n");
		return true;
	}
	catch (int err) {
		printf("Fail(%d)\n", err);
		return false;
	}
}

void CMaterial::Destroy(void)
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

void CMaterial::SetEnableCullFace(bool bEnable, GLenum frontFace)
{
	m_bEnableCullFace = bEnable;
	m_frontFace = frontFace;
}

void CMaterial::SetEnableDepthTest(bool bEnable, GLenum depthFunc)
{
	m_bEnableDepthTest = bEnable;
	m_depthFunc = depthFunc;
}

void CMaterial::SetEnableDepthWrite(bool bEnable)
{
	m_bEnableDepthWrite = bEnable;
}

void CMaterial::SetEnableBlend(bool bEnable, GLenum srcFactor, GLenum dstFactor)
{
	m_bEnableBlend = bEnable;
	m_srcBlendFactor = srcFactor;
	m_dstBlendFactor = dstFactor;
}

void CMaterial::SetEnablePolygonOffset(bool bEnable, GLfloat factor, GLfloat units)
{
	m_bEnablePolygonOffset = bEnable;
	m_polygonOffsetFactor = factor;
	m_polygonOffsetUnits = units;
}

CProgram* CMaterial::GetProgram(void)
{
	if (m_pProgram == NULL) {
		m_pProgram = new CProgram;
	}

	return m_pProgram;
}

CTexture2D* CMaterial::GetTexture2D(const char *szName)
{
	GLuint name = HashValue(szName);

	if (m_pProgram && m_pProgram->IsTextureValid(name)) {
		if (m_pTexture2ds[name] == NULL) {
			m_pTexture2ds[name] = new CTexture2D;
		}

		return m_pTexture2ds[name];
	}

	return NULL;
}

CTexture2DArray* CMaterial::GetTexture2DArray(const char *szName)
{
	GLuint name = HashValue(szName);

	if (m_pProgram && m_pProgram->IsTextureValid(name)) {
		if (m_pTexture2dArrays[name] == NULL) {
			m_pTexture2dArrays[name] = new CTexture2DArray;
		}

		return m_pTexture2dArrays[name];
	}

	return NULL;
}

CTextureCubeMap* CMaterial::GetTextureCubeMap(const char *szName)
{
	GLuint name = HashValue(szName);

	if (m_pProgram && m_pProgram->IsTextureValid(name)) {
		if (m_pTextureCubeMaps[name] == NULL) {
			m_pTextureCubeMaps[name] = new CTextureCubeMap;
		}

		return m_pTextureCubeMaps[name];
	}

	return NULL;
}

CUniformBufferVec1* CMaterial::GetUniformVec1(const char *szName)
{
	GLuint name = HashValue(szName);

	if (m_pProgram && m_pProgram->IsUniformValid(name)) {
		if (m_pUniformVec1s[name] == NULL) {
			m_pUniformVec1s[name] = new CUniformBufferVec1;
		}

		return m_pUniformVec1s[name];
	}

	return NULL;
}

CUniformBufferVec2* CMaterial::GetUniformVec2(const char *szName)
{
	GLuint name = HashValue(szName);

	if (m_pProgram && m_pProgram->IsUniformValid(name)) {
		if (m_pUniformVec2s[name] == NULL) {
			m_pUniformVec2s[name] = new CUniformBufferVec2;
		}

		return m_pUniformVec2s[name];
	}

	return NULL;
}

CUniformBufferVec3* CMaterial::GetUniformVec3(const char *szName)
{
	GLuint name = HashValue(szName);

	if (m_pProgram && m_pProgram->IsUniformValid(name)) {
		if (m_pUniformVec3s[name] == NULL) {
			m_pUniformVec3s[name] = new CUniformBufferVec3;
		}

		return m_pUniformVec3s[name];
	}

	return NULL;
}

CUniformBufferVec4* CMaterial::GetUniformVec4(const char *szName)
{
	GLuint name = HashValue(szName);

	if (m_pProgram && m_pProgram->IsUniformValid(name)) {
		if (m_pUniformVec4s[name] == NULL) {
			m_pUniformVec4s[name] = new CUniformBufferVec4;
		}

		return m_pUniformVec4s[name];
	}

	return NULL;
}

CUniformBufferMat4* CMaterial::GetUniformMat4(const char *szName)
{
	GLuint name = HashValue(szName);

	if (m_pProgram && m_pProgram->IsUniformValid(name)) {
		if (m_pUniformMat4s[name] == NULL) {
			m_pUniformMat4s[name] = new CUniformBufferMat4;
		}

		return m_pUniformMat4s[name];
	}

	return NULL;
}

GLuint CMaterial::GetTextureUnits(void) const
{
	GLuint numTexUnits = 0;

	numTexUnits += m_pTexture2ds.size();
	numTexUnits += m_pTexture2dArrays.size();
	numTexUnits += m_pTextureCubeMaps.size();

	return numTexUnits;
}
