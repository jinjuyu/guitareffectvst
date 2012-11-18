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
#include <string>
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
	mEffHarmonizer = new Harmonizer(mParam, nullptr, nullptr, 32, 1, 4, 2); // keep quality at 4 or 32, DS == 1 means 96000 and so on, leave uq dq at 4,2 for now
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

	//Construct editor here.
	editor = new ExampleEditor(this);


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




	mEffLimiter->processReplacing(outputs, tempOutputs, sampleFrames); // Hidden Final Limiter Chain
	for(int i=0; i<sampleFrames; ++i)
	{
		outputs[0][i] = tempOutputs[0][i];
		outputs[1][i] = tempOutputs[1][i];
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
