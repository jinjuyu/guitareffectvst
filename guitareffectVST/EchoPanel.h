#pragma once
#include "../VSTGL/ExampleEditor.h"
#include "../VSTGL/VstPlugin.h"

namespace EchoNS
{

class EchoPanel;
class PresetCallback : public ButtonCallback
{
public:
	EchoPanel *mPanel;
	PresetCallback(EchoPanel *a);
	void OnClick();
};
class PresetListCallback : public TabbedListBoxCallback
{
public:
	EchoPanel *mPanel;
	PresetListCallback(EchoPanel *a);
	void OnSelect(int idx);
	void OnPageSelect(int idx);
};
class WetDryCallback : public SliderCallback
{
public:
	EchoPanel *mPanel;
	WetDryCallback(EchoPanel *a);
	void SetVal(int val);
};
class ReverseCallback : public SliderCallback
{
public:
	EchoPanel *mPanel;
	ReverseCallback(EchoPanel *a);
	void SetVal(int val);
};
class PanCallback : public SliderCallback
{
public:
	EchoPanel *mPanel;
	PanCallback(EchoPanel *a);
	void SetVal(int val);
};
class DelayCallback : public SliderCallback
{
public:
	EchoPanel *mPanel;
	DelayCallback(EchoPanel *a);
	void SetVal(int val);
};
class LRdlCallback : public SliderCallback
{
public:
	EchoPanel *mPanel;
	LRdlCallback(EchoPanel *a);
	void SetVal(int val);
};
class LRCrCallback : public SliderCallback
{
public:
	EchoPanel *mPanel;
	LRCrCallback(EchoPanel *a);
	void SetVal(int val);
};
class FbCallback : public SliderCallback
{
public:
	EchoPanel *mPanel;
	FbCallback(EchoPanel *a);
	void SetVal(int val);
};
class DampCallback : public SliderCallback
{
public:
	EchoPanel *mPanel;
	DampCallback(EchoPanel *a);
	void SetVal(int val);
};
class EchoPanel
{
public:
	~EchoPanel()
	{
		for(vector<int>::iterator it = mButtons.begin(); it != mButtons.end(); ++it)
		{
			mGUI->DeleteGUIElement(*it);
		}
		/*
		delete cbWetDry;
		delete myCB1;
		delete myCB2;
		delete cbLRCR;
		delete cbDrive;
		delete cbLevel;
		delete cbPan;
		delete cbHPF;
		delete cbLPF;
		delete cbSubOctv;
		delete cbPrefilter;
		delete cbPresetSelect;
		delete cbPresetSelected;
		delete cbType;
		*/
	}
	EchoPanel(GLGUI *gui, VstPlugin *plug, int whereis);
	int *real;
	int *print;
	void SetPreset(int preset);
	vector<string> mPresetStrs;
	int *mPresets;
	int PrintToReal(int idx, int val)
	{
		int printMin = print[idx*2];
		int printMax = print[idx*2+1];
		int realMin = real[idx*2];
		int realMax = real[idx*2+1];
		int printLength = printMax-printMin;
		int realLength = realMax-realMin;
		
		float printVal = float(val - printMin)/float(printLength);
		return realMin + (int)(printVal*(float)realLength+0.5f);
	}
	int RealToPrint(int idx, int val)
	{
		int printMin = print[idx*2];
		int printMax = print[idx*2+1];
		int realMin = real[idx*2];
		int realMax = real[idx*2+1];
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
	GLGUI *mGUI;
	vector<int> mButtons;
	int mWhereis;
	VstPlugin *mPlug;

	PresetCallback *cbPresetSelect;
	PresetListCallback *cbPresetSelected;
	WetDryCallback *cbWetDry;
	ReverseCallback *cbReverse;
	PanCallback *cbPan;
	DelayCallback *cbDelay;
	LRdlCallback *cbLRdl;
	LRCrCallback *cbLRCr;
	FbCallback *cbFb;
	DampCallback *cbDamp;
	int mPresetButton;
	int mVolume;
	int mReverse;
	int mPan;
	int mDelay;
	int mLRdl;
	int mLRCr;
	int mFb;
	int mDamp;
};

};