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
	cbLRCR = new LRCRCallback(this);
	cbDrive = new DriveCallback(this);
	cbLevel = new LevelCallback(this);
	cbPan = new PanCallback(this);
	cbHPF = new HPFCallback(this);
	cbLPF = new LPFCallback(this);
	cbSubOctv = new SubOctvCallback(this);
	cbPrefilter = new DistorsionPrefilterCallback(this);
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
	mGUI->SetSliderCallback(*(mButtons.end()-1), cbLRCR);
	mGUI->SetSliderVal(*(mButtons.end()-1), 32);
	y += 15;
	i=3;
	mButtons.push_back(mGUI->NewSlider(x+60,y,120, print[i*2], print[i*2+1])); // Drive
	mGUI->SetSliderCallback(*(mButtons.end()-1), cbDrive);
	mGUI->SetSliderVal(*(mButtons.end()-1), 32);
	y += 15;
	i=4;
	mButtons.push_back(mGUI->NewSlider(x+60,y,120, print[i*2], print[i*2+1])); // Level
	mGUI->SetSliderCallback(*(mButtons.end()-1), cbLevel);
	mGUI->SetSliderVal(*(mButtons.end()-1), 32);
	y += 15;
		
	mButtons.push_back(mGUI->NewButton(x+5+40,y,60, 20, "ATan", myCB1)); // Type
		
	mButtons.push_back(mGUI->NewOnOffButton(x+180-55,y,50, 20, "Neg.", myCB2)); // Neg.
	y += 23;

	mButtons.push_back(mGUI->NewOnOffButton(x+5,y,75, 20, "Prefilter", cbPrefilter)); // Prefilter
	//mButtons.push_back(mGUI->NewOnOffButton(x+5+80,y,70, 20, "Stereo", myCB2)); // Stereo
	y += 23;

	i=1;
	mButtons.push_back(mGUI->NewSlider(x+60,y,120, print[i*2], print[i*2+1])); // Pan
	mGUI->SetSliderCallback(*(mButtons.end()-1), cbPan);
	mGUI->SetSliderVal(*(mButtons.end()-1), 32);
	y += 15;

	i=12;
	mButtons.push_back(mGUI->NewSlider(x+60,y,120, print[i*2], print[i*2+1])); // Sub Octv
	mGUI->SetSliderCallback(*(mButtons.end()-1), cbSubOctv);
	mGUI->SetSliderVal(*(mButtons.end()-1), 32);
	y += 15;

	i=7;
	mButtons.push_back(mGUI->NewSlider(x+60,y,120, print[i*2], print[i*2+1], true)); // LPF
	mGUI->SetSliderCallback(*(mButtons.end()-1), cbLPF);
	mGUI->SetSliderVal(*(mButtons.end()-1), 32);
	y += 15; 

	i=8;
	mButtons.push_back(mGUI->NewSlider(x+60,y,120, print[i*2], print[i*2+1], true)); // HPF
	mGUI->SetSliderCallback(*(mButtons.end()-1), cbHPF);
	mGUI->SetSliderVal(*(mButtons.end()-1), 32);
	
	
	mPlug->mEffDistorsion->changepar(6, 0); // neg
	mPlug->mEffDistorsion->changepar(10, 0); // prefilter
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
void DistorsionNegCallback::OnOn()
{
	mPanel->mPlug->mEffDistorsion->changepar(6, 1);
}
void DistorsionNegCallback::OnOff()
{
	mPanel->mPlug->mEffDistorsion->changepar(6, 0);
}

DistorsionPrefilterCallback::	DistorsionPrefilterCallback(DistorsionPanel *a)
	:mPanel(a), OnOffButtonCallback()
{
}
void DistorsionPrefilterCallback::OnOn()
{
	mPanel->mPlug->mEffDistorsion->changepar(10, 1);
}
void DistorsionPrefilterCallback::OnOff()
{
	mPanel->mPlug->mEffDistorsion->changepar(10, 0);
}


LPFCallBack::LPFCallBack(DistorsionPanel *a):SliderCallback() ,mPanel(a)
{
}
void LPFCallBack::SetVal(int val)
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
WetDryCallback::WetDryCallback(DistorsionPanel *a): mPanel(a)
{
}
void WetDryCallback::SetVal(int val)
{
	int newval = mPanel->PrintToReal(0, val);
	mPanel->mPlug->mEffDistorsion->changepar(0, newval);
	/*
	char temp[123];
	sprintf(temp, "%d", newval);
	MessageBox(NULL, temp, temp, MB_OK);*/
}
LRCRCallback::LRCRCallback(DistorsionPanel *a): mPanel(a)
{
}
void LRCRCallback::SetVal(int val)
{
	int newval = mPanel->PrintToReal(2, val);
	mPanel->mPlug->mEffDistorsion->changepar(2, newval);
	/*
	char temp[123];
	sprintf(temp, "%d", newval);
	MessageBox(NULL, temp, temp, MB_OK);*/
}

DriveCallback::DriveCallback(DistorsionPanel *a): mPanel(a)
{
}
void DriveCallback::SetVal(int val)
{
	int newval = mPanel->PrintToReal(3, val);
	mPanel->mPlug->mEffDistorsion->changepar(3, newval);
	/*
	char temp[123];
	sprintf(temp, "%d", newval);
	MessageBox(NULL, temp, temp, MB_OK);*/
}

LevelCallback::LevelCallback(DistorsionPanel *a): mPanel(a)
{
}
void LevelCallback::SetVal(int val)
{
	int newval = mPanel->PrintToReal(4, val);
	mPanel->mPlug->mEffDistorsion->changepar(4, newval);
	/*
	char temp[123];
	sprintf(temp, "%d", newval);
	MessageBox(NULL, temp, temp, MB_OK);*/
}


PanCallback::PanCallback(DistorsionPanel *a): mPanel(a)
{
}
void PanCallback::SetVal(int val)
{
	int newval = mPanel->PrintToReal(1, val);
	mPanel->mPlug->mEffDistorsion->changepar(1, newval);
	/*
	char temp[123];
	sprintf(temp, "%d", newval);
	MessageBox(NULL, temp, temp, MB_OK);*/
}

HPFCallback::HPFCallback(DistorsionPanel *a): mPanel(a)
{
}
void HPFCallback::SetVal(int val)
{
	int newval = mPanel->PrintToReal(8, val);
	mPanel->mPlug->mEffDistorsion->changepar(8, newval);
	/*
	char temp[123];
	sprintf(temp, "%d", newval);
	MessageBox(NULL, temp, temp, MB_OK);*/
}

LPFCallback::LPFCallback(DistorsionPanel *a): mPanel(a)
{
}
void LPFCallback::SetVal(int val)
{
	int newval = mPanel->PrintToReal(7, val);
	mPanel->mPlug->mEffDistorsion->changepar(7, newval);
	/*
	char temp[123];
	sprintf(temp, "%d", newval);
	MessageBox(NULL, temp, temp, MB_OK);*/
}

SubOctvCallback::SubOctvCallback(DistorsionPanel *a): mPanel(a)
{
}
void SubOctvCallback::SetVal(int val)
{
	int newval = mPanel->PrintToReal(12, val);
	mPanel->mPlug->mEffDistorsion->changepar(12, newval);
	/*
	char temp[123];
	sprintf(temp, "%d", newval);
	MessageBox(NULL, temp, temp, MB_OK);*/
}


};

