#include "CompressorPanel.h"

namespace CompressorNS
{

const int PRESET_SIZE = 9;
const int NUM_PRESETS = 3;
int presets[] = {
    //2:1
    -30, 2, -6, 20, 120, 1, 0, 0, 0,
    //4:1
	-26, 4, -8, 20, 120, 1, 10, 0, 0,
    //8:1
    -24, 8, -12, 20, 35, 1, 30, 0, 0,
};

int CompressorReal[] = { // Print는 따로 없다.
	-60,-3, // Threshold
	2,42, // Ratio
	-40,0, // Output
	10,250, // A. Time
	10,500, // R. Time
	0,1, // Auto Output:Bool
	0,100, // Knee
	0,1, // Stereo:Bool
	0,1, // Peak:Bool
};

void CompressorPanel::DrawText()
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
		y = 150+h+35;
	}
	TextOption op2(x,y-35+3,180,10, 0,0,0,255);
	mGUI->Print2(op2, "Compressor");
	mGUI->Print(TextOption(x+45,y-35+13,60, 20, 0,0,0,255), "Preset:");


	mGUI->Print(TextOption(x,y,60, 13, 0,0,0,255), "A. Time");
	y += 15;

	mGUI->Print(TextOption(x,y,60, 13, 0,0,0,255), "R. Time");
	y += 15;

	mGUI->Print(TextOption(x,y,60, 13, 0,0,0,255), "Ratio");
	y += 15;

	mGUI->Print(TextOption(x,y,60, 13, 0,0,0,255), "Knee");
	y += 15;

	mGUI->Print(TextOption(x,y,60, 13, 0,0,0,255), "Threshold");
	y += 15;

	mGUI->Print(TextOption(x,y,60, 13, 0,0,0,255), "Output");
	y += 15;

}

void CompressorPanel::SetPreset(int preset)
{
    //for (int n = 0; n < PRESET_SIZE; n++)
        //mPlug->mEffDistorsion->changepar (n, mPresets[preset][n]);
	Button *but = (Button *)mGUI->GetElement(mPresetButton);
	but->mLabel = mPresetStrs[preset];

	Slider *slider;
	OnOffButton *onoff;
	/*
	-60,-3, // Threshold
	2,42, // Ratio
	-40,0, // Output
	10,250, // A. Time
	10,500, // R. Time
	0,1, // Auto Output:Bool
	0,100, // Knee
	0,1, // Stereo:Bool
	0,1, // Peak:Bool
	*/
	slider = (Slider*)(mGUI->GetElement(mThreshold));
	slider->SetVal(mPresets[preset*PRESET_SIZE+0]); // callback automatically calls changepar
	slider = (Slider*)(mGUI->GetElement(mRatio));
	slider->SetVal(mPresets[preset*PRESET_SIZE+1]); // callback automatically calls changepar
	slider = (Slider*)(mGUI->GetElement(mOutput));
	slider->SetVal(mPresets[preset*PRESET_SIZE+2]); // callback automatically calls changepar
	slider = (Slider*)(mGUI->GetElement(mATime));
	slider->SetVal(mPresets[preset*PRESET_SIZE+3]); // callback automatically calls changepar
	slider = (Slider*)(mGUI->GetElement(mRTime));
	slider->SetVal(mPresets[preset*PRESET_SIZE+4]); // callback automatically calls changepar
	onoff = (OnOffButton*)mGUI->GetElement(mAuto);
	if(mPresets[preset*PRESET_SIZE+5])
	{
		onoff->mOn = true;
		cbAuto->OnOn();
	}
	else
	{
		onoff->mOn = false;
		cbAuto->OnOff();
	}
	slider = (Slider*)(mGUI->GetElement(mKnee));
	slider->SetVal(mPresets[preset*PRESET_SIZE+6]); // callback automatically calls changepar
	onoff = (OnOffButton*)mGUI->GetElement(mStereo);
	if(mPresets[preset*PRESET_SIZE+7])
	{
		onoff->mOn = true;
		cbStereo->OnOn();
	}
	else
	{
		onoff->mOn = false;
		cbStereo->OnOff();
	}
	onoff = (OnOffButton*)mGUI->GetElement(mPeak);
	if(mPresets[preset*PRESET_SIZE+8])
	{
		onoff->mOn = true;
		cbPeak->OnOn();
	}
	else
	{
		onoff->mOn = false;
		cbPeak->OnOff();
	}
	mPrevPreset = preset;
}
void CompressorPanel::LoadPreset(int preset)
{
    //for (int n = 0; n < PRESET_SIZE; n++)
        //mPlug->mEffDistorsion->changepar (n, mPresets[preset][n]);
	Button *but = (Button *)mGUI->GetElement(mPresetButton);
	if(preset < mPresetStrs.size())
		but->mLabel = mPresetStrs[preset];
	mPrevPreset = preset;
	Slider *slider;
	OnOffButton *onoff;
	/*
	-60,-3, // Threshold
	2,42, // Ratio
	-40,0, // Output
	10,250, // A. Time
	10,500, // R. Time
	0,1, // Auto Output:Bool
	0,100, // Knee
	0,1, // Stereo:Bool
	0,1, // Peak:Bool
	*/
	slider = (Slider*)(mGUI->GetElement(mThreshold));
	slider->SetVal(mPlug->mEffCompressor->getpar(1)); // callback automatically calls changepar
	slider = (Slider*)(mGUI->GetElement(mRatio));
	slider->SetVal(mPlug->mEffCompressor->getpar(2)); // callback automatically calls changepar
	slider = (Slider*)(mGUI->GetElement(mOutput));
	slider->SetVal(mPlug->mEffCompressor->getpar(3)); // callback automatically calls changepar
	slider = (Slider*)(mGUI->GetElement(mATime));
	slider->SetVal(mPlug->mEffCompressor->getpar(4)); // callback automatically calls changepar
	slider = (Slider*)(mGUI->GetElement(mRTime));
	slider->SetVal(mPlug->mEffCompressor->getpar(5)); // callback automatically calls changepar
	onoff = (OnOffButton*)mGUI->GetElement(mAuto);
	if(mPlug->mEffCompressor->getpar(6))
	{
		onoff->mOn = true;
		cbAuto->OnOn();
	}
	else
	{
		onoff->mOn = false;
		cbAuto->OnOff();
	}
	slider = (Slider*)(mGUI->GetElement(mKnee));
	slider->SetVal(mPlug->mEffCompressor->getpar(7)); // callback automatically calls changepar
	onoff = (OnOffButton*)mGUI->GetElement(mStereo);
	if(mPlug->mEffCompressor->getpar(8))
	{
		onoff->mOn = true;
		cbStereo->OnOn();
	}
	else
	{
		onoff->mOn = false;
		cbStereo->OnOff();
	}
	onoff = (OnOffButton*)mGUI->GetElement(mPeak);
	if(mPlug->mEffCompressor->getpar(9))
	{
		onoff->mOn = true;
		cbPeak->OnOn();
	}
	else
	{
		onoff->mOn = false;
		cbPeak->OnOff();
	}
}

CompressorPanel::CompressorPanel(GLGUI *gui, VstPlugin *plug, int whereis)
	:mGUI(gui), mWhereis(whereis), mPlug(plug)
{
	real = CompressorReal;
	mPresetStrs.push_back("2:1");
    mPresetStrs.push_back("4:1");
    mPresetStrs.push_back("8:1");
	mPresets = presets;

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
	cbATime = new ATimeCallback(this);
	cbRTime = new RTimeCallback(this);
	cbRatio = new RatioCallback(this);
	cbKnee = new KneeCallback(this);
	cbThreshold = new ThresholdCallback(this);
	cbOutput = new OutputCallback(this);
	cbPeak = new PeakCallback(this);
	cbAuto = new AutoCallback(this);
	cbStereo = new StereoCallback(this);

	int i=3;
	mButtons.push_back(mGUI->NewButton(x+100,y-35+13,80, 20, "Default", cbPresetSelect)); // Preset
	mPresetButton = *(mButtons.end()-1);

	mButtons.push_back(mGUI->NewSlider(x+60,y,120, real[i*2], real[i*2+1])); // A. Time
	mATime = *(mButtons.end()-1);
	mGUI->SetSliderCallback(*(mButtons.end()-1), cbATime);
	y += 15;

	i=4;
	mButtons.push_back(mGUI->NewSlider(x+60,y,120, real[i*2], real[i*2+1])); // R. Time
	mRTime = *(mButtons.end()-1);
	mGUI->SetSliderCallback(*(mButtons.end()-1), cbRTime);
	y += 15;

	i=1;
	mButtons.push_back(mGUI->NewSlider(x+60,y,120, real[i*2], real[i*2+1])); // Ratio
	mRatio = *(mButtons.end()-1);
	mGUI->SetSliderCallback(*(mButtons.end()-1), cbRatio);
	y += 15;

	i=6;
	mButtons.push_back(mGUI->NewSlider(x+60,y,120, real[i*2], real[i*2+1])); // Knee
	mKnee = *(mButtons.end()-1);
	mGUI->SetSliderCallback(*(mButtons.end()-1), cbKnee);
	y += 15;

	i=0;
	mButtons.push_back(mGUI->NewSlider(x+60,y,120, real[i*2], real[i*2+1])); // Threshold
	mThreshold = *(mButtons.end()-1);
	mGUI->SetSliderCallback(*(mButtons.end()-1), cbThreshold);
	y += 15;

	i=2;
	mButtons.push_back(mGUI->NewSlider(x+60,y,120, real[i*2], real[i*2+1])); // Output
	mOutput = *(mButtons.end()-1);
	mGUI->SetSliderCallback(*(mButtons.end()-1), cbOutput);
	y += 15;

	mButtons.push_back(mGUI->NewOnOffButton(x+5,y,90, 20, "Peak", cbPeak)); // Peak
	mPeak = *(mButtons.end()-1);
	y += 23;

	mButtons.push_back(mGUI->NewOnOffButton(x+5,y,90, 20, "Auto Output", cbAuto)); // Auto Output
	mAuto = *(mButtons.end()-1);
	y += 23;

	mButtons.push_back(mGUI->NewOnOffButton(x+5,y,90, 20, "Stereo", cbStereo)); // Stereo
	mStereo = *(mButtons.end()-1);


	//SetPreset(0);
}


PresetCallback::	PresetCallback(CompressorPanel *a)
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

PresetListCallback::PresetListCallback(CompressorPanel *a):mPanel(a), TabbedListBoxCallback()
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

ATimeCallback::ATimeCallback(CompressorPanel *a): mPanel(a), SliderCallback()
{
}
void ATimeCallback::SetVal(int val)
{
	int newval = val;
	mPanel->mPlug->mEffCompressor->Compressor_Change(4, newval); // ATime

}

RTimeCallback::RTimeCallback(CompressorPanel *a): mPanel(a), SliderCallback()
{
}
void RTimeCallback::SetVal(int val)
{
	int newval = val;
	mPanel->mPlug->mEffCompressor->Compressor_Change(5, newval); // RTime

}


RatioCallback::RatioCallback(CompressorPanel *a): mPanel(a), SliderCallback()
{
}
void RatioCallback::SetVal(int val)
{
	int newval = val;
	mPanel->mPlug->mEffCompressor->Compressor_Change(2, newval); // Ratio

}


KneeCallback::KneeCallback(CompressorPanel *a): mPanel(a), SliderCallback()
{
}
void KneeCallback::SetVal(int val)
{
	int newval = val;
	mPanel->mPlug->mEffCompressor->Compressor_Change(7, newval); // Knee

}


ThresholdCallback::ThresholdCallback(CompressorPanel *a): mPanel(a), SliderCallback()
{
}
void ThresholdCallback::SetVal(int val)
{
	int newval = val;
	mPanel->mPlug->mEffCompressor->Compressor_Change(1, newval); // Threshold

}


OutputCallback::OutputCallback(CompressorPanel *a): mPanel(a), SliderCallback()
{
}
void OutputCallback::SetVal(int val)
{
	int newval = val;
	mPanel->mPlug->mEffCompressor->Compressor_Change(3, newval); // Output

}


PeakCallback::	PeakCallback(CompressorPanel *a)
	:mPanel(a), OnOffButtonCallback()
{
}
void PeakCallback::OnOn()
{
	mPanel->mPlug->mEffCompressor->Compressor_Change(9, 1);
}
void PeakCallback::OnOff()
{
	mPanel->mPlug->mEffCompressor->Compressor_Change(9, 0);
}

AutoCallback::	AutoCallback(CompressorPanel *a)
	:mPanel(a), OnOffButtonCallback()
{
}
void AutoCallback::OnOn()
{
	mPanel->mPlug->mEffCompressor->Compressor_Change(6, 1);
}
void AutoCallback::OnOff()
{
	mPanel->mPlug->mEffCompressor->Compressor_Change(6, 0);
}

StereoCallback::	StereoCallback(CompressorPanel *a)
	:mPanel(a), OnOffButtonCallback()
{
}
void StereoCallback::OnOn()
{
	mPanel->mPlug->mEffCompressor->Compressor_Change(8, 1);
}
void StereoCallback::OnOff()
{
	mPanel->mPlug->mEffCompressor->Compressor_Change(8, 0);
}


};