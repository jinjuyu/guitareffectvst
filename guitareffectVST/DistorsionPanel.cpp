#include "DistorsionPanel.h"
namespace DistorsionPanelNS
{
void DistorsionPanel::DrawText()
{
	int x,y,w=180,h=250;
	if(mWhereis < 5)
	{
		x = 180*mWhereis;
		y = 150+35;
	}
	else
	{
		x = 180*(mWhereis-5);
		y = 150+250+35;
	}
	TextOption op2(0,y-35+3,180,10, 0,0,0,255);
	mGUI->Print2(op2, "Distortion");
	mGUI->Print(TextOption(x+45,y-35+13,60, 20, 0,0,0,255), "Preset:");
	mGUI->Print(TextOption(x,y,60, 13, 0,0,0,255), "Wet/Dry");
	y += 15;

	mGUI->Print(TextOption(x,y,60, 13, 0,0,0,255), "L/R.Cr");
	y += 15;
	mGUI->Print(TextOption(x,y,60, 13, 0,0,0,255), "Drive");
	y += 15;
	mGUI->Print(TextOption(x,y,60, 13, 0,0,0,255), "Level");
	y += 15;
	mGUI->Print(TextOption(x,y,40, 20, 0,0,0,255), "Type");
		
	y += 23;
	y += 23;

	mGUI->Print(TextOption(x,y,60, 13, 0,0,0,255), "Pan");
	y += 15;

	mGUI->Print(TextOption(x,y,60, 13, 0,0,0,255), "Sub Octv");
	y += 15;

	mGUI->Print(TextOption(x,y,60, 13, 0,0,0,255), "LPF");
	y += 15; 

	mGUI->Print(TextOption(x,y,60, 13, 0,0,0,255), "HPF");
	y += 15;

}
DistorsionPanel::DistorsionPanel(GLGUI *gui, VstPlugin *plug, int whereis)
	:mGUI(gui), mWhereis(whereis), mPlug(plug)
{
	cbWetDry = new WetDryCallback(this);
	myCB1 = new DistorsionTypeCallback(this);
	myCB2 = new DistorsionNegCallback(this);
	mBypass = true;
	mHidden = true;
	real = DistortionReal;

	print = DistortionPrint;
	int x,y,w=180,h=250;
	if(whereis < 5)
	{
		x = 180*whereis;
		y = 150+35;
	}
	else
	{
		x = 180*(whereis-5);
		y = 150+250+35;
	}
	int i=0;
	//mGUI->Print(TextOption(x+45,y-20,60, 20, 0,0,0,255), "Preset:");
	mButtons.push_back(mGUI->NewButton(x+105,y-35+13,70, 20, "Default", myCB1)); // Preset

	mButtons.push_back(mGUI->NewSlider(x+60,y,120, print[i*2], print[i*2+1])); // Wet/Dry
	mGUI->SetSliderCallback(*(mButtons.end()-1), cbWetDry);
	mGUI->SetSliderVal(*(mButtons.end()-1), 32);
	y += 15;

	
	i=2;
	mButtons.push_back(mGUI->NewSlider(x+60,y,120, print[i*2], print[i*2+1])); // L/R.Cr
	y += 15;
	i=3;
	mButtons.push_back(mGUI->NewSlider(x+60,y,120, print[i*2], print[i*2+1])); // Drive
	y += 15;
	i=4;
	mButtons.push_back(mGUI->NewSlider(x+60,y,120, print[i*2], print[i*2+1])); // Level
	y += 15;
		
	mButtons.push_back(mGUI->NewButton(x+5+40,y,60, 20, "ATan", myCB1));
		
	mButtons.push_back(mGUI->NewOnOffButton(x+180-55,y,50, 20, "Neg.", myCB2));
	y += 23;

	mButtons.push_back(mGUI->NewOnOffButton(x+5,y,75, 20, "Prefilter", myCB2));
	mButtons.push_back(mGUI->NewOnOffButton(x+5+80,y,70, 20, "Stereo", myCB2));
	y += 23;

	i=1;
	mButtons.push_back(mGUI->NewSlider(x+60,y,120, print[i*2], print[i*2+1])); // Pan
	y += 15;

	i=12;
	mButtons.push_back(mGUI->NewSlider(x+60,y,120, print[i*2], print[i*2+1])); // Sub Octv
	y += 15;

	i=7;
	mButtons.push_back(mGUI->NewSlider(x+60,y,120, print[i*2], print[i*2+1], true)); // LPF
	y += 15; 

	i=8;
	mButtons.push_back(mGUI->NewSlider(x+60,y,120, print[i*2], print[i*2+1], true)); // HPF
	y += 15;
	/*
	char temp[123];
	sprintf(temp, "%.4f %d", RealToVst(7, 47), VstToReal(7, 1.0));
	MessageBox(NULL, temp, temp, MB_OK);*/
}
DistorsionTypeCallback::	DistorsionTypeCallback(DistorsionPanel *a)
	:mPanel(a), ButtonCallback()
{
}
void DistorsionTypeCallback::OnClick()
{
}

DistorsionNegCallback::	DistorsionNegCallback(DistorsionPanel *a)
	:mPanel(a), OnOffButtonCallback()
{
}
void DistorsionNegCallback::OnClick()
{
}


LPFCallBack::LPFCallBack(DistorsionPanel *a):SliderCallback() ,mPanel(a)
{
}
void LPFCallBack::SetVal(int val)
{
}

WetDryCallback::WetDryCallback(DistorsionPanel *a): mPanel(a)
{
}
int DistortionReal[] = {
	0, 127,
	0, 127,
	0, 127,
	0, 127,
	0, 127,
	0,29,
	0,1,
	47,171, // 20~26000, 이 값을 GetFreqByRealMinMax로 변환하면 주파수가 나온다.
	47,166, // 20~20000
	0,1,
	0,1,
	0,0,
	0,127,
};
int DistortionPrint[] = {
	-64,63, // Volume
	-64,63, // Panning
	-64,63, // L/R.Cr
	0,127, // Drive
	0,127, // Level
	0,29, // Type, Label로 타입을 가져옴 음 그러면 이 버튼을 누르면 위에 빈 공간에 탭드리스트 옵션창이 생성되어 고를수있게 한다.
	0,1, // Neg.:Boolean
	0,100, // LPF
	0,100, // HPF
	0,1, // Stereo:Boolean
	0,1, // Pre Filter:Boolean
	0,0, // 없음
	0,127, // Sub Octv
};
void WetDryCallback::SetVal(int val)
{
	int newval = mPanel->PrintToReal(0, val);
	mPanel->mPlug->mEffDistorsion->changepar(0, newval);
	/*
	char temp[123];
	sprintf(temp, "%d", newval);
	MessageBox(NULL, temp, temp, MB_OK);*/
}


};

