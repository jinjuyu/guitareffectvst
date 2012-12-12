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


void GLGUI::init(HDC dc)
{
	HFONT	font;										// Windows Font ID
	HFONT	oldfont;									// Used For Good House Keeping

	mFont1 = glGenLists(96);
	mFont2 = glGenLists(96);

	font = CreateFont(	-15,							// Height Of Font
						0,								// Width Of Font
						0,								// Angle Of Escapement
						0,								// Orientation Angle
						FW_BOLD,						// Font Weight
						FALSE,							// Italic
						FALSE,							// Underline
						FALSE,							// Strikeout
						ANSI_CHARSET,					// Character Set Identifier
						OUT_TT_PRECIS,					// Output Precision
						CLIP_DEFAULT_PRECIS,			// Clipping Precision
						ANTIALIASED_QUALITY,			// Output Quality
						FF_DONTCARE|DEFAULT_PITCH,		// Family And Pitch
						"Courier New");					// Font Name

	oldfont = (HFONT)SelectObject(dc, font);           // Selects The Font We Want
	wglUseFontBitmaps(dc, 32, 96, mFont1);				// Builds 96 Characters Starting At Character 32
	SelectObject(dc, oldfont);							// Selects The Font We Want
	DeleteObject(font);									// Delete The Font

	font = CreateFont(	-17,							// Height Of Font
						0,								// Width Of Font
						0,								// Angle Of Escapement
						0,								// Orientation Angle
						FW_BOLD,						// Font Weight
						FALSE,							// Italic
						FALSE,							// Underline
						FALSE,							// Strikeout
						ANSI_CHARSET,					// Character Set Identifier
						OUT_TT_PRECIS,					// Output Precision
						CLIP_DEFAULT_PRECIS,			// Clipping Precision
						ANTIALIASED_QUALITY,			// Output Quality
						FF_DONTCARE|DEFAULT_PITCH,		// Family And Pitch
						"Courier New");					// Font Name

	oldfont = (HFONT)SelectObject(dc, font);           // Selects The Font We Want
	wglUseFontBitmaps(dc, 32, 96, mFont2);				// Builds 96 Characters Starting At Character 32
	SelectObject(dc, oldfont);							// Selects The Font We Want
	DeleteObject(font);									// Delete The Font

}
void GLGUI::cleanup()
{
	glDeleteLists(mFont1, 96);
	glDeleteLists(mFont2, 96);
	glDeleteTextures(1, &image);
}
GLvoid GLGUI::Print(TextOption &op, const char *fmt, ...)
{
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, image);

	char        text[256];              // Holds Our String
	va_list     ap;                 // Pointer To List Of Arguments
	va_start(ap, fmt);                  // Parses The String For Variables
	vsprintf(text, fmt, ap);                // And Converts Symbols To Actual Numbers
	va_end(ap);   

	glColor4ub(op.r,op.g,op.b,op.a);
	int width = strlen(text)*6;
	int height = 7;
	float newX;
	if(op.centerX)
		newX = op.x + op.w/2-width/2;
	else
		newX = op.x;
	float newY;
	if(op.centerY)
		newY = op.y + op.h/2-height/2;
	else
		newY = op.y;
		
	glRasterPos2f((float)(newX-6), (float)(newY+4));
	//glTranslatef(newX-6, newY-4, 0.0f);
	glPushAttrib(GL_LIST_BIT);              // Pushes The Display List Bits     ( NEW )
	glListBase(mFont1 - 32);    
	glCallLists(strlen(text), GL_UNSIGNED_BYTE, text);  // Draws The Display List Text  ( NEW )
	glPopAttrib();                      // Pops The Display List Bits   ( NEW )
	glDisable(GL_TEXTURE_2D);
	//glTranslatef(-6.0f*strlen(text), 0.0f, 0.0f);
	//glTranslatef(-newX+6, -newY+4, 0.0f);
}
GLvoid GLGUI::Print2(TextOption &op, const char *fmt, ...) // Bigger Font
{
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, image);

	char        text[256];              // Holds Our String
	va_list     ap;                 // Pointer To List Of Arguments
	va_start(ap, fmt);                  // Parses The String For Variables
	vsprintf(text, fmt, ap);                // And Converts Symbols To Actual Numbers
	va_end(ap);  


	glColor4ub(op.r,op.g,op.b,op.a);
	int width = strlen(text)*7;
	int height = 8;
	float newX;
	if(op.centerX)
		newX = op.x + op.w/2-width/2;
	else
		newX = op.x;
	float newY;
	if(op.centerY)
		newY = op.y + op.h/2-height/2;
	else
		newY = op.y;

	glRasterPos2f((float)(newX-5), (float)(newY+4));
	//glTranslatef(newX-5, newY-4, 0.0f);
	glPushAttrib(GL_LIST_BIT);              // Pushes The Display List Bits     ( NEW )
	glListBase(mFont2 - 32);    
	glCallLists(strlen(text), GL_UNSIGNED_BYTE, text);  // Draws The Display List Text  ( NEW )
	glPopAttrib();                      // Pops The Display List Bits   ( NEW )
	glDisable(GL_TEXTURE_2D);
	//glTranslatef(-7.0f*strlen(text), 0.0f, 0.0f);
	//glTranslatef(-newX+5, -newY+4, 0.0f);

}
void GLGUI::DrawQuad(QuadOption &op)
{
	glDisable(GL_TEXTURE_2D);
	glBegin(GL_QUADS);
	glColor4ub(op.r,op.g,op.b,op.a);
	//glTexCoord2f(0.0f, 0.0f);
	glVertex2i(op.x,   op.y);
	//glTexCoord2f(0.0f, 1.0f);
	glVertex2i(op.x,   op.y+op.h);
	//glTexCoord2f(1.0f, 1.0f);
	glVertex2i(op.x+op.w, op.y+op.h);
	//glTexCoord2f(1.0f, 0.0f);
	glVertex2i(op.x+op.w, op.y);
	glEnd();
}

void GLGUI::DrawQuadBorder(QuadOptionBorder &op, int borderThick)
{
	glDisable(GL_TEXTURE_2D);
	glBegin(GL_QUADS);
	glColor4ub(op.r,op.g,op.b,op.a);
	//DrawQuad
	//glTexCoord2f(0.0f, 0.0f);
	glVertex2i(op.x,   op.y);
	//glTexCoord2f(0.0f, 1.0f);
	glVertex2i(op.x,   op.y+op.h);
	//glTexCoord2f(1.0f, 1.0f);
	glVertex2i(op.x+op.w, op.y+op.h);
	//glTexCoord2f(1.0f, 0.0f);
	glVertex2i(op.x+op.w, op.y);

	//DrawBorder
	glColor4ub(op.rb,op.gb,op.bb,op.ab);

	// TOP
	glVertex2i(op.x,   op.y);
	glVertex2i(op.x,   op.y+borderThick);
	glVertex2i(op.x+op.w, op.y+borderThick);
	glVertex2i(op.x+op.w, op.y);

	// BOTTOM
	glVertex2i(op.x,   op.y+op.h-borderThick);
	glVertex2i(op.x,   op.y+op.h);
	glVertex2i(op.x+op.w, op.y+op.h);
	glVertex2i(op.x+op.w, op.y+op.h-borderThick);

	// LEFT
	glVertex2i(op.x,   op.y);
	glVertex2i(op.x,   op.y+op.h);
	glVertex2i(op.x+borderThick, op.y+op.h);
	glVertex2i(op.x+borderThick, op.y);

	// RIGHT
	glVertex2i(op.x+op.w-borderThick,   op.y);
	glVertex2i(op.x+op.w-borderThick,   op.y+op.h);
	glVertex2i(op.x+op.w, op.y+op.h);
	glVertex2i(op.x+op.w, op.y);

	glEnd();
}

//----------------------------------------------------------------------------
ExampleEditor::ExampleEditor(AudioEffect *effect):
VSTGLEditor(effect, Antialias4x),
Timer(30), //30ms == ~30fps?
thing(0.0f)
{
	//Set the opengl context's size - This must be called here!
	setRect(0, 0, 900, 600);
	mGUI = new GLGUI();
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
	glDisable(GL_DEPTH_TEST);
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


    glDisable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_LINE_SMOOTH);
	glLineWidth(2.0f);

	mGUI->init(dc);

	start();
}

//----------------------------------------------------------------------------
void ExampleEditor::guiClose()
{
	//Stop the timer.
	mGUI->cleanup();
	stop();
}

//----------------------------------------------------------------------------
void ExampleEditor::draw()
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClearDepth(0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	mGUI->DrawElements();
	mGUI->DrawQuad(QuadOption(0,0,100,100,0,255,0,255));
	mGUI->Print(TextOption(0, 0, 100, 100, 0, 0, 255, 255), "werpoj");
}

//----------------------------------------------------------------------------
void ExampleEditor::timerCallback()
{
	refreshGraphics();
}
GUIElement::GUIElement(int handle, GLGUI *gui)
	:mGUI(gui), mHandle(handle)
{
	hidden = false;
	gui->AddElement(this);
}
//===================
int GLGUI::	NewSlider(int x, int y, int w, int min_, int max_, bool isFreq)
{
	int handle = GetNewHandle();
	Slider *sl = new Slider(handle, this, x,y,w,min_,max_, isFreq);
	return handle;
}
int GLGUI::NewTList(int x,int y,int w,int h, TabbedListBoxCallback *cb)
{
	int handle = GetNewHandle();
	TabbedListBox *sl = new TabbedListBox(handle, this, x,y,w,h);
	sl->SetCallback(cb);
	return handle;

}
void GLGUI::AddToTList(int handle, string label, int idx)
{
	((TabbedListBox*)(mGUIElements[handle]))->Add(label, idx);
}
void GLGUI::DeleteTabbedListItem(int handle, int idx)
{
	((TabbedListBox*)(mGUIElements[handle]))->Delete(idx);
}

void GLGUI::	AddToList(int handle, string label, int idx)
{
	((ListBox*)(mGUIElements[handle]))->Add(label, idx);
}
int GLGUI::	NewList(int x,int y,int w,int h, ListBoxCallback *cb)
{
	int handle = GetNewHandle();
	ListBox *sl = new ListBox(handle, this, x,y,w,h);
	sl->SetCallback(cb);
	return handle;
}
void GLGUI::	DeleteListItem(int handle, int idx)
{
	((ListBox*)(mGUIElements[handle]))->Delete(idx);
}
void GLGUI::
SetSliderVal(int handle, int val)
{
	for(GUIElements::iterator i=mGUIElements.begin(); i != mGUIElements.end(); ++i)
	{
		if((*i)->mHandle == handle)
		{
			((Slider*)(*i))->SetVal(val);
			break;
		}
	}
}
void GLGUI::
SetSliderCallback(int handle, SliderCallback *cb)
{
	for(GUIElements::iterator i=mGUIElements.begin(); i != mGUIElements.end(); ++i)
	{
		if((*i)->mHandle == handle)
		{
			((Slider*)(*i))->SetCallback(cb);
			break;
		}
		
	}
}
int GLGUI::NewButton(int x, int y, int w, int h, string label, ButtonCallback *cb)
{
	int handle = GetNewHandle();
	Button *bu = new Button(handle, this, x,y,w,h,label);
	bu->SetCallback(cb);
	return handle;
}
int GLGUI::NewOnOffButton(int x, int y, int w, int h, string label, OnOffButtonCallback *cb)
{
	int handle = GetNewHandle();
	OnOffButton *bu = new OnOffButton(handle, this, x,y,w,h,label);
	bu->SetCallback(cb);
	return handle;
}
GLGUI::GLGUI()
{
	handleCounter = 0;
	mPopupList = new TabbedListBox(GetNewHandle(), this, 0, 0, 300, 150);
	mPopupList->hidden = true;
	mGUIDeleted = false;
}
//------
bool InRect(int x,int y,int w,int h,int x2,int y2)
{
	if(x <= x2 && x2 < x+w && y <= y2 && y2 < y+h)
	{
		return true;
	}
	return false;
}
