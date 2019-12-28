#include "FBO.h"
#include "Application.h"

#include "mmgr/mmgr.h"

FBO::FBO()
{
}

FBO::~FBO()
{
}

bool FBO::Start(uint width, uint height)
{
	bool ret = true;

	RestartBuffers();

	size.x = width; 
	size.y = height; 

	//Generate the FBO and bind it, continue if FBO is complete
	glGenFramebuffers(1, &fbo_b);
	glBindFramebuffer(GL_FRAMEBUFFER, fbo_b);

	//Generate the texture used to render our scene
	glGenTextures(1, &fboTexture);
	glBindTexture(GL_TEXTURE_2D, fboTexture);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, size.x, size.y, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBindTexture(GL_TEXTURE_2D, 0);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, fboTexture, 0);

	//Generate RenderBufferObject
	glGenRenderbuffers(1, &rbo);
	glBindRenderbuffer(GL_RENDERBUFFER, rbo);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, size.x, size.y);
	glBindRenderbuffer(GL_RENDERBUFFER, 0);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo);

	glBindFramebuffer(GL_FRAMEBUFFER, 0);


	return ret;
}

bool FBO::Draw()
{
	glBindFramebuffer(GL_FRAMEBUFFER, fbo_b);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);

	return true;
}

void FBO::Undraw()
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0); 
	glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
}

bool FBO::CleanUp()
{
	RestartBuffers(); 
	return true;
}

void FBO::RestartBuffers()
{
	glDeleteFramebuffers(1, &fbo_b);
	glDeleteRenderbuffers(1, &rbo);
	glDeleteTextures(1, &fboTexture);
}


uint FBO::GetTexture() const
{
	return fbo_b; 
}

ImVec2 FBO::GetTextureSize() const
{
	return size; 
}