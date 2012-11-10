//	ExampleEditor.h - Simple OpenGL editor window.
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

#pragma once
#pragma warning( disable : 4996 4819)
#include "VSTGL/VSTGLEditor.h"
#include "VSTGL/VSTGLTimer.h"
#include <iostream>
#include <stdio.h>
#include <stdarg.h>
///	Simple VSTGL example.
#pragma warning(disable:4244)
class TextOption
{
public:
	TextOption(int x,int y,int w,int h, unsigned int r, unsigned int g, unsigned int b, unsigned int a, bool centerX=true, bool centerY=true)
		:x(x),y(y),w(w),h(h),centerX(centerX),centerY(centerY),r(r),g(g),b(b),a(a)
	{
	}
	int x,y,w,h;
	bool centerX;
	bool centerY;
	unsigned int r,g,b,a;
};
class QuadOption
{
public:
	QuadOption(int x,int y,int w,int h, unsigned int r, unsigned int g, unsigned int b, unsigned int a)
		:x(x),y(y),w(w),h(h),r(r),g(g),b(b),a(a)
	{
	}
	int x,y,w,h;
	unsigned int r,g,b,a;
};

class QuadOptionBorder
{
public:
	QuadOptionBorder(int x,int y,int w,int h, unsigned int r, unsigned int g, unsigned int b, unsigned int a, unsigned int rb, unsigned int gb, unsigned int bb, unsigned int ab)
		:x(x),y(y),w(w),h(h),r(r),g(g),b(b),a(a),rb(rb),gb(gb),bb(bb),ab(ab)
	{
	}
	int x,y,w,h;
	unsigned int r,g,b,a;
	unsigned int rb,gb,bb,ab;
};

class GLGUI
{
public:
	GLGUI(void *hInstance):m_hInstance(hInstance)
	{
	}
	~GLGUI()
	{
		cleanup();
	}
	void DrawQuad(QuadOption &op);
	void DrawQuadBorder(QuadOptionBorder &op, int borderThick=1);
	void *m_hInstance;
	void init();
	void cleanup();
	GLvoid Print(TextOption &op, const char *fmt, ...);
	GLvoid Print2(TextOption &op, const char *fmt, ...);

private:
	GLuint image;
	GLuint mFont1;
	GLuint mFont2;

};
class ExampleEditor : public VSTGLEditor,
					  public Timer
{
  public:
	///	Constructor.
	ExampleEditor(AudioEffect *effect);
	///	Destructor.
	~ExampleEditor();

	///	Called when the Gui's window is opened.
	void guiOpen();
	///	Called when the Gui's window is closed.
	void guiClose();

	///	Draws a spinning pyramid.
	void draw();

	///	Called repeatedly, to update the graphics.
	
	void timerCallback();
  private:
	  GLGUI *mGUI;
	///	Variable used to rotate the pyramid.
	float thing;
};

