#include "FrameBuffer.h"
#include "Application.h"

#include "mmgr/mmgr.h"

FrameBuffer::FrameBuffer()
{
}

FrameBuffer::~FrameBuffer()
{
}

bool FrameBuffer::Start(ImVec2 size)
{
	RestartBuffers();

	Fsize = size; 

	glGenFramebuffers(1, &fbo);
	glBindFramebuffer(GL_FRAMEBUFFER, fbo);

	//Creating a texture for a framebuffer is roughly the same as a normal texture
	glGenTextures(1, &fboTexture);
	glBindTexture(GL_TEXTURE_2D, fboTexture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, size.x, size.y, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBindTexture(GL_TEXTURE_2D, 0);

	//Attach the texture to the framebuffer
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, fboTexture, 0);

	//Creating a renderbuffer object
	glGenRenderbuffers(1, &rbo);
	glBindRenderbuffer(GL_RENDERBUFFER, rbo);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, size.x, size.y);
	glBindRenderbuffer(GL_RENDERBUFFER, 0);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo);

	App->Console_Log("size_ %d", size.x);

	/*if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		App->Console_Log("ERROR::FRAMEBUFFER:: Framebuffer is not complete!");*/

	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	return true;
}

bool FrameBuffer::Draw()
{
	//Camera
	glViewport(0, 0, Fsize.x, Fsize.y);

	//ProjectionView();
	//PrepareModelView();

	//Buffer Texture/Depth
	PrepareDepth();
	PrepareTexture();

	// first pass
	glBindFramebuffer(GL_FRAMEBUFFER, fbo);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // we're not using the stencil buffer now
	glEnable(GL_DEPTH_TEST);

	// second pass
	glBindFramebuffer(GL_FRAMEBUFFER, 0); // back to default
	glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	return true;
}

bool FrameBuffer::CleanUp()
{
	return true;
}

void FrameBuffer::RestartBuffers()
{
	glDeleteFramebuffers(1, &fbo);
	glDeleteRenderbuffers(1, &rbo);
	glDeleteTextures(1, &fboTexture);
}

//void FrameBuffer::ProjectionView()
//{
//	if (App->editor->panel_scene->OnResize())
//	{
//		glMatrixMode(GL_PROJECTION);
//		glLoadIdentity();
//		ProjectionMatrix = perspective(comp_camera->frustum.horizontalFov * RADTODEG, (float)size.x / (float)size.y, comp_camera->frustum.nearPlaneDistance, comp_camera->frustum.farPlaneDistance);
//		glLoadMatrixf((float*)&ProjectionMatrix);
//	}
//	else
//	{
//		glMatrixMode(GL_PROJECTION);
//		glLoadIdentity();
//		glLoadMatrixf((float*)&comp_camera->GetOpenGLProjectionMatrix());
//	}
//}

void FrameBuffer::PrepareDepth()
{
	glBindTexture(GL_TEXTURE_2D, fboTexture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, Fsize.x, Fsize.y, 0, GL_RGB, GL_UNSIGNED_BYTE, 0);

	//Reset buffer
	glBindTexture(GL_TEXTURE_2D, 0);
}

void FrameBuffer::PrepareTexture()
{
	glBindRenderbuffer(GL_RENDERBUFFER, rbo);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, Fsize.x, Fsize.y);

	//Reset buffer
	glBindRenderbuffer(GL_RENDERBUFFER, 0);
}

GLuint FrameBuffer::GetTexture() const
{
	return fbo; 
}

ImVec2 FrameBuffer::GetTextureSize() const
{
	return Fsize; 
}