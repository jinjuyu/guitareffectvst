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
#include "../guitareffectVST/LinealEQ.h"
#include "../guitareffectVST/CompressorPanel.h"
#include "../guitareffectVST/EchoPanel.h"
#include "../guitareffectVST/Panel.h"

#include <string>
#include <algorithm>
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

	char buffer[1024];
	GetModuleFileName((HMODULE)m_hInstance, buffer, sizeof(buffer));
	string a(buffer);
	int pos = a.find_last_of('\\');
	string filename = a.substr(0, pos);
	filename += "\\guitareffectVST\\images\\font.png";

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
		glTranslated(7, 0, 0);      // Move To The Right Of The Character
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
		
	glTranslatef(newX-5, newY-4, 0.0f);
	glPushAttrib(GL_LIST_BIT);              // Pushes The Display List Bits     ( NEW )
	glListBase(mFont2 - 32);    
	glCallLists(strlen(text), GL_UNSIGNED_BYTE, text);  // Draws The Display List Text  ( NEW )
	glPopAttrib();                      // Pops The Display List Bits   ( NEW )
	glDisable(GL_TEXTURE_2D);
	glTranslatef(-7.0f*strlen(text), 0.0f, 0.0f);
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
bool CompEff(EffectName a, EffectName b)
{
	return a.type < b.type;
}

//----------------------------------------------------------------------------
ExampleEditor::ExampleEditor(AudioEffect *effect):
VSTGLEditor(effect, Antialias4x),
Timer(30), //30ms == ~30fps?
thing(0.0f)
{
	//Set the opengl context's size - This must be called here!
	setRect(0, 0, 900, 750);

	mGUI = new GLGUI(m_hInstance);
	mGUI->init();
	
	//mSlider = mGUI->NewSlider(60, 185, 120, 0, 100);
	int x = 400;
	exchangeCB = new ExchangeCallback(this);
	moveUpCB = new MoveUpCallback(this);
	moveDnCB = new MoveDnCallback(this);
	exchangeButton = mGUI->NewButton(x+190, 75-25/2, 40, 25, "<==>", exchangeCB);
	moveUpButton = mGUI->NewButton(x+240+180+15, 75-25/2-40, 60, 25, "MoveUp", moveUpCB);
	moveDnButton = mGUI->NewButton(x+240+180+15, 75-25/2, 60, 25, "MoveDown", moveDnCB);
	beingUsedEffectsList = mGUI->NewList(x+240, 0, 180, 150, &myListCB);
	unusedEffectsList = mGUI->NewTList(x-100, 0, 330-50, 150, &myTLCB);
	char temp[123];
	mEffectNames.push_back(EffectName(EffLinealEQ, "Lineal EQ"));
	mEffectNames.push_back(EffectName(EffCompressor,"Compressor"));
	mEffectNames.push_back(EffectName(EffEcho,"Echo"));
	mEffectNames.push_back(EffectName(EffChorus, "Chorus"));
	mEffectNames.push_back(EffectName(EffFlange, "Flange"));
	mEffectNames.push_back(EffectName(EffPhaser, "Phaser"));
	mEffectNames.push_back(EffectName(EffReverb, "Reverb"));
	mEffectNames.push_back(EffectName(EffParametricEQ, "Parametric EQ"));
	mEffectNames.push_back(EffectName(EffParametricEQ2, "Parametric EQ2"));
	mEffectNames.push_back(EffectName(EffParametricEQ3, "Parametric EQ3"));
	mEffectNames.push_back(EffectName(EffWahWah, "WahWah"));
	mEffectNames.push_back(EffectName(EffAlienWah, "AlienWah"));
	mEffectNames.push_back(EffectName(EffPan, "Pan"));
	mEffectNames.push_back(EffectName(EffDistortion, "Distortion"));
	mEffectNames.push_back(EffectName(EffHarmonizer, "Harmonizer"));
	mEffectNames.push_back(EffectName(EffMusicDelay, "Musical Delay"));
	mEffectNames.push_back(EffectName(EffGate, "Noise Gate"));
	mEffectNames.push_back(EffectName(EffNewDist, "Derelict"));
	mEffectNames.push_back(EffectName(EffAnalogPhaser, "Analog Phaser"));
	mEffectNames.push_back(EffectName(EffValve, "Valve"));
	mEffectNames.push_back(EffectName(EffDualFlange, "Dual Flange"));
	mEffectNames.push_back(EffectName(EffRing, "Ring"));
	mEffectNames.push_back(EffectName(EffExciter, "Exciter"));
	mEffectNames.push_back(EffectName(EffMBDist, "DistBand"));
	mEffectNames.push_back(EffectName(EffArpie, "Arpie"));
	mEffectNames.push_back(EffectName(EffExpander, "Expander"));
	mEffectNames.push_back(EffectName(EffShuffle, "Shuffle"));
	mEffectNames.push_back(EffectName(EffSynthfilter, "Synthfilter"));
	mEffectNames.push_back(EffectName(EffConvolotron, "Convolotron"));
	mEffectNames.push_back(EffectName(EffReverbtron, "Reverbtron"));
	mEffectNames.push_back(EffectName(EffEchotron, "Echotron"));
	mEffectNames.push_back(EffectName(EffMBVvol, "VaryBand"));
	mEffectNames.push_back(EffectName(EffRyanWah, "MutroMojo"));
	// MVVvol VaryBand
	// RyanWah MutroMojo
	mPanels.resize(10);
	mBuiltPanels.resize(10);
	mEffectOn.resize(10);
	mTotalEffectOn = false;
	for(int i=0; i<10; ++i)
	{
		mPanels[i] = nullptr;
		mBuiltPanels[i] = EffNone;
		mEffectOn[i] = false;
	}

	mEQ1Panel = new LinealEQNS::LinealEQ(mGUI,(VstPlugin*)effect);
	mDistPanel = new DistorsionPanelNS::DistorsionPanel(mGUI,(VstPlugin*)effect);
	mCompressorPanel = new CompressorNS::CompressorPanel(mGUI,(VstPlugin*)effect);
	mEchoPanel = new EchoNS::EchoPanel(mGUI,(VstPlugin*)effect);

	sort(mEffectNames.begin(), mEffectNames.end(), CompEff);
	for(int i=0; i< 10; ++i)
	{
		CreateEffectPanel(mEffectNames[i].type, i);
	}

	for(int i=0;i<mUsingEffectList.size();++i)
	{
		sprintf(temp, "%s", mUsingEffectList[i].name.c_str());
		mGUI->AddToList(beingUsedEffectsList, temp);
	}

	vector<EffectName> unusedEffectList;
	for(int i=0; i< mEffectNames.size(); ++i)
	{
		bool found = false;
		for(int j=0; j < mUsingEffectList.size(); ++j)
		{
			if(mUsingEffectList[j].type == mEffectNames[i].type)
			{
				found = true;
				break;
			}
		}
		if(!found)
		{
			unusedEffectList.push_back(mEffectNames[i]);
		}
	}
	sort(unusedEffectList.begin(), unusedEffectList.end(), CompEff);
	for(int i=0;i<unusedEffectList.size();++i)
	{
		sprintf(temp, "%s", unusedEffectList[i].name.c_str());
		mGUI->AddToTList(unusedEffectsList, temp);
	}

	vector<MyEffectOnOff*> mCBOnOffs;
	cbOnOff = new MyTotalEffectOnOff(this);
	mTotalOnOffButton = mGUI->NewOnOffButton(x+240+180+15, 150/2-25/2+40, 50, 25, "On", cbOnOff);
	for(int i=0;i<5;++i)
	{
		mCBOnOffs.push_back(new MyEffectOnOff(this, i));
		int b = mGUI->NewOnOffButton(i*180, 13+150, 50, 20, "On", mCBOnOffs[i]);
		mOnOffButtons[i] = b;
	}
	for(int i=5;i<10;++i)
	{
		mCBOnOffs.push_back(new MyEffectOnOff(this, i));
		int b = mGUI->NewOnOffButton((i-5)*180, 13+150+300, 50, 20, "On", mCBOnOffs[i]);
		mOnOffButtons[i] = b;
	}

	
// 이펙트 온/오프를 만들고 리스트에서 추가/변경을 하게 한다.
	//for(int i=3;i<20;++i)
//		mEQ1Panels.push_back(new LinealEQNS::LinealEQ(mGUI,(VstPlugin*)effect, i));

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
		QuadOptionBorder opEff(i*180,750-300-300,180,300,  255, 128, 64,255, 128,64,32,255);
		mGUI->DrawQuadBorder(opEff);
	}
	for(int i=0;i<5;++i)
	{
		QuadOptionBorder opEff(i*180,750-300,180,300,  255, 128, 64,255, 128,64,32,255);
		mGUI->DrawQuadBorder(opEff);
	}

	mGUI->DrawElements();
	
	for(int i=0; i<10; ++i)
	{
		switch(mBuiltPanels[i])
		{
		case EffNone:
			break;
		case EffLinealEQ:
			if(mEQ1Panel)
				mEQ1Panel->DrawText();
			break;
		case EffDistortion:
			if(mDistPanel)
				mDistPanel->DrawText();
			break;
		case EffCompressor:
			if(mCompressorPanel)
				mCompressorPanel->DrawText();
			break;
		case EffEcho:
			if(mEchoPanel)
				mEchoPanel->DrawText();
			break;
		default:
			if(mPanels[i])
				mPanels[i]->DrawText();
			break;

		}
	}
	//mDistPanel->DrawText();
	/*mWahPanel->DrawText();
	mPEQPanel->DrawText();
	mReverbPanel->DrawText();
	mEQ1Panel->DrawText();
	mEchoPanel->DrawText();
	mTestPanel->DrawText();
	mPhaserPanel->DrawText();
	mAWahPanel->DrawText();
	mPanPanel->DrawText();
	for(int i=0;i<17;++i)
	{
		//mEQ1Panels[i]->DrawText();
	}
	mCompressorPanel->DrawText();*/
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
	//refreshGraphics();
}
void ExampleEditor::idle()
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
	mPopupList = new TabbedListBox(GetNewHandle(), this, 0, 0, 300, 150);
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
//--------
MoveUpCallback::MoveUpCallback(ExampleEditor *editor)
	:mEditor(editor), ButtonCallback()
{
}
void MoveUpCallback::OnClick()
{
	ListBox *list = (ListBox*)(mEditor->mGUI->GetElement(mEditor->beingUsedEffectsList));
	int prevIdx = list->selected;
	int newIdx = list->selected-1;
	if(newIdx >= 0)
	{
		EffNameType prevType = mEditor->mBuiltPanels[prevIdx];
		EffNameType newType = mEditor->mBuiltPanels[newIdx];
		int prevPresetIdx = mEditor->GetEffectPreset(prevIdx);
		int newPresetIdx = mEditor->GetEffectPreset(newIdx);
		mEditor->DeleteEffectPanel(prevIdx);
		mEditor->DeleteEffectPanel(newIdx);
		mEditor->CreateEffectPanel(newType, prevIdx, true, newPresetIdx);
		mEditor->CreateEffectPanel(prevType, newIdx, true, prevPresetIdx);
		
		bool backup = mEditor->mEffectOn[prevIdx];
		mEditor->mEffectOn[prevIdx] = mEditor->mEffectOn[newIdx];
		((OnOffButton*)(mEditor->mGUI->GetElement(mEditor->mOnOffButtons[prevIdx])))->mOn = mEditor->mEffectOn[newIdx];
		mEditor->mEffectOn[newIdx] = backup;
		((OnOffButton*)(mEditor->mGUI->GetElement(mEditor->mOnOffButtons[newIdx])))->mOn = backup;
		list->MoveUpSelection();
	}
	
}

MoveDnCallback::MoveDnCallback(ExampleEditor *editor)
	:mEditor(editor), ButtonCallback()
{
}
void MoveDnCallback::OnClick()
{
	ListBox *list = (ListBox*)(mEditor->mGUI->GetElement(mEditor->beingUsedEffectsList));
	if(list->selected == -1) return;
	int prevIdx = list->selected;
	int newIdx = list->selected+1;
	if(newIdx < 10)
	{
		EffNameType prevType = mEditor->mBuiltPanels[prevIdx];
		EffNameType newType = mEditor->mBuiltPanels[newIdx];
		int prevPresetIdx = mEditor->GetEffectPreset(prevIdx);
		int newPresetIdx = mEditor->GetEffectPreset(newIdx);
		mEditor->DeleteEffectPanel(prevIdx);
		mEditor->DeleteEffectPanel(newIdx);
		mEditor->CreateEffectPanel(newType, prevIdx, true, newPresetIdx);
		mEditor->CreateEffectPanel(prevType, newIdx, true, prevPresetIdx);
		bool backup = mEditor->mEffectOn[prevIdx];
		mEditor->mEffectOn[prevIdx] = mEditor->mEffectOn[newIdx];
		((OnOffButton*)(mEditor->mGUI->GetElement(mEditor->mOnOffButtons[prevIdx])))->mOn = mEditor->mEffectOn[newIdx];
		mEditor->mEffectOn[newIdx] = backup;
		((OnOffButton*)(mEditor->mGUI->GetElement(mEditor->mOnOffButtons[newIdx])))->mOn = backup;
		list->MoveDnSelection();
	}


}

ExchangeCallback::ExchangeCallback(ExampleEditor *editor)
	:mEditor(editor), ButtonCallback()
{
}
void ExchangeCallback::OnClick()
{
	ListBox *list = (ListBox*)(mEditor->mGUI->GetElement(mEditor->beingUsedEffectsList));
	TabbedListBox *list2 = (TabbedListBox*)(mEditor->mGUI->GetElement(mEditor->unusedEffectsList));
	if(list->selected != -1 && list2->selected != -1)
	{
		EffNameType typeLeft;
		EffNameType typeRight;
		string strLeft = list2->mStrs[list2->selected];
		string strRight = list->mStrs[list->selected];
		for(int i=0; i< mEditor->mEffectNames.size(); ++i)
		{
			if(mEditor->mEffectNames[i].name == strLeft)
			{
				typeLeft = mEditor->mEffectNames[i].type;
			}
			if(mEditor->mEffectNames[i].name == strRight)
			{
				typeRight = mEditor->mEffectNames[i].type;
			}
		}
		mEditor->DeleteEffectPanel(list->selected);
		mEditor->CreateEffectPanel(typeLeft, list->selected);
		list->Add(list2->mStrs[list2->selected], list->selected);
		string backup = list->mStrs[list->selected+1];
		list->Delete(list->selected+1);
		//list2->selected = -1;
		list2->mStrs.clear();
		//list2->curPage = 0;

		vector<EffectName> unusedEffectList;
		for(int i=0; i< mEditor->mEffectNames.size(); ++i)
		{
			bool found = false;
			for(int j=0; j < mEditor->mUsingEffectList.size(); ++j)
			{
				if(mEditor->mUsingEffectList[j].type == mEditor->mEffectNames[i].type)
				{
					found = true;
					break;
				}
			}
			if(!found)
			{
				unusedEffectList.push_back(mEditor->mEffectNames[i]);
			}
		}

		sort(unusedEffectList.begin(), unusedEffectList.end(), CompEff);
		for(int i=0;i<unusedEffectList.size(); ++i)
		{
			list2->Add(unusedEffectList[i].name);
		}
	}
}



void ExampleEditor::CreateEffectPanel(EffNameType type, int whereis, bool loadPrev, int prevIdx)
{

	int iii;
	
	vector<string> presetTexts;
	vector<string> lfoTypeStrs;


	int *real;
	int *print;



	switch(type)
	{
	case EffLinealEQ:
		//mEQ1Panel = new LinealEQNS::LinealEQ(mGUI,(VstPlugin*)effect, whereis);
		//mDistPanel = new DistorsionPanelNS::DistorsionPanel(mGUI,(VstPlugin*)effect, whereis);
		//mCompressorPanel = new CompressorNS::CompressorPanel(mGUI,(VstPlugin*)effect, whereis);
		//mEchoPanel = new EchoNS::EchoPanel(mGUI,(VstPlugin*)effect, whereis);
		mEQ1Panel->Create(whereis);
		if(loadPrev)
			mEQ1Panel->LoadPreset(prevIdx);
		else
			mEQ1Panel->LoadDefault();
		break;
	case EffDistortion:
		//mDistPanel = new DistorsionPanelNS::DistorsionPanel(mGUI,(VstPlugin*)effect, whereis);
		//mCompressorPanel = new CompressorNS::CompressorPanel(mGUI,(VstPlugin*)effect, whereis);
		//mEchoPanel = new EchoNS::EchoPanel(mGUI,(VstPlugin*)effect, whereis);
		mDistPanel->Create(whereis);
		if(loadPrev)
			mDistPanel->LoadPreset(prevIdx);
		else
			mDistPanel->SetPreset(0);
		break;
	case EffCompressor:
		//mCompressorPanel = new CompressorNS::CompressorPanel(mGUI,(VstPlugin*)effect, whereis);
		//mEchoPanel = new EchoNS::EchoPanel(mGUI,(VstPlugin*)effect, whereis);
		mCompressorPanel->Create(whereis);
		if(loadPrev)
			mCompressorPanel->LoadPreset(prevIdx);
		else
			mCompressorPanel->SetPreset(0);
		break;
	case EffEcho:
		mEchoPanel->Create(whereis);
		//mEchoPanel = new EchoNS::EchoPanel(mGUI,(VstPlugin*)effect, whereis);
		if(loadPrev)
			mEchoPanel->LoadPreset(prevIdx);
		else
			mEchoPanel->SetPreset(0);
		break;
	case EffChorus:
	{
		const int CHORUS_PRESET_SIZE = 12;
		const int CHORUS_NUM_PRESETS = 10;
		int chorus_presets[] = {
			//Chorus1
			64, 64, 33, 0, 0, 90, 40, 85, 64, 119, 0, 0,
			//Chorus2
			64, 64, 17, 0, 0, 98, 56, 90, 64, 16, 0, 0,
			//Chorus3
			64, 64, 7, 0, 1, 42, 97, 95, 90, 127, 0, 0,
			//Celeste1
			64, 64, 1, 0, 0, 42, 115, 18, 90, 127, 0, 0,
			//Celeste2
			64, 64, 7, 117, 0, 50, 115, 9, 31, 127, 0, 1,
			//Flange1
			64, 64, 39, 0, 0, 60, 23, 3, 62, 0, 0, 0,
			//Flange2
			64, 64, 9, 34, 1, 40, 35, 3, 109, 0, 0, 0,
			//Flange3
			64, 64, 31, 34, 1, 94, 35, 3, 54, 0, 0, 1,
			//Flange4
			64, 64, 14, 0, 1, 62, 12, 19, 97, 0, 0, 0,
			//Flange5
			64, 64, 34, 105, 0, 24, 39, 19, 17, 0, 0, 1

		};
	

		int ChorusReal[] = { // Chorus/Flange! 두개를 하나로 합쳐쓴다.? 아니다. 코러스랑 플랜지를 중복해야한다.
		//case 0:
		//setvolume (value); Wet Dry
			0, 127,
		//case 1:
		//setpanning (value); Pan
			0, 127,
		//case 2:
		//lfo.Pfreq = value; Tempo
			1, 600,
		//case 3:
		//lfo.Prandomness = value; Rnd
			0, 127,
		//case 4:
		//lfo.PLFOtype = value; LFOType
			0, 9,  // type value
			/*
			Sine
			Tri
			RampUp
			RampDown
			ZigZag
			M.Sqare
			M.Saw
			L. Fractal
			L. Fractal XY
			S/H Random*/
		//case 5:
		//lfo.Pstereo = value; St.df
			0, 127,
		//case 6:
		//setdepth (value); // Depth
			0, 127,
		//case 7:
		//setdelay (value); // Delay
			0, 127,
		//case 8:
		//setfb (value); // Fb.
			0, 127,
		//case 9:
		//setlrcross (value); // L/R.Cr
			0, 127,
		//case 10:
			//Pflangemode = value;
			0, 1, // Boolean: Chorus/Flange
		//case 11:
		//Poutsub = value; // Subtract
			0, 1, // Boolean
		//case 12:
		//awesome_mode = value; // Intense
			0, 1,

		};
		int ChorusPrint[] = {
			-64, 63, // 0
			-64, 63, // 1
			1, 600, // 2
			0, 127, // 3
			0, 9, // 4
			0, 127, // 5
			0, 127, // 6
			0, 127, // 7
			0, 127, // 8
			-64, 63, // 9
			0, 1, // 10
			0, 1, // 11
			0, 1, // 12
		};

		presetTexts.clear();
		presetTexts.push_back("Chorus1");
		presetTexts.push_back("Chorus2");
		presetTexts.push_back("Chorus3");
		presetTexts.push_back("Celeste1");
		presetTexts.push_back("Celeste2");
		presetTexts.push_back("Flange1");
		presetTexts.push_back("Flange2");
		presetTexts.push_back("Flange3");
		presetTexts.push_back("Flange4");
		presetTexts.push_back("Flange5");
		mPanels[whereis] = new PanelNS::Panel(mGUI, (VstPlugin*)effect, ((VstPlugin*)effect)->mEffChorus, "Chorus", whereis, chorus_presets, CHORUS_PRESET_SIZE, CHORUS_NUM_PRESETS, presetTexts);

		mPanels[whereis]->AddParamData(PanelNS::Data(0, 0, 127, -64, 63, "Wet/Dry", PanelNS::Slider));
		mPanels[whereis]->AddParamData(PanelNS::Data(1, 0, 127, -64, 63, "Pan", PanelNS::Slider));
		mPanels[whereis]->AddParamData(PanelNS::Data(2, 1, 600, 1, 600, "Tempo", PanelNS::Slider));
		mPanels[whereis]->AddParamData(PanelNS::Data(3, 0, 127, 0, 127, "RND", PanelNS::Slider));
		lfoTypeStrs.clear();
		lfoTypeStrs.push_back("Sine");
		lfoTypeStrs.push_back("Tri");
		lfoTypeStrs.push_back("RampUp");
		lfoTypeStrs.push_back("RampDn");
		lfoTypeStrs.push_back("ZigZag");
		lfoTypeStrs.push_back("M.Sqare");
		lfoTypeStrs.push_back("M.Saw");
		lfoTypeStrs.push_back("L.Fract");
		lfoTypeStrs.push_back("L.FractXY");
		lfoTypeStrs.push_back("S/H Rnd");
		mPanels[whereis]->AddParamData(PanelNS::Data(4, 0, 9, 0, 9, "LFOType", PanelNS::Selection, false, false, lfoTypeStrs));
		mPanels[whereis]->AddParamData(PanelNS::Data(11, 0, 1, 0, 1, "Subtract", PanelNS::OnOff));
		mPanels[whereis]->AddParamData(PanelNS::Data(12, 0, 1, 0, 1, "Intense", PanelNS::OnOff, false, true));

		mPanels[whereis]->AddParamData(PanelNS::Data(5, 0, 127, 0, 127, "St.df", PanelNS::Slider));
		mPanels[whereis]->AddParamData(PanelNS::Data(6, 0, 127, 0, 127, "Depth", PanelNS::Slider));
		mPanels[whereis]->AddParamData(PanelNS::Data(7, 0, 127, 0, 127, "Delay", PanelNS::Slider));
		mPanels[whereis]->AddParamData(PanelNS::Data(8, 0, 127, 0, 127, "Fb", PanelNS::Slider));
		mPanels[whereis]->AddParamData(PanelNS::Data(9, 0, 127, -63, 64, "L/R.Cr", PanelNS::Slider));

		if(loadPrev)
			mPanels[whereis]->LoadPreset(prevIdx);
		else
			mPanels[whereis]->SetPreset(0);
	}
		break;
	case EffFlange:
	{
		const int FCHORUS_PRESET_SIZE = 12;
		const int FCHORUS_NUM_PRESETS = 10;
		int fchorus_presets[] = {
			//Chorus1
			64, 64, 33, 0, 0, 90, 40, 85, 64, 119, 1, 0,
			//Chorus2
			64, 64, 17, 0, 0, 98, 56, 90, 64, 16, 1, 0,
			//Chorus3
			64, 64, 7, 0, 1, 42, 97, 95, 90, 127, 1, 0,
			//Celeste1
			64, 64, 1, 0, 0, 42, 115, 18, 90, 127, 1, 0,
			//Celeste2
			64, 64, 7, 117, 0, 50, 115, 9, 31, 127, 1, 1,
			//Flange1
			64, 64, 39, 0, 0, 60, 23, 3, 62, 0, 1, 0,
			//Flange2
			64, 64, 9, 34, 1, 40, 35, 3, 109, 0, 1, 0,
			//Flange3
			64, 64, 31, 34, 1, 94, 35, 3, 54, 0, 1, 1,
			//Flange4
			64, 64, 14, 0, 1, 62, 12, 19, 97, 0, 1, 0,
			//Flange5
			64, 64, 34, 105, 0, 24, 39, 19, 17, 0, 1, 1

		};
	

		int FChorusReal[] = { // Chorus/Flange! 두개를 하나로 합쳐쓴다.? 아니다. 코러스랑 플랜지를 중복해야한다.
		//case 0:
		//setvolume (value); Wet Dry
			0, 127,
		//case 1:
		//setpanning (value); Pan
			0, 127,
		//case 2:
		//lfo.Pfreq = value; Tempo
			1, 600,
		//case 3:
		//lfo.Prandomness = value; Rnd
			0, 127,
		//case 4:
		//lfo.PLFOtype = value; LFOType
			0, 9,  // type value
			/*
			Sine
			Tri
			RampUp
			RampDown
			ZigZag
			M.Sqare
			M.Saw
			L. Fractal
			L. Fractal XY
			S/H Random*/
		//case 5:
		//lfo.Pstereo = value; St.df
			0, 127,
		//case 6:
		//setdepth (value); // Depth
			0, 127,
		//case 7:
		//setdelay (value); // Delay
			0, 127,
		//case 8:
		//setfb (value); // Fb.
			0, 127,
		//case 9:
		//setlrcross (value); // L/R.Cr
			0, 127,
		//case 10:
			//Pflangemode = value;
			0, 1, // Boolean: Chorus/Flange
		//case 11:
		//Poutsub = value; // Subtract
			0, 1, // Boolean
		//case 12:
		//awesome_mode = value; // Intense
			0, 1,

		};
		int FChorusPrint[] = {
			-64, 63, // 0
			-64, 63, // 1
			1, 600, // 2
			0, 127, // 3
			0, 9, // 4
			0, 127, // 5
			0, 127, // 6
			0, 127, // 7
			0, 127, // 8
			-64, 63, // 9
			0, 1, // 10
			0, 1, // 11
			0, 1, // 12
		};

		presetTexts.clear();
		presetTexts.push_back("Chorus1");
		presetTexts.push_back("Chorus2");
		presetTexts.push_back("Chorus3");
		presetTexts.push_back("Celeste1");
		presetTexts.push_back("Celeste2");
		presetTexts.push_back("Flange1");
		presetTexts.push_back("Flange2");
		presetTexts.push_back("Flange3");
		presetTexts.push_back("Flange4");
		presetTexts.push_back("Flange5");
		mPanels[whereis] = new PanelNS::Panel(mGUI, (VstPlugin*)effect, ((VstPlugin*)effect)->mEffFlange, "Flange", whereis, fchorus_presets, FCHORUS_PRESET_SIZE, FCHORUS_NUM_PRESETS, presetTexts);

		mPanels[whereis]->AddParamData(PanelNS::Data(0, 0, 127, -64, 63, "Wet/Dry", PanelNS::Slider));
		mPanels[whereis]->AddParamData(PanelNS::Data(1, 0, 127, -64, 63, "Pan", PanelNS::Slider));
		mPanels[whereis]->AddParamData(PanelNS::Data(2, 1, 600, 1, 600, "Tempo", PanelNS::Slider));
		mPanels[whereis]->AddParamData(PanelNS::Data(3, 0, 127, 0, 127, "RND", PanelNS::Slider));
		lfoTypeStrs.clear();
		lfoTypeStrs.push_back("Sine");
		lfoTypeStrs.push_back("Tri");
		lfoTypeStrs.push_back("RampUp");
		lfoTypeStrs.push_back("RampDn");
		lfoTypeStrs.push_back("ZigZag");
		lfoTypeStrs.push_back("M.Sqare");
		lfoTypeStrs.push_back("M.Saw");
		lfoTypeStrs.push_back("L.Fract");
		lfoTypeStrs.push_back("L.FractXY");
		lfoTypeStrs.push_back("S/H Rnd");
		mPanels[whereis]->AddParamData(PanelNS::Data(4, 0, 9, 0, 9, "LFOType", PanelNS::Selection, false, false, lfoTypeStrs));
		mPanels[whereis]->AddParamData(PanelNS::Data(11, 0, 1, 0, 1, "Subtract", PanelNS::OnOff));
		mPanels[whereis]->AddParamData(PanelNS::Data(12, 0, 1, 0, 1, "Intense", PanelNS::OnOff, false, true));

		mPanels[whereis]->AddParamData(PanelNS::Data(5, 0, 127, 0, 127, "St.df", PanelNS::Slider));
		mPanels[whereis]->AddParamData(PanelNS::Data(6, 0, 127, 0, 127, "Depth", PanelNS::Slider));
		mPanels[whereis]->AddParamData(PanelNS::Data(7, 0, 127, 0, 127, "Delay", PanelNS::Slider));
		mPanels[whereis]->AddParamData(PanelNS::Data(8, 0, 127, 0, 127, "Fb", PanelNS::Slider));
		mPanels[whereis]->AddParamData(PanelNS::Data(9, 0, 127, -63, 64, "L/R.Cr", PanelNS::Slider));

		if(loadPrev)
			mPanels[whereis]->LoadPreset(prevIdx);
		else
			mPanels[whereis]->SetPreset(0);
	}
		break;
	case EffPhaser:
	{
		const int PHASER_PRESET_SIZE = 12;
		const int PHASER_NUM_PRESETS = 6;
		int phaser_presets[] = {
			//Phaser1
			64, 64, 11, 0, 0, 64, 110, 64, 1, 0, 0, 20,
			//Phaser2
			64, 64, 10, 0, 0, 88, 40, 64, 3, 0, 0, 20,
			//Phaser3
			64, 64, 8, 0, 0, 66, 68, 107, 2, 0, 0, 20,
			//Phaser4
			39, 64, 1, 0, 0, 66, 67, 10, 5, 0, 1, 20,
			//Phaser5
			64, 64, 1, 0, 1, 110, 67, 78, 10, 0, 0, 20,
			//Phaser6
			64, 64, 31, 100, 0, 58, 37, 78, 3, 0, 0, 20
		};
		int PhaserReal[] = {
	//   case 0:
			0,127,
	//      setvolume (value);
		//case 1:
			0,127,
	//      setpanning (value);
	//    break;
		//case 2:
			1,600,
			//lfo.Pfreq = value;
			//lfo.updateparams ();
			//break;
			//case 3:
			0,127,
				//lfo.Prandomness = value;
				//lfo.updateparams ();
				//break;
			//case 4:
	//lfo.PLFOtype = value; LFOType
			0, 9,  // type value
			/*
			Sine
			Tri
			RampUp
			RampDown
			ZigZag
			M.Sqare
			M.Saw
			L. Fractal
			L. Fractal XY
			S/H Random*/
			//case 5:
			0,127,
				//lfo.Pstereo = value;
				//lfo.updateparams ();
				//break;
			//case 6:
			0,127,
				//setdepth (value);
				//break;
			//case 7:
			0,127,
				//setfb (value);
				//break;
			//case 8:
			1,12,
				//setstages (value);
				//break;
			//case 9:
			0,127,
				//setlrcross (value);
				//break;
			//case 10:
			0,1, // Boolean
				//if (value > 1)
					//value = 1;
				//Poutsub = value;
				//break;
			//case 11:
			0,127,
				//setphase (value);
				//break;
		};
		int PhaserPrint[] = {
			-64,63, // 0
			-64,63, // 1
			1,600, // 2
			0,127, // 3
			0,9, // 4
			0,127, // 5
			0,127, //6
			0,127, //7
			1,12, // 8
			-64,63, //9
			0,1, // 10
			0,127, // 11
		};
		real = PhaserReal;
		print = PhaserPrint;
		presetTexts.clear();
		presetTexts.push_back("Phaser1");
		presetTexts.push_back("Phaser2");
		presetTexts.push_back("Phaser3");
		presetTexts.push_back("Phaser4");
		presetTexts.push_back("Phaser5");
		presetTexts.push_back("Phaser6");
		mPanels[whereis] = new PanelNS::Panel(mGUI, (VstPlugin*)effect, ((VstPlugin*)effect)->mEffPhaser, "Phaser", whereis, phaser_presets, PHASER_PRESET_SIZE, PHASER_NUM_PRESETS, presetTexts);

		iii=0;
		mPanels[whereis]->AddParamData(PanelNS::Data(iii, real[iii*2], real[iii*2+1], print[iii*2], print[iii*2+1], "Wet/Dry", PanelNS::Slider));
		iii = 1;
		mPanels[whereis]->AddParamData(PanelNS::Data(iii, real[iii*2], real[iii*2+1], print[iii*2], print[iii*2+1], "Pan", PanelNS::Slider));
		iii = 2;
		mPanels[whereis]->AddParamData(PanelNS::Data(iii, real[iii*2], real[iii*2+1], print[iii*2], print[iii*2+1], "Tempo", PanelNS::Slider));
		iii = 3;
		mPanels[whereis]->AddParamData(PanelNS::Data(iii, real[iii*2], real[iii*2+1], print[iii*2], print[iii*2+1], "RND", PanelNS::Slider));
		lfoTypeStrs.clear();
		lfoTypeStrs.push_back("Sine");
		lfoTypeStrs.push_back("Tri");
		lfoTypeStrs.push_back("RampUp");
		lfoTypeStrs.push_back("RampDn");
		lfoTypeStrs.push_back("ZigZag");
		lfoTypeStrs.push_back("M.Sqare");
		lfoTypeStrs.push_back("M.Saw");
		lfoTypeStrs.push_back("L.Fract");
		lfoTypeStrs.push_back("L.FractXY");
		lfoTypeStrs.push_back("S/H Rnd");
		iii=4;
		mPanels[whereis]->AddParamData(PanelNS::Data(iii, real[iii*2], real[iii*2+1], print[iii*2], print[iii*2+1],  "LFOType", PanelNS::Selection, false, false, lfoTypeStrs));
		iii=10;
		mPanels[whereis]->AddParamData(PanelNS::Data(iii, real[iii*2], real[iii*2+1], print[iii*2], print[iii*2+1], "Subtract", PanelNS::OnOff));
		iii=11;
		mPanels[whereis]->AddParamData(PanelNS::Data(iii, real[iii*2], real[iii*2+1], print[iii*2], print[iii*2+1], "Phase", PanelNS::Slider));
		iii=5;
		mPanels[whereis]->AddParamData(PanelNS::Data(iii, real[iii*2], real[iii*2+1], print[iii*2], print[iii*2+1], "St.df", PanelNS::Slider));
		iii=6;
		mPanels[whereis]->AddParamData(PanelNS::Data(iii, real[iii*2], real[iii*2+1], print[iii*2], print[iii*2+1], "Depth", PanelNS::Slider));
		iii=7;
		mPanels[whereis]->AddParamData(PanelNS::Data(iii, real[iii*2], real[iii*2+1], print[iii*2], print[iii*2+1], "Fb", PanelNS::Slider));
		iii=8;
		mPanels[whereis]->AddParamData(PanelNS::Data(iii, real[iii*2], real[iii*2+1], print[iii*2], print[iii*2+1], "Stages", PanelNS::Slider));
		iii=9;
		mPanels[whereis]->AddParamData(PanelNS::Data(iii, real[iii*2], real[iii*2+1], print[iii*2], print[iii*2+1], "L/R.Cr", PanelNS::Slider));

		if(loadPrev)
			mPanels[whereis]->LoadPreset(prevIdx);
		else
			mPanels[whereis]->SetPreset(0);
	}
		break;
	case EffReverb:
	{
		int ReverbReal[] = {
	//case 0:
			0,127,
			
		//setvolume (value);
		//break;
	//case 1:
			0,127,
		//setpan (value);
		//break;
	//case 2:
			0,127,
		//settime (value);
		//break;
	//case 3:
			0,127,
		//setidelay (value);
		//break;
	//case 4:
			0,127,
		//setidelayfb (value);
		//break;
	//      case 5: setrdelay(value); deleted
	//              break;
			0,0,
	//      case 6: seterbalance(value); deleted
	//              break;
			0,0,
	//case 7:
			47,171, // 20~26000, 이 값을 GetFreqByRealMinMax로 변환하면 주파수가 나온다.
		//setlpf (value);
		//break;
	//case 8:
			47,166, // 20~20000
		//sethpf (value);
		//break;
	//case 9:
			0,127,
		//setlohidamp (value);
		//break;
	//case 10:
			0, 1, // : Selection:
				//Freeverb
				//Random
		//settype (value);
		//break;
	//case 11:
			0,127,
		//setroomsize (value);
		//break;
			
		};
		int ReverbPrint[] = {
			-64,63, // 0
			-64,63, // 1
			0,127, // 2
			0,127, // 3
			0,127, // 4
			0,0, // 5
			0,0, // 6
			0,100, // 7
			0,100, // 8
			0,127, // 9
			0,1, // 10 
			0,127, // 11
		};
		const int REVERB_PRESET_SIZE = 12;
		const int REVERB_NUM_PRESETS = 13;
		int reverb_presets[] = {
			//Cathedral1
			80, 64, 63, 24, 0, 0, 0, 4002, 27, 83, 1, 64,
			//Cathedral2
			80, 64, 69, 35, 0, 0, 0, 25040, 21, 71, 0, 64,
			//Cathedral3
			80, 64, 69, 24, 0, 0, 0, 25040, 2417, 78, 1, 85,
			//Hall1
			90, 64, 51, 10, 0, 0, 0, 25040, 81, 78, 1, 64,
			//Hall2
			90, 64, 53, 20, 0, 0, 0, 25040, 2417, 71, 1, 64,
			//Room1
			100, 64, 33, 0, 0, 0, 0, 25040, 21, 106, 0, 30,
			//Room2
			100, 64, 21, 26, 0, 0, 0, 1223, 21, 77, 1, 45,
			//Basement
			110, 64, 14, 0, 0, 0, 0, 25040, 27, 71, 0, 25,
			//Tunnel
			85, 80, 84, 20, 42, 0, 0, 652, 21, 78, 1, 105,
			//Echoed1
			95, 64, 26, 60, 71, 0, 0, 14722, 21, 64, 1, 64,
			//Echoed2
			90, 64, 40, 88, 71, 0, 0, 14722, 21, 88, 1, 64,
			//VeryLong1
			90, 64, 93, 15, 0, 0, 0, 14722, 21, 77, 0, 95,
			//VeryLong2
			90, 64, 111, 30, 0, 0, 0, 14722, 5058, 74, 1, 80
		};
		real = ReverbReal;
		print = ReverbPrint;
		presetTexts.clear();
		presetTexts.push_back("Cathedral1");
		presetTexts.push_back("Cathedral2");
		presetTexts.push_back("Cathedral3");
		presetTexts.push_back("Hall1");
		presetTexts.push_back("Hall2");
		presetTexts.push_back("Room1");
		presetTexts.push_back("Room2");
		presetTexts.push_back("Basement");
		presetTexts.push_back("Tunnel");
		presetTexts.push_back("Echoed1");
		presetTexts.push_back("Echoed2");
		presetTexts.push_back("VeryLong1");
		presetTexts.push_back("VeryLong2");
		mPanels[whereis] = new PanelNS::Panel(mGUI, (VstPlugin*)effect, ((VstPlugin*)effect)->mEffReverb, "Reverb", whereis, reverb_presets, REVERB_PRESET_SIZE, REVERB_NUM_PRESETS, presetTexts);
		iii=0;
		mPanels[whereis]->AddParamData(PanelNS::Data(iii, real[iii*2], real[iii*2+1], print[iii*2], print[iii*2+1], "Wet/Dry", PanelNS::Slider));
		iii=1;
		mPanels[whereis]->AddParamData(PanelNS::Data(iii, real[iii*2], real[iii*2+1], print[iii*2], print[iii*2+1], "Pan", PanelNS::Slider));
		iii=2;
		mPanels[whereis]->AddParamData(PanelNS::Data(iii, real[iii*2], real[iii*2+1], print[iii*2], print[iii*2+1], "Time", PanelNS::Slider));
		iii=3;
		mPanels[whereis]->AddParamData(PanelNS::Data(iii, real[iii*2], real[iii*2+1], print[iii*2], print[iii*2+1], "I.Del", PanelNS::Slider));
		iii=4;
		mPanels[whereis]->AddParamData(PanelNS::Data(iii, real[iii*2], real[iii*2+1], print[iii*2], print[iii*2+1], "Del.E/R", PanelNS::Slider));
		vector<string> reverbType;
		reverbType.push_back("Freeverb");
		reverbType.push_back("Random");
		iii=10;
		mPanels[whereis]->AddParamData(PanelNS::Data(iii, real[iii*2], real[iii*2+1], print[iii*2], print[iii*2+1],  "Type", PanelNS::Selection, false, false, reverbType));
		iii=11;
		mPanels[whereis]->AddParamData(PanelNS::Data(iii, real[iii*2], real[iii*2+1], print[iii*2], print[iii*2+1], "R.Size", PanelNS::Slider));
		iii=7;
		mPanels[whereis]->AddParamData(PanelNS::Data(iii, real[iii*2], real[iii*2+1], print[iii*2], print[iii*2+1], "LPF", PanelNS::Slider, true ));
		iii=8;
		mPanels[whereis]->AddParamData(PanelNS::Data(iii, real[iii*2], real[iii*2+1], print[iii*2], print[iii*2+1], "HPF", PanelNS::Slider, true));
		iii=9;
		mPanels[whereis]->AddParamData(PanelNS::Data(iii, real[iii*2], real[iii*2+1], print[iii*2], print[iii*2+1], "Damp", PanelNS::Slider));
		/*iii=5;
		mPanels[whereis]->AddParamData(PanelNS::Data(iii, real[iii*2], real[iii*2+1], print[iii*2], print[iii*2+1], "Unused", PanelNS::Slider), true);
		iii=6;
		mPanels[whereis]->AddParamData(PanelNS::Data(iii, real[iii*2], real[iii*2+1], print[iii*2], print[iii*2+1], "Unused", PanelNS::Slider), true);
		*/
		if(loadPrev)
			mPanels[whereis]->LoadPreset(prevIdx);
		else
			mPanels[whereis]->SetPreset(0);
	}
		break;
	case EffParametricEQ:
	{
		int PEQPreset[] = {
			127, 30,64,64, 900,64,64, 7000,64,64
		};
		int ParametricEQReal[] = {
			0,127, // 0 Gain
			47, 115, // 20-1000Hz Low F.
			0,127, // Low G.
			0,127, // Low Q
			111,151, // 800~8000 Mid F.
			0,127, // Mid G.
			0,127, // Mid Q
			145,171, // 6000~26000 High F.
			0,127, // High G.
			0,127, // High Q
		};
		int ParametricEQPrint[] = {
			0,127, // 0
			0,100, // 1
			-64,63, // 2
			-64,63, // 3
			0,100, // 4
			-64,63, // 5
			-64,63, // 6
			0,100, // 7
			-64,63, // 8
			-64,63, // 9
		};

		real = ParametricEQReal;
		print = ParametricEQPrint;
		presetTexts.clear();
		presetTexts.push_back("Default");
		mPanels[whereis] = new PanelNS::Panel(mGUI, (VstPlugin*)effect, ((VstPlugin*)effect)->mEffEQ2, "Parametric EQ", whereis, PEQPreset, 10, 1, presetTexts, true);

		iii = 0;
		mPanels[whereis]->AddParamData(PanelNS::Data(0, real[iii*2], real[iii*2+1], print[iii*2], print[iii*2+1], "Gain", PanelNS::Slider, false, false, vector<string>(), 0));

		iii = 1;
		mPanels[whereis]->AddParamData(PanelNS::Data(11, real[iii*2], real[iii*2+1], print[iii*2], print[iii*2+1], "Low F.", PanelNS::Slider, true, false, vector<string>(), 1));
		iii = 2;
		mPanels[whereis]->AddParamData(PanelNS::Data(12, real[iii*2], real[iii*2+1], print[iii*2], print[iii*2+1], "Low G.", PanelNS::Slider, false, false, vector<string>(), 2));
		iii = 3;
		mPanels[whereis]->AddParamData(PanelNS::Data(13, real[iii*2], real[iii*2+1], print[iii*2], print[iii*2+1], "Q", PanelNS::Slider, false, false, vector<string>(), 3));

		iii = 4;
		mPanels[whereis]->AddParamData(PanelNS::Data(11+5, real[iii*2], real[iii*2+1], print[iii*2], print[iii*2+1], "Mid F.", PanelNS::Slider, true, false, vector<string>(), 4));
		iii = 5;
		mPanels[whereis]->AddParamData(PanelNS::Data(12+5, real[iii*2], real[iii*2+1], print[iii*2], print[iii*2+1], "Mid G.", PanelNS::Slider, false, false, vector<string>(), 5));
		iii = 6;
		mPanels[whereis]->AddParamData(PanelNS::Data(13+5, real[iii*2], real[iii*2+1], print[iii*2], print[iii*2+1], "Q", PanelNS::Slider, false, false, vector<string>(), 6));

		iii = 7;
		mPanels[whereis]->AddParamData(PanelNS::Data(11+10, real[iii*2], real[iii*2+1], print[iii*2], print[iii*2+1], "High F.", PanelNS::Slider, true, false, vector<string>(), 7));
		iii = 8;
		mPanels[whereis]->AddParamData(PanelNS::Data(12+10, real[iii*2], real[iii*2+1], print[iii*2], print[iii*2+1], "High G.", PanelNS::Slider, false, false, vector<string>(), 8));
		iii = 9;
		mPanels[whereis]->AddParamData(PanelNS::Data(13+10, real[iii*2], real[iii*2+1], print[iii*2], print[iii*2+1], "Q", PanelNS::Slider, false, false, vector<string>(), 9));
		if(loadPrev)
			mPanels[whereis]->LoadPreset(prevIdx);
		else
			mPanels[whereis]->SetPreset(0);
	}
		break;
	case EffParametricEQ2:
	{
		int PEQPreset[] = {
			127, 30,64,64, 900,64,64, 7000,64,64
		};
		int ParametricEQReal[] = {
			0,127, // 0 Gain
			47, 115, // 20-1000Hz Low F.
			0,127, // Low G.
			0,127, // Low Q
			111,151, // 800~8000 Mid F.
			0,127, // Mid G.
			0,127, // Mid Q
			145,171, // 6000~26000 High F.
			0,127, // High G.
			0,127, // High Q
		};
		int ParametricEQPrint[] = {
			0,127, // 0
			0,100, // 1
			-64,63, // 2
			-64,63, // 3
			0,100, // 4
			-64,63, // 5
			-64,63, // 6
			0,100, // 7
			-64,63, // 8
			-64,63, // 9
		};

		real = ParametricEQReal;
		print = ParametricEQPrint;
		presetTexts.clear();
		presetTexts.push_back("Default");
		mPanels[whereis] = new PanelNS::Panel(mGUI, (VstPlugin*)effect, ((VstPlugin*)effect)->mEffEQ3, "Parametric EQ", whereis, PEQPreset, 10, 1, presetTexts, true);

		iii = 0;
		mPanels[whereis]->AddParamData(PanelNS::Data(0, real[iii*2], real[iii*2+1], print[iii*2], print[iii*2+1], "Gain", PanelNS::Slider, false, false, vector<string>(), 0));

		iii = 1;
		mPanels[whereis]->AddParamData(PanelNS::Data(11, real[iii*2], real[iii*2+1], print[iii*2], print[iii*2+1], "Low F.", PanelNS::Slider, true, false, vector<string>(), 1));
		iii = 2;
		mPanels[whereis]->AddParamData(PanelNS::Data(12, real[iii*2], real[iii*2+1], print[iii*2], print[iii*2+1], "Low G.", PanelNS::Slider, false, false, vector<string>(), 2));
		iii = 3;
		mPanels[whereis]->AddParamData(PanelNS::Data(13, real[iii*2], real[iii*2+1], print[iii*2], print[iii*2+1], "Q", PanelNS::Slider, false, false, vector<string>(), 3));

		iii = 4;
		mPanels[whereis]->AddParamData(PanelNS::Data(11+5, real[iii*2], real[iii*2+1], print[iii*2], print[iii*2+1], "Mid F.", PanelNS::Slider, true, false, vector<string>(), 4));
		iii = 5;
		mPanels[whereis]->AddParamData(PanelNS::Data(12+5, real[iii*2], real[iii*2+1], print[iii*2], print[iii*2+1], "Mid G.", PanelNS::Slider, false, false, vector<string>(), 5));
		iii = 6;
		mPanels[whereis]->AddParamData(PanelNS::Data(13+5, real[iii*2], real[iii*2+1], print[iii*2], print[iii*2+1], "Q", PanelNS::Slider, false, false, vector<string>(), 6));

		iii = 7;
		mPanels[whereis]->AddParamData(PanelNS::Data(11+10, real[iii*2], real[iii*2+1], print[iii*2], print[iii*2+1], "High F.", PanelNS::Slider, true, false, vector<string>(), 7));
		iii = 8;
		mPanels[whereis]->AddParamData(PanelNS::Data(12+10, real[iii*2], real[iii*2+1], print[iii*2], print[iii*2+1], "High G.", PanelNS::Slider, false, false, vector<string>(), 8));
		iii = 9;
		mPanels[whereis]->AddParamData(PanelNS::Data(13+10, real[iii*2], real[iii*2+1], print[iii*2], print[iii*2+1], "Q", PanelNS::Slider, false, false, vector<string>(), 9));
		if(loadPrev)
			mPanels[whereis]->LoadPreset(prevIdx);
		else
			mPanels[whereis]->SetPreset(0);
	}
		break;
	case EffParametricEQ3:
	{
		int PEQPreset[] = {
			127, 30,64,64, 900,64,64, 7000,64,64
		};
		int ParametricEQReal[] = {
			0,127, // 0 Gain
			47, 115, // 20-1000Hz Low F.
			0,127, // Low G.
			0,127, // Low Q
			111,151, // 800~8000 Mid F.
			0,127, // Mid G.
			0,127, // Mid Q
			145,171, // 6000~26000 High F.
			0,127, // High G.
			0,127, // High Q
		};
		int ParametricEQPrint[] = {
			0,127, // 0
			0,100, // 1
			-64,63, // 2
			-64,63, // 3
			0,100, // 4
			-64,63, // 5
			-64,63, // 6
			0,100, // 7
			-64,63, // 8
			-64,63, // 9
		};

		real = ParametricEQReal;
		print = ParametricEQPrint;
		presetTexts.clear();
		presetTexts.push_back("Default");
		mPanels[whereis] = new PanelNS::Panel(mGUI, (VstPlugin*)effect, ((VstPlugin*)effect)->mEffEQ4, "Parametric EQ", whereis, PEQPreset, 10, 1, presetTexts, true);

		iii = 0;
		mPanels[whereis]->AddParamData(PanelNS::Data(0, real[iii*2], real[iii*2+1], print[iii*2], print[iii*2+1], "Gain", PanelNS::Slider, false, false, vector<string>(), 0));

		iii = 1;
		mPanels[whereis]->AddParamData(PanelNS::Data(11, real[iii*2], real[iii*2+1], print[iii*2], print[iii*2+1], "Low F.", PanelNS::Slider, true, false, vector<string>(), 1));
		iii = 2;
		mPanels[whereis]->AddParamData(PanelNS::Data(12, real[iii*2], real[iii*2+1], print[iii*2], print[iii*2+1], "Low G.", PanelNS::Slider, false, false, vector<string>(), 2));
		iii = 3;
		mPanels[whereis]->AddParamData(PanelNS::Data(13, real[iii*2], real[iii*2+1], print[iii*2], print[iii*2+1], "Q", PanelNS::Slider, false, false, vector<string>(), 3));

		iii = 4;
		mPanels[whereis]->AddParamData(PanelNS::Data(11+5, real[iii*2], real[iii*2+1], print[iii*2], print[iii*2+1], "Mid F.", PanelNS::Slider, true, false, vector<string>(), 4));
		iii = 5;
		mPanels[whereis]->AddParamData(PanelNS::Data(12+5, real[iii*2], real[iii*2+1], print[iii*2], print[iii*2+1], "Mid G.", PanelNS::Slider, false, false, vector<string>(), 5));
		iii = 6;
		mPanels[whereis]->AddParamData(PanelNS::Data(13+5, real[iii*2], real[iii*2+1], print[iii*2], print[iii*2+1], "Q", PanelNS::Slider, false, false, vector<string>(), 6));

		iii = 7;
		mPanels[whereis]->AddParamData(PanelNS::Data(11+10, real[iii*2], real[iii*2+1], print[iii*2], print[iii*2+1], "High F.", PanelNS::Slider, true, false, vector<string>(), 7));
		iii = 8;
		mPanels[whereis]->AddParamData(PanelNS::Data(12+10, real[iii*2], real[iii*2+1], print[iii*2], print[iii*2+1], "High G.", PanelNS::Slider, false, false, vector<string>(), 8));
		iii = 9;
		mPanels[whereis]->AddParamData(PanelNS::Data(13+10, real[iii*2], real[iii*2+1], print[iii*2], print[iii*2+1], "Q", PanelNS::Slider, false, false, vector<string>(), 9));
		if(loadPrev)
			mPanels[whereis]->LoadPreset(prevIdx);
		else
			mPanels[whereis]->SetPreset(0);
	}
		break;
	case EffWahWah:
	{
		const int WAH_PRESET_SIZE = 10;
		const int WAH_NUM_PRESETS = 5;
		int wah_presets[] = {
			//WahWah
			64, 64, 80, 0, 0, 64, 70, 90, 0, 60,
			//AutoWah
			64, 64, 70, 0, 0, 80, 70, 0, 0, 60,
			//Sweep
			64, 64, 30, 0, 0, 50, 80, 0, 0, 60,
			//VocalMorph1
			64, 64, 80, 0, 0, 64, 70, 64, 0, 60,
			//VocalMorph1
			64, 64, 50, 0, 0, 96, 64, 0, 0, 60
		};
		
		int WahWahReal[] = {
			//case 0:
			0,127,
				//setvolume (value);
				//break;
			//case 1:
			0,127,
				//setpanning (value);
				//break;
			//case 2:
			1,600,
				//lfo.Pfreq = value;
				//lfo.updateparams ();
				//break;
			//case 3:
			0,127,
				//lfo.Prandomness = value;
				//lfo.updateparams ();
				//break;
			//case 4:
			0, 9,  // type value
			/*
			Sine
			Tri
			RampUp
			RampDown
			ZigZag
			M.Sqare
			M.Saw
			L. Fractal
			L. Fractal XY
			S/H Random*/
				//lfo.PLFOtype = value;
				//lfo.updateparams ();
				//break;
			//case 5:
			0,127,
				//lfo.Pstereo = value;
				//lfo.updateparams ();
				//break;
			//case 6:
			0,127,
				//setdepth (value);
				//break;
			//case 7:
			0,127,
				//setampsns (value);
				//break;
			//case 8:
			0,1, // Boolean
				//Pampsnsinv = value;
				//setampsns (Pampsns);
				//break;
			//case 9:
			0,127,
				//Pampsmooth = value;
				//setampsns (Pampsns);
				//break;
		};
		int WahWahPrint[] = {
			-64,63, // 0
			-64,63, // 1
			1,600, // 2
			0,127, // 3
			0,9, // 4
			0,127, // 5
			0,127, // 6
			0,127, // 7
			0,1,
			0,127,
		};
		real = WahWahReal;
		print = WahWahPrint;
		presetTexts.clear();
		presetTexts.push_back("WahWah");
		presetTexts.push_back("AutoWah");
		presetTexts.push_back("Sweep");
		presetTexts.push_back("VocalMorph1");
		presetTexts.push_back("VocalMorph1");
		mPanels[whereis] = new PanelNS::Panel(mGUI, (VstPlugin*)effect, ((VstPlugin*)effect)->mEffWahWah, "WahWah", whereis, wah_presets, WAH_PRESET_SIZE, WAH_NUM_PRESETS, presetTexts, false, true);
		iii=0;
		mPanels[whereis]->AddParamData(PanelNS::Data(iii, real[iii*2], real[iii*2+1], print[iii*2], print[iii*2+1], "Wet/Dry", PanelNS::Slider));
		iii=1;
		mPanels[whereis]->AddParamData(PanelNS::Data(iii, real[iii*2], real[iii*2+1], print[iii*2], print[iii*2+1], "Pan", PanelNS::Slider));
		iii=2;
		mPanels[whereis]->AddParamData(PanelNS::Data(iii, real[iii*2], real[iii*2+1], print[iii*2], print[iii*2+1], "Tempo", PanelNS::Slider));
		iii=3;
		mPanels[whereis]->AddParamData(PanelNS::Data(iii, real[iii*2], real[iii*2+1], print[iii*2], print[iii*2+1], "Rnd", PanelNS::Slider));
		lfoTypeStrs.clear();
		lfoTypeStrs.push_back("Sine");
		lfoTypeStrs.push_back("Tri");
		lfoTypeStrs.push_back("RampUp");
		lfoTypeStrs.push_back("RampDn");
		lfoTypeStrs.push_back("ZigZag");
		lfoTypeStrs.push_back("M.Sqare");
		lfoTypeStrs.push_back("M.Saw");
		lfoTypeStrs.push_back("L.Fract");
		lfoTypeStrs.push_back("L.FractXY");
		lfoTypeStrs.push_back("S/H Rnd");
		iii=4;
		mPanels[whereis]->AddParamData(PanelNS::Data(iii, real[iii*2], real[iii*2+1], print[iii*2], print[iii*2+1],  "LFOType", PanelNS::Selection, false, false, lfoTypeStrs));
		iii=5;
		mPanels[whereis]->AddParamData(PanelNS::Data(iii, real[iii*2], real[iii*2+1], print[iii*2], print[iii*2+1], "St.df", PanelNS::Slider));
		iii=6;
		mPanels[whereis]->AddParamData(PanelNS::Data(iii, real[iii*2], real[iii*2+1], print[iii*2], print[iii*2+1], "Depth", PanelNS::Slider));
		iii=7;
		mPanels[whereis]->AddParamData(PanelNS::Data(iii, real[iii*2], real[iii*2+1], print[iii*2], print[iii*2+1], "Amp.S.", PanelNS::Slider));
		iii=8;
		mPanels[whereis]->AddParamData(PanelNS::Data(iii, real[iii*2], real[iii*2+1], print[iii*2], print[iii*2+1], "Amp.S Inv", PanelNS::OnOff));
		iii=9;
		mPanels[whereis]->AddParamData(PanelNS::Data(iii, real[iii*2], real[iii*2+1], print[iii*2], print[iii*2+1], "Smooth", PanelNS::Slider));
		if(loadPrev)
			mPanels[whereis]->LoadPreset(prevIdx);
		else
			mPanels[whereis]->SetPreset(0);
	}
		break;
	case EffAlienWah:
	{
		const int AWAH_PRESET_SIZE = 11;
		const int AWAH_NUM_PRESETS = 4;
		int awah_presets[] = {
			//AlienWah1
			64, 64, 80, 0, 0, 62, 60, 105, 25, 0, 64,
			//AlienWah2
			64, 64, 95, 106, 0, 101, 60, 105, 17, 0, 64,
			//AlienWah3
			64, 64, 55, 0, 1, 100, 112, 105, 31, 0, 42,
			//AlienWah4
			64, 64, 1, 0, 1, 66, 101, 11, 47, 0, 86
		};

		int AlienWahReal[] = {
			//case 0:
			0,127,
				//setvolume (value);
			//case 1:
			0,127,
				//setpanning (value);
			//case 2:
			1,600,
				//lfo.Pfreq = value;
			//case 3:
			0,127,
				//lfo.Prandomness = value;
			//case 4:
			0,9,
			/*
			Sine
			Tri
			RampUp
			RampDown
			ZigZag
			M.Sqare
			M.Saw
			L. Fractal
			L. Fractal XY
			S/H Random*/
			//case 5:
			0,127,
				//lfo.Pstereo = value;
			//case 6:
			0,127,
				//setdepth (value);
			//case 7:
			0,127,
				//setfb (value);
			//case 8:
			0,127,
				//setdelay (value);
			//case 9:
			0,127,
				//setlrcross (value);
			//case 10:
			0,127,
				//setphase (value);
		};
		int AlienWahPrint[] = {
			-64,63, // 0
			-64,63, // 1
			1,600, // 2
			0,127, // 3
			0,9, // 4
			0,127, // 5
			0,127, // 6
			0,127, // 7
			0,127, // 8
			-64,63, // 9
			0,127,
		};
		real = AlienWahReal;
		print = AlienWahPrint;
		presetTexts.clear();
		presetTexts.push_back("AlienWah1");
		presetTexts.push_back("AlienWah2");
		presetTexts.push_back("AlienWah3");
		presetTexts.push_back("AlienWah4");
		mPanels[whereis] = new PanelNS::Panel(mGUI, (VstPlugin*)effect, ((VstPlugin*)effect)->mEffAlienwah, "Alien Wah", whereis, awah_presets, AWAH_PRESET_SIZE, AWAH_NUM_PRESETS, presetTexts);
		iii=0;
		mPanels[whereis]->AddParamData(PanelNS::Data(iii, real[iii*2], real[iii*2+1], print[iii*2], print[iii*2+1], "Wet/Dry", PanelNS::Slider));
		iii=1;
		mPanels[whereis]->AddParamData(PanelNS::Data(iii, real[iii*2], real[iii*2+1], print[iii*2], print[iii*2+1], "Pan", PanelNS::Slider));
		iii=2;
		mPanels[whereis]->AddParamData(PanelNS::Data(iii, real[iii*2], real[iii*2+1], print[iii*2], print[iii*2+1], "Tempo", PanelNS::Slider));
		iii=3;
		mPanels[whereis]->AddParamData(PanelNS::Data(iii, real[iii*2], real[iii*2+1], print[iii*2], print[iii*2+1], "Rnd", PanelNS::Slider));
		lfoTypeStrs.clear();
		lfoTypeStrs.push_back("Sine");
		lfoTypeStrs.push_back("Tri");
		lfoTypeStrs.push_back("RampUp");
		lfoTypeStrs.push_back("RampDn");
		lfoTypeStrs.push_back("ZigZag");
		lfoTypeStrs.push_back("M.Sqare");
		lfoTypeStrs.push_back("M.Saw");
		lfoTypeStrs.push_back("L.Fract");
		lfoTypeStrs.push_back("L.FractXY");
		lfoTypeStrs.push_back("S/H Rnd");
		iii=4;
		mPanels[whereis]->AddParamData(PanelNS::Data(iii, real[iii*2], real[iii*2+1], print[iii*2], print[iii*2+1],  "LFOType", PanelNS::Selection, false, false, lfoTypeStrs));
		iii=10;
		mPanels[whereis]->AddParamData(PanelNS::Data(iii, real[iii*2], real[iii*2+1], print[iii*2], print[iii*2+1], "Phase", PanelNS::Slider));
		iii=5;
		mPanels[whereis]->AddParamData(PanelNS::Data(iii, real[iii*2], real[iii*2+1], print[iii*2], print[iii*2+1], "St.df", PanelNS::Slider));
		iii=6;
		mPanels[whereis]->AddParamData(PanelNS::Data(iii, real[iii*2], real[iii*2+1], print[iii*2], print[iii*2+1], "Depth", PanelNS::Slider));
		iii=8;
		mPanels[whereis]->AddParamData(PanelNS::Data(iii, real[iii*2], real[iii*2+1], print[iii*2], print[iii*2+1], "Delay", PanelNS::Slider));
		iii=7;
		mPanels[whereis]->AddParamData(PanelNS::Data(iii, real[iii*2], real[iii*2+1], print[iii*2], print[iii*2+1], "Fb", PanelNS::Slider));
		iii=9;
		mPanels[whereis]->AddParamData(PanelNS::Data(iii, real[iii*2], real[iii*2+1], print[iii*2], print[iii*2+1], "L/R.Cr", PanelNS::Slider));
		if(loadPrev)
			mPanels[whereis]->LoadPreset(prevIdx);
		else
			mPanels[whereis]->SetPreset(0);
	}
	break;
	case EffPan:
	{
		const int PAN_PRESET_SIZE = 9;
		const int PAN_NUM_PRESETS = 2;
		int pan_presets[] = {
			//AutoPan
			64, 64, 26, 0, 0, 0, 0, 1, 0,
			//Extra Stereo
			64, 64, 80, 0, 0, 0, 10, 0, 1
		};
		int PanReal[] = {
			//case 0:
			0,127,
				//setvolume (value);
				//break;
			//case 1:
			0,127,
				//setpanning (value);
				//break;
			//case 2:
			1,600,
				//lfo.Pfreq = value;
				//lfo.updateparams ();
				//break;
			//case 3:
			0,127,
				//lfo.Prandomness = value;
				//lfo.updateparams ();
				//break;
			//case 4:
			0,9,
				//lfo.PLFOtype = value;
				//lfo.updateparams ();
				//break;
			//case 5:
			0,127,
				//lfo.Pstereo = value;
				//lfo.updateparams ();
				//break;
			//case 6:
			0,127,
				//setextra (value);
				//break;
			//case 7:
			0,1,
				//PAutoPan = value;
				//break;
			//case 8:
			0,1,
				//PextraON = value;
				//break;

		};
		int PanPrint[] = {
			-64,63, // 0
			-64,63, // 1
			1,600, // 2
			0,127, // 3
			0,9, // 4
			0,127, // 5
			0,127, // 6
			0,1, // 7
			0.1, // 8
		};
		real = PanReal;
		print = PanPrint;
		presetTexts.clear();
		presetTexts.push_back("AutoPan");
		presetTexts.push_back("Extra Stereo");
		mPanels[whereis] = new PanelNS::Panel(mGUI, (VstPlugin*)effect, ((VstPlugin*)effect)->mEffPan, "Pan", whereis, pan_presets, PAN_PRESET_SIZE, PAN_NUM_PRESETS, presetTexts);
		iii=0;
		mPanels[whereis]->AddParamData(PanelNS::Data(iii, real[iii*2], real[iii*2+1], print[iii*2], print[iii*2+1], "Wet/Dry", PanelNS::Slider));
		iii=7;
		mPanels[whereis]->AddParamData(PanelNS::Data(iii, real[iii*2], real[iii*2+1], print[iii*2], print[iii*2+1], "Autopan", PanelNS::OnOff));
		iii=8;
		mPanels[whereis]->AddParamData(PanelNS::Data(iii, real[iii*2], real[iii*2+1], print[iii*2], print[iii*2+1], "ExtraSt", PanelNS::OnOff, false, true));
		iii=1;
		mPanels[whereis]->AddParamData(PanelNS::Data(iii, real[iii*2], real[iii*2+1], print[iii*2], print[iii*2+1], "Pan", PanelNS::Slider));
		iii=6;
		mPanels[whereis]->AddParamData(PanelNS::Data(iii, real[iii*2], real[iii*2+1], print[iii*2], print[iii*2+1], "ExtraSt.", PanelNS::Slider));
		iii=2;
		mPanels[whereis]->AddParamData(PanelNS::Data(iii, real[iii*2], real[iii*2+1], print[iii*2], print[iii*2+1], "Freq", PanelNS::Slider));
		iii=3;
		mPanels[whereis]->AddParamData(PanelNS::Data(iii, real[iii*2], real[iii*2+1], print[iii*2], print[iii*2+1], "Rnd", PanelNS::Slider));
		lfoTypeStrs.clear();
		lfoTypeStrs.push_back("Sine");
		lfoTypeStrs.push_back("Tri");
		lfoTypeStrs.push_back("RampUp");
		lfoTypeStrs.push_back("RampDn");
		lfoTypeStrs.push_back("ZigZag");
		lfoTypeStrs.push_back("M.Sqare");
		lfoTypeStrs.push_back("M.Saw");
		lfoTypeStrs.push_back("L.Fract");
		lfoTypeStrs.push_back("L.FractXY");
		lfoTypeStrs.push_back("S/H Rnd");
		iii=4;
		mPanels[whereis]->AddParamData(PanelNS::Data(iii, real[iii*2], real[iii*2+1], print[iii*2], print[iii*2+1],  "LFOType", PanelNS::Selection, false, false, lfoTypeStrs));
		iii=5;
		mPanels[whereis]->AddParamData(PanelNS::Data(iii, real[iii*2], real[iii*2+1], print[iii*2], print[iii*2+1], "St.df", PanelNS::Slider));
		if(loadPrev)
			mPanels[whereis]->LoadPreset(prevIdx);
		else
			mPanels[whereis]->SetPreset(0);
	}
		break;
	case EffHarmonizer:
	{
		const int harm_PRESET_SIZE = 11;
		const int harm_NUM_PRESETS = 3;
		int harm_presets[] = {
			//Plain
			64, 64, 64, 12, 6000, 0, 0, 0, 64, 64, 0,
			//Octavador
			64, 64, 64, 0, 6000, 0, 0, 0, 64, 64, 0,
			//3mdown
			64, 64, 64, 9, 6000, 0, 0, 0, 64, 64, 0
		};
		int HarmonizerReal[] = {
			//case 0:
			0,127,
				//setvolume (value);
				//break;
			//case 1:
			0,127,
				//setpanning (value);
				//break;
			//case 2:
			0,127,
				//setgain (value);
				//break;
			//case 3:
			0,24,
				//setinterval (value);
				//break;
			//case 4:
			47,171, // 20~26000, 이 값을 GetFreqByRealMinMax로 변환하면 주파수가 나온다.
				//fsetfreq (value);
				//break;
			//case 5:
			0,1,
				//PSELECT = value;;
				//break;
			//case 6:
			0,23,
				//Pnote = value;
				//break;
			//case 7:
			0,33,
				//Ptype = value;
				//break;
			//case 8:
			0,127,
				//fsetgain (value);
				//break;
			//case 9:
			0,127,
				//fsetq (value);
				//break;
			//case 10:
			0,1,
				//setMIDI (value);
				//break;
		};
		int HarmonizerPrint[] = {
			-64,63, // 0
			-64,63, // 1
			-64,63, // 2
			-12,12, // 3
			0,100, // 4
			0,1, // 5
			0,23, // 6
			0,33, // 7
			-64,63, // 8
			-64,63, // 9
			0,1,
		};

		real = HarmonizerReal;
		print = HarmonizerPrint;
		presetTexts.clear();
		presetTexts.push_back("Plain");
		presetTexts.push_back("Octavador");
		presetTexts.push_back("3mdown");
		mPanels[whereis] = new PanelNS::Panel(mGUI, (VstPlugin*)effect, ((VstPlugin*)effect)->mEffHarmonizer, "Harmonizer", whereis, harm_presets, harm_PRESET_SIZE, harm_NUM_PRESETS, presetTexts);
		iii=0;
		mPanels[whereis]->AddParamData(PanelNS::Data(iii, real[iii*2], real[iii*2+1], print[iii*2], print[iii*2+1], "Wet/Dry", PanelNS::Slider));
		iii=3;
		mPanels[whereis]->AddParamData(PanelNS::Data(iii, real[iii*2], real[iii*2+1], print[iii*2], print[iii*2+1], "Int.", PanelNS::Slider));
		iii=2;
		mPanels[whereis]->AddParamData(PanelNS::Data(iii, real[iii*2], real[iii*2+1], print[iii*2], print[iii*2+1], "Gain", PanelNS::Slider));
		iii=1;
		mPanels[whereis]->AddParamData(PanelNS::Data(iii, real[iii*2], real[iii*2+1], print[iii*2], print[iii*2+1], "Pan", PanelNS::Slider));
		iii=4;
		mPanels[whereis]->AddParamData(PanelNS::Data(iii, real[iii*2], real[iii*2+1], print[iii*2], print[iii*2+1], "Freq", PanelNS::Slider, true));
		iii=8;
		mPanels[whereis]->AddParamData(PanelNS::Data(iii, real[iii*2], real[iii*2+1], print[iii*2], print[iii*2+1], "Gain", PanelNS::Slider));
		iii=9;
		mPanels[whereis]->AddParamData(PanelNS::Data(iii, real[iii*2], real[iii*2+1], print[iii*2], print[iii*2+1], "Q", PanelNS::Slider));
		iii=10;
		mPanels[whereis]->AddParamData(PanelNS::Data(iii, real[iii*2], real[iii*2+1], print[iii*2], print[iii*2+1], "MIDI", PanelNS::OnOff));
		iii=5;
		mPanels[whereis]->AddParamData(PanelNS::Data(iii, real[iii*2], real[iii*2+1], print[iii*2], print[iii*2+1], "SEL", PanelNS::OnOff, false, true));
		iii=6;
		mPanels[whereis]->AddParamData(PanelNS::Data(iii, real[iii*2], real[iii*2+1], print[iii*2], print[iii*2+1], "Note", PanelNS::Slider));
		iii=7;
		mPanels[whereis]->AddParamData(PanelNS::Data(iii, real[iii*2], real[iii*2+1], print[iii*2], print[iii*2+1], "Chord", PanelNS::Slider));

		if(loadPrev)
			mPanels[whereis]->LoadPreset(prevIdx);
		else
			mPanels[whereis]->SetPreset(0);
	}
	break;
	case EffMusicDelay:
	{
		const int mdel_PRESET_SIZE = 13;
		const int mdel_NUM_PRESETS = 2;
		int mdel_presets[] = {
        //Echo 1
        64, 0, 2-1, 7-1, 0, 59, 0, 127, 4-1, 59, 106, 75, 75,
        //Echo 2
        67, 0, 3-1, 7-1, 0, 59, 0, 127, 6-1, 69, 60, 127, 127,

		};
		int MusicDelayReal[] = {
			//case 0:
			0,127,
				//setvolume (value);
				//break;
			//case 1:
			0,127,
				//setpanning (1, value);
				//break;
			//case 2:
			0,5,
				/*
				1
				1/2
				1/3
				1/4
				1/5
				1/6
				*/
				//setdelay (1, value);
				//break;
			//case 3:
			0,6,
				/*
				1
				1/2
				1/3
				1/4
				1/5
				1/6
				0
				*/
				//setdelay (3, value);
				//break;
			//case 4:
			0,127,
				//setlrcross (value);
				//break;
			//case 5:
			0,127,
				//setfb (1, value);
				//break;
			//case 6:
			0,127,
				//sethidamp (value);
				//break;
			//case 7:
			0,127,
				//setpanning (2, value);
				//break;
			//case 8:
			0,5,
				/*
				1
				1/2
				1/3
				1/4
				1/5
				1/6
				*/
				//setdelay (2, value);
				//break;
			//case 9:
			0,127,
				//setfb (2, value);
				//break;
			//case 10:
			10,480, // 10
				//settempo (value);
				//break;
			//case 11:
			0,127,
				//setgain (1, value);
				//break;
			//case 12:
			0,127,
				//setgain (2, value);
				//break;


		};
		int MusicDelayPrint[] = {
			-64, 63, // 0
			-64, 63, // 1
			0, 5, // 2
			0, 6, // 3
			-64, 63, // 4
			0, 127, // 5
			0, 127, // 6
			-64, 63, // 7
			0, 5, // 8
			0, 127, // 9
			10, 480, // 10
			-64, 63, // 11
			-64, 63, // 12
		};
		real = MusicDelayReal;
		print = MusicDelayPrint;
		presetTexts.clear();
		presetTexts.push_back("Echo 1");
		presetTexts.push_back("Echo 2");
		mPanels[whereis] = new PanelNS::Panel(mGUI, (VstPlugin*)effect, ((VstPlugin*)effect)->mEffMusicDelay, "Musical Delay", whereis, mdel_presets, mdel_PRESET_SIZE, mdel_NUM_PRESETS, presetTexts);
		iii=0;
		mPanels[whereis]->AddParamData(PanelNS::Data(iii, real[iii*2], real[iii*2+1], print[iii*2], print[iii*2+1], "Wet/Dry", PanelNS::Slider));
		iii=4;
		mPanels[whereis]->AddParamData(PanelNS::Data(iii, real[iii*2], real[iii*2+1], print[iii*2], print[iii*2+1], "L/R.Cr", PanelNS::Slider));
		iii=1;
		mPanels[whereis]->AddParamData(PanelNS::Data(iii, real[iii*2], real[iii*2+1], print[iii*2], print[iii*2+1], "Pan1", PanelNS::Slider));
		iii=7;
		mPanels[whereis]->AddParamData(PanelNS::Data(iii, real[iii*2], real[iii*2+1], print[iii*2], print[iii*2+1], "Pan2", PanelNS::Slider));
		vector<string> notes1;
		notes1.push_back("1");
		notes1.push_back("1/2");
		notes1.push_back("1/3");
		notes1.push_back("1/4");
		notes1.push_back("1/5");
		notes1.push_back("1/6");
		vector<string> notes2;
		notes2.push_back("1");
		notes2.push_back("1/2");
		notes2.push_back("1/3");
		notes2.push_back("1/4");
		notes2.push_back("1/5");
		notes2.push_back("1/6");
		notes2.push_back("0");
		iii = 2;
		mPanels[whereis]->AddParamData(PanelNS::Data(iii, real[iii*2], real[iii*2+1], print[iii*2], print[iii*2+1], "LDelay", PanelNS::Selection, false, false, notes1));
		iii = 3;
		mPanels[whereis]->AddParamData(PanelNS::Data(iii, real[iii*2], real[iii*2+1], print[iii*2], print[iii*2+1], "LRDelay", PanelNS::Selection, false, false, notes2));
		iii = 8;
		mPanels[whereis]->AddParamData(PanelNS::Data(iii, real[iii*2], real[iii*2+1], print[iii*2], print[iii*2+1], "RDelay", PanelNS::Selection, false, false, notes1));
		iii=10;
		mPanels[whereis]->AddParamData(PanelNS::Data(iii, real[iii*2], real[iii*2+1], print[iii*2], print[iii*2+1], "Tempo", PanelNS::Slider));

		iii=11;
		mPanels[whereis]->AddParamData(PanelNS::Data(iii, real[iii*2], real[iii*2+1], print[iii*2], print[iii*2+1], "Gain1", PanelNS::Slider));
		iii=12;
		mPanels[whereis]->AddParamData(PanelNS::Data(iii, real[iii*2], real[iii*2+1], print[iii*2], print[iii*2+1], "Gain2", PanelNS::Slider));
		iii=5;
		mPanels[whereis]->AddParamData(PanelNS::Data(iii, real[iii*2], real[iii*2+1], print[iii*2], print[iii*2+1], "Fb1", PanelNS::Slider));
		iii=9;
		mPanels[whereis]->AddParamData(PanelNS::Data(iii, real[iii*2], real[iii*2+1], print[iii*2], print[iii*2+1], "Fb2", PanelNS::Slider));
		iii=6;
		mPanels[whereis]->AddParamData(PanelNS::Data(iii, real[iii*2], real[iii*2+1], print[iii*2], print[iii*2+1], "Damp", PanelNS::Slider));
		if(loadPrev)
			mPanels[whereis]->LoadPreset(prevIdx);
		else
			mPanels[whereis]->SetPreset(0);
	}
	break;
	case EffGate:
	{
		const int gate_PRESET_SIZE = 7;
		const int gate_NUM_PRESETS = 3;
		int gate_presets[] = {
			//0dB
			0, 0, 1, 2, 6703, 76, 2,
			//-10dB
			0, -10, 1, 2, 6703, 76, 2,
			//-20dB
			0, -20, 1, 2, 6703, 76, 2
		};


		int GateReal[] = {
			//case 1:
			-70,20,
				//Pthreshold = value;
				//t_level = dB2rap ((float)Pthreshold);
				//break;
			//case 2:
			-90,0,
				//Prange = value;
				//cut = dB2rap ((float)Prange);
				//break;
			//case 3:
			1,250,
				//Pattack = value;
				//a_rate = 1000.0f / ((float)Pattack * fs);
				//break;
			//case 4:
			2,250,
				//Pdecay = value;
				//d_rate = 1000.0f / ((float)Pdecay * fs);
				//break;
			//case 5:
			47,171,
				//setlpf(value);
				//break;
			//case 6:
			47,166,
				//sethpf(value);
				//break;
			//case 7:
			2,500,
				//Phold = value;
				//hold = (float)Phold;
				//break;


		};
		int GatePrint[] = {
			-70,20,
			-90,0,
			1,250,
			2,250,
			0,100,
			0,100,
			2,500,
		};
		real = GateReal;
		print = GatePrint;
		presetTexts.clear();
		presetTexts.push_back("0dB");
		presetTexts.push_back("-10dB");
		presetTexts.push_back("-20dB");
		mPanels[whereis] = new PanelNS::Panel(mGUI, (VstPlugin*)effect, ((VstPlugin*)effect)->mEffGate, "Noise Gate", whereis, gate_presets, gate_PRESET_SIZE, gate_NUM_PRESETS, presetTexts);
		iii=2;
		mPanels[whereis]->AddParamData(PanelNS::Data(iii, real[iii*2], real[iii*2+1], print[iii*2], print[iii*2+1], "A.Time", PanelNS::Slider, false, false, vector<string>()));
		iii=3;
		mPanels[whereis]->AddParamData(PanelNS::Data(iii, real[iii*2], real[iii*2+1], print[iii*2], print[iii*2+1], "R.Time", PanelNS::Slider, false, false, vector<string>()));
		iii=1;
		mPanels[whereis]->AddParamData(PanelNS::Data(iii, real[iii*2], real[iii*2+1], print[iii*2], print[iii*2+1], "Range", PanelNS::Slider, false, false, vector<string>()));
		iii=0;
		mPanels[whereis]->AddParamData(PanelNS::Data(iii, real[iii*2], real[iii*2+1], print[iii*2], print[iii*2+1], "Thrshld", PanelNS::Slider, false, false, vector<string>()));
		iii=6;
		mPanels[whereis]->AddParamData(PanelNS::Data(iii, real[iii*2], real[iii*2+1], print[iii*2], print[iii*2+1], "Hold", PanelNS::Slider, false, false, vector<string>()));
		iii=4;
		mPanels[whereis]->AddParamData(PanelNS::Data(iii, real[iii*2], real[iii*2+1], print[iii*2], print[iii*2+1], "LPF", PanelNS::Slider, true, false, vector<string>()));
		iii=5;
		mPanels[whereis]->AddParamData(PanelNS::Data(iii, real[iii*2], real[iii*2+1], print[iii*2], print[iii*2+1], "HPF", PanelNS::Slider, true, false, vector<string>()));
		if(loadPrev)
			mPanels[whereis]->LoadPreset(prevIdx);
		else
			mPanels[whereis]->SetPreset(0);
	}
	break;
	case EffNewDist:
	{
		const int der_PRESET_SIZE = 11;
		const int der_NUM_PRESETS = 3;
		int der_presets[] = {
			//NewDist 1
			0, 64, 64, 83, 65, 15, 0, 2437, 169, 68, 0,
			//NewDist 2
			0, 64, 64, 95, 45, 6, 0, 3459, 209, 60, 1,
			//NewDist 3
			0, 64, 64, 43, 77, 16, 0, 2983, 118, 83, 0
		};
		int DerelictReal[] = {
			//switch (npar) {
			//case 0:
			0,127,
				//setvolume (value);
				//break;
			//case 1:
			0,127,
				//setpanning (value);
				//break;
			//case 2:
			0,127,
				//setlrcross (value);
				//break;
			//case 3:
			1,127,
				//Pdrive = value;
				//break;
			//case 4:
			0,127,
				//Plevel = value;
				//break;
			//case 5:
			0,29,
			/*
	mTypeStrs.push_back("Atan");
	mTypeStrs.push_back("Asym");
	mTypeStrs.push_back("Pow");
	mTypeStrs.push_back("Sine");
	mTypeStrs.push_back("Quant");
	mTypeStrs.push_back("ZigZag");
	mTypeStrs.push_back("Lim");
	mTypeStrs.push_back("UpLim");
	mTypeStrs.push_back("LoLim");
	mTypeStrs.push_back("InvLim");

	mTypeStrs.push_back("Clip");
	mTypeStrs.push_back("Asym2");
	mTypeStrs.push_back("Pow2");
	mTypeStrs.push_back("Sigmoid");
	mTypeStrs.push_back("Crunch");
	mTypeStrs.push_back("HardCr");
	mTypeStrs.push_back("OctvUp");
	mTypeStrs.push_back("MSquare");
	mTypeStrs.push_back("MSaw");
	mTypeStrs.push_back("Compres");

	mTypeStrs.push_back("Overdrv");
	mTypeStrs.push_back("Soft");
	mTypeStrs.push_back("SupSoft");
	mTypeStrs.push_back("HardCmp");
	mTypeStrs.push_back("LmtNoG");
	mTypeStrs.push_back("FET");
	mTypeStrs.push_back("DynoFET");
	mTypeStrs.push_back("Valve1");
	mTypeStrs.push_back("Valve2");
	mTypeStrs.push_back("DiodeClp");

			*/
				//Ptype = value;
				//break;
			//case 6:
			0,1,
				//if (value > 1)
					//value = 1;
				//Pnegate = value;
				//break;
			//case 7:
			47,171, // 20~26000, 이 값을 GetFreqByRealMinMax로 변환하면 주파수가 나온다.
				//setlpf (value);
				//break;
			//case 8:
			47,166, // 20~20000
				//sethpf (value);
				//break;
			//case 9:
			0,127,
				//Prfreq = value;
				//rfreq = expf (powf ((float)value / 127.0f, 0.5f) * logf (25000.0f)) + 40.0f;
				//filterl->setfreq(rfreq);
				//filterr->setfreq(rfreq);

				//break;
			//case 10:
			0,1,
				//Pprefiltering = value;
				//break;
			//case 11:
			0,127,
				//setoctave (value);
				//break;



		};
		int DerelictPrint[] = {
			-64,63,
			-64,63,
			-64,63,
			1,127,
			0,127,
			0,29,
			0,1,
			0,100,
			0,100,
			0,127,
			0,1,
			0,127,

		};

		real = DerelictReal;
		print = DerelictPrint;
		presetTexts.clear();
		presetTexts.push_back("Derelict 1");
		presetTexts.push_back("Derelict 2");
		presetTexts.push_back("Derelict 3");
		mPanels[whereis] = new PanelNS::Panel(mGUI, (VstPlugin*)effect, ((VstPlugin*)effect)->mEffNewDist, "Derelict", whereis, der_presets, der_PRESET_SIZE, der_NUM_PRESETS, presetTexts);
		iii=0;
		mPanels[whereis]->AddParamData(PanelNS::Data(iii, real[iii*2], real[iii*2+1], print[iii*2], print[iii*2+1], "Wet/Dry", PanelNS::Slider));
		iii=2;
		mPanels[whereis]->AddParamData(PanelNS::Data(iii, real[iii*2], real[iii*2+1], print[iii*2], print[iii*2+1], "L/R.Cr", PanelNS::Slider));
		iii=3;
		mPanels[whereis]->AddParamData(PanelNS::Data(iii, real[iii*2], real[iii*2+1], print[iii*2], print[iii*2+1], "Drive", PanelNS::Slider));
		iii=4;
		mPanels[whereis]->AddParamData(PanelNS::Data(iii, real[iii*2], real[iii*2+1], print[iii*2], print[iii*2+1], "Level", PanelNS::Slider));
		vector<string> mTypeStrs;
		mTypeStrs.push_back("Atan");
		mTypeStrs.push_back("Asym");
		mTypeStrs.push_back("Pow");
		mTypeStrs.push_back("Sine");
		mTypeStrs.push_back("Quant");
		mTypeStrs.push_back("ZigZag");
		mTypeStrs.push_back("Lim");
		mTypeStrs.push_back("UpLim");
		mTypeStrs.push_back("LoLim");
		mTypeStrs.push_back("InvLim");

		mTypeStrs.push_back("Clip");
		mTypeStrs.push_back("Asym2");
		mTypeStrs.push_back("Pow2");
		mTypeStrs.push_back("Sigmoid");
		mTypeStrs.push_back("Crunch");
		mTypeStrs.push_back("HardCr");
		mTypeStrs.push_back("OctvUp");
		mTypeStrs.push_back("MSquare");
		mTypeStrs.push_back("MSaw");
		mTypeStrs.push_back("Compres");

		mTypeStrs.push_back("Overdrv");
		mTypeStrs.push_back("Soft");
		mTypeStrs.push_back("SupSoft");
		mTypeStrs.push_back("HardCmp");
		mTypeStrs.push_back("LmtNoG");
		mTypeStrs.push_back("FET");
		mTypeStrs.push_back("DynoFET");
		mTypeStrs.push_back("Valve1");
		mTypeStrs.push_back("Valve2");
		mTypeStrs.push_back("DiodeClp");
		iii=5;
		mPanels[whereis]->AddParamData(PanelNS::Data(iii, real[iii*2], real[iii*2+1], print[iii*2], print[iii*2+1],  "Type", PanelNS::Selection, false, false, mTypeStrs));
		iii=6;
		mPanels[whereis]->AddParamData(PanelNS::Data(iii, real[iii*2], real[iii*2+1], print[iii*2], print[iii*2+1], "Neg", PanelNS::OnOff));
		iii=10;
		mPanels[whereis]->AddParamData(PanelNS::Data(iii, real[iii*2], real[iii*2+1], print[iii*2], print[iii*2+1], "Prefilter", PanelNS::OnOff, false, true));
		iii=9;
		mPanels[whereis]->AddParamData(PanelNS::Data(iii, real[iii*2], real[iii*2+1], print[iii*2], print[iii*2+1], "Color", PanelNS::Slider));
		iii=11;
		mPanels[whereis]->AddParamData(PanelNS::Data(iii, real[iii*2], real[iii*2+1], print[iii*2], print[iii*2+1], "Sub Octv", PanelNS::Slider));
		iii=1;
		mPanels[whereis]->AddParamData(PanelNS::Data(iii, real[iii*2], real[iii*2+1], print[iii*2], print[iii*2+1], "Pan", PanelNS::Slider));
		iii=7;
		mPanels[whereis]->AddParamData(PanelNS::Data(iii, real[iii*2], real[iii*2+1], print[iii*2], print[iii*2+1], "LPF", PanelNS::Slider, true));
		iii=8;
		mPanels[whereis]->AddParamData(PanelNS::Data(iii, real[iii*2], real[iii*2+1], print[iii*2], print[iii*2+1], "HPF", PanelNS::Slider, true));
		if(loadPrev)
			mPanels[whereis]->LoadPreset(prevIdx);
		else
			mPanels[whereis]->SetPreset(0);

	}
	break;
	case EffAnalogPhaser:
	{
		const int aphaser_PRESET_SIZE = 13;
		const int aphaser_NUM_PRESETS = 6;
		int aphaser_presets[] = {
			//Phaser1
			64, 20, 14, 0, 1, 64, 110, 40, 4, 10, 0, 64, 1,
			//Phaser2
			64, 20, 14, 5, 1, 64, 110, 40, 6, 10, 0, 70, 1,
			//Phaser3
			64, 20, 9, 0, 0, 64, 40, 40, 8, 10, 0, 60, 0,
			//Phaser4
			64, 20, 14, 10, 0, 64, 110, 80, 7, 10, 1, 45, 1,
			//Phaser5
			25, 20, 240, 10, 0, 64, 25, 16, 8, 100, 0, 25, 0,
			//Phaser6
			64, 20, 1, 10, 1, 64, 110, 40, 12, 10, 0, 70, 1
		};
		int APhaserReal[] = {
			 //case 0:
			0,127,
				//setvolume (value);
				//break;
			//case 1:
			0,100,
				//setdistortion (value);
				//break;
			//case 2:
			//lfo.Pfreq = value; Tempo
			1, 600,
			//case 3:
			//lfo.Prandomness = value; Rnd
			0, 127,
			//case 4:
			//lfo.PLFOtype = value; LFOType
			0, 9,  // type value
				/*
				Sine
				Tri
				RampUp
				RampDown
				ZigZag
				M.Sqare
				M.Saw
				L. Fractal
				L. Fractal XY
				S/H Random*/
			//case 5:
			0, 127,
				//lfo.Pstereo = value;
				//lfo.updateparams ();
				//break;
			//case 6:
			0,127,
				//setwidth (value);
				//break;
			//case 7:
			0,127, 
				//setfb (value);
				//break;
			//case 8:
			1,12,
				//setstages (value);
				//break;
			//case 9:
			0,100,
				//setoffset (value);
				//break;
			//case 10:
			0,1,
				//if (value > 1)
					//value = 1;
				//Poutsub = value;
				//break;
			//case 11:
			0,127,
				//setdepth (value);
				//break;
			//case 12:
			0,1,
				//if (value > 1)
					//value = 1;
				//Phyper = value;
				//break;
		};
		int APhaserPrint[] = {
			-64,63,
			0,100,
			1,600,
			0,127,
			0,9,
			0, 127, // 5
			0,127,
			-64,63,
			1,12,
			0,100, // 9
			0,1,
			0,127,
			0,1,
		};
		real = APhaserReal;
		print = APhaserPrint;
		presetTexts.clear();
		presetTexts.push_back("Phaser 1");
		presetTexts.push_back("Phaser 2");
		presetTexts.push_back("Phaser 3");
		presetTexts.push_back("Phaser 4");
		presetTexts.push_back("Phaser 5");
		presetTexts.push_back("Phaser 6");
		mPanels[whereis] = new PanelNS::Panel(mGUI, (VstPlugin*)effect, ((VstPlugin*)effect)->mEffAPhaser, "Analog Phaser", whereis, aphaser_presets, aphaser_PRESET_SIZE, aphaser_NUM_PRESETS, presetTexts);
		iii=0;
		mPanels[whereis]->AddParamData(PanelNS::Data(iii, real[iii*2], real[iii*2+1], print[iii*2], print[iii*2+1], "Wet/Dry", PanelNS::Slider));
		lfoTypeStrs.clear();
		lfoTypeStrs.push_back("Sine");
		lfoTypeStrs.push_back("Tri");
		lfoTypeStrs.push_back("RampUp");
		lfoTypeStrs.push_back("RampDn");
		lfoTypeStrs.push_back("ZigZag");
		lfoTypeStrs.push_back("M.Sqare");
		lfoTypeStrs.push_back("M.Saw");
		lfoTypeStrs.push_back("L.Fract");
		lfoTypeStrs.push_back("L.FractXY");
		lfoTypeStrs.push_back("S/H Rnd");
		iii=4;
		mPanels[whereis]->AddParamData(PanelNS::Data(iii, real[iii*2], real[iii*2+1], print[iii*2], print[iii*2+1],  "LFOType", PanelNS::Selection, false, false, lfoTypeStrs));
		iii=2;
		mPanels[whereis]->AddParamData(PanelNS::Data(iii, real[iii*2], real[iii*2+1], print[iii*2], print[iii*2+1], "Tempo", PanelNS::Slider));

		iii=11;
		mPanels[whereis]->AddParamData(PanelNS::Data(iii, real[iii*2], real[iii*2+1], print[iii*2], print[iii*2+1], "Depth", PanelNS::Slider));
		iii=6;
		mPanels[whereis]->AddParamData(PanelNS::Data(iii, real[iii*2], real[iii*2+1], print[iii*2], print[iii*2+1], "Width", PanelNS::Slider));
		iii=7;
		mPanels[whereis]->AddParamData(PanelNS::Data(iii, real[iii*2], real[iii*2+1], print[iii*2], print[iii*2+1], "Fb", PanelNS::Slider));
		iii=9;
		mPanels[whereis]->AddParamData(PanelNS::Data(iii, real[iii*2], real[iii*2+1], print[iii*2], print[iii*2+1], "Mismatch", PanelNS::Slider));
		iii=1;
		mPanels[whereis]->AddParamData(PanelNS::Data(iii, real[iii*2], real[iii*2+1], print[iii*2], print[iii*2+1], "Distort", PanelNS::Slider));
		iii=5;
		mPanels[whereis]->AddParamData(PanelNS::Data(iii, real[iii*2], real[iii*2+1], print[iii*2], print[iii*2+1], "St.df", PanelNS::Slider));
		iii=3;
		mPanels[whereis]->AddParamData(PanelNS::Data(iii, real[iii*2], real[iii*2+1], print[iii*2], print[iii*2+1], "Rnd", PanelNS::Slider));
		iii=8;
		mPanels[whereis]->AddParamData(PanelNS::Data(iii, real[iii*2], real[iii*2+1], print[iii*2], print[iii*2+1], "Stages", PanelNS::Slider));
		iii=10;
		mPanels[whereis]->AddParamData(PanelNS::Data(iii, real[iii*2], real[iii*2+1], print[iii*2], print[iii*2+1], "Subtract", PanelNS::OnOff));
		iii=12;
		mPanels[whereis]->AddParamData(PanelNS::Data(iii, real[iii*2], real[iii*2+1], print[iii*2], print[iii*2+1], "Hyper", PanelNS::OnOff, false, true));
		if(loadPrev)
			mPanels[whereis]->LoadPreset(prevIdx);
		else
			mPanels[whereis]->SetPreset(0);

	}
	break;
	case EffValve:
	{
		const int valvePRESET_SIZE = 13;
		const int valveNUM_PRESETS = 3;
		int valvepresets[] = {
			//Valve 1
			0, 64, 64, 127, 64, 0, 5841, 61, 1, 0, 69, 1, 84,
			//Valve 2
			0, 64, 64, 127, 64, 0, 5078, 61, 1, 0, 112, 0, 30,
			//Valve 3
			0, 64, 35, 80, 64, 1, 3134, 358, 1, 1, 100, 1, 30

		};

		int ValveReal[] = {
		   //switch (npar) {
			//case 0:
			0,127,
				//setvolume (value);
				//break;
			//case 1:
			0,127,
				//setpanning (value);
				//break;
			//case 2:
			0,127,
				//setlrcross (value);
				//break;
			//case 3:
			0,127,
				//Pdrive = value;
				//dist = (float) Pdrive / 127.0f * 40.0f + .5f;
				//break;
			//case 4:
			0,127,
				//Plevel = value;
				//break;
			//case 5:
			0,1,
				//if (value > 1)
					//value = 1;
				//Pnegate = value;
				//break;
			//case 6:
			47,171,
				//setlpf (value);
				//break;
			//case 7:
			47,166,
				//sethpf (value);
				//break;
			//case 8:
			0,1,
				//if (value > 1)
					//value = 1;
				//Pstereo = value;
				//break;
			//case 9:
			0,1,
				//Pprefiltering = value;
				//break;
			//case 10:
			0,127,
				//Q_q = value;
				//q = (float)Q_q /127.0f - 1.0f;
				//factor = 1.0f - ((float)Q_q / 128.0f);
				//break;
			//case 11:
			0,1,
				//Ped = value;
				//break;
			//case 12:
			0,100,
				//Presence=value;
				//setpresence(value);
				//break;

				//init_coefs();


		};
		int ValvePrint[] = {
			-64,63, // 0
			-64,63,
			-64,63, // 2
			0,127,
			0,127, // 4
			0,1,
			0,100, // 6
			0,100,
			0,1, // 8
			0,1, 
			0,127, // 10
			0,1,
			0,100,
		};
		real = ValveReal;
		print = ValvePrint;
		presetTexts.clear();
		presetTexts.push_back("Valve 1");
		presetTexts.push_back("Valve 2");
		presetTexts.push_back("Valve 3");
		mPanels[whereis] = new PanelNS::Panel(mGUI, (VstPlugin*)effect, ((VstPlugin*)effect)->mEffValve, "Valve", whereis, valvepresets, valvePRESET_SIZE, valveNUM_PRESETS, presetTexts);
		iii=0;
		mPanels[whereis]->AddParamData(PanelNS::Data(iii, real[iii*2], real[iii*2+1], print[iii*2], print[iii*2+1], "Wet/Dry", PanelNS::Slider));
		iii=2;
		mPanels[whereis]->AddParamData(PanelNS::Data(iii, real[iii*2], real[iii*2+1], print[iii*2], print[iii*2+1], "L/R.Cr", PanelNS::Slider));
		iii=1;
		mPanels[whereis]->AddParamData(PanelNS::Data(iii, real[iii*2], real[iii*2+1], print[iii*2], print[iii*2+1], "Panning", PanelNS::Slider));

		iii=4;
		mPanels[whereis]->AddParamData(PanelNS::Data(iii, real[iii*2], real[iii*2+1], print[iii*2], print[iii*2+1], "Level", PanelNS::Slider));
		iii=3;
		mPanels[whereis]->AddParamData(PanelNS::Data(iii, real[iii*2], real[iii*2+1], print[iii*2], print[iii*2+1], "Drive", PanelNS::Slider));

		iii=10;
		mPanels[whereis]->AddParamData(PanelNS::Data(iii, real[iii*2], real[iii*2+1], print[iii*2], print[iii*2+1], "Dist.", PanelNS::Slider));
		iii=12;
		mPanels[whereis]->AddParamData(PanelNS::Data(iii, real[iii*2], real[iii*2+1], print[iii*2], print[iii*2+1], "Presence", PanelNS::Slider));
		iii=6;
		mPanels[whereis]->AddParamData(PanelNS::Data(iii, real[iii*2], real[iii*2+1], print[iii*2], print[iii*2+1], "LPF", PanelNS::Slider, true));
		iii=7;
		mPanels[whereis]->AddParamData(PanelNS::Data(iii, real[iii*2], real[iii*2+1], print[iii*2], print[iii*2+1], "HPF", PanelNS::Slider, true));


		iii=11;
		mPanels[whereis]->AddParamData(PanelNS::Data(iii, real[iii*2], real[iii*2+1], print[iii*2], print[iii*2+1], "ExtraDist", PanelNS::OnOff));
		iii=9;
		mPanels[whereis]->AddParamData(PanelNS::Data(iii, real[iii*2], real[iii*2+1], print[iii*2], print[iii*2+1], "Prefilter", PanelNS::OnOff, false, true));
		iii=8;
		mPanels[whereis]->AddParamData(PanelNS::Data(iii, real[iii*2], real[iii*2+1], print[iii*2], print[iii*2+1], "Stereo", PanelNS::OnOff));
		iii=5;
		mPanels[whereis]->AddParamData(PanelNS::Data(iii, real[iii*2], real[iii*2+1], print[iii*2], print[iii*2+1], "Neg", PanelNS::OnOff, false, true));

		if(loadPrev)
			mPanels[whereis]->LoadPreset(prevIdx);
		else
			mPanels[whereis]->SetPreset(0);
	}
	break;
	case EffDualFlange:
	{
		const int dflangePRESET_SIZE = 15;
		const int dflangeNUM_PRESETS = 7;
		int dflangepresets[] = {
			//Preset 1
			32, 0, 0, 110, 800, 10, -27, 16000, 1, 0, 24, 64, 1, 10, 0,
			//Flange-Wha
			0, 0, 64, 500, 3000, 50, -40, 8000, 1, 0, 196, 96, 0, 0, 0,
			//FbFlange
			0, 0, 64, 68, 75, 50, -50, 8000, 0, 1, 23, 96, 5, 0, 0,
			//SoftFlange
			32, 0, 64, 60, 10, 100, 20, 16000, 0, 0, 16, 90, 4, 0, 0,
			//Flanger
			32, 0, 64, 170, 1200, 50, 0, 16000, 1, 0, 68, 127, 0, 0, 0,
			//Chorus 1
			15, 0, 0, 42, 12, 50, -10, 1500, 0, 0, 120, 0, 0, 20, 0,
			//Chorus 2
			40, 0, 0, 35, 9, 67, 12, 4700, 1, 1, 160, 75, 0, 60, 0,
		};
		int DFlangeReal[] = {
			//switch (npar) {
			//case 0:
			-64,64,
				//Pwetdry = value;
				//break;
			//case 1:
			-64,64,
				//Ppanning = value;
			//case 2:
			-64,64,
				//Plrcross = value;
			//case 3:
			20,500,
				//Pdepth = value;
			//case 4:
			0,3000,
				//Pwidth = value;
			//case 5:
			0,100,
				//Poffset = value;
				//foffset = 0.5f + (float) Poffset/255.0;
				//break;
			//case 6:
			-64,64,
				//Pfb = value;
				//ffb = (float) Pfb/64.5f;
				//break;
			//case 7:
			47,166,
				//Phidamp = value;
				//fhidamp = f_exp(-D_PI * (float) Phidamp/fSAMPLE_RATE);
				//break;
			//case 8:
			0,1,
				//Psubtract = value;
				//fsubtract = 0.5f;
				//if(Psubtract) {
					//fsubtract = -0.5f;  //In loop a mult by 0.5f is necessary, so this kills 2 birds with 1...
					//ldelayline0->set_mix(-dry);
					//rdelayline0->set_mix(-dry);
					//ldelayline1->set_mix(-dry);
					//rdelayline1->set_mix(-dry);
				//}
				//break;
			//case 9:
			0,1,
				//Pzero = value;
				//if (Pzero) fzero = 1.0f;
				//break;
			//case 10:
		    1, 600,

				//lfo.Pfreq = value;
				//lfo.updateparams ();
				//break;
			//case 11:
			0, 127,

				//lfo.Pstereo = value;
				//lfo.updateparams ();
				//break;
			//case 12:
			0, 9,  // type value
			/*
            Sine
            Tri
            RampUp
            RampDown
            ZigZag
            M.Sqare
            M.Saw
			L. Fractal
            L. Fractal XY
            S/H Random*/

				//lfo.PLFOtype = value;
				//lfo.updateparams ();
				//break;
			//case 13:
			0, 127,

				//lfo.Prandomness = value;
				//lfo.updateparams ();
				//break;
			//case 14:
			0,1,
				//Pintense = value;
				//break;


		};
		int DFlangePrint[] = {
			-64,64,
			-64,64,
			-64,64,
			20,500,
			0,3000, // 4
			0,100,
			-64,64,
			0,100, // 7
			0,1, // 8
			0,1, // 9
			1,600, // 10
			0,127, // 11
			0,9, // 12
			0,127, // 13
			0,1, // 14
		};
		real = DFlangeReal;
		print = DFlangePrint;
		presetTexts.clear();
		presetTexts.push_back("Preset 1");
		presetTexts.push_back("Flange-Wha");
		presetTexts.push_back("FbFlange");
		presetTexts.push_back("SoftFlange");
		presetTexts.push_back("Flanger");
		presetTexts.push_back("Chorus 1");
		presetTexts.push_back("Chorus 2");

		mPanels[whereis] = new PanelNS::Panel(mGUI, (VstPlugin*)effect, ((VstPlugin*)effect)->mEffDualFlange, "Dual Flange", whereis, dflangepresets, dflangePRESET_SIZE, dflangeNUM_PRESETS, presetTexts);
		iii=0;
		mPanels[whereis]->AddParamData(PanelNS::Data(iii, real[iii*2], real[iii*2+1], print[iii*2], print[iii*2+1], "Wet/Dry", PanelNS::Slider));
		iii=1;
		mPanels[whereis]->AddParamData(PanelNS::Data(iii, real[iii*2], real[iii*2+1], print[iii*2], print[iii*2+1], "Panning", PanelNS::Slider));
		iii=2;
		mPanels[whereis]->AddParamData(PanelNS::Data(iii, real[iii*2], real[iii*2+1], print[iii*2], print[iii*2+1], "L/R.Cr", PanelNS::Slider));
		iii=3;
		mPanels[whereis]->AddParamData(PanelNS::Data(iii, real[iii*2], real[iii*2+1], print[iii*2], print[iii*2+1], "Depth", PanelNS::Slider));
		iii=4;
		mPanels[whereis]->AddParamData(PanelNS::Data(iii, real[iii*2], real[iii*2+1], print[iii*2], print[iii*2+1], "Width", PanelNS::Slider));

		iii=5;
		mPanels[whereis]->AddParamData(PanelNS::Data(iii, real[iii*2], real[iii*2+1], print[iii*2], print[iii*2+1], "Offset", PanelNS::Slider));
		iii=6;
		mPanels[whereis]->AddParamData(PanelNS::Data(iii, real[iii*2], real[iii*2+1], print[iii*2], print[iii*2+1], "Fb", PanelNS::Slider));
		iii=7;
		mPanels[whereis]->AddParamData(PanelNS::Data(iii, real[iii*2], real[iii*2+1], print[iii*2], print[iii*2+1], "LPF", PanelNS::Slider, true));

		iii=8;
		mPanels[whereis]->AddParamData(PanelNS::Data(iii, real[iii*2], real[iii*2+1], print[iii*2], print[iii*2+1], "Subtract", PanelNS::OnOff));
		iii=9;
		mPanels[whereis]->AddParamData(PanelNS::Data(iii, real[iii*2], real[iii*2+1], print[iii*2], print[iii*2+1], "Th.Zero", PanelNS::OnOff, false, true));

		iii=10;
		mPanels[whereis]->AddParamData(PanelNS::Data(iii, real[iii*2], real[iii*2+1], print[iii*2], print[iii*2+1], "Tempo", PanelNS::Slider));
		iii=11;
		mPanels[whereis]->AddParamData(PanelNS::Data(iii, real[iii*2], real[iii*2+1], print[iii*2], print[iii*2+1], "St.df", PanelNS::Slider));
		lfoTypeStrs.clear();
		lfoTypeStrs.push_back("Sine");
		lfoTypeStrs.push_back("Tri");
		lfoTypeStrs.push_back("RampUp");
		lfoTypeStrs.push_back("RampDn");
		lfoTypeStrs.push_back("ZigZag");
		lfoTypeStrs.push_back("M.Sqare");
		lfoTypeStrs.push_back("M.Saw");
		lfoTypeStrs.push_back("L.Fract");
		lfoTypeStrs.push_back("L.FractXY");
		lfoTypeStrs.push_back("S/H Rnd");
		iii=12;
		mPanels[whereis]->AddParamData(PanelNS::Data(iii, real[iii*2], real[iii*2+1], print[iii*2], print[iii*2+1],  "LFOType", PanelNS::Selection, false, false, lfoTypeStrs));
		iii=13;
		mPanels[whereis]->AddParamData(PanelNS::Data(iii, real[iii*2], real[iii*2+1], print[iii*2], print[iii*2+1], "Rnd", PanelNS::Slider));
		if(loadPrev)
			mPanels[whereis]->LoadPreset(prevIdx);
		else
			mPanels[whereis]->SetPreset(0);

	}
	break;
	case EffRing:
	{
		const int ringPRESET_SIZE = 13;
		const int ringNUM_PRESETS = 6;
		int ringpresets[] = {
			//Saw-Sin
			-64, 0, -64, 64, 35, 1, 0, 20, 0, 40, 0, 64, 1,
			//E string
			0, 0, 0, 64, 100, 82, 0, 100, 0, 0, 0, 64, 0,
			//A string
			0, 0, 0, 64, 100, 110, 0, 0, 100, 50, 0, 64, 0,
			//dissonance
			0, 0, 0, 64, 100, 817, 0, 20, 0, 100, 0, 64, 1,
			//Fast Beat
			0, 0, 0, 64, 100, 15, 0, 20, 0, 100, 0, 64, 1,
			//Ring Amp
			0, 0, 0, 64, 100, 1, 0, 20, 0, 100, 0, 64, 0,
		};
		
		int RingReal[] = {
			//case 0:
			-64,64,
				//Pvolume = value;
				//outvolume = (float)(64+value)/128.0f;
				//break;
			//case 1:
			-64,64,
				//setpanning (value);
				//break;
			//case 2:
			-64,64,
				//setlrcross (value);
				//break;
			//case 3:
			0,127,
				//Plevel = value;
				//break;
			//case 4:
			0,100,
				//Pdepthp = value;
				//depth = (float) Pdepthp / 100.0;
				//idepth = 1.0f - depth;
				//break;
			//case 5:
			-6,166,
				//if(value > 20000) {	//Make sure bad inputs can't cause buffer overflow
					//Pfreq = 20000;
				//} else if (value < 1) {
					//Pfreq = 1;
				//} else {
					//Pfreq = value;
				//}
				//break;
			//case 6:
			0,1,
				//if (value > 1)
					//value = 1;
				//Pstereo = value;
				//break;
			//case 7:
			0,100,
				//Psin = value;
				//sin = (float) Psin / 100.0;
				//setscale();
				//break;
			//case 8:
			0,100,
				//Ptri = value;
				//tri = (float) Ptri / 100.0;
				//setscale();
				//break;
			//case 9:
			0,100,
				//Psaw = value;
				//saw = (float) Psaw / 100.0;
				//setscale();
				//break;
			//case 10:
			0,100,
				//Psqu = value;
				//squ = (float) Psqu / 100.0;
				//setscale();
				//break;
			//case 11:
			1,127,
				//Pinput = value;
				//break;
			//case 12:
			0,1,
				//Pafreq = value;
				//break;

		//

		};
		int RingPrint[] = {
			-64,64,
			-64,64,
			-64,64, // 2
			0,127,
			0,100, // 4
			0,100,
			0,1, // 6
			0,100,
			0,100,
			0,100,
			0,100, // 10
			1,127,
			0,1,
		}; 
		real = RingReal;
		print = RingPrint;
		presetTexts.clear();
		presetTexts.push_back("Saw-Sin");
		presetTexts.push_back("E string");
		presetTexts.push_back("A string");
		presetTexts.push_back("dissonance");
		presetTexts.push_back("Fast Beat");
		presetTexts.push_back("Ring Amp");
		mPanels[whereis] = new PanelNS::Panel(mGUI, (VstPlugin*)effect, ((VstPlugin*)effect)->mEffRing, "Ring", whereis, ringpresets, ringPRESET_SIZE, ringNUM_PRESETS, presetTexts);
		iii=0;
		mPanels[whereis]->AddParamData(PanelNS::Data(iii, real[iii*2], real[iii*2+1], print[iii*2], print[iii*2+1], "Wet/Dry", PanelNS::Slider));
		iii=2;
		mPanels[whereis]->AddParamData(PanelNS::Data(iii, real[iii*2], real[iii*2+1], print[iii*2], print[iii*2+1], "L/R.Cr", PanelNS::Slider));
		iii=11;
		mPanels[whereis]->AddParamData(PanelNS::Data(iii, real[iii*2], real[iii*2+1], print[iii*2], print[iii*2+1], "Input", PanelNS::Slider));
		iii=3;
		mPanels[whereis]->AddParamData(PanelNS::Data(iii, real[iii*2], real[iii*2+1], print[iii*2], print[iii*2+1], "Level", PanelNS::Slider));
		iii=1;
		mPanels[whereis]->AddParamData(PanelNS::Data(iii, real[iii*2], real[iii*2+1], print[iii*2], print[iii*2+1], "Pan", PanelNS::Slider));
		iii=6;
		mPanels[whereis]->AddParamData(PanelNS::Data(iii, real[iii*2], real[iii*2+1], print[iii*2], print[iii*2+1], "Stereo", PanelNS::OnOff));
		iii=12;
		mPanels[whereis]->AddParamData(PanelNS::Data(iii, real[iii*2], real[iii*2+1], print[iii*2], print[iii*2+1], "AutoFreq", PanelNS::OnOff, false, true));
		iii=4;
		mPanels[whereis]->AddParamData(PanelNS::Data(iii, real[iii*2], real[iii*2+1], print[iii*2], print[iii*2+1], "Depth", PanelNS::Slider));
		iii=5;
		mPanels[whereis]->AddParamData(PanelNS::Data(iii, real[iii*2], real[iii*2+1], print[iii*2], print[iii*2+1], "Freq", PanelNS::Slider, true));
		iii=7;
		mPanels[whereis]->AddParamData(PanelNS::Data(iii, real[iii*2], real[iii*2+1], print[iii*2], print[iii*2+1], "Sin", PanelNS::Slider));
		iii=8;
		mPanels[whereis]->AddParamData(PanelNS::Data(iii, real[iii*2], real[iii*2+1], print[iii*2], print[iii*2+1], "Tri", PanelNS::Slider));
		iii=9;
		mPanels[whereis]->AddParamData(PanelNS::Data(iii, real[iii*2], real[iii*2+1], print[iii*2], print[iii*2+1], "Saw", PanelNS::Slider));
		iii=10;
		mPanels[whereis]->AddParamData(PanelNS::Data(iii, real[iii*2], real[iii*2+1], print[iii*2], print[iii*2+1], "Squ", PanelNS::Slider));
		if(loadPrev)
			mPanels[whereis]->LoadPreset(prevIdx);
		else
			mPanels[whereis]->SetPreset(0);

	}
	break;
	case EffExciter:
	{
		const int exciPRESET_SIZE = 13;
		const int exciNUM_PRESETS = 5;
		int excipresets[] = {
			//Plain
			64, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 20000, 20,
			//Loudness
			64, 0, 0, 0, 0, 24, 0, -24, 0, 24, 0, 80, 20,
			//Exciter 1
			64, 64, 0, 0, 0, 64, 0, 0, 0, 64, 0, 20000, 20,
			//Exciter 2
			64, 0, 0, 0, -32, 0, -32, -64, 0, 48, 0, 14100, 5660,
			//Exciter 3
			64, 64, 0, -64, 0, 64, 0, -64, 0, 64, 0, 20000, 20

		};
		int ExciterReal[] = {
			//switch (npar) {
			//case 0:
			0,127,
				//setvolume (value);
				//break;
			//case 1:
			-64,64,
				//sethar(0,value);
				//break;
			//case 2:
			-64,64,
				//sethar(1,value);
				//break;
			//case 3:
			-64,64,
				//sethar(2,value);
				//break;
			//case 4:
			-64,64,
				//sethar(3,value);
				//break;
			//case 5:
			-64,64,
				//sethar(4,value);
				//break;
			//case 6:
			-64,64,
				//sethar(5,value);
				//break;
			//case 7:
			-64,64,
				//sethar(6,value);
				//break;
			//case 8:
			-64,64,
				//sethar(7,value);
				//break;
			//case 9:
			-64,64,
				//sethar(8,value);
				//break;
			//case 10:
			-64,64,
				//sethar(9,value);
				//break;
			//case 11:
			47,171, // 20~26000, 이 값을 GetFreqByRealMinMax로 변환하면 주파수가 나온다.
				//setlpf(value);
				//break;
			//case 12:
			47,166, // 20~20000
				//sethpf(value);
				//break;

		//

		};
		int ExciterPrint[] = {
			0,127,
			-64,64,
			-64,64, // 2
			-64,64,
			-64,64, // 4
			-64,64,
			-64,64, // 6
			-64,64,
			-64,64, // 8
			-64,64,
			-64,64, // 10
			0,100,
			0,100, // 12
		};
		real = ExciterReal;
		print = ExciterPrint;
		presetTexts.clear();
		presetTexts.push_back("Plain");
		presetTexts.push_back("Loudness");
		presetTexts.push_back("Exciter 1");
		presetTexts.push_back("Exciter 2");
		presetTexts.push_back("Exciter 3");
		mPanels[whereis] = new PanelNS::Panel(mGUI, (VstPlugin*)effect, ((VstPlugin*)effect)->mEffExciter, "Exciter", whereis, excipresets, exciPRESET_SIZE, exciNUM_PRESETS, presetTexts);
		iii=0;
		mPanels[whereis]->AddParamData(PanelNS::Data(iii, real[iii*2], real[iii*2+1], print[iii*2], print[iii*2+1], "Gain", PanelNS::Slider));
		iii=11;
		mPanels[whereis]->AddParamData(PanelNS::Data(iii, real[iii*2], real[iii*2+1], print[iii*2], print[iii*2+1], "LPF", PanelNS::Slider, true));
		iii=12;
		mPanels[whereis]->AddParamData(PanelNS::Data(iii, real[iii*2], real[iii*2+1], print[iii*2], print[iii*2+1], "HPF", PanelNS::Slider, true));


		iii=1;
		mPanels[whereis]->AddParamData(PanelNS::Data(iii, real[iii*2], real[iii*2+1], print[iii*2], print[iii*2+1], "Har 1", PanelNS::Slider));
		iii=2;
		mPanels[whereis]->AddParamData(PanelNS::Data(iii, real[iii*2], real[iii*2+1], print[iii*2], print[iii*2+1], "Har 2", PanelNS::Slider));
		iii=3;
		mPanels[whereis]->AddParamData(PanelNS::Data(iii, real[iii*2], real[iii*2+1], print[iii*2], print[iii*2+1], "Har 3", PanelNS::Slider));
		iii=4;
		mPanels[whereis]->AddParamData(PanelNS::Data(iii, real[iii*2], real[iii*2+1], print[iii*2], print[iii*2+1], "Har 4", PanelNS::Slider));
		iii=5;
		mPanels[whereis]->AddParamData(PanelNS::Data(iii, real[iii*2], real[iii*2+1], print[iii*2], print[iii*2+1], "Har 5", PanelNS::Slider));
		iii=6;
		mPanels[whereis]->AddParamData(PanelNS::Data(iii, real[iii*2], real[iii*2+1], print[iii*2], print[iii*2+1], "Har 6", PanelNS::Slider));
		iii=7;
		mPanels[whereis]->AddParamData(PanelNS::Data(iii, real[iii*2], real[iii*2+1], print[iii*2], print[iii*2+1], "Har 7", PanelNS::Slider));
		iii=8;
		mPanels[whereis]->AddParamData(PanelNS::Data(iii, real[iii*2], real[iii*2+1], print[iii*2], print[iii*2+1], "Har 8", PanelNS::Slider));
		iii=9;
		mPanels[whereis]->AddParamData(PanelNS::Data(iii, real[iii*2], real[iii*2+1], print[iii*2], print[iii*2+1], "Har 9", PanelNS::Slider));
		iii=10;
		mPanels[whereis]->AddParamData(PanelNS::Data(iii, real[iii*2], real[iii*2+1], print[iii*2], print[iii*2+1], "Har 10", PanelNS::Slider));
		if(loadPrev)
			mPanels[whereis]->LoadPreset(prevIdx);
		else
			mPanels[whereis]->SetPreset(0);
		
	}
	break;
	case EffMBDist:
	{

		const int mbdistPRESET_SIZE = 15;
		const int mbdistNUM_PRESETS = 8;
		int mbdistpresets[] = {
			//Saturation
			0, 64, 0, 41, 64, 26, 19, 26, 41, 20, 35, 0, 400, 1200, 0,
			//Dist 1
			0, 64, 64, 20, 64, 0, 14, 13, 38, 49, 40, 0, 288, 1315, 0,
			//Soft
			0, 64, 0, 32, 64, 6, 13, 6, 50, 70, 50, 0, 400, 1800, 0,
			//Modulated
			0, 64, 0, 36, 64, 18, 17, 18, 40, 70, 30, 0, 500, 2200, 0,
			//Crunch
			0, 64, 0, 24, 64, 19, 14, 19, 30, 80, 30, 0, 800, 1800, 0,
			//Dist 2
			0, 64, 0, 64, 64, 22, 27, 22, 25, 50, 25, 0, 440, 1500, 0,
			//Dist 3
			0, 64, 0, 64, 64, 27, 22, 27, 50, 69, 50, 0, 800, 1200, 0,
			//Dist 4
			0, 64, 0, 30, 64, 19, 25, 26, 20, 51, 83, 0, 329, 800, 0

		};
		int MBDistReal[] = {
			//case 0:
			0,127,
				//setvolume (value);
				//break;
			//case 1:
			0,127,
				//setpanning (value);
				//break;
			//case 2:
			0,127,
				//setlrcross (value);
				//break;
			//case 3:
			0,127,
				//Pdrive = value;
				//PdriveL = (int)((float)Pdrive*volL);
				//PdriveM = (int)((float)Pdrive*volM);
				//PdriveH = (int)((float)Pdrive*volH);
				//break;
			//case 4:
			0,127,
				//Plevel = value;
				//break;
			//case 5:
			0,29,
			/*
		vector<string> mTypeStrs;
		mTypeStrs.push_back("Atan");
		mTypeStrs.push_back("Asym");
		mTypeStrs.push_back("Pow");
		mTypeStrs.push_back("Sine");
		mTypeStrs.push_back("Quant");
		mTypeStrs.push_back("ZigZag");
		mTypeStrs.push_back("Lim");
		mTypeStrs.push_back("UpLim");
		mTypeStrs.push_back("LoLim");
		mTypeStrs.push_back("InvLim");

		mTypeStrs.push_back("Clip");
		mTypeStrs.push_back("Asym2");
		mTypeStrs.push_back("Pow2");
		mTypeStrs.push_back("Sigmoid");
		mTypeStrs.push_back("Crunch");
		mTypeStrs.push_back("HardCr");
		mTypeStrs.push_back("OctvUp");
		mTypeStrs.push_back("MSquare");
		mTypeStrs.push_back("MSaw");
		mTypeStrs.push_back("Compres");

		mTypeStrs.push_back("Overdrv");
		mTypeStrs.push_back("Soft");
		mTypeStrs.push_back("SupSoft");
		mTypeStrs.push_back("HardCmp");
		mTypeStrs.push_back("LmtNoG");
		mTypeStrs.push_back("FET");
		mTypeStrs.push_back("DynoFET");
		mTypeStrs.push_back("Valve1");
		mTypeStrs.push_back("Valve2");
		mTypeStrs.push_back("DiodeClp");

			*/
				//PtypeL = value;
				//break;
			//case 6:
			0,29,
				//PtypeM = value;
				//break;
			//case 7:
			0,29,
				//PtypeH = value;
				//break;
			//case 8:
			0,100,
				//PvolL = value;
				//volL = (float) value /100.0;
				//PdriveL = (int)((float)Pdrive*volL);
				//break;
			//case 9:
			0,100,
				//PvolM = value;
				//volM = (float) value /100.0;
				//PdriveM = (int)((float)Pdrive*volM);
				//break;
			//case 10:
			0,100,
				//PvolH = value;
				//volH = (float) value /100.0;
				//PdriveH = (int)((float)Pdrive*volH);
				//break;
			//case 11:
			0,1,
				//Pnegate = value;
				//break;
			//case 12:
			47,115,
				//setCross1 (value);
				//break;
			//case 13:
			110,158,
				//setCross2 (value);
				//break;
			//case 14:
			0,1,
				//Pstereo = value;
				//break;


		};
		int MBDistPrint[] = {
			-64,63,
			-64,63,
			-64,63, // 2
			0,127,
			0,127, // 4
			0,29,
			0,29, // 6
			0,29,
			0,100, // 8
			0,100, // 9
			0,100,// 10
			0,1, // 11
			0,100, // 12
			0,100,
			0,1,
		};
		real = MBDistReal;
		print = MBDistPrint;
		presetTexts.clear();
		presetTexts.push_back("Saturation");
		presetTexts.push_back("Dist 1");
		presetTexts.push_back("Soft");
		presetTexts.push_back("Modulated");
		presetTexts.push_back("Crunch");
		presetTexts.push_back("Dist 2");
		presetTexts.push_back("Dist 3");
		presetTexts.push_back("Dist 4");
		mPanels[whereis] = new PanelNS::Panel(mGUI, (VstPlugin*)effect, ((VstPlugin*)effect)->mEffMBDist, "DistBand", whereis, mbdistpresets, mbdistPRESET_SIZE, mbdistNUM_PRESETS, presetTexts);
		iii=0;
		mPanels[whereis]->AddParamData(PanelNS::Data(iii, real[iii*2], real[iii*2+1], print[iii*2], print[iii*2+1], "Wet/Dry", PanelNS::Slider));
		iii=2;
		mPanels[whereis]->AddParamData(PanelNS::Data(iii, real[iii*2], real[iii*2+1], print[iii*2], print[iii*2+1], "L/R.Cr", PanelNS::Slider));
		iii=3;
		mPanels[whereis]->AddParamData(PanelNS::Data(iii, real[iii*2], real[iii*2+1], print[iii*2], print[iii*2+1], "Drive", PanelNS::Slider));
		iii=4;
		mPanels[whereis]->AddParamData(PanelNS::Data(iii, real[iii*2], real[iii*2+1], print[iii*2], print[iii*2+1], "Level", PanelNS::Slider));
		iii=8;
		mPanels[whereis]->AddParamData(PanelNS::Data(iii, real[iii*2], real[iii*2+1], print[iii*2], print[iii*2+1], "L.Gain", PanelNS::Slider));
		iii=9;
		mPanels[whereis]->AddParamData(PanelNS::Data(iii, real[iii*2], real[iii*2+1], print[iii*2], print[iii*2+1], "M.Gain", PanelNS::Slider));
		iii=10;
		mPanels[whereis]->AddParamData(PanelNS::Data(iii, real[iii*2], real[iii*2+1], print[iii*2], print[iii*2+1], "H.Gain", PanelNS::Slider));
		iii=12;
		mPanels[whereis]->AddParamData(PanelNS::Data(iii, real[iii*2], real[iii*2+1], print[iii*2], print[iii*2+1], "H.Gain", PanelNS::Slider, true));
		iii=13;
		mPanels[whereis]->AddParamData(PanelNS::Data(iii, real[iii*2], real[iii*2+1], print[iii*2], print[iii*2+1], "H.Gain", PanelNS::Slider, true));

		vector<string> mTypeStrs;
		mTypeStrs.push_back("Atan");
		mTypeStrs.push_back("Asym");
		mTypeStrs.push_back("Pow");
		mTypeStrs.push_back("Sine");
		mTypeStrs.push_back("Quant");
		mTypeStrs.push_back("ZigZag");
		mTypeStrs.push_back("Lim");
		mTypeStrs.push_back("UpLim");
		mTypeStrs.push_back("LoLim");
		mTypeStrs.push_back("InvLim");

		mTypeStrs.push_back("Clip");
		mTypeStrs.push_back("Asym2");
		mTypeStrs.push_back("Pow2");
		mTypeStrs.push_back("Sigmoid");
		mTypeStrs.push_back("Crunch");
		mTypeStrs.push_back("HardCr");
		mTypeStrs.push_back("OctvUp");
		mTypeStrs.push_back("MSquare");
		mTypeStrs.push_back("MSaw");
		mTypeStrs.push_back("Compres");

		mTypeStrs.push_back("Overdrv");
		mTypeStrs.push_back("Soft");
		mTypeStrs.push_back("SupSoft");
		mTypeStrs.push_back("HardCmp");
		mTypeStrs.push_back("LmtNoG");
		mTypeStrs.push_back("FET");
		mTypeStrs.push_back("DynoFET");
		mTypeStrs.push_back("Valve1");
		mTypeStrs.push_back("Valve2");
		mTypeStrs.push_back("DiodeClp");
		iii=5;
		mPanels[whereis]->AddParamData(PanelNS::Data(iii, real[iii*2], real[iii*2+1], print[iii*2], print[iii*2+1],  "TypeL", PanelNS::Selection, false, false, mTypeStrs));
		iii=6;
		mPanels[whereis]->AddParamData(PanelNS::Data(iii, real[iii*2], real[iii*2+1], print[iii*2], print[iii*2+1],  "TypeM", PanelNS::Selection, false, false, mTypeStrs));
		iii=7;
		mPanels[whereis]->AddParamData(PanelNS::Data(iii, real[iii*2], real[iii*2+1], print[iii*2], print[iii*2+1],  "TypeH", PanelNS::Selection, false, false, mTypeStrs));
		iii=1;
		mPanels[whereis]->AddParamData(PanelNS::Data(iii, real[iii*2], real[iii*2+1], print[iii*2], print[iii*2+1], "Pan", PanelNS::Slider));
		iii=14;
		mPanels[whereis]->AddParamData(PanelNS::Data(iii, real[iii*2], real[iii*2+1], print[iii*2], print[iii*2+1], "Stereo", PanelNS::OnOff));
		iii=11;
		mPanels[whereis]->AddParamData(PanelNS::Data(iii, real[iii*2], real[iii*2+1], print[iii*2], print[iii*2+1], "Neg.", PanelNS::OnOff, false, true));
		if(loadPrev)
			mPanels[whereis]->LoadPreset(prevIdx);
		else
			mPanels[whereis]->SetPreset(0);


	}
	break;
	case EffArpie:
	{
		CreateArpie(whereis, loadPrev, prevIdx);
	}
	break;
	case EffExpander:
	{
		CreateExpander(whereis, loadPrev, prevIdx);
	}
	break;
	case EffEchotron:
	{
		CreateEchotron(whereis, loadPrev, prevIdx);

	}
	break;
	case EffShuffle:
	{
		CreateShuffle(whereis, loadPrev, prevIdx);
	}
	break;
	case EffConvolotron:
	{
		CreateConvolotron(whereis, loadPrev, prevIdx);
		
	}
	break;
	case EffSynthfilter:
	{
		CreateSynthfilter(whereis, loadPrev, prevIdx);

	}
	break;
	case EffReverbtron:
	{
		CreateReverbtron(whereis, loadPrev, prevIdx);

	}
	break;
	
	case EffMBVvol:
	{
		CreateMVVvol(whereis, loadPrev, prevIdx);
	}
	break;
	case EffRyanWah:
	{
		CreateRyanWah(whereis, loadPrev, prevIdx);

	}
	break;
	default:
		break;
	}
	string effName;
	for(int i=0; i< mEffectNames.size(); ++i)
	{
		if(mEffectNames[i].type == type)
		{
			effName = mEffectNames[i].name;
			break;
		}
	}
	mUsingEffectList.push_back(EffectName(type, effName));
	mBuiltPanels[whereis] = type;
}
int ExampleEditor::GetEffectPreset(int whereis)
{
	switch(mBuiltPanels[whereis])
	{
	case EffNone:
		break;
	case EffLinealEQ:
		if(mEQ1Panel)
			return mEQ1Panel->mPrevPreset;
		break;
	case EffDistortion:
		if(mDistPanel)
			return mDistPanel->mPrevPreset;
		break;
	case EffCompressor:
		if(mCompressorPanel)
			return mCompressorPanel->mPrevPreset;
		break;
	case EffEcho:
		if(mEchoPanel)
			return mEchoPanel->mPrevPreset;
		break;
	default:
		if(mPanels[whereis])
			return mPanels[whereis]->mPrevPreset;
		break;
	}
	return -1;
}
void ExampleEditor::DeleteEffectPanel(int whereis)
{
	EffNameType type = mBuiltPanels[whereis];
	switch(mBuiltPanels[whereis])
	{
	case EffNone:
		break;
	case EffLinealEQ:
		mEQ1Panel->Delete();
		break;
	case EffDistortion:
		mDistPanel->Delete();
		break;
	case EffCompressor:
		mCompressorPanel->Delete();
		break;
	case EffEcho:
		mEchoPanel->Delete();
		break;
	default:
		if(mPanels[whereis]) // TODO: 여기서 실제 Delete가 아닌 mEchoPanel->Delete처럼 해주고 실제 포인터들은 어딘가에 저장해둔다.
			delete mPanels[whereis];
		mPanels[whereis] = nullptr;
		break;
	}
	for(int i=0; i<mUsingEffectList.size(); ++i)
	{
		if(mUsingEffectList[i].type == type)
		{
			mUsingEffectList.erase(mUsingEffectList.begin()+i);
			break;
		}
	}
	mBuiltPanels[whereis] = EffNone;
}

MyTotalEffectOnOff::MyTotalEffectOnOff(ExampleEditor *editor)
	:OnOffButtonCallback(), mEditor(editor)
{
}
void MyTotalEffectOnOff::OnOn()
{
	mEditor->mTotalEffectOn = true;
}
void MyTotalEffectOnOff::OnOff()
{
	mEditor->mTotalEffectOn = false;
}

MyEffectOnOff::MyEffectOnOff(ExampleEditor *editor, int whereis)
	:OnOffButtonCallback(), mEditor(editor), mWhereis(whereis)
{
}
void MyEffectOnOff::OnOn()
{
	mEditor->mEffectOn[mWhereis] = true;
}
void MyEffectOnOff::OnOff()
{
	mEditor->mEffectOn[mWhereis] = false;
}

// 이제 이펙트를 움직여도(삭제->재생성) 파라메터가 변경되지 않도록 해야한다.
// 이펙트 익스체인지시에는 관계 없음
// SetPreset말고 LoadPreset을 부르게 하면 된다. presetIdx만 저장하면 됨