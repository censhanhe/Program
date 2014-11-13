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

	typedef void (GAIA_BASEAPI* GLGENBUFFERS)(GLsizei n, GLuint *buffers);
	typedef void (GAIA_BASEAPI* GLDELETEBUFFERS)(GLsizei n, const GLuint *buffers);
	typedef void (GAIA_BASEAPI* GLBINDBUFFER)(GLenum target, GLuint buffer);
	typedef void (GAIA_BASEAPI* GLBUFFERDATA)(GLenum target, GAIA::NM size, const void *data, GLenum usage);

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

	static GLGENBUFFERS glGenBuffers = GNIL;
	static GLDELETEBUFFERS glDeleteBuffers = GNIL;
	static GLBINDBUFFER glBindBuffer = GNIL;
	static GLBUFFERDATA glBufferData = GNIL;

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
#endif
	RenderGL::Context::Context()
	{
		this->init();
	}
	RenderGL::Context::~Context()
	{
		GAIA_RELEASE_SAFE(pIB);
		for(GAIA::SIZE x = 0; x < sizeofarray(pVB); ++x)
			GAIA_RELEASE_SAFE(pVB[x]);
		GAIA_RELEASE_SAFE(pVDecl);
		GAIA_RELEASE_SAFE(pVS);
		GAIA_RELEASE_SAFE(pPS);
		for(GAIA::SIZE x = 0; x < sizeofarray(pTex); ++x)
			GAIA_RELEASE_SAFE(pTex[x]);
		for(GAIA::SIZE x = 0; x < sizeofarray(pTarget); ++x)
			GAIA_RELEASE_SAFE(pTarget[x]);
		GAIA_RELEASE_SAFE(pDepther);
		this->init();
	}
	GAIA::GVOID RenderGL::Context::init()
	{
		eletype = VENUS::Render::ELEMENT_TYPE_TRIANGLELIST;
		pIB = GNIL;
		GAIA::ALGO::nil(pVB, sizeofarray(pVB));
		pVDecl = GNIL;
		pVS = GNIL;
		pPS = GNIL;
		GAIA::ALGO::nil(pTex, sizeofarray(pTex));
		GAIA::ALGO::nil(pTarget, sizeofarray(pTarget));
		pDepther = GNIL;
	}
	RenderGL::IndexBuffer::IndexBuffer()
	{
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
	GAIA::BL RenderGL::IndexBuffer::Commit(VENUS::Render::COMMIT_METHOD cm, GAIA::SIZE sOffsetInBytes, GAIA::SIZE sSize, const GAIA::GVOID* p)
	{
		GPCHR_NULL_RET(p, GAIA::False);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_uIB);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sSize, p, GL_STATIC_DRAW);
		return GAIA::True;
	}
	GAIA::BL RenderGL::IndexBuffer::Create(const VENUS::Render::IndexBuffer::Desc& desc)
	{
		GAIA_AST(desc.check());
		if(this->IsCreated())
			this->Destroy();
		glGenBuffers(1, &m_uIB);
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
	GAIA::BL RenderGL::VertexBuffer::Commit(VENUS::Render::COMMIT_METHOD cm, GAIA::SIZE sOffsetInBytes, GAIA::SIZE sSize, const GAIA::GVOID* p)
	{
		GPCHR_NULL_RET(p, GAIA::False);
		glBindBuffer(GL_ARRAY_BUFFER, m_uVB);
		glBufferData(GL_ARRAY_BUFFER, sSize, p, GL_STATIC_DRAW);
		return GAIA::True;
	}
	GAIA::BL RenderGL::VertexBuffer::Create(const VENUS::Render::VertexBuffer::Desc& desc)
	{
		GAIA_AST(desc.check());
		if(this->IsCreated())
			this->Destroy();
		glGenBuffers(1, &m_uVB);
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
	RenderGL::VertexDeclaration::VertexDeclaration()
	{
	}
	RenderGL::VertexDeclaration::~VertexDeclaration()
	{
		if(this->IsCreated())
			this->Destroy();
	}
	GAIA::BL RenderGL::VertexDeclaration::SaveToFile(GAIA::FSYS::FileBase* pFile) const
	{
		GPCHR_NULL_RET(pFile, GAIA::False);
		return GAIA::True;
	}
	GAIA::BL RenderGL::VertexDeclaration::Create(const VENUS::Render::VertexDeclaration::Desc& desc)
	{
		GAIA_AST(desc.check());
		if(this->IsCreated())
			this->Destroy();
		return GAIA::True;
	}
	GAIA::BL RenderGL::VertexDeclaration::Destroy()
	{
		return GAIA::True;
	}
	GAIA::BL RenderGL::VertexDeclaration::IsCreated() const
	{
		return GAIA::False;
	}
	RenderGL::Shader::Shader()
	{
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
	GAIA::BL RenderGL::Shader::Create(const VENUS::Render::Shader::Desc& desc)
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
			return GAIA::False;
		}
		if(m_uShader == GL_INVALID)
			return GAIA::False;
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
	GAIA::BL RenderGL::Program::Create(const VENUS::Render::Program::Desc& desc)
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
			return GAIA::False;
		}
		return GAIA::True;
	}
	GAIA::BL RenderGL::Program::Destroy()
	{
		if(m_uProgram != GL_INVALID)
		{
			glDeleteProgram(m_uProgram);
			m_uProgram = GL_INVALID;
		}
		return GAIA::True;
	}
	GAIA::BL RenderGL::Program::IsCreated() const
	{
		return m_uProgram != GL_INVALID;
	}
	RenderGL::Texture::Texture()
	{
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
	GAIA::BL RenderGL::Texture::Commit(VENUS::Render::COMMIT_METHOD cm, GAIA::SIZE sOffsetInBytes, GAIA::SIZE sSize, GAIA::SIZE sMipIndex, GAIA::SIZE sFaceIndex, const GAIA::GVOID* p)
	{
		GPCHR_NULL_RET(p, GAIA::False);
		return GAIA::True;
	}
	GAIA::BL RenderGL::Texture::Create(const VENUS::Render::Texture::Desc& desc)
	{
		GAIA_AST(desc.check());
		if(this->IsCreated())
			this->Destroy();
		return GAIA::True;
	}
	GAIA::BL RenderGL::Texture::Destroy()
	{
		return GAIA::True;
	}
	GAIA::BL RenderGL::Texture::IsCreated() const
	{
		return GAIA::False;
	}
	RenderGL::Target::Target()
	{
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
	GAIA::BL RenderGL::Target::Commit(VENUS::Render::COMMIT_METHOD cm, GAIA::SIZE sOffsetInBytes, GAIA::SIZE sSize, const GAIA::GVOID* p)
	{
		GPCHR_NULL_RET(p, GAIA::False);
		return GAIA::True;
	}
	GAIA::BL RenderGL::Target::Create(const VENUS::Render::Target::Desc& desc)
	{
		GAIA_AST(desc.check());
		if(this->IsCreated())
			this->Destroy();
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
	GAIA::BL RenderGL::Depther::Commit(VENUS::Render::COMMIT_METHOD cm, GAIA::SIZE sOffsetInBytes, GAIA::SIZE sSize, const GAIA::GVOID* p)
	{
		GPCHR_NULL_RET(p, GAIA::False);
		return GAIA::True;
	}
	GAIA::BL RenderGL::Depther::Create(const VENUS::Render::Depther::Desc& desc)
	{
		GAIA_AST(desc.check());
		if(this->IsCreated())
			this->Destroy();
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
		case VENUS::Render::RENDER_STATE_ALPHABLEND:
			{
				if((GAIA::BL)v)
					glEnable(GL_BLEND);
				else
					glDisable(GL_BLEND);
			}
			break;
		case VENUS::Render::RENDER_STATE_ZTEST:
			{
			}
			break;
		case VENUS::Render::RENDER_STATE_ZFUNC:
			{
			}
			break;
		case VENUS::Render::RENDER_STATE_ZWRITE:
			{
			}
			break;
		case VENUS::Render::RENDER_STATE_CULL:
			{
			}
			break;
		default:
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
		case VENUS::Render::SAMPLER_STATE_MINFILTER:
			{
			}
			break;
		case VENUS::Render::SAMPLER_STATE_MAXFILTER:
			{
			}
			break;
		case VENUS::Render::SAMPLER_STATE_MIPFILTER:
			{
			}
			break;
		case VENUS::Render::SAMPLER_STATE_BORDERCOLOR:
			{
			}
			break;
		case VENUS::Render::SAMPLER_STATE_BORDER:
			{
			}
			break;
		default:
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
		case VENUS::Render::RENDER_STATE_ALPHABLEND:
			{
				if(glIsEnabled(GL_BLEND))
					v = GAIA::True;
				else
					v = GAIA::False;
			}
			break;
		case VENUS::Render::RENDER_STATE_ZTEST:
			{
			}
			break;
		case VENUS::Render::RENDER_STATE_ZFUNC:
			{
			}
			break;
		case VENUS::Render::RENDER_STATE_ZWRITE:
			{
			}
			break;
		case VENUS::Render::RENDER_STATE_CULL:
			{
			}
			break;
		default:
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
		case VENUS::Render::SAMPLER_STATE_MINFILTER:
			{
			}
			break;
		case VENUS::Render::SAMPLER_STATE_MAXFILTER:
			{
			}
			break;
		case VENUS::Render::SAMPLER_STATE_MIPFILTER:
			{
			}
			break;
		case VENUS::Render::SAMPLER_STATE_BORDERCOLOR:
			{
			}
			break;
		case VENUS::Render::SAMPLER_STATE_BORDER:
			{
			}
			break;
		default:
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
			return GAIA::False;
		}
		return GAIA::True;
	}
	VENUS::Render::IndexBuffer* RenderGL::CreateIndexBuffer(const VENUS::Render::IndexBuffer::Desc& desc)
	{
		if(!desc.check())
			return GNIL;
		VENUS::RenderGL::IndexBuffer* pIB = new VENUS::RenderGL::IndexBuffer;
		if(!pIB->Create(desc))
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
		if(!pVB->Create(desc))
		{
			pVB->Release();
			return GNIL;
		}
		return pVB;
	}
	VENUS::Render::VertexDeclaration* RenderGL::CreateVertexDeclaration(const VENUS::Render::VertexDeclaration::Desc& desc)
	{
		if(!desc.check())
			return GNIL;
		VENUS::RenderGL::VertexDeclaration* pVDecl = new VENUS::RenderGL::VertexDeclaration;
		if(!pVDecl->Create(desc))
		{
			pVDecl->Release();
			return GNIL;
		}
		return pVDecl;
	}
	VENUS::Render::Shader* RenderGL::CreateShader(const VENUS::Render::Shader::Desc& desc)
	{
		if(!desc.check())
			return GNIL;
		VENUS::RenderGL::Shader* pShader = new VENUS::RenderGL::Shader;
		if(!pShader->Create(desc))
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
		if(!pProgram->Create(desc))
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
		if(!pTex->Create(desc))
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
		if(!pTarget->Create(desc))
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
		if(!pDepther->Create(desc))
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
		return GAIA::True;
	}
	GAIA::BL RenderGL::SetVertexBuffer(VENUS::Render::Context& ctx, GAIA::SIZE sStreamIndex, VENUS::Render::VertexBuffer* pVB)
	{
		VENUS::RenderGL::Context* pContext = GDCAST(VENUS::RenderGL::Context*)(&ctx);
		GPCHR_NULL_RET(pContext, GAIA::False);
		return GAIA::True;
	}
	GAIA::BL RenderGL::SetVertexDeclaration(VENUS::Render::Context& ctx, VENUS::Render::VertexDeclaration* pVDecl)
	{
		VENUS::RenderGL::Context* pContext = GDCAST(VENUS::RenderGL::Context*)(&ctx);
		GPCHR_NULL_RET(pContext, GAIA::False);
		return GAIA::True;
	}
	GAIA::BL RenderGL::SetProgram(VENUS::Render::Context& ctx, VENUS::Render::Program* pProgram)
	{
		VENUS::RenderGL::Context* pContext = GDCAST(VENUS::RenderGL::Context*)(&ctx);
		GPCHR_NULL_RET(pContext, GAIA::False);
		return GAIA::True;
	}
	GAIA::BL RenderGL::SetTexture(VENUS::Render::Context& ctx, GAIA::SIZE sTextureIndex, VENUS::Render::Texture* pTex)
	{
		VENUS::RenderGL::Context* pContext = GDCAST(VENUS::RenderGL::Context*)(&ctx);
		GPCHR_NULL_RET(pContext, GAIA::False);
		return GAIA::True;
	}
	GAIA::BL RenderGL::SetTarget(VENUS::Render::Context& ctx, GAIA::SIZE sTargetIndex, VENUS::Render::Target* pTarget)
	{
		VENUS::RenderGL::Context* pContext = GDCAST(VENUS::RenderGL::Context*)(&ctx);
		GPCHR_NULL_RET(pContext, GAIA::False);
		return GAIA::True;
	}
	GAIA::BL RenderGL::SetDepther(VENUS::Render::Context& ctx, VENUS::Render::Depther* pDepther)
	{
		VENUS::RenderGL::Context* pContext = GDCAST(VENUS::RenderGL::Context*)(&ctx);
		GPCHR_NULL_RET(pContext, GAIA::False);
		return GAIA::True;
	}
	VENUS::Render::IndexBuffer* RenderGL::GetIndexBuffer(VENUS::Render::Context& ctx)
	{
		VENUS::RenderGL::Context* pContext = GDCAST(VENUS::RenderGL::Context*)(&ctx);
		GPCHR_NULL_RET(pContext, GNIL);
		return GNIL;
	}
	VENUS::Render::VertexBuffer* RenderGL::GetVertexBuffer(VENUS::Render::Context& ctx, GAIA::SIZE sStreamIndex)
	{
		VENUS::RenderGL::Context* pContext = GDCAST(VENUS::RenderGL::Context*)(&ctx);
		GPCHR_NULL_RET(pContext, GNIL);
		return GNIL;
	}
	VENUS::Render::VertexDeclaration* RenderGL::GetVertexDeclaration(VENUS::Render::Context& ctx)
	{
		VENUS::RenderGL::Context* pContext = GDCAST(VENUS::RenderGL::Context*)(&ctx);
		GPCHR_NULL_RET(pContext, GNIL);
		return GNIL;
	}
	VENUS::Render::Program* RenderGL::GetProgram(VENUS::Render::Context& ctx)
	{
		VENUS::RenderGL::Context* pContext = GDCAST(VENUS::RenderGL::Context*)(&ctx);
		GPCHR_NULL_RET(pContext, GNIL);
		return GNIL;
	}
	VENUS::Render::Texture* RenderGL::GetTexture(VENUS::Render::Context& ctx, GAIA::SIZE sTextureIndex)
	{
		VENUS::RenderGL::Context* pContext = GDCAST(VENUS::RenderGL::Context*)(&ctx);
		GPCHR_NULL_RET(pContext, GNIL);
		return GNIL;
	}
	VENUS::Render::Target* RenderGL::GetTarget(VENUS::Render::Context& ctx, GAIA::SIZE sTargetIndex)
	{
		VENUS::RenderGL::Context* pContext = GDCAST(VENUS::RenderGL::Context*)(&ctx);
		GPCHR_NULL_RET(pContext, GNIL);
		return GNIL;
	}
	VENUS::Render::Depther* RenderGL::GetDepther(VENUS::Render::Context& ctx)
	{
		VENUS::RenderGL::Context* pContext = GDCAST(VENUS::RenderGL::Context*)(&ctx);
		GPCHR_NULL_RET(pContext, GNIL);
		return GNIL;
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
	GAIA::BL RenderGL::SetVertexBufferBase(VENUS::Render::Context& ctx, GAIA::SIZE sStreamIndex, GAIA::SIZE sBaseIndex)
	{
		VENUS::RenderGL::Context* pContext = GDCAST(VENUS::RenderGL::Context*)(&ctx);
		GPCHR_NULL_RET(pContext, GAIA::False);
		return GAIA::True;
	}
	GAIA::BL RenderGL::SetIndexBufferBase(VENUS::Render::Context& ctx, GAIA::SIZE sBaseIndex)
	{
		VENUS::RenderGL::Context* pContext = GDCAST(VENUS::RenderGL::Context*)(&ctx);
		GPCHR_NULL_RET(pContext, GAIA::False);
		return GAIA::True;
	}
	GAIA::BL RenderGL::Draw(VENUS::Render::Context& ctx, GAIA::SIZE sElementCount)
	{
		VENUS::RenderGL::Context* pContext = GDCAST(VENUS::RenderGL::Context*)(&ctx);
		GPCHR_NULL_RET(pContext, GAIA::False);
		GLenum mode;
		switch(pContext->eletype)
		{
		case VENUS::Render::ELEMENT_TYPE_SLINE:
			mode = GL_LINES;
			break;
		case VENUS::Render::ELEMENT_TYPE_SLINESTRIP:
			mode = GL_LINE_STRIP;
			break;
		case VENUS::Render::ELEMENT_TYPE_STRIANGLELIST:
			mode = GL_TRIANGLES;
			break;
		case VENUS::Render::ELEMENT_TYPE_STRIANGLEFAN:
			mode = GL_TRIANGLE_FAN;
			break;
		case VENUS::Render::ELEMENT_TYPE_STRIANGLESTRIP:
			mode = GL_TRIANGLE_STRIP;
			break;
		case VENUS::Render::ELEMENT_TYPE_TRIANGLELIST:
			mode = GL_TRIANGLES;
			break;
		case VENUS::Render::ELEMENT_TYPE_TRIANGLEFAN:
			mode = GL_TRIANGLE_FAN;
			break;
		case VENUS::Render::ELEMENT_TYPE_TRIANGLESTRIP:
			mode = GL_TRIANGLE_STRIP;
			break;
		default:
			return GAIA::False;
		}
		glDrawElements(mode, sElementCount, GL_UNSIGNED_SHORT, GNIL);
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