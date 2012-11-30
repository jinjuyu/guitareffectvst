#pragma once
#include "global.h"
#include "../VSTGL/ExampleEditor.h"
#include "../VSTGL/VstPlugin.h"
namespace PanelNS
{
class Panel;
class PanelSliderCallback : public SliderCallback
{
public:
	Panel *mPanel;
	int mDataIdx;
	PanelSliderCallback(Panel *a, int dataIdx);
	void SetVal(int val);
};
class PanelListCallback : public TabbedListBoxCallback
{
public:
	Panel *mPanel;
	int mDataIdx;
	PanelListCallback(Panel *a, int dataIdx);
	void OnSelect(int idx);
	void OnPageSelect(int idx);
};
class PanelOnOffCallback : public OnOffButtonCallback
{
public:
	int mDataIdx;
	Panel *mPanel;
	PanelOnOffCallback(Panel *a, int dataIdx);
	void OnOn();
	void OnOff();
};
class PanelButtonCallback : public ButtonCallback
{
public:
	int mDataIdx;
	Panel *mPanel;
	PanelListCallback *mCBList;
	PanelButtonCallback(Panel *a, int dataIdx, PanelListCallback *cbList); // dataIdx만 있으면 parIdx등을 다 얻어올 수 있다.
	void OnClick();
};
enum DataType
{
	Slider,
	OnOff,
	Selection,
	Browser,
};
class Data
{
public:
	Data(int idx, int realMin, int realMax, int pMin, int pMax, string txt, DataType type, bool isFreq = false, bool useSameY = false, vector<string> typeStrs = vector<string>(), int preIdx = -1)
		:parIdx(idx), valRealMin(realMin), valRealMax(realMax), valPrintMin(pMin), valPrintMax(pMax), isFreq(isFreq), text(txt), mTypeStrs(typeStrs), type(type), useSameYAsPrev(useSameY), preIdx(preIdx)
	{
		cbIdx = -1;
		cbListIdx = -1;
		typeStrsIdx = -1;
		handle = -1;
	}
	//input
	int parIdx;
	int valRealMin;
	int valRealMax;
	int valPrintMin;
	int valPrintMax;
	bool isFreq;
	string text;
	vector<string> mTypeStrs;
	DataType type;
	bool useSameYAsPrev;
	
	int preIdx; // preset Idx used in parametric eq and others

	//used internally
	int cbIdx;
	int cbListIdx;
	int typeStrsIdx;
	int handle;
};
class PresetCallback : public ButtonCallback
{
public:
	Panel *mPanel;
	PresetCallback(Panel *a);
	void OnClick();
};
class PresetListCallback : public TabbedListBoxCallback
{
public:
	Panel *mPanel;
	PresetListCallback(Panel *a);
	void OnSelect(int idx);
	void OnPageSelect(int idx);
};
class Panel
{
public:
	PresetCallback *cbPresetSelect;
	PresetListCallback *cbPresetSelected;
	vector<int> mButtons;
	int mPresetButton;
	vector<PanelSliderCallback*> mCBSliders;
	vector<PanelButtonCallback*> mCBButtons;
	vector<PanelOnOffCallback*> mCBOnOffs;
	vector<PanelListCallback*> mCBLists;
	vector<Data> mData;
	int mSizePreset;
	Panel(GLGUI *gui, VstPlugin *plug, Effect *effect, string effName, int whereis, int *presets, int sizePreset, int numPresets, vector<string> presetTexts, bool usePresetIdx=false, bool doICallSetPreset=false);
	~Panel();
	bool mUsePresetIdx;
	Effect *mEffect;
	vector<vector<string>> mTypeStrs;
	vector<string> mPresetStrs;
	vector<vector<int>> mPresets;
	void SetPreset(int preset);
	GLGUI *mGUI;
	int mWhereis;
	VstPlugin *mPlug;
	string mEffName;
	int mY;
	bool mDoICallSetPreset;
	void AddParamData(Data &data, bool unused=false);
	int PrintToReal(int idx, int val) // idx 는 dataIdx
	{
		int printMin = mData[idx].valPrintMin;
		int printMax = mData[idx].valPrintMax;
		int realMin = mData[idx].valRealMin;
		int realMax = mData[idx].valRealMax;
		int printLength = printMax-printMin;
		int realLength = realMax-realMin;
		
		float printVal = float(val - printMin)/float(printLength);
		return realMin + (int)(printVal*(float)realLength+0.5f);
	}
	int RealToPrint(int idx, int val)
	{
		int printMin = mData[idx].valPrintMin;
		int printMax = mData[idx].valPrintMax;
		int realMin = mData[idx].valRealMin;
		int realMax = mData[idx].valRealMax;
		int printLength = printMax-printMin;
		int realLength = realMax-realMin;
		
		float realVal = float(val - realMin)/float(realLength);
		return printMin + (int)(realVal*(float)printLength+0.5f);
	}
	float RealToVst(int idx, int val)
	{
		int realMin = mData[idx].valRealMin;
		int realMax = mData[idx].valRealMax;
		int realLength = realMax-realMin;
		float realVal = float(val - realMin)/float(realLength);
		return realVal;
	}
	int VstToReal(int idx, float val)
	{
		int realMin = mData[idx].valRealMin;
		int realMax = mData[idx].valRealMax;
		int realLength = realMax-realMin;
		return realMin + (int)(val*realLength+0.5f);
	}
	void LoadPreset(int presetIdx);
	void DrawText();
	int mPrevPreset;
};


};