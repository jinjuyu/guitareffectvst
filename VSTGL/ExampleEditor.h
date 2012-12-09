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
#include <vector>
#include <math.h>
#include "../guitareffectVST/ParamAuto.h"

using namespace std;
///	Simple VSTGL example.
#pragma warning(disable: 4018)
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

inline double logB(double x, double base) {
  return log(x) / log(base);
}

inline float GetFreqByRealMinMax(int val)
{
	return 440.0f * powf(2.0f,(((float)val-100.0f)/12.0f));
}
inline int GetRealMinMaxByFreq(float freq)
{
	return (int)((12.0f*(logB(freq/440.0f, 2.0))+100)+0.5f);
}

class GLGUI;
class GUIElement
{
public:
	GUIElement(int handle, GLGUI *gui);
	virtual void OnMouseDown(int button, int x, int y)
	{
	}
	virtual void OnMouseUp(int button, int x, int y)
	{
	}
	virtual void OnMouseMove(int x, int y)
	{
	}
	virtual void Draw()
	{
	}
	GLGUI *mGUI;
	int mHandle;
	bool hidden;
};
class SliderCallback
{
public:
	SliderCallback()
	{
	}
	virtual void SetVal(int val)
	{
	}
	virtual void OnRDown()
	{
	}
	
};
class ButtonCallback
{
public:
	ButtonCallback()
	{
	}
	virtual void OnClick()
	{
	}
};
class OnOffButtonCallback
{
public:
	OnOffButtonCallback()
	{
	}
	virtual void OnOn()
	{
	}
	virtual void OnOff()
	{
	}
};
class ListBoxCallback
{
public:
	ListBoxCallback()
	{
	}
	virtual void OnSelect(int idx)
	{
	}
};
class TabbedListBoxCallback
{
public:
	TabbedListBoxCallback()
	{
	}
	virtual void OnSelect(int idx)
	{
	}
	virtual void OnPageSelect(int idx)
	{
	}
};
class TabbedListBox;
class GLGUI
{
public:
	GLGUI(void *hInstance);
	TabbedListBox *mPopupList;
	~GLGUI()
	{
		/*for(GUIElements::iterator i=mGUIElements.begin(); i != mGUIElements.end(); ++i)
		{
			delete (*i);
		}*/
		cleanup();
	}
	void AddElement(GUIElement *ele)
	{
		mGUIElements.push_back(ele);
	}
	GUIElement *GetElement(int handle)
	{
		for(GUIElements::iterator it=mGUIElements.begin(); it != mGUIElements.end(); ++it)
		{
			if((*it)->mHandle == handle)
			{
				return *it;
			}
		}
		return nullptr;
	}
	int GetNewHandle()
	{
		int result = handleCounter;
		handleCounter++;
		return result;
	}
	void Show(int handle, bool show)
	{
		for(GUIElements::iterator i=mGUIElements.begin(); i != mGUIElements.end(); ++i)
		{
			if((*i)->mHandle == handle)
			{
				(*i)->hidden = show;
				break;
			}
		}
	}
	int NewSlider(int x, int y, int w, int min_, int max_, bool isFreq=false);
	void SetSliderVal(int handle, int val);
	void SetSliderCallback(int handle, SliderCallback *cb);
	int NewList(int x,int y,int w,int h, ListBoxCallback *cb);
	void AddToList(int handle, string label, int idx=-1);
	void DeleteListItem(int handle, int idx);
	int NewTList(int x,int y,int w,int h, TabbedListBoxCallback *cb);
	void AddToTList(int handle, string label, int idx=-1);
	void DeleteTabbedListItem(int handle, int idx);
	int NewButton(int x, int y, int w, int h, string label, ButtonCallback *cb);
	int NewOnOffButton(int x, int y, int w, int h, string label, OnOffButtonCallback *cb);
	void DeleteGUIElement(int handle)
	{
		for(GUIElements::iterator i=mGUIElements.begin(); i != mGUIElements.end(); ++i)
		{
			if((*i)->mHandle == handle)
			{
				(*i)->hidden = true;
				GUIElement *item = *i;
				mGUIElements.erase(i);
				delete item;
				break;
			}
		}
		mGUIDeleted = true;
	}
	bool mGUIDeleted;
	int handleCounter;

	void DrawQuad(QuadOption &op);
	void DrawQuadBorder(QuadOptionBorder &op, int borderThick=1);
	void *m_hInstance;
	void init();
	void cleanup();
	GLvoid Print(TextOption &op, const char *fmt, ...);
	GLvoid Print2(TextOption &op, const char *fmt, ...);
	void DrawElements()
	{
		for(GUIElements::iterator i=mGUIElements.begin(); i != mGUIElements.end(); ++i)
		{
			if(!(*i)->hidden)
				(*i)->Draw();
		}
	}
	void onMouseDown(int button, int x, int y)
	{
		// GUIElements->OnMouseDown에서 mGUIElements자체를 수정하게 된다.
		// 그러므로 이 코드는 invalid
		// mGUIElements를 카피해서 써야한다.
		// 아 그래도 안된다.
		// 하나의 엘리먼트가 멀티플한 엘리먼트를 삭제하게 된다.
		// 어떻게 할지 고민좀 해보자.
		GUIElements copy;
		GUIElements alreadyUsed;
		for(int i=0; i < mGUIElements.size(); ++i)
		{
			copy.push_back(mGUIElements[i]);
		}
		int i=0;
		int max = copy.size();
		while(i < max)
		{
			bool found = false;
			for(int j=0; j< alreadyUsed.size(); ++j)
			{
				if(copy[i] == alreadyUsed[j])
					found = true;
			}
			if(!(copy[i])->hidden && !found)
				(copy[i])->OnMouseDown(button,x,y);
			alreadyUsed.push_back(copy[i]);
			i++;
			if(mGUIDeleted)
			{
				i = 0;
				copy.clear();
				for(int j=0; j < mGUIElements.size(); ++j)
				{
					copy.push_back(mGUIElements[j]);
				}
				mGUIDeleted = false;
				max = copy.size();
			}
		}
	}
	void onMouseUp(int button, int x, int y)
	{
		GUIElements copy;
		GUIElements alreadyUsed;

		for(int i=0; i < mGUIElements.size(); ++i)
		{
			copy.push_back(mGUIElements[i]);
		}
		int i=0;
		int max = copy.size();

		while(i < max)
		{
			bool found = false;
			for(int j=0; j< alreadyUsed.size(); ++j)
			{
				if(copy[i] == alreadyUsed[j])
					found = true;
			}
			if(!(copy[i])->hidden && !found)
				(copy[i])->OnMouseUp(button,x,y);
			alreadyUsed.push_back(copy[i]);

			i++;
			if(mGUIDeleted)
			{
				i = 0;
				copy.clear();
				for(int j=0; j < mGUIElements.size(); ++j)
				{
					copy.push_back(mGUIElements[j]);
				}
				mGUIDeleted = false;
				max = copy.size();
			}

		}
	}
	void onMouseMove(int x, int y)
	{
		GUIElements copy;
		GUIElements alreadyUsed;

		for(int i=0; i < mGUIElements.size(); ++i)
		{
			copy.push_back(mGUIElements[i]);
		}
		int i=0;
		int max = copy.size();
		while(i < max)
		{
			bool found = false;
			for(int j=0; j< alreadyUsed.size(); ++j)
			{
				if(copy[i] == alreadyUsed[j])
					found = true;
			}
			if(!(copy[i])->hidden && !found)
				(copy[i])->OnMouseMove(x,y);
			alreadyUsed.push_back(copy[i]);
			i++;
			if(mGUIDeleted)
			{
				i = 0;
				copy.clear();
				for(int j=0; j < mGUIElements.size(); ++j)
				{
					copy.push_back(mGUIElements[j]);
				}
				mGUIDeleted = false;
				max = copy.size();
			}

		}
	}
	typedef vector<GUIElement *> GUIElements;
	GUIElements mGUIElements;
private:
	GLuint image;
	GLuint mFont1;
	GLuint mFont2;

};

bool InRect(int x,int y,int w,int h,int x2,int y2);
class Slider : public GUIElement
{
public:
	Slider(int handle, GLGUI* gui, int x, int y, int w, int min_, int max_, bool isFreq=false)
		:GUIElement(handle, gui), 
		x(x),y(y),w(w),min_(min_),max_(max_),
		line(x+29, y+13/2, w-29, 3, 255,255,255,255, 0,0,0,255),
		slider(x+30, y, 20, 13, 255,255,255,255, 0,0,0,255),
		top(x,y,29,13, 0,0,0,255), mIsFreq(isFreq)

	{
		h = 13;
		LMouseDown = false;
		mCB = nullptr;
	}
	bool mIsFreq;
	SliderCallback *mCB;
	void SetCallback(SliderCallback *cb)
	{
		mCB = cb;
	}

	void Draw()
	{
		mGUI->Print(top, "%d", curVal);
		mGUI->DrawQuadBorder(line);
		mGUI->DrawQuadBorder(slider);
	}
	void OnMouseDown(int button, int x_, int y_)
	{
		if(button == 1 && InRect(slider.x,slider.y,slider.w,slider.h,x_,y_))
		{
			clickedX = x_;
			clickedY = y_;
			LMouseDown = true;
		}
		else if(button == 2 && InRect(x,y,w,h, x_, y_))
		{
			if(mCB) mCB->OnRDown();
		}
	}
	int clickedX, clickedY;
	void OnMouseUp(int button, int x_, int y_)
	{
		if(button == 1) LMouseDown = false;
	}

	void OnMouseMove(int x_, int y_)
	{
		if(LMouseDown)
		{
			slider.x += x_-clickedX;
			clickedX = x_;
			if(slider.x < x+30)
				slider.x = x+30;
			if(slider.x > x+w-1-20)
				slider.x = x+w-1-20;
			int prevVal = curVal;
			UpdateVal();
			if(prevVal != curVal && mCB)
				mCB->SetVal(curVal);
		}
	}
	void UpdateVal()
	{
		int startPosX = x+30;
		int val = slider.x - startPosX;
		float valFloat = (float)val / (float)CalculateTotalSliderLength();
		curVal = (int)((float)min_ + float(max_-min_)*valFloat);
	}
	void SetVal(int val)
	{
		int prevVal = curVal;
		curVal = val;
		if(prevVal != curVal && mCB) mCB->SetVal(curVal);
		SetPosByVal();
	}
	void SetPosByVal()
	{
		int startPosX = x+30;

		float valFloat = float(curVal-min_) / (float)((max_-min_));
		int val = (int)(valFloat * (float)CalculateTotalSliderLength());
		slider.x = val + startPosX;
	}
	int CalculateTotalSliderLength()
	{
		return line.w-slider.w-2;
	}
	bool LMouseDown;

	TextOption top;
	QuadOptionBorder line;
	QuadOptionBorder slider;

	int x,y,w,h,min_,max_;
	int curVal;
};


class Button : public GUIElement
{
public:
	Button(int handle, GLGUI* gui, int x, int y, int w, int h, string label)
		:GUIElement(handle, gui), 
		x(x),y(y),w(w),h(h), mLabel(label),
		top(x,y,w,h, 0,0,0,255),
		button(x,y,w,h, 255,255,255,255, 0,0,0,255)

	{
		mCB = nullptr;
	}
	string mLabel;
	ButtonCallback *mCB;
	void SetCallback(ButtonCallback *cb)
	{
		mCB = cb;
	}

	void Draw()
	{
		mGUI->DrawQuadBorder(button);
		mGUI->Print(top, "%s", mLabel.c_str());
	}
	void OnMouseDown(int button, int x_, int y_)
	{
		if(button == 1 && InRect(x,y,w,h,x_,y_))
		{
			if(mCB) mCB->OnClick();
		}
	}
	TextOption top;
	QuadOptionBorder button;

	int x,y,w,h;
};

class ListBox : public GUIElement
{
public:
	ListBox(int handle, GLGUI* gui, int x, int y, int w, int h)
		:GUIElement(handle, gui), 
		x(x),y(y),w(w),h(h),
		box(x,y,w,h, 255,255,255,255, 0,0,0,255)

	{
		mCB = nullptr;
		selected = -1;
		listH = 15;
	}
	ListBoxCallback *mCB;
	void MoveUpSelection()
	{
		if(selected >= 1 && selected < mStrs.size())
		{
			string backup = mStrs[selected-1];
			mStrs[selected-1] = mStrs[selected];
			mStrs[selected] = backup;
			selected -= 1;
		}
	}
	void MoveDnSelection()
	{
		if(selected >= 0 && selected < mStrs.size()-1)
		{
			string backup = mStrs[selected+1];
			mStrs[selected+1] = mStrs[selected];
			mStrs[selected] = backup;
			selected += 1;
		}
	}
	void SetCallback(ListBoxCallback *cb)
	{
		mCB = cb;
	}
	vector<string> mStrs;
	void Add(string label, int idx = -1)
	{
		if(idx != -1)
			mStrs.insert(mStrs.begin()+idx, label);
		else
			mStrs.push_back(label);
	}
	void Delete(int idx)
	{
		if(idx >= 0 && idx < mStrs.size())
			mStrs.erase(mStrs.begin()+idx);
	}
	int selected;
	int listH;
	void Draw()
	{
		mGUI->DrawQuadBorder(box);
		int curY = y;
		int idx=0;
		for(vector<string>::iterator it = mStrs.begin(); it != mStrs.end(); ++it)
		{
			if(curY + listH > y+h) break;
			TextOption top(x,curY,w,listH, 0,0,0,255);
			if(idx == selected)
			{
				QuadOptionBorder sel(x,curY,w,listH, 32,128,32,255,  0,0,0,255);
				mGUI->DrawQuadBorder(sel);
			}
			curY += listH;
			idx++;
			mGUI->Print(top, "%s", (*it).c_str());
		}
		
	}
	void OnMouseDown(int button, int x_, int y_)
	{
		if(button == 1)
		{
			int curY = y;
			int idx=0;
			bool found = false;
			for(vector<string>::iterator it = mStrs.begin(); it != mStrs.end(); ++it)
			{
				if(curY + listH > y+h) break;
				if(InRect(x,curY,w,listH,x_,y_))
				{
					selected = idx;
					found = true;
				}
				idx++;
				curY += listH;
			}
			if(found && mCB) mCB->OnSelect(selected);
		}
	}
	QuadOptionBorder box;

	int x,y,w,h;
};

class TabbedListBox : public GUIElement
{
public:
	TabbedListBox(int handle, GLGUI* gui, int x, int y, int w, int h)
		:GUIElement(handle, gui), 
		x(x),y(y),w(w),h(h),
		box(x,y,w,h, 255,255,255,255, 0,0,0,255)

	{
		mCB = nullptr;
		selected = -1;
		listH = 15;
		buttonH = 20;
		margin = 3;
		curPage = 0;
	}
	int buttonH;
	int margin;
	TabbedListBoxCallback *mCB;
	void SetCallback(TabbedListBoxCallback *cb)
	{
		mCB = cb;
	}
	vector<string> mStrs;
	void Clear()
	{
		mStrs.clear();
		selected = -1;
		curPage = 0;
	}
	void Add(string label, int idx = -1)
	{
		if(idx != -1)
			mStrs.insert(mStrs.begin()+idx, label);
		else
			mStrs.push_back(label);
	}
	int curPage;
	void Delete(int idx)
	{
		if(idx >= 0 && idx < mStrs.size())
			mStrs.erase(mStrs.begin()+idx);
	}
	int selected;
	int listH;
	int GetNumItemsPerPage()
	{
		return (h-margin*2-buttonH)/listH;
	}
	int GetNumButtons()
	{
		int numItemPerPage = (h-margin*2-buttonH)/listH;
		return (mStrs.size()/numItemPerPage)+1;
	}
	void Draw()
	{
		mGUI->DrawQuadBorder(box);
		QuadOptionBorder boxList(x,y,w,h-margin*2-buttonH, 255,255,255,255, 0,0,0,255);
		mGUI->DrawQuadBorder(boxList);

		for(int i=0; i<GetNumButtons();++i)
		{
			QuadOptionBorder button(x+margin + i*margin + i*buttonH,y+h-margin-buttonH,buttonH, buttonH, 255,255,255,255, 0,0,0,255);
			mGUI->DrawQuadBorder(button);
			TextOption top2(x+margin + i*margin + i*buttonH,y+h-margin-buttonH,buttonH, buttonH, 0,0,0,255);
			mGUI->Print(top2, "%d", i+1);
		}
		int curY = y;
		int idx=0;
		char temp[123];
		sprintf(temp, "%d %d %d", curPage, GetNumItemsPerPage(), mStrs.size());
		//MessageBox(NULL, temp, temp, MB_OK);
		if(curPage*GetNumItemsPerPage() >= 0 && curPage*GetNumItemsPerPage() < mStrs.size())
		{
			for(vector<string>::iterator it = mStrs.begin()+curPage*GetNumItemsPerPage(); it != mStrs.end(); ++it)
			{
				if(curY + listH > y+h-margin*2-buttonH) break;
				TextOption top(x,curY,w,listH, 0,0,0,255);
				if(idx+curPage*GetNumItemsPerPage() == selected)
				{
					QuadOptionBorder sel(x,curY,w,listH, 32,128,32,255,  0,0,0,255);
					mGUI->DrawQuadBorder(sel);
				}
				curY += listH;
				idx++;
				mGUI->Print(top, "%s", (*it).c_str());
			}
		}
		
	}
	void OnMouseDown(int button, int x_, int y_)
	{
		if(button == 1)
		{
			int curY = y;
			int idx=0;
			bool found = false;
			for(vector<string>::iterator it = mStrs.begin()+curPage*GetNumItemsPerPage(); it != mStrs.end(); ++it)
			{
				if(curY + listH > y+h-margin*2-buttonH) break;
				if(InRect(x,curY,w,listH,x_,y_))
				{
					selected = idx+curPage*GetNumItemsPerPage();
					found = true;
					break;
				}
				idx++;
				curY += listH;
			}
			if(found && mCB) mCB->OnSelect(selected);
			
			for(int i=0; i<GetNumButtons();++i)
			{
				if(InRect(x+margin + i*margin + i*buttonH,y+h-margin-buttonH,buttonH, buttonH,x_,y_))
				{
					curPage = i;
					if(mCB) mCB->OnPageSelect(curPage);
					selected = -1;
					if(mCB) mCB->OnSelect(selected);
					break;
				}
			}


		}
	}
	QuadOptionBorder box;

	int x,y,w,h;
};

class OnOffButton : public GUIElement
{
public:
	OnOffButton(int handle, GLGUI* gui, int x, int y, int w, int h, string label)
		:GUIElement(handle, gui), 
		x(x),y(y),w(w),h(h), mLabel(label),
		top(x+17,y,w-17,h, 0,0,0,255),
		button(x,y,w,h, 255,255,255,255, 0,0,0,255),
		indicatorOn(x+14/2-10/2, y+h/2-10/2, 10, 10, 0, 255, 0, 255,  0,0,0,255),
		indicatorOff(x+14/2-10/2, y+h/2-10/2, 10, 10, 0, 0, 0, 255,  0,0,0,255)

	{
		mOn = false;
		mCB = nullptr;
	}
	bool mOn;
	string mLabel;
	
	OnOffButtonCallback *mCB;
	void SetCallback(OnOffButtonCallback *cb)
	{
		mCB = cb;
	}

	void Draw()
	{
		mGUI->DrawQuadBorder(button);
		if(mOn)
			mGUI->DrawQuadBorder(indicatorOn);
		else
			mGUI->DrawQuadBorder(indicatorOff);
		mGUI->Print(top, "%s", mLabel.c_str());
	}
	void OnMouseDown(int button, int x_, int y_)
	{
		if(button == 1 && InRect(x,y,w,h,x_,y_))
		{
			mOn = !mOn;
			if(mCB) 
			{
				if(mOn)
					mCB->OnOn();
				else
					mCB->OnOff();
			}
		}
	}
	void SetOn(bool onOff)
	{
		mOn = onOff;
		if(mCB) 
		{
			if(mOn)
				mCB->OnOn();
			else
				mCB->OnOff();
		}
	}
	TextOption top;
	QuadOptionBorder button;
	QuadOptionBorder indicatorOn;
	QuadOptionBorder indicatorOff;

	int x,y,w,h;
};


class MySliderCallback : public SliderCallback
{
public:
	MySliderCallback()
		:SliderCallback()
	{
	}
	void SetVal(int val)
	{
		
	}
};
class MyListCallback : public ListBoxCallback
{
public:
	MyListCallback()
		:ListBoxCallback()
	{
	}
	void OnSelect(int idx)
	{
		char temp[32];
		sprintf(temp, "%d", idx);
		//MessageBox(NULL, temp, temp, MB_OK);
		
	}
};
class MyButtonCallback : public ButtonCallback
{
public:
	MyButtonCallback()
		:ButtonCallback()
	{
	}
	void OnClick()
	{
		//MessageBox(NULL, "", "", MB_OK);
	}
};
class ExampleEditor;
class MoveUpCallback : public ButtonCallback
{
public:
	MoveUpCallback(ExampleEditor *editor);
	ExampleEditor *mEditor;
	void OnClick();
};
class MoveDnCallback : public ButtonCallback
{
public:
	MoveDnCallback(ExampleEditor *editor);
	ExampleEditor *mEditor;
	void OnClick();
};
class ExchangeCallback : public ButtonCallback
{
public:
	ExchangeCallback(ExampleEditor *editor);
	ExampleEditor *mEditor;
	void OnClick();
};

class MyTotalEffectOnOff : public OnOffButtonCallback
{
public:
	ExampleEditor *mEditor;
	MyTotalEffectOnOff(ExampleEditor *editor);
	void OnOn();
	void OnOff();
};
class MyEffectOnOff : public OnOffButtonCallback
{
public:
	ExampleEditor *mEditor;
	int mWhereis;
	MyEffectOnOff(ExampleEditor *editor, int whereis);
	void OnOn();
	void OnOff();
};



class MyButtonCallback2 : public OnOffButtonCallback
{
public:
	MyButtonCallback2()
		:OnOffButtonCallback()
	{
	}
	void OnOn()
	{
		char temp[123];
		sprintf(temp, "%d", GetRealMinMaxByFreq(GetFreqByRealMinMax(48)));
		MessageBox(NULL, temp, "", MB_OK);
	}
	void OnOff()
	{
		MessageBox(NULL, "Off", "", MB_OK);
	}
};
class MyTLButtonCallback : public TabbedListBoxCallback
{
public:
	MyTLButtonCallback()
		:TabbedListBoxCallback()
	{
	}
	void OnPageSelect(int idx)
	{
		char temp[123];
		sprintf(temp, "%d", idx);
		//MessageBox(NULL, temp, "asd", MB_OK);
	}
	void OnSelect(int idx)
	{
		char temp[123];
		sprintf(temp, "%d", idx);
		//MessageBox(NULL, temp, temp, MB_OK);
	}
};
namespace DistorsionPanelNS
{
	class DistorsionPanel;
};
namespace LinealEQNS
{
	class LinealEQ;
};
namespace CompressorNS
{
	class CompressorPanel;
};
namespace EchoNS
{
	class EchoPanel;
};
namespace PanelNS
{
	class Panel;
};
enum EffNameType
{
	EffNone,
	EffAlienWah,
	EffAnalogPhaser,
	EffArpie,
	EffChorus,
	EffCoilCrafter,
	EffCompBand,
	EffCompressor,
	EffConvolotron,
	EffDistortion,
	EffDualFlange,
	EffEcho,
	EffEchotron,
	EffExciter,
	EffExpander,
	EffFlange,
	EffGate,
	EffHarmonizer,
	EffInfinity,
	EffLinealEQ,
	EffMBDist,
	EffMBVvol,
	EffMusicDelay,
	EffNewDist,
	EffOpticaltrem,
	EffPan,
	EffParametricEQ,
	EffParametricEQ2,
	EffParametricEQ3,
	EffPhaser,
	EffRBEcho,
	EffReverb,
	EffReverbtron,
	EffRing,
	EffRyanWah,
	EffSequence,
	EffShelfBoost,
	EffShifter,
	EffShuffle,
	EffStereoHarm,
	EffStompBox,
	EffSustainer,
	EffSynthfilter,
	EffValve,
	EffVibe,
	EffWahWah,
	NumEffs,
};

class EffectName
{
public:
	EffectName(EffNameType type, string name):type(type), name(name){};
	EffNameType type;
	string name;
};

struct SaveParams
{
	int presetIdx;
	int params[20];

};

struct SaveState{
	EffNameType type[10];
	SaveParams params[10];
	int totalOn;
	int effOn[10];
	char ConFN[1024];
	char EchoFN[1024];
	char ReverbFN[1024];
	ParamAuto mParamAuto[16];
};



bool CompEff(EffectName a, EffectName b);
class ExampleEditor : public VSTGLEditor,
					  public Timer
{
  public:
	  vector<EffectName> mEffectNames;
	  vector<EffectName> mUsingEffectList;
	///	Constructor.
	  void idle();
	  void* getDirectory (){return NULL;}
	ExampleEditor(AudioEffect *effect);
	///	Destructor.
	~ExampleEditor();
	struct Preset_Bank_Struct {
		char Preset_Name[64];
		char Author[64];
		char Classe[36];
		char Type[4];
		char ConvoFiname[128];
		char cInput_Gain[64];
		char cMaster_Volume[64];
		char cBalance[64];
		float Input_Gain;
		float Master_Volume;
		float Balance;
		int Bypass;
		char RevFiname[128];
		char EchoFiname[128];
		int lv[70][20];
		int XUserMIDI[128][20];
		int XMIDIrangeMin[128];
		int XMIDIrangeMax[128];
	} Bank[62];
	/*
        if ((fn = fopen (temp, "rb")) != NULL) {
            New_Bank();
            while (!feof (fn)) {
                fread (&Bank, sizeof (Bank), 1, fn);
                for(j=1; j<=60; j++) strcpy(B_Names[k][j].Preset_Name,Bank[j].Preset_Name);
            }
            fclose (fn);
        }

int
RKR::loadbank (char *filename)
{

    int err_message=1;
    char meslabel[64];
    FILE *fn;


    memset(meslabel,0, sizeof(meslabel));
    sprintf(meslabel, "%s %s",jackcliname,VERSION);


    err_message = CheckOldBank(filename);

    switch(err_message) {
    case 0:
        break;
    case 1:
        Message(1, meslabel, "Can not load this Bank file because is from a old rakarrack version,\n please use 'Convert Old Bank' menu entry in the Bank window.");
        return(0);
        break;
    case 2:
        Message(1, meslabel, "Can not load this Bank file\n");
        return(0);
        break;
    case 3:
        Message(1, meslabel, "Can not load this Bank file because is from a old rakarrack git version,\n please use rakgit2new utility to convert.");
        return(0);
        break;

    }


    if ((fn = fopen (filename, "rb")) != NULL) {
        New_Bank();
        while (!feof (fn)) {
            fread (&Bank, sizeof (Bank), 1, fn);
        }
        fclose (fn);
        if(BigEndian()) fix_endianess();
        convert_IO();
        modified=0;
        new_bank_loaded=1;
        return (1);
    }
    return (0);
};


int
RKR::savebank (char *filename)
{

    FILE *fn;

    if ((fn = fopen (filename, "wb")) != NULL) {
        copy_IO();
        if(BigEndian()) fix_endianess();
        fwrite (&Bank, sizeof (Bank), 1, fn);
        if(BigEndian()) fix_endianess();
        fclose (fn);
        modified=0;
        return(1);
    }

    if(errno==EACCES) Error_Handle(3);
    return (0);
};
void
RKR::New_Bank ()
{

    int i, j, k;

    int presets[48][16] = {
//Reverb
        {80, 64, 63, 24, 0, 0, 0, 85, 5, 83, 1, 64, 0, 0, 0, 0},
//Echo
        {67, 64, 35, 64, 30, 59, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
//Chorus
        {64, 64, 33, 0, 0, 90, 40, 85, 64, 119, 0, 0, 0, 0, 0, 0},
//Flanger
        {64, 64, 39, 0, 0, 60, 23, 3, 62, 0, 0, 0, 0, 0, 0, 0},
//Phaser
        {64, 64, 11, 0, 0, 64, 110, 64, 1, 0, 0, 20, 0, 0, 0, 0},
//Overdrive
        {84, 64, 35, 56, 40, 0, 0, 6703, 21, 0, 0, 0, 0, 0, 0, 0},
//Distorsion
        {0, 64, 0, 87, 14, 6, 0, 3134, 157, 0, 1, 0, 0, 0, 0, 0},
//EQ1
        {64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 0, 0, 0, 0},
//EQ2
        {24, 64, 64, 75, 64, 64, 113, 64, 64, 64, 0, 0, 0, 0, 0, 0},
//Compressor
        {-30, 2, -6, 20, 120, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
//Order
        {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15},
//WahWah
        {64, 64, 138, 0, 0, 64, 20, 90, 0, 60, 0, 0, 0, 0, 0, 0},
//AlienWah1
        {64, 64, 80, 0, 0, 62, 60, 105, 25, 0, 64, 0, 0, 0, 0, 0},
//Cabinet
        {0, 64, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
//Pan
        {64, 64, 26, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0},
//Harmonizer
        {64, 64, 64, 12, 6000, 0, 0, 0, 64, 64, 0, 0, 0, 0, 0, 0},
//MusicDelay
        {64, 0, 2, 7, 0, 59, 0, 127, 4, 59, 106, 75, 75, 0, 0, 0},
//NoiseGate
        {0, 0, 1, 2, 6703, 76, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0},
//NewDist
        {0, 64, 64, 83, 65, 15, 0, 2437, 169, 68, 0, 0, 0, 0, 0, 0},
//APhaser
        {64, 20, 14, 0, 1, 64, 110, 40, 4, 10, 0, 64, 1, 0, 0, 0},
//Valve
        {0, 64, 64, 127, 64, 0, 5841, 61, 1, 0, 69, 1, 80 ,0 ,0 ,0},
//Dual Flange
        {-32, 0, 0, 110, 800, 10, -27, 16000, 1, 0, 24, 64, 1, 10, 0, 0},
//Ring
        {-64, 0, -64, 64, 35, 1, 0, 20, 0, 40, 0, 64, 1, 0, 0 ,0},
//Exciter
        {127, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 20000, 20, 0, 0, 0 },
//MBDist
        {0, 64, 64, 56, 40, 0, 0, 0, 29, 35, 100, 0, 450, 1500, 1, 0},
//Arpie
        {67, 64, 35, 64, 30, 59, 0, 127, 0, 0, 0, 0, 0, 0, 0, 0},
//Expander
        {-50, 20, 50, 50, 3134, 76, 0, 0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0},
//Shuffle 1
        {64, 10, 0, 0, 0, 600, 1200, 2000, 6000,-14, 1, 0, 0 ,0 ,0, 0},
//Synthfilter
        {0, 20, 14, 0, 1, 64, 110, -40, 6, 0, 0, 32, -32, 500, 100, 0},
//MBVvol
        {0, 40, 0, 64, 80, 0, 0, 500, 2500, 5000, 0, 0, 0, 0, 0, 0},
//Convolotron 1
        {67, 64, 1, 100, 0, 64, 30, 20, 0, 0, 0, 0, 0, 0, 0, 0},
//Looper
        {64, 0, 1, 0, 1, 0, 64, 1, 0, 0, 64, 0, 0, 0, 0, 0},
//RyanWah
        {16, 10, 60, 0, 0, 64, 0, 0, 10, 7, -16, 40, -3, 1, 2000, 450},
//Echoverse
        {64, 64, 90, 64, 64, 64, 64, 0, 1, 96, 0, 0, 0, 0, 0, 0},
//CoilCrafter
        {32, 6, 1, 3300, 16, 4400, 42, 20, 0, 0, 0, 0, 0, 0, 0, 0},
//ShelfBoost
        {127, 64, 16000, 1, 24, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
//Vocoder
        {0, 64, 10, 70, 70, 40, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
//Systainer
        {67, 64, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
//Sequence
        {20, 100, 10, 50, 25, 120, 60, 127, 0, 90, 40, 0, 0, 0, 3, 0},
//Shifter
        {0, 64, 64, 200, 200, -20, 2, 0, 0, 0, 0, 0 ,0 ,0 ,0 ,0},
//StompBox
        {48, 32, 0, 32, 65, 0, 0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0},
//Reverbtron
        {64, 0, 1, 1500, 0, 0, 60, 18, 4, 0, 0, 64, 0 ,0 ,0 ,0},
//Echotron
        {64, 45, 34, 4, 0, 76, 3, 41, 0, 96, -13, 64, 1, 1, 1, 1},
//StereoHarm
        {64, 64, 12, 0, 64, 12, 0, 0, 0, 0, 0, 64, 0, 0, 0, 0},
//CompBand
        {0, 16, 16, 16, 16, 0, 0, 0, 0, 1000, 5000, 10000, 48, 0, 0, 0},
//Opticaltrem
        {127, 260, 10, 0, 64, 64, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
//Vibe
        {35, 120, 10, 0, 64, 64, 64, 64, 3, 64, 0, 0, 0, 0, 0, 0},
//Infinity
        {64, 64, 64, 64, 64, 64, 64, 64, 64, 700, 20, 80, 60, 0, 1, 0}








    };




    for (i = 0; i < 62; i++) {
        memset(Bank[i].Preset_Name, 0, sizeof (Bank[i].Preset_Name));
        memset(Bank[i].Author, 0, sizeof (Bank[i].Author));
        strcpy(Bank[i].Author,UserRealName);
        memset(Bank[i].ConvoFiname,0, sizeof(Bank[i].ConvoFiname));
        memset(Bank[i].RevFiname,0,sizeof(Bank[i].RevFiname));
        memset(Bank[i].EchoFiname,0,sizeof(Bank[i].EchoFiname));

        Bank[i].Input_Gain = .5f;
        Bank[i].Master_Volume = .5f;
        Bank[i].Balance = 1.0f;
        Bank[i].Bypass = 0;
        memset(Bank[i].lv , 0 , sizeof(Bank[i].lv));

        for (j = 0; j < NumEffects; j++) {
            for (k = 0; k < 16; k++) {
                Bank[i].lv[j][k] = presets[j][k];
            }
            Bank[i].lv[j][19] =0;

        }

        memset(Bank[i].XUserMIDI, 0, sizeof(Bank[i].XUserMIDI));

    }




};
void
RKR::Bank_to_Preset (int i)
{

    int j, k;


    memset(Preset_Name, 0,sizeof (Preset_Name));
    strcpy (Preset_Name, Bank[i].Preset_Name);
    memset(Author, 0,sizeof (Author));
    strcpy (Author, Bank[i].Author);
    memset(efx_Convol->Filename, 0, sizeof (efx_Convol->Filename));
    strcpy (efx_Convol->Filename,Bank[i].ConvoFiname);
    memset(efx_Reverbtron->Filename, 0, sizeof (efx_Reverbtron->Filename));
    strcpy (efx_Reverbtron->Filename,Bank[i].RevFiname);
    memset(efx_Echotron->Filename, 0, sizeof (efx_Echotron->Filename));
    strcpy (efx_Echotron->Filename,Bank[i].EchoFiname);


    for (j = 0; j <=NumEffects; j++) {
        for (k = 0; k < 20; k++) {
            lv[j][k] = Bank[i].lv[j][k];
        }
    }


    for (k = 0; k < 12; k++)
        efx_order[k] = Bank[i].lv[10][k];
	// 이게 바로 어떤 이펙트가 어디에 있는가를 결정하는거

    Reverb_B = Bank[i].lv[0][19];
    Echo_B = Bank[i].lv[1][19];
    Chorus_B = Bank[i].lv[2][19];
    Flanger_B = Bank[i].lv[3][19];
    Phaser_B = Bank[i].lv[4][19];
    Overdrive_B = Bank[i].lv[5][19];
    Distorsion_B = Bank[i].lv[6][19];
    EQ1_B = Bank[i].lv[7][19];
    EQ2_B = Bank[i].lv[8][19];
    Compressor_B = Bank[i].lv[9][19];
    WhaWha_B = Bank[i].lv[11][19];
    Alienwah_B = Bank[i].lv[12][19];
    Cabinet_B = Bank[i].lv[13][19];
    Pan_B = Bank[i].lv[14][19];
    Harmonizer_B = Bank[i].lv[15][19];
    MusDelay_B = Bank[i].lv[16][19];
    Gate_B = Bank[i].lv[17][19];
    NewDist_B = Bank[i].lv[18][19];
    APhaser_B = Bank[i].lv[19][19];
    Valve_B = Bank[i].lv[20][19];
    DFlange_B = Bank[i].lv[21][19];
    Ring_B = Bank[i].lv[22][19];
    Exciter_B = Bank[i].lv[23][19];
    MBDist_B = Bank[i].lv[24][19];
    Arpie_B = Bank[i].lv[25][19];
    Expander_B = Bank[i].lv[26][19];
    Shuffle_B = Bank[i].lv[27][19];
    Synthfilter_B = Bank[i].lv[28][19];
    MBVvol_B = Bank[i].lv[29][19];
    Convol_B = Bank[i].lv[30][19];
    Looper_B = Bank[i].lv[31][19];
    RyanWah_B = Bank[i].lv[32][19];
    RBEcho_B = Bank[i].lv[33][19];
    CoilCrafter_B = Bank[i].lv[34][19];
    ShelfBoost_B = Bank[i].lv[35][19];
    Vocoder_B = Bank[i].lv[36][19];
    Sustainer_B = Bank[i].lv[37][19];
    Sequence_B = Bank[i].lv[38][19];
    Shifter_B = Bank[i].lv[39][19];
    StompBox_B = Bank[i].lv[40][19];
    Reverbtron_B = Bank[i].lv[41][19];
    Echotron_B = Bank[i].lv[42][19];
    StereoHarm_B = Bank[i].lv[43][19];
    CompBand_B = Bank[i].lv[44][19];
    Opticaltrem_B = Bank[i].lv[45][19];
    Vibe_B = Bank[i].lv[46][19];
    Infinity_B = Bank[i].lv[47][19];

	//_B는 바이패스 즉 온 오프
    Bypass_B = Bypass;


    memcpy(XUserMIDI, Bank[i].XUserMIDI, sizeof(XUserMIDI));



    Actualizar_Audio ();

    if (actuvol == 0) {
        Input_Gain = Bank[i].Input_Gain;
        Master_Volume = Bank[i].Master_Volume;
        Fraction_Bypass = Bank[i].Balance;
    }

    if((Tap_Updated) && (Tap_Bypass) && (Tap_TempoSet>0) && (Tap_TempoSet<601)) Update_tempo();

};


void
RKR::Preset_to_Bank (int i)
{


    int j, k;
    memset(Bank[i].Preset_Name, 0, sizeof (Bank[i].Preset_Name));
    strcpy (Bank[i].Preset_Name, Preset_Name);
    memset(Bank[i].Author, 0, sizeof (Bank[i].Author));
    strcpy (Bank[i].Author, Author);
    memset(Bank[i].ConvoFiname,0, sizeof(Bank[i].ConvoFiname));
    strcpy(Bank[i].ConvoFiname, efx_Convol->Filename);
    memset(Bank[i].RevFiname, 0, sizeof(Bank[i].RevFiname));
    strcpy(Bank[i].RevFiname, efx_Reverbtron->Filename);
    memset(Bank[i].EchoFiname, 0, sizeof(Bank[i].EchoFiname));
    strcpy(Bank[i].EchoFiname, efx_Echotron->Filename);


    Bank[i].Input_Gain = Input_Gain;
    Bank[i].Master_Volume = Master_Volume;
    Bank[i].Balance = Fraction_Bypass;


    for (j = 0; j <= 11; j++)
        lv[0][j] = efx_Rev->getpar (j);
    for (j = 0; j <= 8; j++)
        lv[1][j] = efx_Echo->getpar (j);
    for (j = 0; j <= 12; j++)
        lv[2][j] = efx_Chorus->getpar (j);
    for (j = 0; j <= 12; j++)
        lv[3][j] = efx_Flanger->getpar (j);
    for (j = 0; j <= 11; j++)
        lv[4][j] = efx_Phaser->getpar (j);
    for (j = 0; j <= 12; j++)
        lv[5][j] = efx_Overdrive->getpar (j);
    for (j = 0; j <= 12; j++)
        lv[6][j] = efx_Distorsion->getpar (j);
    for (j = 0; j <= 8; j++)
        lv[9][j] = efx_Compressor->getpar (j + 1);
    for (j = 0; j <= 9; j++)
        lv[11][j] = efx_WhaWha->getpar (j);
    for (j = 0; j <= 10; j++)
        lv[12][j] = efx_Alienwah->getpar (j);
    for (j = 0; j <= 8; j++)
        lv[14][j] = efx_Pan->getpar (j);
    for (j = 0; j <= 10; j++)
        lv[15][j] = efx_Har->getpar (j);
    for (j = 0; j <= 12; j++)
        lv[16][j] = efx_MusDelay->getpar (j);
    for (j = 0; j <= 6; j++)
        lv[17][j] = efx_Gate->getpar (j + 1);
    for (j = 0; j <= 11; j++)
        lv[18][j] = efx_NewDist->getpar (j);
    for (j = 0; j <= 12; j++)
        lv[19][j] = efx_APhaser->getpar(j);
    for (j = 0; j <= 12; j++)
        lv[20][j] = efx_Valve->getpar(j);
    for (j = 0; j <= 14; j++)
        lv[21][j] = efx_DFlange->getpar(j);
    for (j = 0; j <= 12; j++)
        lv[22][j] = efx_Ring->getpar(j);
    for (j = 0; j <= 12; j++)
        lv[23][j] = efx_Exciter->getpar(j);
    for (j = 0; j <= 14; j++)
        lv[24][j] = efx_MBDist->getpar(j);
    for (j = 0; j <= 10; j++)
        lv[25][j] = efx_Arpie->getpar(j);
    for (j = 0; j <= 6; j++)
        lv[26][j] = efx_Expander->getpar(j+1);
    for (j = 0; j <= 10; j++)
        lv[27][j] = efx_Shuffle->getpar(j);
    for (j = 0; j <= 15; j++)
        lv[28][j] = efx_Synthfilter->getpar(j);
    for (j = 0; j <= 10; j++)
        lv[29][j] = efx_MBVvol->getpar(j);
    for (j = 0; j <= 10; j++)
        lv[30][j] = efx_Convol->getpar(j);
    for (j = 0; j <= 13; j++)
        lv[31][j] = efx_Looper->getpar(j);
    for (j = 0; j <= 18; j++)
        lv[32][j] = efx_RyanWah->getpar(j);
    for (j = 0; j <= 9; j++)
        lv[33][j] = efx_RBEcho->getpar(j);
    for (j = 0; j <= 8; j++)
        lv[34][j] = efx_CoilCrafter->getpar(j);
    for (j = 0; j <= 4; j++)
        lv[35][j] = efx_ShelfBoost->getpar(j);
    for (j = 0; j <= 6; j++)
        lv[36][j] = efx_Vocoder->getpar(j);
    for (j = 0; j <= 1; j++)
        lv[37][j] = efx_Sustainer->getpar(j);
    for (j = 0; j <= 14; j++)
        lv[38][j] = efx_Sequence->getpar(j);
    for (j = 0; j <= 9; j++)
        lv[39][j] = efx_Shifter->getpar(j);
    for (j = 0; j <= 5; j++)
        lv[40][j] = efx_StompBox->getpar(j);
    for (j = 0; j <= 15; j++)
        lv[41][j] = efx_Reverbtron->getpar(j);
    for (j = 0; j <= 15; j++)
        lv[42][j] = efx_Echotron->getpar(j);
    for (j = 0; j <= 11; j++)
        lv[43][j] = efx_StereoHarm->getpar(j);
    for (j = 0; j <= 12; j++)
        lv[44][j] = efx_CompBand->getpar(j);
    for (j = 0; j <= 5; j++)
        lv[45][j] = efx_Opticaltrem->getpar(j);
    for (j = 0; j <= 10; j++)
        lv[46][j] = efx_Vibe->getpar(j);
    for (j = 0; j <= 17; j++)
        lv[47][j] = efx_Infinity->getpar(j);


    for (j = 0; j <= 12; j++)
        lv[10][j] = efx_order[j];

    for (j = 0; j < 10; j++)
        lv[7][j] = efx_EQ1->getpar (j * 5 + 12);
    lv[7][10] = efx_EQ1->getpar (0);
    lv[7][11] = efx_EQ1->getpar (13);

    for (j = 0; j < 3; j++) {
        lv[8][0 + j * 3] = efx_EQ2->getpar (j * 5 + 11);
        lv[8][1 + j * 3] = efx_EQ2->getpar (j * 5 + 12);
        lv[8][2 + j * 3] = efx_EQ2->getpar (j * 5 + 13);
    }
    lv[8][9] = efx_EQ2->getpar (0);

    lv[13][0] = Cabinet_Preset;
    lv[13][1] = efx_Cabinet->getpar (0);



    for (j = 0; j <= NumEffects; j++) {
        for (k = 0; k < 19; k++) {
            Bank[i].lv[j][k] = lv[j][k];
        }
    }

    Bank[i].lv[11][10] = efx_WhaWha->Ppreset;


    Bank[i].lv[0][19] = Reverb_Bypass;
    Bank[i].lv[1][19] = Echo_Bypass;
    Bank[i].lv[2][19] = Chorus_Bypass;
    Bank[i].lv[3][19] = Flanger_Bypass;
    Bank[i].lv[4][19] = Phaser_Bypass;
    Bank[i].lv[5][19] = Overdrive_Bypass;
    Bank[i].lv[6][19] = Distorsion_Bypass;
    Bank[i].lv[7][19] = EQ1_Bypass;
    Bank[i].lv[8][19] = EQ2_Bypass;
    Bank[i].lv[9][19] = Compressor_Bypass;
    Bank[i].lv[11][19] = WhaWha_Bypass;
    Bank[i].lv[12][19] = Alienwah_Bypass;
    Bank[i].lv[13][19] = Cabinet_Bypass;
    Bank[i].lv[14][19] = Pan_Bypass;
    Bank[i].lv[15][19] = Harmonizer_Bypass;
    Bank[i].lv[16][19] = MusDelay_Bypass;
    Bank[i].lv[17][19] = Gate_Bypass;
    Bank[i].lv[18][19] = NewDist_Bypass;
    Bank[i].lv[19][19] = APhaser_Bypass;
    Bank[i].lv[20][19] = Valve_Bypass;
    Bank[i].lv[21][19] = DFlange_Bypass;
    Bank[i].lv[22][19] = Ring_Bypass;
    Bank[i].lv[23][19] = Exciter_Bypass;
    Bank[i].lv[24][19] = MBDist_Bypass;
    Bank[i].lv[25][19] = Arpie_Bypass;
    Bank[i].lv[26][19] = Expander_Bypass;
    Bank[i].lv[27][19] = Shuffle_Bypass;
    Bank[i].lv[28][19] = Synthfilter_Bypass;
    Bank[i].lv[29][19] = MBVvol_Bypass;
    Bank[i].lv[30][19] = Convol_Bypass;
    Bank[i].lv[31][19] = Looper_Bypass;
    Bank[i].lv[32][19] = RyanWah_Bypass;
    Bank[i].lv[33][19] = RBEcho_Bypass;
    Bank[i].lv[34][19] = CoilCrafter_Bypass;
    Bank[i].lv[35][19] = ShelfBoost_Bypass;
    Bank[i].lv[36][19] = Vocoder_Bypass;
    Bank[i].lv[37][19] = Sustainer_Bypass;
    Bank[i].lv[38][19] = Sequence_Bypass;
    Bank[i].lv[39][19] = Shifter_Bypass;
    Bank[i].lv[40][19] = StompBox_Bypass;
    Bank[i].lv[41][19] = Reverbtron_Bypass;
    Bank[i].lv[42][19] = Echotron_Bypass;
    Bank[i].lv[43][19] = StereoHarm_Bypass;
    Bank[i].lv[44][19] = CompBand_Bypass;
    Bank[i].lv[45][19] = Opticaltrem_Bypass;
    Bank[i].lv[46][19] = Vibe_Bypass;
    Bank[i].lv[47][19] = Infinity_Bypass;


    memcpy(Bank[i].XUserMIDI,XUserMIDI,sizeof(XUserMIDI));


};

플러그인윈도우의 가로 길이를 늘려서 거기에 뱅크 로드(임포트)/세이브(익스포트), 선택/새로저장 기능을 넣는다.
        switch(efx_order[j]) {
        case 0: //EQ1
        case 1:// Compressor
        case 2://Distortion
        case 3://Overdrive
        case 4://Echo
        case 5://Chorus
        case 6://Phaser
        case 7://Flanger
        case 8://Reverb
        case 9://EQ2
        case 10://WhaWha
        case 11://Alienwah
        case 12://Cabinet
        case 13://Pan
        case 14://Harmonizer
        case 15://MusDelay
        case 16://Gate
        case 17://NewDist
        case 18://APhaser
        case 19://Valve
        case 20://DFlange
        case 21://Ring
        case 22://Exciter
        case 23://MBDist
        case 24://Arpie
        case 25://Expander
        case 26://Shuffle
        case 27://Synthfilter
        case 28://MBVvol
        case 29://Convolotron
        case 30://Looper
        case 31://RyanWah
        case 32://RBEcho
        case 33://CoilCrafter
        case 34://ShelfBoost
        case 35://Vocoder
        case 36://Sustainer
        case 37://Sequence
        case 38://Shifter
        case 39://StompBox
        case 40://Reverbtron
        case 41://Echotron
        case 42://StereoHarm
        case 43://CompBand
        case 44://OpticalTrem
        case 45://Vibe
        case 46://Infinity

		*/
	MySliderCallback myCB;
	MyButtonCallback myButtonCB;
	MyButtonCallback2 myButton2CB;
	MyListCallback myListCB;
	MyTLButtonCallback myTLCB;
	MoveUpCallback *moveUpCB;
	MoveDnCallback *moveDnCB;
	ExchangeCallback *exchangeCB;
	vector<EffNameType> mBuiltPanels;
	vector<PanelNS::Panel*> mPanels;
	vector<bool> mEffectOn;
	vector<MyEffectOnOff*> mCBOnOffs;
	MyTotalEffectOnOff *cbOnOff;
	bool mTotalEffectOn;
	void CreateEffectPanel(EffNameType type, int whereis, bool loadPrev = false, int prevIdx = -1);
	void DeleteEffectPanel(int whereis);
	int GetEffectPreset(int whereis);
	bool mDelMeCompressor;
	bool mDelMeEQ;
	bool mDelMeDist;
	bool mDelMeEcho;
	
	DistorsionPanelNS::DistorsionPanel *mDistPanel;
	LinealEQNS::LinealEQ *mEQ1Panel;
	EchoNS::EchoPanel *mEchoPanel;
	
	CompressorNS::CompressorPanel *mCompressorPanel;
	///	Called when the Gui's window is opened.
	void guiOpen();
	///	Called when the Gui's window is closed.
	void guiClose();

	///	Draws a spinning pyramid.
	void draw();

	///	Called repeatedly, to update the graphics.
	void onMouseDown(int button, int x, int y)// button: 1 lmb 2 rmb 3 mmb
	{
			mGUI->onMouseDown(button, x,y);
	}
	void onMouseUp(int button, int x, int y)
	{
			mGUI->onMouseUp(button, x,y);
	}
	void onMouseMove(int x, int y)
	{
			mGUI->onMouseMove(x,y);
	}
	void CreateEchotron(int whereis, bool loadPrev, int prevIdx);
	void CreateConvolotron(int whereis, bool loadPrev, int prevIdx);
	void CreateRyanWah(int whereis, bool loadPrev, int prevIdx);
	void CreateReverbtron(int whereis, bool loadPrev, int prevIdx);
	void CreateArpie(int whereis, bool loadPrev, int prevIdx);
	void CreateExpander(int whereis, bool loadPrev, int prevIdx);
	void CreateShuffle(int whereis, bool loadPrev, int prevIdx);
	void CreateSynthfilter(int whereis, bool loadPrev, int prevIdx);
	void CreateMVVvol(int whereis, bool loadPrev, int prevIdx);
	void CreateRBEcho(int whereis, bool loadPrev, int prevIdx);
	void CreateCoilCrafter(int whereis, bool loadPrev, int prevIdx); 
	void CreateShelfBoost(int whereis, bool loadPrev, int prevIdx);
	void CreateSustainer(int whereis, bool loadPrev, int prevIdx);
	void CreateSequence(int whereis, bool loadPrev, int prevIdx);
	void CreateShifter(int whereis, bool loadPrev, int prevIdx);
	void CreateStompBox(int whereis, bool loadPrev, int prevIdx);
	void CreateStereoHarm(int whereis, bool loadPrev, int prevIdx);
	void CreateCompBand(int whereis, bool loadPrev, int prevIdx);
	void CreateOpticalTrem(int whereis, bool loadPrev, int prevIdx);
	void CreateInfinity(int whereis, bool loadPrev, int prevIdx);
	void CreateVibe(int whereis, bool loadPrev, int prevIdx);
	
	

	
	
	
	
	

	void timerCallback();
	GLGUI *mGUI;
	int moveUpButton;
	int moveDnButton;
	int exchangeButton;
	int unusedEffectsList;
	int beingUsedEffectsList;
	int mOnOffButtons[10];
	int mTotalOnOffButton;
  private:
	int mSlider;
	
	///	Variable used to rotate the pyramid.
	float thing;
};

