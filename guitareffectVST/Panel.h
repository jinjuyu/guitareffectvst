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
	Selection
};
struct Data
{
	int parIdx;
	int valRealMin;
	int valRealMax;
	int valPrintMin;
	int valPrintMax;
	bool isFreq;
	string text;
	vector<string> mTypeStrs;
	DataType type;
	int cbIdx;
	int cbListIdx;
};
class Panel
{
public:
	vector<int> mButtons;
	vector<PanelSliderCallback*> mCBSliders;
	vector<PanelButtonCallback*> mCBButtons;
	vector<PanelOnOffCallback*> mCBOnOffs;
	vector<PanelListCallback*> mCBLists;
	vector<Data> mData;
	Panel(GLGUI *gui, VstPlugin *plug, Effect *effect, int whereis, int *presets, int sizePreset, int numPresets);
	~Panel();
	Effect *mEffect;
	vector<vector<string>> mTypeStrs;
	vector<vector<int>> mPresets;
	void SetPreset(int preset);
	GLGUI *mGUI;
	int mWhereis;
	VstPlugin *mPlug;
	void AddParamData(Data &data);
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
	void DrawText();
};


};