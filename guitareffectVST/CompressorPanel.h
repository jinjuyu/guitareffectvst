#pragma once
#include "../VSTGL/ExampleEditor.h"
#include "../VSTGL/VstPlugin.h"


namespace CompressorNS
{
class CompressorPanel;
class PresetCallback : public ButtonCallback
{
public:
	CompressorPanel *mPanel;
	PresetCallback(CompressorPanel *a);
	void OnClick();
};
class PresetListCallback : public TabbedListBoxCallback
{
public:
	CompressorPanel *mPanel;
	PresetListCallback(CompressorPanel *a);
	void OnSelect(int idx);
	void OnPageSelect(int idx);
};
class ATimeCallback : public SliderCallback
{
public:
	CompressorPanel *mPanel;
	ATimeCallback(CompressorPanel *a);
	void SetVal(int val);
};

class RTimeCallback : public SliderCallback
{
public:
	CompressorPanel *mPanel;
	RTimeCallback(CompressorPanel *a);
	void SetVal(int val);
};

class RatioCallback : public SliderCallback
{
public:
	CompressorPanel *mPanel;
	RatioCallback(CompressorPanel *a);
	void SetVal(int val);
};

class KneeCallback : public SliderCallback
{
public:
	CompressorPanel *mPanel;
	KneeCallback(CompressorPanel *a);
	void SetVal(int val);
};

class ThresholdCallback : public SliderCallback
{
public:
	CompressorPanel *mPanel;
	ThresholdCallback(CompressorPanel *a);
	void SetVal(int val);
};

class OutputCallback : public SliderCallback
{
public:
	CompressorPanel *mPanel;
	OutputCallback(CompressorPanel *a);
	void SetVal(int val);
};

class PeakCallback : public OnOffButtonCallback
{
public:
	CompressorPanel *mPanel;
	PeakCallback(CompressorPanel *a);
	void OnOn();
	void OnOff();
};

class AutoCallback : public OnOffButtonCallback
{
public:
	CompressorPanel *mPanel;
	AutoCallback(CompressorPanel *a);
	void OnOn();
	void OnOff();
};

class StereoCallback : public OnOffButtonCallback
{
public:
	CompressorPanel *mPanel;
	StereoCallback(CompressorPanel *a);
	void OnOn();
	void OnOff();
};




class CompressorPanel
{
public:
	~CompressorPanel()
	{
		for(vector<int>::iterator it = mButtons.begin(); it != mButtons.end(); ++it)
		{
			mGUI->DeleteGUIElement(*it);
		}
		// delete callbacks here
		delete cbPresetSelect;
		delete cbPresetSelected;
		delete cbATime;
		delete cbRTime;
		delete cbRatio;
		delete cbKnee;
		delete cbThreshold;
		delete cbOutput;
		delete cbPeak;
		delete cbAuto;
		delete cbStereo;

	}
	int *real;
	int mWhereis;
	CompressorPanel(GLGUI *gui, VstPlugin *plug, int whereis);
	void DrawText();
	void SetPreset(int preset);
	vector<string> mPresetStrs;
	int *mPresets;
	VstPlugin *mPlug;
	GLGUI *mGUI;
	vector<int> mButtons;

	PresetCallback *cbPresetSelect;
	PresetListCallback *cbPresetSelected;
	ATimeCallback *cbATime;
	RTimeCallback *cbRTime;
	RatioCallback *cbRatio;
	KneeCallback *cbKnee;
	ThresholdCallback *cbThreshold;
	OutputCallback *cbOutput;
	PeakCallback *cbPeak;
	AutoCallback *cbAuto;
	StereoCallback *cbStereo;
	int mPresetButton;
	int mATime;
	int mRTime;
	int mRatio;
	int mKnee;
	int mThreshold;
	int mOutput;
	int mAuto;
	int mPeak;
	int mStereo;
};


};