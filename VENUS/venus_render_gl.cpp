#include "venus.h"
#include "venus_render_gl.h"
#include <gl/gl.h>

#if GAIA_OS == GAIA_OS_WINDOWS
#	pragma comment(lib, "opengl32.lib")
#endif

namespace VENUS
{
#if GAIA_OS == GAIA_OS_WINDOWS
	#define GL_INVALID 0
	#define GL_ARRAY_BUFFER 0x8892
	#define GL_ELEMENT_ARRAY_BUFFER 0x8893
	#define GL_STATIC_DRAW 0x88E4
	#define GL_SHADER_COMPILER 0x8DFA
	#define GL_NUM_SHADER_BINARY_FORMATS 0x8DF9
	#define GL_SHADER_BINARY_FORMATS 0x8DF8
	#define GL_FRAGMENT_SHADER 0x8B30
	#define GL_VERTEX_SHADER 0x8B31
	#define GL_COMPILE_STATUS 0x8B81
	#define GL_MAX_VERTEX_ATTRIBS 0x8869
	#define GL_MAX_VERTEX_UNIFORM_VECTORS 0x8DFB
	#define GL_MAX_VARYING_VECTORS 0x8DFC
	#define GL_MAX_VERTEX_TEXTURE_IMAGE_UNITS 0x8B4C
	#define GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS 0x8B4D
	#define GL_MAX_FRAGMENT_UNIFORM_VECTORS 0x8DFD
	#define GL_MAX_TEXTURE_IMAGE_UNITS 0x8872
	#define GL_LINK_STATUS 0x8B82
	#define GL_ACTIVE_ATTRIBUTES 0x8B89
	#define GL_ACTIVE_UNIFORMS 0x8B86
	#define GL_ACTIVE_ATTRIBUTE_MAX_LENGTH 0x8B8A
	#define GL_ACTIVE_UNIFORM_MAX_LENGTH 0x8B87
	#define GL_FLOAT 0x1406
	#define GL_FLOAT_VEC2 0x8B50
	#define GL_FLOAT_VEC3 0x8B51
	#define GL_FLOAT_VEC4 0x8B52
	#define GL_FLOAT_MAT2 0x8B5A
	#define GL_FLOAT_MAT3 0x8B5B
	#define GL_FLOAT_MAT4 0x8B5C
	#define GL_TEXTURE_CUBE_MAP 0x8513
	#define GL_TEXTURE_CUBE_MAP_POSITIVE_X 0x8515
	#define GL_TEXTURE_CUBE_MAP_NEGATIVE_X 0x8516
	#define GL_TEXTURE_CUBE_MAP_POSITIVE_Y 0x8517
	#define GL_TEXTURE_CUBE_MAP_NEGATIVE_Y 0x8518
	#define GL_TEXTURE_CUBE_MAP_POSITIVE_Z 0x8519
	#define GL_TEXTURE_CUBE_MAP_NEGATIVE_Z 0x851A
	#define GL_CLAMP_TO_EDGE 0x812F
	#define GL_MIRRORED_REPEAT 0x8370
	#define GL_BLEND_SRC_ALPHA 0x80CB
	#define GL_BLEND_DST_ALPHA 0x80CA
	#define GL_FUNC_ADD 0x8006
	#define GL_FUNC_SUBTRACT 0x800A
	#define GL_FUNC_REVERSE_SUBTRACT 0x800B
	#define GL_BLEND_EQUATION_ALPHA 0x883D

	typedef void (GAIA_BASEAPI* GLGENBUFFERS)(GLsizei n, GLuint *buffers);
	typedef void (GAIA_BASEAPI* GLDELETEBUFFERS)(GLsizei n, const GLuint *buffers);
	typedef void (GAIA_BASEAPI* GLBINDBUFFER)(GLenum target, GLuint buffer);
	typedef void (GAIA_BASEAPI* GLBUFFERDATA)(GLenum target, GAIA::NM size, const void *data, GLenum usage);

	typedef void (GAIA_BASEAPI* GLACTIVETEXTURE)(GLenum texture);

	typedef GLuint (GAIA_BASEAPI* GLCREATESHADER)(GLenum type);
	typedef void (GAIA_BASEAPI* GLDELETESHADER)(GLuint shader);
	typedef void (GAIA_BASEAPI* GLSHADERSOURCE)(GLuint shader, GLsizei count, const GAIA::CH *const*string, const GLint *length);
	typedef void (GAIA_BASEAPI* GLSHADERBINARY)(GLsizei count, const GLuint *shaders, GLenum binaryformat, const void *binary, GLsizei length);
	typedef void (GAIA_BASEAPI* GLCOMPILESHADER)(GLuint shader);
	typedef void (GAIA_BASEAPI* GLGETSHADERIV)(GLuint shader, GLenum pname, GLint *params);
	typedef void (GAIA_BASEAPI* GLGETSHADERINFOLOG)(GLuint shader, GLsizei bufSize, GLsizei *length, GAIA::CH *infoLog);
	typedef void (GAIA_BASEAPI* GLRELEASESHADERCOMPILER)(void);

	typedef GLuint (GAIA_BASEAPI* GLCREATEPROGRAM)(void);
	typedef void (GAIA_BASEAPI* GLDELETEPROGRAM)(GLuint program);
	typedef void (GAIA_BASEAPI* GLATTACHSHADER)(GLuint program, GLuint shader);
	typedef void (GAIA_BASEAPI* GLDETACHSHADER)(GLuint program, GLuint shader);
	typedef void (GAIA_BASEAPI* GLLINKPROGRAM)(GLuint program);
	typedef void (GAIA_BASEAPI* GLGETPROGRAMIV)(GLuint program, GLenum pname, GLint *params);
	typedef void (GAIA_BASEAPI* GLGETPROGRAMINFOLOG)(GLuint program, GLsizei bufSize, GLsizei *length, GAIA::CH *infoLog);
	typedef void (GAIA_BASEAPI* GLUSEPROGRAM)(GLuint program);

	typedef void (GAIA_BASEAPI* GLENABLEVERTEXATTRIBARRAY)(GLuint index);
	typedef void (GAIA_BASEAPI* GLDISABLEVERTEXATTRIBARRAY)(GLuint index);
	typedef GLint (GAIA_BASEAPI* GLGETATTRIBLOCATION)(GLuint program, const GAIA::CH *name);
	typedef void (GAIA_BASEAPI* GLGETACTIVEATTRIB)(GLuint program, GLuint index, GLsizei bufSize, GLsizei *length, GLint *size, GLenum *type, GAIA::CH *name);
	typedef GLint (GAIA_BASEAPI* GLGETUNIFORMLOCATION)(GLuint program, const GAIA::CH *name);
	typedef void (GAIA_BASEAPI* GLGETACTIVEUNIFORM)(GLuint program, GLuint index, GLsizei bufSize, GLsizei *length, GLint *size, GLenum *type, GAIA::CH *name);

	typedef void (GAIA_BASEAPI* GLVERTEXATTRIBPOINTER)(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void *pointer);

	typedef void (GAIA_BASEAPI* GLUNIFORM1FV)(GLint location, GLsizei count, const GLfloat *value);
	typedef void (GAIA_BASEAPI* GLUNIFORM2FV)(GLint location, GLsizei count, const GLfloat *value);
	typedef void (GAIA_BASEAPI* GLUNIFORM3FV)(GLint location, GLsizei count, const GLfloat *value);
	typedef void (GAIA_BASEAPI* GLUNIFORM4FV)(GLint location, GLsizei count, const GLfloat *value);
	typedef void (GAIA_BASEAPI* GLUNIFORMMATRIX2FV)(GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
	typedef void (GAIA_BASEAPI* GLUNIFORMMATRIX3FV)(GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
	typedef void (GAIA_BASEAPI* GLUNIFORMMATRIX4FV)(GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);

	typedef void (GAIA_BASEAPI* GLGETUNIFORMFV)(GLuint program, GLint location, GLfloat *params);
	typedef void (GAIA_BASEAPI* GLUNIFORM1I)(GLint location, GLint v0);

	typedef void (GAIA_BASEAPI* GLBLENDEQUATION)(GLenum mode);

	static GLGENBUFFERS glGenBuffers = GNIL;
	static GLDELETEBUFFERS glDeleteBuffers = GNIL;
	static GLBINDBUFFER glBindBuffer = GNIL;
	static GLBUFFERDATA glBufferData = GNIL;

	static GLACTIVETEXTURE glActiveTexture = GNIL;

	static GLCREATESHADER glCreateShader = GNIL;
	static GLDELETESHADER glDeleteShader = GNIL;
	static GLSHADERSOURCE glShaderSource = GNIL;
	static GLSHADERBINARY glShaderBinary = GNIL;
	static GLCOMPILESHADER glCompileShader = GNIL;
	static GLGETSHADERIV glGetShaderiv = GNIL;
	static GLGETSHADERINFOLOG glGetShaderInfoLog = GNIL;
	static GLRELEASESHADERCOMPILER glReleaseShaderCompiler = GNIL;

	static GLCREATEPROGRAM glCreateProgram = GNIL;
	static GLDELETEPROGRAM glDeleteProgram = GNIL;
	static GLATTACHSHADER glAttachShader = GNIL;
	static GLDETACHSHADER glDetachShader = GNIL;
	static GLLINKPROGRAM glLinkProgram = GNIL;
	static GLGETPROGRAMIV glGetProgramiv = GNIL;
	static GLGETPROGRAMINFOLOG glGetProgramInfoLog = GNIL;
	static GLUSEPROGRAM glUseProgram = GNIL;

	static GLENABLEVERTEXATTRIBARRAY glEnableVertexAttribArray = GNIL;
	static GLDISABLEVERTEXATTRIBARRAY glDisableVertexAttribArray = GNIL;
	static GLGETATTRIBLOCATION glGetAttribLocation = GNIL;
	static GLGETACTIVEATTRIB glGetActiveAttrib = GNIL;
	static GLGETUNIFORMLOCATION glGetUniformLocation = GNIL;
	static GLGETACTIVEUNIFORM glGetActiveUniform = GNIL;

	static GLVERTEXATTRIBPOINTER glVertexAttribPointer = GNIL;

	static GLUNIFORM1FV glUniform1fv = GNIL;
	static GLUNIFORM2FV glUniform2fv = GNIL;
	static GLUNIFORM3FV glUniform3fv = GNIL;
	static GLUNIFORM4FV glUniform4fv = GNIL;
	static GLUNIFORMMATRIX2FV glUniformMatrix2fv = GNIL;
	static GLUNIFORMMATRIX3FV glUniformMatrix3fv = GNIL;
	static GLUNIFORMMATRIX4FV glUniformMatrix4fv = GNIL;

	static GLGETUNIFORMFV glGetUniformfv = GNIL;
	static GLUNIFORM1I glUniform1i = GNIL;

	static GLBLENDEQUATION glBlendEquation = GNIL;
#endif
	RenderGL::Context::Context()
	{
		this->init();
	}
	RenderGL::Context::~Context()
	{
		GAIA_RELEASE_SAFE(pIB);
		for(GAIA::CTN::Set<VertexBufferRec>::it it = vbset.front_it(); !it.empty(); ++it)
		{
			VertexBufferRec& vbr = *it;
			GAIA_RELEASE_SAFE(vbr.pVB);
		}
		vbset.destroy();
		GAIA_RELEASE_SAFE(pProgram);
		for(GAIA::CTN::Set<TextureRec>::it it = texset.front_it(); !it.empty(); ++it)
		{
			TextureRec& tr = *it;
			GAIA_RELEASE_SAFE(tr.pTex);
		}
		for(GAIA::SIZE x = 0; x < sizeofarray(pTarget); ++x)
			GAIA_RELEASE_SAFE(pTarget[x]);
		GAIA_RELEASE_SAFE(pDepther);
		this->init();
	}
	GAIA::GVOID RenderGL::Context::init()
	{
		eletype = VENUS::Render::ELEMENT_TYPE_TRIANGLELIST;
		pIB = GNIL;
		pProgram = GNIL;
		GAIA::ALGO::nil(pTarget, sizeofarray(pTarget));
		pDepther = GNIL;

		glGetIntegerv(GL_BLEND_SRC_ALPHA, &nSrcBlend);
		glGetIntegerv(GL_BLEND_DST_ALPHA, &nDstBlend);
	}
	RenderGL::IndexBuffer::IndexBuffer()
	{
		m_desc.reset();
		m_uIB = GL_INVALID;
	}
	RenderGL::IndexBuffer::~IndexBuffer()
	{
		if(this->IsCreated())
			this->Destroy();
	}
	GAIA::BL RenderGL::IndexBuffer::SaveToFile(GAIA::FSYS::FileBase* pFile) const
	{
		GPCHR_NULL_RET(pFile, GAIA::False);
		return GAIA::True;
	}
	const VENUS::Render::IndexBuffer::Desc& RenderGL::IndexBuffer::GetDesc() const
	{
		return m_desc;
	}
	GAIA::BL RenderGL::IndexBuffer::Commit(VENUS::Render::COMMIT_METHOD cm, GAIA::SIZE sOffsetInBytes, GAIA::SIZE sSize, const GAIA::GVOID* p)
	{
		GPCHR_NULL_RET(p, GAIA::False);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_uIB);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sSize, p, GL_STATIC_DRAW);
		return GAIA::True;
	}
	GAIA::BL RenderGL::IndexBuffer::Create(VENUS::RenderGL& r, const VENUS::Render::IndexBuffer::Desc& desc)
	{
		GAIA_AST(desc.check());
		if(this->IsCreated())
			this->Destroy();
		glGenBuffers(1, &m_uIB);
		if(m_uIB == GL_INVALID)
			return GAIA::False;
		m_desc = desc;
		return GAIA::True;
	}
	GAIA::BL RenderGL::IndexBuffer::Destroy()
	{
		if(m_uIB != GL_INVALID)
		{
			glDeleteBuffers(1, &m_uIB);
			m_uIB = GL_INVALID;
		}
		return GAIA::True;
	}
	GAIA::BL RenderGL::IndexBuffer::IsCreated() const
	{
		return m_uIB != GL_INVALID;
	}
	RenderGL::VertexBuffer::VertexBuffer()
	{
		m_desc.reset();
		m_uVB = GL_INVALID;
	}
	RenderGL::VertexBuffer::~VertexBuffer()
	{
		if(this->IsCreated())
			this->Destroy();
	}
	GAIA::BL RenderGL::VertexBuffer::SaveToFile(GAIA::FSYS::FileBase* pFile) const
	{
		GPCHR_NULL_RET(pFile, GAIA::False);
		return GAIA::True;
	}
	const VENUS::Render::VertexBuffer::Desc& RenderGL::VertexBuffer::GetDesc() const
	{
		return m_desc;
	}
	GAIA::BL RenderGL::VertexBuffer::Commit(VENUS::Render::COMMIT_METHOD cm, GAIA::SIZE sOffsetInBytes, GAIA::SIZE sSize, const GAIA::GVOID* p)
	{
		GPCHR_NULL_RET(p, GAIA::False);
		glBindBuffer(GL_ARRAY_BUFFER, m_uVB);
		glBufferData(GL_ARRAY_BUFFER, sSize, p, GL_STATIC_DRAW);
		return GAIA::True;
	}
	GAIA::BL RenderGL::VertexBuffer::Create(VENUS::RenderGL& r, const VENUS::Render::VertexBuffer::Desc& desc)
	{
		GAIA_AST(desc.check());
		if(this->IsCreated())
			this->Destroy();
		glGenBuffers(1, &m_uVB);
		if(m_uVB == GL_INVALID)
			return GAIA::False;
		m_desc = desc;
		return GAIA::True;
	}
	GAIA::BL RenderGL::VertexBuffer::Destroy()
	{
		if(m_uVB != GL_INVALID)
		{
			glDeleteBuffers(1, &m_uVB);
			m_uVB = GL_INVALID;
		}
		return GAIA::True;
	}
	GAIA::BL RenderGL::VertexBuffer::IsCreated() const
	{
		return m_uVB != GL_INVALID;
	}
	RenderGL::Shader::Shader()
	{
		m_desc.reset();
		m_uShader = GL_INVALID;
	}
	RenderGL::Shader::~Shader()
	{
		if(this->IsCreated())
			this->Destroy();
	}
	GAIA::BL RenderGL::Shader::SaveToFile(GAIA::FSYS::FileBase* pFile) const
	{
		GPCHR_NULL_RET(pFile, GAIA::False);
		return GAIA::True;
	}
	const VENUS::Render::Shader::Desc& RenderGL::Shader::GetDesc() const
	{
		return m_desc;
	}
	GAIA::BL RenderGL::Shader::Commit(const GAIA::CH* p)
	{
		if(m_uShader == GL_INVALID)
			return GAIA::False;
		GPCHR_NULL_RET(p, GAIA::False);
		GPCHR_NULL_RET(p, GNIL);
		GLint nLen = GAIA::ALGO::strlen(p);
		glShaderSource(m_uShader, 1, &p, &nLen);
		glCompileShader(m_uShader);
		GLint status;
		glGetShaderiv(m_uShader, GL_COMPILE_STATUS, &status);
		if(status != GL_TRUE)
		{
			GAIA::CTN::AString strLog;
			strLog.resize(1024);
			GLsizei ressize;
			glGetShaderInfoLog(m_uShader, 1024, &ressize, strLog.front_ptr());
			return GAIA::False;
		}
		return GAIA::True;
	}
	GAIA::BL RenderGL::Shader::Create(VENUS::RenderGL& r, const VENUS::Render::Shader::Desc& desc)
	{
		GAIA_AST(desc.check());
		if(this->IsCreated())
			this->Destroy();
		switch(desc.type)
		{
		case VENUS::Render::SHADER_TYPE_VERTEXSHADER:
			m_uShader = glCreateShader(GL_VERTEX_SHADER);
			break;
		case VENUS::Render::SHADER_TYPE_PIXELSHADER:
			m_uShader = glCreateShader(GL_FRAGMENT_SHADER);
			break;
		default:
			GAIA_AST(GAIA::ALWAYSFALSE);
			return GAIA::False;
		}
		if(m_uShader == GL_INVALID)
			return GAIA::False;
		m_desc = desc;
		return GAIA::True;
	}
	GAIA::BL RenderGL::Shader::Destroy()
	{
		if(m_uShader != GL_INVALID)
		{
			glDeleteShader(m_uShader);
			m_uShader = GL_INVALID;
		}
		return GAIA::True;
	}
	GAIA::BL RenderGL::Shader::IsCreated() const
	{
		return m_uShader != GL_INVALID;
	}
	RenderGL::Program::Program()
	{
		m_desc.reset();
		m_uProgram = GL_INVALID;
	}
	RenderGL::Program::~Program()
	{
		if(this->IsCreated())
			this->Destroy();
	}
	GAIA::BL RenderGL::Program::SaveToFile(GAIA::FSYS::FileBase* pFile) const
	{
		GPCHR_NULL_RET(pFile, GAIA::False);
		return GAIA::True;
	}
	const VENUS::Render::Program::Desc& RenderGL::Program::GetDesc() const
	{
		return m_desc;
	}
	GAIA::BL RenderGL::Program::Create(VENUS::RenderGL& r, const VENUS::Render::Program::Desc& desc)
	{
		GAIA_AST(desc.check());
		if(this->IsCreated())
			this->Destroy();
		m_uProgram = glCreateProgram();
		if(m_uProgram == GL_INVALID)
			return GAIA::False;
		VENUS::RenderGL::Shader* pShader = GDCAST(VENUS::RenderGL::Shader*)(desc.pVS);
		if(pShader == GNIL)
		{
			glDeleteProgram(m_uProgram);
			m_uProgram = GL_INVALID;
			return GAIA::False;
		}
		glAttachShader(m_uProgram, pShader->m_uShader);
		pShader = GDCAST(VENUS::RenderGL::Shader*)(desc.pPS);
		if(pShader == GNIL)
		{
			glDeleteProgram(m_uProgram);
			m_uProgram = GL_INVALID;
			return GAIA::False;
		}
		glAttachShader(m_uProgram, pShader->m_uShader);
		glLinkProgram(m_uProgram);
		GLint status;
		glGetProgramiv(m_uProgram, GL_LINK_STATUS, &status);
		if(status != GL_TRUE)
		{
			GAIA::CTN::AString strLog;
			strLog.resize(1024);
			GLsizei ressize;
			glGetProgramInfoLog(m_uProgram, 1024, &ressize, strLog.front_ptr());
			glDeleteProgram(m_uProgram);
			m_uProgram = GL_INVALID;
			return GAIA::False;
		}
		GLint nActiveAttrCount;
		glGetProgramiv(m_uProgram, GL_ACTIVE_ATTRIBUTES, &nActiveAttrCount);
		GLint nMaxAttrNameLen;
		glGetProgramiv(m_uProgram, GL_ACTIVE_ATTRIBUTE_MAX_LENGTH, &nMaxAttrNameLen);
		for(GAIA::N32 x = 0; x < nActiveAttrCount; ++x)
		{
			GAIA::CH szTemp[256];
			GLsizei reslen;
			GLint resdatasize;
			GLenum restype;
			glGetActiveAttrib(m_uProgram, x, sizeof(szTemp), &reslen, &resdatasize, &restype, szTemp);
			GLint nLocation = glGetAttribLocation(m_uProgram, szTemp);
			if(nLocation == -1)
			{
				glDeleteProgram(m_uProgram);
				m_uProgram = GL_INVALID;
				attrlist.clear();
				uniformlist.clear();
				return GAIA::False;
			}

			Constant c;
			c.sNameIndex = r.m_strpool.alloc(szTemp);
			switch(restype)
			{
			case GL_FLOAT:
				{
					c.type = GAIA::TYPEID_F32;
					c.uDimenX = 1;
					c.uDimenY = 1;
				}
				break;
			case GL_FLOAT_VEC2:
				{
					c.type = GAIA::TYPEID_F32;
					c.uDimenX = 2;
					c.uDimenY = 1;
				}
				break;
			case GL_FLOAT_VEC3:
				{
					c.type = GAIA::TYPEID_F32;
					c.uDimenX = 3;
					c.uDimenY = 1;
				}
				break;
			case GL_FLOAT_VEC4:
				{
					c.type = GAIA::TYPEID_F32;
					c.uDimenX = 4;
					c.uDimenY = 1;
				}
				break;
			case GL_FLOAT_MAT2:
				{
					c.type = GAIA::TYPEID_F32;
					c.uDimenX = 2;
					c.uDimenY = 2;
				}
				break;
			case GL_FLOAT_MAT3:
				{
					c.type = GAIA::TYPEID_F32;
					c.uDimenX = 3;
					c.uDimenY = 3;
				}
				break;
			case GL_FLOAT_MAT4:
				{
					c.type = GAIA::TYPEID_F32;
					c.uDimenX = 4;
					c.uDimenY = 4;
				}
				break;
			default:
				GAIA_AST(GAIA::ALWAYSFALSE);
				glDeleteProgram(m_uProgram);
				m_uProgram = GL_INVALID;
				attrlist.clear();
				uniformlist.clear();
				return GAIA::False;
			}
			c.uCount = resdatasize;
			c.nLocation = nLocation;
			attrlist.push_back(c);
		}
		attrlist.sort();
		GLint nActiveUniformCount;
		glGetProgramiv(m_uProgram, GL_ACTIVE_UNIFORMS, &nActiveUniformCount);
		GLint nMaxUniformNameLen;
		glGetProgramiv(m_uProgram, GL_ACTIVE_UNIFORM_MAX_LENGTH, &nMaxUniformNameLen);
		for(GAIA::N32 x = 0; x < nActiveUniformCount; ++x)
		{
			GAIA::CH szTemp[256];
			GLsizei reslen;
			GLint resdatasize;
			GLenum restype;
			glGetActiveUniform(m_uProgram, x, sizeof(szTemp), &reslen, &resdatasize, &restype, szTemp);
			GLint nLocation = glGetUniformLocation(m_uProgram, szTemp);
			if(nLocation == -1)
			{
				glDeleteProgram(m_uProgram);
				m_uProgram = GL_INVALID;
				attrlist.clear();
				uniformlist.clear();
				return GAIA::False;
			}

			Constant c;
			c.sNameIndex = r.m_strpool.alloc(szTemp);
			switch(restype)
			{
			case GL_FLOAT:
				{
					c.type = GAIA::TYPEID_F32;
					c.uDimenX = 1;
					c.uDimenY = 1;
				}
				break;
			case GL_FLOAT_VEC2:
				{
					c.type = GAIA::TYPEID_F32;
					c.uDimenX = 2;
					c.uDimenY = 1;
				}
				break;
			case GL_FLOAT_VEC3:
				{
					c.type = GAIA::TYPEID_F32;
					c.uDimenX = 3;
					c.uDimenY = 1;
				}
				break;
			case GL_FLOAT_VEC4:
				{
					c.type = GAIA::TYPEID_F32;
					c.uDimenX = 4;
					c.uDimenY = 1;
				}
				break;
			case GL_FLOAT_MAT2:
				{
					c.type = GAIA::TYPEID_F32;
					c.uDimenX = 2;
					c.uDimenY = 2;
				}
				break;
			case GL_FLOAT_MAT3:
				{
					c.type = GAIA::TYPEID_F32;
					c.uDimenX = 3;
					c.uDimenY = 3;
				}
				break;
			case GL_FLOAT_MAT4:
				{
					c.type = GAIA::TYPEID_F32;
					c.uDimenX = 4;
					c.uDimenY = 4;
				}
				break;
			default:
				GAIA_AST(GAIA::ALWAYSFALSE);
				glDeleteProgram(m_uProgram);
				m_uProgram = GL_INVALID;
				attrlist.clear();
				uniformlist.clear();
				return GAIA::False;
			}
			c.uCount = resdatasize;
			c.nLocation = nLocation;
			uniformlist.push_back(c);
		}
		uniformlist.sort();
		m_desc = desc;
		if(m_desc.pVS != GNIL)
			m_desc.pVS->Reference();
		if(m_desc.pPS != GNIL)
			m_desc.pPS->Reference();
		return GAIA::True;
	}
	GAIA::BL RenderGL::Program::Destroy()
	{
		if(m_uProgram != GL_INVALID)
		{
			glDeleteProgram(m_uProgram);
			m_uProgram = GL_INVALID;
		}
		GAIA_RELEASE_SAFE(m_desc.pVS);
		GAIA_RELEASE_SAFE(m_desc.pPS);
		attrlist.destroy();
		uniformlist.destroy();
		return GAIA::True;
	}
	GAIA::BL RenderGL::Program::IsCreated() const
	{
		return m_uProgram != GL_INVALID;
	}
	RenderGL::Texture::Texture()
	{
		m_desc.reset();
		m_uTex = GL_INVALID;
	}
	RenderGL::Texture::~Texture()
	{
		if(this->IsCreated())
			this->Destroy();
	}
	GAIA::BL RenderGL::Texture::SaveToFile(GAIA::FSYS::FileBase* pFile) const
	{
		GPCHR_NULL_RET(pFile, GAIA::False);
		return GAIA::True;
	}
	const VENUS::Render::Texture::Desc& RenderGL::Texture::GetDesc() const
	{
		return m_desc;
	}
	GAIA::BL RenderGL::Texture::Commit(VENUS::Render::COMMIT_METHOD cm, GAIA::SIZE sOffsetInBytes, GAIA::SIZE sSize, GAIA::SIZE sMipIndex, GAIA::SIZE sFaceIndex, const GAIA::GVOID* p)
	{
		GPCHR_NULL_RET(p, GAIA::False);
		GLint nFormat = GL_INVALID;
		GLenum uType = GL_INVALID;
		switch(m_desc.fmt)
		{
		case VENUS::Render::FORMAT_A8R8G8B8:
			nFormat = GL_RGBA;
			uType = GL_UNSIGNED_BYTE;
			break;
		case VENUS::Render::FORMAT_X8R8G8B8:
			nFormat = GL_RGBA;
			uType = GL_UNSIGNED_BYTE;
			break;
		case VENUS::Render::FORMAT_R8G8B8:
			nFormat = GL_RGB;
			uType = GL_UNSIGNED_BYTE;
			break;
		case VENUS::Render::FORMAT_DXT1:
			break;
		case VENUS::Render::FORMAT_DXT3:
			break;
		case VENUS::Render::FORMAT_DXT5:
			break;
		default:
			GAIA_AST(GAIA::ALWAYSFALSE);
			return GAIA::False;
		}
		switch(m_desc.type)
		{
		case VENUS::Render::TEXTURE_TYPE_1D:
			{
				glBindTexture(GL_TEXTURE_2D, m_uTex);
				glTexImage2D(GL_TEXTURE_2D, sMipIndex, nFormat, m_desc.sSizeX, m_desc.sSizeY, 0, nFormat, uType, p);
			}
			break;
		case VENUS::Render::TEXTURE_TYPE_2D:
			{
				glBindTexture(GL_TEXTURE_2D, m_uTex);
				glTexImage2D(GL_TEXTURE_2D, sMipIndex, nFormat, m_desc.sSizeX, m_desc.sSizeY, 0, nFormat, uType, p);
			}
			break;
		case VENUS::Render::TEXTURE_TYPE_3D:
			return GAIA::False;
		case VENUS::Render::TEXTURE_TYPE_CUBE:
			{
				glBindTexture(GL_TEXTURE_CUBE_MAP, m_uTex);
				glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X, sMipIndex, nFormat, m_desc.sSizeX, m_desc.sSizeY, 0, nFormat, uType, (GAIA::U8*)p + sSize / 6 * 0);
				glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_X, sMipIndex, nFormat, m_desc.sSizeX, m_desc.sSizeY, 0, nFormat, uType, (GAIA::U8*)p + sSize / 6 * 1);
				glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Y, sMipIndex, nFormat, m_desc.sSizeX, m_desc.sSizeY, 0, nFormat, uType, (GAIA::U8*)p + sSize / 6 * 2);
				glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, sMipIndex, nFormat, m_desc.sSizeX, m_desc.sSizeY, 0, nFormat, uType, (GAIA::U8*)p + sSize / 6 * 3);
				glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Z, sMipIndex, nFormat, m_desc.sSizeX, m_desc.sSizeY, 0, nFormat, uType, (GAIA::U8*)p + sSize / 6 * 4);
				glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Z, sMipIndex, nFormat, m_desc.sSizeX, m_desc.sSizeY, 0, nFormat, uType, (GAIA::U8*)p + sSize / 6 * 5);
			}
			break;
		default:
			GAIA_AST(GAIA::ALWAYSFALSE);
			return GAIA::False;
		}
		return GAIA::True;
	}
	GAIA::BL RenderGL::Texture::Create(VENUS::RenderGL& r, const VENUS::Render::Texture::Desc& desc)
	{
		GAIA_AST(desc.check());
		if(this->IsCreated())
			this->Destroy();
		glGenTextures(1, &m_uTex);
		if(m_uTex == GL_INVALID)
			return GAIA::False;
		m_desc = desc;
		return GAIA::True;
	}
	GAIA::BL RenderGL::Texture::Destroy()
	{
		if(m_uTex != GL_INVALID)
		{
			glDeleteTextures(1, &m_uTex);
			m_uTex = GL_INVALID;
		}
		return GAIA::True;
	}
	GAIA::BL RenderGL::Texture::IsCreated() const
	{
		return GAIA::False;
	}
	RenderGL::Target::Target()
	{
		m_desc.reset();
	}
	RenderGL::Target::~Target()
	{
		if(this->IsCreated())
			this->Destroy();
	}
	GAIA::BL RenderGL::Target::SaveToFile(GAIA::FSYS::FileBase* pFile) const
	{
		GPCHR_NULL_RET(pFile, GAIA::False);
		return GAIA::True;
	}
	const VENUS::Render::Target::Desc& RenderGL::Target::GetDesc() const
	{
		return m_desc;
	}
	GAIA::BL RenderGL::Target::Commit(VENUS::Render::COMMIT_METHOD cm, GAIA::SIZE sOffsetInBytes, GAIA::SIZE sSize, const GAIA::GVOID* p)
	{
		GPCHR_NULL_RET(p, GAIA::False);
		return GAIA::True;
	}
	GAIA::BL RenderGL::Target::Create(VENUS::RenderGL& r, const VENUS::Render::Target::Desc& desc)
	{
		GAIA_AST(desc.check());
		if(this->IsCreated())
			this->Destroy();
		m_desc = desc;
		return GAIA::True;
	}
	GAIA::BL RenderGL::Target::Destroy()
	{
		return GAIA::True;
	}
	GAIA::BL RenderGL::Target::IsCreated() const
	{
		return GAIA::False;
	}
	RenderGL::Depther::Depther()
	{
		m_desc.reset();
	}
	RenderGL::Depther::~Depther()
	{
		if(this->IsCreated())
			this->Destroy();
	}
	GAIA::BL RenderGL::Depther::SaveToFile(GAIA::FSYS::FileBase* pFile) const
	{
		GPCHR_NULL_RET(pFile, GAIA::False);
		return GAIA::True;
	}
	const VENUS::Render::Depther::Desc& RenderGL::Depther::GetDesc() const
	{
		return m_desc;
	}
	GAIA::BL RenderGL::Depther::Commit(VENUS::Render::COMMIT_METHOD cm, GAIA::SIZE sOffsetInBytes, GAIA::SIZE sSize, const GAIA::GVOID* p)
	{
		GPCHR_NULL_RET(p, GAIA::False);
		return GAIA::True;
	}
	GAIA::BL RenderGL::Depther::Create(VENUS::RenderGL& r, const VENUS::Render::Depther::Desc& desc)
	{
		GAIA_AST(desc.check());
		if(this->IsCreated())
			this->Destroy();
		m_desc = desc;
		return GAIA::True;
	}
	GAIA::BL RenderGL::Depther::Destroy()
	{
		return GAIA::True;
	}
	GAIA::BL RenderGL::Depther::IsCreated() const
	{
		return GAIA::False;
	}
	GAIA::FWORK::ClsID RenderGL::GetClassID() const
	{
		return VENUS::CLSID_VENUS_RENDERGL;
	}
	RenderGL::RenderGL()
	{
		this->init();
	}
	RenderGL::~RenderGL()
	{
		if(this->IsCreated())
			this->Destroy();
	}
	GAIA::BL RenderGL::Create(const VENUS::Render::Desc& desc)
	{
		if(this->IsCreated())
			return GAIA::False;
		if(!desc.check())
			return GAIA::False;

	#if GAIA_OS == GAIA_OS_WINDOWS
		HWND hWnd = GSCAST(HWND)(desc.pCanvas->GetHandle());
		m_hDC = ::GetDC(hWnd);

		PIXELFORMATDESCRIPTOR pfd;
		GAIA::ALGO::xmemset(&pfd, 0, sizeof(pfd));
		pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
		pfd.nVersion = 1;
		pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
		pfd.iPixelType = PFD_TYPE_RGBA;
		pfd.cColorBits = 24;
		pfd.cRedBits = pfd.cRedShift = pfd.cGreenBits = pfd.cGreenShift = pfd.cBlueBits = pfd.cBlueShift = 0;
		pfd.cAlphaBits = pfd.cAlphaShift = 0;
		pfd.cAccumBits = 0;
		pfd.cAccumRedBits = pfd.cAccumGreenBits = pfd.cAccumBlueBits = pfd.cAccumAlphaBits = 0;
		pfd.cDepthBits = 32;
		pfd.cStencilBits = 0;
		pfd.cAuxBuffers= 0;
		pfd.iLayerType = PFD_MAIN_PLANE;
		pfd.bReserved = 0;
		pfd.dwLayerMask = pfd.dwVisibleMask = pfd.dwDamageMask = 0;

		GAIA::N32 nIndex = ::ChoosePixelFormat(m_hDC, &pfd);
		if(nIndex == 0)
		{
			::ReleaseDC(hWnd, m_hDC);
			m_hDC = GNIL;

			m_desc.pCanvas->Release();
			m_desc.pCanvas = GNIL;
			m_desc.reset();

			return GAIA::False;
		}

		if(!::SetPixelFormat(m_hDC, nIndex, &pfd))
		{
			::ReleaseDC(hWnd, m_hDC);
			m_hDC = GNIL;

			m_desc.pCanvas->Release();
			m_desc.pCanvas = GNIL;
			m_desc.reset();

			return GAIA::False;
		}

		m_hGLRC = ::wglCreateContext(m_hDC);
		if(m_hGLRC == GNIL)
		{
			::ReleaseDC(hWnd, m_hDC);
			m_hDC = GNIL;

			m_desc.pCanvas->Release();
			m_desc.pCanvas = GNIL;
			m_desc.reset();

			return GAIA::False;
		}

		if(!::wglMakeCurrent(m_hDC, m_hGLRC))
		{
			::wglDeleteContext(m_hGLRC);
			m_hGLRC = GNIL;

			::ReleaseDC(hWnd, m_hDC);
			m_hDC = GNIL;

			m_desc.pCanvas->Release();
			m_desc.pCanvas = GNIL;
			m_desc.reset();

			return GAIA::False;
		}

		glGenBuffers = (GLGENBUFFERS)::wglGetProcAddress("glGenBuffers");
		glDeleteBuffers = (GLDELETEBUFFERS)::wglGetProcAddress("glDeleteBuffers");
		glBindBuffer = (GLBINDBUFFER)::wglGetProcAddress("glBindBuffer");
		glBufferData = (GLBUFFERDATA)::wglGetProcAddress("glBufferData");

		glActiveTexture = (GLACTIVETEXTURE)::wglGetProcAddress("glActiveTexture");

		glCreateShader = (GLCREATESHADER)::wglGetProcAddress("glCreateShader");
		glDeleteShader = (GLDELETESHADER)::wglGetProcAddress("glDeleteShader");
		glShaderSource = (GLSHADERSOURCE)::wglGetProcAddress("glShaderSource");
		glShaderBinary = (GLSHADERBINARY)::wglGetProcAddress("glShaderBinary");
		glCompileShader = (GLCOMPILESHADER)::wglGetProcAddress("glCompileShader");
		glGetShaderiv = (GLGETSHADERIV)::wglGetProcAddress("glGetShaderiv");
		glGetShaderInfoLog = (GLGETSHADERINFOLOG)::wglGetProcAddress("glGetShaderInfoLog");
		glReleaseShaderCompiler = (GLRELEASESHADERCOMPILER)::wglGetProcAddress("glReleaseShaderCompiler");

		glCreateProgram = (GLCREATEPROGRAM)::wglGetProcAddress("glCreateProgram");
		glDeleteProgram = (GLDELETEPROGRAM)::wglGetProcAddress("glDeleteProgram");
		glAttachShader = (GLATTACHSHADER)::wglGetProcAddress("glAttachShader");
		glDetachShader = (GLDETACHSHADER)::wglGetProcAddress("glDetachShader");
		glLinkProgram = (GLLINKPROGRAM)::wglGetProcAddress("glLinkProgram");
		glGetProgramiv = (GLGETPROGRAMIV)::wglGetProcAddress("glGetProgramiv");
		glGetProgramInfoLog = (GLGETPROGRAMINFOLOG)::wglGetProcAddress("glGetProgramInfoLog");
		glUseProgram = (GLUSEPROGRAM)::wglGetProcAddress("glUseProgram");

		glEnableVertexAttribArray = (GLENABLEVERTEXATTRIBARRAY)::wglGetProcAddress("glEnableVertexAttribArray");
		glDisableVertexAttribArray = (GLDISABLEVERTEXATTRIBARRAY)::wglGetProcAddress("glDisableVertexAttribArray");
		glGetAttribLocation = (GLGETATTRIBLOCATION)::wglGetProcAddress("glGetAttribLocation");
		glGetActiveAttrib = (GLGETACTIVEATTRIB)::wglGetProcAddress("glGetActiveAttrib");
		glGetUniformLocation = (GLGETUNIFORMLOCATION)::wglGetProcAddress("glGetUniformLocation");
		glGetActiveUniform = (GLGETACTIVEUNIFORM)::wglGetProcAddress("glGetActiveUniform");

		glVertexAttribPointer = (GLVERTEXATTRIBPOINTER)::wglGetProcAddress("glVertexAttribPointer");

		glUniform1fv = (GLUNIFORM1FV)::wglGetProcAddress("glUniform1fv");
		glUniform2fv = (GLUNIFORM2FV)::wglGetProcAddress("glUniform2fv");
		glUniform3fv = (GLUNIFORM3FV)::wglGetProcAddress("glUniform3fv");
		glUniform4fv = (GLUNIFORM4FV)::wglGetProcAddress("glUniform4fv");
		glUniformMatrix2fv = (GLUNIFORMMATRIX2FV)::wglGetProcAddress("glUniformMatrix2fv");
		glUniformMatrix3fv = (GLUNIFORMMATRIX3FV)::wglGetProcAddress("glUniformMatrix3fv");
		glUniformMatrix4fv = (GLUNIFORMMATRIX4FV)::wglGetProcAddress("glUniformMatrix4fv");

		glGetUniformfv = (GLGETUNIFORMFV)::wglGetProcAddress("glGetUniformfv");
		glUniform1i = (GLUNIFORM1I)::wglGetProcAddress("glUniform1i");

		glBlendEquation = (GLBLENDEQUATION)::wglGetProcAddress("glBlendEquation");
	#endif

		const GLubyte* pVersion = glGetString(GL_VERSION);
		const GLubyte* pRenderer = glGetString(GL_RENDERER);
		const GLubyte* pExtension = glGetString(GL_EXTENSIONS);
		const GLubyte* pVendor = glGetString(GL_VENDOR);

		GLboolean bSupportOnlineCompile;
		glGetBooleanv(GL_SHADER_COMPILER, &bSupportOnlineCompile);
		GLint nSupportBinShaderCount;
		glGetIntegerv(GL_NUM_SHADER_BINARY_FORMATS, &nSupportBinShaderCount);
		for(GAIA::SIZE x = 0; x < nSupportBinShaderCount; ++x)
		{
			GLint nSupportBinShaderFormat;
			glGetIntegerv(GL_SHADER_BINARY_FORMATS, &nSupportBinShaderFormat);
		}

		GLint nMaxVertexAttrCount;
		glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nMaxVertexAttrCount);

		GLint nMaxVertexUniformVectorCount;
		glGetIntegerv(GL_MAX_VERTEX_UNIFORM_VECTORS, &nMaxVertexUniformVectorCount);

		GLint nMaxVaryingVectorCount;
		glGetIntegerv(GL_MAX_VARYING_VECTORS, &nMaxVaryingVectorCount);

		GLint nMaxFragmentUniformVectorCount;
		glGetIntegerv(GL_MAX_FRAGMENT_UNIFORM_VECTORS, &nMaxFragmentUniformVectorCount);

		GLint nMaxTextureImageUnit;
		glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS, &nMaxTextureImageUnit);

		GLint nMaxVertexTextureImageUnit;
		glGetIntegerv(GL_MAX_VERTEX_TEXTURE_IMAGE_UNITS, &nMaxVertexTextureImageUnit);

		GLint nMaxCombinedTextureImageUnit;
		glGetIntegerv(GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS, &nMaxCombinedTextureImageUnit);

		m_desc = desc;
		m_desc.pCanvas->Reference();

		m_bCreated = GAIA::True;
		return GAIA::True;
	}
	GAIA::BL RenderGL::Destroy()
	{
		if(!this->IsCreated())
			return GAIA::False;

		GAIA_AST(glGetError() == GL_NO_ERROR);

	#if GAIA_OS == GAIA_OS_WINDOWS
		if(m_hGLRC != GNIL)
		{
			::wglDeleteContext(m_hGLRC);
			m_hGLRC = GNIL;
		}

		if(m_hDC != GNIL)
		{
			HWND hWnd = GSCAST(HWND)(m_desc.pCanvas->GetHandle());
			if(hWnd != GNIL)	// Because windows window can be destroy by user, so the handle could be GNIL. 
								// Search ::PostQuitMessage in gaia will find out the reason.
				::ReleaseDC(hWnd, m_hDC);
			m_hDC = GNIL;
		}
	#endif

		m_desc.pCanvas->Release();
		m_desc.pCanvas = GNIL;

		m_bCreated = GAIA::False;
		return GAIA::True;
	}
	GAIA::BL RenderGL::IsCreated() const
	{
		return m_bCreated;
	}
	const VENUS::Render::Desc& RenderGL::GetDesc() const
	{
		return m_desc;
	}
	VENUS::Render::Context* RenderGL::CreateContext()
	{
		VENUS::RenderGL::Context* pContext = new VENUS::RenderGL::Context;
		return pContext;
	}
	GAIA::BL RenderGL::Begin(VENUS::Render::Context& ctx)
	{
		if(this->IsBegin(ctx))
			return GAIA::False;
		m_bBegin = GAIA::True;
		return GAIA::True;
	}
	GAIA::BL RenderGL::End(VENUS::Render::Context& ctx)
	{
		if(!this->IsBegin(ctx))
			return GAIA::False;
		m_bBegin = GAIA::False;
		return GAIA::True;
	}
	GAIA::BL RenderGL::IsBegin(VENUS::Render::Context& ctx) const
	{
		return m_bBegin;
	}
	GAIA::BL RenderGL::Flush(VENUS::Render::Context& ctx, GAIA::BL bWaitComplete)
	{
		GPCHR_TRUE_RET(this->IsBegin(ctx), GAIA::False);
	#if GAIA_OS == GAIA_OS_WINDOWS
		if(m_hDC == GNIL)
			return GAIA::False;
	#endif
		if(bWaitComplete)
		{
		#if GAIA_OS == GAIA_OS_WINDOWS
			::SwapBuffers(m_hDC);
		#else
			glFinish();
		#endif
			GAIA_AST(glGetError() == GL_NO_ERROR);
		}
		else
			glFlush();

		return GAIA::True;
	}
	GAIA::BL RenderGL::SetRenderState(VENUS::Render::Context& ctx, VENUS::Render::RENDER_STATE s, const GAIA::CTN::Vari& v)
	{
		VENUS::RenderGL::Context* pContext = GDCAST(VENUS::RenderGL::Context*)(&ctx);
		GPCHR_NULL_RET(pContext, GAIA::False);
		switch(s)
		{
		case VENUS::Render::RENDER_STATE_BLEND:
			{
				if((GAIA::BL)v)
					glEnable(GL_BLEND);
				else
					glDisable(GL_BLEND);
			}
			break;
		case VENUS::Render::RENDER_STATE_BLENDSRC:
			{
				VENUS::Render::BLEND blend = (VENUS::Render::BLEND)(GAIA::EN)v;
				switch(blend)
				{
				case VENUS::Render::BLEND_ZERO:
					glBlendFunc(GL_ZERO, pContext->nDstBlend);
					pContext->nSrcBlend = GL_ZERO;
					break;
				case VENUS::Render::BLEND_ONE:
					glBlendFunc(GL_ONE, pContext->nDstBlend);
					pContext->nSrcBlend = GL_ONE;
					break;
				case VENUS::Render::BLEND_SRCALPHA:
					glBlendFunc(GL_SRC_ALPHA, pContext->nDstBlend);
					pContext->nSrcBlend = GL_SRC_ALPHA;
					break;
				case VENUS::Render::BLEND_DSTALPHA:
					glBlendFunc(GL_DST_ALPHA, pContext->nDstBlend);
					pContext->nSrcBlend = GL_DST_ALPHA;
					break;
				case VENUS::Render::BLEND_SRCALPHAINV:
					glBlendFunc(GL_ONE_MINUS_SRC_ALPHA, pContext->nDstBlend);
					pContext->nSrcBlend = GL_ONE_MINUS_SRC_ALPHA;
					break;
				case VENUS::Render::BLEND_DSTALPHAINV:
					glBlendFunc(GL_ONE_MINUS_DST_ALPHA, pContext->nDstBlend);
					pContext->nSrcBlend = GL_ONE_MINUS_DST_ALPHA;
					break;
				default:
					GAIA_AST(GAIA::ALWAYSFALSE);
					return GAIA::False;
				}
			}
			break;
		case VENUS::Render::RENDER_STATE_BLENDDST:
			{
				VENUS::Render::BLEND blend = (VENUS::Render::BLEND)(GAIA::EN)v;
				switch(blend)
				{
				case VENUS::Render::BLEND_ZERO:
					glBlendFunc(pContext->nSrcBlend, GL_ZERO);
					pContext->nDstBlend = GL_ZERO;
					break;
				case VENUS::Render::BLEND_ONE:
					glBlendFunc(pContext->nSrcBlend, GL_ONE);
					pContext->nDstBlend = GL_ONE;
					break;
				case VENUS::Render::BLEND_SRCALPHA:
					glBlendFunc(pContext->nSrcBlend, GL_SRC_ALPHA);
					pContext->nDstBlend = GL_SRC_ALPHA;
					break;
				case VENUS::Render::BLEND_DSTALPHA:
					glBlendFunc(pContext->nSrcBlend, GL_DST_ALPHA);
					pContext->nDstBlend = GL_DST_ALPHA;
					break;
				case VENUS::Render::BLEND_SRCALPHAINV:
					glBlendFunc(pContext->nSrcBlend, GL_ONE_MINUS_SRC_ALPHA);
					pContext->nDstBlend = GL_ONE_MINUS_SRC_ALPHA;
					break;
				case VENUS::Render::BLEND_DSTALPHAINV:
					glBlendFunc(pContext->nSrcBlend, GL_ONE_MINUS_DST_ALPHA);
					pContext->nDstBlend = GL_ONE_MINUS_DST_ALPHA;
					break;
				default:
					GAIA_AST(GAIA::ALWAYSFALSE);
					return GAIA::False;
				}
			}
			break;
		case VENUS::Render::RENDER_STATE_BLENDMETHOD:
			{
				VENUS::Render::BLEND_METHOD bm = (VENUS::Render::BLEND_METHOD)(GAIA::EN)v;
				switch(bm)
				{
				case VENUS::Render::BLEND_METHOD_ADD:
					glBlendEquation(GL_FUNC_ADD);
					break;
				case VENUS::Render::BLEND_METHOD_SUB:
					glBlendEquation(GL_FUNC_SUBTRACT);
					break;
				case VENUS::Render::BLEND_METHOD_SUBINV:
					glBlendEquation(GL_FUNC_REVERSE_SUBTRACT);
					break;
				default:
					GAIA_AST(GAIA::ALWAYSFALSE);
					return GAIA::False;
				}
			}
			break;
		case VENUS::Render::RENDER_STATE_ZTEST:
			{
				if((GAIA::BL)v)
					glEnable(GL_DEPTH_TEST);
				else
					glDisable(GL_DEPTH_TEST);
			}
			break;
		case VENUS::Render::RENDER_STATE_ZFUNC:
			{
				GAIA::RELATION_TYPE r = (GAIA::RELATION_TYPE)(GAIA::EN)v;
				switch(r)
				{
				case GAIA::RELATION_TYPE_EQUAL:
					glDepthFunc(GL_EQUAL);
					break;
				case GAIA::RELATION_TYPE_NOTEQUAL:
					glDepthFunc(GL_NOTEQUAL);
					break;
				case GAIA::RELATION_TYPE_ABOVE:
					glDepthFunc(GL_GREATER);
					break;
				case GAIA::RELATION_TYPE_BELOW:
					glDepthFunc(GL_LESS);
					break;
				case GAIA::RELATION_TYPE_ABOVEEQUAL:
					glDepthFunc(GL_GEQUAL);
					break;
				case GAIA::RELATION_TYPE_BELOWEQUAL:
					glDepthFunc(GL_LEQUAL);
					break;
				case GAIA::RELATION_TYPE_TRUE:
					glDepthFunc(GL_ALWAYS);
					break;
				case GAIA::RELATION_TYPE_FALSE:
					glDepthFunc(GL_NEVER);
					break;
				default:
					GAIA_AST(GAIA::ALWAYSFALSE);
					return GAIA::False;
				}
			}
			break;
		case VENUS::Render::RENDER_STATE_ZWRITE:
			{
			}
			break;
		case VENUS::Render::RENDER_STATE_CULL:
			{
				if((GAIA::BL)v)
					glEnable(GL_CULL_FACE);
				else
					glDisable(GL_CULL_FACE);
			}
			break;
		default:
			GAIA_AST(GAIA::ALWAYSFALSE);
			return GAIA::False;
		}
		return GAIA::True;
	}
	GAIA::BL RenderGL::SetSamplerState(VENUS::Render::Context& ctx, VENUS::Render::SAMPLER_STATE s, const GAIA::CTN::Vari& v)
	{
		VENUS::RenderGL::Context* pContext = GDCAST(VENUS::RenderGL::Context*)(&ctx);
		GPCHR_NULL_RET(pContext, GAIA::False);
		switch(s)
		{
		case VENUS::Render::SAMPLER_STATE_UNWRAPMODEU:
			{
				VENUS::Render::UNWRAPMODE m = (VENUS::Render::UNWRAPMODE)(GAIA::EN)v;
				switch(m)
				{
				case VENUS::Render::UNWRAPMODE_REPEAT:
					glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
					glTexParameterf(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_REPEAT);
					break;
				case VENUS::Render::UNWRAPMODE_CLAMP:
					glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
					glTexParameterf(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
					break;
				case VENUS::Render::UNWRAPMODE_MIRRIOR:
					glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
					glTexParameterf(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
					break;
				default:
					GAIA_AST(GAIA::ALWAYSFALSE);
					return GAIA::False;
				}
			}
			break;
		case VENUS::Render::SAMPLER_STATE_UNWRAPMODEV:
			{
				VENUS::Render::UNWRAPMODE m = (VENUS::Render::UNWRAPMODE)(GAIA::EN)v;
				switch(m)
				{
				case VENUS::Render::UNWRAPMODE_REPEAT:
					glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
					glTexParameterf(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_REPEAT);
					break;
				case VENUS::Render::UNWRAPMODE_CLAMP:
					glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
					glTexParameterf(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
					break;
				case VENUS::Render::UNWRAPMODE_MIRRIOR:
					glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
					glTexParameterf(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
					break;
				default:
					GAIA_AST(GAIA::ALWAYSFALSE);
					return GAIA::False;
				}
			}
			break;
		case VENUS::Render::SAMPLER_STATE_MINFILTER:
			{
				VENUS::Render::FILTER f = (VENUS::Render::FILTER)(GAIA::EN)v;
				switch(f)
				{
				case VENUS::Render::FILTER_NEAREST:
					glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
					glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
					break;
				case VENUS::Render::FILTER_LINEAR:
					glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
					glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
					break;
				default:
					GAIA_AST(GAIA::ALWAYSFALSE);
					return GAIA::False;
				}
			}
			break;
		case VENUS::Render::SAMPLER_STATE_MAXFILTER:
			{
				VENUS::Render::FILTER f = (VENUS::Render::FILTER)(GAIA::EN)v;
				switch(f)
				{
				case VENUS::Render::FILTER_NEAREST:
					glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
					glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
					break;
				case VENUS::Render::FILTER_LINEAR:
					glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
					glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
					break;
				default:
					GAIA_AST(GAIA::ALWAYSFALSE);
					return GAIA::False;
				}
			}
			break;
		default:
			GAIA_AST(GAIA::ALWAYSFALSE);
			return GAIA::False;
		}
		return GAIA::True;
	}
	GAIA::BL RenderGL::SetQualityState(VENUS::Render::Context& ctx, VENUS::Render::QUALITY_STATE s, const GAIA::CTN::Vari& v)
	{
		VENUS::RenderGL::Context* pContext = GDCAST(VENUS::RenderGL::Context*)(&ctx);
		GPCHR_NULL_RET(pContext, GAIA::False);
		switch(s)
		{
		case VENUS::Render::QUALITY_STATE_ANTIALIAS:
			{
			}
			break;
		case VENUS::Render::QUALITY_STATE_FONTANTIALIAS:
			{
			}
			break;
		default:
			GAIA_AST(GAIA::ALWAYSFALSE);
			return GAIA::False;
		}
		return GAIA::True;
	}
	GAIA::BL RenderGL::GetRenderState(VENUS::Render::Context& ctx, VENUS::Render::RENDER_STATE s, GAIA::CTN::Vari& v)
	{
		VENUS::RenderGL::Context* pContext = GDCAST(VENUS::RenderGL::Context*)(&ctx);
		GPCHR_NULL_RET(pContext, GAIA::False);
		switch(s)
		{
		case VENUS::Render::RENDER_STATE_BLEND:
			{
				if(glIsEnabled(GL_BLEND))
					v = GAIA::True;
				else
					v = GAIA::False;
			}
			break;
		case VENUS::Render::RENDER_STATE_BLENDSRC:
			{
				GLint n;
				glGetIntegerv(GL_BLEND_SRC_ALPHA, &n);
				switch(n)
				{
				case GL_ZERO:
					v = VENUS::Render::BLEND_ZERO;
					break;
				case GL_ONE:
					v = VENUS::Render::BLEND_ONE;
					break;
				case GL_SRC_ALPHA:
					v = VENUS::Render::BLEND_SRCALPHA;
					break;
				case GL_DST_ALPHA:
					v = VENUS::Render::BLEND_DSTALPHA;
					break;
				case GL_ONE_MINUS_SRC_ALPHA:
					v = VENUS::Render::BLEND_SRCALPHAINV;
					break;
				case GL_ONE_MINUS_DST_ALPHA:
					v = VENUS::Render::BLEND_DSTALPHAINV;
					break;
				default:
					GAIA_AST(GAIA::ALWAYSFALSE);
					return GAIA::False;
				}
			}
			break;
		case VENUS::Render::RENDER_STATE_BLENDDST:
			{
				GLint n;
				glGetIntegerv(GL_BLEND_DST_ALPHA, &n);
				switch(n)
				{
				case GL_ZERO:
					v = VENUS::Render::BLEND_ZERO;
					break;
				case GL_ONE:
					v = VENUS::Render::BLEND_ONE;
					break;
				case GL_SRC_ALPHA:
					v = VENUS::Render::BLEND_SRCALPHA;
					break;
				case GL_DST_ALPHA:
					v = VENUS::Render::BLEND_DSTALPHA;
					break;
				case GL_ONE_MINUS_SRC_ALPHA:
					v = VENUS::Render::BLEND_SRCALPHAINV;
					break;
				case GL_ONE_MINUS_DST_ALPHA:
					v = VENUS::Render::BLEND_DSTALPHAINV;
					break;
				default:
					GAIA_AST(GAIA::ALWAYSFALSE);
					return GAIA::False;
				}
			}
			break;
		case VENUS::Render::RENDER_STATE_BLENDMETHOD:
			{
				GLint n;
				glGetIntegerv(GL_BLEND_EQUATION_ALPHA, &n);
				switch(n)
				{
				case GL_FUNC_ADD:
					v = VENUS::Render::BLEND_METHOD_ADD;
					break;
				case GL_FUNC_SUBTRACT:
					v = VENUS::Render::BLEND_METHOD_SUB;
					break;
				case GL_FUNC_REVERSE_SUBTRACT:
					v = VENUS::Render::BLEND_METHOD_SUBINV;
					break;
				default:
					GAIA_AST(GAIA::ALWAYSFALSE);
					break;
				}
			}
			break;
		case VENUS::Render::RENDER_STATE_ZTEST:
			{
				if(glIsEnabled(GL_DEPTH_TEST))
					v = GAIA::True;
				else
					v = GAIA::False;
			}
			break;
		case VENUS::Render::RENDER_STATE_ZFUNC:
			{
				GLint n;
				glGetIntegerv(GL_DEPTH_FUNC, &n);
				switch(n)
				{
				case GL_EQUAL:
					v = GAIA::RELATION_TYPE_EQUAL;
					break;
				case GL_NOTEQUAL:
					v = GAIA::RELATION_TYPE_NOTEQUAL;
					break;
				case GL_GREATER:
					v = GAIA::RELATION_TYPE_ABOVE;
					break;
				case GL_LESS:
					v = GAIA::RELATION_TYPE_BELOW;
					break;
				case GL_GEQUAL:
					v = GAIA::RELATION_TYPE_ABOVEEQUAL;
					break;
				case GL_LEQUAL:
					v = GAIA::RELATION_TYPE_BELOWEQUAL;
					break;
				case GL_ALWAYS:
					v = GAIA::RELATION_TYPE_TRUE;
					break;
				case GL_NEVER:
					v = GAIA::RELATION_TYPE_FALSE;
					break;
				default:
					GAIA_AST(GAIA::ALWAYSFALSE);
					return GAIA::False;
				}
			}
			break;
		case VENUS::Render::RENDER_STATE_ZWRITE:
			{
			}
			break;
		case VENUS::Render::RENDER_STATE_CULL:
			{
				if(glIsEnabled(GL_CULL_FACE))
					v = GAIA::True;
				else
					v = GAIA::False;
			}
			break;
		default:
			GAIA_AST(GAIA::ALWAYSFALSE);
			return GAIA::False;
		}
		return GAIA::True;
	}
	GAIA::BL RenderGL::GetSamplerState(VENUS::Render::Context& ctx, VENUS::Render::SAMPLER_STATE s, GAIA::CTN::Vari& v)
	{
		VENUS::RenderGL::Context* pContext = GDCAST(VENUS::RenderGL::Context*)(&ctx);
		GPCHR_NULL_RET(pContext, GAIA::False);
		switch(s)
		{
		case VENUS::Render::SAMPLER_STATE_UNWRAPMODEU:
			{
				GLint n;
				glGetTexParameteriv(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, &n);
				switch(n)
				{
				case GL_REPEAT:
					v = VENUS::Render::UNWRAPMODE_REPEAT;
					break;
				case GL_CLAMP_TO_EDGE:
					v = VENUS::Render::UNWRAPMODE_CLAMP;
					break;
				case GL_MIRRORED_REPEAT:
					v = VENUS::Render::UNWRAPMODE_MIRRIOR;
					break;
				default:
					GAIA_AST(GAIA::ALWAYSFALSE);
					return GAIA::False;
				}
			}
			break;
		case VENUS::Render::SAMPLER_STATE_UNWRAPMODEV:
			{
				GLint n;
				glGetTexParameteriv(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, &n);
				switch(n)
				{
				case GL_REPEAT:
					v = VENUS::Render::UNWRAPMODE_REPEAT;
					break;
				case GL_CLAMP_TO_EDGE:
					v = VENUS::Render::UNWRAPMODE_CLAMP;
					break;
				case GL_MIRRORED_REPEAT:
					v = VENUS::Render::UNWRAPMODE_MIRRIOR;
					break;
				default:
					GAIA_AST(GAIA::ALWAYSFALSE);
					return GAIA::False;
				}
			}
			break;
		case VENUS::Render::SAMPLER_STATE_MINFILTER:
			{
				GLint n;
				glGetTexParameteriv(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, &n);
				switch(n)
				{
				case GL_NEAREST:
					v = VENUS::Render::FILTER_NEAREST;
					break;
				case GL_LINEAR:
					v = VENUS::Render::FILTER_LINEAR;
					break;
				default:
					GAIA_AST(GAIA::ALWAYSFALSE);
					return GAIA::False;
				}
			}
			break;
		case VENUS::Render::SAMPLER_STATE_MAXFILTER:
			{
				GLint n;
				glGetTexParameteriv(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, &n);
				switch(n)
				{
				case GL_NEAREST:
					v = VENUS::Render::FILTER_NEAREST;
					break;
				case GL_LINEAR:
					v = VENUS::Render::FILTER_LINEAR;
					break;
				default:
					GAIA_AST(GAIA::ALWAYSFALSE);
					return GAIA::False;
				}
			}
			break;
		default:
			GAIA_AST(GAIA::ALWAYSFALSE);
			return GAIA::False;
		}
		return GAIA::True;
	}
	GAIA::BL RenderGL::GetQualityState(VENUS::Render::Context& ctx, VENUS::Render::QUALITY_STATE s, GAIA::CTN::Vari& v)
	{
		VENUS::RenderGL::Context* pContext = GDCAST(VENUS::RenderGL::Context*)(&ctx);
		GPCHR_NULL_RET(pContext, GAIA::False);
		switch(s)
		{
		case VENUS::Render::QUALITY_STATE_ANTIALIAS:
			{
			}
			break;
		case VENUS::Render::QUALITY_STATE_FONTANTIALIAS:
			{
			}
			break;
		default:
			GAIA_AST(GAIA::ALWAYSFALSE);
			return GAIA::False;
		}
		return GAIA::True;
	}
	VENUS::Render::IndexBuffer* RenderGL::CreateIndexBuffer(const VENUS::Render::IndexBuffer::Desc& desc)
	{
		if(!desc.check())
			return GNIL;
		VENUS::RenderGL::IndexBuffer* pIB = new VENUS::RenderGL::IndexBuffer;
		if(!pIB->Create(*this, desc))
		{
			pIB->Release();
			return GNIL;
		}
		return pIB;
	}
	VENUS::Render::VertexBuffer* RenderGL::CreateVertexBuffer(const VENUS::Render::VertexBuffer::Desc& desc)
	{
		if(!desc.check())
			return GNIL;
		VENUS::RenderGL::VertexBuffer* pVB = new VENUS::RenderGL::VertexBuffer;
		if(!pVB->Create(*this, desc))
		{
			pVB->Release();
			return GNIL;
		}
		return pVB;
	}
	VENUS::Render::Shader* RenderGL::CreateShader(const VENUS::Render::Shader::Desc& desc)
	{
		if(!desc.check())
			return GNIL;
		VENUS::RenderGL::Shader* pShader = new VENUS::RenderGL::Shader;
		if(!pShader->Create(*this, desc))
		{
			pShader->Release();
			return GNIL;
		}
		return pShader;
	}
	VENUS::Render::Program* RenderGL::CreateProgram(const VENUS::Render::Program::Desc& desc)
	{
		if(!desc.check())
			return GNIL;
		VENUS::RenderGL::Program* pProgram = new VENUS::RenderGL::Program;
		if(!pProgram->Create(*this, desc))
		{
			pProgram->Release();
			return GNIL;
		}
		return pProgram;
	}
	VENUS::Render::Texture* RenderGL::CreateTexture(const VENUS::Render::Texture::Desc& desc)
	{
		if(!desc.check())
			return GNIL;
		VENUS::RenderGL::Texture* pTex = new VENUS::RenderGL::Texture;
		if(!pTex->Create(*this, desc))
		{
			pTex->Release();
			return GNIL;
		}
		return pTex;
	}
	VENUS::Render::Target* RenderGL::CreateTarget(const VENUS::Render::Target::Desc& desc)
	{
		if(!desc.check())
			return GNIL;
		VENUS::RenderGL::Target* pTarget = new VENUS::RenderGL::Target;
		if(!pTarget->Create(*this, desc))
		{
			pTarget->Release();
			return GNIL;
		}
		return pTarget;
	}
	VENUS::Render::Depther* RenderGL::CreateDepther(const VENUS::Render::Depther::Desc& desc)
	{
		if(!desc.check())
			return GNIL;
		VENUS::RenderGL::Depther* pDepther = new VENUS::RenderGL::Depther;
		if(!pDepther->Create(*this, desc))
		{
			pDepther->Release();
			return GNIL;
		}
		return pDepther;
	}
	GAIA::BL RenderGL::SetIndexBuffer(VENUS::Render::Context& ctx, VENUS::Render::IndexBuffer* pIB)
	{
		VENUS::RenderGL::Context* pContext = GDCAST(VENUS::RenderGL::Context*)(&ctx);
		GPCHR_NULL_RET(pContext, GAIA::False);

		if(pContext->pIB == pIB)
			return GAIA::True;

		GAIA_RELEASE_SAFE(pContext->pIB);
		if(pIB != GNIL)
		{
			pContext->pIB = GDCAST(VENUS::RenderGL::IndexBuffer*)(pIB);
			GPCHR_NULL_RET(pContext->pIB, GAIA::False);
			pContext->pIB->Reference();
		}

		return GAIA::True;
	}
	GAIA::BL RenderGL::SetVertexBuffer(VENUS::Render::Context& ctx, const GAIA::CH* pszName, VENUS::Render::VertexBuffer* pVB, GAIA::SIZE sStride, GAIA::SIZE sOffset)
	{
		VENUS::RenderGL::Context* pContext = GDCAST(VENUS::RenderGL::Context*)(&ctx);
		GPCHR_NULL_RET(pContext, GAIA::False);
		GPCHR_NULLSTRPTR_RET(pszName, GAIA::False);

		Context::VertexBufferRec finder;
		finder.sNameIndex = m_strpool.alloc(pszName);
		Context::VertexBufferRec* pFinded = pContext->vbset.find(finder);
		if(pVB != GNIL)
		{
			GPCHR_BELOWEQUALZERO_RET(sStride, GAIA::False);
			GPCHR_BELOWZERO_RET(sOffset, GAIA::False);
			if(pFinded != GNIL)
			{
				if(pFinded->pVB != pVB || pFinded->sStride != sStride || pFinded->sOffset != sOffset)
				{
					GAIA_RELEASE_SAFE(pFinded->pVB);
					pFinded->pVB = GDCAST(VENUS::RenderGL::VertexBuffer*)(pVB);
					GPCHR_NULL_RET(pFinded->pVB, GAIA::False);
					pFinded->pVB->Reference();
					pFinded->sStride = sStride;
					pFinded->sOffset = sOffset;
				}
			}
			else
			{
				finder.pVB = GDCAST(VENUS::RenderGL::VertexBuffer*)(pVB);
				GPCHR_NULL_RET(finder.pVB, GAIA::False);
				finder.pVB->Reference();
				finder.sStride = sStride;
				finder.sOffset = sOffset;
				pContext->vbset.insert(finder);
			}
		}
		else
		{
			if(pFinded != GNIL)
			{
				pFinded->pVB->Release();
				pContext->vbset.erase(finder);
			}
			else
				return GAIA::False;
		}

		return GAIA::True;
	}
	GAIA::BL RenderGL::SetProgram(VENUS::Render::Context& ctx, VENUS::Render::Program* pProgram)
	{
		VENUS::RenderGL::Context* pContext = GDCAST(VENUS::RenderGL::Context*)(&ctx);
		GPCHR_NULL_RET(pContext, GAIA::False);

		if(pContext->pProgram == pProgram)
			return GAIA::True;

		GAIA_RELEASE_SAFE(pContext->pProgram);
		if(pProgram != GNIL)
		{
			pContext->pProgram = GDCAST(VENUS::RenderGL::Program*)(pProgram);
			GPCHR_NULL_RET(pContext->pProgram, GAIA::False);
			pContext->pProgram->Reference();
			glUseProgram(pContext->pProgram->m_uProgram);
		}
		else
			glUseProgram(0);

		return GAIA::True;
	}
	GAIA::BL RenderGL::SetTexture(VENUS::Render::Context& ctx, const GAIA::CH* pszName, VENUS::Render::Texture* pTex)
	{
		VENUS::RenderGL::Context* pContext = GDCAST(VENUS::RenderGL::Context*)(&ctx);
		GPCHR_NULL_RET(pContext, GAIA::False);
		GPCHR_NULLSTRPTR_RET(pszName, GAIA::False);

		Context::TextureRec finder;
		finder.sNameIndex = m_strpool.alloc(pszName);
		Context::TextureRec* pFinded = pContext->texset.find(finder);
		if(pTex != GNIL)
		{
			if(pFinded != GNIL)
			{
				if(pFinded->pTex != pTex)
				{
					GAIA_RELEASE_SAFE(pFinded->pTex);
					pFinded->pTex = GDCAST(VENUS::RenderGL::Texture*)(pTex);
					GPCHR_NULL_RET(pFinded->pTex, GAIA::False);
					pFinded->pTex->Reference();
				}
			}
			else
			{
				finder.pTex = GDCAST(VENUS::RenderGL::Texture*)(pTex);
				GPCHR_NULL_RET(finder.pTex, GAIA::False);
				finder.pTex->Reference();
				pContext->texset.insert(finder);
			}
		}
		else
		{
			if(pFinded != GNIL)
			{
				pFinded->pTex->Release();
				pContext->texset.erase(finder);
			}
			else
				return GAIA::False;
		}

		return GAIA::True;
	}
	GAIA::BL RenderGL::SetTarget(VENUS::Render::Context& ctx, GAIA::SIZE sTargetIndex, VENUS::Render::Target* pTarget)
	{
		VENUS::RenderGL::Context* pContext = GDCAST(VENUS::RenderGL::Context*)(&ctx);
		GPCHR_NULL_RET(pContext, GAIA::False);
		GPCHR_BELOWZERO_RET(sTargetIndex, GAIA::False);
		GAIA_AST(sTargetIndex < sizeofarray(pContext->pTarget));
		if(sTargetIndex >= sizeofarray(pContext->pTarget))
			return GAIA::False;

		if(pContext->pTarget[sTargetIndex] == pTarget)
			return GAIA::True;

		GAIA_RELEASE_SAFE(pContext->pTarget[sTargetIndex]);
		if(pTarget != GNIL)
		{
			pContext->pTarget[sTargetIndex] = GDCAST(VENUS::RenderGL::Target*)(pTarget);
			GPCHR_NULL_RET(pContext->pTarget[sTargetIndex], GAIA::False);
			pContext->pTarget[sTargetIndex]->Reference();
		}
		return GAIA::True;
	}
	GAIA::BL RenderGL::SetDepther(VENUS::Render::Context& ctx, VENUS::Render::Depther* pDepther)
	{
		VENUS::RenderGL::Context* pContext = GDCAST(VENUS::RenderGL::Context*)(&ctx);
		GPCHR_NULL_RET(pContext, GAIA::False);

		if(pContext->pDepther == pDepther)
			return GAIA::True;

		GAIA_RELEASE_SAFE(pContext->pDepther);
		if(pDepther != GNIL)
		{
			pContext->pDepther = GDCAST(VENUS::RenderGL::Depther*)(pDepther);
			GPCHR_NULL_RET(pContext->pDepther, GAIA::False);
			pContext->pDepther->Reference();
		}

		return GAIA::True;
	}
	VENUS::Render::IndexBuffer* RenderGL::GetIndexBuffer(VENUS::Render::Context& ctx)
	{
		VENUS::RenderGL::Context* pContext = GDCAST(VENUS::RenderGL::Context*)(&ctx);
		GPCHR_NULL_RET(pContext, GNIL);
		if(pContext->pIB != GNIL)
			pContext->pIB->Reference();
		return pContext->pIB;
	}
	VENUS::Render::VertexBuffer* RenderGL::GetVertexBuffer(VENUS::Render::Context& ctx, const GAIA::CH* pszName, GAIA::SIZE& sStride, GAIA::SIZE& sOffset)
	{
		VENUS::RenderGL::Context* pContext = GDCAST(VENUS::RenderGL::Context*)(&ctx);
		GPCHR_NULL_RET(pContext, GNIL);
		GPCHR_NULLSTRPTR_RET(pszName, GNIL);

		Context::VertexBufferRec finder;
		finder.sNameIndex = m_strpool.alloc(pszName);
		Context::VertexBufferRec* pFinded = pContext->vbset.find(finder);
		if(pFinded == GNIL)
			return GNIL;
		sStride = pFinded->sStride;
		sOffset = pFinded->sOffset;
		pFinded->pVB->Reference();
		return pFinded->pVB;
	}
	VENUS::Render::Program* RenderGL::GetProgram(VENUS::Render::Context& ctx)
	{
		VENUS::RenderGL::Context* pContext = GDCAST(VENUS::RenderGL::Context*)(&ctx);
		GPCHR_NULL_RET(pContext, GNIL);
		if(pContext->pProgram != GNIL)
			pContext->pProgram->Reference();
		return pContext->pProgram;
	}
	VENUS::Render::Texture* RenderGL::GetTexture(VENUS::Render::Context& ctx, const GAIA::CH* pszName)
	{
		VENUS::RenderGL::Context* pContext = GDCAST(VENUS::RenderGL::Context*)(&ctx);
		GPCHR_NULL_RET(pContext, GNIL);
		GPCHR_NULLSTRPTR_RET(pszName, GNIL);

		Context::TextureRec finder;
		finder.sNameIndex = m_strpool.alloc(pszName);
		Context::TextureRec* pFinded = pContext->texset.find(finder);
		if(pFinded == GNIL)
			return GNIL;
		pFinded->pTex->Reference();
		return pFinded->pTex;
	}
	VENUS::Render::Target* RenderGL::GetTarget(VENUS::Render::Context& ctx, GAIA::SIZE sTargetIndex)
	{
		VENUS::RenderGL::Context* pContext = GDCAST(VENUS::RenderGL::Context*)(&ctx);
		GPCHR_NULL_RET(pContext, GNIL);
		GPCHR_BELOWZERO_RET(sTargetIndex, GNIL);
		GAIA_AST(sTargetIndex < sizeofarray(pContext->pTarget));
		if(sTargetIndex >= sizeofarray(pContext->pTarget))
			return GAIA::False;
		if(pContext->pTarget[sTargetIndex] != GNIL)
			pContext->pTarget[sTargetIndex]->Reference();
		return pContext->pTarget[sTargetIndex];
	}
	VENUS::Render::Depther* RenderGL::GetDepther(VENUS::Render::Context& ctx)
	{
		VENUS::RenderGL::Context* pContext = GDCAST(VENUS::RenderGL::Context*)(&ctx);
		GPCHR_NULL_RET(pContext, GNIL);
		if(pContext->pDepther != GNIL)
			pContext->pDepther->Reference();
		return pContext->pDepther;
	}
	GAIA::BL RenderGL::SetConstant(VENUS::Render::Context& ctx, VENUS::Render::Program& prog, const GAIA::CH* pszUniformName, const GAIA::F32* p, GAIA::U8 uDimenX, GAIA::U8 uDimenY, GAIA::SIZE sCount)
	{
		VENUS::RenderGL::Context* pContext = GDCAST(VENUS::RenderGL::Context*)(&ctx);
		GPCHR_NULL_RET(pContext, GAIA::False);
		GPCHR_NULLSTRPTR_RET(pszUniformName, GAIA::False);
		GPCHR_NULL_RET(p, GAIA::False);

		VENUS::RenderGL::Program* pProgram = GDCAST(VENUS::RenderGL::Program*)(&prog);
		if(pProgram == GNIL)
			return GAIA::False;

		GAIA::BL bChangeProgram;
		if(pProgram != pContext->pProgram)
		{
			bChangeProgram = GAIA::True;
			glUseProgram(pProgram->m_uProgram);
		}
		else
			bChangeProgram = GAIA::False;

		VENUS::RenderGL::Program::Constant finder;
		finder.sNameIndex = m_strpool.alloc(pszUniformName);
		GAIA::SIZE sFindedIndex = pProgram->uniformlist.search(finder);
		if(sFindedIndex == GINVALID)
			return GAIA::False;
		VENUS::RenderGL::Program::Constant& c = pProgram->uniformlist[sFindedIndex];

		switch(uDimenX)
		{
		case 1:
			{
				switch(uDimenY)
				{
				case 1:
					glUniform1fv(c.nLocation, sCount, p);
					break;
				case 2:
				case 3:
				case 4:
				default:
					GAIA_AST(GAIA::ALWAYSFALSE);
					return GAIA::False;
				}
			}
			break;
		case 2:
			{
				switch(uDimenY)
				{
				case 1:
					glUniform2fv(c.nLocation, sCount, p);
					break;
				case 2:
					glUniformMatrix2fv(c.nLocation, sCount, GL_FALSE, p);
					break;
				case 3:
				case 4:
				default:
					GAIA_AST(GAIA::ALWAYSFALSE);
					return GAIA::False;
				}
			}
			break;
		case 3:
			{
				switch(uDimenY)
				{
				case 1:
					glUniform3fv(c.nLocation, sCount, p);
					break;
				case 2:
					return GAIA::False;
				case 3:
					glUniformMatrix3fv(c.nLocation, sCount, GL_FALSE, p);
					break;
				case 4:
				default:
					GAIA_AST(GAIA::ALWAYSFALSE);
					return GAIA::False;
				}
			}
			break;
		case 4:
			{
				switch(uDimenY)
				{
				case 1:
					glUniform4fv(c.nLocation, sCount, p);
					break;
				case 2:
				case 3:
					return GAIA::False;
				case 4:
					glUniformMatrix4fv(c.nLocation, sCount, GL_FALSE, p);
					break;
				default:
					GAIA_AST(GAIA::ALWAYSFALSE);
					return GAIA::False;
				}
			}
			break;
		default:
			GAIA_AST(GAIA::ALWAYSFALSE);
			return GAIA::False;
		}

		if(bChangeProgram)
		{
			if(pContext->pProgram != GNIL)
				glUseProgram(pContext->pProgram->m_uProgram);
			else
				glUseProgram(0);
		}

		return GAIA::True;
	}
	GAIA::BL RenderGL::GetConstant(VENUS::Render::Context& ctx, VENUS::Render::Program& prog, const GAIA::CH* pszUniformName, GAIA::F32* p, GAIA::U8 uDimenX, GAIA::U8 uDimenY, GAIA::SIZE sCount)
	{
		VENUS::RenderGL::Context* pContext = GDCAST(VENUS::RenderGL::Context*)(&ctx);
		GPCHR_NULL_RET(pContext, GAIA::False);
		GPCHR_NULLSTRPTR_RET(pszUniformName, GAIA::False);
		GPCHR_NULL_RET(p, GAIA::False);

		VENUS::RenderGL::Program* pProgram = GDCAST(VENUS::RenderGL::Program*)(&prog);
		if(pProgram == GNIL)
			return GAIA::False;

		VENUS::RenderGL::Program::Constant finder;
		finder.sNameIndex = m_strpool.alloc(pszUniformName);
		GAIA::SIZE sFindedIndex = pProgram->uniformlist.search(finder);
		if(sFindedIndex == GINVALID)
			return GAIA::False;
		VENUS::RenderGL::Program::Constant& c = pProgram->uniformlist[sFindedIndex];
		if(c.uDimenX != uDimenX || c.uDimenY != uDimenY)
			return GAIA::False;
		if(c.uCount != sCount)
			return GAIA::False;

		glGetUniformfv(pProgram->m_uProgram, c.nLocation, p);

		return GAIA::True;
	}
	GAIA::BL RenderGL::SetViewport(const GAIA::MATH::AABR<GAIA::N32>& vp)
	{
		glViewport(vp.pmin.x, vp.pmin.y, vp.width(), vp.height());
		return GAIA::True;
	}
	GAIA::BL RenderGL::GetViewport(GAIA::MATH::AABR<GAIA::N32>& vp) const
	{
		GLint n[4];
		glGetIntegerv(GL_VIEWPORT, n);
		vp.pmin.x = n[0];
		vp.pmin.y = n[1];
		vp.pmax.x = n[0] + n[2];
		vp.pmax.y = n[1] + n[3];
		return GAIA::True;
	}
	GAIA::BL RenderGL::SetScissor(const GAIA::MATH::AABR<GAIA::N32>& s)
	{
		glScissor(s.pmin.x, s.pmin.y, s.width(), s.height());
		return GAIA::True;
	}
	GAIA::BL RenderGL::GetScissor(GAIA::MATH::AABR<GAIA::N32>& s) const
	{
		GLint n[4];
		glGetIntegerv(GL_SCISSOR_BOX, n);
		s.pmin.x = n[0];
		s.pmin.y = n[1];
		s.pmax.x = n[0] + n[2];
		s.pmax.y = n[1] + n[3];
		return GAIA::True;
	}
	GAIA::BL RenderGL::SetElementType(VENUS::Render::Context& ctx, VENUS::Render::ELEMENT_TYPE eletype)
	{
		VENUS::RenderGL::Context* pContext = GDCAST(VENUS::RenderGL::Context*)(&ctx);
		GPCHR_NULL_RET(pContext, GAIA::False);
		pContext->eletype = eletype;
		return GAIA::True;
	}
	VENUS::Render::ELEMENT_TYPE RenderGL::GetElementType(VENUS::Render::Context& ctx) const
	{
		VENUS::RenderGL::Context* pContext = GDCAST(VENUS::RenderGL::Context*)(&ctx);
		GPCHR_NULL_RET(pContext, VENUS::Render::ELEMENT_TYPE_INVALID);
		return pContext->eletype;
	}
	GAIA::BL RenderGL::ClearTarget(VENUS::Render::Context& ctx, GAIA::SIZE sTargetIndex, const GAIA::MATH::ARGB<GAIA::REAL>& cr)
	{
		VENUS::RenderGL::Context* pContext = GDCAST(VENUS::RenderGL::Context*)(&ctx);
		GPCHR_NULL_RET(pContext, GAIA::False);
		glClearColor(cr.r, cr.g, cr.b, cr.a);
		glClear(GL_COLOR_BUFFER_BIT);
		return GAIA::True;
	}
	GAIA::BL RenderGL::ClearDepther(VENUS::Render::Context& ctx, GAIA::REAL rDepth)
	{
		VENUS::RenderGL::Context* pContext = GDCAST(VENUS::RenderGL::Context*)(&ctx);
		GPCHR_NULL_RET(pContext, GAIA::False);
		glClearDepth(rDepth);
		glClear(GL_DEPTH_BUFFER_BIT);
		return GAIA::True;
	}
	GAIA::BL RenderGL::Draw(VENUS::Render::Context& ctx, GAIA::SIZE sElementCount)
	{
		/* Parameter check up. */
		VENUS::RenderGL::Context* pContext = GDCAST(VENUS::RenderGL::Context*)(&ctx);
		GPCHR_NULL_RET(pContext, GAIA::False);
		if(pContext->pProgram == GNIL)
			return GAIA::False;
		if(pContext->pIB == GNIL)
			return GAIA::False;

		/* calculate mode and count. */
		GLenum mode;
		GLsizei count;
		switch(pContext->eletype)
		{
		case VENUS::Render::ELEMENT_TYPE_LINE:
			mode = GL_LINES;
			count = sElementCount * 2;
			break;
		case VENUS::Render::ELEMENT_TYPE_TRIANGLELIST:
			mode = GL_TRIANGLES;
			count = sElementCount * 3;
			break;
		case VENUS::Render::ELEMENT_TYPE_TRIANGLEFAN:
			mode = GL_TRIANGLE_FAN;
			count = sElementCount + 2;
			break;
		case VENUS::Render::ELEMENT_TYPE_TRIANGLESTRIP:
			mode = GL_TRIANGLE_STRIP;
			count = sElementCount + 2;
			break;
		default:
			GAIA_AST(GAIA::ALWAYSFALSE);
			return GAIA::False;
		}

		/* Set index buffer. */
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, pContext->pIB->m_uIB);

		/* Set mapping vertex buffer. */
		for(GAIA::CTN::Vector<VENUS::RenderGL::Program::Constant>::it it = pContext->pProgram->attrlist.front_it(); !it.empty(); ++it)
		{
			VENUS::RenderGL::Program::Constant& c = *it;
			VENUS::RenderGL::Context::VertexBufferRec finder;
			finder.sNameIndex = c.sNameIndex;
			VENUS::RenderGL::Context::VertexBufferRec* pFinded = pContext->vbset.find(finder);
			if(pFinded == GNIL)
				return GAIA::False;

			glBindBuffer(GL_ARRAY_BUFFER, pFinded->pVB->m_uVB);
			glEnableVertexAttribArray(c.nLocation);

			GLenum type;
			switch(c.type)
			{
			case GAIA::TYPEID_F32:
				type = GL_FLOAT;
				break;
			default:
				GAIA_AST(GAIA::ALWAYSFALSE);
				return GAIA::False;
			}
		#if GAIA_COMPILER == GAIA_COMPILER_CL
		#	pragma warning(disable : 4312)
		#endif
			glVertexAttribPointer(c.nLocation, c.uDimenX, type, GL_FALSE, pFinded->sStride, GRCAST(const GLvoid*)(pFinded->sOffset));
		#if GAIA_COMPILER == GAIA_COMPILER_CL
		#	pragma warning(default: 4312)
		#endif
		}

		/* Draw. */
		glDrawElements(mode, count, GL_UNSIGNED_SHORT, GNIL);
		GAIA_AST(glGetError() == GL_NO_ERROR);

		return GAIA::True;
	}
	GAIA::GVOID RenderGL::init()
	{
		m_bCreated = GAIA::False;
		m_bBegin = GAIA::False;
	#if GAIA_OS == GAIA_OS_WINDOWS
		m_hDC = GNIL;
		m_hGLRC = GNIL;
	#endif
	}
};