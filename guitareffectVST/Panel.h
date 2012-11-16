#pragma once
#include "../VSTGL/ExampleEditor.h"
#include "../VSTGL/VstPlugin.h"

/*
const int PRESET_SIZE = 12;
const int NUM_PRESETS = 10;
int presets[NUM_PRESETS][PRESET_SIZE] = {
    //Chorus1
    {64, 64, 33, 0, 0, 90, 40, 85, 64, 119, 0, 0},
    //Chorus2
    {64, 64, 19, 0, 0, 98, 56, 90, 64, 19, 0, 0},
    //Chorus3
    {64, 64, 7, 0, 1, 42, 97, 95, 90, 127, 0, 0},
    //Celeste1
    {64, 64, 1, 0, 0, 42, 115, 18, 90, 127, 0, 0},
    //Celeste2
    {64, 64, 7, 117, 0, 50, 115, 9, 31, 127, 0, 1},
    //Flange1
    {64, 64, 39, 0, 0, 60, 23, 3, 62, 0, 0, 0},
    //Flange2
    {64, 64, 9, 34, 1, 40, 35, 3, 109, 0, 0, 0},
    //Flange3
    {64, 64, 31, 34, 1, 94, 35, 3, 54, 0, 0, 1},
    //Flange4
    {64, 64, 14, 0, 1, 62, 12, 19, 97, 0, 0, 0},
    //Flange5
    {64, 64, 34, 105, 0, 24, 39, 19, 17, 0, 0, 1}
};


int ChorusReal[] = { // Chorus/Flange! 두개를 하나로 합쳐쓴다.? 아니다. 코러스랑 플랜지를 중복해야한다.
//case 0:
//setvolume (value); Wet Dry
	0, 127,
//case 1:
//setpanning (value); Pan
	0, 127,
//case 2:
//lfo.Pfreq = value; Tempo
	1, 600,
//case 3:
//lfo.Prandomness = value; Rnd
	0, 127,
//case 4:
//lfo.PLFOtype = value; LFOType
	0, 9,  // type value
	/*
    Sine
    Tri
    RampUp
    RampDown
    ZigZag
    M.Sqare
    M.Saw
	L. Fractal
    L. Fractal XY
    S/H Random*/
//case 5:
//lfo.Pstereo = value; St.df
	0, 127,
//case 6:
//setdepth (value); // Depth
	0, 127,
//case 7:
//setdelay (value); // Delay
	0, 127,
//case 8:
//setfb (value); // Fb.
	0, 127,
//case 9:
//setlrcross (value); // L/R.Cr
	0, 127,
//case 10:
	//Pflangemode = value;
	0, 1, // Boolean: Chorus/Flange
//case 11:
//Poutsub = value; // Subtract
	0, 1, // Boolean
//case 12:
//awesome_mode = value; // Intense
	0, 1,

};
int ChorusPrint[] = {
	-64, 63, // 0
	-64, 63, // 1
	1, 600, // 2
	0, 127, // 3
	0, 9, // 4
	0, 127, // 5
	0, 127, // 6
	0, 127, // 7
	0, 127, // 8
	-64, 63, // 9
	0, 1, // 10
	0, 1, // 11
	0, 1, // 12
};
*/