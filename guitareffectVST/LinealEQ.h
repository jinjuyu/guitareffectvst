#pragma once

#include "../VSTGL/ExampleEditor.h"
#include "../VSTGL/VstPlugin.h"
#include <vector>

#include <string>
using namespace std;

namespace LinealEQNS
{
class LinealEQ;
class GainCallback : public SliderCallback
{
public:
	LinealEQ *mPanel;
	GainCallback(LinealEQ *a);
	void SetVal(int val);
};
class QCallback : public SliderCallback
{
public:
	LinealEQ *mPanel;
	QCallback(LinealEQ *a);
	void SetVal(int val);
};

class F31Callback : public SliderCallback
{
public:
	LinealEQ *mPanel;
	F31Callback(LinealEQ *a);
	void SetVal(int val);
};


class F63Callback : public SliderCallback
{
public:
	LinealEQ *mPanel;
	F63Callback(LinealEQ *a);
	void SetVal(int val);
};

class F125Callback : public SliderCallback
{
public:
	LinealEQ *mPanel;
	F125Callback(LinealEQ *a);
	void SetVal(int val);
};

class F250Callback : public SliderCallback
{
public:
	LinealEQ *mPanel;
	F250Callback(LinealEQ *a);
	void SetVal(int val);
};

class F500Callback : public SliderCallback
{
public:
	LinealEQ *mPanel;
	F500Callback(LinealEQ *a);
	void SetVal(int val);
};

class F1KCallback : public SliderCallback
{
public:
	LinealEQ *mPanel;
	F1KCallback(LinealEQ *a);
	void SetVal(int val);
};

class F2KCallback : public SliderCallback
{
public:
	LinealEQ *mPanel;
	F2KCallback(LinealEQ *a);
	void SetVal(int val);
};

class F4KCallback : public SliderCallback
{
public:
	LinealEQ *mPanel;
	F4KCallback(LinealEQ *a);
	void SetVal(int val);
};

class F8KCallback : public SliderCallback
{
public:
	LinealEQ *mPanel;
	F8KCallback(LinealEQ *a);
	void SetVal(int val);
};

class F16KCallback : public SliderCallback
{
public:
	LinealEQ *mPanel;
	F16KCallback(LinealEQ *a);
	void SetVal(int val);
};


class LinealEQ
{
public:
	int *real;
	int *print;
	VstPlugin *mPlug;
	GLGUI *mGUI;
	vector<int> mButtons;
	int mGain;
	int mQ;
	int m31;
	int m63;
	int m125;
	int m250;
	int m500;
	int m1K;
	int m2K;
	int m4K;
	int m8K;
	int m16K;
	GainCallback *cbGain;
	QCallback *cbQ;
	F31Callback *cb31;
	F63Callback *cb63;
	F125Callback *cb125;
	F250Callback *cb250;
	F500Callback *cb500;
	F1KCallback *cb1K;
	F2KCallback *cb2K;
	F4KCallback *cb4K;
	F8KCallback *cb8K;
	F16KCallback *cb16K;

	LinealEQ(GLGUI *gui, VstPlugin *plug, int whereis);
	~LinealEQ()
	{
		for(vector<int>::iterator it = mButtons.begin(); it != mButtons.end(); ++it)
		{
			mGUI->DeleteGUIElement(*it);
		}
		// delete callbacks here
		delete cbGain;
		delete cbQ;
		delete cb31;
		delete cb63;
		delete cb125;
		delete cb250;
		delete cb500;
		delete cb1K;
		delete cb2K;
		delete cb4K;
		delete cb8K;
		delete cb16K;
	}
	int PrintToReal(int val)
	{
		int printMin = print[0];
		int printMax = print[1];
		int realMin = real[0];
		int realMax = real[1];
		int printLength = printMax-printMin;
		int realLength = realMax-realMin;
		
		float printVal = float(val - printMin)/float(printLength);
		return realMin + (int)(printVal*(float)realLength+0.5f);
	}
	int RealToPrint(int val)
	{
		int printMin = print[0];
		int printMax = print[1];
		int realMin = real[0];
		int realMax = real[1];
		int printLength = printMax-printMin;
		int realLength = realMax-realMin;
		
		float realVal = float(val - realMin)/float(realLength);
		return printMin + (int)(realVal*(float)printLength+0.5f);
	}
	float RealToVst(int idx, int val)
	{
		int realMin = real[idx*2];
		int realMax = real[idx*2+1];
		int realLength = realMax-realMin;
		float realVal = float(val - realMin)/float(realLength);
		return realVal;
	}
	int VstToReal(int idx, float val)
	{
		int realMin = real[idx*2];
		int realMax = real[idx*2+1];
		int realLength = realMax-realMin;
		return realMin + (int)(val*realLength+0.5f);
	}
	void DrawText();
	int mWhereis;
};

}