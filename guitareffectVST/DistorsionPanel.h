#pragma once
#include "../VSTGL/ExampleEditor.h"
#include "../VSTGL/VstPlugin.h"

namespace DistorsionPanelNS
{


class DistorsionPanel;
class DistorsionTypeCallback : public ButtonCallback
{
public:
	DistorsionPanel *mPanel;
	DistorsionTypeCallback(DistorsionPanel *a);
	void OnClick();
};
class PresetCallback : public ButtonCallback
{
public:
	DistorsionPanel *mPanel;
	PresetCallback(DistorsionPanel *a);
	void OnClick();
};
class DistorsionNegCallback : public OnOffButtonCallback
{
public:
	DistorsionPanel *mPanel;
	DistorsionNegCallback(DistorsionPanel *a);
	void OnOn();
	void OnOff();
};
class DistorsionPrefilterCallback : public OnOffButtonCallback
{
public:
	DistorsionPanel *mPanel;
	DistorsionPrefilterCallback(DistorsionPanel *a);
	void OnOn();
	void OnOff();
};

class LPFCallBack : public SliderCallback
{
public:
	DistorsionPanel *mPanel;
	LPFCallBack(DistorsionPanel *a);
	void SetVal(int val);
};
class WetDryCallback : public SliderCallback
{
public:
	DistorsionPanel *mPanel;
	WetDryCallback(DistorsionPanel *a);
	void SetVal(int val);
};
class LRCRCallback : public SliderCallback
{
public:
	DistorsionPanel *mPanel;
	LRCRCallback(DistorsionPanel *a);
	void SetVal(int val);
};
class DriveCallback : public SliderCallback
{
public:
	DistorsionPanel *mPanel;
	DriveCallback(DistorsionPanel *a);
	void SetVal(int val);
};
class LevelCallback : public SliderCallback
{
public:
	DistorsionPanel *mPanel;
	LevelCallback(DistorsionPanel *a);
	void SetVal(int val);
};
class PanCallback : public SliderCallback
{
public:
	DistorsionPanel *mPanel;
	PanCallback(DistorsionPanel *a);
	void SetVal(int val);
};
class TypeCallback : public TabbedListBoxCallback
{
public:
	DistorsionPanel *mPanel;
	TypeCallback(DistorsionPanel *a);
	void OnSelect(int idx);
	void OnPageSelect(int idx);
};
class PresetListCallback : public TabbedListBoxCallback
{
public:
	DistorsionPanel *mPanel;
	PresetListCallback(DistorsionPanel *a);
	void OnSelect(int idx);
	void OnPageSelect(int idx);
};
class LPFCallback : public SliderCallback
{
public:
	DistorsionPanel *mPanel;
	LPFCallback(DistorsionPanel *a);
	void SetVal(int val);
};
class HPFCallback : public SliderCallback
{
public:
	DistorsionPanel *mPanel;
	HPFCallback(DistorsionPanel *a);
	void SetVal(int val);
};
class SubOctvCallback : public SliderCallback
{
public:
	DistorsionPanel *mPanel;
	SubOctvCallback(DistorsionPanel *a);
	void SetVal(int val);
};
extern int DistortionReal[];
extern int DistortionPrint[];
class DistorsionPanel
{
public:
	int *real;
	int *print;
	int mTypeButton;
	int mPresetButton;
	vector<string> mTypeStrs;
	WetDryCallback *cbWetDry;
	LRCRCallback *cbLRCR;
	DriveCallback *cbDrive;
	LevelCallback *cbLevel;
	PanCallback *cbPan;
	HPFCallback *cbHPF;
	LPFCallback *cbLPF;
	TypeCallback *cbType;
	SubOctvCallback *cbSubOctv;
	DistorsionTypeCallback *myCB1;
	DistorsionNegCallback *myCB2;
	DistorsionPrefilterCallback *cbPrefilter;
	PresetCallback *cbPresetSelect;
	PresetListCallback *cbPresetSelected;
	VstPlugin *mPlug;
	int mVolume;
	int mPanning;
	int mLRCr;
	int mDrive;
	int mLevel;
	int mNeg;
	int mLPF;
	int mHPF;
	int mPreFilter;
	int mSubOctv;

	~DistorsionPanel()
	{
		for(vector<int>::iterator it = mButtons.begin(); it != mButtons.end(); ++it)
		{
			mGUI->DeleteGUIElement(*it);
		}
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

	}
	DistorsionPanel(GLGUI *gui, VstPlugin *plug, int whereis);
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
	bool mBypass;
	vector<int> mButtons;


	int mWhereis;
	bool mHidden;
};


};