#include "ModuleTexture.h"
#include "Application.h"
#include "ModuleGeometry.h"

#include "glew/include/GL/glew.h"

#include "DevIL/IL/il.h"
#include "DevIL/IL/ilu.h"
#include "DevIL/IL/ilut.h"

#pragma comment (lib, "DevIL/libx86/DevIL.lib")
#pragma comment (lib, "DevIL/libx86/ILU.lib")
#pragma comment (lib, "DevIL/libx86/ILUT.lib")

#include "mmgr/mmgr.h"

ModuleTexture::ModuleTexture(bool start_enabled) : Module(start_enabled)
{}


ModuleTexture::~ModuleTexture()
{}

bool ModuleTexture::Init() 
{
	bool ret = true;

	// Checking current version
	if (ilGetInteger(IL_VERSION_NUM) < IL_VERSION || iluGetInteger(ILU_VERSION_NUM) < ILU_VERSION || ilutGetInteger(ILUT_VERSION_NUM) < ILUT_VERSION)
	{
		App->Console_Log("DevIL version is different...exiting!\n");
		ret = false;
	}
	else
	{
		App->Console_Log("Initializing DevIL");

		ilInit();
		iluInit();
		ilutInit();

		// Initialize DevIL's OpenGL access
		ilutRenderer(ILUT_OPENGL);
	}
	return ret;
}


bool ModuleTexture::Start()
{
	bool ret = true;

	DefaultTexture = CreateDefeaultTexture(); 
	CheckerTexture = CreateCheckerTexture(); 

	return ret;
}

update_status ModuleTexture::Update(float dt)
{
	return UPDATE_CONTINUE;
}

bool ModuleTexture::CleanUp()
{
	bool ret = true;

	glDeleteTextures(1, (GLuint*)&DefaultTexture.textureID);
	glDeleteTextures(1, (GLuint*)&CheckerTexture.textureID);

	return ret;
}

TextureStruct ModuleTexture::CreateCheckerTexture() const
{
	GLubyte checkImage[CHECKERS_HEIGHT][CHECKERS_WIDTH][4];
	for (int i = 0; i < CHECKERS_HEIGHT; i++) {
		for (int j = 0; j < CHECKERS_WIDTH; j++) {
			int c = ((((i & 0x8) == 0) ^ (((j & 0x8)) == 0))) * 255;
			checkImage[i][j][0] = (GLubyte)c;
			checkImage[i][j][1] = (GLubyte)c;
			checkImage[i][j][2] = (GLubyte)c;
			checkImage[i][j][3] = (GLubyte)255;
		}
	}

	TextureStruct texture;

	texture.path = "NoPath"; 

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	glGenTextures(1, &texture.textureID);
	glBindTexture(GL_TEXTURE_2D, texture.textureID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, CHECKERS_WIDTH, CHECKERS_HEIGHT,
		0, GL_RGBA, GL_UNSIGNED_BYTE, checkImage);
	
	glBindTexture(GL_TEXTURE_2D, 0);

	texture.width = CHECKERS_WIDTH; 
	texture.height = CHECKERS_HEIGHT; 

	return texture;
}

TextureStruct ModuleTexture::LoadTexturePath(const char* image_path)
{
	// List of textures, so if a texture is already loaded, it will not be loaded again. 
	for (std::vector<TextureStruct>::iterator it = textureList.begin(); it != textureList.end(); ++it)
	{
		if ((*it).path == image_path)
		{
			return (*it); 
		}
	}

	TextureStruct texture;

	//Texture loading success
	texture.textureID = 0;

	if (image_path != nullptr)
	{
		//Generate and set current image ID
		ILuint imgID = 0;
		ilGenImages(1, &imgID);
		ilBindImage(imgID);

		//Load image
		ILboolean success = ilLoadImage(image_path);

		//Image loaded successfully
		if (success == IL_TRUE)
		{
			ILinfo ImgInfo;
			iluGetImageInfo(&ImgInfo);

			if (ImgInfo.Origin == IL_ORIGIN_UPPER_LEFT)
				iluFlipImage();

			//Convert image to RGBA
			success = ilConvertImage(IL_RGBA, IL_UNSIGNED_BYTE);

			if (success == IL_TRUE)
			{
				//Create texture from file pixels
				texture.textureID = LoadTextureFromPixels((GLuint*)ilGetData(), (GLuint)ilGetInteger(IL_IMAGE_WIDTH), (GLuint)ilGetInteger(IL_IMAGE_HEIGHT), (GLuint)ilGetInteger(IL_IMAGE_FORMAT), (GLuint)ilGetInteger(IL_IMAGE_FORMAT));

				texture.height = (GLuint)ilGetInteger(IL_IMAGE_HEIGHT);
				texture.width = (GLuint)ilGetInteger(IL_IMAGE_WIDTH);
				texture.path = image_path;

				ImportTexture(image_path);
			}
			//Delete file from memory
			ilDeleteImages(1, &imgID);
		}
		else
			App->Console_Log("Unable to load image path: %s", image_path);
	}
	else
	{
		App->Console_Log("[WARNING]: Image with path %s could not be loaded as it was NULL", image_path); 
	}
	textureList.push_back(texture); 

	return texture; //return TEXTURE STRUCT (WIDHT, HEIGHT, ID, PATH)
}

uint ModuleTexture::LoadTextureFromPixels(const void* img, uint TextureWidth, uint TextureHeight, int internalFormat, uint format) const
{
	uint TextureID = 0;

	//Generate texture ID
	glGenTextures(1, (GLuint*)&TextureID);

	//Bind texture ID
	glBindTexture(GL_TEXTURE_2D, TextureID);

	//Set texture parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

	if (glewIsSupported("GL_EXT_texture_filter_anisotropic"))
	{
		float max_anisotropy;
		glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &max_anisotropy);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, max_anisotropy);
	}

	//Generate texture
	glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, TextureWidth, TextureHeight, 0, format, GL_UNSIGNED_BYTE, img);
	glGenerateMipmap(GL_TEXTURE_2D);

	//Unbind texture
	glBindTexture(GL_TEXTURE_2D, NULL);

	return TextureID; 
}

TextureStruct ModuleTexture::CreateDefeaultTexture() const
{
	TextureStruct default_tex;

	default_tex.textureID = 0; 
	default_tex.path = "No Path";
	default_tex.width = 0;
	default_tex.height = 0; 

	return default_tex;
}

bool ModuleTexture::ImportTexture(const char* path)
{
	bool ret = false;  

	string output_file, name; 
	name = App->GetNameFromPath(path); 

	ILuint bufferSize;
	ILubyte* bufferData;

	ilSetInteger(IL_DXTC_FORMAT, IL_DXT5);// To pick a specific DXT compression use

	bufferSize = ilSaveL(IL_DDS, NULL, 0); // Get the size of the data buffer

	if (bufferSize > 0)
	{
		bufferData = new ILubyte[bufferSize]; // allocate data buffer

		if (ilSaveL(IL_DDS, bufferData, bufferSize) > 0) // Save to buffer with the ilSaveIL function
			ret = App->filesystem->SaveUnique(output_file, bufferData, bufferSize, LIBRARY_TEXTURES_FOLDER, name.data(), "dds");

		RELEASE_ARRAY(bufferData);
	}

	return ret;
}


