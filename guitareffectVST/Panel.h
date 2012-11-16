#pragma once
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
	PanelButtonCallback(Panel *a, int dataIdx);
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
	int realPrintIdx;
	string text;
	DataType type;
};
class Panel
{
public:
	int *real;
	int *print;
	vector<int> mButtons;
	vector<PanelSliderCallback*> mCBSliders;
	vector<PanelButtonCallback*> mCBButtons;
	vector<PanelOnOffCallback*> mCBOnOffs;
	vector<PanelListCallback*> mCBLists;
	vector<Data> mData;
	Panel();
	~Panel();
	vector<string> mTypeStrs[4];
}


};