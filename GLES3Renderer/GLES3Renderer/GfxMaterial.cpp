#include "stdio.h"
#include "stdlib.h"
#include "GfxUtils.h"
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


CGfxMaterial::CGfxMaterial(GLuint name)
	: m_name(name)
	, m_pProgram(NULL)

	, refCount(0)
{
	m_state.bEnableCullFace = GL_TRUE;
	m_state.bEnableDepthTest = GL_TRUE;
	m_state.bEnableDepthWrite = GL_TRUE;
	m_state.bEnableColorWrite[0] = GL_TRUE;
	m_state.bEnableColorWrite[1] = GL_TRUE;
	m_state.bEnableColorWrite[2] = GL_TRUE;
	m_state.bEnableColorWrite[3] = GL_TRUE;
	m_state.bEnableBlend = GL_FALSE;
	m_state.bEnablePolygonOffset = GL_FALSE;
	m_state.frontFace = GL_CCW;
	m_state.depthFunc = GL_LESS;
	m_state.srcBlendFactor = GL_SRC_ALPHA;
	m_state.dstBlendFactor = GL_ONE_MINUS_SRC_ALPHA;
	m_state.polygonOffsetFactor = 0.0f;
	m_state.polygonOffsetUnits = 0.0f;
}

CGfxMaterial::~CGfxMaterial(void)
{
	Free();
}

GLuint CGfxMaterial::GetName(void) const
{
	return m_name;
}

void CGfxMaterial::Bind(void) const
{
	if (m_pProgram) {
		m_pProgram->UseProgram();
		BindState();
		BindUniforms(m_pProgram);
		BindTextures(m_pProgram, 0);
	}
}

void CGfxMaterial::BindState(void) const
{
	if (m_state.bEnableCullFace) {
		glEnable(GL_CULL_FACE);
	}
	else {
		glDisable(GL_CULL_FACE);
	}

	if (m_state.bEnableDepthTest) {
		glEnable(GL_DEPTH_TEST);
	}
	else {
		glDisable(GL_DEPTH_TEST);
	}

	if (m_state.bEnableDepthWrite) {
		glDepthMask(GL_TRUE);
	}
	else {
		glDepthMask(GL_FALSE);
	}

	if (m_state.bEnableBlend) {
		glEnable(GL_BLEND);
	}
	else {
		glDisable(GL_BLEND);
	}

	if (m_state.bEnablePolygonOffset) {
		glEnable(GL_POLYGON_OFFSET_FILL);
	}
	else {
		glDisable(GL_POLYGON_OFFSET_FILL);
	}

	glCullFace(GL_BACK);
	glFrontFace(m_state.frontFace);
	glDepthFunc(m_state.depthFunc);
	glBlendFunc(m_state.srcBlendFactor, m_state.dstBlendFactor);
	glPolygonOffset(m_state.polygonOffsetFactor, m_state.polygonOffsetUnits);
	glColorMask(m_state.bEnableColorWrite[0] ? GL_TRUE : GL_FALSE, m_state.bEnableColorWrite[1] ? GL_TRUE : GL_FALSE, m_state.bEnableColorWrite[2] ? GL_TRUE : GL_FALSE, m_state.bEnableColorWrite[3] ? GL_TRUE : GL_FALSE);
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
		if (pProgram->BindTexture2D(itTexture.first, itTexture.second->GetTexture(), m_pSamplers.find(itTexture.first)->second->GetSampler(), indexUnit)) {
			indexUnit++;
		}
	}

	for (const auto &itTexture : m_pTexture2dArrays) {
		if (pProgram->BindTextureArray(itTexture.first, itTexture.second->GetTexture(), m_pSamplers.find(itTexture.first)->second->GetSampler(), indexUnit)) {
			indexUnit++;
		}
	}

	for (const auto &itTexture : m_pTextureCubeMaps) {
		if (pProgram->BindTextureCubeMap(itTexture.first, itTexture.second->GetTexture(), m_pSamplers.find(itTexture.first)->second->GetSampler(), indexUnit)) {
			indexUnit++;
		}
	}
}

bool CGfxMaterial::Load(const char *szFileName)
{
	/*
	<Material>
		<Cull enable="" front_face="" />
		<Depth enable_test="" enable_write="" depth_func="" />
		<Color enable_write_red="" enable_write_green="" enable_write_blue="" enable_write_alpha="" />
		<Blend enable="" src_factor="" dst_factor="" />
		<Offset enable="" factor="" units="" />

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

	try {
		Free();

		LogOutput("LoadMaterial(%s)\n", szFileName);
		{
			char szFullPath[260];
			CGfxRenderer::GetInstance()->GetMaterialFullPath(szFileName, szFullPath);

			TiXmlDocument xmlDoc;
			if (xmlDoc.LoadFile(szFullPath) == false) throw 0;

			TiXmlNode *pMaterialNode = xmlDoc.FirstChild("Material");
			if (pMaterialNode == NULL) throw 1;

			if (LoadState(pMaterialNode) == false) throw 2;
			if (LoadProgram(pMaterialNode) == false) throw 3;
			if (LoadTexture2D(pMaterialNode) == false) throw 4;
			if (LoadTexture2DArray(pMaterialNode) == false) throw 5;
			if (LoadTextureCubeMap(pMaterialNode) == false) throw 6;
			if (LoadUniformVec1(pMaterialNode) == false) throw 7;
			if (LoadUniformVec2(pMaterialNode) == false) throw 8;
			if (LoadUniformVec3(pMaterialNode) == false) throw 9;
			if (LoadUniformVec4(pMaterialNode) == false) throw 10;
		}
		return true;
	}
	catch (int) {
		Free();
		return false;
	}
}

bool CGfxMaterial::LoadState(TiXmlNode *pMaterialNode)
{
	try {
		LogOutput("\tLoadState ... ");
		{
			if (TiXmlNode *pCullNode = pMaterialNode->FirstChild("Cull")) {
				m_state.bEnableCullFace = pCullNode->ToElement()->AttributeBool("enable");
				m_state.frontFace = StringToFrontFace(pCullNode->ToElement()->AttributeString("front_face"));
			}

			if (TiXmlNode *pDepthNode = pMaterialNode->FirstChild("Depth")) {
				m_state.bEnableDepthTest = pDepthNode->ToElement()->AttributeBool("enable_test");
				m_state.bEnableDepthWrite = pDepthNode->ToElement()->AttributeBool("enable_write");
				m_state.depthFunc = StringToDepthFunc(pDepthNode->ToElement()->AttributeString("depth_func"));
			}

			if (TiXmlNode *pColorNode = pMaterialNode->FirstChild("Color")) {
				m_state.bEnableColorWrite[0] = pColorNode->ToElement()->AttributeBool("enable_write_red");
				m_state.bEnableColorWrite[1] = pColorNode->ToElement()->AttributeBool("enable_write_green");
				m_state.bEnableColorWrite[2] = pColorNode->ToElement()->AttributeBool("enable_write_blue");
				m_state.bEnableColorWrite[3] = pColorNode->ToElement()->AttributeBool("enable_write_alpha");
			}

			if (TiXmlNode *pBlendNode = pMaterialNode->FirstChild("Blend")) {
				m_state.bEnableBlend = pBlendNode->ToElement()->AttributeBool("enable");
				m_state.srcBlendFactor = StringToBlendSrcFactor(pBlendNode->ToElement()->AttributeString("src_factor"));
				m_state.dstBlendFactor = StringToBlendDstFactor(pBlendNode->ToElement()->AttributeString("dst_factor"));
			}

			if (TiXmlNode *pOffsetNode = pMaterialNode->FirstChild("Offset")) {
				m_state.bEnablePolygonOffset = pOffsetNode->ToElement()->AttributeBool("enable");
				m_state.polygonOffsetFactor = pOffsetNode->ToElement()->AttributeFloat1("factor");
				m_state.polygonOffsetUnits = pOffsetNode->ToElement()->AttributeFloat1("units");
			}
		}
		LogOutput("OK\n");
		return true;
	}
	catch (int) {
		LogOutput("Fail\n");
		return false;
	}
}

bool CGfxMaterial::LoadProgram(TiXmlNode *pMaterialNode)
{
	try {
		LogOutput("\tLoadProgram ... ");
		{
			TiXmlNode *pProgramNode = pMaterialNode->FirstChild("Program");
			if (pProgramNode == NULL) throw 0;

			const char *szVertexFileName = pProgramNode->ToElement()->AttributeString("vertex_file_name");
			const char *szFragmentFileName = pProgramNode->ToElement()->AttributeString("fragment_file_name");
			if (szVertexFileName == NULL || szFragmentFileName == NULL) throw 1;

			m_pProgram = CGfxRenderer::GetInstance()->GetProgramManager()->LoadProgram(szVertexFileName, szFragmentFileName);
			if (m_pProgram->IsValid() == false) throw 2;
		}
		LogOutput("OK\n");
		return true;
	}
	catch (int err) {
		LogOutput("Fail(%d)\n", err);
		return false;
	}
}

bool CGfxMaterial::LoadTexture2D(TiXmlNode *pMaterialNode)
{
	try {
		TiXmlNode *pTextureNode = pMaterialNode->FirstChild("Texture2D");
		if (pTextureNode == NULL) return true;

		LogOutput("\tLoadTexture2D ... ");
		{
			do {
				const char *szFileName = pTextureNode->ToElement()->AttributeString("file_name");
				const char *szName = pTextureNode->ToElement()->AttributeString("name");
				if (szFileName == NULL || szName == NULL) throw 0;

				GLuint name = HashValue(szName);
				GLenum minFilter = StringToMinFilter(pTextureNode->ToElement()->AttributeString("min_filter"));
				GLenum magFilter = StringToMagFilter(pTextureNode->ToElement()->AttributeString("mag_filter"));
				GLenum addressMode = StringToAddressMode(pTextureNode->ToElement()->AttributeString("address_mode"));
				if (minFilter == GL_INVALID_ENUM || magFilter == GL_INVALID_ENUM || addressMode == GL_INVALID_ENUM) throw 1;

				if (m_pTexture2ds.find(name) != m_pTexture2ds.end()) {
					throw 2;
				}

				if (m_pProgram->IsTextureValid(name)) {
					m_pSamplers[name] = CGfxRenderer::GetInstance()->GetTextureManager()->CreateSampler(minFilter, magFilter, addressMode);
					m_pTexture2ds[name] = CGfxRenderer::GetInstance()->GetTextureManager()->LoadTexture2D(szFileName);
					if (m_pTexture2ds[name]->IsValid() == false) throw 3;
				}
			} while (pTextureNode = pMaterialNode->IterateChildren("Texture2D", pTextureNode));
		}
		LogOutput("OK\n");
		return true;
	}
	catch (int err) {
		LogOutput("Fail(%d)\n", err);
		return false;
	}
}

bool CGfxMaterial::LoadTexture2DArray(TiXmlNode *pMaterialNode)
{
	try {
		TiXmlNode *pTextureNode = pMaterialNode->FirstChild("Texture2DArray");
		if (pTextureNode == NULL) return true;

		LogOutput("\tLoadTexture2DArray ... ");
		{
			do {
				const char *szFileName = pTextureNode->ToElement()->AttributeString("file_name");
				const char *szName = pTextureNode->ToElement()->AttributeString("name");
				if (szFileName == NULL || szName == NULL) throw 0;

				GLuint name = HashValue(szName);
				GLenum minFilter = StringToMinFilter(pTextureNode->ToElement()->AttributeString("min_filter"));
				GLenum magFilter = StringToMagFilter(pTextureNode->ToElement()->AttributeString("mag_filter"));
				GLenum addressMode = StringToAddressMode(pTextureNode->ToElement()->AttributeString("address_mode"));
				if (minFilter == GL_INVALID_ENUM || magFilter == GL_INVALID_ENUM || addressMode == GL_INVALID_ENUM) throw 1;

				if (m_pTexture2dArrays.find(name) != m_pTexture2dArrays.end()) {
					throw 2;
				}

				if (m_pProgram->IsTextureValid(name)) {
					m_pSamplers[name] = CGfxRenderer::GetInstance()->GetTextureManager()->CreateSampler(minFilter, magFilter, addressMode);
					m_pTexture2dArrays[name] = CGfxRenderer::GetInstance()->GetTextureManager()->LoadTexture2DArray(szFileName);
					if (m_pTexture2dArrays[name]->IsValid() == false) throw 3;
				}
			} while (pTextureNode = pMaterialNode->IterateChildren("Texture2DArray", pTextureNode));
		}
		LogOutput("OK\n");
		return true;
	}
	catch (int err) {
		LogOutput("Fail(%d)\n", err);
		return false;
	}
}

bool CGfxMaterial::LoadTextureCubeMap(TiXmlNode *pMaterialNode)
{
	try {
		TiXmlNode *pTextureNode = pMaterialNode->FirstChild("TextureCubeMap");
		if (pTextureNode == NULL) return true;

		LogOutput("\tLoadTextureCubeMap ... ");
		{
			do {
				const char *szFileName = pTextureNode->ToElement()->AttributeString("file_name");
				const char *szName = pTextureNode->ToElement()->AttributeString("name");
				if (szFileName == NULL || szName == NULL) throw 0;

				GLuint name = HashValue(szName);
				GLenum minFilter = StringToMinFilter(pTextureNode->ToElement()->AttributeString("min_filter"));
				GLenum magFilter = StringToMagFilter(pTextureNode->ToElement()->AttributeString("mag_filter"));
				GLenum addressMode = StringToAddressMode(pTextureNode->ToElement()->AttributeString("address_mode"));
				if (minFilter == GL_INVALID_ENUM || magFilter == GL_INVALID_ENUM || addressMode == GL_INVALID_ENUM) throw 1;

				if (m_pTextureCubeMaps.find(name) != m_pTextureCubeMaps.end()) {
					throw 2;
				}

				if (m_pProgram->IsTextureValid(name)) {
					m_pSamplers[name] = CGfxRenderer::GetInstance()->GetTextureManager()->CreateSampler(minFilter, magFilter, addressMode);
					m_pTextureCubeMaps[name] = CGfxRenderer::GetInstance()->GetTextureManager()->LoadTextureCubeMap(szFileName);
					if (m_pTextureCubeMaps[name]->IsValid() == false) throw 3;
				}
			} while (pTextureNode = pMaterialNode->IterateChildren("TextureCubeMap", pTextureNode));
		}
		LogOutput("OK\n");
		return true;
	}
	catch (int err) {
		LogOutput("Fail(%d)\n", err);
		return false;
	}
}

bool CGfxMaterial::LoadUniformVec1(TiXmlNode *pMaterialNode)
{
	try {
		TiXmlNode *pUniformNode = pMaterialNode->FirstChild("Uniform1f");
		if (pUniformNode == NULL) return true;

		LogOutput("\tLoadUniformVec1 ... ");
		{
			do {
				const char *szName = pUniformNode->ToElement()->AttributeString("name");
				if (szName == NULL) throw 0;

				GLuint name = HashValue(szName);
				GLfloat value = pUniformNode->ToElement()->AttributeFloat1("value");

				if (m_pUniformVec1s.find(name) != m_pUniformVec1s.end()) {
					throw 1;
				}

				if (m_pProgram->IsUniformValid(name)) {
					if (m_pUniformVec1s[name] = new CGfxUniformVec1) {
						m_pUniformVec1s[name]->SetValue(value);
					}
				}
			} while (pUniformNode = pMaterialNode->IterateChildren("Uniform1f", pUniformNode));
		}
		LogOutput("OK\n");
		return true;
	}
	catch (int err) {
		LogOutput("Fail(%d)\n", err);
		return false;
	}
}

bool CGfxMaterial::LoadUniformVec2(TiXmlNode *pMaterialNode)
{
	try {
		TiXmlNode *pUniformNode = pMaterialNode->FirstChild("Uniform2f");
		if (pUniformNode == NULL) return true;

		LogOutput("\tLoadUniformVec2 ... ");
		{
			do {
				const char *szName = pUniformNode->ToElement()->AttributeString("name");
				if (szName == NULL) throw 0;

				GLuint name = HashValue(szName);
				GLfloat value[2]; pUniformNode->ToElement()->AttributeFloat2("value", value);

				if (m_pUniformVec2s.find(name) != m_pUniformVec2s.end()) {
					throw 1;
				}

				if (m_pProgram->IsUniformValid(name)) {
					if (m_pUniformVec2s[name] = new CGfxUniformVec2) {
						m_pUniformVec2s[name]->SetValue(value[0], value[1]);
					}
				}
			} while (pUniformNode = pMaterialNode->IterateChildren("Uniform2f", pUniformNode));
		}
		LogOutput("OK\n");
		return true;
	}
	catch (int err) {
		LogOutput("Fail(%d)\n", err);
		return false;
	}
}

bool CGfxMaterial::LoadUniformVec3(TiXmlNode *pMaterialNode)
{
	try {
		TiXmlNode *pUniformNode = pMaterialNode->FirstChild("Uniform3f");
		if (pUniformNode == NULL) return true;

		LogOutput("\tLoadUniformVec3 ... ");
		{
			do {
				const char *szName = pUniformNode->ToElement()->AttributeString("name");
				if (szName == NULL) throw 0;

				GLuint name = HashValue(szName);
				GLfloat value[3]; pUniformNode->ToElement()->AttributeFloat3("value", value);

				if (m_pUniformVec3s.find(name) != m_pUniformVec3s.end()) {
					throw 1;
				}

				if (m_pProgram->IsUniformValid(name)) {
					if (m_pUniformVec3s[name] = new CGfxUniformVec3) {
						m_pUniformVec3s[name]->SetValue(value[0], value[1], value[2]);
					}
				}
			} while (pUniformNode = pMaterialNode->IterateChildren("Uniform3f", pUniformNode));
		}
		LogOutput("OK\n");
		return true;
	}
	catch (int err) {
		LogOutput("Fail(%d)\n", err);
		return false;
	}
}

bool CGfxMaterial::LoadUniformVec4(TiXmlNode *pMaterialNode)
{
	try {
		TiXmlNode *pUniformNode = pMaterialNode->FirstChild("Uniform4f");
		if (pUniformNode == NULL) return true;

		LogOutput("\tLoadUniformVec4 ... ");
		{
			do {
				const char *szName = pUniformNode->ToElement()->AttributeString("name");
				if (szName == NULL) throw 0;

				GLuint name = HashValue(szName);
				GLfloat value[4]; pUniformNode->ToElement()->AttributeFloat4("value", value);

				if (m_pUniformVec4s.find(name) != m_pUniformVec4s.end()) {
					throw 1;
				}

				if (m_pProgram->IsUniformValid(name)) {
					if (m_pUniformVec4s[name] = new CGfxUniformVec4) {
						m_pUniformVec4s[name]->SetValue(value[0], value[1], value[2], value[3]);
					}
				}
			} while (pUniformNode = pMaterialNode->IterateChildren("Uniform4f", pUniformNode));
		}
		LogOutput("OK\n");
		return true;
	}
	catch (int err) {
		LogOutput("Fail(%d)\n", err);
		return false;
	}
}

void CGfxMaterial::Free(void)
{
	for (auto &itTexture : m_pTexture2ds) {
		CGfxRenderer::GetInstance()->GetTextureManager()->FreeTexture(itTexture.second);
	}

	for (auto &itTexture : m_pTexture2dArrays) {
		CGfxRenderer::GetInstance()->GetTextureManager()->FreeTexture(itTexture.second);
	}

	for (auto &itTexture : m_pTextureCubeMaps) {
		CGfxRenderer::GetInstance()->GetTextureManager()->FreeTexture(itTexture.second);
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
	m_pSamplers.clear();
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
	m_state.bEnableCullFace = bEnable;
	m_state.frontFace = frontFace;
}

void CGfxMaterial::SetEnableDepthTest(bool bEnable, GLenum depthFunc)
{
	m_state.bEnableDepthTest = bEnable;
	m_state.depthFunc = depthFunc;
}

void CGfxMaterial::SetEnableDepthWrite(bool bEnable)
{
	m_state.bEnableDepthWrite = bEnable;
}

void CGfxMaterial::SetEnableColorWrite(bool bEnableRed, bool bEnableGreen, bool bEnableBlue, bool bEnableAlpha)
{
	m_state.bEnableColorWrite[0] = bEnableRed;
	m_state.bEnableColorWrite[1] = bEnableGreen;
	m_state.bEnableColorWrite[2] = bEnableBlue;
	m_state.bEnableColorWrite[3] = bEnableAlpha;
}

void CGfxMaterial::SetEnableBlend(bool bEnable, GLenum srcFactor, GLenum dstFactor)
{
	m_state.bEnableBlend = bEnable;
	m_state.srcBlendFactor = srcFactor;
	m_state.dstBlendFactor = dstFactor;
}

void CGfxMaterial::SetEnablePolygonOffset(bool bEnable, GLfloat factor, GLfloat units)
{
	m_state.bEnablePolygonOffset = bEnable;
	m_state.polygonOffsetFactor = factor;
	m_state.polygonOffsetUnits = units;
}

bool CGfxMaterial::IsEnableBlend(void) const
{
	return m_state.bEnableBlend;
}

CGfxProgram* CGfxMaterial::GetProgram(void) const
{
	return m_pProgram;
}

CGfxSampler* CGfxMaterial::GetSampler(const char *szName, GLenum minFilter, GLenum magFilter, GLenum addressMode)
{
	GLuint name = HashValue(szName);

	if ((m_pProgram == NULL) || (m_pProgram && m_pProgram->IsTextureValid(name))) {
		if (m_pSamplers[name] == NULL) {
			m_pSamplers[name] = CGfxRenderer::GetInstance()->GetTextureManager()->CreateSampler(minFilter, magFilter, addressMode);
		}

		return m_pSamplers[name];
	}

	return NULL;
}

CGfxTexture2D* CGfxMaterial::GetTexture2D(const char *szName)
{
	GLuint name = HashValue(szName);

	if ((m_pProgram == NULL) || (m_pProgram && m_pProgram->IsTextureValid(name))) {
		if (m_pTexture2ds[name] == NULL) {
			m_pTexture2ds[name] = new CGfxTexture2D(HashValue(szName));
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
			m_pTexture2dArrays[name] = new CGfxTexture2DArray(HashValue(szName));
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
			m_pTextureCubeMaps[name] = new CGfxTextureCubeMap(HashValue(szName));
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
