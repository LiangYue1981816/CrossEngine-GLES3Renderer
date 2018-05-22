#include "stdio.h"
#include "stdlib.h"
#include "Program.h"
#include "Renderer.h"


uint32_t HashValue(const char *szString)
{
	const char *c = szString;
	uint32_t dwHashValue = 0x00000000;

	while (*c) {
		dwHashValue = (dwHashValue << 5) - dwHashValue + (*c == '/' ? '\\' : *c);
		c++;
	}

	return dwHashValue ? dwHashValue : 0xffffffff;
}

static size_t fsize(FILE *stream)
{
	long pos;
	size_t size;

	pos = ftell(stream);
	{
		fseek(stream, 0, SEEK_END);
		size = ftell(stream);
	}
	fseek(stream, pos, SEEK_SET);

	return size;
}

static std::string LoadShader(const char *szFileName)
{
	if (FILE *pFile = fopen(szFileName, "rb")) {
		static char szSource[128 * 1024];
		size_t size = fsize(pFile);

		fread(szSource, 1, size, pFile);
		fclose(pFile);

		return szSource;
	}

	return "";
}

static std::vector<GLuint> LoadShaderBinary(const char *szFileName)
{
	std::vector<GLuint> words;

	if (FILE *pFile = fopen(szFileName, "rb")) {
		size_t size = fsize(pFile);
		words.resize(size / sizeof(GLuint));
		fread(words.data(), sizeof(GLuint), words.size(), pFile);
		fclose(pFile);
	}

	return words;
}


CProgram::CProgram(void)
	: m_program(0)
	, m_vertexShader(0)
	, m_fragmentShader(0)
	, m_pShaderCompilers{ NULL }
{

}

CProgram::~CProgram(void)
{
	Destroy();
}

bool CProgram::Create(const char *szVertexFileName, const char *szFragmentFileName)
{
	try {
		printf("\t\tCreate ... \n");
		{
			int err = 0;
			if (CreateShader(szVertexFileName, GL_VERTEX_SHADER, m_vertexShader, m_pShaderCompilers[0]) == false) throw err++;
			if (CreateShader(szFragmentFileName, GL_FRAGMENT_SHADER, m_fragmentShader, m_pShaderCompilers[1]) == false) throw err++;
			if (CreateProgram() == false) throw err++;
			if (CreateLocations() == false) throw err++;
		}
		printf("\t\tOK\n");
		return true;
	}
	catch (int err) {
		Destroy();

		printf("\t\tFail(%d)\n", err);
		return false;
	}
}

bool CProgram::CreateShader(const char *szFileName, GLenum type, GLuint &shader, spirv_cross::CompilerGLSL *&pShaderCompiler)
{
	shader = 0;
	pShaderCompiler = NULL;

	try {
		printf("\t\t\tCreateShader(%s) ... ", szFileName);
		{
			char szFullPath[260];
			CRenderer::GetInstance()->GetShaderFullPath(szFileName, szFullPath);

			std::vector<GLuint> words = LoadShaderBinary(szFullPath);
			pShaderCompiler = new spirv_cross::CompilerGLSL(words.data(), words.size());

			spirv_cross::CompilerGLSL::Options options;
			options.version = 300;
			options.es = true;
			pShaderCompiler->set_options(options);

			const std::string strSource = pShaderCompiler->compile();
			const char *szSource[1] = { strSource.c_str() };

			shader = glCreateShader(type);
			glShaderSource(shader, 1, szSource, NULL);
			glCompileShader(shader);

			GLint success;
			glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
			if (success == GL_FALSE) throw success;
		}
		printf("OK\n");
		return true;
	}
	catch (int) {
		static char szLog[64 * 1024];
		glGetShaderInfoLog(shader, sizeof(szLog), NULL, szLog);
		glDeleteShader(shader);
		shader = 0;

		if (pShaderCompiler) {
			delete pShaderCompiler;
			pShaderCompiler = NULL;
		}

		printf("\n");
		printf("\t\t\tCompile Error: %s\n", szLog);
		return false;
	}
}

bool CProgram::CreateProgram(void)
{
	try {
		printf("\t\t\tCreateProgram() ... ");
		{
			m_program = glCreateProgram();
			glAttachShader(m_program, m_vertexShader);
			glAttachShader(m_program, m_fragmentShader);
			glLinkProgram(m_program);

			GLint success;
			glGetProgramiv(m_program, GL_LINK_STATUS, &success);
			if (success == GL_FALSE) throw success;
		}
		printf("OK\n");
		return true;
	}
	catch (int) {
		static char szLog[64 * 1024];
		glGetProgramInfoLog(m_program, sizeof(szLog), NULL, szLog);
		glDeleteProgram(m_program);
		m_program = 0;

		printf("\n");
		printf("\t\t\tLink Error: %s\n", szLog);
		return false;
	}
}

bool CProgram::CreateLocations(void)
{
	for (int index = 0; index < 2; index++) {
		const spirv_cross::ShaderResources shaderResources = m_pShaderCompilers[index]->get_shader_resources();

		for (const auto &itUniform : shaderResources.uniform_buffers) {
			if (m_pShaderCompilers[index]->get_type(itUniform.type_id).basetype == spirv_cross::SPIRType::Struct) {
				SetUniformLocation(itUniform.name.c_str());
			}
		}

		for (const auto &itSampledImage : shaderResources.sampled_images) {
			if (m_pShaderCompilers[index]->get_type(itSampledImage.type_id).basetype == spirv_cross::SPIRType::SampledImage) {
				SetTextureLocation(itSampledImage.name.c_str());
			}
		}
	}

	return true;
}

void CProgram::Destroy(void)
{
	if (m_program) {
		glDeleteProgram(m_program);
	}

	if (m_vertexShader) {
		glDeleteShader(m_vertexShader);
	}

	if (m_fragmentShader) {
		glDeleteShader(m_fragmentShader);
	}

	if (m_pShaderCompilers[0]) {
		delete m_pShaderCompilers[0];
	}

	if (m_pShaderCompilers[1]) {
		delete m_pShaderCompilers[1];
	}

	m_program = 0;
	m_vertexShader = 0;
	m_fragmentShader = 0;
	m_pShaderCompilers[0] = NULL;
	m_pShaderCompilers[1] = NULL;
}

bool CProgram::SetUniformLocation(const char *szName)
{
	GLuint name = HashValue(szName);

	if (m_uniformBlockLocations.find(name) == m_uniformBlockLocations.end()) {
		GLuint location = glGetUniformBlockIndex(m_program, szName);

		if (location != GL_INVALID_INDEX) {
			m_uniformBlockLocations[name] = location;
			glUniformBlockBinding(m_program, location, location);
			return true;
		}
	}

	return false;
}

bool CProgram::SetTextureLocation(const char *szName)
{
	GLuint name = HashValue(szName);

	if (m_sampledImageLocations.find(name) == m_sampledImageLocations.end()) {
		GLuint location = glGetUniformLocation(m_program, szName);

		if (location != GL_INVALID_INDEX) {
			m_sampledImageLocations[name] = location;
			return true;
		}
	}

	return false;
}

void CProgram::UseProgram(void) const
{
	glUseProgram(m_program);
}

bool CProgram::BindUniformBuffer(GLuint name, GLuint buffer, GLsizeiptr size, GLintptr offset) const
{
	const auto &itLocation = m_uniformBlockLocations.find(name);

	if (itLocation != m_uniformBlockLocations.end()) {
		glBindBufferRange(GL_UNIFORM_BUFFER, itLocation->second, buffer, offset, size);
		return true;
	}

	return false;
}

bool CProgram::BindTexture2D(GLuint name, GLuint texture, GLuint sampler, GLuint unit) const
{
	const auto &itLocation = m_sampledImageLocations.find(name);

	if (itLocation != m_sampledImageLocations.end()) {
		glActiveTexture(GL_TEXTURE0 + unit);
		glBindSampler(unit, sampler);
		glBindTexture(GL_TEXTURE_2D, texture);
		glUniform1i(itLocation->second, unit);
		return true;
	}

	return false;
}

bool CProgram::BindTextureArray(GLuint name, GLuint texture, GLuint sampler, GLuint unit) const
{
	const auto &itLocation = m_sampledImageLocations.find(name);

	if (itLocation != m_sampledImageLocations.end()) {
		glActiveTexture(GL_TEXTURE0 + unit);
		glBindSampler(unit, sampler);
		glBindTexture(GL_TEXTURE_2D_ARRAY, texture);
		glUniform1i(itLocation->second, unit);
		return true;
	}

	return false;
}

bool CProgram::BindTextureCubeMap(GLuint name, GLuint texture, GLuint sampler, GLuint unit) const
{
	const auto &itLocation = m_sampledImageLocations.find(name);

	if (itLocation != m_sampledImageLocations.end()) {
		glActiveTexture(GL_TEXTURE0 + unit);
		glBindSampler(unit, sampler);
		glBindTexture(GL_TEXTURE_CUBE_MAP, texture);
		glUniform1i(itLocation->second, unit);
		return true;
	}

	return false;
}

bool CProgram::IsUniformValid(GLuint name) const
{
	return m_uniformBlockLocations.find(name) != m_uniformBlockLocations.end();
}

bool CProgram::IsTextureValid(GLuint name) const
{
	return m_sampledImageLocations.find(name) != m_sampledImageLocations.end();
}
