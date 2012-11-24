//	VstPlugin.cpp - Definition of the plugin class.
//	--------------------------------------------------------------------------
//	Copyright (c) 2005-2006 Niall Moody
//
//	Permission is hereby granted, free of charge, to any person obtaining a
//	copy of this software and associated documentation files (the "Software"),
//	to deal in the Software without restriction, including without limitation
//	the rights to use, copy, modify, merge, publish, distribute, sublicense,
//	and/or sell copies of the Software, and to permit persons to whom the
//	Software is furnished to do so, subject to the following conditions:
//
//	The above copyright notice and this permission notice shall be included in
//	all copies or substantial portions of the Software.
//
//	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//	IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//	FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
//	THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//	LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
//	FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
//	DEALINGS IN THE SOFTWARE.
//	--------------------------------------------------------------------------

#include "VstPlugin.h"
#include "ExampleEditor.h"
#include "../guitareffectVST/paramsMinMax.h"
#include "../guitareffectVST/DistorsionPanel.h"
#include "../guitareffectVST/LinealEQ.h"
#include "../guitareffectVST/CompressorPanel.h"
#include "../guitareffectVST/EchoPanel.h"
#include "../guitareffectVST/Panel.h"

#include "../guitareffectVST/paramsMinMax.h"
#include <string>
#include <algorithm>
#include <vector>
using namespace std;

//----------------------------------------------------------------------------
AudioEffect* createEffectInstance (audioMasterCallback audioMaster)
{
	return new VstPlugin(audioMaster);
}

//----------------------------------------------------------------------------

void
VstPlugin::update_freqs(float val)
{
    int i;

    aFreq=val;
    freqs[0] = aFreq;
    lfreqs[0] = logf (freqs[0]);
    for (i = 1; i < 12; i++) {
        freqs[i] = freqs[i - 1] * D_NOTE;
        lfreqs[i] = lfreqs[i - 1] + LOG_D_NOTE;
    }

}




extern void* hInstance;
VstPlugin::VstPlugin(audioMasterCallback audioMaster):
AudioEffectX(audioMaster, numPrograms, numParameters),
programs(0),
samplerate(44100.0f),
tempo(120.0f),
tempEvents(0),
numEvents(0),
numPendingEvents(0),
frames(0),
effectName("guitareffectVST"),
vendorName("Jinju")
{
	// Setup RAKARRACK global vars
	mParam = new Parameters();
	mParam->fPERIOD = 32768.0f;
	mParam->PERIOD = 32768;
	SAMPLE_RATE = samplerate;
	fSAMPLE_RATE = samplerate;
	cSAMPLE_RATE = 1.0f / samplerate;
	aFreq = 440.0;
	update_freqs(aFreq);
	reconota = -1;
	error_num = 0;
	Wave_res_amount = 2;
	Wave_up_q = 4;
	Wave_down_q = 1;

	char buffer[260];
	GetModuleFileName((HMODULE)hInstance, buffer, sizeof(buffer));
	string a(buffer);
	int pos = a.find_last_of('\\');
	string b = a.substr(0, pos);
	b += "\\data";
	strcpy(DATADIR, b.c_str());

	// RAKARRACK effects
	mEffEcho = new Echo(mParam, nullptr, nullptr);
	mEffDistorsion = new Distorsion(mParam, nullptr, nullptr);
	mEffConvolotron = new Convolotron(mParam, nullptr, nullptr, 1, 4, 2);
	mEffAlienwah = new Alienwah(mParam, nullptr, nullptr);
	mEffAPhaser = new Analog_Phaser(mParam, nullptr, nullptr);
	mEffArpie = new Arpie(mParam, nullptr, nullptr);
	mEffChorus = new Chorus(mParam, nullptr, nullptr);
	mEffFlange = new Chorus(mParam, nullptr, nullptr);
	mEffCoil = new CoilCrafter(mParam, nullptr, nullptr);
	mEffCompBand = new CompBand(mParam, nullptr, nullptr);
	mEffCompressor = new Compressor(mParam, nullptr, nullptr);
	mEffDualFlange = new Dflange(mParam, nullptr, nullptr);
	mEffEchotron = new Echotron(mParam, nullptr, nullptr);
	mEffEQ1 = new EQ(mParam, nullptr, nullptr);
	mEffEQ2 = new EQ(mParam, nullptr, nullptr);
	mEffExciter = new Exciter(mParam, nullptr, nullptr);
	mEffExpander = new Expander(mParam, nullptr, nullptr);
	mEffGate = new Gate(mParam, nullptr, nullptr);
	mEffHarmonizer = new Harmonizer(mParam, nullptr, nullptr, 4, 1, 4, 2); // keep quality at 4 or 32, DS == 1 means 96000 and so on, leave uq dq at 4,2 for now
	mEffInfinity = new Infinity(mParam, nullptr, nullptr);
	mEffMBDist = new MBDist(mParam, nullptr, nullptr);
	mEffMBVvol = new MBVvol(mParam, nullptr, nullptr);
	mEffMusicDelay= new MusicDelay(mParam, nullptr, nullptr);
	mEffNewDist = new NewDist(mParam, nullptr, nullptr);
	mEffOpticalTrem = new Opticaltrem(mParam, nullptr, nullptr);
	mEffPan = new Pan(mParam, nullptr, nullptr);
	mEffPhaser = new Phaser(mParam, nullptr, nullptr);
	mEffRBEcho = new RBEcho(mParam, nullptr, nullptr);
	mEffReverb = new Reverb(mParam, nullptr, nullptr);
	mEffReverbtron = new Reverbtron(mParam, nullptr, nullptr, 1, 4, 2);
	mEffRing = new Ring(mParam, nullptr, nullptr);
	mEffRyanWah = new RyanWah(mParam, nullptr, nullptr);
	mEffSequence = new Sequence(mParam, nullptr, nullptr, 32, 1, 4, 2);
	mEffShelfBoost = new ShelfBoost(mParam, nullptr, nullptr);
	mEffShifter = new Shifter(mParam, nullptr, nullptr, 32, 1, 4, 2);
	mEffShuffle = new Shuffle(mParam, nullptr, nullptr);
	mEffStereoHarm = new StereoHarm(mParam, nullptr, nullptr, 32, 1, 4, 2);
	mEffStompBox = new StompBox(mParam, nullptr, nullptr);
	mEffSustainer = new Sustainer(mParam, nullptr, nullptr);
	mEffSynthfilter = new Synthfilter(mParam, nullptr, nullptr);
	mEffValve = new Valve(mParam, nullptr, nullptr);
	mEffVibe = new Vibe(mParam, nullptr, nullptr);
	mEffLimiter = new Compressor(mParam, nullptr, nullptr);
	mEffLimiter->Compressor_Change_Preset(0,3);
	mEffWahWah = new DynamicFilter(mParam, nullptr, nullptr);
	mEffWahWah->setpreset(0);
	//presets
	
	int preset[9] =  {62, 64, 456, 64, 100, 90, 55, 0, 0};
    for (int n = 0; n < 9; n++) 
        mEffEcho->changepar (n, preset[n]);
	int preset2[11] =  {84, 64, 35, 56, 40, 0, 0, 6703, 21, 0, 0};
    for (int n = 0; n < 11; n++)
        mEffDistorsion->changepar (n, preset2[n]);
	
	int preset3[11] = {67, 64, 1, 100, 0, 64, 30, 20, 0, 0, 0};
    for (int n = 0; n < 11; n++)
        mEffConvolotron->changepar (n, preset3[n]);
		
	int preset4[11] = {64, 64, 40, 0, 0, 62, 60, 105, 25, 0, 64};
	for (int n = 0; n < 11; n++)
		mEffAlienwah->changepar (n, preset4[n]);
		
	int preset5[13] = {64, 20, 1, 10, 1, 64, 110, 40, 12, 10, 0, 70, 1};
	for (int n = 0; n < 13; n++)
		mEffAPhaser->changepar (n, preset5[n]);
		
	int preset6[9] = {81, 60, 26, 100, 127, 67, 36, 0, 4};
	for (int n = 0; n < 9; n++)
		mEffArpie->changepar (n, preset6[n]);
	mEffArpie->changepar(9, 2);	
	mEffArpie->changepar(10, 1);
			
	int preset7[12] = {64, 64, 1, 0, 0, 42, 115, 18, 90, 127, 0, 0};
	for (int n = 0; n < 12; n++)
	{
		mEffChorus->changepar (n, preset7[n]);
		mEffFlange->changepar (n, preset7[n]);
	}

	int preset8[9] = {32, 6, 1, 3300, 16,  4400, 42, 20, 0};
	for (int n = 0; n < 9; n++)
		mEffCoil->changepar (n, preset8[n]);

	int preset9[13] = {0, 16, 2, 2, 4, -16, 24, 24, -8, 140, 1000, 5000, 48};
	for (int n = 0; n < 13; n++)
		mEffCompBand->changepar (n, preset9[n]);

	int preset10[10] = {-1, 15, 0, 5, 250, 0 ,0 ,1 ,1};
	for (int n = 0; n < 10; n++)
		mEffCompressor->Compressor_Change (n, preset10[n]);

	int preset11[15] = {0, 0, 64, 500, 3000, 50, -40, 8000, 1, 0, 196, 96, 0, 0, 0};
	for (int n = 0; n < 15; n++)
		mEffDualFlange->changepar (n, preset11[n]);
	
	int preset12[16] = {64, 45, 34, 4, 0, 76, 3, 41, 0, 96, -13, 64, 1, 1, 1, 1};
	for (int n = 0; n < 16; n++)
		mEffEchotron->changepar (n, preset12[n]);


    for (int i = 0; i <= 45; i += 5) {
        mEffEQ1->changepar (i + 10, 7); // type
        mEffEQ1->changepar (i + 14, 0); // stage
    }

    mEffEQ1->changepar (11, 31); // freqs
    mEffEQ1->changepar (16, 63);
    mEffEQ1->changepar (21, 125);
    mEffEQ1->changepar (26, 250);
    mEffEQ1->changepar (31, 500);
    mEffEQ1->changepar (36, 1000);
    mEffEQ1->changepar (41, 2000);
    mEffEQ1->changepar (46, 4000);
    mEffEQ1->changepar (51, 8000);
    mEffEQ1->changepar (56, 16000);

	for(int i=0; i<10; ++i)
	{
		mEffEQ1->changepar (i*5+12, 64); // gain
		mEffEQ1->changepar (i*5+13, 64); // q(resonance)
	}
	
    for (int i = 0; i <= 10; i += 5) {
		mEffEQ2->changepar (i + 12, 64); // gain
        mEffEQ2->changepar (i + 10, 7);
        mEffEQ2->changepar (i + 13, 64); // q
        mEffEQ2->changepar (i + 14, 0);

    }

	mEffExciter->setpreset(2);
	mEffExpander->Expander_Change_Preset(1);
	mEffGate->Gate_Change_Preset(2);
	mEffHarmonizer->setpreset(2);
	mEffInfinity->setpreset(5);
	mEffMBDist->setpreset(1);
	mEffMBVvol->setpreset(0);
	mEffMusicDelay->setpreset(0);
	mEffNewDist->setpreset(0);
	mEffOpticalTrem->setpreset(0);
	mEffPan->setpreset(0);
	mEffPhaser->setpreset(0);
	mEffRBEcho->setpreset(0);
	mEffReverb->setpreset(0);
	mEffReverbtron->setpreset(0);
	mEffRing->setpreset(1);
	mEffRyanWah->setpreset(1);
	mEffSequence->setpreset(0);
	mEffShelfBoost->setpreset(0);
	mEffShifter->setpreset(0);
	mEffShuffle->setpreset(0);
	mEffStereoHarm->setpreset(0);
	mEffStompBox->setpreset(0);
	mEffSustainer->setpreset(0);
	mEffSynthfilter->setpreset(0);
	mEffValve->setpreset(0);
	mEffVibe->setpreset(0);
	
	// originals
	int i;

	//Initialise parameters.
	for(i=0;i<numParameters;++i)
		parameters[i] = 0.0f;

	//Setup event queue.
	for(i=0;i<maxNumEvents;++i)
	{
		midiEvent[i] = new VstMidiEvent;

		midiEvent[i]->type = 1;
		midiEvent[i]->midiData[3] = 0;
		midiEvent[i]->reserved1 = 99;
		midiEvent[i]->deltaFrames = -99;
		midiEvent[i]->noteLength = 0;
		midiEvent[i]->noteOffset = 0;

		eventNumArray[i] = -1;
	}
	tempEvents = new VstEvents;
	tempEvents->numEvents = 1;
	tempEvents->events[0] = (VstEvent *)midiEvent[0];

	//Setup programs here.
	programs = new PluginProgram[numPrograms];
	setProgram(0);

	//Set various constants.
    setNumInputs(2); // 2in2out here
    setNumOutputs(2);
    canProcessReplacing(true);
    isSynth(false);
    setUniqueID('JinJ');
	programsAreChunks(true);

	//Construct editor here.
	
	mEditor = new ExampleEditor(this);
	editor = mEditor;
	//SetCurrentDirectory() 이건 호스트에서나 쓸 수 있다.
}

//----------------------------------------------------------------------------
VstPlugin::~VstPlugin()
{
	delete mEffEcho;
	delete mEffDistorsion;
	delete mEffConvolotron;
	delete mEffAlienwah;
	delete mEffAPhaser;
	delete mEffArpie;
	delete mEffChorus;
	delete mEffCoil;
	delete mEffCompressor;
	delete mEffDualFlange;
	delete mEffEchotron;
	delete mEffEQ1;
	delete mEffEQ2;
	delete mEffExciter;
	delete mEffExpander;
	delete mEffGate;
	delete mEffHarmonizer;
	delete mEffInfinity;
	delete mEffMBDist;
	delete mEffMBVvol;
	delete mEffMusicDelay;
	delete mEffNewDist;
	delete mEffOpticalTrem;
	delete mEffPan;
	delete mEffPhaser;
	delete mEffRBEcho;
	delete mEffReverb;
	delete mEffReverbtron;
	delete mEffRing;
	delete mEffRyanWah;
	delete mEffSequence;
	delete mEffShelfBoost;
	delete mEffShifter;
	delete mEffShuffle;
	delete mEffStereoHarm;
	delete mEffStompBox;
	delete mEffSustainer;
	delete mEffSynthfilter;
	delete mEffValve;
	delete mEffVibe;
	delete mEffWahWah;
	delete mParam;
	int i;

	//Delete event queue.
	for(i=0;i<maxNumEvents;++i)
	{
		if(midiEvent[i])
			delete midiEvent[i];
	}
	if(tempEvents)
		delete tempEvents;

	//Delete programs.
	if(programs)
		delete [] programs;
}

//----------------------------------------------------------------------------
void VstPlugin::process(float **inputs, float **outputs, VstInt32 sampleFrames)
{
	VstInt32 i;

	frames = sampleFrames;

	//Calculate audio.
	for(i=0;i<frames;++i)
	{
		//Process MIDI events,if there are any.
		if(numEvents>0)
			processMIDI(i);

		outputs[0][i] += inputs[0][i];
		outputs[1][i] += inputs[1][i];
	}
	//If there are events remaining in the queue, update their delta values.
	//mEffDistorsion->processReplacing(inputs, outputs, sampleFrames);
	if(numPendingEvents > 0)
	{
		for(i=0;i<numPendingEvents;++i)
			midiEvent[eventNumArray[i]]->deltaFrames -= frames;
	}
}

//----------------------------------------------------------------------------
void VstPlugin::processReplacing(float **inputs,
								 float **outputs,
								 VstInt32 sampleFrames)
{
	VstInt32 i;

	frames = sampleFrames;

	//Calculate audio.
	for(i=0;i<frames;++i)
	{
		//Process MIDI events,if there are any.
		if(numEvents>0)
			processMIDI(i);

		outputs[0][i] = inputs[0][i];
		outputs[1][i] = inputs[1][i];
	}
	//mEffDistorsion->processReplacing(outputs, outputs, sampleFrames);
	//mEffConvolotron->processReplacing(outputs, outputs, sampleFrames);
	//mEffAlienwah->processReplacing(outputs, outputs, sampleFrames);
	//mEffEcho->processReplacing(outputs, outputs, sampleFrames);
	//mEffAPhaser->processReplacing(outputs, outputs, sampleFrames);
	//mEffArpie->processReplacing(outputs, outputs, sampleFrames);
	//mEffChorus->processReplacing(outputs, outputs, sampleFrames);
	//mEffCoil->processReplacing(outputs, outputs, sampleFrames);
	//mEffCompBand->processReplacing(outputs, outputs, sampleFrames);
	//mEffCompressor->processReplacing(outputs, outputs, sampleFrames);
	//mEffDualFlange->processReplacing(outputs, outputs, sampleFrames);
	//mEffCompBand->processReplacing(outputs, outputs, sampleFrames);
	//mEffEchotron->processReplacing(outputs, outputs, sampleFrames);
	//mEffEQ1->processReplacing(outputs, outputs, sampleFrames);
	//mEffEQ2->processReplacing(outputs, outputs, sampleFrames);
	//mEffExciter->processReplacing(outputs, outputs, sampleFrames);
	//mEffExpander->processReplacing(outputs, outputs, sampleFrames);
	//mEffGate->processReplacing(outputs, outputs, sampleFrames);
	//mEffHarmonizer->processReplacing(outputs, outputs, sampleFrames);
	//mEffInfinity->processReplacing(outputs, outputs, sampleFrames);
	//mEffMBDist->processReplacing(outputs, outputs, sampleFrames);
	//mEffMBVvol->processReplacing(outputs, outputs, sampleFrames);
	//mEffMusicDelay->processReplacing(outputs, outputs, sampleFrames);
	//mEffNewDist->processReplacing(outputs, outputs, sampleFrames);
	//mEffOpticalTrem->processReplacing(outputs, outputs, sampleFrames);
	//mEffPan->processReplacing(outputs, outputs, sampleFrames);
	//mEffPhaser->processReplacing(outputs, outputs, sampleFrames);
	//mEffRBEcho->processReplacing(outputs, outputs, sampleFrames);
	//mEffReverb->processReplacing(outputs, outputs, sampleFrames);
	//mEffReverbtron->processReplacing(outputs, outputs, sampleFrames);
	//mEffRing->processReplacing(outputs, outputs, sampleFrames);
	//mEffRyanWah->processReplacing(outputs, outputs, sampleFrames);
	//mEffSequence->processReplacing(outputs, outputs, sampleFrames);
	//mEffShelfBoost->processReplacing(outputs, outputs, sampleFrames);
	//mEffShifter->processReplacing(outputs, outputs, sampleFrames);
	//mEffShuffle->processReplacing(outputs, outputs, sampleFrames);
	//mEffStereoHarm->processReplacing(outputs, outputs, sampleFrames);
	//mEffStompBox->processReplacing(outputs, outputs, sampleFrames);
	//mEffSustainer->processReplacing(outputs, outputs, sampleFrames);
	//mEffSynthfilter->processReplacing(outputs, outputs, sampleFrames);
	//mEffValve->processReplacing(outputs, outputs, sampleFrames);
	//mEffWahWah->processReplacing(outputs, outputs, sampleFrames);
	float *tempOutputs[2];
	tempOutputs[0] = new float[sampleFrames];
	tempOutputs[1] = new float[sampleFrames];
	float outVolume;

	/*
	outVolume = mEffVibe->outvolume;
	mEffVibe->processReplacing(outputs, tempOutputs, sampleFrames);
	for(int i=0; i<sampleFrames; ++i)
	{
		outputs[0][i] = outputs[0][i]*(1.0-outVolume) + tempOutputs[0][i]*outVolume;
		outputs[1][i] = outputs[1][i]*(1.0-outVolume) + tempOutputs[1][i]*outVolume;
	}
	*/
	/*
	outVolume = mEffDistorsion->outvolume;
	if(outVolume > 1.0f) outVolume = 1.0f;
	mEffDistorsion->processReplacing(outputs, tempOutputs, sampleFrames); // Type: WetDry
	for(int i=0; i<sampleFrames; ++i)
	{
		outputs[0][i] = outputs[0][i]*(1.0-outVolume) + tempOutputs[0][i]*outVolume;
		outputs[1][i] = outputs[1][i]*(1.0-outVolume) + tempOutputs[1][i]*outVolume;
	}

	outVolume = mEffEQ1->outvolume;
	mEffEQ1->processReplacing(outputs, tempOutputs, sampleFrames); // Type: Gain
	for(int i=0; i<sampleFrames; ++i)
	{
		outputs[0][i] = tempOutputs[0][i]*outVolume;
		outputs[1][i] = tempOutputs[1][i]*outVolume;
	}

	mEffCompressor->processReplacing(outputs, tempOutputs, sampleFrames); // Type: None
	for(int i=0; i<sampleFrames; ++i)
	{
		outputs[0][i] = tempOutputs[0][i];
		outputs[1][i] = tempOutputs[1][i];
	}

	outVolume = mEffEcho->outvolume;
	if(outVolume > 1.0f) outVolume = 1.0f;
	mEffEcho->processReplacing(outputs, tempOutputs, sampleFrames);
	for(int i=0; i<sampleFrames; ++i)
	{
		outputs[0][i] = outputs[0][i]*(1.0-outVolume) + tempOutputs[0][i]*outVolume;
		outputs[1][i] = outputs[1][i]*(1.0-outVolume) + tempOutputs[1][i]*outVolume;
	}
	*/
	/*
	outVolume = mEffChorus->outvolume;
	if(outVolume > 1.0f) outVolume = 1.0f;
	mEffChorus->processReplacing(outputs, tempOutputs, sampleFrames); // Type: WetDry
	for(int i=0; i<sampleFrames; ++i)
	{
		outputs[0][i] = outputs[0][i]*(1.0-outVolume) + tempOutputs[0][i]*outVolume;
		outputs[1][i] = outputs[1][i]*(1.0-outVolume) + tempOutputs[1][i]*outVolume;
	}

	outVolume = mEffPhaser->outvolume;
	if(outVolume > 1.0f) outVolume = 1.0f;
	mEffPhaser->processReplacing(outputs, tempOutputs, sampleFrames); // Type: WetDry
	for(int i=0; i<sampleFrames; ++i)
	{
		outputs[0][i] = outputs[0][i]*(1.0-outVolume) + tempOutputs[0][i]*outVolume;
		outputs[1][i] = outputs[1][i]*(1.0-outVolume) + tempOutputs[1][i]*outVolume;
	}

	outVolume = mEffReverb->outvolume;
	if(outVolume > 1.0f) outVolume = 1.0f;
	mEffReverb->processReplacing(outputs, tempOutputs, sampleFrames); // Type: WetDry
	for(int i=0; i<sampleFrames; ++i)
	{
		outputs[0][i] = outputs[0][i]*(1.0-outVolume) + tempOutputs[0][i]*outVolume;
		outputs[1][i] = outputs[1][i]*(1.0-outVolume) + tempOutputs[1][i]*outVolume;
	}


	mEffEQ2->processReplacing(outputs, tempOutputs, sampleFrames); // Type: None
	for(int i=0; i<sampleFrames; ++i)
	{
		outputs[0][i] = tempOutputs[0][i];
		outputs[1][i] = tempOutputs[1][i];
	}*/

	/*outVolume = mEffWahWah->outvolume;
	if(outVolume > 1.0f) outVolume = 1.0f;
	mEffWahWah->processReplacing(outputs, tempOutputs, sampleFrames); // Type: WetDry
	for(int i=0; i<sampleFrames; ++i)
	{
		outputs[0][i] = outputs[0][i]*(1.0-outVolume) + tempOutputs[0][i]*outVolume;
		outputs[1][i] = outputs[1][i]*(1.0-outVolume) + tempOutputs[1][i]*outVolume;
	}
	outVolume = mEffAlienwah->outvolume;
	if(outVolume > 1.0f) outVolume = 1.0f;
	mEffAlienwah->processReplacing(outputs, tempOutputs, sampleFrames); // Type: WetDry
	for(int i=0; i<sampleFrames; ++i)
	{
		outputs[0][i] = outputs[0][i]*(1.0-outVolume) + tempOutputs[0][i]*outVolume;
		outputs[1][i] = outputs[1][i]*(1.0-outVolume) + tempOutputs[1][i]*outVolume;
	}*/

	/*
	outVolume = mEffPan->outvolume;
	if(outVolume > 1.0f) outVolume = 1.0f;
	mEffPan->processReplacing(outputs, tempOutputs, sampleFrames); // Type: WetDry
	for(int i=0; i<sampleFrames; ++i)
	{
		outputs[0][i] = outputs[0][i]*(1.0-outVolume) + tempOutputs[0][i]*outVolume;
		outputs[1][i] = outputs[1][i]*(1.0-outVolume) + tempOutputs[1][i]*outVolume;
	}
	*/
	if(mEditor->mTotalEffectOn)
	{
		Effect *eff = nullptr;
		for(int i=0; i<10; ++i)
		{
			if(!mEditor->mEffectOn[i])
			{
				continue;
			}
			switch(mEditor->mBuiltPanels[i])
			{
			case EffEcho:
				eff = mEffEcho;
				break;
			case EffCompressor:
				eff = mEffCompressor;
				break;
			case EffLinealEQ:
				eff = mEffEQ1;
				break;
			case EffChorus:
				eff = mEffChorus;
				break;
			case EffPhaser:
				eff = mEffPhaser;
				break;
			case EffReverb:
				eff = mEffReverb;
				break;
			case EffParametricEQ:
				eff = mEffEQ2;
				break;
			case EffWahWah:
				eff = mEffWahWah;
				break;
			case EffAlienWah:
				eff = mEffAlienwah;
				break;
			case EffPan:
				eff = mEffPan;
				break;
			case EffDistortion:
				eff = mEffDistorsion;
				break;
			}
			if(eff->mType == WetDry)
			{
				outVolume = eff->outvolume;
				if(outVolume > 1.0f) outVolume = 1.0f;
				eff->processReplacing(outputs, tempOutputs, sampleFrames); // Type: WetDry
				for(int i=0; i<sampleFrames; ++i)
				{
					outputs[0][i] = outputs[0][i]*(1.0-outVolume) + tempOutputs[0][i]*outVolume;
					outputs[1][i] = outputs[1][i]*(1.0-outVolume) + tempOutputs[1][i]*outVolume;
				}
			}
			else if(eff->mType == Gain)
			{
				outVolume = eff->outvolume;
				eff->processReplacing(outputs, tempOutputs, sampleFrames); // Type: Gain
				for(int i=0; i<sampleFrames; ++i)
				{
					outputs[0][i] = tempOutputs[0][i]*outVolume;
					outputs[1][i] = tempOutputs[1][i]*outVolume;
				}
			}
			else if(eff->mType == None)
			{
				eff->processReplacing(outputs, tempOutputs, sampleFrames); // Type: None
				for(int i=0; i<sampleFrames; ++i)
				{
					outputs[0][i] = tempOutputs[0][i];
					outputs[1][i] = tempOutputs[1][i];
				}
			}
		}


		mEffLimiter->processReplacing(outputs, tempOutputs, sampleFrames); // Hidden Final Limiter Chain
		for(int i=0; i<sampleFrames; ++i)
		{
			outputs[0][i] = tempOutputs[0][i];
			outputs[1][i] = tempOutputs[1][i];
		}
	}
	delete tempOutputs[0];
	delete tempOutputs[1];


	//If there are events remaining in the queue, update their delta values.
	if(numPendingEvents > 0)
	{
		for(i=0;i<numPendingEvents;++i)
			midiEvent[eventNumArray[i]]->deltaFrames -= frames;
	}
}

//----------------------------------------------------------------------------
VstInt32 VstPlugin::processEvents(VstEvents *events)
{
	int i, j, k;
	VstMidiEvent *event;

	//Go through each event in events.
	for(i=0;i<events->numEvents;++i)
	{
		//Only interested in MIDI events.
		if(events->events[i]->type == kVstMidiType)
		{
			event = (VstMidiEvent *)events->events[i];
			j = -1;

			//Find a space for it in the midiEvent queue.
			for(k=1;k<maxNumEvents;++k)
			{
				if(midiEvent[k]->deltaFrames == -99)
				{
					eventNumArray[numPendingEvents] = k;
					++numPendingEvents;

					j = k;
					break;
				}
			}
			//Add it to the queue if there's still room.
			if((j > 0)&&(numEvents < maxNumEvents))
			{
				numEvents++;
				midiEvent[j]->midiData[0] =		event->midiData[0];
				midiEvent[j]->midiData[1] =		event->midiData[1];
				midiEvent[j]->midiData[2] =		event->midiData[2];
				midiEvent[j]->midiData[3] =		event->midiData[3];
				midiEvent[j]->type =			event->type;
				midiEvent[j]->byteSize =		event->byteSize;
				midiEvent[j]->deltaFrames =		event->deltaFrames;
				midiEvent[j]->flags =			event->flags;
				midiEvent[j]->noteLength =		event->noteLength;
				midiEvent[j]->noteOffset =		event->noteOffset;
				midiEvent[j]->detune =			event->detune;
				midiEvent[j]->noteOffVelocity = event->noteOffVelocity;
				midiEvent[j]->reserved1 =		99;
				midiEvent[j]->reserved2 =		event->reserved2;
			}
		}
	}

	return 1;
}

//----------------------------------------------------------------------------
void VstPlugin::resume()
{
	//Let old hosts know we want to receive MIDI events.
    AudioEffectX::resume();
}

//----------------------------------------------------------------------------
void VstPlugin::suspend()
{
    
}

//----------------------------------------------------------------------------
void VstPlugin::setProgram(VstInt32 program)
{
	int i;

	curProgram = program;

	for(i=0;i<numParameters;++i)
		setParameter(i, programs[curProgram].parameters[i]);
}

//----------------------------------------------------------------------------
void VstPlugin::setProgramName(char *name)
{
	programs[curProgram].name = name;
}


//----------------------------------------------------------------------------
void VstPlugin::getProgramName(char *name)
{
	strcpy(name, programs[curProgram].name.c_str());
}

//----------------------------------------------------------------------------
bool VstPlugin::getProgramNameIndexed(VstInt32 category, VstInt32 index, char* text)
{
	bool retval = false;

    if(index < numPrograms)
    {
		strcpy(text, programs[index].name.c_str());
		retval = true;
    }

	return retval;
}

//----------------------------------------------------------------------------
bool VstPlugin::copyProgram(VstInt32 destination)
{
	bool retval = false;

    if(destination < numPrograms)
    {
		programs[destination] = programs[curProgram];
        retval = true;
    }

    return retval;
}

//----------------------------------------------------------------------------
void VstPlugin::setParameter(VstInt32 index, float value)
{
	parameters[index] = value;
	programs[curProgram].parameters[index] = parameters[index];

	if(editor)
	{
		((VSTGLEditor *)editor)->setParameter(index, value);
	}
}

//----------------------------------------------------------------------------
float VstPlugin::getParameter(VstInt32 index)
{
	return parameters[index];
}

//----------------------------------------------------------------------------
void VstPlugin::getParameterLabel(VstInt32 index, char *label)
{
	strcpy(label, " ");
}

//----------------------------------------------------------------------------
void VstPlugin::getParameterDisplay(VstInt32 index, char *text)
{
	float2string(parameters[index], text, 7);
}

//----------------------------------------------------------------------------
void VstPlugin::getParameterName(VstInt32 index, char *label)
{
	char tempch[8];

	sprintf(tempch, "p%d", static_cast<int>(index));
	strcpy(label, tempch);
}

//----------------------------------------------------------------------------
VstInt32 VstPlugin::canDo(char *text)
{
	if(!strcmp(text, "sendVstEvents")) return 1;
	if(!strcmp(text, "sendVstMidiEvent")) return 1; //because the plugin acts as a MIDI through
	if(!strcmp(text, "sendVstTimeInfo")) return -1;
	if(!strcmp(text, "receiveVstEvents")) return 1;
	if(!strcmp(text, "receiveVstMidiEvent")) return 1;
	if(!strcmp(text, "receiveVstTimeInfo")) return 1;
	if(!strcmp(text, "offline")) return -1;
	if(!strcmp(text, "plugAsChannelInsert")) return -1;
	if(!strcmp(text, "plugAsSend")) return -1;
	if(!strcmp(text, "mixDryWet")) return -1;
	if(!strcmp(text, "noRealTime")) return -1;
	if(!strcmp(text, "multipass")) return -1;
	if(!strcmp(text, "metapass")) return -1;
	if(!strcmp(text, "1in1out")) return -1;
	if(!strcmp(text, "1in2out")) return -1;
	if(!strcmp(text, "2in1out")) return -1;
	if(!strcmp(text, "2in2out")) return -1;
	if(!strcmp(text, "2in4out")) return -1;
	if(!strcmp(text, "4in2out")) return -1;
	if(!strcmp(text, "4in4out")) return -1;
	if(!strcmp(text, "4in8out")) return -1;					// 4:2 matrix to surround bus
	if(!strcmp(text, "8in4out")) return -1;					// surround bus to 4:2 matrix
	if(!strcmp(text, "8in8out")) return -1;
	if(!strcmp(text, "midiProgramNames")) return -1;
	if(!strcmp(text, "conformsToWindowRules") ) return -1;	// mac: doesn't mess with grafport. general: may want
															// to call sizeWindow (). if you want to use sizeWindow (),
															// you must return true (1) in canDo ("conformsToWindowRules")
	if(!strcmp(text, "bypass")) return -1;

	return -1;
}

//----------------------------------------------------------------------------
float VstPlugin::getVu()
{
	return 0.0f;
}

//----------------------------------------------------------------------------
bool VstPlugin::getEffectName(char* name)
{
    strcpy(name, effectName.c_str());

    return true;
}

//----------------------------------------------------------------------------
bool VstPlugin::getVendorString(char* text)
{
    strcpy(text, vendorName.c_str());

    return true;
}

//----------------------------------------------------------------------------
bool VstPlugin::getProductString(char* text)
{
    strcpy(text, effectName.c_str());

    return true;
}

//----------------------------------------------------------------------------
VstInt32 VstPlugin::getVendorVersion()
{
    return versionNumber;
}

//----------------------------------------------------------------------------
VstPlugCategory VstPlugin::getPlugCategory()
{
    return(kPlugCategEffect);
}

//----------------------------------------------------------------------------
bool VstPlugin::getInputProperties(VstInt32 index, VstPinProperties* properties)
{
	bool retval = false;

	if(index == 0)
	{
		sprintf(properties->label, "%s Left Input 1", effectName.c_str());
		properties->flags = kVstPinIsStereo|kVstPinIsActive;
		retval = true;
	}
	else if(index == 1)
	{
		sprintf(properties->label, "%s Right Input 1", effectName.c_str());
		properties->flags = kVstPinIsStereo|kVstPinIsActive;
		retval = true;
	}

	return retval;
}

//----------------------------------------------------------------------------
bool VstPlugin::getOutputProperties(VstInt32 index, VstPinProperties* properties)
{
	bool retval = false;

	if(index == 0)
	{
		sprintf(properties->label, "%s Left Output 1", effectName.c_str());
		properties->flags = kVstPinIsStereo|kVstPinIsActive;
		retval = true;
	}
	else if(index == 1)
	{
		sprintf(properties->label, "%s Right Output 1", effectName.c_str());
		properties->flags = kVstPinIsStereo|kVstPinIsActive;
		retval = true;
	}

	return retval;
}

//----------------------------------------------------------------------------
VstInt32 VstPlugin::getGetTailSize()
{
	return 1; //1=no tail, 0=don't know, everything else=tail size
}

//----------------------------------------------------------------------------
void VstPlugin::processMIDI(VstInt32 pos)
{
	int data1, data2;
	int status, ch, delta;
	int note;
	int i, j;

	for(i=0;i<numPendingEvents;++i)
	{
		if((midiEvent[eventNumArray[i]]->deltaFrames%frames) == pos)
		{
			//--pass on/act on event--
			delta = 0; //because we're at pos frames into the buffer...
			ch = (midiEvent[eventNumArray[i]]->midiData[0] & 0x0F);
			status = (midiEvent[eventNumArray[i]]->midiData[0] & 0xF0);
			data1 = (midiEvent[eventNumArray[i]]->midiData[1] & 0x7F);
			data2 = (midiEvent[eventNumArray[i]]->midiData[2] & 0x7F);

			note = data1;

			switch(status)
			{
				case 0x90:
					if(data2 > 0)
						MIDI_NoteOn(ch, data1, data2, delta);
					else
						MIDI_NoteOff(ch, data1, data2, delta);
					break;
				case 0x80:
					MIDI_NoteOff(ch, data1, data2, delta);
					break;
				case 0xA0:
					MIDI_PolyAftertouch(ch, data1, data2, delta);
					break;
				case 0xB0:
					MIDI_CC(ch, data1, data2, delta);
					break;
				case 0xC0:
					MIDI_ProgramChange(ch, data1, delta);
					break;
				case 0xD0:
					MIDI_ChannelAftertouch(ch, data1, delta);
					break;
				case 0xE0:
					MIDI_PitchBend(ch, data1, data2, delta);
					break;
			}
			midiEvent[eventNumArray[i]]->deltaFrames = -99;
			--numEvents;

			//--reset EventNumArray--
			for(j=(i+1);j<numPendingEvents;++j)
				eventNumArray[(j-1)] = eventNumArray[j];
			--numPendingEvents;
			//break;
		}
	}
}

//----------------------------------------------------------------------------
void VstPlugin::MIDI_NoteOn(int ch, int note, int val, int delta)
{
	midiEvent[0]->midiData[0] = 0x90 + ch;
	midiEvent[0]->midiData[1] = note;
	midiEvent[0]->midiData[2] = val;
	midiEvent[0]->deltaFrames = delta;
	sendVstEventsToHost(tempEvents);
}

//----------------------------------------------------------------------------
void VstPlugin::MIDI_NoteOff(int ch, int note, int val, int delta)
{
	midiEvent[0]->midiData[0] = 0x80 + ch;
	midiEvent[0]->midiData[1] = note;
	midiEvent[0]->midiData[2] = val;
	midiEvent[0]->deltaFrames = delta;
	sendVstEventsToHost(tempEvents);
}

//----------------------------------------------------------------------------
void VstPlugin::MIDI_PolyAftertouch(int ch, int note, int val, int delta)
{
	midiEvent[0]->midiData[0] = 0xA0 + ch;
	midiEvent[0]->midiData[1] = note;
	midiEvent[0]->midiData[2] = val;
	midiEvent[0]->deltaFrames = delta;
	sendVstEventsToHost(tempEvents);
}

//----------------------------------------------------------------------------
void VstPlugin::MIDI_CC(int ch, int num, int val, int delta)
{
	float tempf;

	tempf = static_cast<float>(val)/127.0f;	// CC data

	midiEvent[0]->midiData[0] = 0xB0 + ch;
	midiEvent[0]->midiData[1] = num;
	midiEvent[0]->midiData[2] = val;
	midiEvent[0]->deltaFrames = delta;
	sendVstEventsToHost(tempEvents);
}

//----------------------------------------------------------------------------
void VstPlugin::MIDI_ProgramChange(int ch, int val, int delta)
{
	if(val < numPrograms)
		setProgram(val);

	midiEvent[0]->midiData[0] = 0xD0 + ch;
	midiEvent[0]->midiData[1] = val;
	midiEvent[0]->midiData[2] = 0;
	midiEvent[0]->deltaFrames = delta;
	sendVstEventsToHost(tempEvents);
}

//----------------------------------------------------------------------------
void VstPlugin::MIDI_ChannelAftertouch(int ch, int val, int delta)
{
	midiEvent[0]->midiData[0] = 0xD0 + ch;
	midiEvent[0]->midiData[1] = val;
	midiEvent[0]->midiData[2] = 0;
	midiEvent[0]->deltaFrames = delta;
	sendVstEventsToHost(tempEvents);
}

//----------------------------------------------------------------------------
void VstPlugin::MIDI_PitchBend(int ch, int x1, int x2, int delta)
{
	midiEvent[0]->midiData[0] = 0xE0 + ch;
	midiEvent[0]->midiData[1] = x1;
	midiEvent[0]->midiData[2] = x2;
	midiEvent[0]->deltaFrames = delta;
	sendVstEventsToHost(tempEvents);
}
VstInt32 VstPlugin::getChunk (void** data, bool isPreset)
{///< Host stores plug-in state. Returns the size in bytes of the chunk (plug-in allocates the data array)
	// 여기에 플러그인의 상태를 저장한다.
	// 그런 후에 마우스 우측버튼으로 파라메터 오토메이션이 가능하도록 16개의 파라메터를 매핑 가능하게 하면
	// 완전 앰플리튜브...
	//if(isPreset)
		//return 0;
	//MessageBox(NULL, "2", "asd2", MB_OK);
	SaveState save;
	for(int i=0; i< 10; ++i)
	{
		save.type[i] = mEditor->mBuiltPanels[i];
		switch(mEditor->mBuiltPanels[i])
		{
		case EffLinealEQ:
			{
				save.params[i].presetIdx = 0;
				save.params[i].params[0] = mEffEQ1->getpar(0);
				save.params[i].params[1] = mEffEQ1->getpar(13);
				save.params[i].params[2] = mEffEQ1->getpar(0*5+12);
				save.params[i].params[3] = mEffEQ1->getpar(1*5+12);
				save.params[i].params[4] = mEffEQ1->getpar(2*5+12);
				save.params[i].params[5] = mEffEQ1->getpar(3*5+12);
				save.params[i].params[6] = mEffEQ1->getpar(4*5+12);
				save.params[i].params[7] = mEffEQ1->getpar(5*5+12);
				save.params[i].params[8] = mEffEQ1->getpar(6*5+12);
				save.params[i].params[9] = mEffEQ1->getpar(7*5+12);
				save.params[i].params[10] = mEffEQ1->getpar(8*5+12);
				save.params[i].params[11] = mEffEQ1->getpar(9*5+12);
			}
			break;
		case EffParametricEQ:
			{
				save.params[i].presetIdx = mEditor->mPanels[i]->mPrevPreset;
				save.params[i].params[0] = mEffEQ2->getpar(0);
				
				save.params[i].params[1] = mEffEQ2->getpar(11);
				save.params[i].params[2] = mEffEQ2->getpar(12);
				save.params[i].params[3] = mEffEQ2->getpar(13);

				save.params[i].params[4] = mEffEQ2->getpar(5+11);
				save.params[i].params[5] = mEffEQ2->getpar(5+12);
				save.params[i].params[6] = mEffEQ2->getpar(5+13);

				save.params[i].params[7] = mEffEQ2->getpar(10+11);
				save.params[i].params[8] = mEffEQ2->getpar(10+12);
				save.params[i].params[9] = mEffEQ2->getpar(10+13);
			}
			break;
		case EffEcho:
			{
				save.params[i].presetIdx = mEditor->mEchoPanel->mPrevPreset;
				for(int j=0; j< 20; ++j)
				{
					save.params[i].params[j] = mEffEcho->getpar(j);
				}
			}
			break;
		case EffDistortion:
			{
				save.params[i].presetIdx = mEditor->mDistPanel->mPrevPreset;
				for(int j=0; j< 20; ++j)
				{
					save.params[i].params[j] = mEffDistorsion->getpar(j);
				}
			}
			break;
		case EffCompressor:
			{
				save.params[i].presetIdx = mEditor->mCompressorPanel->mPrevPreset;
				for(int j=0; j< 20; ++j)
				{
					save.params[i].params[j] = mEffCompressor->getpar(j+1);
				}
			}
			break;
		case EffExpander:
		case EffGate:
			{
				save.params[i].presetIdx = mEditor->mPanels[i]->mPrevPreset;
				for(int j=0; j< 20; ++j)
				{
					save.params[i].params[j] = mEditor->mPanels[i]->mEffect->getpar(j+1);
				}
			}
			break;

		case EffWahWah:
		case EffAlienWah:
		case EffPan:
		case EffChorus:
		case EffPhaser:
		case EffReverb:
		default:
			{
				save.params[i].presetIdx = mEditor->mPanels[i]->mPrevPreset;
				for(int j=0; j< 20; ++j)
				{
					save.params[i].params[j] = mEditor->mPanels[i]->mEffect->getpar(j);
				}
			}
			break;
		}
	}
	save.totalOn = mEditor->mTotalEffectOn;
	for(int i=0;i<10;++i)
	{
		save.effOn[i] = mEditor->mEffectOn[i];
	}
	int size = sizeof(SaveState);
	(*data) = malloc(size);
	memcpy(*data, &save, size);
	return size;
}
	
VstInt32 VstPlugin::setChunk (void* data, VstInt32 byteSize, bool isPreset)
{
	//MessageBox(NULL, "", "asd", MB_OK);
	//if(isPreset)
		//return 0;
	if(byteSize < sizeof(SaveState))
		return 0;
	SaveState save;
	int size = sizeof(SaveState);
	memcpy(&save, data, size);
	for(int i=0; i< 10; ++i)
		mEditor->DeleteEffectPanel(i);
	mEditor->mUsingEffectList.clear();
	
	for(int i=0; i< 10; ++i)
	{
		int presetIdx = save.params[i].presetIdx;
		//save.type[i] = mEditor->mBuiltPanels[i];
		switch(save.type[i])
		{
		case EffLinealEQ:
			{
				mEffEQ1->changepar(0, save.params[i].params[0]);
				mEffEQ1->changepar(13, save.params[i].params[1]);
				mEffEQ1->changepar(0*5+12, save.params[i].params[2]);
				mEffEQ1->changepar(1*5+12, save.params[i].params[3]);
				mEffEQ1->changepar(2*5+12, save.params[i].params[4]);
				mEffEQ1->changepar(3*5+12, save.params[i].params[5]);
				mEffEQ1->changepar(4*5+12, save.params[i].params[6]);
				mEffEQ1->changepar(5*5+12, save.params[i].params[7]);
				mEffEQ1->changepar(6*5+12, save.params[i].params[8]);
				mEffEQ1->changepar(7*5+12, save.params[i].params[9]);
				mEffEQ1->changepar(8*5+12, save.params[i].params[10]);
				mEffEQ1->changepar(9*5+12, save.params[i].params[11]);
			}
			break;
		case EffParametricEQ:
			{
				mEffEQ2->changepar(0, save.params[i].params[0]);
				
				mEffEQ2->changepar(11, save.params[i].params[1]);
				mEffEQ2->changepar(12, save.params[i].params[2]);
				mEffEQ2->changepar(13, save.params[i].params[3]);

				mEffEQ2->changepar(5+11, save.params[i].params[4]);
				mEffEQ2->changepar(5+12, save.params[i].params[5]);
				mEffEQ2->changepar(5+13, save.params[i].params[6]);

				mEffEQ2->changepar(10+11, save.params[i].params[7]);
				mEffEQ2->changepar(10+12, save.params[i].params[8]);
				mEffEQ2->changepar(10+13, save.params[i].params[9]);
			}
			break;
		case EffEcho:
			{
				for(int j=0; j< 20; ++j)
				{
					mEffEcho->changepar(j, save.params[i].params[j]);
				}
			}
			break;
		case EffDistortion:
			{
				for(int j=0; j< 20; ++j)
				{
					mEffDistorsion->changepar(j, save.params[i].params[j]);
				}
			}
			break;
		case EffCompressor:
			{
				for(int j=0; j< 20; ++j)
				{
					mEffCompressor->changepar(j+1, save.params[i].params[j]);
				}
			}
			break;
		case EffExpander:
				for(int j=0; j< 20; ++j)
				{
					mEffExpander->changepar(j+1, save.params[i].params[j]);
				}
		case EffGate:
			{
				for(int j=0; j< 20; ++j)
				{
					mEffGate->changepar(j+1, save.params[i].params[j]);
				}
			}
			break;

		case EffWahWah:
			{
				for(int j=0; j< 20; ++j)
				{
					mEffWahWah->changepar(j, save.params[i].params[j]);
				}
			}
			break;
		case EffAlienWah:
			{
				for(int j=0; j< 20; ++j)
				{
					mEffAlienwah->changepar(j, save.params[i].params[j]);
				}
			}
			break;
		case EffPan:
			{
				for(int j=0; j< 20; ++j)
				{
					mEffPan->changepar(j, save.params[i].params[j]);
				}
			}
			break;
		case EffChorus:
			{
				for(int j=0; j< 20; ++j)
				{
					mEffChorus->changepar(j, save.params[i].params[j]);
				}
			}
			break;
		case EffPhaser:
			{
				for(int j=0; j< 20; ++j)
				{
					mEffPhaser->changepar(j, save.params[i].params[j]);
				}
			}
			break;
		case EffReverb:
			{
				for(int j=0; j< 20; ++j)
				{
					mEffReverb->changepar(j, save.params[i].params[j]);
				}
			}
			break;
		case EffConvolotron:
			{
				for(int j=0; j< 20; ++j)
				{
					mEffConvolotron->changepar(j, save.params[i].params[j]);
				}
			}
			break;
		case EffAnalogPhaser:
			{
				for(int j=0; j< 20; ++j)
				{
					mEffAPhaser->changepar(j, save.params[i].params[j]);
				}
			}
			break;
		case EffArpie:
			{
				for(int j=0; j< 20; ++j)
				{
					mEffArpie->changepar(j, save.params[i].params[j]);
				}
			}
			break;
		case EffFlange:
			{
				for(int j=0; j< 20; ++j)
				{
					mEffFlange->changepar(j, save.params[i].params[j]);
				}
			}
			break;
		case EFfCoilCrafter:
			{
				for(int j=0; j< 20; ++j)
				{
					mEffCoil->changepar(j, save.params[i].params[j]);
				}
			}
			break;
		case EFfCompBand:
			{
				for(int j=0; j< 20; ++j)
				{
					mEffCompBand->changepar(j, save.params[i].params[j]);
				}
			}
			break;
		case EffDualFlange:
			{
				for(int j=0; j< 20; ++j)
				{
					mEffDualFlange->changepar(j, save.params[i].params[j]);
				}
			}
			break;
		case EffEchotron:
			{
				for(int j=0; j< 20; ++j)
				{
					mEffEchotron->changepar(j, save.params[i].params[j]);
				}
			}
			break;
		case EffExciter:
			{
				for(int j=0; j< 20; ++j)
				{
					mEffExciter->changepar(j, save.params[i].params[j]);
				}
			}
			break;
		case EffHarmonizer:
			{
				for(int j=0; j< 20; ++j)
				{
					mEffHarmonizer->changepar(j, save.params[i].params[j]);
				}
			}
			break;
		case EffInfinity:
			{
				for(int j=0; j< 20; ++j)
				{
					mEffInfinity->changepar(j, save.params[i].params[j]);
				}
			}
			break;
		case EffMBDist:
			{
				for(int j=0; j< 20; ++j)
				{
					mEffMBDist->changepar(j, save.params[i].params[j]);
				}
			}
			break;
		case EffMBVvol:
			{
				for(int j=0; j< 20; ++j)
				{
					mEffMBVvol->changepar(j, save.params[i].params[j]);
				}
			}
			break;
		case EffMusicDelay:
			{
				for(int j=0; j< 20; ++j)
				{
					mEffMusicDelay->changepar(j, save.params[i].params[j]);
				}
			}
			break;
		case EffNewDist:
			{
				for(int j=0; j< 20; ++j)
				{
					mEffNewDist->changepar(j, save.params[i].params[j]);
				}
			}
			break;
		case EffOpticaltrem:
			{
				for(int j=0; j< 20; ++j)
				{
					mEffOpticalTrem->changepar(j, save.params[i].params[j]);
				}
			}
			break;
		case EffRBEcho:
			{
				for(int j=0; j< 20; ++j)
				{
					mEffRBEcho->changepar(j, save.params[i].params[j]);
				}
			}
			break;
		case EffReverbtron:
			{
				for(int j=0; j< 20; ++j)
				{
					mEffReverbtron->changepar(j, save.params[i].params[j]);
				}
			}
			break;
		case EffRing:
			{
				for(int j=0; j< 20; ++j)
				{
					mEffRing->changepar(j, save.params[i].params[j]);
				}
			}
			break;
		case EffRyanWah:
			{
				for(int j=0; j< 20; ++j)
				{
					mEffRyanWah->changepar(j, save.params[i].params[j]);
				}
			}
			break;
		case EffSequence:
			{
				for(int j=0; j< 20; ++j)
				{
					mEffSequence->changepar(j, save.params[i].params[j]);
				}
			}
			break;
		case EffShelfBoost:
			{
				for(int j=0; j< 20; ++j)
				{
					mEffShelfBoost->changepar(j, save.params[i].params[j]);
				}
			}
			break;
		case EffShifter:
			{
				for(int j=0; j< 20; ++j)
				{
					mEffShifter->changepar(j, save.params[i].params[j]);
				}
			}
			break;
		case EffShuffle:
			{
				for(int j=0; j< 20; ++j)
				{
					mEffShuffle->changepar(j, save.params[i].params[j]);
				}
			}
			break;
		case EffStereoHarm:
			{
				for(int j=0; j< 20; ++j)
				{
					mEffStereoHarm->changepar(j, save.params[i].params[j]);
				}
			}
			break;
		case EffStompBox:
			{
				for(int j=0; j< 20; ++j)
				{
					mEffStompBox->changepar(j, save.params[i].params[j]);
				}
			}
			break;
		case EffSustainer:
			{
				for(int j=0; j< 20; ++j)
				{
					mEffSustainer->changepar(j, save.params[i].params[j]);
				}
			}
			break;
		case EffSynthfilter:
			{
				for(int j=0; j< 20; ++j)
				{
					mEffSynthfilter->changepar(j, save.params[i].params[j]);
				}
			}
			break;
		case EffValve:
			{
				for(int j=0; j< 20; ++j)
				{
					mEffValve->changepar(j, save.params[i].params[j]);
				}
			}
			break;
		case EffVibe:
			{
				for(int j=0; j< 20; ++j)
				{
					mEffVibe->changepar(j, save.params[i].params[j]);
				}
			}
			break;
		}
		mEditor->CreateEffectPanel(save.type[i], i, true, presetIdx);
	}
	ListBox *rightList = (ListBox*)(mEditor->mGUI->GetElement(mEditor->beingUsedEffectsList));
	TabbedListBox *leftList = (TabbedListBox*)(mEditor->mGUI->GetElement(mEditor->unusedEffectsList));

	char temp[123];
	for(int i=0;i<mEditor->mUsingEffectList.size();++i)
	{
		sprintf(temp, "%s", mEditor->mUsingEffectList[i].name.c_str());
		rightList->Add(temp);
	}


	vector<EffectName> unusedEffectList;
	for(int i=0; i< mEditor->mEffectNames.size(); ++i)
	{
		bool found = false;
		for(int j=0; j < mEditor->mUsingEffectList.size(); ++j)
		{
			if(mEditor->mUsingEffectList[j].type == mEditor->mEffectNames[i].type)
			{
				found = true;
				break;
			}
		}
		if(!found)
		{
			unusedEffectList.push_back(mEditor->mEffectNames[i]);
		}
	}
	sort(unusedEffectList.begin(), unusedEffectList.end(), CompEff);

	for(int i=0;i<unusedEffectList.size();++i)
	{
		sprintf(temp, "%s", unusedEffectList[i].name.c_str());
		leftList->Add(temp);
	}

	mEditor->mTotalEffectOn = save.totalOn;
	((OnOffButton*)(mEditor->mGUI->GetElement(mEditor->mTotalOnOffButton)))->mOn = mEditor->mTotalEffectOn;
	
	for(int i=0;i<10;++i)
	{
		mEditor->mEffectOn[i] = save.effOn[i];
		((OnOffButton*)(mEditor->mGUI->GetElement(mEditor->mOnOffButtons[i])))->mOn = mEditor->mEffectOn[i];

	}


	return size;
}	///< Host restores plug-in state