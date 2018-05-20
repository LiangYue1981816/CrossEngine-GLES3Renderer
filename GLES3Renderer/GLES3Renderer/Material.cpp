#include "stdio.h"
#include "stdlib.h"
#include "Material.h"
#include "Renderer.h"


static GLenum StringToMinFilter(const char *szString)
{
	if (!stricmp(szString, "GL_LINEAR")) return GL_LINEAR;
	if (!stricmp(szString, "GL_LINEAR_MIPMAP_LINEAR")) return GL_LINEAR_MIPMAP_LINEAR;
	if (!stricmp(szString, "GL_LINEAR_MIPMAP_NEAREST")) return GL_LINEAR_MIPMAP_NEAREST;
	if (!stricmp(szString, "GL_NEAREST")) return GL_NEAREST;
	if (!stricmp(szString, "GL_NEAREST_MIPMAP_LINEAR")) return GL_NEAREST_MIPMAP_LINEAR;
	if (!stricmp(szString, "GL_NEAREST_MIPMAP_NEAREST")) return GL_NEAREST_MIPMAP_NEAREST;
	
	return GL_INVALID_ENUM;
}

static GLenum StringToMagFilter(const char *szString)
{
	if (!stricmp(szString, "GL_LINEAR")) return GL_LINEAR;
	if (!stricmp(szString, "GL_NEAREST")) return GL_NEAREST;

	return GL_INVALID_ENUM;
}

static GLenum StringToAddressMode(const char *szString)
{
	if (!stricmp(szString, "GL_REPEAT")) return GL_REPEAT;
	if (!stricmp(szString, "GL_CLAMP_TO_EDGE")) return GL_CLAMP_TO_EDGE;

	return GL_INVALID_ENUM;
}

static GLenum StringToBlendFactor(const char *szString)
{
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

	return GL_INVALID_ENUM;
}


CMaterial::CMaterial(void)
	: m_pProgram(NULL)
	, m_pUniformCamera(NULL)
	, m_pUniformAmbientLight(NULL)
	, m_pUniformPointLight(NULL)
	, m_pUniformDirectionLight(NULL)

	, m_bEnableCullFace(true)
	, m_bEnableDepthTest(true)
	, m_bEnableDepthWrite(true)
	, m_bEnableBlend(false)
	, m_srcBlendFactor(GL_SRC_ALPHA)
	, m_dstBlendFactor(GL_ONE_MINUS_SRC_ALPHA)
	, m_bEnablePolygonOffset(false)
	, m_polygonOffsetFactor(0.0f)
	, m_polygonOffsetUnits(0.0f)

	, m_inUseTexUnits(0)
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
	GLuint texUnits = 0;

	for (const auto &itTexture : m_pTexture2ds) {
		if (m_pProgram->BindTexture2D(itTexture.first, itTexture.second->GetTexture(), itTexture.second->GetSampler(), texUnits)) {
			texUnits++;
		}
	}

	for (const auto &itTexture : m_pTexture2dArrays) {
		if (m_pProgram->BindTextureArray(itTexture.first, itTexture.second->GetTexture(), itTexture.second->GetSampler(), texUnits)) {
			texUnits++;
		}
	}

	for (const auto &itTexture : m_pTextureCubeMaps) {
		if (m_pProgram->BindTextureCubeMap(itTexture.first, itTexture.second->GetTexture(), itTexture.second->GetSampler(), texUnits)) {
			texUnits++;
		}
	}
}

void CMaterial::BindUniforms(void) const
{
	for (const auto &itUniform : m_pUniform1fs) {
		m_pProgram->BindUniformBuffer(itUniform.first, itUniform.second->GetBuffer(), itUniform.second->GetSize());
	}

	for (const auto &itUniform : m_pUniform2fs) {
		m_pProgram->BindUniformBuffer(itUniform.first, itUniform.second->GetBuffer(), itUniform.second->GetSize());
	}

	for (const auto &itUniform : m_pUniform3fs) {
		m_pProgram->BindUniformBuffer(itUniform.first, itUniform.second->GetBuffer(), itUniform.second->GetSize());
	}

	for (const auto &itUniform : m_pUniform4fs) {
		m_pProgram->BindUniformBuffer(itUniform.first, itUniform.second->GetBuffer(), itUniform.second->GetSize());
	}

	m_pProgram->BindUniformBuffer(HashValue(ENGINE_CAMERA_NAME), m_pUniformCamera->GetBuffer(), m_pUniformCamera->GetSize());
	m_pProgram->BindUniformBuffer(HashValue(ENGINE_AMBIENT_LIGHT_NAME), m_pUniformAmbientLight->GetBuffer(), m_pUniformAmbientLight->GetSize());
	m_pProgram->BindUniformBuffer(HashValue(ENGINE_POINT_LIGHT_NAME), m_pUniformPointLight->GetBuffer(), m_pUniformPointLight->GetSize());
	m_pProgram->BindUniformBuffer(HashValue(ENGINE_DIRECTION_LIGHT_NAME), m_pUniformDirectionLight->GetBuffer(), m_pUniformDirectionLight->GetSize());
}

bool CMaterial::Create(const char *szFileName, CUniformBufferCamera *pUniformCamera, CUniformBufferAmbientLight *pUniformAmbientLight, CUniformBufferPointLight *pUniformPointLight, CUniformBufferDirectionLight *pUniformDirectionLight)
{
	try {
		printf("LoadMaterial(%s)\n", szFileName);
		{
			if (Load(szFileName) == false) {
				throw 0;
			}

			m_pUniformCamera = pUniformCamera;
			m_pUniformAmbientLight = pUniformAmbientLight;
			m_pUniformPointLight = pUniformPointLight;
			m_pUniformDirectionLight = pUniformDirectionLight;
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
	<Material id="" opaque="">
		<Cull enable="" />
		<Depth enable_test="" enable_write="" />
		<Blend enable="" src_factor="" dst_factor="" />
		<Offset factor="" units="" />

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

	m_inUseTexUnits = 0;

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
			if (LoadUniform1f(pMaterialNode) == false) return false;
			if (LoadUniform2f(pMaterialNode) == false) return false;
			if (LoadUniform3f(pMaterialNode) == false) return false;
			if (LoadUniform4f(pMaterialNode) == false) return false;
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
			m_id = pMaterialNode->ToElement()->AttributeInt1("id");

			if (TiXmlNode *pCullNode = pMaterialNode->FirstChild("Cull")) {
				m_bEnableCullFace = pCullNode->ToElement()->AttributeBool("enable");
			}

			if (TiXmlNode *pDepthNode = pMaterialNode->FirstChild("Depth")) {
				m_bEnableDepthTest = pDepthNode->ToElement()->AttributeBool("enable_test");
				m_bEnableDepthWrite = pDepthNode->ToElement()->AttributeBool("enable_write");
			}

			if (TiXmlNode *pBlendNode = pMaterialNode->FirstChild("Blend")) {
				m_bEnableBlend = pBlendNode->ToElement()->AttributeBool("enable");
				m_srcBlendFactor = StringToBlendFactor(pBlendNode->ToElement()->AttributeString("src_factor"));
				m_dstBlendFactor = StringToBlendFactor(pBlendNode->ToElement()->AttributeString("dst_factor"));
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

				if (m_pTexture2ds[name] = new CTexture2D) {
					if (m_pTexture2ds[name]->Create(szFileName, minFilter, magFilter, addressMode) == false) {
						throw err++;
					}

					if (m_pProgram->IsTextureValid(name)) {
						m_inUseTexUnits++;
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

				if (m_pTexture2dArrays[name] = new CTexture2DArray) {
					if (m_pTexture2dArrays[name]->Create(szFileName, minFilter, magFilter, addressMode) == false) {
						throw err++;
					}

					if (m_pProgram->IsTextureValid(name)) {
						m_inUseTexUnits++;
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

				if (m_pTextureCubeMaps[name] = new CTextureCubeMap) {
					if (m_pTextureCubeMaps[name]->Create(szFileName, minFilter, magFilter, addressMode) == false) {
						throw err++;
					}

					if (m_pProgram->IsTextureValid(name)) {
						m_inUseTexUnits++;
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

bool CMaterial::LoadUniform1f(TiXmlNode *pMaterialNode)
{
	try {
		TiXmlNode *pUniformNode = pMaterialNode->FirstChild("Uniform1f");
		if (pUniformNode == NULL) return true;

		printf("\tLoadUniform1f ... ");
		{
			do {
				int err = 0;

				const char *szName = pUniformNode->ToElement()->AttributeString("name");
				if (szName == NULL) throw err++;

				GLuint name = HashValue(szName);
				GLfloat value = pUniformNode->ToElement()->AttributeFloat1("value");

				if (m_pUniform1fs.find(name) != m_pUniform1fs.end()) {
					throw err++;
				}

				if (m_pUniform1fs[name] = new CUniformBufferVec1) {
					m_pUniform1fs[name]->SetValue(value);
					m_pUniform1fs[name]->Apply();
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

bool CMaterial::LoadUniform2f(TiXmlNode *pMaterialNode)
{
	try {
		TiXmlNode *pUniformNode = pMaterialNode->FirstChild("Uniform2f");
		if (pUniformNode == NULL) return true;

		printf("\tLoadUniform2f ... ");
		{
			do {
				int err = 0;

				const char *szName = pUniformNode->ToElement()->AttributeString("name");
				if (szName == NULL) throw err++;

				GLuint name = HashValue(szName);
				GLfloat value[2]; pUniformNode->ToElement()->AttributeFloat2("value", value);

				if (m_pUniform2fs.find(name) != m_pUniform2fs.end()) {
					throw err++;
				}

				if (m_pUniform2fs[name] = new CUniformBufferVec2) {
					m_pUniform2fs[name]->SetValue(value[0], value[1]);
					m_pUniform2fs[name]->Apply();
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

bool CMaterial::LoadUniform3f(TiXmlNode *pMaterialNode)
{
	try {
		TiXmlNode *pUniformNode = pMaterialNode->FirstChild("Uniform3f");
		if (pUniformNode == NULL) return true;

		printf("\tLoadUniform3f ... ");
		{
			do {
				int err = 0;

				const char *szName = pUniformNode->ToElement()->AttributeString("name");
				if (szName == NULL) throw err++;

				GLuint name = HashValue(szName);
				GLfloat value[3]; pUniformNode->ToElement()->AttributeFloat3("value", value);

				if (m_pUniform3fs.find(name) != m_pUniform3fs.end()) {
					throw err++;
				}

				if (m_pUniform3fs[name] = new CUniformBufferVec3) {
					m_pUniform3fs[name]->SetValue(value[0], value[1], value[2]);
					m_pUniform3fs[name]->Apply();
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

bool CMaterial::LoadUniform4f(TiXmlNode *pMaterialNode)
{
	try {
		TiXmlNode *pUniformNode = pMaterialNode->FirstChild("Uniform4f");
		if (pUniformNode == NULL) return true;

		printf("\tLoadUniform4f ... ");
		{
			do {
				int err = 0;

				const char *szName = pUniformNode->ToElement()->AttributeString("name");
				if (szName == NULL) throw err++;

				GLuint name = HashValue(szName);
				GLfloat value[4]; pUniformNode->ToElement()->AttributeFloat4("value", value);

				if (m_pUniform4fs.find(name) != m_pUniform4fs.end()) {
					throw err++;
				}

				if (m_pUniform4fs[name] = new CUniformBufferVec4) {
					m_pUniform4fs[name]->SetValue(value[0], value[1], value[2], value[3]);
					m_pUniform4fs[name]->Apply();
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

	for (auto &itUniform : m_pUniform1fs) {
		delete itUniform.second;
	}

	for (auto &itUniform : m_pUniform2fs) {
		delete itUniform.second;
	}

	for (auto &itUniform : m_pUniform3fs) {
		delete itUniform.second;
	}

	for (auto &itUniform : m_pUniform4fs) {
		delete itUniform.second;
	}

	m_pProgram = NULL;
	m_pTexture2ds.clear();
	m_pTexture2dArrays.clear();
	m_pTextureCubeMaps.clear();
	m_pUniform1fs.clear();
	m_pUniform2fs.clear();
	m_pUniform3fs.clear();
	m_pUniform4fs.clear();
}

CProgram* CMaterial::GetProgram(void) const
{
	return m_pProgram;
}

GLuint CMaterial::GetID(void) const
{
	return m_id;
}

GLuint CMaterial::GetInUseTextureUnits(void) const
{
	return m_inUseTexUnits;
}
