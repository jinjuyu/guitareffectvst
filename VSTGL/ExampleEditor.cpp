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
#include "../guitareffectVST/paramsMinMax.h"
#include "../guitareffectVST/DistorsionPanel.h"
#include <string>
using namespace std;

//----------------------------------------------------------------------------
void GLGUI::init()
{
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
	filename += "\\images\\font.png";

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
		glGenTextures(1, &image);
		glBindTexture(GL_TEXTURE_2D, image);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
		glTexImage2D(GL_TEXTURE_2D, 0, ilGetInteger(IL_IMAGE_BPP), ilGetInteger(IL_IMAGE_WIDTH),
		ilGetInteger(IL_IMAGE_HEIGHT), 0, ilGetInteger(IL_IMAGE_FORMAT), GL_UNSIGNED_BYTE,
		ilGetData());
	}
	else
	{
		MessageBox(NULL, filename.c_str(), "Error", MB_OK);
		/* Error occured */
		//exit(1);
		//return -1;
	}
	ilDeleteImages(1, &texid);

	mFont1 = glGenLists(96);
	mFont2 = glGenLists(96);
	
	float cx;
	float cy;
	for (int loop = 0; loop < 96; loop++)      // Loop Through All 256 Lists
	{
		cx = (float) (loop % 16) / 16.0f;  // X Position Of Current Character
		cy = (float) (loop / 16) / 16.0f;  // Y Position Of Current Character

		glNewList(mFont1 + loop, GL_COMPILE);  // Start Building A List
		glBegin(GL_QUADS);      // Use A Quad For Each Character
		glTexCoord2f(cx, 1 - cy);    // Texture Coord (Top Left)
		glVertex2i(0, 0);      // Vertex Coord (Bottom Left)
		glTexCoord2f(cx + 0.0625f, 1 - cy);  // Texture Coord (Top Right)
		glVertex2i(16, 0);      // Vertex Coord (Bottom Right)
		glTexCoord2f(cx + 0.0625f, 1 - cy - 0.0625f);  // Texture Coord (Bottom Right)
		glVertex2i(16, 16);      // Vertex Coord (Top Right)
		glTexCoord2f(cx, 1 - cy - 0.0625f);  // Texture Coord (Bottom Left)
		glVertex2i(0, 16);      // Vertex Coord (Top Left)
		glEnd();          // Done Building Our Quad (Character)
		glTranslated(6, 0, 0);      // Move To The Right Of The Character
		glEndList();        // Done Building The Display List
	}            // Loop Until All 256 Are Built
	for (int loop = 0; loop < 96; loop++)      // Loop Through All 256 Lists
	{
		cx = (float) (loop % 16) / 16.0f;  // X Position Of Current Character
		cy = 0.5f+(float) (loop / 16) / 16.0f;  // Y Position Of Current Character

		glNewList(mFont2 + loop, GL_COMPILE);  // Start Building A List
		glBegin(GL_QUADS);      // Use A Quad For Each Character
		glTexCoord2f(cx, 1 - cy);    // Texture Coord (Top Left)
		glVertex2i(0, 0);      // Vertex Coord (Bottom Left)
		glTexCoord2f(cx + 0.0625f, 1 - cy);  // Texture Coord (Top Right)
		glVertex2i(16, 0);      // Vertex Coord (Bottom Right)
		glTexCoord2f(cx + 0.0625f, 1 - cy - 0.0625f);  // Texture Coord (Bottom Right)
		glVertex2i(16, 16);      // Vertex Coord (Top Right)
		glTexCoord2f(cx, 1 - cy - 0.0625f);  // Texture Coord (Bottom Left)
		glVertex2i(0, 16);      // Vertex Coord (Top Left)
		glEnd();          // Done Building Our Quad (Character)
		glTranslated(8, 0, 0);      // Move To The Right Of The Character
		glEndList();        // Done Building The Display List
	}            // Loop Until All 256 Are Built
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
		
	glTranslatef(newX-6, newY-4, 0.0f);
	glPushAttrib(GL_LIST_BIT);              // Pushes The Display List Bits     ( NEW )
	glListBase(mFont1 - 32);    
	glCallLists(strlen(text), GL_UNSIGNED_BYTE, text);  // Draws The Display List Text  ( NEW )
	glPopAttrib();                      // Pops The Display List Bits   ( NEW )
	glDisable(GL_TEXTURE_2D);
	glTranslatef(-6.0f*strlen(text), 0.0f, 0.0f);
	glTranslatef(-newX+6, -newY+4, 0.0f);
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
	int width = strlen(text)*8;
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
		
	glTranslatef(newX-5, newY-4, 0.0f);
	glPushAttrib(GL_LIST_BIT);              // Pushes The Display List Bits     ( NEW )
	glListBase(mFont2 - 32);    
	glCallLists(strlen(text), GL_UNSIGNED_BYTE, text);  // Draws The Display List Text  ( NEW )
	glPopAttrib();                      // Pops The Display List Bits   ( NEW )
	glDisable(GL_TEXTURE_2D);
	glTranslatef(-8.0f*strlen(text), 0.0f, 0.0f);
	glTranslatef(-newX+5, -newY+4, 0.0f);

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
//-------------

//----------------------------------------------------------------------------
ExampleEditor::ExampleEditor(AudioEffect *effect):
VSTGLEditor(effect, Antialias4x),
Timer(30), //30ms == ~30fps?
thing(0.0f)
{
	//Set the opengl context's size - This must be called here!
	setRect(0, 0, 900, 650);

	mGUI = new GLGUI(m_hInstance);
	mGUI->init();
	
	//mSlider = mGUI->NewSlider(60, 185, 120, 0, 100);
	int x = 400;
	int button = mGUI->NewButton(x+190, 75-25/2, 40, 25, "<==>", &myButtonCB);
	int list = mGUI->NewList(x+240, 0, 180, 150, &myListCB);
	int list2 = mGUI->NewTList(x+0, 0, 180, 150, &myTLCB);
	char temp[123];
	for(int i=0;i<10;++i)
	{
		sprintf(temp, "EffectName%d", i);
		mGUI->AddToList(list, temp);
	}

	for(int i=0;i<50;++i)
	{
		sprintf(temp, "EffectName%d", i);
		mGUI->AddToTList(list2, temp);
	}
	
	int b2 = mGUI->NewOnOffButton(x+240+180+15, 150/2-25/2, 50, 25, "On", &myButton2CB);
	for(int i=0;i<5;++i)
	{
		int b = mGUI->NewOnOffButton(i*180, 13+150, 50, 20, "On", &myButton2CB);
		mOnOffButtons[i] = b;
	}
	for(int i=5;i<10;++i)
	{
		int b = mGUI->NewOnOffButton((i-5)*180, 13+150+250, 50, 20, "On", &myButton2CB);
		mOnOffButtons[i] = b;
	}

	mDistPanel = new DistorsionPanelNS::DistorsionPanel(mGUI,(VstPlugin*)effect, 0);
	/*
	mSlider = mGUI->NewSlider(0, 300, 120, 0, 100);
	mGUI->SetSliderVal(mSlider, 50);
	mGUI->SetSliderCallback(mSlider, &myCB);
	int button = mGUI->NewButton(0, 400, 100, 30, "Test", &myButtonCB);
	int b2 = mGUI->NewOnOffButton(0, 500, 100, 30, "Test", &myButton2CB);
	int list = mGUI->NewList(130, 500, 100, 35, &myListCB);
	mGUI->AddToList(list, "test1");
	mGUI->AddToList(list, "test2");
	mGUI->AddToList(list, "test3");
	mGUI->AddToList(list, "test4");
	mGUI->AddToList(list, "test5");

	int list2 = mGUI->NewTList(130, 0, 100, 300, &myTLCB);
	char temp[123];
	for(int i=0;i<100;++i)
	{
		sprintf(temp, "test%d", i);
		mGUI->AddToTList(list2, temp);
	}
	*/
}

//----------------------------------------------------------------------------
ExampleEditor::~ExampleEditor()
{
	delete mGUI;
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

	mGUI->init();


	start();
}

//----------------------------------------------------------------------------
void ExampleEditor::guiClose()
{
	mGUI->cleanup();
	//Stop the timer.
	stop();
}

//----------------------------------------------------------------------------
void ExampleEditor::draw()
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClearDepth(0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	/*
	QuadOption opQ(0,0,100,100, 0, 128, 128,255);
	mGUI->DrawQuad(opQ);
	TextOption op(0,0,100,100,0,0,255,255);
	mGUI->Print(op, "1234!@#$asd23");

	QuadOptionBorder opQ2(0,100,100,100, 0, 128, 128,255, 0,0,0,255);
	mGUI->DrawQuadBorder(opQ2);
	TextOption op2(0,100,100,100, 0,0,255,255);
	mGUI->Print2(op2, "AAAAAAAAAAAA");
	*/
	for(int i=0;i<5;++i)
	{
		QuadOptionBorder opEff(i*180,650-250-250,180,250,  255, 128, 64,255, 128,64,32,255);
		mGUI->DrawQuadBorder(opEff);
	}
	for(int i=0;i<5;++i)
	{
		QuadOptionBorder opEff(i*180,650-250,180,250,  255, 128, 64,255, 128,64,32,255);
		mGUI->DrawQuadBorder(opEff);
	}

	mGUI->DrawElements();
	mDistPanel->DrawText();
	/*glBegin(GL_QUADS);
	glColor4ub(0,0,255,255);
	glTexCoord2f(0.0f, 0.0f); glVertex2i(0,   0);
	glTexCoord2f(0.0f, 1.0f); glVertex2i(0,   256);
	glTexCoord2f(1.0f, 1.0f); glVertex2i(256, 256);
	glTexCoord2f(1.0f, 0.0f); glVertex2i(256, 0);
	glEnd();*/
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
GLGUI::GLGUI(void *hInstance):m_hInstance(hInstance)
{
	handleCounter = 0;
	mPopupList = new TabbedListBox(GetNewHandle(), this, 0, 0, 200, 150);
	mPopupList->hidden = true;
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
