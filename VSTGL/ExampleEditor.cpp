//	ExampleEditor.cpp - Simple OpenGL editor window.
//	--------------------------------------------------------------------------
//	Copyright (c) 2005-2006 Niall Moody
//	
//	Permission is hereby granted, free of charge, to any person obtaining a
//	copy of this software and associated documentation files (the "Software"),
//	to deal in the Software without restriction, including without limitation
//	the rights to use, copy, modify, merge, publish, distribute, sublicense,
//	and/or sell copies of the Software, and to permit persons to whom the
//	Software is furnished to do so, subject to the following conditions:
//
//	The above copyright notice and this permission notice shall be included in
//	all copies or substantial portions of the Software.
//
//	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//	IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//	FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
//	THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//	LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
//	FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
//	DEALINGS IN THE SOFTWARE.
//	--------------------------------------------------------------------------

#include "ExampleEditor.h"
#include <string>
using namespace std;
//----------------------------------------------------------------------------
ExampleEditor::ExampleEditor(AudioEffect *effect):
VSTGLEditor(effect, Antialias4x),
Timer(30), //30ms == ~30fps?
thing(0.0f)
{
	//Set the opengl context's size - This must be called here!
	setRect(0, 0, 900, 650);
}

//----------------------------------------------------------------------------
ExampleEditor::~ExampleEditor()
{
	
}

//----------------------------------------------------------------------------
void ExampleEditor::guiOpen()
{
	glEnable(GL_TEXTURE_2D);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);


	//Setup OpenGL stuff.
	glClearColor(0.0f, 1.0f, 1.0f, 1.0f);
	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	

	glViewport(0, 0, getWidth(), getHeight());
	/*
    //Set viewing projection.
    glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(45.0f,
				   (GLfloat)getWidth()/(GLfloat)getHeight(),
				   0.1f,
				   100.0f);

    //Position viewer.
    glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();*/
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0, (double)getWidth(), (double)getHeight(), 0.0, 0.0, 100.0);
	glMatrixMode(GL_MODELVIEW);
	glClearColor(0.0f, 1.0f, 1.0f, 1.0f);
	glClearDepth(0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


    glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_LINE_SMOOTH);
	glLineWidth(2.0f);


	ILuint texid;
	ILboolean success;
	
	//Start timer to constantly update gui.

	if (ilGetInteger(IL_VERSION_NUM) < IL_VERSION)
	{
		//exit(1);
	}
	ilInit(); /* Initialization of DevIL */
	ilGenImages(1, &texid); /* Generation of one image name */
	ilBindImage(texid); /* Binding of image name */

	char buffer[260];
	GetModuleFileName((HMODULE)m_hInstance, buffer, sizeof(buffer));
	string a(buffer);
	int pos = a.find_last_of('\\');
	string filename = a.substr(0, pos);
	filename += "\\images\\font.tga";

	success = ilLoadImage((const ILstring)filename.c_str()); /* Loading of image "image.jpg" */
	if (success) /* If no error occured: */
	{
		success = ilConvertImage(IL_RGBA, IL_UNSIGNED_BYTE); /* Convert every colour component into
		unsigned byte. If your image contains alpha channel you can replace IL_RGB with IL_RGBA */
		if (!success)
		{
			MessageBox(NULL, filename.c_str(), "Error", MB_OK);
			/* Error occured */
			//exit(1);
			//return -1;
		}
		glGenTextures(1, &image); /* Texture name generation */
		glBindTexture(GL_TEXTURE_2D, image); /* Binding of texture name */
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); /* We will use linear
		interpolation for magnification filter */
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); /* We will use linear
		interpolation for minifying filter */
		glTexImage2D(GL_TEXTURE_2D, 0, ilGetInteger(IL_IMAGE_BPP), ilGetInteger(IL_IMAGE_WIDTH),
		ilGetInteger(IL_IMAGE_HEIGHT), 0, ilGetInteger(IL_IMAGE_FORMAT), GL_UNSIGNED_BYTE,
		ilGetData()); /* Texture specification */
	}
	else
	{
		MessageBox(NULL, filename.c_str(), "Error", MB_OK);
		/* Error occured */
		//exit(1);
		//return -1;
	}
	ilDeleteImages(1, &texid); /* Because we have already copied image data into texture data
	we can release memory used by image. */





	start();
}

//----------------------------------------------------------------------------
void ExampleEditor::guiClose()
{
	glDeleteTextures(1, &image);
	//Stop the timer.
	stop();
}

//----------------------------------------------------------------------------
void ExampleEditor::draw()
{
	glClearColor(0.0f, 1.0f, 1.0f, 1.0f);
	glClearDepth(0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, image);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex2i(0,   0);
	glTexCoord2f(0.0f, 1.0f); glVertex2i(0,   256);
	glTexCoord2f(1.0f, 1.0f); glVertex2i(256, 256);
	glTexCoord2f(1.0f, 0.0f); glVertex2i(256, 0);
	glEnd();
	/*
	glTranslatef(0.0f, 0.0f, -6.0f);
	glRotatef(thing, 1.0f, 1.0f, 1.0f);
	thing += 2.0f;

	glBegin(GL_TRIANGLES);
		glColor3f(1.0f,0.0f,0.0f);
		glVertex3f( 0.0f, 1.0f, 0.0f);
		glColor3f(0.0f,1.0f,0.0f);
		glVertex3f(-1.0f,-1.0f, 1.0f);
		glColor3f(0.0f,0.0f,1.0f);
		glVertex3f( 1.0f,-1.0f, 1.0f);

		glColor3f(1.0f,0.0f,0.0f);
		glVertex3f( 0.0f, 1.0f, 0.0f);
		glColor3f(0.0f,0.0f,1.0f);
		glVertex3f( 1.0f,-1.0f, 1.0f);
		glColor3f(0.0f,1.0f,0.0f);
		glVertex3f( 1.0f,-1.0f, -1.0f);

		glColor3f(1.0f,0.0f,0.0f);
		glVertex3f( 0.0f, 1.0f, 0.0f);
		glColor3f(0.0f,1.0f,0.0f);
		glVertex3f( 1.0f,-1.0f, -1.0f);
		glColor3f(0.0f,0.0f,1.0f);
		glVertex3f(-1.0f,-1.0f, -1.0f);

		glColor3f(1.0f,0.0f,0.0f);
		glVertex3f( 0.0f, 1.0f, 0.0f);
		glColor3f(0.0f,0.0f,1.0f);
		glVertex3f(-1.0f,-1.0f,-1.0f);
		glColor3f(0.0f,1.0f,0.0f);
		glVertex3f(-1.0f,-1.0f, 1.0f);
	glEnd();
	*/
}

//----------------------------------------------------------------------------
void ExampleEditor::timerCallback()
{
	refreshGraphics();
}
