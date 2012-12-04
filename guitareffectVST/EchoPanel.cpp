#include "EchoPanel.h"

namespace EchoNS
{
const int PRESET_SIZE = 9;
const int NUM_PRESETS = 9;
int presets[] = {
    //Echo 1
    67, 64, 565, 64, 30, 59, 0, 127, 0,
    //Echo 2
    67, 64, 357, 64, 30, 59, 0, 64, 0,
    //Echo 3
    67, 75, 955, 64, 30, 59, 10, 0, 0,
    //Simple Echo
    67, 60, 705, 64, 30, 0, 0, 0, 0,
    //Canyon
    67, 60, 1610, 50, 30, 82, 48, 0, 0,
    //Panning Echo 1
    67, 64, 705, 17, 0, 82, 24, 0, 0,
    //Panning Echo 2
    81, 60, 737, 118, 100, 68, 18, 0, 0,
    //Panning Echo 3
    81, 60, 472, 100, 127, 67, 36, 0, 0,
    //Feedback Echo
    62, 64, 456, 64, 100, 90, 55, 0, 0
};

int EchoReal[] = { 
	0, 127, // Dry/Wet
	0, 127, // Panning
	20, 2000, // Delay
	0, 127, // LRDelay
	0, 127, // LRCross
	0, 127, // FB
	0, 127, // hidamp
	0, 127, // Reverse
	0, 1, // Direct:Boolean
};
int EchoPrint[] = {
	-64,63,
	-64,63,
	20, 2000,
	0, 127,
	-64, 63,
	0, 127,
	0, 127,
	0, 127,
	0, 1,
};
void EchoPanel::SetPreset(int preset)
{
    //for (int n = 0; n < PRESET_SIZE; n++)
        //mPlug->mEffDistorsion->changepar (n, mPresets[preset][n]);
	Button *but = (Button *)mGUI->GetElement(mPresetButton);
	if(preset < mPresetStrs.size())
		but->mLabel = mPresetStrs[preset];
	mPlug->mEffEcho->changepar (8, 0); // Direct
	mPrevPreset = preset;
	Slider *slider;
	slider = (Slider*)(mGUI->GetElement(mVolume));
	slider->SetVal(RealToPrint(0, mPresets[preset*PRESET_SIZE+0])); // callback automatically calls changepar
	slider = (Slider*)(mGUI->GetElement(mPan));
	slider->SetVal(RealToPrint(1, mPresets[preset*PRESET_SIZE+1])); // callback automatically calls changepar
	slider = (Slider*)(mGUI->GetElement(mDelay));
	slider->SetVal(RealToPrint(2, mPresets[preset*PRESET_SIZE+2])); // callback automatically calls changepar
	slider = (Slider*)(mGUI->GetElement(mLRdl));
	slider->SetVal(RealToPrint(3, mPresets[preset*PRESET_SIZE+3])); // callback automatically calls changepar
	slider = (Slider*)(mGUI->GetElement(mLRCr));
	slider->SetVal(RealToPrint(4, mPresets[preset*PRESET_SIZE+4])); // callback automatically calls changepar
	slider = (Slider*)(mGUI->GetElement(mFb));
	slider->SetVal(RealToPrint(5, mPresets[preset*PRESET_SIZE+5])); // callback automatically calls changepar
	slider = (Slider*)(mGUI->GetElement(mDamp));
	slider->SetVal(RealToPrint(6, mPresets[preset*PRESET_SIZE+6])); // callback automatically calls changepar
	slider = (Slider*)(mGUI->GetElement(mReverse));
	slider->SetVal(RealToPrint(7, mPresets[preset*PRESET_SIZE+7])); // callback automatically calls changepar

}
void EchoPanel::LoadPreset(int preset)
{
    //for (int n = 0; n < PRESET_SIZE; n++)
        //mPlug->mEffDistorsion->changepar (n, mPresets[preset][n]);
	mPrevPreset = preset;
	Button *but = (Button *)mGUI->GetElement(mPresetButton);
	but->mLabel = mPresetStrs[preset];
	mPlug->mEffEcho->changepar (8, 0); // Direct
	mPrevPreset = preset;
	Slider *slider;
	slider = (Slider*)(mGUI->GetElement(mVolume));
	slider->SetVal(RealToPrint(0, mPlug->mEffEcho->getpar (0))); // callback automatically calls changepar
	slider = (Slider*)(mGUI->GetElement(mPan));
	slider->SetVal(RealToPrint(1, mPlug->mEffEcho->getpar (1))); // callback automatically calls changepar
	slider = (Slider*)(mGUI->GetElement(mDelay));
	slider->SetVal(RealToPrint(2, mPlug->mEffEcho->getpar (2))); // callback automatically calls changepar
	slider = (Slider*)(mGUI->GetElement(mLRdl));
	slider->SetVal(RealToPrint(3, mPlug->mEffEcho->getpar (3))); // callback automatically calls changepar
	slider = (Slider*)(mGUI->GetElement(mLRCr));
	slider->SetVal(RealToPrint(4, mPlug->mEffEcho->getpar (4))); // callback automatically calls changepar
	slider = (Slider*)(mGUI->GetElement(mFb));
	slider->SetVal(RealToPrint(5, mPlug->mEffEcho->getpar (5))); // callback automatically calls changepar
	slider = (Slider*)(mGUI->GetElement(mDamp));
	slider->SetVal(RealToPrint(6, mPlug->mEffEcho->getpar (6))); // callback automatically calls changepar
	slider = (Slider*)(mGUI->GetElement(mReverse));
	slider->SetVal(RealToPrint(7, mPlug->mEffEcho->getpar (7))); // callback automatically calls changepar

}
void EchoPanel::DrawText()
{
	int x,y,w=180,h=300;
	if(mWhereis < 5)
	{
		x = 180*mWhereis;
		y = 150+35;
	}
	else
	{
		x = 180*(mWhereis-5);
		y = 150+300+35;
	}
	TextOption op2(x,y-35+3,180,10, 0,0,0,255);
	mGUI->Print2(op2, "Echo");
	mGUI->Print(TextOption(x+45,y-35+13,60, 20, 0,0,0,255), "Preset:");
	mGUI->Print(TextOption(x,y,60, 13, 0,0,0,255), "Wet/Dry");
	y += 15;

	mGUI->Print(TextOption(x,y,60, 13, 0,0,0,255), "Reverse");
	y += 15;

	mGUI->Print(TextOption(x,y,60, 13, 0,0,0,255), "Pan");
	y += 15;

	mGUI->Print(TextOption(x,y,60, 13, 0,0,0,255), "Delay");
	y += 15;
	
	mGUI->Print(TextOption(x,y,60, 13, 0,0,0,255), "LR Delay");
	y += 15;
		
	mGUI->Print(TextOption(x,y,60, 13, 0,0,0,255), "L/R.Cr");
	y += 15;
		
	mGUI->Print(TextOption(x,y,60, 13, 0,0,0,255), "Fb.");
	y += 15;
		
	mGUI->Print(TextOption(x,y,60, 13, 0,0,0,255), "Damp");
	y += 15;

}
EchoPanel::EchoPanel(GLGUI *gui, VstPlugin *plug)
	:mGUI(gui), mPlug(plug)
{
}
void EchoPanel::Create(int whereis)
{
	mWhereis = whereis;
    mPresetStrs.push_back("Echo 1");
    mPresetStrs.push_back("Echo 2");
    mPresetStrs.push_back("Echo 3");
    mPresetStrs.push_back("Simple Echo");
    mPresetStrs.push_back("Canyon");
    mPresetStrs.push_back("Panning Echo 1");
    mPresetStrs.push_back("Panning Echo 2");
    mPresetStrs.push_back("Panning Echo 3");
    mPresetStrs.push_back("Feedback Echo");
	mPresets = presets;


	real = EchoReal;

	print = EchoPrint;
	int x,y,w=180,h=300;
	if(whereis < 5)
	{
		x = 180*whereis;
		y = 150+35;
	}
	else
	{
		x = 180*(whereis-5);
		y = 150+300+35;
	}
	cbPresetSelect = new PresetCallback(this);
	cbPresetSelected = new PresetListCallback(this);
	cbWetDry = new WetDryCallback (this);
	cbReverse = new ReverseCallback (this);
	cbPan = new PanCallback (this);
	cbDelay = new DelayCallback (this);
	cbLRdl = new LRdlCallback (this);
	cbLRCr = new LRCrCallback (this);
	cbFb = new FbCallback (this);
	cbDamp = new DampCallback(this);


	//mGUI->Print(TextOption(x+45,y-20,60, 20, 0,0,0,255), "Preset:");
	mButtons.push_back(mGUI->NewButton(x+100,y-35+13,80, 20, "Default", cbPresetSelect)); // Preset
	mPresetButton = *(mButtons.end()-1);

	int i=0;
	mButtons.push_back(mGUI->NewSlider(x+60,y,120, print[i*2], print[i*2+1])); // Wet/Dry
	mVolume = *(mButtons.end()-1);
	mGUI->SetSliderCallback(*(mButtons.end()-1), cbWetDry);
	y += 15;

	i=7;
	mButtons.push_back(mGUI->NewSlider(x+60,y,120, print[i*2], print[i*2+1])); // Reverse
	mReverse = *(mButtons.end()-1);
	mGUI->SetSliderCallback(*(mButtons.end()-1), cbReverse);
	y += 15;

	i=1;
	mButtons.push_back(mGUI->NewSlider(x+60,y,120, print[i*2], print[i*2+1])); // Pan
	mPan = *(mButtons.end()-1);
	mGUI->SetSliderCallback(*(mButtons.end()-1), cbPan);
	y += 15;

	i=2;
	mButtons.push_back(mGUI->NewSlider(x+60,y,120, print[i*2], print[i*2+1])); // Delay
	mDelay = *(mButtons.end()-1);
	mGUI->SetSliderCallback(*(mButtons.end()-1), cbDelay);
	y += 15;
		
	i=3;
	mButtons.push_back(mGUI->NewSlider(x+60,y,120, print[i*2], print[i*2+1])); // LRdl.
	mLRdl = *(mButtons.end()-1);
	mGUI->SetSliderCallback(*(mButtons.end()-1), cbLRdl);
	y += 15;
		
	i=4;
	mButtons.push_back(mGUI->NewSlider(x+60,y,120, print[i*2], print[i*2+1])); // LRCr
	mLRCr = *(mButtons.end()-1);
	mGUI->SetSliderCallback(*(mButtons.end()-1), cbLRCr);
	y += 15;
		
	i=5;
	mButtons.push_back(mGUI->NewSlider(x+60,y,120, print[i*2], print[i*2+1])); // Fb
	mFb = *(mButtons.end()-1);
	mGUI->SetSliderCallback(*(mButtons.end()-1), cbFb);
	y += 15;
		
	i=6;
	mButtons.push_back(mGUI->NewSlider(x+60,y,120, print[i*2], print[i*2+1])); // Damp
	mDamp = *(mButtons.end()-1);
	mGUI->SetSliderCallback(*(mButtons.end()-1), cbDamp);
	y += 15;
		

	//SetPreset(0);
	/*
	char temp[123];
	sprintf(temp, "%.4f %d", RealToVst(7, 47), VstToReal(7, 1.0));
	MessageBox(NULL, temp, temp, MB_OK);*/

}

PresetCallback::	PresetCallback(EchoPanel *a)
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
PresetListCallback::PresetListCallback(EchoPanel *a):mPanel(a), TabbedListBoxCallback()
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
WetDryCallback::WetDryCallback(EchoPanel *a): mPanel(a)
{
}
void WetDryCallback::SetVal(int val)
{
	int newval = mPanel->PrintToReal(0, val);
	mPanel->mPlug->mEffEcho->changepar(0, newval);
	/*
	char temp[123];
	sprintf(temp, "%d", newval);
	MessageBox(NULL, temp, temp, MB_OK);*/
}

/*
	0, 127, // Dry/Wet
	0, 127, // Panning
	20, 2000, // Delay
	0, 127, // LRDelay
	0, 127, // LRCross
	0, 127, // FB
	0, 127, // hidamp
	0, 127, // Reverse
	0, 1, // Direct:Boolean	
*/
PanCallback::PanCallback(EchoPanel *a): mPanel(a)
{
}
void PanCallback::SetVal(int val)
{
	int newval = mPanel->PrintToReal(1, val);
	mPanel->mPlug->mEffEcho->changepar(1, newval);
	/*
	char temp[123];
	sprintf(temp, "%d", newval);
	MessageBox(NULL, temp, temp, MB_OK);*/
}
DelayCallback::DelayCallback(EchoPanel *a): mPanel(a)
{
}
void DelayCallback::SetVal(int val)
{
	int newval = mPanel->PrintToReal(2, val);
	mPanel->mPlug->mEffEcho->changepar(2, newval);
	/*
	char temp[123];
	sprintf(temp, "%d", newval);
	MessageBox(NULL, temp, temp, MB_OK);*/
}
LRdlCallback::LRdlCallback(EchoPanel *a): mPanel(a)
{
}
void LRdlCallback::SetVal(int val)
{
	int newval = mPanel->PrintToReal(3, val);
	mPanel->mPlug->mEffEcho->changepar(3, newval);
	/*
	char temp[123];
	sprintf(temp, "%d", newval);
	MessageBox(NULL, temp, temp, MB_OK);*/
}
LRCrCallback::LRCrCallback(EchoPanel *a): mPanel(a)
{
}
void LRCrCallback::SetVal(int val)
{
	int newval = mPanel->PrintToReal(4, val);
	mPanel->mPlug->mEffEcho->changepar(4, newval);
	/*
	char temp[123];
	sprintf(temp, "%d", newval);
	MessageBox(NULL, temp, temp, MB_OK);*/
}
FbCallback::FbCallback(EchoPanel *a): mPanel(a)
{
}
void FbCallback::SetVal(int val)
{
	int newval = mPanel->PrintToReal(5, val);
	mPanel->mPlug->mEffEcho->changepar(5, newval);
	/*
	char temp[123];
	sprintf(temp, "%d", newval);
	MessageBox(NULL, temp, temp, MB_OK);*/
}
DampCallback::DampCallback(EchoPanel *a): mPanel(a)
{
}
void DampCallback::SetVal(int val)
{
	int newval = mPanel->PrintToReal(6, val);
	mPanel->mPlug->mEffEcho->changepar(6, newval);
	/*
	char temp[123];
	sprintf(temp, "%d", newval);
	MessageBox(NULL, temp, temp, MB_OK);*/
}
ReverseCallback::ReverseCallback(EchoPanel *a): mPanel(a)
{
}
void ReverseCallback::SetVal(int val)
{
	int newval = mPanel->PrintToReal(7, val);
	mPanel->mPlug->mEffEcho->changepar(7, newval);
	/*
	char temp[123];
	sprintf(temp, "%d", newval);
	MessageBox(NULL, temp, temp, MB_OK);*/
}

};