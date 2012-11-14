#include "DistorsionPanel.h"
namespace DistorsionPanelNS
{

const int PRESET_SIZE = 11;
const int NUM_PRESETS = 6;
int presets[] = {
    //Overdrive 1
    127, 64, 35, 56, 40, 0, 0, 6703, 21, 0, 0,
    //Overdrive 2
    127, 64, 35, 29, 45, 1, 0, 25040, 21, 0, 0,
    //Distorsion 1
    127, 64, 0, 87, 14, 6, 0, 3134, 157, 0, 1,
    //Distorsion 2
    127, 64, 127, 87, 14, 0, 1, 3134, 102, 0, 0,
    //Distorsion 3
    127, 64, 127, 127, 12, 13, 0, 5078, 56, 0, 1,
    //Guitar Amp
    127, 64, 35, 63, 50, 2, 0, 824, 21, 0, 0
};      

void DistorsionPanel::SetPreset(int preset)
{
    //for (int n = 0; n < PRESET_SIZE; n++)
        //mPlug->mEffDistorsion->changepar (n, mPresets[preset][n]);
	Button *but = (Button *)mGUI->GetElement(mPresetButton);
	but->mLabel = mPresetStrs[preset];

	mPlug->mEffDistorsion->changepar (12, 0);

	Slider *slider;
	/*
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
	*/
	slider = (Slider*)(mGUI->GetElement(mVolume));
	slider->SetVal(RealToPrint(0, mPresets[preset*PRESET_SIZE+0])); // callback automatically calls changepar
	slider = (Slider*)(mGUI->GetElement(mPanning));
	slider->SetVal(RealToPrint(1, mPresets[preset*PRESET_SIZE+1])); // callback automatically calls changepar
	slider = (Slider*)(mGUI->GetElement(mLRCr));
	slider->SetVal(RealToPrint(2, mPresets[preset*PRESET_SIZE+2])); // callback automatically calls changepar
	slider = (Slider*)(mGUI->GetElement(mDrive));
	slider->SetVal(RealToPrint(3, mPresets[preset*PRESET_SIZE+3])); // callback automatically calls changepar
	slider = (Slider*)(mGUI->GetElement(mLevel));
	slider->SetVal(RealToPrint(4, mPresets[preset*PRESET_SIZE+4])); // callback automatically calls changepar
	cbType->OnSelect(mPresets[preset*PRESET_SIZE+5]);
	OnOffButton *onoff;
	onoff = (OnOffButton*)mGUI->GetElement(mNeg);
	if(mPresets[preset*PRESET_SIZE+6])
	{
		onoff->mOn = true;
		myCB2->OnOn(); // neg
	}
	else
	{
		onoff->mOn = false;
		myCB2->OnOff();
	}
	slider = (Slider*)(mGUI->GetElement(mLPF));
	slider->SetVal(RealToPrint(7, GetRealMinMaxByFreq((float)mPresets[preset*PRESET_SIZE+7]))); // callback automatically calls changepar
	slider = (Slider*)(mGUI->GetElement(mHPF));
	slider->SetVal(RealToPrint(8, GetRealMinMaxByFreq((float)mPresets[preset*PRESET_SIZE+8]))); // callback automatically calls changepar
	//stereo in distorsion isn't being used in my plug
	
	onoff = (OnOffButton*)mGUI->GetElement(mPreFilter);
	if(mPresets[preset*PRESET_SIZE+10]) // prefilter
	{
		onoff->mOn = true;
		cbPrefilter->OnOn();
	}
	else
	{
		onoff->mOn = false;
		cbPrefilter->OnOff();
	}
	slider = (Slider*)(mGUI->GetElement(mSubOctv));
	slider->SetVal(0); // callback automatically calls changepar
}
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
	TextOption op2(x,y-35+3,180,10, 0,0,0,255);
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
	cbPresetSelect = new PresetCallback(this);
	cbPresetSelected = new PresetListCallback(this);
	cbType = new TypeCallback(this);
	mBypass = true;
	//mHidden = true;

	mPresetStrs.push_back("Overdrive 1");
    mPresetStrs.push_back("Overdrive 2");
    mPresetStrs.push_back("Distorsion 1");
    mPresetStrs.push_back("Distorsion 2");
    mPresetStrs.push_back("Distorsion 3");
    mPresetStrs.push_back("Guitar Amp");
  
	mPresets = presets;
	mTypeStrs.push_back("Atan");
	mTypeStrs.push_back("Asym");
	mTypeStrs.push_back("Pow");
	mTypeStrs.push_back("Sine");
	mTypeStrs.push_back("Quant");
	mTypeStrs.push_back("ZigZag");
	mTypeStrs.push_back("Lim");
	mTypeStrs.push_back("UpLim");
	mTypeStrs.push_back("LoLim");
	mTypeStrs.push_back("InvLim");

	mTypeStrs.push_back("Clip");
	mTypeStrs.push_back("Asym2");
	mTypeStrs.push_back("Pow2");
	mTypeStrs.push_back("Sigmoid");
	mTypeStrs.push_back("Crunch");
	mTypeStrs.push_back("HardCr");
	mTypeStrs.push_back("OctvUp");
	mTypeStrs.push_back("MSquare");
	mTypeStrs.push_back("MSaw");
	mTypeStrs.push_back("Compres");

	mTypeStrs.push_back("Overdrv");
	mTypeStrs.push_back("Soft");
	mTypeStrs.push_back("SupSoft");
	mTypeStrs.push_back("HardCmp");
	mTypeStrs.push_back("LmtNoG");
	mTypeStrs.push_back("FET");
	mTypeStrs.push_back("DynoFET");
	mTypeStrs.push_back("Valve1");
	mTypeStrs.push_back("Valve2");
	mTypeStrs.push_back("DiodeClp");


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
	
	mButtons.push_back(mGUI->NewButton(x+100,y-35+13,80, 20, "Default", cbPresetSelect)); // Preset
	mPresetButton = *(mButtons.end()-1);

	mButtons.push_back(mGUI->NewSlider(x+60,y,120, print[i*2], print[i*2+1])); // Wet/Dry
	mVolume = *(mButtons.end()-1);
	mGUI->SetSliderCallback(*(mButtons.end()-1), cbWetDry);
	mGUI->SetSliderVal(*(mButtons.end()-1), 32);
	y += 15;

	
	i=2;
	mButtons.push_back(mGUI->NewSlider(x+60,y,120, print[i*2], print[i*2+1])); // L/R.Cr
	mLRCr = *(mButtons.end()-1);
	mGUI->SetSliderCallback(*(mButtons.end()-1), cbLRCR);
	mGUI->SetSliderVal(*(mButtons.end()-1), 32);
	y += 15;
	i=3;
	mButtons.push_back(mGUI->NewSlider(x+60,y,120, print[i*2], print[i*2+1])); // Drive
	mDrive = *(mButtons.end()-1);
	mGUI->SetSliderCallback(*(mButtons.end()-1), cbDrive);
	mGUI->SetSliderVal(*(mButtons.end()-1), 32);
	y += 15;
	i=4;
	mButtons.push_back(mGUI->NewSlider(x+60,y,120, print[i*2], print[i*2+1])); // Level
	mLevel = *(mButtons.end()-1);
	mGUI->SetSliderCallback(*(mButtons.end()-1), cbLevel);
	mGUI->SetSliderVal(*(mButtons.end()-1), 32);
	y += 15;
		
	mButtons.push_back(mGUI->NewButton(x+5+40,y,60, 20, "ATan", myCB1)); // Type
	mTypeButton = *(mButtons.end()-1);
	mButtons.push_back(mGUI->NewOnOffButton(x+180-55,y,50, 20, "Neg.", myCB2)); // Neg.
	mNeg = *(mButtons.end()-1);
	y += 23;

	mButtons.push_back(mGUI->NewOnOffButton(x+5,y,75, 20, "Prefilter", cbPrefilter)); // Prefilter
	mPreFilter = *(mButtons.end()-1);
	//mButtons.push_back(mGUI->NewOnOffButton(x+5+80,y,70, 20, "Stereo", myCB2)); // Stereo
	y += 23;

	i=1;
	mButtons.push_back(mGUI->NewSlider(x+60,y,120, print[i*2], print[i*2+1])); // Pan
	mPanning = *(mButtons.end()-1);
	mGUI->SetSliderCallback(*(mButtons.end()-1), cbPan);
	mGUI->SetSliderVal(*(mButtons.end()-1), 32);
	y += 15;

	i=12;
	mButtons.push_back(mGUI->NewSlider(x+60,y,120, print[i*2], print[i*2+1])); // Sub Octv
	mSubOctv = *(mButtons.end()-1);
	mGUI->SetSliderCallback(*(mButtons.end()-1), cbSubOctv);
	mGUI->SetSliderVal(*(mButtons.end()-1), 32);
	y += 15;

	i=7;
	mButtons.push_back(mGUI->NewSlider(x+60,y,120, print[i*2], print[i*2+1], true)); // LPF
	mLPF = *(mButtons.end()-1);
	mGUI->SetSliderCallback(*(mButtons.end()-1), cbLPF);
	mGUI->SetSliderVal(*(mButtons.end()-1), 32);
	y += 15; 

	i=8;
	mButtons.push_back(mGUI->NewSlider(x+60,y,120, print[i*2], print[i*2+1], true)); // HPF
	mHPF = *(mButtons.end()-1);
	mGUI->SetSliderCallback(*(mButtons.end()-1), cbHPF);
	mGUI->SetSliderVal(*(mButtons.end()-1), 32);
	
	
	mPlug->mEffDistorsion->changepar(6, 0); // neg
	mPlug->mEffDistorsion->changepar(10, 0); // prefilter
	y += 15;

	SetPreset(0);
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
	mPanel->mGUI->mPopupList->hidden = false;
	mPanel->mGUI->mPopupList->Clear();

	for(int i=0;i<30;++i)
	{
		mPanel->mGUI->mPopupList->Add(mPanel->mTypeStrs[i]);
	}
	mPanel->mGUI->mPopupList->SetCallback(mPanel->cbType);
	
}

PresetCallback::	PresetCallback(DistorsionPanel *a)
	:mPanel(a), ButtonCallback()
{
}
void PresetCallback::OnClick()
{
	mPanel->mGUI->mPopupList->hidden = false;
	mPanel->mGUI->mPopupList->Clear();

	for(int i=0;i<NUM_PRESETS;++i)
	{
		mPanel->mGUI->mPopupList->Add(mPanel->mPresetStrs[i]);
	}
	mPanel->mGUI->mPopupList->SetCallback(mPanel->cbPresetSelected);
	
}


TypeCallback::TypeCallback(DistorsionPanel *a):mPanel(a), TabbedListBoxCallback()
{
}
void TypeCallback::OnPageSelect(int idx)
{
}
void TypeCallback::OnSelect(int idx)
{
	if(idx != -1)
	{
		mPanel->mGUI->mPopupList->hidden = true;
		mPanel->mGUI->mPopupList->Clear();
		mPanel->mPlug->mEffDistorsion->changepar(5, idx);
		Button *but = (Button *)mPanel->mGUI->GetElement(mPanel->mTypeButton);
		but->mLabel = mPanel->mTypeStrs[idx];
	}

}
PresetListCallback::PresetListCallback(DistorsionPanel *a):mPanel(a), TabbedListBoxCallback()
{
}
void PresetListCallback::OnPageSelect(int idx)
{
}
void PresetListCallback::OnSelect(int idx)
{
	if(idx != -1)
	{
		mPanel->mGUI->mPopupList->hidden = true;
		mPanel->mGUI->mPopupList->Clear();
		mPanel->SetPreset(idx);
	}

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
	
	mPanel->mPlug->mEffDistorsion->changepar(8, GetFreqByRealMinMax(newval));

	/*
	char temp[123];
	sprintf(temp, "%d", newval);
	MessageBox(NULL, temp, temp, MB_OK);*/
}

LPFCallback::LPFCallback(DistorsionPanel *a): mPanel(a), SliderCallback()
{
}
void LPFCallback::SetVal(int val)
{
	int newval = mPanel->PrintToReal(7, val);
	mPanel->mPlug->mEffDistorsion->changepar(7, GetFreqByRealMinMax(newval));
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

