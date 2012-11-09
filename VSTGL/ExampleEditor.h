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
	GLvoid Print(const char *fmt, ...)
	{
		char        text[256];              // Holds Our String
		va_list     ap;                 // Pointer To List Of Arguments
		va_start(ap, fmt);                  // Parses The String For Variables
		vsprintf(text, fmt, ap);                // And Converts Symbols To Actual Numbers
		va_end(ap);       
		glPushAttrib(GL_LIST_BIT);              // Pushes The Display List Bits     ( NEW )
		glListBase(mFont1 - 32);    
		glCallLists(strlen(text), GL_UNSIGNED_BYTE, text);  // Draws The Display List Text  ( NEW )
		glPopAttrib();                      // Pops The Display List Bits   ( NEW )
	}
	GLvoid Print2(const char *fmt, ...) // Bigger Font
	{
		char        text[256];              // Holds Our String
		va_list     ap;                 // Pointer To List Of Arguments
		va_start(ap, fmt);                  // Parses The String For Variables
		vsprintf(text, fmt, ap);                // And Converts Symbols To Actual Numbers
		va_end(ap);       
		glPushAttrib(GL_LIST_BIT);              // Pushes The Display List Bits     ( NEW )
		glListBase(mFont2 - 32);    
		glCallLists(strlen(text), GL_UNSIGNED_BYTE, text);  // Draws The Display List Text  ( NEW )
		glPopAttrib();                      // Pops The Display List Bits   ( NEW )
	}
  private:
	GLuint image;
	GLuint mFont1;
	GLuint mFont2;
	///	Variable used to rotate the pyramid.
	float thing;
};

