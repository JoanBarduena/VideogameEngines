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

	////Buffers
	//if (glGenFramebuffers == 0)
	//	LOG("Error, glGenFramebuffers not present!");
	//glGenFramebuffers(1, &fbo_b);
	//glBindFramebuffer(GL_FRAMEBUFFER, fbo_b);

	////Color
	//glGenTextures(1, &rbo);
	//glBindTexture(GL_TEXTURE_2D, rbo);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	//glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, 0);
	//glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, rbo, 0);

	////Texture
	//glGenRenderbuffers(1, &fboTexture);
	//glBindRenderbuffer(GL_RENDERBUFFER, fboTexture);
	//glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);
	//glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, fboTexture);


	//if (glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE) {
	//	LOG("Framebuffer created succesfully!");
	//	ret = false;
	//}

	//size = ImVec2(width, height);

	//glBindFramebuffer(GL_FRAMEBUFFER, 0);

	RestartBuffers();
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
	//size = size_; 

	////Camera
	//glViewport(0, 0, size.x, size.y);

	////ProjectionView();
	////PrepareModelView();

	////Buffer Texture/Depth
	//PrepareDepth();
	//PrepareTexture();

	//glBindFramebuffer(GL_FRAMEBUFFER, fbo_b);
	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	//glEnable(GL_DEPTH_TEST);

	//glStencilFunc(GL_NOTEQUAL, 1, -1);
	//glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
	glBindFramebuffer(GL_FRAMEBUFFER, fbo_b);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // we're not using the stencil buffer now
	glEnable(GL_DEPTH_TEST);

	return true;
}

void FBO::Undraw()
{
	/*glStencilFunc(GL_ALWAYS, 1, 0);
	glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);

	glBindFramebuffer(GL_FRAMEBUFFER, 0);*/
	glBindFramebuffer(GL_FRAMEBUFFER, 0); // back to default
	glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

}

bool FBO::CleanUp()
{
	return true;
}

void FBO::RestartBuffers()
{
	glDeleteFramebuffers(1, &fbo_b);
	glDeleteRenderbuffers(1, &rbo);
	glDeleteTextures(1, &fboTexture);
}

//void FBO::ProjectionView()
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

void FBO::PrepareDepth()
{
	glBindTexture(GL_TEXTURE_2D, fboTexture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, size.x, size.y, 0, GL_RGB, GL_UNSIGNED_BYTE, 0);

	//Reset buffer
	glBindTexture(GL_TEXTURE_2D, 0);
}

void FBO::PrepareTexture()
{
	glBindRenderbuffer(GL_RENDERBUFFER, rbo);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, size.x, size.y);

	//Reset buffer
	glBindRenderbuffer(GL_RENDERBUFFER, 0);
}

uint FBO::GetTexture() const
{
	return fbo_b; 
}

ImVec2 FBO::GetTextureSize() const
{
	return size; 
}