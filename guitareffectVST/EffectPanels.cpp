#include "../VSTGL/ExampleEditor.h"
#include "../VSTGL/VstPlugin.h"
#include "Panel.h"
void ExampleEditor::CreateMVVvol(int whereis, bool loadPrev, int prevIdx)
{
		const int mbvPRESET_SIZE = 11;
		const int mbvNUM_PRESETS = 3;
		int mbvpresets[] = {
			//Vary1
			0, 40, 0, 64, 80, 0, 0, 500, 2500, 5000, 0,
			//Vary2
			0, 80, 0, 64, 40, 0, 0, 120, 600, 2300, 1,
			//Vary3
			0, 120, 0, 64, 40, 0, 0, 800, 2300, 5200, 2
		};

		int MBVvolReal[] = {
			//case 0:
			0,127,
				//setvolume (value);
				//break;
			//case 1:
			1,600,
				//lfo1.Pfreq = value;
				//lfo1.updateparams ();
				//break;
			//case 2:
			0,9,
				//lfo1.PLFOtype = value;
				//lfo1.updateparams ();
				//break;
			//case 3:
			0,127,
				//lfo1.Pstereo = value;
				//lfo1.updateparams ();
				//break;
			//case 4:
			1,600,
				//lfo2.Pfreq = value;
				//lfo2.updateparams ();
				//break;
			//case 5:
			0,9,
				//lfo2.PLFOtype = value;
				//lfo2.updateparams ();
				//break;
			//case 6:
			0,127,
				//lfo2.Pstereo = value;
				//lfo2.updateparams ();
				//break;
			//case 7:
			47, 115,// 20~1000
				//setCross1 (value);
				//break;
			//case 8:
			114, 151, // 1000~8000
				//setCross2 (value);
				//break;
			//case 9:
			126, 167, // 2000~26000
				//setCross3(value);
				//break;
			//case 10:
			0,10,
			/*
            1122
            1221
            1212
            o11o
            o12o // 5
            x11x
            x12x
            1oo1
            1oo2
            1xx1 // 10
            1xx2 // 11
			*/
				//Pcombi=value;
				//break;


		};
		int MBVvolPrint[] = {
			-64,63,
			1,600,
			0,9,
			0,127,
			1,600,
			0,9,
			0,127,
			0,100,
			0,100,
			0,100,
			0,10,
		};
		int *real = MBVvolReal;
		int *print = MBVvolPrint;
		vector<string> presetTexts;
		presetTexts.push_back("Vary Band 1");
		presetTexts.push_back("Vary Band 2");
		presetTexts.push_back("Vary Band 3");
		mPanels[whereis] = new PanelNS::Panel(mGUI, (VstPlugin*)effect, ((VstPlugin*)effect)->mEffMBVvol, "VaryBand", whereis, mbvpresets, mbvPRESET_SIZE, mbvNUM_PRESETS, presetTexts);
		int iii=0;
		mPanels[whereis]->AddParamData(PanelNS::Data(iii, real[iii*2], real[iii*2+1], print[iii*2], print[iii*2+1], "Wet/Dry", PanelNS::Slider));
		iii=1;
		mPanels[whereis]->AddParamData(PanelNS::Data(iii, real[iii*2], real[iii*2+1], print[iii*2], print[iii*2+1], "Tempo1", PanelNS::Slider));
		vector<string> lfoTypeStrs;
		lfoTypeStrs.push_back("Sine");
		lfoTypeStrs.push_back("Tri");
		lfoTypeStrs.push_back("RampUp");
		lfoTypeStrs.push_back("RampDn");
		lfoTypeStrs.push_back("ZigZag");
		lfoTypeStrs.push_back("M.Sqare");
		lfoTypeStrs.push_back("M.Saw");
		lfoTypeStrs.push_back("L.Fract");
		lfoTypeStrs.push_back("L.FractXY");
		lfoTypeStrs.push_back("S/H Rnd");
		iii=2;
		mPanels[whereis]->AddParamData(PanelNS::Data(iii, real[iii*2], real[iii*2+1], print[iii*2], print[iii*2+1],  "LFO1Type", PanelNS::Selection, false, false, lfoTypeStrs));
		iii=3;
		mPanels[whereis]->AddParamData(PanelNS::Data(iii, real[iii*2], real[iii*2+1], print[iii*2], print[iii*2+1], "St.df1", PanelNS::Slider));
		iii=4;
		mPanels[whereis]->AddParamData(PanelNS::Data(iii, real[iii*2], real[iii*2+1], print[iii*2], print[iii*2+1], "Tempo2", PanelNS::Slider));
		lfoTypeStrs.clear();
		lfoTypeStrs.push_back("Sine");
		lfoTypeStrs.push_back("Tri");
		lfoTypeStrs.push_back("RampUp");
		lfoTypeStrs.push_back("RampDn");
		lfoTypeStrs.push_back("ZigZag");
		lfoTypeStrs.push_back("M.Sqare");
		lfoTypeStrs.push_back("M.Saw");
		lfoTypeStrs.push_back("L.Fract");
		lfoTypeStrs.push_back("L.FractXY");
		lfoTypeStrs.push_back("S/H Rnd");
		iii=5;
		mPanels[whereis]->AddParamData(PanelNS::Data(iii, real[iii*2], real[iii*2+1], print[iii*2], print[iii*2+1],  "LFO2Type", PanelNS::Selection, false, false, lfoTypeStrs));
		iii=6;
		mPanels[whereis]->AddParamData(PanelNS::Data(iii, real[iii*2], real[iii*2+1], print[iii*2], print[iii*2+1], "St.df2", PanelNS::Slider));

		iii=7;
		mPanels[whereis]->AddParamData(PanelNS::Data(iii, real[iii*2], real[iii*2+1], print[iii*2], print[iii*2+1], "Cross1", PanelNS::Slider, true));
		iii=8;
		mPanels[whereis]->AddParamData(PanelNS::Data(iii, real[iii*2], real[iii*2+1], print[iii*2], print[iii*2+1], "Cross2", PanelNS::Slider, true));
		iii=9;
		mPanels[whereis]->AddParamData(PanelNS::Data(iii, real[iii*2], real[iii*2+1], print[iii*2], print[iii*2+1], "Cross3", PanelNS::Slider, true));
		vector<string> combiStrs;
        combiStrs.push_back("1122");
        combiStrs.push_back("1221");
        combiStrs.push_back("1212");
        combiStrs.push_back("o11o");
        combiStrs.push_back("o12o");
        combiStrs.push_back("x11x");
        combiStrs.push_back("x12x");
        combiStrs.push_back("1oo1");
        combiStrs.push_back("1oo2");
        combiStrs.push_back("1xx1");
        combiStrs.push_back("1xx2");
		iii=10;
		mPanels[whereis]->AddParamData(PanelNS::Data(iii, real[iii*2], real[iii*2+1], print[iii*2], print[iii*2+1],  "Combi", PanelNS::Selection, false, false, combiStrs));
		if(loadPrev)
			mPanels[whereis]->LoadPreset(prevIdx);
		else
			mPanels[whereis]->SetPreset(0);

}
void ExampleEditor::CreateSynthfilter(int whereis, bool loadPrev, int prevIdx)
{
		const int sfilPRESET_SIZE = 16;
		const int sfilNUM_PRESETS = 7;
		int sfilpresets[] = {
			//Low Pass
			0, 20, 14, 0, 1, 64, 110, -40, 6, 0, 0, 32, -32, 500, 100, 0,
			//High Pass
			0, 20, 14, 0, 1, 64, 110, -40, 0, 6, 0, 32, -32, 500, 100, 0,
			//Band Pass
			0, 20, 14, 0, 1, 64, 110, -40, 4, 4, 0, 32, -32, 500, 100, 0,
			//Lead Synth
			0, 89, 31, 0, 1, 95, 38, -16, 1, 2, 1, 114, -32, 92, 215, 29,
			//Water
			20, 69, 88, 0, 6, 0, 76, -50, 6, 2, 1, 0, 19, 114, 221, 127,
			//Pan Filter
			0, 20, 100, 0, 5, 127, 127, -64, 2, 0, 0, 57, 0, 340, 288, 110,
			//Multi
			64, 45, 88, 0, 1, 127, 81, 0, 4, 2, 0, 67, 0, 394, 252, 61


		};
		int SynthFilterReal[] = {
			//case 0:
			0,127,
				//setvolume (value);
				//break;
			//case 1:
			0,127,
				//setdistortion (value);
				//break;
			//case 2:
			1,600,
				//lfo.Pfreq = value;
				//lfo.updateparams ();
				//break;
			//case 3:
			0, 127,
				//lfo.Prandomness = value;
				//lfo.updateparams ();
				//break;
			//case 4:
			0,9,
				//lfo.PLFOtype = value;
				//lfo.updateparams ();
				//break;
			//case 5:
			0,127,
				//lfo.Pstereo = value;
				//lfo.updateparams ();
				//break;
			//case 6:
			0,127,
				//setwidth (value);
				//break;
			//case 7:
			-64,64,
				//setfb (value);
				//break;
			//case 8:
			0,12,
				//Plpstages = value;
				//if (Plpstages >= MAX_SFILTER_STAGES)
					//Plpstages = MAX_SFILTER_STAGES ;
				//if(Plpstages<=2) fb = (float) Pfb * 0.25/65.0f;  //keep filter stable when phase shift is small
				//cleanup ();
				//break;
			//case 9:
			0,12,
				//Phpstages = value;
				//if (Phpstages >= MAX_SFILTER_STAGES)
					//Phpstages = MAX_SFILTER_STAGES ;
				//cleanup ();
				//break;
			//case 10:
			0,1,
				//if (value > 1)
					//value = 1;
				//Poutsub = value;
				//break;
			//case 11:
			0,127,
				//setdepth (value);
				//break;
			//case 12:
			-64,64,
				//Penvelope = value;
				//sns = (float) Penvelope/8.0f;
				//break;
			//case 13:
			5,1000,
				//Pattack = value;
				//if(Pattack < 5) Pattack = 5;
				//att = delta * 1000.0f/((float) Pattack);
				//break;
			//case 14:
			5,500,
				//Prelease = value;
				//if(Prelease < 5) Prelease = 5;
				//rls = delta * 1000.0f/((float) Prelease);
				//break;
			//case 15:
			0,127,
				//Pbandwidth = value;
				//Chp = C * (1.0f + ((float) value)/64.0f);  // C*3
				//Clp = C * (1.0f - ((float) value)/190.0f); // C/3
				//break;


		};
		int SynthFilterPrint[] = {
			-64,63, // 0
			0,127,
			1,600, // 2
			0,127,
			0,9, // 4
			0,127,
			0,127, // 6
			-64,64,
			0,12, // 8
			0,12,
			0,1, // 10
			0,127,
			-64,64, // 12
			5,1000,
			5,500, // 14
			0,127,
		};
		int *real = SynthFilterReal;
		int *print = SynthFilterPrint;
		vector<string> presetTexts;
		presetTexts.push_back("Low Pass");
		presetTexts.push_back("High Pass");
		presetTexts.push_back("Band Pass");
		presetTexts.push_back("Lead Synth");
		presetTexts.push_back("Water");
		presetTexts.push_back("Pan Filter");
		presetTexts.push_back("Multi");
		mPanels[whereis] = new PanelNS::Panel(mGUI, (VstPlugin*)effect, ((VstPlugin*)effect)->mEffSynthfilter, "Synthfilter", whereis, sfilpresets, sfilPRESET_SIZE, sfilNUM_PRESETS, presetTexts);
		int iii=0;
		mPanels[whereis]->AddParamData(PanelNS::Data(iii, real[iii*2], real[iii*2+1], print[iii*2], print[iii*2+1], "Wet/Dry", PanelNS::Slider));
		iii=1;
		mPanels[whereis]->AddParamData(PanelNS::Data(iii, real[iii*2], real[iii*2+1], print[iii*2], print[iii*2+1], "Distort", PanelNS::Slider));
		iii=2;
		mPanels[whereis]->AddParamData(PanelNS::Data(iii, real[iii*2], real[iii*2+1], print[iii*2], print[iii*2+1], "Tempo", PanelNS::Slider));
		vector<string> lfoTypeStrs;
		lfoTypeStrs.push_back("Sine");
		lfoTypeStrs.push_back("Tri");
		lfoTypeStrs.push_back("RampUp");
		lfoTypeStrs.push_back("RampDn");
		lfoTypeStrs.push_back("ZigZag");
		lfoTypeStrs.push_back("M.Sqare");
		lfoTypeStrs.push_back("M.Saw");
		lfoTypeStrs.push_back("L.Fract");
		lfoTypeStrs.push_back("L.FractXY");
		lfoTypeStrs.push_back("S/H Rnd");
		iii=4;
		mPanels[whereis]->AddParamData(PanelNS::Data(iii, real[iii*2], real[iii*2+1], print[iii*2], print[iii*2+1],  "LFOType", PanelNS::Selection, false, false, lfoTypeStrs));
		iii=10;
		mPanels[whereis]->AddParamData(PanelNS::Data(iii, real[iii*2], real[iii*2+1], print[iii*2], print[iii*2+1], "Subtract", PanelNS::OnOff));
		iii=5;
		mPanels[whereis]->AddParamData(PanelNS::Data(iii, real[iii*2], real[iii*2+1], print[iii*2], print[iii*2+1], "St.df", PanelNS::Slider));
		iii=6;
		mPanels[whereis]->AddParamData(PanelNS::Data(iii, real[iii*2], real[iii*2+1], print[iii*2], print[iii*2+1], "Width", PanelNS::Slider));
		iii=7;
		mPanels[whereis]->AddParamData(PanelNS::Data(iii, real[iii*2], real[iii*2+1], print[iii*2], print[iii*2+1], "Fb", PanelNS::Slider));
		iii=8;
		mPanels[whereis]->AddParamData(PanelNS::Data(iii, real[iii*2], real[iii*2+1], print[iii*2], print[iii*2+1], "LPF Stg.", PanelNS::Slider));
		iii=9;
		mPanels[whereis]->AddParamData(PanelNS::Data(iii, real[iii*2], real[iii*2+1], print[iii*2], print[iii*2+1], "HPF Stg.", PanelNS::Slider));
		iii=11;
		mPanels[whereis]->AddParamData(PanelNS::Data(iii, real[iii*2], real[iii*2+1], print[iii*2], print[iii*2+1], "Depth", PanelNS::Slider));
		iii=12;
		mPanels[whereis]->AddParamData(PanelNS::Data(iii, real[iii*2], real[iii*2+1], print[iii*2], print[iii*2+1], "E.Sens", PanelNS::Slider));
		iii=13;
		mPanels[whereis]->AddParamData(PanelNS::Data(iii, real[iii*2], real[iii*2+1], print[iii*2], print[iii*2+1], "A.Time", PanelNS::Slider));
		iii=14;
		mPanels[whereis]->AddParamData(PanelNS::Data(iii, real[iii*2], real[iii*2+1], print[iii*2], print[iii*2+1], "R.Time", PanelNS::Slider));
		iii=15;
		mPanels[whereis]->AddParamData(PanelNS::Data(iii, real[iii*2], real[iii*2+1], print[iii*2], print[iii*2+1], "Offset", PanelNS::Slider));
		if(loadPrev)
			mPanels[whereis]->LoadPreset(prevIdx);
		else
			mPanels[whereis]->SetPreset(0);

}
void ExampleEditor::CreateShuffle(int whereis, bool loadPrev, int prevIdx)
{
		const int shufflPRESET_SIZE = 11;
		const int shufflNUM_PRESETS = 4;
		int shufflpresets[] = {
			//Shuffle 1
			64, 10, 0, 0, 0,600, 1200,2000, 6000,-14, 1,
			//Shuffle 2
			64, 0, 0, 0, 0, 120, 1000,2400, 8000,-7, 1,
			//Shuffle 3
			64, 0, 0, 0, 0, 60, 1800, 3700, 12000, 7, 0,
			//Remover
			0, 17, 0, 7, 5, 600, 1200, 2000, 13865, -45, 1
		};

		int ShuffleReal[] = {
			//case 0:
			0,128,
				//setvolume (value);
				//break;
			//case 1:
			-64,64,
				//setGainL(value);
				//break;
			//case 2:
			-64,64,
				//setGainML(value);
				//break;
			//case 3:
			-64,64,
				//setGainMH(value);
				//break;
			//case 4:
			-64,64,
				//setGainH(value);
				//break;
			//case 5:
			47,115,
				//setCross1 (value);
				//break;
			//case 6:
			98,139,
				//setCross2 (value);
				//break;
			//case 7:
			117,139,
				//setCross3 (value);
				//break;
			//case 8:
			145,171,
				//setCross4 (value);
				//break;
			//case 9:
			-64,64,
				//PQ = value;
				//value +=64;
				//tmp = powf (30.0f, ((float)value - 64.0f) / 64.0f);
				//lr->setq(tmp);
				//mlr->setq(tmp);
				//mhr->setq(tmp);
				//hr->setq(tmp);
				//break;
			//case 10:
			0,1,
				//E=value;
				//break;


		};
		int ShufflePrint[] = {
			-64,64, // 0
			-64,64,
			-64,64, // 2
			-64,64,
			-64,64, // 4
			0,100,
			0,100, // 6
			0,100,
			0,100, // 8
			-64,64,
			0,1,
		};
		int *real = ShuffleReal;
		int *print = ShufflePrint;
		vector<string> presetTexts;
		presetTexts.push_back("Shuffle 1");
		presetTexts.push_back("Shuffle 2");
		presetTexts.push_back("Shuffle 3");
		presetTexts.push_back("Remover");
		mPanels[whereis] = new PanelNS::Panel(mGUI, (VstPlugin*)effect, ((VstPlugin*)effect)->mEffShuffle, "Shuffle", whereis, shufflpresets, shufflPRESET_SIZE, shufflNUM_PRESETS, presetTexts);
		int iii=0;
		mPanels[whereis]->AddParamData(PanelNS::Data(iii, real[iii*2], real[iii*2+1], print[iii*2], print[iii*2+1], "Wet/Dry", PanelNS::Slider));
		iii=5;
		mPanels[whereis]->AddParamData(PanelNS::Data(iii, real[iii*2], real[iii*2+1], print[iii*2], print[iii*2+1], "Low Freq", PanelNS::Slider, true));
		iii=1;
		mPanels[whereis]->AddParamData(PanelNS::Data(iii, real[iii*2], real[iii*2+1], print[iii*2], print[iii*2+1], "Low Gain", PanelNS::Slider));
		iii=6;
		mPanels[whereis]->AddParamData(PanelNS::Data(iii, real[iii*2], real[iii*2+1], print[iii*2], print[iii*2+1], "MLow Freq", PanelNS::Slider, true));
		iii=2;
		mPanels[whereis]->AddParamData(PanelNS::Data(iii, real[iii*2], real[iii*2+1], print[iii*2], print[iii*2+1], "MLow Gain", PanelNS::Slider));
		iii=7;
		mPanels[whereis]->AddParamData(PanelNS::Data(iii, real[iii*2], real[iii*2+1], print[iii*2], print[iii*2+1], "MHi Freq", PanelNS::Slider, true));
		iii=3;
		mPanels[whereis]->AddParamData(PanelNS::Data(iii, real[iii*2], real[iii*2+1], print[iii*2], print[iii*2+1], "MHi Gain", PanelNS::Slider));
		iii=8;
		mPanels[whereis]->AddParamData(PanelNS::Data(iii, real[iii*2], real[iii*2+1], print[iii*2], print[iii*2+1], "Hi Freq", PanelNS::Slider, true));
		iii=4;
		mPanels[whereis]->AddParamData(PanelNS::Data(iii, real[iii*2], real[iii*2+1], print[iii*2], print[iii*2+1], "Hi Gain", PanelNS::Slider));
		iii=9;
		mPanels[whereis]->AddParamData(PanelNS::Data(iii, real[iii*2], real[iii*2+1], print[iii*2], print[iii*2+1], "Q", PanelNS::Slider));
		iii=10;
		mPanels[whereis]->AddParamData(PanelNS::Data(iii, real[iii*2], real[iii*2+1], print[iii*2], print[iii*2+1], "Rev", PanelNS::OnOff));
		if(loadPrev)
			mPanels[whereis]->LoadPreset(prevIdx);
		else
			mPanels[whereis]->SetPreset(0);

}
void ExampleEditor::CreateExpander(int whereis, bool loadPrev, int prevIdx)
{
		const int expanderPRESET_SIZE = 7;
		const int expanderNUM_PRESETS = 3;
		int expanderpresets[] = {
			//Noise Gate
			-50, 20, 50, 50, 3134, 76, 0,
			//Boost Gate
			-55, 30, 50, 50, 1441, 157, 50,
			//Treble swell
			-30, 9, 950, 25, 6703, 526, 90
		};
		int ExpanderReal[] = {
			//case 1:
			-80,0,
				//Pthreshold = value;
				//tfactor = dB2rap (-((float) Pthreshold));
				//tlevel = 1.0f/tfactor;
				//break;
			//case 2:
			1,50,
				//Pshape = value;
				//sfactor = dB2rap ((float)Pshape/2);
				//sgain = expf(-sfactor);
				//break;
			//case 3:
			10,2000,
				//Pattack = value;
				//a_rate = 1000.0f/((float)Pattack * fs);
				//break;
			//case 4:
			10,500,
				//Pdecay = value;
				//d_rate = 1000.0f/((float)Pdecay * fs);
				//break;
			//case 5:
			47,171, // 20~26000, 이 값을 GetFreqByRealMinMax로 변환하면 주파수가 나온다.
				//setlpf(value);
				//break;
			//case 6:
			47,166, // 20~20000
				//sethpf(value);
				//break;
			//case 7:
			1,127,
				//Plevel = value;
				//level = dB2rap((float) value/6.0f);
				//break;


		};
		int ExpanderPrint[] = {
			-80,0,
			1,50,
			10,2000,
			10,500,
			0,100,
			0,100,
			1,127,
		};

		int *real = ExpanderReal;
		int *print = ExpanderPrint;
		vector<string> presetTexts;
		presetTexts.push_back("Noise Gate");
		presetTexts.push_back("Boost Gate");
		presetTexts.push_back("Treble swell");
		mPanels[whereis] = new PanelNS::Panel(mGUI, (VstPlugin*)effect, ((VstPlugin*)effect)->mEffExpander, "Expander", whereis, expanderpresets, expanderPRESET_SIZE, expanderNUM_PRESETS, presetTexts);
		int iii=2;
		mPanels[whereis]->AddParamData(PanelNS::Data(iii, real[iii*2], real[iii*2+1], print[iii*2], print[iii*2+1], "A.Time", PanelNS::Slider, false, false, vector<string>(), iii));
		iii=3;
		mPanels[whereis]->AddParamData(PanelNS::Data(iii, real[iii*2], real[iii*2+1], print[iii*2], print[iii*2+1], "R.Time", PanelNS::Slider, false, false, vector<string>(), iii));
		iii=1;
		mPanels[whereis]->AddParamData(PanelNS::Data(iii, real[iii*2], real[iii*2+1], print[iii*2], print[iii*2+1], "Shape", PanelNS::Slider, false, false, vector<string>(), iii));
		iii=0;
		mPanels[whereis]->AddParamData(PanelNS::Data(iii, real[iii*2], real[iii*2+1], print[iii*2], print[iii*2+1], "Thrshld", PanelNS::Slider, false, false, vector<string>(), iii));
		iii=6;
		mPanels[whereis]->AddParamData(PanelNS::Data(iii, real[iii*2], real[iii*2+1], print[iii*2], print[iii*2+1], "Level", PanelNS::Slider, false, false, vector<string>(), iii));
		iii=4;
		mPanels[whereis]->AddParamData(PanelNS::Data(iii, real[iii*2], real[iii*2+1], print[iii*2], print[iii*2+1], "LPF", PanelNS::Slider, true, false, vector<string>(), iii));
		iii=5;
		mPanels[whereis]->AddParamData(PanelNS::Data(iii, real[iii*2], real[iii*2+1], print[iii*2], print[iii*2+1], "HPF", PanelNS::Slider, true, false, vector<string>(), iii));
		if(loadPrev)
			mPanels[whereis]->LoadPreset(prevIdx);
		else
			mPanels[whereis]->SetPreset(0);

}
void ExampleEditor::CreateArpie(int whereis, bool loadPrev, int prevIdx)
{
		const int arpPRESET_SIZE = 9;
		const int arpNUM_PRESETS = 9;
		int arppresets[] = {
			//Arpie 1
			67, 64, 35, 64, 30, 59, 0, 127, 4,
			//Arpie 2
			67, 64, 21, 64, 30, 59, 0, 64, 4,
			//Arpie 3
			67, 75, 60, 64, 30, 59, 10, 0, 4,
			//Simple Arpie
			67, 60, 44, 64, 30, 0, 0, 0, 4,
			//Canyon
			67, 60, 102, 50, 30, 82, 48, 0, 4,
			//Panning Arpie 1
			67, 64, 44, 17, 0, 82, 24, 0, 4,
			//Panning Arpie 2
			81, 60, 46, 118, 100, 68, 18, 0, 4,
			//Panning Arpie 3
			81, 60, 26, 100, 127, 67, 36, 0, 4,
			//Feedback Arpie
			62, 64, 28, 64, 100, 90, 55, 0, 4
		};

		int ArpieReal[] = {
			//case 0:
			0,127,
				//setvolume (value);
				//break;
			//case 1:
			0,127,
				//setpanning (value);
				//break;
			//case 2:
			1,600,
				//setdelay (value);
				//break;
			//case 3:
			0,127,
				//setlrdelay (value);
				//break;
			//case 4:
			0,127,
				//setlrcross (value);
				//break;
			//case 5:
			0,127,
				//setfb (value);
				//break;
			//case 6:
			0,127,
				//sethidamp (value);
				//break;
			//case 7:
			0,127,
				//setreverse (value);
				//break;
			//case 8:
			1,8,
				//Pharms = value;
				//if ( (Pharms < 2) && (Pharms >= MAXHARMS)) {
					//Pharms = 2;
				//}
				//break;
			//case 9:
			0,5,
          /*MenuItem {} {
            label Ascending
            xywh {77 77 36 21} labelsize 10
          }
          MenuItem {} {
            label Descending
            xywh {77 77 36 21} labelsize 10
          }
          MenuItem {} {
            label UpDown
            xywh {77 77 36 21} labelsize 10
          }
          MenuItem {} {
            label Stutter
            xywh {87 87 36 21} labelsize 10
          }
          MenuItem {} {
            label {Interrupted Descent}
            xywh {97 97 36 21} labelsize 10
          }
          MenuItem {} {
            label {Double Descend }
            xywh {117 117 36 21} labelsize 10
          }*/
				//setpattern(value);
				//break;
			//case 10:
			0,5,
			/*MenuItem {} {
            label 1
            xywh {87 87 36 21} labelsize 10
          }
          MenuItem {} {
            label {1/2}
            xywh {87 87 36 21} labelsize 10
          }
          MenuItem {} {
            label {1/3}
            xywh {87 87 36 21} labelsize 10
          }
          MenuItem {} {
            label {1/4}
            xywh {97 97 36 21} labelsize 10
          }
          MenuItem {} {
            label {1/5}
            xywh {107 107 36 21} labelsize 10
          }
          MenuItem {} {
            label {1/6}
            xywh {127 127 36 21} labelsize 10
          }*/
				//Psubdiv = value;
				//subdiv = Psubdiv+1;
				//setdelay (Pdelay);
				//break;


		};
		int ArpiePrint[] = {
			-64,63, // 0
			-64,63, // 1
			1,600, // 2
			0,127, // 3
			-64,63, // 4
			0,127, // 5
			0,127,
			0,127,
			1,8,
			0,5,
			0,5,
		};
		int *real = ArpieReal;
		int *print = ArpiePrint;
		vector<string> presetTexts;
		presetTexts.push_back("Arpie 1");
		presetTexts.push_back("Arpie 2");
		presetTexts.push_back("Arpie 3");
		presetTexts.push_back("Simple Arpie");
		presetTexts.push_back("Canyon");
		presetTexts.push_back("Panning Arpie 1");
		presetTexts.push_back("Panning Arpie 2");
		presetTexts.push_back("Panning Arpie 3");
		presetTexts.push_back("Feedback Arpie");
		mPanels[whereis] = new PanelNS::Panel(mGUI, (VstPlugin*)effect, ((VstPlugin*)effect)->mEffArpie, "Arpie", whereis, arppresets, arpPRESET_SIZE, arpNUM_PRESETS, presetTexts);
		int iii=0;
		mPanels[whereis]->AddParamData(PanelNS::Data(iii, real[iii*2], real[iii*2+1], print[iii*2], print[iii*2+1], "Wet/Dry", PanelNS::Slider));
		iii=7;
		mPanels[whereis]->AddParamData(PanelNS::Data(iii, real[iii*2], real[iii*2+1], print[iii*2], print[iii*2+1], "Arpe's", PanelNS::Slider));
		iii=1;
		mPanels[whereis]->AddParamData(PanelNS::Data(iii, real[iii*2], real[iii*2+1], print[iii*2], print[iii*2+1], "Pan", PanelNS::Slider));
		iii=2;
		mPanels[whereis]->AddParamData(PanelNS::Data(iii, real[iii*2], real[iii*2+1], print[iii*2], print[iii*2+1], "Tempo", PanelNS::Slider));
		vector<string> mTypeStrs;
		mTypeStrs.push_back("1");
		mTypeStrs.push_back("1/2");
		mTypeStrs.push_back("1/3");
		mTypeStrs.push_back("1/4");
		mTypeStrs.push_back("1/5");
		mTypeStrs.push_back("1/6");
		iii=10;
		mPanels[whereis]->AddParamData(PanelNS::Data(iii, real[iii*2], real[iii*2+1], print[iii*2], print[iii*2+1],  "Subdivision", PanelNS::Selection, false, false, mTypeStrs));
		iii=3;
		mPanels[whereis]->AddParamData(PanelNS::Data(iii, real[iii*2], real[iii*2+1], print[iii*2], print[iii*2+1], "LRdl.", PanelNS::Slider));
		iii=4;
		mPanels[whereis]->AddParamData(PanelNS::Data(iii, real[iii*2], real[iii*2+1], print[iii*2], print[iii*2+1], "L/R.Cr", PanelNS::Slider));
		iii=5;
		mPanels[whereis]->AddParamData(PanelNS::Data(iii, real[iii*2], real[iii*2+1], print[iii*2], print[iii*2+1], "Fb", PanelNS::Slider));
		iii=8;
		mPanels[whereis]->AddParamData(PanelNS::Data(iii, real[iii*2], real[iii*2+1], print[iii*2], print[iii*2+1], "H", PanelNS::Slider));
		mTypeStrs.clear();
		mTypeStrs.push_back("Ascending");
        mTypeStrs.push_back("Descending");
        mTypeStrs.push_back("UpDown");
        mTypeStrs.push_back("Stutter");
        mTypeStrs.push_back("Interrupted Descent");
        mTypeStrs.push_back("Double Descend");
		iii=9;
		mPanels[whereis]->AddParamData(PanelNS::Data(iii, real[iii*2], real[iii*2+1], print[iii*2], print[iii*2+1],  "Pattern", PanelNS::Selection, false, false, mTypeStrs));
		iii=6;
		mPanels[whereis]->AddParamData(PanelNS::Data(iii, real[iii*2], real[iii*2+1], print[iii*2], print[iii*2+1], "Damp", PanelNS::Slider));
		if(loadPrev)
			mPanels[whereis]->LoadPreset(prevIdx);
		else
			mPanels[whereis]->SetPreset(0);

}
void ExampleEditor::CreateEchotron(int whereis, bool loadPrev, int prevIdx)
{
		const int etronPRESET_SIZE = 16;
		const int etronNUM_PRESETS = 5;
		int etronpresets[16*5] = {
			//Summer
			64, 45, 34, 4, 0,   76, 3, 41, 0, 96,   -13, 64, 1, 1, 1,   1,
			//Ambience
			96, 64, 16, 4, 0, 180, 50, 64, 1, 96, -4, 64, 1, 0, 0, 0,
			//Arranjer
			64, 64, 10, 4, 0, 400, 32, 64, 1, 96, -8, 64, 1, 0, 0, 0,
			//Suction
			0, 47, 28, 8, 0, 92, 0, 64, 3, 32, 0, 64, 1, 1, 1, 1,
			//SucFlange
			64, 36, 93, 8, 0, 81, 0, 64, 3, 32, 0, 64, 1, 0, 1, 1,

		};
		int EchotronReal[16*2] = {
			//case 0:
			0,128,
				//setvolume (value);
				//break;
			//case 1:
			0,127,
				//Pdepth=value;
				//initparams=1;
				//break;
			//case 2:
			0,127,
				//Pwidth=value;
				//initparams=1;
				//break;
			//case 3:
			1,127,
				//Plength = value;
				//if(Plength>127) Plength = 127;
				//initparams=1;
				//break;
			//case 4:
			0,1,
				//Puser = value;
				//break;
			//case 5:
			1,600,
				//Ptempo = value;

				//tmptempo = (float) Ptempo;
				//tempo_coeff = 60.0f / tmptempo;
				//lfo.Pfreq = lrintf(subdiv_fmod*tmptempo);
				//dlfo.Pfreq = lrintf(subdiv_dmod*tmptempo);
				//lfo.updateparams ();
				//initparams=1;
				//break;
			//case 6:
			0,127,
				//sethidamp (value);
				//break;
			//case 7:
			0,128,
				//Plrcross = value;
				//lrcross = ((float)(Plrcross)-64)/64.0;
				//ilrcross = 1.0f - abs(lrcross);
				//break;
			//case 8:
			0,1,
				///*if(!setfile(value)) {
					//error_num=4;
					//MessageBox(NULL, "Could not find Echotron dly files.", "Error", MB_OK);
				//}*/
				//break;
			//case 9:
			0,127,
				//lfo.Pstereo = value;
				//dlfo.Pstereo = value;
				//lfo.updateparams ();
				//dlfo.updateparams ();
				//break;
			//case 10:
			-64,64,
				//Pfb = value;
				//setfb(value);
				//break;
			//case 11:
			0,127,
				//setpanning (value);
				//break;
			//case 12:
			0,1,
				//Pmoddly = value;//delay modulation on/off
				//break;
			//case 13:
			0,1,
				//Pmodfilts = value;//filter modulation on/off
				//if(!Pmodfilts) initparams=1;
				//break;
			//case 14:
			0,9,
				////LFO Type
				//lfo.PLFOtype = value;
				//lfo.updateparams ();
				//dlfo.PLFOtype = value;
				//dlfo.updateparams ();
				//break;
			//case 15:
			0,1,
				//Pfilters = value;//Pfilters
				//break;


		};
		int EchotronPrint[16*2] = {
			-64,64,
			-64,63,
			0,127, // 2
			1,127,
			0,1, // 4
			1,600,
			0,127,
			-64,64,
			0,1,
			0,127,
			-64,64,
			-64,63,
			0,1,
			0,1, // 13
			0,9,
			0,1,
		};
		int *real = EchotronReal;
		int *print = EchotronPrint;
		vector<string> presetTexts;
		int iii;
		presetTexts.push_back("Summer");
		presetTexts.push_back("Ambience");
		presetTexts.push_back("Arranjer");
		presetTexts.push_back("Suction");
		presetTexts.push_back("SucFlange");
		mPanels[whereis] = new PanelNS::Panel(mGUI, (VstPlugin*)effect, ((VstPlugin*)effect)->mEffEchotron, "Echotron", whereis, etronpresets, etronPRESET_SIZE, etronNUM_PRESETS, presetTexts);
		
		iii=0;
		mPanels[whereis]->AddParamData(PanelNS::Data(iii, real[iii*2], real[iii*2+1], print[iii*2], print[iii*2+1], "Wet/Dry", PanelNS::Slider));
		iii=11;
		mPanels[whereis]->AddParamData(PanelNS::Data(iii, real[iii*2], real[iii*2+1], print[iii*2], print[iii*2+1], "Pan", PanelNS::Slider));
		iii=5;
		mPanels[whereis]->AddParamData(PanelNS::Data(iii, real[iii*2], real[iii*2+1], print[iii*2], print[iii*2+1], "Tempo", PanelNS::Slider));
		iii=6;
		mPanels[whereis]->AddParamData(PanelNS::Data(iii, real[iii*2], real[iii*2+1], print[iii*2], print[iii*2+1], "Damp", PanelNS::Slider));
		iii=10;
		mPanels[whereis]->AddParamData(PanelNS::Data(iii, real[iii*2], real[iii*2+1], print[iii*2], print[iii*2+1], "Fb", PanelNS::Slider));
		iii=7;
		mPanels[whereis]->AddParamData(PanelNS::Data(iii, real[iii*2], real[iii*2+1], print[iii*2], print[iii*2+1], "L/R.Cr", PanelNS::Slider));
		iii=2;
		mPanels[whereis]->AddParamData(PanelNS::Data(iii, real[iii*2], real[iii*2+1], print[iii*2], print[iii*2+1], "Width", PanelNS::Slider));
		iii=1;
		mPanels[whereis]->AddParamData(PanelNS::Data(iii, real[iii*2], real[iii*2+1], print[iii*2], print[iii*2+1], "Depth", PanelNS::Slider));
		iii=9;
		mPanels[whereis]->AddParamData(PanelNS::Data(iii, real[iii*2], real[iii*2+1], print[iii*2], print[iii*2+1], "St.df", PanelNS::Slider));
		
		vector<string> lfoTypeStrs;
		lfoTypeStrs.push_back("Sine"); 
		lfoTypeStrs.push_back("Tri");
		lfoTypeStrs.push_back("RampUp");
		lfoTypeStrs.push_back("RampDn");
		lfoTypeStrs.push_back("ZigZag");
		lfoTypeStrs.push_back("M.Sqare");
		lfoTypeStrs.push_back("M.Saw");
		lfoTypeStrs.push_back("L.Fract");
		lfoTypeStrs.push_back("L.FractXY");
		lfoTypeStrs.push_back("S/H Rnd");
		iii=14;
		mPanels[whereis]->AddParamData(PanelNS::Data(iii, real[iii*2], real[iii*2+1], print[iii*2], print[iii*2+1],  "LFOType", PanelNS::Selection, false, false, lfoTypeStrs));
		
		iii=15;
		mPanels[whereis]->AddParamData(PanelNS::Data(iii, real[iii*2], real[iii*2+1], print[iii*2], print[iii*2+1], "AF", PanelNS::OnOff));
		iii=13;
		mPanels[whereis]->AddParamData(PanelNS::Data(iii, real[iii*2], real[iii*2+1], print[iii*2], print[iii*2+1], "MF", PanelNS::OnOff));
		iii=12;
		mPanels[whereis]->AddParamData(PanelNS::Data(iii, real[iii*2], real[iii*2+1], print[iii*2], print[iii*2+1], "MD", PanelNS::OnOff, false, true));		
		iii=3;
		mPanels[whereis]->AddParamData(PanelNS::Data(iii, real[iii*2], real[iii*2+1], print[iii*2], print[iii*2+1], "#", PanelNS::Slider));
		
		iii=8;
		mPanels[whereis]->AddParamData(PanelNS::Data(iii, real[iii*2], real[iii*2+1], print[iii*2], print[iii*2+1], "Browse", PanelNS::Browser));
		
		if(loadPrev)
			mPanels[whereis]->LoadPreset(prevIdx);
		else
			mPanels[whereis]->SetPreset(0);

}
void ExampleEditor::CreateConvolotron(int whereis, bool loadPrev, int prevIdx)
{
		const int convPRESET_SIZE = 11;
		const int convNUM_PRESETS = 4;
		int convpresets[11*4] = {
			//Convolotron 1
			67, 64, 1, 100, 0, 64, 30, 20, 0, 0, 0,
			//Convolotron 2
			67, 64, 1, 100, 0, 64, 30, 20, 1, 0, 0,
			//Convolotron 3
			67, 75, 1, 100, 0, 64, 30, 20, 2, 0, 0,
			//Convolotron 4
			67, 60, 1, 100, 0, 64, 30, 20, 3, 0, 0
		};

		int ConvolotronReal[11*2] = {
			//case 0:
			0,128,
				//setvolume (value);
				//break;
			//case 1:
			0,127,
				//setpanning (value);
				//break;
			//case 2:
			0,1,
				//Psafe = value;
				//UpdateLength();
				//break;
			//case 3:
			5,250,
				//Plength = value;
				//UpdateLength();
				//break;
			//case 4:
			0,1,
				//Puser = value;
				//break;
			//case 5:
			0,1,
				//break;
			//case 6:
			0,127,
				//sethidamp (value);
				//break;
			//case 7:
			0,127,
				//Plevel = value;
				//level =  dB2rap (60.0f * (float)Plevel / 127.0f - 40.0f);
				//levpanl=lpanning*level*2.0f;
				//levpanr=rpanning*level*2.0f;
				//break;
			//case 8:
			0,1,
				////if(!setfile(value)) error_num=1;
				////UpdateLength();
				//break;
			//case 9:
			0,1,
				//break;
			//case 10:
			-64,64,
				//Pfb = value;
				//if(Pfb<0) {
					//fb = (float) .1f*value/250.0f*.15f;
				//} else {
					//fb = (float) .1f*value/500.0f*.15f;
				//}
				//break;


		};
		int ConvolotronPrint[11*2] = {
			-64,64, // 0
			-64,63,
			0,1, // 2
			5,250, 
			0,1, // 4
			0,1,
			0,127, // 6
			0,127,
			0,1, // 8
			0,1,
			-64,64,
		};
		int *real = ConvolotronReal;
		int *print = ConvolotronPrint;
		vector<string> presetTexts;
		presetTexts.push_back("Convolotron 1");
		presetTexts.push_back("Convolotron 2");
		presetTexts.push_back("Convolotron 3");
		presetTexts.push_back("Convolotron 4");
		int iii;
		mPanels[whereis] = new PanelNS::Panel(mGUI, (VstPlugin*)effect, ((VstPlugin*)effect)->mEffConvolotron, "Convolotron", whereis, convpresets, convPRESET_SIZE, convNUM_PRESETS, presetTexts);
		iii=0;
		mPanels[whereis]->AddParamData(PanelNS::Data(iii, real[iii*2], real[iii*2+1], print[iii*2], print[iii*2+1], "Wet/Dry", PanelNS::Slider));
		iii=1;
		mPanels[whereis]->AddParamData(PanelNS::Data(iii, real[iii*2], real[iii*2+1], print[iii*2], print[iii*2+1], "Pan", PanelNS::Slider));
		iii=7;
		mPanels[whereis]->AddParamData(PanelNS::Data(iii, real[iii*2], real[iii*2+1], print[iii*2], print[iii*2+1], "Level", PanelNS::Slider));
		iii=6;
		mPanels[whereis]->AddParamData(PanelNS::Data(iii, real[iii*2], real[iii*2+1], print[iii*2], print[iii*2+1], "Damp", PanelNS::Slider));
		iii=10;
		mPanels[whereis]->AddParamData(PanelNS::Data(iii, real[iii*2], real[iii*2+1], print[iii*2], print[iii*2+1], "Fb", PanelNS::Slider));
		iii=3;
		mPanels[whereis]->AddParamData(PanelNS::Data(iii, real[iii*2], real[iii*2+1], print[iii*2], print[iii*2+1], "Length", PanelNS::Slider));
		iii=2;
		mPanels[whereis]->AddParamData(PanelNS::Data(iii, real[iii*2], real[iii*2+1], print[iii*2], print[iii*2+1], "Safe Mode", PanelNS::OnOff));
		iii=8;
		mPanels[whereis]->AddParamData(PanelNS::Data(iii, real[iii*2], real[iii*2+1], print[iii*2], print[iii*2+1], "Browse", PanelNS::Browser));
		
		if(loadPrev)
			mPanels[whereis]->LoadPreset(prevIdx);
		else
			mPanels[whereis]->SetPreset(0);

}
void ExampleEditor::CreateRyanWah(int whereis, bool loadPrev, int prevIdx)
{
		const int ryanPRESET_SIZE = 19;
		const int ryanNUM_PRESETS = 6;
		int ryanpresets[] = {
			//Wah Pedal
			16, 10, 60, 0, 0, 64, 0, 0, 10, 7, -16, 40, -3, 1, 2000, 450, 1, 1, 0,
			//Mutron
			0, 15, 138, 0, 0, 64, 0, 50, 0, 30, 32, 0, 5, 1, 2000, 60, 0, 1, 1,
			//Phase Wah
			0, 50, 60, 0, 0, 64, 30, 10, 10, 30, 32, 0, 10, 2, 2000, 350, 1, 1, 2,
			//Succulent Phaser
			64, 8, 35, 10, 0, 64, 50, -10, 53, 35, 28, -16, 32, 4, 2600, 300, 1, 1, 3,
			//Quacky
			16, 10, 60, 0, 0, 64, 0, 40, 10, 32, -16, 40, -3, 1, 2000, 400, 1, 1, 4,
			//Smoothtron
			0, 15, 138, 0, 0, 64, 0, 15, 0, 20, 32, 0, 5, 1, 2000, 60, 0, 3, 5

		};

		int RyanReal[] = {
			//case 0:
			0,127,
				//setvolume (value);
				//break;
			//case 1:
			1,127,
				//Pq = value;
				//q = (float) Pq;
				//break;
			//case 2:
			1,600,
				//lfo.Pfreq = value;
				//lfo.updateparams ();
				//break;
			//case 3:
			0,127,
				//lfo.Prandomness = 0;//value;
				//lfo.updateparams ();
				//break;
			//case 4:
			0,9,
				//lfo.PLFOtype = value;
				//lfo.updateparams ();
				//break;
			//case 5:
			0,127,
				//lfo.Pstereo = value;
				//lfo.updateparams ();
				//break;
			//case 6:
			0,127,
				//setwidth (value);
				//break;
			//case 7:
			-64,64,
				//setampsns (value);
				//break;
			//case 8:
			0,127,
				//Pampsnsinv = value;
				//setampsns (Pampsns);
				//break;
			//case 9:
			0,127,
				//Pampsmooth = value;
				//setampsns (Pampsns);
				//break;
			//case 10:
			-64,64,
				//Plp = value;
				//lpmix = ((float) Plp)/32.0f;
				//reinitfilter ();
				//break;
			//case 11:
			-64,64,
				//Pbp = value;
				//bpmix = ((float) Pbp)/32.0f;
				//reinitfilter ();
				//break;
			//case 12:
			-64,64,
				//Php = value;
				//hpmix = ((float) Php)/32.0f;
				//reinitfilter ();
				//break;
			//case 13:
			1,12,
				//Pstages = (value - 1);
				//filterl->setstages(Pstages);
				//filterr->setstages(Pstages);
				//cleanup();
				//break;
			//case 14:
			10,6000,
				//Prange = value;
				//if(Pamode) maxfreq = ((float) Prange)/(fSAMPLE_RATE/6.0f);
				//else maxfreq = ((float) Prange);
				//break;
			//case 15:
			0,0,
				//Pminfreq = value;
				//if (Pamode)  minfreq = ((float) Pminfreq)/(fSAMPLE_RATE/6.0f);
				//else minfreq = (float) value;
				//break;
			//case 16:
			0,0,
				//variq = value;
				//break;
			//case 17:
			0,0,
				//Pmode=value;
				//if((Pmode==1) || (Pmode==3)) Pqm = 1;
				//else Pqm = 0;
				//filterl->setmode(Pqm);
				//filterr->setmode(Pqm);

				//if((Pmode==2) || (Pmode==3)) Pamode = 1;
				//else Pamode = 0;
				//if(Pamode) {
					//minfreq = ((float) Pminfreq)/(fSAMPLE_RATE/6.0f);
					//maxfreq = ((float) Prange)/(fSAMPLE_RATE/6.0f);
				//} else {
					//minfreq = (float) Pminfreq;
					//maxfreq = (float) Prange;
				//}

				//break;
			//case 18:
			0,0,
				//Ppreset = value;
				//break;


		};
		int RyanPrint[] = {
			-64,63,
			1,127,
			1,600, // 2
			0,127,
			0,9, // 4
			0,127,
			0,127, // 6
			-64,64,
			0,127, // 8
			0,127, 
			-64,64, // 10
			-64,64,
			-64,64, // 12
			1,12,
			10,6000, // 14
			0,127,
			0,0, // 16
			0,0,
			0,0, // 18
		};

		int *real = RyanReal;
		int *print = RyanPrint;
		vector<string> presetTexts;
		presetTexts.push_back("Wah Pedal");
		presetTexts.push_back("Mutron");
		presetTexts.push_back("Phase Wah");
		presetTexts.push_back("Succulent Phaser");
		presetTexts.push_back("Quacky");
		presetTexts.push_back("Smoothtron");
		mPanels[whereis] = new PanelNS::Panel(mGUI, (VstPlugin*)effect, ((VstPlugin*)effect)->mEffRyanWah, "MutroMojo", whereis, ryanpresets, ryanPRESET_SIZE, ryanNUM_PRESETS, presetTexts);
		int iii=0;
		mPanels[whereis]->AddParamData(PanelNS::Data(iii, real[iii*2], real[iii*2+1], print[iii*2], print[iii*2+1], "Wet/Dry", PanelNS::Slider));
		iii=10;
		mPanels[whereis]->AddParamData(PanelNS::Data(iii, real[iii*2], real[iii*2+1], print[iii*2], print[iii*2+1], "LP", PanelNS::Slider));
		iii=11;
		mPanels[whereis]->AddParamData(PanelNS::Data(iii, real[iii*2], real[iii*2+1], print[iii*2], print[iii*2+1], "BP", PanelNS::Slider));
		iii=12;
		mPanels[whereis]->AddParamData(PanelNS::Data(iii, real[iii*2], real[iii*2+1], print[iii*2], print[iii*2+1], "HP", PanelNS::Slider));
		iii=13;
		mPanels[whereis]->AddParamData(PanelNS::Data(iii, real[iii*2], real[iii*2+1], print[iii*2], print[iii*2+1], "Stg.", PanelNS::Slider));
		vector<string> lfoTypeStrs;
		lfoTypeStrs.push_back("Sine");
		lfoTypeStrs.push_back("Tri");
		lfoTypeStrs.push_back("RampUp");
		lfoTypeStrs.push_back("RampDn");
		lfoTypeStrs.push_back("ZigZag");
		lfoTypeStrs.push_back("M.Sqare");
		lfoTypeStrs.push_back("M.Saw");
		lfoTypeStrs.push_back("L.Fract");
		lfoTypeStrs.push_back("L.FractXY");
		lfoTypeStrs.push_back("S/H Rnd");
		iii=4;
		mPanels[whereis]->AddParamData(PanelNS::Data(iii, real[iii*2], real[iii*2+1], print[iii*2], print[iii*2+1],  "LFOType", PanelNS::Selection, false, false, lfoTypeStrs));
		iii=6;
		mPanels[whereis]->AddParamData(PanelNS::Data(iii, real[iii*2], real[iii*2+1], print[iii*2], print[iii*2+1], "Width", PanelNS::Slider));
		iii=2;
		mPanels[whereis]->AddParamData(PanelNS::Data(iii, real[iii*2], real[iii*2+1], print[iii*2], print[iii*2+1], "Tempo", PanelNS::Slider));
		iii=1;
		mPanels[whereis]->AddParamData(PanelNS::Data(iii, real[iii*2], real[iii*2+1], print[iii*2], print[iii*2+1], "Res.", PanelNS::Slider));
		iii=14;
		mPanels[whereis]->AddParamData(PanelNS::Data(iii, real[iii*2], real[iii*2+1], print[iii*2], print[iii*2+1], "Range", PanelNS::Slider));
		iii=8;
		mPanels[whereis]->AddParamData(PanelNS::Data(iii, real[iii*2], real[iii*2+1], print[iii*2], print[iii*2+1], "Wah", PanelNS::Slider));
		iii=7;
		mPanels[whereis]->AddParamData(PanelNS::Data(iii, real[iii*2], real[iii*2+1], print[iii*2], print[iii*2+1], "E.Sens", PanelNS::Slider));
		iii=9;
		mPanels[whereis]->AddParamData(PanelNS::Data(iii, real[iii*2], real[iii*2+1], print[iii*2], print[iii*2+1], "Smooth", PanelNS::Slider));
		if(loadPrev)
			mPanels[whereis]->LoadPreset(prevIdx);
		else
			mPanels[whereis]->SetPreset(0);

}
void ExampleEditor::CreateReverbtron(int whereis, bool loadPrev, int prevIdx)
{
		const int retronPRESET_SIZE = 16;
		const int retronNUM_PRESETS = 9;
		int retronpresets[16*9] = {
			//Spring
			64, 0, 1, 500, 0,  0, 99, 70, 0, 0,  0, 64, 0, 0, 20000,  0,
			//Concrete Stair
			64, 0, 1, 500, 0, 0, 0, 40, 1, 0, 0, 64, 0, 0, 20000, 0,
			//Nice Hall
			64, 0, 1, 500, 0, 0, 60, 15, 2, 0, 0, 64, 0, 0, 20000, 0,
			//Hall
			64, 16, 1, 500, 0, 0, 0, 22, 3, -17, 0, 64, 0, 0, 20000, 0,
			//Room
			64, 0, 1, 1500, 0, 0, 48, 20, 4, 0, 0, 64, 0, 0, 20000, 0,
			//Hall
			88, 0, 1, 1500, 0, 0, 88, 14, 5, 0, 0, 64, 0, 0, 20000, 0,
			//Guitar
			64, 0, 1, 1500, 0, 0, 30, 34, 6, 0, 0, 64, 0, 0, 20000, 0,
			//Studio
			64, 0, 1, 1500, 0, 0, 30, 20, 7, 0, 0, 64, 0, 0, 20000, 0,
			//Cathedral
			64, 0, 1, 1500, 0, 30, 0, 40, 9, 0, 0, 64, 0, 0, 20000, 0
		};
		int ReverbtronReal[16*2] = {
			//case 0:
			0,128,
				//setvolume (value);
				//break;
			//case 1:
			0,127,
				//Pfade=value;
				//ffade = ((float) value)/127.0f;
				//convert_time();
				//break;
			//case 2:
			0,1,
				//Psafe=value;
				//break;
			//case 3:
			20,1500,
				//Plength = value;
				//if((Psafe) && (Plength>400)) Plength = 400;
				//convert_time();
				//break;
			//case 4:
			0,1,
				//Puser = value;
				//break;
			//case 5:
			0,500,
				//Pidelay = value;
				//idelay = ((float) value)/1000.0f;
				//convert_time();
				//break;
			//case 6:
			0,127,
				//sethidamp (value);
				//break;
			//case 7:
			0,127,
				//Plevel = value;
				//level =  2.0f * dB2rap (60.0f * (float)Plevel / 127.0f - 40.0f);
				//levpanl=level*lpanning;
				//levpanr=level*rpanning;
				//break;
			//case 8:
			0,1,
				////if(!setfile(value)) error_num=2;
				//break;
			//case 9:
			-64,64,
				//Pstretch = value;
				//fstretch = ((float) value)/64.0f;
				//convert_time();
				//break;
			//case 10:
			-64,64,
				//Pfb = value;
				//setfb(value);
				//break;
			//case 11:
			0,128,
				//setpanning (value);
				//break;
			//case 12:
			0,1,
				//Pes = value;
				//break;
			//case 13:
			0,1,
				//Prv = value;
				//break;
			//case 14:
			47,171, // 20~26000, 이 값을 GetFreqByRealMinMax로 변환하면 주파수가 나온다.
				//setlpf (value);
				//break;
			//case 15:
			0,127,
				//Pdiff=value;
				//diffusion = ((float) value)/127.0f;
				//convert_time();
				//break;


		};
		int ReverbtronPrint[16*2] = {
			-64,64, // 0
			0,127,
			0,1, // 2
			20,1500, 
			0,1, // 4
			0,500,
			0,127, // 6
			0,127,
			0,1, // 8
			-64,64,
			-64,64, // 10
			-64,64,
			0,1, // 12
			0,1,
			0,100, // 14
			0,127,
		};
		int *real = ReverbtronReal;
		int *print = ReverbtronPrint;
		vector<string> presetTexts;
		presetTexts.push_back("Spring");
		presetTexts.push_back("Concrete Stair");
		presetTexts.push_back("Nice Hall");
		presetTexts.push_back("Hall");
		presetTexts.push_back("Room");
		presetTexts.push_back("Hall");
		presetTexts.push_back("Guitar");
		presetTexts.push_back("Studio");
		presetTexts.push_back("Cathedral");
		mPanels[whereis] = new PanelNS::Panel(mGUI, (VstPlugin*)effect, ((VstPlugin*)effect)->mEffReverbtron, "Reverbtron", whereis, retronpresets, retronPRESET_SIZE, retronNUM_PRESETS, presetTexts);
		int iii=0;
		mPanels[whereis]->AddParamData(PanelNS::Data(iii, real[iii*2], real[iii*2+1], print[iii*2], print[iii*2+1], "Wet/Dry", PanelNS::Slider));
		iii=11;
		mPanels[whereis]->AddParamData(PanelNS::Data(iii, real[iii*2], real[iii*2+1], print[iii*2], print[iii*2+1], "Pan", PanelNS::Slider));
		iii=7;
		mPanels[whereis]->AddParamData(PanelNS::Data(iii, real[iii*2], real[iii*2+1], print[iii*2], print[iii*2+1], "Level", PanelNS::Slider));
		iii=6;
		mPanels[whereis]->AddParamData(PanelNS::Data(iii, real[iii*2], real[iii*2+1], print[iii*2], print[iii*2+1], "Damp", PanelNS::Slider));
		iii=10;
		mPanels[whereis]->AddParamData(PanelNS::Data(iii, real[iii*2], real[iii*2+1], print[iii*2], print[iii*2+1], "Fb", PanelNS::Slider));
		iii=3;
		mPanels[whereis]->AddParamData(PanelNS::Data(iii, real[iii*2], real[iii*2+1], print[iii*2], print[iii*2+1], "Length", PanelNS::Slider));
		iii=9;
		mPanels[whereis]->AddParamData(PanelNS::Data(iii, real[iii*2], real[iii*2+1], print[iii*2], print[iii*2+1], "Stretch", PanelNS::Slider));
		iii=5;
		mPanels[whereis]->AddParamData(PanelNS::Data(iii, real[iii*2], real[iii*2+1], print[iii*2], print[iii*2+1], "I.Del", PanelNS::Slider));
		iii=1;
		mPanels[whereis]->AddParamData(PanelNS::Data(iii, real[iii*2], real[iii*2+1], print[iii*2], print[iii*2+1], "Fade", PanelNS::Slider));
		iii=15;
		mPanels[whereis]->AddParamData(PanelNS::Data(iii, real[iii*2], real[iii*2+1], print[iii*2], print[iii*2+1], "Diffusion", PanelNS::Slider));
		iii=14;
		mPanels[whereis]->AddParamData(PanelNS::Data(iii, real[iii*2], real[iii*2+1], print[iii*2], print[iii*2+1], "LPF", PanelNS::Slider, true));

		iii=2;
		mPanels[whereis]->AddParamData(PanelNS::Data(iii, real[iii*2], real[iii*2+1], print[iii*2], print[iii*2+1], "Safe Mode", PanelNS::OnOff));
		iii=13;
		mPanels[whereis]->AddParamData(PanelNS::Data(iii, real[iii*2], real[iii*2+1], print[iii*2], print[iii*2+1], "Sh", PanelNS::OnOff));
		iii=12;
		mPanels[whereis]->AddParamData(PanelNS::Data(iii, real[iii*2], real[iii*2+1], print[iii*2], print[iii*2+1], "ES", PanelNS::OnOff, false, true));

		iii=8;
		mPanels[whereis]->AddParamData(PanelNS::Data(iii, real[iii*2], real[iii*2+1], print[iii*2], print[iii*2+1], "Browse", PanelNS::Browser));
		if(loadPrev)
			mPanels[whereis]->LoadPreset(prevIdx);
		else
			mPanels[whereis]->SetPreset(0);

}

void ExampleEditor::CreateRBEcho(int whereis, bool loadPrev, int prevIdx)

{
		const int rbechoPRESET_SIZE = 10;
		const int rbechoNUM_PRESETS = 3;
		int rbechopresets[rbechoNUM_PRESETS*rbechoPRESET_SIZE] = {
			//Echo 1
			64, 64, 90, 64, 64, 64, 64, 0, 1, 96,
			//Echo 2
			64, 64, 90, 64, 64, 64, 64, 0, 2 ,96,
			//Echo 3
			64, 64, 90, 64, 64, 64, 64, 0, 3 ,96
		};
		int RBEchoReal[] = {
			//case 0:
			0,127,
				//setvolume (value);
				//break;
			//case 1:
			0,127,
				//setpanning (value);
				//break;
			//case 2:
			1,600,
				//setdelay (value);
				//break;
			//case 3:
			0,127,
				//setlrdelay (value);
				//break;
			//case 4:
			0,128,
				//setlrcross (value);
				//break;
			//case 5:
			0,127,
				//setfb (value);
				//break;
			//case 6:
			0,127,
				//sethidamp (value);
				//break;
			//case 7:
			0,127,
				//setreverse (value);
				//break;
			//case 8:
			0,5,
			/*
				label 1
				label {1/2}
				label {1/3}
				label {1/4}
				label {1/5}
				label {1/6}
				*/

				//Psubdiv = value;
				//subdiv = 1.0f/((float)(value + 1));
				//delay = subdiv * fdelay;
				//initdelays ();
				//break;
			//case 9:
			0,127,
				//Pes = value;
				//pes = 8.0f * (float)Pes / 127.0f;
				//break;
		};
		int RBEchoPrint[] = {
			-64,63,
			-64,63,
			1,600,
			0,127,
			-64,64,
			0,127,
			0,127,
			0,127,
			0,5,
			0,127,
		};
		int *real = RBEchoReal;
		int *print = RBEchoPrint;
		vector<string> presetTexts;
		presetTexts.push_back("Echo 1");
		presetTexts.push_back("Echo 2");
		presetTexts.push_back("Echo 3");
		mPanels[whereis] = new PanelNS::Panel(mGUI, (VstPlugin*)effect, ((VstPlugin*)effect)->mEffRBEcho, "Echoverse", whereis, rbechopresets, rbechoPRESET_SIZE, rbechoNUM_PRESETS, presetTexts);
		int iii=0;
		mPanels[whereis]->AddParamData(PanelNS::Data(iii, real[iii*2], real[iii*2+1], print[iii*2], print[iii*2+1], "Wet/Dry", PanelNS::Slider));
		iii=7;
		mPanels[whereis]->AddParamData(PanelNS::Data(iii, real[iii*2], real[iii*2+1], print[iii*2], print[iii*2+1], "Reverse", PanelNS::Slider));
		iii=1;
		mPanels[whereis]->AddParamData(PanelNS::Data(iii, real[iii*2], real[iii*2+1], print[iii*2], print[iii*2+1], "Pan", PanelNS::Slider));
		iii=2;
		mPanels[whereis]->AddParamData(PanelNS::Data(iii, real[iii*2], real[iii*2+1], print[iii*2], print[iii*2+1], "Tempo", PanelNS::Slider));
		iii=3;
		mPanels[whereis]->AddParamData(PanelNS::Data(iii, real[iii*2], real[iii*2+1], print[iii*2], print[iii*2+1], "LRdl.", PanelNS::Slider));
		iii=5;
		mPanels[whereis]->AddParamData(PanelNS::Data(iii, real[iii*2], real[iii*2+1], print[iii*2], print[iii*2+1], "Fb.", PanelNS::Slider));
		vector<string> mTypeStrs;
		mTypeStrs.push_back("1");
		mTypeStrs.push_back("1/2");
		mTypeStrs.push_back("1/3");
		mTypeStrs.push_back("1/4");
		mTypeStrs.push_back("1/5");
		mTypeStrs.push_back("1/6");
		iii=8;
		mPanels[whereis]->AddParamData(PanelNS::Data(iii, real[iii*2], real[iii*2+1], print[iii*2], print[iii*2+1],  "Subdivision", PanelNS::Selection, false, false, mTypeStrs));
		iii=6;
		mPanels[whereis]->AddParamData(PanelNS::Data(iii, real[iii*2], real[iii*2+1], print[iii*2], print[iii*2+1], "Damp", PanelNS::Slider));
		iii=9;
		mPanels[whereis]->AddParamData(PanelNS::Data(iii, real[iii*2], real[iii*2+1], print[iii*2], print[iii*2+1], "E.S.", PanelNS::Slider));
		iii=4;
		mPanels[whereis]->AddParamData(PanelNS::Data(iii, real[iii*2], real[iii*2+1], print[iii*2], print[iii*2+1], "Angle", PanelNS::Slider));
		if(loadPrev)
			mPanels[whereis]->LoadPreset(prevIdx);
		else
			mPanels[whereis]->SetPreset(0);

}
void ExampleEditor::CreateCoilCrafter(int whereis, bool loadPrev, int prevIdx)
{
		const int coilPRESET_SIZE = 9;
		const int coilNUM_PRESETS = 2;
		int coilpresets[coilNUM_PRESETS*coilPRESET_SIZE] = {
			//H to S
			32, 6, 1, 3300, 16,  4400, 42, 20, 0,
			//S to H
			32, 1, 6, 4400, 42, 3300, 16, 20, 0,


		};
		int CoilReal[] = {
			//case 0:
			0,127,
				//setvolume (value);
				//break;
			//case 1:
			0,8,
			/*
            Off
            Fender Strat (old)
            Fender Strat (new)
            Squire Strat
            Fender Hambucker
            Gibson P90
            Gibson Standard
            Gibson Mini
            Gibson Super L6S
			*/
				//Ppo = value;
				//if (Ppo>0) {
					//freq1 = tfreqs[value];
					//Pfreq1 = (int)freq1;
					//setfreq1();
					//q1 = tqs[value];
					//Pq1 = (int)(q1*10.0f);
					//setq1();
				//}
				//break;
			//case 2:
			0,8,
				//Ppd = value;
				//if(Ppd>0) {
					//freq2 = tfreqs[value];
					//Pfreq2 = (int)freq2;
					//setfreq2();
					//q2 = tqs[value];
					//Pq2 =(int)(q2*10.0f);
					//setq2();
				//}
				//break;
			//case 3:
			2600,4500,
				//Pfreq1 = value;
				//freq1 = (float) value;
				//setfreq1();
				//break;
			//case 4:
			10,65,
				//Pq1 = value;
				//q1 = (float)value/10.0f;
				//setq1();
				//break;
			//case 5:
			2600,4500,
				//Pfreq2 = value;
				//freq2 = (float) value;
				//setfreq2();
				//break;
			//case 6:
			10,65,
				//Pq2 = value;
				//q2 = (float)value/10.0f;
				//setq2();
				//break;
			//case 7:
			47,139, // 20~4400
				//Ptone = value;
				//sethpf(value);
				//break;
			//case 8:
			0,1,
				//Pmode = value;
				//break;


		};
		int CoilPrint[] = {
			0,127,
			0,8,
			0,8,
			2600,4500,
			10,65,
			2600,4500,
			10,65,
			0,100,
			0,1,
		};
		int *real = CoilReal;
		int *print = CoilPrint;
		vector<string> presetTexts;
		presetTexts.push_back("H to S");
		presetTexts.push_back("S to H");
		mPanels[whereis] = new PanelNS::Panel(mGUI, (VstPlugin*)effect, ((VstPlugin*)effect)->mEffCoil, "CoilCrafter", whereis, coilpresets, coilPRESET_SIZE, coilNUM_PRESETS, presetTexts);
		int iii=0;
		mPanels[whereis]->AddParamData(PanelNS::Data(iii, real[iii*2], real[iii*2+1], print[iii*2], print[iii*2+1], "Gain", PanelNS::Slider));
		iii=7;
		mPanels[whereis]->AddParamData(PanelNS::Data(iii, real[iii*2], real[iii*2+1], print[iii*2], print[iii*2+1], "Tone", PanelNS::Slider, true));
		vector<string> typeStrs;
        typeStrs.push_back("Off");
        typeStrs.push_back("Fender Strat (old)");
        typeStrs.push_back("Fender Strat (new)");
        typeStrs.push_back("Squire Strat");
        typeStrs.push_back("Fender Hambucker");
        typeStrs.push_back("Gibson P90");
        typeStrs.push_back("Gibson Standard");
        typeStrs.push_back("Gibson Mini");
        typeStrs.push_back("Gibson Super L6S");
		iii=1;
		mPanels[whereis]->AddParamData(PanelNS::Data(iii, real[iii*2], real[iii*2+1], print[iii*2], print[iii*2+1],  "Origin", PanelNS::Selection, false, false, typeStrs));
		iii=3;
		mPanels[whereis]->AddParamData(PanelNS::Data(iii, real[iii*2], real[iii*2+1], print[iii*2], print[iii*2+1], "Tone", PanelNS::Slider));
		iii=4;
		mPanels[whereis]->AddParamData(PanelNS::Data(iii, real[iii*2], real[iii*2+1], print[iii*2], print[iii*2+1], "Tone", PanelNS::Slider));
		iii=2;
		mPanels[whereis]->AddParamData(PanelNS::Data(iii, real[iii*2], real[iii*2+1], print[iii*2], print[iii*2+1],  "Destiny", PanelNS::Selection, false, false, typeStrs));
		iii=5;
		mPanels[whereis]->AddParamData(PanelNS::Data(iii, real[iii*2], real[iii*2+1], print[iii*2], print[iii*2+1], "Tone", PanelNS::Slider));
		iii=6;
		mPanels[whereis]->AddParamData(PanelNS::Data(iii, real[iii*2], real[iii*2+1], print[iii*2], print[iii*2+1], "Tone", PanelNS::Slider));
		iii=8;
		mPanels[whereis]->AddParamData(PanelNS::Data(iii, real[iii*2], real[iii*2+1], print[iii*2], print[iii*2+1], "Pos.", PanelNS::OnOff));
		if(loadPrev)
			mPanels[whereis]->LoadPreset(prevIdx);
		else
			mPanels[whereis]->SetPreset(0);

}