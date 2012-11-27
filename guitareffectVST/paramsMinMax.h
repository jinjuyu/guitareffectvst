#pragma once

#include "../VSTGL/ExampleEditor.h"
#include "../VSTGL/VstPlugin.h"
// 모든 파라메터(랙의 위치라던가 등등)를 vst param으로 내보내어 저장할 수 있게 한다.
// EQ1 Freq 등등으로 파라메터의 이름을 모두 저장하고 minmax를 여기에 넣는다.
// Rack 0 -> 0이면 EQ1이고 1이면 EQ2 등등.6


class Params
{
public:
	Params()
	{

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
		
		const int aphaser_PRESET_SIZE = 13;
		const int aphaser_NUM_PRESETS = 6;
		int aphaser_presets[] = {
			//Phaser1
			64, 20, 14, 0, 1, 64, 110, 40, 4, 10, 0, 64, 1,
			//Phaser2
			64, 20, 14, 5, 1, 64, 110, 40, 6, 10, 0, 70, 1,
			//Phaser3
			64, 20, 9, 0, 0, 64, 40, 40, 8, 10, 0, 60, 0,
			//Phaser4
			64, 20, 14, 10, 0, 64, 110, 80, 7, 10, 1, 45, 1,
			//Phaser5
			25, 20, 240, 10, 0, 64, 25, 16, 8, 100, 0, 25, 0,
			//Phaser6
			64, 20, 1, 10, 1, 64, 110, 40, 12, 10, 0, 70, 1
		};
		int APhaserReal[] = {

		};
		int APhaserPrint[] = {
		};

	}
};

/*
      Fl_Group APHASER {
        user_data 1
        xywh {480 211 158 184} box UP_BOX color 0 selection_color 0 labelfont 1 align 112 hide
      } {
        Fl_Light_Button aphaser_activar {
          label On
          user_data 2
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(116);
 o->value(rkr->APhaser_Bypass);
 return;
}
rkr->APhaser_Bypass=(int)o->value();
if((int) o->value()==0)
rkr->efx_APhaser->cleanup();
findpos(18,(int)o->value(),o);}
          xywh {485 215 34 18} shortcut 0x37 color 62 selection_color 1 labelsize 10 align 84 when 1
        }
        Fl_Choice aphaser_preset {
          label Preset
          user_data 12018
          callback {long long ud= (long long) v;
if((ud==0)||(ud==12018))rkr->efx_APhaser->setpreset((int) o->value());
aphaser_WD->value(rkr->efx_APhaser->getpar(0)-64);
aphaser_pan->value(rkr->efx_APhaser->getpar(1));
aphaser_freq->value(rkr->efx_APhaser->getpar(2));
aphaser_lfotype->value(rkr->efx_APhaser->getpar(4));
aphaser_stdf->value(rkr->efx_APhaser->getpar(5));
aphaser_dpth->value(rkr->efx_APhaser->getpar(6));
aphaser_stages->value(rkr->efx_APhaser->getpar(8));
aphaser_fb->value(rkr->efx_APhaser->getpar(7)-64);
aphaser_LR->value(rkr->efx_APhaser->getpar(9));
aphaser_subs->value(rkr->efx_APhaser->getpar(10));
aphaser_phase->value(rkr->efx_APhaser->getpar(11));
aphaser_hyper->value(rkr->efx_APhaser->getpar(12));}
          xywh {557 215 76 18} down_box BORDER_BOX selection_color 0 labelsize 10 labelcolor 7 when 6 textsize 10 textcolor 7
        } {
          MenuItem {} {
            label {Phaser 1}
            xywh {72 72 36 21} labelsize 10
          }
          MenuItem {} {
            label {Phaser 2}
            xywh {72 72 36 21} labelsize 10
          }
          MenuItem {} {
            label {Phaser 3}
            xywh {72 72 36 21} labelsize 10
          }
          MenuItem {} {
            label {Phaser 4}
            xywh {82 82 36 21} labelsize 10
          }
          MenuItem {} {
            label {Phaser 5}
            xywh {92 92 36 21} labelsize 10
          }
          MenuItem {} {
            label {Phaser 6}
            xywh {102 102 36 21} labelsize 10
          }
        }
        Fl_Value_Slider aphaser_WD {
          label {Wet/Dry}
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(117);
 return;
} 
rkr->efx_APhaser->changepar(0,(int)(o->value()+64));}
          xywh {529 238 100 10} type {Horz Knob} box FLAT_BOX color 178 selection_color 62 labelsize 10 labelcolor 7 align 4 minimum -64 maximum 63 step 1 textcolor 7
          class SliderW
        }
        Fl_Choice aphaser_lfotype {
          label {LFO Type}
          callback {rkr->efx_APhaser->changepar(4,(int)o->value());} open
          xywh {555 252 72 16} down_box BORDER_BOX selection_color 0 labelsize 10 labelcolor 7 textsize 10 textcolor 7
          code0 {o->menu(menu_chorus_lfotype);}
        } {}
        Fl_Value_Slider aphaser_freq {
          label Tempo
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(119);
 return;
} 
rkr->efx_APhaser->changepar(2,(int)o->value());}
          xywh {528 273 100 10} type {Horz Knob} box FLAT_BOX color 178 selection_color 62 labelsize 10 labelcolor 7 align 4 minimum 1 maximum 600 step 1 textcolor 7
          class SliderW
        }
        Fl_Value_Slider aphaser_dpth {
          label Width
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(121);
 return;
} 
rkr->efx_APhaser->changepar(6,(int)o->value());}
          xywh {528 297 100 10} type {Horz Knob} box FLAT_BOX color 178 selection_color 62 labelsize 10 labelcolor 7 align 4 maximum 127 step 1 textcolor 7
          class SliderW
        }
        Fl_Value_Slider aphaser_phase {
          label Depth
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(120);
 return;
} 
rkr->efx_APhaser->changepar(11,(int)o->value());}
          xywh {529 285 100 10} type {Horz Knob} box FLAT_BOX color 178 selection_color 62 labelsize 10 labelcolor 7 align 4 maximum 127 step 1 textcolor 7
          class SliderW
        }
        Fl_Value_Slider aphaser_fb {
          label Fb
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(122);
 return;
} 
rkr->efx_APhaser->changepar(7,(int)(o->value()+64));}
          xywh {528 309 100 10} type {Horz Knob} box FLAT_BOX color 178 selection_color 62 labelsize 10 labelcolor 7 align 4 minimum -64 maximum 64 step 1 textcolor 7
          class SliderW
        }
        Fl_Value_Slider aphaser_LR {
          label Mismatch
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(123);
 return;
} 
rkr->efx_APhaser->changepar(9,(int)o->value());}
          xywh {528 322 100 10} type {Horz Knob} box FLAT_BOX color 178 selection_color 62 labelsize 7 labelcolor 7 align 4 maximum 100 step 1 textcolor 7
          class SliderW
        }
        Fl_Value_Slider aphaser_pan {
          label Distort
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(118);
 return;
} 
rkr->efx_APhaser->changepar(1,(int)o->value());}
          xywh {528 333 100 10} type {Horz Knob} box FLAT_BOX color 178 selection_color 62 labelsize 10 labelcolor 7 align 4 maximum 100 step 1 textcolor 7
          class SliderW
        }
        Fl_Value_Slider aphaser_stdf {
          label {St.df}
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(124);
 return;
} 
rkr->efx_APhaser->changepar(5,(int)o->value());}
          xywh {529 345 100 10} type {Horz Knob} box FLAT_BOX color 178 selection_color 62 labelsize 10 labelcolor 7 align 4 maximum 127 step 1 textcolor 7
          class SliderW
        }
        Fl_Counter aphaser_stages {
          label Stages
          callback {rkr->efx_APhaser->changepar(8,(int)o->value());}
          xywh {560 362 52 12} type Simple box THIN_UP_BOX labelsize 10 labelcolor 7 align 4 minimum 1 maximum 12 step 1 value 1 textsize 9
        }
        Fl_Check_Button aphaser_subs {
          label Subtract
          user_data 2
          callback {rkr->efx_APhaser->changepar(10,(int)o->value())}
          xywh {490 376 64 15} down_box BORDER_BOX labelsize 10 labelcolor 7
        }
        Fl_Check_Button aphaser_hyper {
          label Hyper
          user_data 2
          callback {rkr->efx_APhaser->changepar(12,(int)o->value())}
          xywh {555 376 53 15} down_box BORDER_BOX labelsize 10 labelcolor 7
        }
      }
      Fl_Group VALVE {
        user_data 1
        xywh {161 212 158 184} box UP_BOX color 0 selection_color 0 labelfont 1 align 112 hide
      } {
        Fl_Light_Button valve_activar {
          label On
          user_data 2
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(116);
 o->value(rkr->Valve_Bypass);
 return;
}
rkr->Valve_Bypass=(int)o->value();
if((int) o->value()==0)
rkr->efx_Valve->cleanup();
findpos(19,(int)o->value(),o);}
          xywh {166 216 34 18} shortcut 0x33 color 62 selection_color 1 labelsize 10 align 84 when 1
        }
        Fl_Choice valve_preset {
          label Preset
          user_data 12019
          callback {long long ud= (long long) v;
if((ud==0)||(ud==12019))rkr->efx_Valve->setpreset((int)o->value());
valve_WD->value(rkr->efx_Valve->getpar(0)-64);
valve_LRc->value(rkr->efx_Valve->getpar(2)-64);
valve_drive->value(rkr->efx_Valve->getpar(3));
valve_level->value(rkr->efx_Valve->getpar(4));
valve_neg->value(rkr->efx_Valve->getpar(5));
valve_st->value(rkr->efx_Valve->getpar(8));
valve_pan->value(rkr->efx_Valve->getpar(1)-64);
valve_pf->value(rkr->efx_Valve->getpar(9));
valve_lpf->value(rkr->efx_Valve->getpar(6));
valve_hpf->value(rkr->efx_Valve->getpar(7));
valve_Q->value(rkr->efx_Valve->getpar(10));
valve_ed->value(rkr->efx_Valve->getpar(11));
valve_Pre->value(rkr->efx_Valve->getpar(12));}
          xywh {238 216 76 18} down_box BORDER_BOX selection_color 0 labelsize 10 labelcolor 7 when 6 textsize 10 textcolor 7
        } {
          MenuItem {} {
            label {Valve 1}
            xywh {42 42 36 21} labelsize 10
          }
          MenuItem {} {
            label {Valve 2}
            xywh {42 42 36 21} labelsize 10
          }
          MenuItem {} {
            label {Valve 3}
            xywh {52 52 36 21} labelsize 10
          }
        }
        Fl_Value_Slider valve_WD {
          label {Wet/Dry}
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(169);
 return;
} 
rkr->efx_Valve->changepar(0,(int)(o->value()+64));}
          xywh {214 243 100 10} type {Horz Knob} box FLAT_BOX color 178 selection_color 62 labelsize 10 labelcolor 7 align 4 minimum -64 maximum 63 step 1 textcolor 7
          class SliderW
        }
        Fl_Value_Slider valve_LRc {
          label {L/R.Cr}
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(170);
 return;
} 
rkr->efx_Valve->changepar(2,(int)(o->value()+64));}
          xywh {214 256 100 10} type {Horz Knob} box FLAT_BOX color 178 selection_color 62 labelsize 10 labelcolor 7 align 4 minimum -64 maximum 63 step 1 textcolor 7
          class SliderW
        }
        Fl_Value_Slider valve_pan {
          label Pan
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(171);
 return;
} 
rkr->efx_Valve->changepar(1,(int)(o->value()+64));}
          xywh {214 269 100 10} type {Horz Knob} box FLAT_BOX color 178 selection_color 62 labelsize 10 labelcolor 7 align 4 minimum -64 maximum 63 step 1 textcolor 7
          class SliderW
        }
        Fl_Value_Slider valve_level {
          label Level
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(172);
 return;
} 
rkr->efx_Valve->changepar(4,(int)o->value());}
          xywh {214 283 100 10} type {Horz Knob} box FLAT_BOX color 178 selection_color 62 labelsize 10 labelcolor 7 align 4 maximum 127 step 1 textcolor 7
          class SliderW
        }
        Fl_Value_Slider valve_drive {
          label Drive
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(173);
 return;
} 
rkr->efx_Valve->changepar(3,(int)o->value());}
          xywh {214 296 100 10} type {Horz Knob} box FLAT_BOX color 178 selection_color 62 labelsize 10 labelcolor 7 align 4 maximum 127 step 1 textcolor 7
          class SliderW
        }
        Fl_Check_Button valve_ed {
          label {Extra Dist.}
          user_data 2
          callback {rkr->efx_Valve->changepar(11,(int)o->value());}
          xywh {176 308 72 15} down_box BORDER_BOX labelsize 10 labelcolor 7
        }
        Fl_Value_Slider valve_Q {
          label {Dist.}
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(174);
 return;
} 
rkr->efx_Valve->changepar(10,(int)o->value());}
          xywh {214 324 100 10} type {Horz Knob} box FLAT_BOX color 178 selection_color 62 labelsize 10 labelcolor 7 align 4 maximum 127 step 1 textcolor 7
          class SliderW
        }
        Fl_Value_Slider valve_Pre {
          label Presence
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(175);
 return;
} 
rkr->efx_Valve->changepar(12,(int)o->value());}
          xywh {214 339 100 10} type {Horz Knob} box FLAT_BOX color 178 selection_color 62 labelsize 10 labelcolor 7 align 4 maximum 100 step 1 textcolor 7
          class SliderW
        }
        Fl_Check_Button valve_pf {
          label {Pre Filter}
          user_data 2
          callback {rkr->efx_Valve->changepar(9,(int)o->value());}
          xywh {166 351 62 15} down_box BORDER_BOX labelsize 10 labelcolor 7
        }
        Fl_Check_Button valve_st {
          label Stereo
          user_data 2
          callback {rkr->efx_Valve->changepar(8,(int)o->value());}
          xywh {226 351 50 15} down_box BORDER_BOX labelsize 10 labelcolor 7
        }
        Fl_Check_Button valve_neg {
          label {Neg.}
          user_data 2
          callback {rkr->efx_Valve->changepar(5,(int)o->value());}
          xywh {275 351 40 15} down_box BORDER_BOX labelsize 10 labelcolor 7
        }
        Fl_Value_Slider valve_lpf {
          label LPF
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(176);
 return;
} 
rkr->efx_Valve->changepar(6,(int)o->value());}
          xywh {214 368 100 10} type {Horz Knob} box FLAT_BOX color 178 selection_color 62 labelsize 10 labelcolor 7 align 4 minimum 20 maximum 26000 step 1 value 20000 textcolor 7
          class SliderW
        }
        Fl_Value_Slider valve_hpf {
          label HPF
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(177);
 return;
} 
rkr->efx_Valve->changepar(7,(int)o->value());}
          xywh {214 381 100 10} type {Horz Knob} box FLAT_BOX color 178 selection_color 62 labelsize 10 labelcolor 7 align 4 minimum 20 maximum 20000 step 1 value 20 textcolor 7
          class SliderW
        }
      }
      Fl_Group DFLANGE {
        user_data 1
        xywh {321 212 158 184} box UP_BOX color 0 selection_color 0 labelfont 1 align 112 hide
      } {
        Fl_Light_Button dflange_activar {
          label On
          user_data 2
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(116);
 o->value(rkr->DFlange_Bypass);
 return;
}
rkr->DFlange_Bypass=(int)o->value();
if((int) o->value()==0)
rkr->efx_DFlange->cleanup();
findpos(20,(int)o->value(),o);}
          xywh {326 216 34 18} shortcut 0x38 color 62 selection_color 1 labelsize 10 align 84 when 1
        }
        Fl_Choice dflange_preset {
          label Preset
          user_data 12020
          callback {long long ud= (long long) v;
if((ud==0)||(ud==12020))rkr->efx_DFlange->setpreset((int)o->value());
dflange_WD->value(rkr->efx_DFlange->getpar(0));
dflange_pan->value(rkr->efx_DFlange->getpar(1));
dflange_freq->value(rkr->efx_DFlange->getpar(10));
dflange_rnd->value(rkr->efx_DFlange->getpar(13));
dflange_lfotype->value(rkr->efx_DFlange->getpar(12));
dflange_stdf->value(rkr->efx_DFlange->getpar(11));
dflange_width->value(rkr->efx_DFlange->getpar(4));
dflange_depth->value(rkr->efx_DFlange->getpar(3));
dflange_fb->value(rkr->efx_DFlange->getpar(6));
dflange_LR->value(rkr->efx_DFlange->getpar(2));
dflange_subs->value(rkr->efx_DFlange->getpar(8));
dflange_tz->value(rkr->efx_DFlange->getpar(9));
dflange_offset->value(rkr->efx_DFlange->getpar(5));
dflange_lpf->value(rkr->efx_DFlange->getpar(7));
dflange_intense->value(rkr->efx_DFlange->getpar(14));}
          xywh {398 216 76 18} down_box BORDER_BOX selection_color 0 labelsize 10 labelcolor 7 when 6 textsize 10 textcolor 7
        } {
          MenuItem {} {
            label {Dual Flange 1}
            xywh {72 72 36 21} labelsize 10
          }
          MenuItem {} {
            label {Flange-Wah}
            xywh {72 72 36 21} labelsize 10
          }
          MenuItem {} {
            label FbFlange
            xywh {72 72 36 21} labelsize 10
          }
          MenuItem {} {
            label SoftFlange
            xywh {82 82 36 21} labelsize 10
          }
          MenuItem {} {
            label Flanger
            xywh {92 92 36 21} labelsize 10
          }
          MenuItem {} {
            label {Deep Chorus}
            xywh {102 102 36 21} labelsize 10
          }
          MenuItem {} {
            label {Bright Chorus}
            xywh {112 112 36 21} labelsize 10
          }
        }
        Fl_Value_Slider dflange_WD {
          label {Wet/Dry}
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(158);
 return;
} 
rkr->efx_DFlange->changepar(0,(int)(o->value()));}
          xywh {373 236 100 10} type {Horz Knob} box FLAT_BOX color 178 selection_color 62 labelsize 10 labelcolor 7 align 4 minimum -64 maximum 64 step 1 textcolor 7
          class SliderW
        }
        Fl_Value_Slider dflange_pan {
          label Pan
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(159);
 return;
} 
rkr->efx_DFlange->changepar(1,(int)o->value());}
          xywh {373 247 100 10} type {Horz Knob} box FLAT_BOX color 178 selection_color 62 labelsize 10 labelcolor 7 align 4 minimum -64 maximum 64 step 1 textcolor 7
          class SliderW
        }
        Fl_Value_Slider dflange_LR {
          label {L/R.Cr}
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(160);
 return;
} 
rkr->efx_DFlange->changepar(2,(int)o->value());}
          xywh {373 258 100 10} type {Horz Knob} box FLAT_BOX color 178 selection_color 62 labelsize 10 labelcolor 7 align 4 maximum 127 step 1 textcolor 7
          class SliderW
        }
        Fl_Value_Slider dflange_depth {
          label Depth
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(161);
 return;
} 
rkr->efx_DFlange->changepar(3,(int)o->value());}
          xywh {373 269 100 10} type {Horz Knob} box FLAT_BOX color 178 selection_color 62 labelsize 10 labelcolor 7 align 4 minimum 20 maximum 500 step 1 value 20 textcolor 7
          class SliderW
        }
        Fl_Value_Slider dflange_width {
          label Width
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(162);
 return;
} 
rkr->efx_DFlange->changepar(4,(int)o->value());}
          xywh {373 281 100 10} type {Horz Knob} box FLAT_BOX color 178 selection_color 62 labelsize 10 labelcolor 7 align 4 maximum 3000 step 1 textcolor 7
          class SliderW
        }
        Fl_Value_Slider dflange_offset {
          label Offset
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(163);
 return;
} 
rkr->efx_DFlange->changepar(5,(int)o->value());}
          xywh {373 292 100 10} type {Horz Knob} box FLAT_BOX color 178 selection_color 62 labelsize 10 labelcolor 7 align 4 maximum 100 step 1 textcolor 7
          class SliderW
        }
        Fl_Value_Slider dflange_fb {
          label Fb
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(164);
 return;
} 
rkr->efx_DFlange->changepar(6,(int)o->value());}
          xywh {373 303 100 10} type {Horz Knob} box FLAT_BOX color 178 selection_color 62 labelsize 10 labelcolor 7 align 4 minimum -64 maximum 64 step 1 textcolor 7
          class SliderW
        }
        Fl_Value_Slider dflange_lpf {
          label LPF
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(165);
 return;
} 
rkr->efx_DFlange->changepar(7,(int)o->value());}
          xywh {373 314 100 10} type {Horz Knob} box FLAT_BOX color 178 selection_color 62 labelsize 10 labelcolor 7 align 4 minimum 20 maximum 20000 step 1 value 20 textcolor 7
          class SliderW
        }
        Fl_Check_Button dflange_subs {
          label Subtr
          user_data 2
          callback {rkr->efx_DFlange->changepar(8,(int)o->value());}
          xywh {326 325 46 15} down_box BORDER_BOX labelsize 10 labelcolor 7
        }
        Fl_Check_Button dflange_tz {
          label {Th. zero}
          user_data 2
          callback {rkr->efx_DFlange->changepar(9,(int)o->value());}
          xywh {369 325 55 15} down_box BORDER_BOX labelsize 10 labelcolor 7
        }
        Fl_Check_Button dflange_intense {
          label Intense
          user_data 2
          callback {rkr->efx_DFlange->changepar(14,(int)o->value());}
          xywh {423 325 52 15} down_box BORDER_BOX labelsize 10 labelcolor 7
        }
        Fl_Value_Slider dflange_freq {
          label Tempo
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(166);
 return;
} 
rkr->efx_DFlange->changepar(10,(int)o->value());}
          xywh {373 340 100 10} type {Horz Knob} box FLAT_BOX color 178 selection_color 62 labelsize 10 labelcolor 7 align 4 minimum 1 maximum 600 step 1 value 100 textcolor 7
          class SliderW
        }
        Fl_Value_Slider dflange_stdf {
          label {St.df}
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(167);
 return;
} 
rkr->efx_DFlange->changepar(11,(int)o->value());}
          xywh {373 352 100 10} type {Horz Knob} box FLAT_BOX color 178 selection_color 62 labelsize 10 labelcolor 7 align 4 maximum 127 step 1 textcolor 7
          class SliderW
        }
        Fl_Choice dflange_lfotype {
          label {LFO Type}
          callback {rkr->efx_DFlange->changepar(12,(int)o->value());} open
          xywh {384 365 72 15} down_box BORDER_BOX selection_color 0 labelsize 10 labelcolor 7 textsize 10 textcolor 7
          code0 {o->menu(menu_chorus_lfotype);}
        } {}
        Fl_Value_Slider dflange_rnd {
          label Rnd
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(168);
 return;
} 
rkr->efx_DFlange->changepar(13,(int)o->value());}
          xywh {373 382 100 10} type {Horz Knob} box FLAT_BOX color 178 selection_color 62 labelsize 10 labelcolor 7 align 4 maximum 127 step 1 textcolor 7
          class SliderW
        }
      }
      Fl_Group RING {
        user_data 1
        xywh {322 411 158 184} box UP_BOX color 0 selection_color 0 labelfont 1 align 112 hide
      } {
        Fl_Light_Button ring_activar {
          label On
          user_data 2
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(116);
 o->value(rkr->Ring_Bypass);
 return;
}
rkr->Ring_Bypass=(int)o->value();
if((int) o->value()==0)
rkr->efx_Ring->cleanup();
findpos(21,(int)o->value(),o);}
          xywh {327 415 34 18} shortcut 0x34 color 62 selection_color 1 labelsize 10 align 84 when 1
        }
        Fl_Choice ring_preset {
          label Preset
          user_data 12021
          callback {long long ud= (long long) v;
if((ud==0)||(ud==12021))rkr->efx_Ring->setpreset((int) o->value());
ring_WD->value(rkr->efx_Ring->getpar(0));
ring_LRc->value(rkr->efx_Ring->getpar(2));
ring_input->value(rkr->efx_Ring->getpar(11));
ring_level->value(rkr->efx_Ring->getpar(3));
ring_st->value(rkr->efx_Ring->getpar(6));
ring_depth->value(rkr->efx_Ring->getpar(4));
ring_freq->value(rkr->efx_Ring->getpar(5));
ring_sin->value(rkr->efx_Ring->getpar(7));
ring_tri->value(rkr->efx_Ring->getpar(8));
ring_saw->value(rkr->efx_Ring->getpar(9));
ring_squ->value(rkr->efx_Ring->getpar(10));
ring_pan->value(rkr->efx_Ring->getpar(1));
ring_afreq->value(rkr->efx_Ring->getpar(12));}
          xywh {399 415 76 18} down_box BORDER_BOX selection_color 0 labelsize 10 labelcolor 7 when 6 textsize 10 textcolor 7
        } {
          MenuItem {} {
            label Saw_Sin
            xywh {52 52 36 21} labelsize 10
          }
          MenuItem {} {
            label {E string}
            xywh {52 52 36 21} labelsize 10
          }
          MenuItem {} {
            label {A string}
            xywh {62 62 36 21} labelsize 10
          }
          MenuItem {} {
            label Dissonance
            xywh {72 72 36 21} labelsize 10
          }
          MenuItem {} {
            label {Fast Beat}
            xywh {82 82 36 21} labelsize 10
          }
          MenuItem {} {
            label {Ring Amp}
            xywh {92 92 36 21} labelsize 10
          }
        }
        Fl_Value_Slider ring_WD {
          label {Wet/Dry}
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(178);
 return;
} 
rkr->efx_Ring->changepar(0,(int)o->value());}
          xywh {373 440 100 10} type {Horz Knob} box FLAT_BOX color 178 selection_color 62 labelsize 10 labelcolor 7 align 4 minimum -64 maximum 64 step 1 textcolor 7
          class SliderW
        }
        Fl_Value_Slider ring_LRc {
          label {L/R Cr.}
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(179);
 return;
} 
rkr->efx_Ring->changepar(2,(int)o->value());}
          xywh {373 453 100 10} type {Horz Knob} box FLAT_BOX color 178 selection_color 62 labelsize 10 labelcolor 7 align 4 minimum -64 maximum 64 step 1 textcolor 7
          class SliderW
        }
        Fl_Value_Slider ring_input {
          label Input
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(180);
 return;
} 
rkr->efx_Ring->changepar(11,(int)o->value());}
          xywh {373 466 100 10} type {Horz Knob} box FLAT_BOX color 178 selection_color 62 labelsize 10 labelcolor 7 align 4 minimum 1 maximum 127 step 1 value 1 textcolor 7
          class SliderW
        }
        Fl_Value_Slider ring_level {
          label Level
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(181);
 return;
} 
rkr->efx_Ring->changepar(3,(int)o->value());}
          xywh {373 479 100 10} type {Horz Knob} box FLAT_BOX color 178 selection_color 62 labelsize 10 labelcolor 7 align 4 maximum 127 step 1 textcolor 7
          class SliderW
        }
        Fl_Value_Slider ring_pan {
          label Pan
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(182);
 return;
} 
rkr->efx_Ring->changepar(1,(int)o->value());}
          xywh {373 492 100 10} type {Horz Knob} box FLAT_BOX color 178 selection_color 62 labelsize 10 labelcolor 7 align 4 minimum -64 maximum 64 step 1 textcolor 7
          class SliderW
        }
        Fl_Check_Button ring_st {
          label Stereo
          user_data 2
          callback {rkr->efx_Ring->changepar(6,(int)o->value());}
          xywh {350 503 52 15} down_box BORDER_BOX labelsize 10 labelcolor 7
        }
        Fl_Check_Button ring_afreq {
          label {Auto Freq}
          user_data 2
          callback {rkr->efx_Ring->changepar(12,(int)o->value());}
          xywh {402 503 69 15} down_box BORDER_BOX labelsize 10 labelcolor 7
        }
        Fl_Value_Slider ring_depth {
          label Depth
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(183);
 return;
} 
rkr->efx_Ring->changepar(4,(int)o->value());}
          xywh {373 517 100 10} type {Horz Knob} box FLAT_BOX color 178 selection_color 62 labelsize 10 labelcolor 7 align 4 maximum 100 step 1 textcolor 7
          class SliderW
        }
        Fl_Value_Slider ring_freq {
          label Freq
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(184);
 return;
} 
rkr->efx_Ring->changepar(5,(int)o->value());}
          xywh {373 529 100 10} type {Horz Knob} box FLAT_BOX color 178 selection_color 62 labelsize 10 labelcolor 7 align 4 minimum 1 maximum 20000 step 10 textcolor 7
          class SliderW
        }
        Fl_Value_Slider ring_sin {
          label Sin
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(185);
 return;
} 
rkr->efx_Ring->changepar(7,(int)o->value());}
          xywh {373 541 100 10} type {Horz Knob} box FLAT_BOX color 178 selection_color 62 labelsize 10 labelcolor 7 align 4 maximum 100 step 1 textcolor 7
          class SliderW
        }
        Fl_Value_Slider ring_tri {
          label Tri
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(186);
 return;
} 
rkr->efx_Ring->changepar(8,(int)o->value());}
          xywh {373 553 100 10} type {Horz Knob} box FLAT_BOX color 178 selection_color 62 labelsize 10 labelcolor 7 align 4 maximum 100 step 1 textcolor 7
          class SliderW
        }
        Fl_Value_Slider ring_saw {
          label Saw
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(187);
 return;
} 
rkr->efx_Ring->changepar(9,(int)o->value());}
          xywh {373 565 100 10} type {Horz Knob} box FLAT_BOX color 178 selection_color 62 labelsize 10 labelcolor 7 align 4 maximum 100 step 1 textcolor 7
          class SliderW
        }
        Fl_Value_Slider ring_squ {
          label Squ
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(188);
 return;
} 
rkr->efx_Ring->changepar(10,(int)o->value());}
          xywh {373 578 100 10} type {Horz Knob} box FLAT_BOX color 178 selection_color 62 labelsize 10 labelcolor 7 align 4 maximum 100 step 1 textcolor 7
          class SliderW
        }
      }
      Fl_Group EXCITER {
        user_data 1
        xywh {162 212 158 184} box UP_BOX color 0 selection_color 0 labelfont 1 align 112 hide
      } {
        Fl_Light_Button exciter_activar {
          label On
          user_data 2
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(116);
 o->value(rkr->Exciter_Bypass);
 return;
}
rkr->Exciter_Bypass=(int)o->value();
if((int) o->value()==0)
rkr->efx_Exciter->cleanup();
findpos(22,(int)o->value(),o);}
          xywh {167 216 34 18} shortcut 0x31 color 62 selection_color 1 labelsize 10 align 84 when 1
        }
        Fl_Choice exciter_preset {
          label Preset
          user_data 12022
          callback {long long ud= (long long) v;
if((ud==0)||(ud==12022))rkr->efx_Exciter->setpreset((int) o->value());
ex_Gain->value(rkr->efx_Exciter->getpar(0));
ex_1->value(rkr->efx_Exciter->getpar(1));
ex_2->value(rkr->efx_Exciter->getpar(2));
ex_3->value(rkr->efx_Exciter->getpar(3));
ex_4->value(rkr->efx_Exciter->getpar(4));
ex_5->value(rkr->efx_Exciter->getpar(5));
ex_6->value(rkr->efx_Exciter->getpar(6));
ex_7->value(rkr->efx_Exciter->getpar(7));
ex_8->value(rkr->efx_Exciter->getpar(8));
ex_9->value(rkr->efx_Exciter->getpar(9));
ex_10->value(rkr->efx_Exciter->getpar(10));
ex_lfreq->value(rkr->efx_Exciter->getpar(11));
ex_hfreq->value(rkr->efx_Exciter->getpar(12));}
          xywh {239 216 76 18} down_box BORDER_BOX selection_color 0 labelsize 10 labelcolor 7 when 6 textsize 10 textcolor 7
        } {
          MenuItem {} {
            label Plain
            xywh {22 22 36 21} labelsize 10
          }
          MenuItem {} {
            label Loudness
            xywh {0 0 36 21} labelsize 10
          }
          MenuItem {} {
            label {Exciter 1}
            xywh {22 22 36 21} labelsize 10
          }
          MenuItem {} {
            label {Exciter 2}
            xywh {22 22 36 21} labelsize 10
          }
          MenuItem {} {
            label {Exciter 3}
            xywh {32 32 36 21} labelsize 10
          }
        }
        Fl_Value_Slider ex_Gain {
          label Gain
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(189);
 return;
} 
rkr->efx_Exciter->changepar(0,(int)o->value());}
          xywh {211 237 100 10} type {Horz Knob} box FLAT_BOX color 178 selection_color 62 labelsize 10 labelcolor 7 align 4 maximum 127 step 1 textcolor 7
          class SliderW
        }
        Fl_Value_Slider ex_lfreq {
          label LPF
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(190);
 return;
} 
rkr->efx_Exciter->changepar(11,(int)o->value());}
          xywh {211 249 100 10} type {Horz Knob} box FLAT_BOX color 178 selection_color 62 labelsize 10 labelcolor 7 align 4 minimum 20 maximum 26000 step 1 value 20000 textcolor 7
          class SliderW
        }
        Fl_Value_Slider ex_hfreq {
          label HPF
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(191);
 return;
} 
rkr->efx_Exciter->changepar(12,(int)o->value());}
          xywh {211 261 100 10} type {Horz Knob} box FLAT_BOX color 178 selection_color 62 labelsize 10 labelcolor 7 align 4 minimum 20 maximum 20000 step 1 value 20 textcolor 7
          class SliderW
        }
        Fl_Value_Slider ex_1 {
          label {Har 1}
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(192);
 return;
} 
rkr->efx_Exciter->changepar(1,(int)o->value());}
          xywh {211 273 100 10} type {Horz Knob} box FLAT_BOX color 178 selection_color 62 labelsize 10 labelcolor 7 align 4 minimum -64 maximum 64 step 1 textcolor 7
          class SliderW
        }
        Fl_Value_Slider ex_2 {
          label {Har 2}
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(193);
 return;
} 
rkr->efx_Exciter->changepar(2,(int)o->value());}
          xywh {211 285 100 10} type {Horz Knob} box FLAT_BOX color 178 selection_color 62 labelsize 10 labelcolor 7 align 4 minimum -64 maximum 64 step 1 textcolor 7
          class SliderW
        }
        Fl_Value_Slider ex_3 {
          label {Har 3}
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(194);
 return;
} 
rkr->efx_Exciter->changepar(3,(int)o->value());}
          xywh {211 297 100 10} type {Horz Knob} box FLAT_BOX color 178 selection_color 62 labelsize 10 labelcolor 7 align 4 minimum -64 maximum 64 step 1 textcolor 7
          class SliderW
        }
        Fl_Value_Slider ex_4 {
          label {Har 4}
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(195);
 return;
} 
rkr->efx_Exciter->changepar(4,(int)o->value());}
          xywh {211 309 100 10} type {Horz Knob} box FLAT_BOX color 178 selection_color 62 labelsize 10 labelcolor 7 align 4 minimum -64 maximum 64 step 1 textcolor 7
          class SliderW
        }
        Fl_Value_Slider ex_5 {
          label {Har 5}
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(196);
 return;
} 
rkr->efx_Exciter->changepar(5,(int)o->value());}
          xywh {211 321 100 10} type {Horz Knob} box FLAT_BOX color 178 selection_color 62 labelsize 10 labelcolor 7 align 4 minimum -64 maximum 64 step 1 textcolor 7
          class SliderW
        }
        Fl_Value_Slider ex_6 {
          label {Har 6}
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(197);
 return;
} 
rkr->efx_Exciter->changepar(6,(int)o->value());}
          xywh {211 333 100 10} type {Horz Knob} box FLAT_BOX color 178 selection_color 62 labelsize 10 labelcolor 7 align 4 minimum -64 maximum 64 step 1 textcolor 7
          class SliderW
        }
        Fl_Value_Slider ex_7 {
          label {Har 7}
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(198);
 return;
} 
rkr->efx_Exciter->changepar(7,(int)o->value());}
          xywh {211 346 100 10} type {Horz Knob} box FLAT_BOX color 178 selection_color 62 labelsize 10 labelcolor 7 align 4 minimum -64 maximum 64 step 1 textcolor 7
          class SliderW
        }
        Fl_Value_Slider ex_8 {
          label {Har 8}
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(199);
 return;
} 
rkr->efx_Exciter->changepar(8,(int)o->value());}
          xywh {211 358 100 10} type {Horz Knob} box FLAT_BOX color 178 selection_color 62 labelsize 10 labelcolor 7 align 4 minimum -64 maximum 64 step 1 textcolor 7
          class SliderW
        }
        Fl_Value_Slider ex_9 {
          label {Har 9}
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(200);
 return;
} 
rkr->efx_Exciter->changepar(9,(int)o->value());}
          xywh {211 370 100 10} type {Horz Knob} box FLAT_BOX color 178 selection_color 62 labelsize 10 labelcolor 7 align 4 minimum -64 maximum 64 step 1 textcolor 7
          class SliderW
        }
        Fl_Value_Slider ex_10 {
          label {Har 10}
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(201);
 return;
} 
rkr->efx_Exciter->changepar(10,(int)o->value());}
          xywh {211 381 100 10} type {Horz Knob} box FLAT_BOX color 178 selection_color 62 labelsize 10 labelcolor 7 align 4 minimum -64 maximum 64 step 1 textcolor 7
          class SliderW
        }
      }
      Fl_Group MBDIST {
        user_data 1
        xywh {480 211 158 184} box UP_BOX color 0 selection_color 0 labelfont 1 align 112 hide
      } {
        Fl_Light_Button mbdist_activar {
          label On
          user_data 2
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(116);
 o->value(rkr->MBDist_Bypass);
 return;
}
rkr->MBDist_Bypass=(int)o->value();
if((int) o->value()==0)
rkr->efx_MBDist->cleanup();
findpos(23,(int)o->value(),o);}
          xywh {485 215 34 18} shortcut 0x33 color 62 selection_color 1 labelsize 10 align 84 when 1
        }
        Fl_Choice mbdist_preset {
          label Preset
          user_data 12023
          callback {long long ud= (long long) v;
if((ud==0)||(ud==12023))rkr->efx_MBDist->setpreset((int)o->value());
mbdist_WD->value(rkr->efx_MBDist->getpar(0)-64);
mbdist_LRc->value(rkr->efx_MBDist->getpar(2)-64);
mbdist_drive->value(rkr->efx_MBDist->getpar(3));
mbdist_level->value(rkr->efx_MBDist->getpar(4));
mbdist_tipoL->value(rkr->efx_MBDist->getpar(5));
mbdist_tipoM->value(rkr->efx_MBDist->getpar(6));
mbdist_tipoH->value(rkr->efx_MBDist->getpar(7));
mbdist_volL->value(rkr->efx_MBDist->getpar(8));
mbdist_volM->value(rkr->efx_MBDist->getpar(9));
mbdist_volH->value(rkr->efx_MBDist->getpar(10));
mbdist_neg->value(rkr->efx_MBDist->getpar(11));
mbdist_st->value(rkr->efx_MBDist->getpar(14));
mbdist_pan->value(rkr->efx_MBDist->getpar(1)-64);
mbdist_cross1->value(rkr->efx_MBDist->getpar(12));
mbdist_cross2->value(rkr->efx_MBDist->getpar(13));}
          xywh {557 215 76 18} down_box BORDER_BOX selection_color 0 labelsize 10 labelcolor 7 when 6 textsize 10 textcolor 7
        } {
          MenuItem {} {
            label Saturation
            xywh {0 0 36 21} labelsize 10
          }
          MenuItem {} {
            label {Distorsion 1}
            xywh {42 42 36 21} labelsize 10
          }
          MenuItem {} {
            label Soft
            xywh {42 42 36 21} labelsize 10
          }
          MenuItem {} {
            label Modulated
            xywh {52 52 36 21} labelsize 10
          }
          MenuItem {} {
            label Crunch
            xywh {42 42 36 21} labelsize 10
          }
          MenuItem {} {
            label {Distortion 2}
            xywh {0 0 36 21} labelsize 10
          }
          MenuItem {} {
            label {Distortion 3}
            xywh {0 0 36 21} labelsize 10
          }
          MenuItem {} {
            label {Distortion 4}
            xywh {0 0 36 21} labelsize 10
          }
        }
        Fl_Value_Slider mbdist_WD {
          label {Wet/Dry}
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(202);
 return;
} 
rkr->efx_MBDist->changepar(0,(int)(o->value()+64));}
          xywh {532 237 100 10} type {Horz Knob} box FLAT_BOX color 178 selection_color 62 labelsize 10 labelcolor 7 align 4 minimum -64 maximum 64 step 1 textcolor 7
          class SliderW
        }
        Fl_Value_Slider mbdist_LRc {
          label {L/R.Cr}
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(203);
 return;
} 
rkr->efx_MBDist->changepar(2,(int)(o->value()+64));}
          xywh {532 249 100 10} type {Horz Knob} box FLAT_BOX color 178 selection_color 62 labelsize 10 labelcolor 7 align 4 minimum -64 maximum 64 step 1 textcolor 7
          class SliderW
        }
        Fl_Value_Slider mbdist_drive {
          label Drive
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(204);
 return;
} 
rkr->efx_MBDist->changepar(3,(int)o->value());}
          xywh {532 261 100 10} type {Horz Knob} box FLAT_BOX color 178 selection_color 62 labelsize 10 labelcolor 7 align 4 maximum 127 step 1 textcolor 7
          class SliderW
        }
        Fl_Value_Slider mbdist_level {
          label Level
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(205);
 return;
} 
rkr->efx_MBDist->changepar(4,(int)o->value());}
          xywh {532 273 100 10} type {Horz Knob} box FLAT_BOX color 178 selection_color 62 labelsize 10 labelcolor 7 align 4 maximum 127 step 1 textcolor 7
          class SliderW
        }
        Fl_Value_Slider mbdist_volL {
          label {L.Gain}
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(206);
 return;
} 
rkr->efx_MBDist->changepar(8,(int)o->value());}
          xywh {532 287 100 10} type {Horz Knob} box FLAT_BOX color 178 selection_color 62 labelsize 10 labelcolor 7 align 4 maximum 100 step 1 textcolor 7
          class SliderW
        }
        Fl_Value_Slider mbdist_volM {
          label {M.Gain}
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(207);
 return;
} 
rkr->efx_MBDist->changepar(9,(int)o->value());}
          xywh {532 300 100 10} type {Horz Knob} box FLAT_BOX color 178 selection_color 62 labelsize 10 labelcolor 7 align 4 maximum 100 step 1 textcolor 7
          class SliderW
        }
        Fl_Value_Slider mbdist_volH {
          label {H. Gain}
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(208);
 return;
} 
rkr->efx_MBDist->changepar(10,(int)o->value());}
          xywh {532 313 100 10} type {Horz Knob} box FLAT_BOX color 178 selection_color 62 labelsize 10 labelcolor 7 align 4 maximum 100 step 1 textcolor 7
          class SliderW
        }
        Fl_Value_Slider mbdist_cross1 {
          label Cross1
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(209);
 return;
} 
rkr->efx_MBDist->changepar(12,(int)o->value());}
          xywh {532 326 100 10} type {Horz Knob} box FLAT_BOX color 178 selection_color 62 labelsize 10 labelcolor 7 align 4 minimum 20 maximum 1000 step 1 textcolor 7
          class SliderW
        }
        Fl_Value_Slider mbdist_cross2 {
          label Cross2
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(210);
 return;
} 
rkr->efx_MBDist->changepar(13,(int)o->value());}
          xywh {532 338 100 10} type {Horz Knob} box FLAT_BOX color 178 selection_color 62 labelsize 10 labelcolor 7 align 4 minimum 800 maximum 12000 step 1 textcolor 7
          class SliderW
        }
        Fl_Choice mbdist_tipoL {
          callback {rkr->efx_MBDist->changepar(5,(int)o->value());} open
          xywh {483 350 50 16} down_box BORDER_BOX selection_color 0 labelsize 10 labelcolor 7 textsize 10 textcolor 7
          code0 {o->menu(menu_dist_tipo);}
        } {}
        Fl_Choice mbdist_tipoM {
          callback {rkr->efx_MBDist->changepar(6,(int)o->value());} open
          xywh {534 350 50 16} down_box BORDER_BOX selection_color 0 labelsize 10 labelcolor 7 textsize 10 textcolor 7
          code0 {o->menu(menu_dist_tipo);}
        } {}
        Fl_Choice mbdist_tipoH {
          callback {rkr->efx_MBDist->changepar(7,(int)o->value());} open
          xywh {585 350 50 16} down_box BORDER_BOX selection_color 0 labelsize 10 labelcolor 7 textsize 10 textcolor 7
          code0 {o->menu(menu_dist_tipo);}
        } {}
        Fl_Value_Slider mbdist_pan {
          label Pan
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(211);
 return;
} 
rkr->efx_MBDist->changepar(1,(int)(o->value()+64));}
          xywh {532 369 100 10} type {Horz Knob} box FLAT_BOX color 178 selection_color 62 labelsize 10 labelcolor 7 align 4 minimum -64 maximum 64 step 1 textcolor 7
          class SliderW
        }
        Fl_Check_Button mbdist_st {
          label Stereo
          user_data 2
          callback {rkr->efx_MBDist->changepar(14,(int)o->value());}
          xywh {512 379 54 15} down_box BORDER_BOX labelsize 10 labelcolor 7
        }
        Fl_Check_Button mbdist_neg {
          label {Neg.}
          user_data 2
          callback {rkr->efx_MBDist->changepar(11,(int)o->value());}
          xywh {581 378 44 15} down_box BORDER_BOX labelsize 10 labelcolor 7
        }
      }
      Fl_Group ARPIE {
        user_data 1
        xywh {161 211 158 184} box UP_BOX color 0 selection_color 0 labelfont 1 align 112 hide
      } {
        Fl_Light_Button arpie_activar {
          label On
          user_data 2
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(116);
 o->value(rkr->Arpie_Bypass);
 return;
}
rkr->Arpie_Bypass=(int)o->value();
if((int) o->value()==0)
rkr->efx_Arpie->cleanup();
findpos(24,(int)o->value(),o);}
          xywh {166 215 34 18} shortcut 0x35 color 62 selection_color 1 labelsize 10 align 84 when 1
        }
        Fl_Choice arpie_preset {
          label Preset
          user_data 12024
          callback {long long ud= (long long) v;
if((ud==0)||(ud==12024))rkr->efx_Arpie->setpreset((int) o->value());
arpie_WD->value(rkr->efx_Arpie->getpar(0)-64);
arpie_pan->value(rkr->efx_Arpie->getpar(1)-64);
arpie_delay->value(rkr->efx_Arpie->getpar(2));
arpie_LRdl->value(rkr->efx_Arpie->getpar(3));
arpie_LRc->value(rkr->efx_Arpie->getpar(4)-64);
arpie_fb->value(rkr->efx_Arpie->getpar(5));
arpie_damp->value(rkr->efx_Arpie->getpar(6));
arpie_arpe->value(rkr->efx_Arpie->getpar(7));
arpie_harm->value(rkr->efx_Arpie->getpar(8));
arpie_pattern->value(rkr->efx_Arpie->getpar(9));
arpie_subdiv->value(rkr->efx_Arpie->getpar(10));}
          xywh {238 215 76 18} down_box BORDER_BOX selection_color 0 labelsize 10 labelcolor 7 when 6 textsize 10 textcolor 7
        } {
          MenuItem {} {
            label {Arpie 1}
            xywh {67 67 36 21} labelsize 10
          }
          MenuItem {} {
            label {Arpie 2}
            xywh {67 67 36 21} labelsize 10
          }
          MenuItem {} {
            label {Arpie 3}
            xywh {67 67 36 21} labelsize 10
          }
          MenuItem {} {
            label {Simple Arpie}
            xywh {77 77 36 21} labelsize 10
          }
          MenuItem {} {
            label Canyon
            xywh {87 87 36 21} labelsize 10
          }
          MenuItem {} {
            label {Panning Arpie 1}
            xywh {107 107 36 21} labelsize 10
          }
          MenuItem {} {
            label {Panning Arpie 2}
            xywh {117 117 36 21} labelsize 10
          }
          MenuItem {} {
            label {Panning Arpie 3}
            xywh {127 127 36 21} labelsize 10
          }
          MenuItem {} {
            label {Feedback Arpie}
            xywh {137 137 36 21} labelsize 10
          }
        }
        Fl_Value_Slider arpie_WD {
          label {Wet/Dry}
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(212);
 return;
} 
rkr->efx_Arpie->changepar(0,(int)(o->value()+64));}
          xywh {212 239 100 10} type {Horz Knob} box FLAT_BOX color 178 selection_color 62 labelsize 10 labelcolor 7 align 4 minimum -64 maximum 63 step 1 textcolor 7
          class SliderW
        }
        Fl_Value_Slider arpie_arpe {
          label {Arpe's}
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(213);
 return;
} 
rkr->efx_Arpie->changepar(7,(int)o->value());}
          xywh {212 253 100 10} type {Horz Knob} box FLAT_BOX color 178 selection_color 62 labelsize 10 labelcolor 7 align 4 maximum 127 step 1 textcolor 7
          class SliderW
        }
        Fl_Value_Slider arpie_pan {
          label Pan
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(214);
 return;
} 
rkr->efx_Arpie->changepar(1,(int)(o->value()+64));}
          xywh {212 267 100 10} type {Horz Knob} box FLAT_BOX color 178 selection_color 62 labelsize 10 labelcolor 7 align 4 minimum -64 maximum 63 step 1 textcolor 7
          class SliderW
        }
        Fl_Value_Slider arpie_delay {
          label Tempo
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(215);
 return;
} 
rkr->efx_Arpie->changepar(2,(int)o->value());}
          xywh {212 281 100 10} type {Horz Knob} box FLAT_BOX color 178 selection_color 62 labelsize 10 labelcolor 7 align 4 when 4 minimum 1 maximum 600 step 1 value 1 textcolor 7
          class SliderW
        }
        Fl_Choice arpie_subdiv {
          label SubDivision
          user_data 12
          callback {rkr->efx_Arpie->changepar(10,(int)o->value());}
          xywh {239 293 76 18} down_box BORDER_BOX selection_color 0 labelsize 10 labelcolor 7 when 6 textsize 10 textcolor 7
        } {
          MenuItem {} {
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
          }
        }
        Fl_Value_Slider arpie_LRdl {
          label {LRdl.}
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(216);
 return;
} 
rkr->efx_Arpie->changepar(3,(int)o->value());}
          xywh {212 314 100 10} type {Horz Knob} box FLAT_BOX color 178 selection_color 62 labelsize 10 labelcolor 7 align 4 when 4 maximum 127 step 1 textcolor 7
          class SliderW
        }
        Fl_Value_Slider arpie_LRc {
          label {L/R.Cr}
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(217);
 return;
} 
rkr->efx_Arpie->changepar(4,(int)(o->value()+64));}
          xywh {212 329 100 10} type {Horz Knob} box FLAT_BOX color 178 selection_color 62 labelsize 10 labelcolor 7 align 4 minimum -64 maximum 63 step 1 textcolor 7
          class SliderW
        }
        Fl_Value_Slider arpie_fb {
          label {Fb.}
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(218);
 return;
} 
rkr->efx_Arpie->changepar(5,(int)o->value());}
          xywh {212 344 100 10} type {Horz Knob} box FLAT_BOX color 178 selection_color 62 labelsize 10 labelcolor 7 align 4 maximum 127 step 1 textcolor 7
          class SliderW
        }
        Fl_Value_Slider arpie_damp {
          label Damp
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(219);
 return;
} 
rkr->efx_Arpie->changepar(6,(int)o->value());}
          xywh {212 378 100 10} type {Horz Knob} box FLAT_BOX color 178 selection_color 62 labelsize 10 labelcolor 7 align 4 maximum 127 step 1 textcolor 7
          class SliderW
        }
        Fl_Counter arpie_harm {
          label H
          callback {rkr->efx_Arpie->changepar(8,(int)o->value());}
          tooltip {Number of steps in the pattern} xywh {181 361 52 12} type Simple box THIN_UP_BOX labelsize 10 labelcolor 7 align 4 minimum 1 maximum 8 step 1 value 1 textsize 9
        }
        Fl_Choice arpie_pattern {
          user_data 12
          callback {rkr->efx_Arpie->changepar(9,(int)o->value());}
          xywh {238 358 76 18} down_box BORDER_BOX selection_color 0 labelsize 10 labelcolor 7 when 6 textsize 10 textcolor 7
        } {
          MenuItem {} {
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
          }
        }
      }
      Fl_Group EXPANDER {
        user_data 1
        xywh {321 211 158 184} box UP_BOX color 0 selection_color 0 labelfont 1 align 112 hide
      } {
        Fl_Light_Button expander_activar {
          label On
          user_data 2
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(116);
 o->value(rkr->Expander_Bypass);
 return;
}
rkr->Expander_Bypass=(int)o->value();
findpos(25,(int)o->value(),o);}
          xywh {326 215 34 18} shortcut 0x32 color 62 selection_color 1 labelsize 10 align 84 when 1
        }
        Fl_Choice expander_preset {
          label Preset
          user_data 12025
          callback {long long ud= (long long) v;
if((ud==0)||(ud==12025))rkr->efx_Expander->Expander_Change_Preset((int) o->value());
expander_ATime->value(rkr->efx_Expander->getpar(3));
expander_RTime->value(rkr->efx_Expander->getpar(4));
expander_shape->value(rkr->efx_Expander->getpar(2));
expander_threshold->value(rkr->efx_Expander->getpar(1));
expander_HPF->value(rkr->efx_Expander->getpar(6));
expander_LPF->value(rkr->efx_Expander->getpar(5));
expander_level->value(rkr->efx_Expander->getpar(7));}
          xywh {398 215 76 18} down_box BORDER_BOX selection_color 0 labelsize 10 labelcolor 7 when 6 textsize 10 textcolor 7
        } {
          MenuItem {} {
            label {Noise Gate}
            xywh {52 52 36 21} labelsize 10
          }
          MenuItem {} {
            label {Boost Gate}
            xywh {52 52 36 21} labelsize 10
          }
          MenuItem {} {
            label {Treble swell}
            xywh {52 52 36 21} labelsize 10
          }
        }
        Fl_Value_Slider expander_ATime {
          label {A. Time}
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(220);
 return;
} 
rkr->efx_Expander->Expander_Change(3,(int)o->value());}
          xywh {372 250 100 10} type {Horz Knob} box FLAT_BOX color 178 selection_color 62 labelsize 10 labelcolor 7 align 4 minimum 10 maximum 2000 step 1 value 10 textcolor 7
          class SliderW
        }
        Fl_Value_Slider expander_RTime {
          label {R. Time}
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(221);
 return;
} 
rkr->efx_Expander->Expander_Change(4,(int) o->value());}
          xywh {371 272 100 10} type {Horz Knob} box FLAT_BOX color 178 selection_color 62 labelsize 10 labelcolor 7 align 4 minimum 10 maximum 500 step 1 value 500 textcolor 7
          class SliderW
        }
        Fl_Value_Slider expander_shape {
          label Shape
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(222);
 return;
} 
rkr->efx_Expander->Expander_Change(2, (int) o->value());}
          xywh {371 294 100 10} type {Horz Knob} box FLAT_BOX color 178 selection_color 62 labelsize 10 labelcolor 7 align 4 minimum 1 maximum 50 step 1 value 1 textcolor 7
          class SliderW
        }
        Fl_Value_Slider expander_threshold {
          label Thrhold
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(223);
 return;
} 
rkr->efx_Expander->Expander_Change(1, (int)o->value());}
          xywh {371 316 100 10} type {Horz Knob} box FLAT_BOX color 178 selection_color 62 labelsize 10 labelcolor 7 align 4 minimum -80 maximum 0 step 1 textcolor 7
          class SliderW
        }
        Fl_Value_Slider expander_level {
          label Level
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(224);
 return;
} 
rkr->efx_Expander->Expander_Change(7, (int) o->value());}
          xywh {371 336 100 10} type {Horz Knob} box FLAT_BOX color 178 selection_color 62 labelsize 10 labelcolor 7 align 4 minimum 1 maximum 127 step 1 value 1 textcolor 7
          class SliderW
        }
        Fl_Value_Slider expander_LPF {
          label LPF
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(225);
 return;
} 
rkr->efx_Expander->Expander_Change(5, (int)o->value());}
          xywh {371 357 100 10} type {Horz Knob} box FLAT_BOX color 178 selection_color 62 labelsize 10 labelcolor 7 align 4 minimum 20 maximum 26000 step 1 value 20000 textcolor 7
          class SliderW
        }
        Fl_Value_Slider expander_HPF {
          label HPF
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(226);
 return;
} 
rkr->efx_Expander->Expander_Change(6, (int)o->value());}
          xywh {371 373 100 10} type {Horz Knob} box FLAT_BOX color 178 selection_color 62 labelsize 10 labelcolor 7 align 4 minimum 20 maximum 20000 step 1 value 20 textcolor 7
          class SliderW
        }
      }
      Fl_Group SHUFFLE {
        label {High Freq}
        user_data 1
        xywh {480 211 158 184} box UP_BOX color 0 selection_color 0 labelfont 1 align 112 hide
      } {
        Fl_Light_Button shuffle_activar {
          label On
          user_data 2
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(116);
 o->value(rkr->Shuffle_Bypass);
 return;
}
rkr->Shuffle_Bypass=(int)o->value();
if((int) o->value()==0)
rkr->efx_Shuffle->cleanup();
findpos(26,(int)o->value(),o);}
          xywh {485 215 34 18} shortcut 0x33 color 62 selection_color 1 labelsize 10 align 84 when 1
        }
        Fl_Choice shuffle_preset {
          label Preset
          user_data 12026
          callback {long long ud= (long long) v;
if((ud==0)||(ud==12026))rkr->efx_Shuffle->setpreset((int)o->value());
shuffle_volL->value(rkr->efx_Shuffle->getpar(1));
shuffle_volML->value(rkr->efx_Shuffle->getpar(2));
shuffle_volMH->value(rkr->efx_Shuffle->getpar(2));
shuffle_volH->value(rkr->efx_Shuffle->getpar(4));
shuffle_cross1->value(rkr->efx_Shuffle->getpar(5));
shuffle_cross2->value(rkr->efx_Shuffle->getpar(6));
shuffle_cross3->value(rkr->efx_Shuffle->getpar(7));
shuffle_cross4->value(rkr->efx_Shuffle->getpar(8));
shuffle_Q->value(rkr->efx_Shuffle->getpar(9));
shuffle_WD->value(rkr->efx_Shuffle->getpar(0)-64);
shuffle_E->value(rkr->efx_Shuffle->getpar(10));}
          xywh {557 215 76 18} down_box BORDER_BOX selection_color 0 labelsize 10 labelcolor 7 when 6 textsize 10 textcolor 7
        } {
          MenuItem {} {
            label {Shuffle 1}
            xywh {52 52 36 21} labelsize 10
          }
          MenuItem {} {
            label {Shuffle 2}
            xywh {52 52 36 21} labelsize 10
          }
          MenuItem {} {
            label {Shuffle 3}
            xywh {62 62 36 21} labelsize 10
          }
          MenuItem {} {
            label Remover
            xywh {72 72 36 21} labelsize 10
          }
        }
        Fl_Value_Slider shuffle_WD {
          label {Wet/Dry}
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(227);
 return;
} 
rkr->efx_Shuffle->changepar(0,(int)o->value()+64);}
          xywh {535 242 100 10} type {Horz Knob} box FLAT_BOX color 178 selection_color 62 labelsize 10 labelcolor 7 align 4 minimum -64 maximum 64 step 1 textcolor 7
          class SliderW
        }
        Fl_Value_Slider shuffle_cross1 {
          label {Low Freq}
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(228);
 return;
} 
rkr->efx_Shuffle->changepar(5,(int)o->value());}
          xywh {535 260 100 10} type {Horz Knob} box FLAT_BOX color 178 selection_color 62 labelsize 10 labelcolor 7 align 4 minimum 20 maximum 1000 step 1 textcolor 7
          class SliderW
        }
        Fl_Value_Slider shuffle_volL {
          label {Low Gain}
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(229);
 return;
} 
rkr->efx_Shuffle->changepar(1,(int)o->value());}
          xywh {535 275 100 10} type {Horz Knob} box FLAT_BOX color 178 selection_color 62 labelsize 10 labelcolor 7 align 4 minimum -64 maximum 64 step 1 textcolor 7
          class SliderW
        }
        Fl_Value_Slider shuffle_cross2 {
          label {M.L. Freq}
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(230);
 return;
} 
rkr->efx_Shuffle->changepar(6,(int)o->value());}
          xywh {535 290 100 10} type {Horz Knob} box FLAT_BOX color 178 selection_color 62 labelsize 10 labelcolor 7 align 4 minimum 400 maximum 4000 step 1 textcolor 7
          class SliderW
        }
        Fl_Value_Slider shuffle_volML {
          label {M.L Gain}
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(231);
 return;
}
rkr->efx_Shuffle->changepar(2,(int)o->value());}
          xywh {535 305 100 10} type {Horz Knob} box FLAT_BOX color 178 selection_color 62 labelsize 10 labelcolor 7 align 4 minimum -64 maximum 64 step 1 textcolor 7
          class SliderW
        }
        Fl_Value_Slider shuffle_cross3 {
          label {M.H. Freq}
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(232);
 return;
}
rkr->efx_Shuffle->changepar(7,(int)o->value());}
          xywh {535 320 100 10} type {Horz Knob} box FLAT_BOX color 178 selection_color 62 labelsize 10 labelcolor 7 align 4 minimum 1200 maximum 8000 step 1 textcolor 7
          class SliderW
        }
        Fl_Value_Slider shuffle_volMH {
          label {M.L Gain}
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(233);
 return;
}
rkr->efx_Shuffle->changepar(3,(int)o->value());}
          xywh {535 335 100 10} type {Horz Knob} box FLAT_BOX color 178 selection_color 62 labelsize 10 labelcolor 7 align 4 minimum -64 maximum 64 step 1 textcolor 7
          class SliderW
        }
        Fl_Value_Slider shuffle_cross4 {
          label {High Freq}
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(234);
 return;
}
rkr->efx_Shuffle->changepar(8,(int)o->value());}
          xywh {535 350 100 10} type {Horz Knob} box FLAT_BOX color 178 selection_color 62 labelsize 10 labelcolor 7 align 4 minimum 6000 maximum 26000 step 1 textcolor 7
          class SliderW
        }
        Fl_Value_Slider shuffle_volH {
          label {High Gain}
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(235);
 return;
}
rkr->efx_Shuffle->changepar(4,(int)o->value());}
          xywh {535 365 100 10} type {Horz Knob} box FLAT_BOX color 178 selection_color 62 labelsize 10 labelcolor 7 align 4 minimum -64 maximum 64 step 1 textcolor 7
          class SliderW
        }
        Fl_Value_Slider shuffle_Q {
          label Q
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(236);
 return;
}
rkr->efx_Shuffle->changepar(9,(int)o->value());}
          xywh {535 380 100 10} type {Horz Knob} box FLAT_BOX color 178 selection_color 62 labelsize 10 labelcolor 7 align 4 minimum -64 maximum 64 step 1 textcolor 7
          class SliderW
        }
        Fl_Check_Button shuffle_E {
          label Rev
          user_data 2
          callback {rkr->efx_Shuffle->changepar(10,(int)o->value());}
          xywh {482 378 40 15} down_box BORDER_BOX labelsize 10 labelcolor 7
        }
      }
      Fl_Group SYNTHFILTER {
        user_data 1
        xywh {319 211 158 184} box UP_BOX color 0 selection_color 0 labelfont 1 align 112 hide
      } {
        Fl_Light_Button synthfilter_activar {
          label On
          user_data 2
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(116);
 o->value(rkr->Synthfilter_Bypass);
 return;
}
rkr->Synthfilter_Bypass=(int)o->value();
if((int) o->value()==0)
rkr->efx_Synthfilter->cleanup();
findpos(27,(int)o->value(),o);}
          xywh {324 215 34 18} shortcut 0x37 color 62 selection_color 1 labelsize 10 align 84 when 1
        }
        Fl_Choice synthfilter_preset {
          label Preset
          user_data 12027
          callback {long long ud= (long long) v;
if((ud==0)||(ud==12027))rkr->efx_Synthfilter->setpreset((int) o->value());
synthfilter_WD->value(rkr->efx_Synthfilter->getpar(0)-64);
synthfilter_Distort->value(rkr->efx_Synthfilter->getpar(1));
synthfilter_freq->value(rkr->efx_Synthfilter->getpar(2));
synthfilter_lfotype->value(rkr->efx_Synthfilter->getpar(4));
synthfilter_stdf->value(rkr->efx_Synthfilter->getpar(5));
synthfilter_width->value(rkr->efx_Synthfilter->getpar(6));
synthfilter_Lstages->value(rkr->efx_Synthfilter->getpar(8));
synthfilter_Hstages->value(rkr->efx_Synthfilter->getpar(9));
synthfilter_fb->value(rkr->efx_Synthfilter->getpar(7));
synthfilter_Offset->value(rkr->efx_Synthfilter->getpar(15));
synthfilter_subs->value(rkr->efx_Synthfilter->getpar(10));
synthfilter_dpth->value(rkr->efx_Synthfilter->getpar(11));
synthfilter_EnvSens->value(rkr->efx_Synthfilter->getpar(12));
synthfilter_ATime->value(rkr->efx_Synthfilter->getpar(13));
synthfilter_RTime->value(rkr->efx_Synthfilter->getpar(14));}
          xywh {396 215 76 18} down_box BORDER_BOX selection_color 0 labelsize 10 labelcolor 7 when 6 textsize 10 textcolor 7
        } {
          MenuItem {} {
            label {Low Pass}
            xywh {82 82 36 21} labelsize 10
          }
          MenuItem {} {
            label {High Pass}
            xywh {82 82 36 21} labelsize 10
          }
          MenuItem {} {
            label {Band Pass}
            xywh {82 82 36 21} labelsize 10
          }
          MenuItem {} {
            label {Lead Synth}
            xywh {92 92 36 21} labelsize 10
          }
          MenuItem {} {
            label Water
            xywh {0 0 36 21} labelsize 10
          }
          MenuItem {} {
            label {Pan Filter}
            xywh {0 0 36 21} labelsize 10
          }
          MenuItem {} {
            label Multi
            xywh {0 0 36 21} labelsize 10
          }
        }
        Fl_Value_Slider synthfilter_WD {
          label {Wet/Dry}
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(237);
 return;
}
rkr->efx_Synthfilter->changepar(0,(int)(o->value()+64));}
          xywh {368 236 100 10} type {Horz Knob} box FLAT_BOX color 178 selection_color 62 labelsize 10 labelcolor 7 align 4 minimum -64 maximum 63 step 1 textcolor 7
          class SliderW
        }
        Fl_Value_Slider synthfilter_Distort {
          label Distort
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(238);
 return;
}
rkr->efx_Synthfilter->changepar(1,(int)o->value());}
          xywh {368 248 100 10} type {Horz Knob} box FLAT_BOX color 178 selection_color 62 labelsize 10 labelcolor 7 align 4 maximum 127 step 1 textcolor 7
          class SliderW
        }
        Fl_Value_Slider synthfilter_freq {
          label Tempo
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(239);
 return;
}
rkr->efx_Synthfilter->changepar(2,(int)o->value());}
          xywh {368 260 100 10} type {Horz Knob} box FLAT_BOX color 178 selection_color 62 labelsize 10 labelcolor 7 align 4 minimum 1 maximum 600 step 1 textcolor 7
          class SliderW
        }
        Fl_Choice synthfilter_lfotype {
          label {LFO Type}
          callback {rkr->efx_Synthfilter->changepar(4,(int)o->value());}
          xywh {373 271 52 13} down_box BORDER_BOX selection_color 0 labelsize 10 labelcolor 7 textsize 10 textcolor 7
          code0 {o->menu(menu_chorus_lfotype);}
        } {}
        Fl_Check_Button synthfilter_subs {
          label {Subtr.}
          user_data 2
          callback {rkr->efx_Synthfilter->changepar(10,(int)o->value())}
          xywh {428 270 46 15} down_box BORDER_BOX labelsize 10 labelcolor 7
        }
        Fl_Value_Slider synthfilter_stdf {
          label {St.df}
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(240);
 return;
}
rkr->efx_Synthfilter->changepar(5,(int)o->value());}
          xywh {368 286 100 10} type {Horz Knob} box FLAT_BOX color 178 selection_color 62 labelsize 10 labelcolor 7 align 4 maximum 127 step 1 textcolor 7
          class SliderW
        }
        Fl_Value_Slider synthfilter_width {
          label Width
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(241);
 return;
}
rkr->efx_Synthfilter->changepar(6,(int)o->value());}
          xywh {368 298 100 10} type {Horz Knob} box FLAT_BOX color 178 selection_color 62 labelsize 10 labelcolor 7 align 4 maximum 127 step 1 textcolor 7
          class SliderW
        }
        Fl_Value_Slider synthfilter_fb {
          label Fb
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(242);
 return;
}
rkr->efx_Synthfilter->changepar(7,(int)o->value());}
          xywh {368 310 100 10} type {Horz Knob} box FLAT_BOX color 178 selection_color 62 labelsize 10 labelcolor 7 align 4 minimum -64 maximum 64 step 1 textcolor 7
          class SliderW
        }
        Fl_Counter synthfilter_Lstages {
          label {LPF Stg.}
          callback {rkr->efx_Synthfilter->changepar(8,(int)o->value());}
          xywh {367 322 28 11} type Simple box THIN_UP_BOX labelsize 10 labelcolor 7 align 4 minimum 0 maximum 12 step 1 value 1 textsize 9
        }
        Fl_Counter synthfilter_Hstages {
          label {HPF Stg.}
          callback {rkr->efx_Synthfilter->changepar(9,(int)o->value());}
          xywh {444 322 28 11} type Simple box THIN_UP_BOX labelsize 10 labelcolor 7 align 4 minimum 0 maximum 12 step 1 value 1 textsize 9
        }
        Fl_Value_Slider synthfilter_dpth {
          label Depth
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(243);
 return;
}
rkr->efx_Synthfilter->changepar(11,(int)o->value());}
          xywh {368 335 100 10} type {Horz Knob} box FLAT_BOX color 178 selection_color 62 labelsize 10 labelcolor 7 align 4 maximum 127 step 1 textcolor 7
          class SliderW
        }
        Fl_Value_Slider synthfilter_EnvSens {
          label {E.Sens}
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(244);
 return;
}
rkr->efx_Synthfilter->changepar(12,(int)(o->value()));}
          xywh {368 347 100 10} type {Horz Knob} box FLAT_BOX color 178 selection_color 62 labelsize 10 labelcolor 7 align 4 minimum -64 maximum 64 step 1 textcolor 7
          class SliderW
        }
        Fl_Value_Slider synthfilter_ATime {
          label {A.Time}
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(245);
 return;
}
rkr->efx_Synthfilter->changepar(13,(int)o->value());}
          xywh {368 359 100 10} type {Horz Knob} box FLAT_BOX color 178 selection_color 62 labelsize 10 labelcolor 7 align 4 minimum 5 maximum 1000 step 1 value 5 textcolor 7
          class SliderW
        }
        Fl_Value_Slider synthfilter_RTime {
          label {R.Time}
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(246);
 return;
}
rkr->efx_Synthfilter->changepar(14,(int)o->value());}
          xywh {368 371 100 10} type {Horz Knob} box FLAT_BOX color 178 selection_color 62 labelsize 10 labelcolor 7 align 4 minimum 5 maximum 500 step 1 value 5 textcolor 7
          class SliderW
        }
        Fl_Value_Slider synthfilter_Offset {
          label Offset
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(247);
 return;
}
rkr->efx_Synthfilter->changepar(15,(int)o->value());}
          xywh {368 383 100 10} type {Horz Knob} box FLAT_BOX color 178 selection_color 62 labelsize 10 labelcolor 7 align 4 maximum 127 step 1 textcolor 7
          class SliderW
        }
      }
      Fl_Group MBVVOL {
        user_data 1
        xywh {321 212 158 184} box UP_BOX color 0 selection_color 0 labelfont 1 align 112 hide
      } {
        Fl_Light_Button mbvvol_activar {
          label On
          user_data 2
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(116);
 o->value(rkr->MBVvol_Bypass);
 return;
}
rkr->MBVvol_Bypass=(int)o->value();
if((int) o->value()==0)
rkr->efx_MBVvol->cleanup();
findpos(28,(int)o->value(),o);}
          xywh {326 216 34 18} shortcut 0x38 color 62 selection_color 1 labelsize 10 align 84 when 1
        }
        Fl_Choice mbvvol_preset {
          label Preset
          user_data 12028
          callback {long long ud= (long long) v;
if((ud==0)||(ud==12028))rkr->efx_MBVvol->setpreset((int)o->value());
mbvvol_WD->value(rkr->efx_MBVvol->getpar(0)-64);
mbvvol_freq1->value(rkr->efx_MBVvol->getpar(1));
mbvvol_lfotype1->value(rkr->efx_MBVvol->getpar(2));
mbvvol_stdf1->value(rkr->efx_MBVvol->getpar(3));
mbvvol_freq2->value(rkr->efx_MBVvol->getpar(4));
mbvvol_lfotype2->value(rkr->efx_MBVvol->getpar(5));
mbvvol_stdf2->value(rkr->efx_MBVvol->getpar(6));
mbvvol_cross1->value(rkr->efx_MBVvol->getpar(7));
mbvvol_cross2->value(rkr->efx_MBVvol->getpar(8));
mbvvol_cross3->value(rkr->efx_MBVvol->getpar(9));
mbvvol_combi->value(rkr->efx_MBVvol->getpar(10));}
          xywh {398 216 76 18} down_box BORDER_BOX selection_color 0 labelsize 10 labelcolor 7 when 6 textsize 10 textcolor 7
        } {
          MenuItem {} {
            label {VaryVol 1}
            xywh {72 72 36 21} labelsize 10
          }
          MenuItem {} {
            label {VaryVol 2}
            xywh {72 72 36 21} labelsize 10
          }
          MenuItem {} {
            label {VaryVol 3}
            xywh {72 72 36 21} labelsize 10
          }
        }
        Fl_Value_Slider mbvvol_WD {
          label {Wet/Dry}
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(248);
 return;
}
rkr->efx_MBVvol->changepar(0,(int)(o->value()+64));}
          xywh {373 239 100 10} type {Horz Knob} box FLAT_BOX color 178 selection_color 62 labelsize 10 labelcolor 7 align 4 minimum -64 maximum 63 step 1 textcolor 7
          class SliderW
        }
        Fl_Value_Slider mbvvol_freq1 {
          label {Tempo 1}
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(249);
 return;
}
rkr->efx_MBVvol->changepar(1,(int)o->value());}
          xywh {373 251 100 10} type {Horz Knob} box FLAT_BOX color 178 selection_color 62 labelsize 10 labelcolor 7 align 4 minimum 1 maximum 600 step 1 textcolor 7
          class SliderW
        }
        Fl_Choice mbvvol_lfotype1 {
          label {LFO 1 Type}
          callback {rkr->efx_MBVvol->changepar(2,(int)o->value());}
          xywh {384 264 72 16} down_box BORDER_BOX selection_color 0 labelsize 10 labelcolor 7 textsize 10 textcolor 7
          code0 {o->menu(menu_chorus_lfotype);}
        } {}
        Fl_Value_Slider mbvvol_stdf1 {
          label {St.df 1}
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(250);
 return;
}
rkr->efx_MBVvol->changepar(3,(int)o->value());}
          xywh {373 283 100 10} type {Horz Knob} box FLAT_BOX color 178 selection_color 62 labelsize 10 labelcolor 7 align 4 maximum 127 step 1 textcolor 7
          class SliderW
        }
        Fl_Value_Slider mbvvol_freq2 {
          label {Tempo 2}
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(251);
 return;
}
rkr->efx_MBVvol->changepar(4,(int)o->value());}
          xywh {373 295 100 10} type {Horz Knob} box FLAT_BOX color 178 selection_color 62 labelsize 10 labelcolor 7 align 4 minimum 1 maximum 600 step 1 textcolor 7
          class SliderW
        }
        Fl_Choice mbvvol_lfotype2 {
          label {LFO 2 Type}
          callback {rkr->efx_MBVvol->changepar(5,(int)o->value());}
          xywh {384 308 72 16} down_box BORDER_BOX selection_color 0 labelsize 10 labelcolor 7 textsize 10 textcolor 7
          code0 {o->menu(menu_chorus_lfotype);}
        } {}
        Fl_Value_Slider mbvvol_stdf2 {
          label {St.df 2}
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(252);
 return;
}
rkr->efx_MBVvol->changepar(6,(int)o->value());}
          xywh {373 327 100 10} type {Horz Knob} box FLAT_BOX color 178 selection_color 62 labelsize 10 labelcolor 7 align 4 maximum 127 step 1 textcolor 7
          class SliderW
        }
        Fl_Value_Slider mbvvol_cross1 {
          label Cross1
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(253);
 return;
}
rkr->efx_MBVvol->changepar(7,(int)o->value());}
          xywh {373 339 100 10} type {Horz Knob} box FLAT_BOX color 178 selection_color 62 labelsize 10 labelcolor 7 align 4 minimum 20 maximum 1000 step 1 textcolor 7
          class SliderW
        }
        Fl_Value_Slider mbvvol_cross2 {
          label Cross2
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(254);
 return;
}
rkr->efx_MBVvol->changepar(8,(int)o->value());}
          xywh {373 351 100 10} type {Horz Knob} box FLAT_BOX color 178 selection_color 62 labelsize 10 labelcolor 7 align 4 minimum 1000 maximum 8000 step 1 textcolor 7
          class SliderW
        }
        Fl_Value_Slider mbvvol_cross3 {
          label Cross3
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(255);
 return;
}
rkr->efx_MBVvol->changepar(9,(int)o->value());}
          xywh {373 363 100 10} type {Horz Knob} box FLAT_BOX color 178 selection_color 62 labelsize 10 labelcolor 7 align 4 minimum 2000 maximum 26000 step 1 textcolor 7
          class SliderW
        }
        Fl_Choice mbvvol_combi {
          label Combi
          user_data 12
          callback {rkr->efx_MBVvol->changepar(10,(int)o->value());}
          xywh {384 375 72 16} down_box BORDER_BOX selection_color 0 labelsize 10 labelcolor 7 textsize 10 textcolor 7
        } {
          MenuItem {} {
            label 1122
            xywh {0 0 36 21} labelsize 10
          }
          MenuItem {} {
            label 1221
            xywh {10 10 36 21} labelsize 10
          }
          MenuItem {} {
            label 1212
            xywh {20 20 36 21} labelsize 10
          }
          MenuItem {} {
            label o11o
            xywh {30 30 36 21} labelsize 10
          }
          MenuItem {} {
            label o12o
            xywh {40 40 36 21} labelsize 10
          }
          MenuItem {} {
            label x11x
            xywh {50 50 36 21} labelsize 10
          }
          MenuItem {} {
            label x12x
            xywh {60 60 36 21} labelsize 10
          }
          MenuItem {} {
            label 1oo1
            xywh {40 40 36 21} labelsize 10
          }
          MenuItem {} {
            label 1oo2
            xywh {50 50 36 21} labelsize 10
          }
          MenuItem {} {
            label 1xx1
            xywh {60 60 36 21} labelsize 10
          }
          MenuItem {} {
            label 1xx2
            xywh {70 70 36 21} labelsize 10
          }
        }
      }
      Fl_Group CONVOLOTRON {
        user_data 1 open
        xywh {322 213 158 184} box UP_BOX color 0 selection_color 0 labelfont 1 align 112 hide
      } {
        Fl_Light_Button convo_activar {
          label On
          user_data 2
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(116);
 o->value(rkr->Convol_Bypass);
 return;
}
rkr->Convol_Bypass=(int)o->value();
if((int) o->value()==0)
rkr->efx_Convol->cleanup();
findpos(29,(int)o->value(),o);}
          xywh {328 217 34 18} shortcut 0x35 color 62 selection_color 1 labelsize 10 align 84 when 1
        }
        Fl_Choice convo_preset {
          label Preset
          user_data 12029
          callback {long long ud= (long long) v;
if((ud==0)||(ud==12029))rkr->efx_Convol->setpreset((int) o->value());
convo_pan->value(rkr->efx_Convol->getpar(1)-64);
convo_level->value(rkr->efx_Convol->getpar(7));
convo_WD->value(rkr->efx_Convol->getpar(0)-64);
convo_damp->value(rkr->efx_Convol->getpar(6));
convo_fnum->value(rkr->efx_Convol->getpar(8));
convo_length->value(rkr->efx_Convol->getpar(3));
convo_user->value(rkr->efx_Convol->getpar(4));
convo_user->do_callback();
convo_safe->value(rkr->efx_Convol->getpar(2));
convo_fb->value(rkr->efx_Convol->getpar(10));}
          xywh {401 217 76 18} down_box BORDER_BOX selection_color 0 labelsize 10 labelcolor 7 when 6 textsize 10 textcolor 7
        } {
          MenuItem {} {
            label {Marshall JCM200}
            xywh {67 67 36 21} labelsize 10
          }
          MenuItem {} {
            label {Fender Superchamp}
            xywh {67 67 36 21} labelsize 10
          }
          MenuItem {} {
            label {Mesa Boogie}
            xywh {67 67 36 21} labelsize 10
          }
          MenuItem {} {
            label {Mesa Boogie 2}
            xywh {77 77 36 21} labelsize 10
          }
        }
        Fl_Value_Slider convo_WD {
          label {Wet/Dry}
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(280);
 return;
}
rkr->efx_Convol->changepar(0,(int)(o->value()+64));}
          xywh {374 243 100 10} type {Horz Knob} box FLAT_BOX color 178 selection_color 62 labelsize 10 labelcolor 7 align 4 minimum -64 maximum 64 step 1 textcolor 7
          class SliderW
        }
        Fl_Value_Slider convo_pan {
          label Pan
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(281);
 return;
}
rkr->efx_Convol->changepar(1,(int)(o->value()+64));}
          xywh {374 259 100 10} type {Horz Knob} box FLAT_BOX color 178 selection_color 62 labelsize 10 labelcolor 7 align 4 minimum -64 maximum 63 step 1 textcolor 7
          class SliderW
        }
        Fl_Value_Slider convo_level {
          label Level
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(282);
 return;
}
rkr->efx_Convol->changepar(7,(int)o->value());}
          xywh {374 275 100 10} type {Horz Knob} box FLAT_BOX color 178 selection_color 62 labelsize 10 labelcolor 7 align 4 maximum 127 step 1 textcolor 7
          class SliderW
        }
        Fl_Value_Slider convo_damp {
          label Damp
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(283);
 return;
}
rkr->efx_Convol->changepar(6,(int)o->value());}
          xywh {374 291 100 10} type {Horz Knob} box FLAT_BOX color 178 selection_color 62 labelsize 10 labelcolor 7 align 4 maximum 127 step 1 textcolor 7
          class SliderW
        }
        Fl_Value_Slider convo_fb {
          label Fb
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(284);
 return;
}
rkr->efx_Convol->changepar(10,(int)o->value());}
          xywh {374 307 100 10} type {Horz Knob} box FLAT_BOX color 178 selection_color 62 labelsize 10 labelcolor 7 align 4 minimum -64 maximum 64 step 1 textcolor 7
          class SliderW
        }
        Fl_Value_Slider convo_length {
          label Length
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(285);
 return;
}
rkr->efx_Convol->changepar(3,(int)o->value());}
          xywh {374 323 100 10} type {Horz Knob} box FLAT_BOX color 178 selection_color 62 labelsize 10 labelcolor 7 align 4 when 4 minimum 5 maximum 250 step 1 value 100 textcolor 7
          class SliderW
        }
        Fl_Check_Button convo_user {
          label User
          user_data 2
          callback {rkr->efx_Convol->changepar(4,(int)o->value());

if((int)o->value())B_wav->activate(); else B_wav->deactivate();}
          xywh {432 339 43 15} down_box BORDER_BOX labelsize 10 labelcolor 7
        }
        Fl_Check_Button convo_safe {
          label {Safe Mode}
          user_data 2
          callback {rkr->efx_Convol->changepar(2,(int)o->value())}
          xywh {341 354 73 15} down_box BORDER_BOX labelsize 10 labelcolor 7
        }
        Fl_Button B_wav {
          label Browse
          user_data 2
          callback {char *filename;
filename=fl_file_chooser("Load Wav File:","(*.wav)",NULL,0);
if (filename==NULL) return;
filename=fl_filename_setext(filename,".wav");
strcpy(rkr->efx_Convol->Filename,filename);
rkr->efx_Convol->setfile(100);}
          xywh {428 356 46 12} labelsize 10 deactivate
        }
        Fl_Choice convo_fnum {
          label Preset
          user_data 12
          callback {rkr->efx_Convol->changepar(8,(int)o->value());}
          xywh {373 372 101 16} down_box BORDER_BOX selection_color 0 labelsize 10 labelcolor 7 textsize 10 textcolor 7
        } {
          MenuItem {} {
            label {Marshall JCM200}
            xywh {44 44 36 21} labelsize 10
          }
          MenuItem {} {
            label {Fender Superchamp}
            xywh {54 54 36 21} labelsize 10
          }
          MenuItem {} {
            label {Mesa Boogie}
            xywh {0 0 36 21} labelsize 10
          }
          MenuItem {} {
            label {Mesa Boogie 2}
            xywh {0 0 36 21} labelsize 10
          }
          MenuItem {} {
            label {Marshall Plexi}
            xywh {0 0 36 21} labelsize 10
          }
          MenuItem {} {
            label Bassman
            xywh {10 10 36 21} labelsize 10
          }
          MenuItem {} {
            label JCM2000
            xywh {20 20 36 21} labelsize 10
          }
          MenuItem {} {
            label Ampeg
            xywh {30 30 36 21} labelsize 10
          }
          MenuItem {} {
            label Marshall2
            xywh {40 40 36 21} labelsize 10
          }
        }
      }
      Fl_Group LOOPER {
        user_data 1
        xywh {319 213 158 184} box UP_BOX color 0 selection_color 0 labelfont 1 align 112 hide
      } {
        Fl_Light_Button looper_activar {
          label On
          user_data 2
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(116);
 o->value(rkr->Looper_Bypass);
 return;
}
rkr->Looper_Bypass=(int)o->value();
if((int) o->value()==0)
rkr->efx_Looper->cleanup();
findpos(30,(int)o->value(),o);}
          xywh {324 217 34 18} shortcut 0x35 color 62 selection_color 1 labelsize 10 align 84 when 1
        }
        Fl_Choice looper_preset {
          label Preset
          user_data 12030
          callback {long long ud= (long long) v;
if((ud==0)||(ud==12030))rkr->efx_Looper->setpreset((int) o->value());
looper_WD->value(rkr->efx_Looper->getpar(0)-64);
looper_play->value(rkr->efx_Looper->getpar(1));
looper_record->value(rkr->efx_Looper->getpar(3));
looper_rv->value(rkr->efx_Looper->getpar(5));
looper_ap->value(rkr->efx_Looper->getpar(9));
looper_level1->value(rkr->efx_Looper->getpar(6));
looper_level2->value(rkr->efx_Looper->getpar(10));

looper_t1->value(rkr->efx_Looper->getpar(7));
looper_t2->value(rkr->efx_Looper->getpar(8));
looper_r1->value(rkr->efx_Looper->getpar(11));
looper_r2->value(rkr->efx_Looper->getpar(12));
looper_lnk->value(rkr->efx_Looper->getpar(13));
looper_Tempo->value(rkr->efx_Looper->getpar(14));
looper_bar->value(rkr->efx_Looper->getpar(15));
looper_ms->value(rkr->efx_Looper->getpar(17));}
          xywh {396 217 76 18} down_box BORDER_BOX selection_color 0 labelsize 10 labelcolor 7 when 6 textsize 10 textcolor 7
        } {
          MenuItem {} {
            label Looper
            xywh {67 67 36 21} labelsize 10
          }
          MenuItem {} {
            label Reverse
            xywh {0 0 36 21} labelsize 10
          }
        }
        Fl_Value_Slider looper_WD {
          label {Wet/Dry}
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(267);
 return;
}
rkr->efx_Looper->changepar(0,(int)(o->value()+64));}
          xywh {370 238 100 10} type {Horz Knob} box FLAT_BOX color 178 selection_color 62 labelsize 10 labelcolor 7 align 4 minimum -64 maximum 63 step 1 textcolor 7
          class SliderW
        }
        Fl_Value_Slider looper_level1 {
          label {Level 1}
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(268);
 return;
}
rkr->efx_Looper->changepar(6,(int)o->value());}
          xywh {370 250 100 10} type {Horz Knob} box FLAT_BOX color 178 selection_color 62 labelsize 10 labelcolor 7 align 4 when 4 maximum 127 step 1 textcolor 7
          class SliderW
        }
        Fl_Value_Slider looper_level2 {
          label {Level 2}
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(269);
 return;
}
rkr->efx_Looper->changepar(10,(int)o->value());}
          xywh {370 262 100 10} type {Horz Knob} box FLAT_BOX color 178 selection_color 62 labelsize 10 labelcolor 7 align 4 when 4 maximum 127 step 1 textcolor 7
          class SliderW
        }
        Fl_Value_Slider looper_Tempo {
          label Tempo
          callback {rkr->efx_Looper->changepar(14,(int)o->value());}
          xywh {370 274 100 10} type {Horz Knob} box FLAT_BOX color 178 selection_color 62 labelsize 10 labelcolor 7 align 4 when 4 minimum 20 maximum 380 step 1 value 100 textcolor 7
          class SliderW
        }
        Fl_Choice looper_bar {
          label {Time Sig.}
          callback {rkr->efx_Looper->changepar(15,(int)o->value());}
          xywh {376 286 40 15} down_box BORDER_BOX selection_color 0 labelsize 10 labelcolor 7 when 6 textsize 10 textcolor 7
        } {
          MenuItem {} {
            label {2/4}
            xywh {0 0 36 21} labelsize 9
          }
          MenuItem {} {
            label {3/4}
            xywh {10 10 36 21} labelsize 9
          }
          MenuItem {} {
            label {4/4}
            xywh {20 20 36 21} labelsize 9
          }
          MenuItem {} {
            label {5/4}
            xywh {30 30 36 21} labelsize 9
          }
          MenuItem {} {
            label {6/8}
            xywh {40 40 36 21} labelsize 9
          }
          MenuItem {} {
            label {7/8}
            xywh {50 50 36 21} labelsize 9
          }
          MenuItem {} {
            label {9/8}
            xywh {60 60 36 21} labelsize 9
          }
          MenuItem {} {
            label {11/8}
            xywh {70 70 36 21} labelsize 9
          }
        }
        Fl_Choice looper_ms {
          label MS
          callback {rkr->efx_Looper->changepar(17,(int)o->value());}
          xywh {440 286 29 15} down_box BORDER_BOX selection_color 0 labelsize 10 labelcolor 7 when 6 textsize 10 textcolor 7
        } {
          MenuItem {} {
            label N
            xywh {10 10 36 21} labelsize 9
          }
          MenuItem {} {
            label H
            xywh {20 20 36 21} labelsize 9
          }
          MenuItem {} {
            label L
            xywh {20 20 36 21} labelsize 9
          }
        }
        Fl_Check_Button looper_rv {
          label Reverse
          user_data 2
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(270);
 return;
}
rkr->efx_Looper->changepar(5,(int)o->value())}
          xywh {327 302 61 15} down_box BORDER_BOX labelsize 10 labelcolor 7
        }
        Fl_Check_Button looper_ap {
          label {Auto Play}
          user_data 2
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(271);
 return;
}
rkr->efx_Looper->changepar(9,(int)o->value())}
          xywh {397 302 67 15} down_box BORDER_BOX labelsize 10 labelcolor 7
        }
        Fl_Box Box_Play {
          label {Play/Stop}
          xywh {323 316 52 14} labelsize 10 labelcolor 7
        }
        Fl_Box Box_P {
          label Pause
          xywh {377 316 44 14} labelsize 10 labelcolor 7
        }
        Fl_Box {} {
          label Record
          xywh {428 316 44 14} labelsize 10 labelcolor 7
        }
        Fl_Button looper_play {
          label {@|>}
          user_data 2
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(272);
 return;
}
rkr->efx_Looper->changepar(1,(int)o->value());
update_looper();}
          xywh {327 330 44 22} type Toggle shortcut 0xffc2
        }
        Fl_Button looper_stop {
          label {@||}
          user_data 2
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(273);
 return;
}
rkr->efx_Looper->changepar(2,(int)o->value());
update_looper();}
          xywh {378 330 44 22} type Toggle shortcut 0xffc3
        }
        Fl_Button looper_record {
          label {@circle}
          user_data 2
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(274);
 return;
}
rkr->efx_Looper->changepar(3,(int)o->value());
update_looper();}
          xywh {428 330 44 22} type Toggle labelcolor 1
        }
        Fl_Box {} {
          label Track
          xywh {390 362 39 14} labelsize 10 labelcolor 7
        }
        Fl_Check_Button looper_r1 {
          label R1
          user_data 2
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(275);
 return;
}
rkr->efx_Looper->changepar(11,(int)o->value())}
          xywh {327 366 15 15} down_box BORDER_BOX labelsize 10 labelcolor 7 align 1
        }
        Fl_Check_Button looper_r2 {
          label R2
          user_data 2
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(276);
 return;
}
rkr->efx_Looper->changepar(12,(int)o->value())}
          xywh {346 366 15 15} down_box BORDER_BOX labelsize 10 labelcolor 7 align 1
        }
        Fl_Button looper_t1 {
          label 1
          user_data 2
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(277);
 return;
}
rkr->efx_Looper->changepar(7,(int)o->value());
update_looper();}
          xywh {430 360 18 18} type Toggle labelsize 10 align 16
        }
        Fl_Button looper_t2 {
          label 2
          user_data 2
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(278);
 return;
}
rkr->efx_Looper->changepar(8,(int)o->value());
update_looper();}
          xywh {453 360 18 18} type Toggle labelsize 10 align 16
        }
        Fl_Check_Button looper_lnk {
          label Lnk
          user_data 2
          callback {rkr->efx_Looper->changepar(13,(int)o->value())}
          xywh {346 380 15 15} down_box BORDER_BOX labelsize 10 labelcolor 7 align 4
        }
        Fl_Button looper_clear {
          label Clear
          user_data 2
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(279);
 return;
}
rkr->efx_Looper->changepar(4,(int)o->value());
update_looper();}
          xywh {365 378 43 14} labelsize 10
        }
        Fl_Check_Button looper_mt {
          label M
          user_data 2
          callback {rkr->efx_Looper->changepar(16,(int)o->value())}
          xywh {412 380 27 15} down_box BORDER_BOX labelsize 10 labelcolor 7
        }
        Fl_Box L_TimePos {
          xywh {440 379 35 14} box DOWN_BOX align 84
        }
      }
      Fl_Group RYANWAH {
        user_data 1
        xywh {479 211 158 184} box UP_BOX color 0 selection_color 0 labelfont 1 align 112 hide
      } {
        Fl_Light_Button ryanwah_activar {
          label On
          user_data 2
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(116);
 o->value(rkr->RyanWah_Bypass);
 return;
}
rkr->RyanWah_Bypass=(int)o->value();
if((int) o->value()==0)
rkr->efx_RyanWah->cleanup();
findpos(31,(int)o->value(),o);}
          xywh {485 216 34 18} shortcut 0x36 color 62 selection_color 1 labelsize 10 align 84 when 1
        }
        Fl_Choice ryanwah_preset {
          label Preset
          user_data 12031
          callback {long long ud= (long long) v;
if((ud==0)||(ud==12031))rkr->efx_RyanWah->setpreset((int) o->value());
ryanwah_WD->value(rkr->efx_RyanWah->getpar(0)-64);

int temp=rkr->efx_RyanWah->getpar(17);

if((temp==1) || (temp==3)) ryanwah_qm->value(1); else ryanwah_qm->value(0);
if((temp==2) || (temp==3)) ryanwah_nat->value(1); else ryanwah_nat->value(0);


ryanwah_q->value(rkr->efx_RyanWah->getpar(1));
ryanwah_freq->value(rkr->efx_RyanWah->getpar(2));
ryanwah_lfotype->value(rkr->efx_RyanWah->getpar(4));
ryanwah_dpth->value(rkr->efx_RyanWah->getpar(6));
ryanwah_ampsns->value(rkr->efx_RyanWah->getpar(7));
ryanwah_ampsnsinv->value(rkr->efx_RyanWah->getpar(8));
ryanwah_smooth->value(rkr->efx_RyanWah->getpar(9));
ryanwah_lp->value(rkr->efx_RyanWah->getpar(10));
ryanwah_bp->value(rkr->efx_RyanWah->getpar(11));
ryanwah_hp->value(rkr->efx_RyanWah->getpar(12));
svfilter_stages->value(rkr->efx_RyanWah->getpar(13));
ryanwah_rng->value(rkr->efx_RyanWah->getpar(14));
o->value(rkr->efx_RyanWah->getpar(18));
o->redraw();}
          xywh {557 216 76 18} down_box BORDER_BOX selection_color 0 labelsize 10 labelcolor 7 when 6 textsize 10 textcolor 7
        } {
          MenuItem {} {
            label WahWah
            xywh {72 72 36 21} labelsize 10
          }
          MenuItem {} {
            label Mutron
            xywh {72 72 36 21} labelsize 10
          }
          MenuItem {} {
            label {Phase Wah}
            xywh {72 72 36 21} labelsize 10
          }
          MenuItem {} {
            label Phaser
            xywh {82 82 36 21} labelsize 10
          }
          MenuItem {} {
            label {Quack Quack}
            xywh {92 92 36 21} labelsize 10
          }
          MenuItem {} {
            label SmoothTron
            xywh {102 102 36 21} labelsize 10
          }
        }
        Fl_Value_Slider ryanwah_WD {
          label {Wet/Dry}
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(256);
 return;
}
rkr->efx_RyanWah->changepar(0,(int)(o->value()+64));}
          xywh {529 241 100 10} type {Horz Knob} box FLAT_BOX color 178 selection_color 62 labelsize 10 labelcolor 7 align 4 minimum -64 maximum 63 step 1 textcolor 7
          class SliderW
        }
        Fl_Check_Button ryanwah_qm {
          label M
          user_data 2
          callback {if((int)o->value()) 
rkr->efx_RyanWah->Pmode +=1;
else
rkr->efx_RyanWah->Pmode -=1;
rkr->efx_RyanWah->changepar(17,rkr->efx_RyanWah->Pmode);}
          xywh {495 254 15 15} down_box BORDER_BOX labelsize 10 labelcolor 7 align 4
        }
        Fl_Value_Slider ryanwah_lp {
          label LP
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(257);
 return;
}
rkr->efx_RyanWah->changepar(10,(int)o->value());}
          xywh {529 255 100 10} type {Horz Knob} box FLAT_BOX color 178 selection_color 62 labelsize 10 labelcolor 7 align 4 minimum -64 maximum 64 step 1 textcolor 7
          class SliderW
        }
        Fl_Check_Button ryanwah_nat {
          label N
          user_data 2
          callback {if((int)o->value()) 
rkr->efx_RyanWah->Pmode +=2;
else
rkr->efx_RyanWah->Pmode -=2;
rkr->efx_RyanWah->changepar(17,rkr->efx_RyanWah->Pmode);}
          xywh {495 267 15 15} down_box BORDER_BOX labelsize 10 labelcolor 7 align 4
        }
        Fl_Value_Slider ryanwah_bp {
          label BP
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(258);
 return;
}
rkr->efx_RyanWah->changepar(11,(int)o->value());}
          xywh {529 266 100 10} type {Horz Knob} box FLAT_BOX color 178 selection_color 62 labelsize 10 labelcolor 7 align 4 minimum -64 maximum 64 step 1 textcolor 7
          class SliderW
        }
        Fl_Value_Slider ryanwah_hp {
          label HP
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(259);
 return;
}
rkr->efx_RyanWah->changepar(12,(int)o->value());}
          xywh {529 277 100 10} type {Horz Knob} box FLAT_BOX color 178 selection_color 62 labelsize 10 labelcolor 7 align 4 minimum -64 maximum 64 step 1 textcolor 7
          class SliderW
        }
        Fl_Counter svfilter_stages {
          label Stg
          callback {rkr->efx_RyanWah->changepar(13,(int)o->value());}
          xywh {506 294 27 12} type Simple box THIN_UP_BOX labelsize 10 labelcolor 7 align 4 minimum 1 maximum 12 step 1 value 1 textsize 9
        }
        Fl_Choice ryanwah_lfotype {
          label LFO
          callback {rkr->efx_RyanWah->changepar(4,(int)o->value())}
          xywh {559 293 72 16} down_box BORDER_BOX selection_color 0 labelsize 10 labelcolor 7 textsize 10 textcolor 7
          code0 {o->menu(menu_chorus_lfotype);}
        } {}
        Fl_Value_Slider ryanwah_dpth {
          label Width
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(260);
 return;
}
rkr->efx_RyanWah->changepar(6,(int)o->value());}
          xywh {529 313 100 10} type {Horz Knob} box FLAT_BOX color 178 selection_color 62 labelsize 10 labelcolor 7 align 4 maximum 127 step 1 textcolor 7
          class SliderW
        }
        Fl_Value_Slider ryanwah_freq {
          label Tempo
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(261);
 return;
}
rkr->efx_RyanWah->changepar(2,(int)o->value());}
          xywh {529 325 100 10} type {Horz Knob} box FLAT_BOX color 178 selection_color 62 labelsize 10 labelcolor 7 align 4 minimum 1 maximum 600 step 1 textcolor 7
          class SliderW
        }
        Fl_Value_Slider ryanwah_q {
          label {Res.}
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(262);
 return;
}
rkr->efx_RyanWah->changepar(1,(int)(o->value()));}
          xywh {529 337 100 10} type {Horz Knob} box FLAT_BOX color 178 selection_color 62 labelsize 10 labelcolor 7 align 4 minimum 1 maximum 127 step 1 textcolor 7
          class SliderW
        }
        Fl_Value_Slider ryanwah_rng {
          label Range
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(263);
 return;
}
rkr->efx_RyanWah->changepar(14,(int)o->value());}
          xywh {529 348 100 10} type {Horz Knob} box FLAT_BOX color 178 selection_color 62 labelsize 10 labelcolor 7 align 4 minimum 10 maximum 6000 step 1 textcolor 7
          class SliderW
        }
        Fl_Value_Slider ryanwah_ampsnsinv {
          label Wah
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(264);
 return;
}
rkr->efx_RyanWah->changepar(8,(int)o->value());}
          xywh {529 359 100 10} type {Horz Knob} box FLAT_BOX color 178 selection_color 62 labelsize 10 labelcolor 7 align 4 maximum 127 step 1 textcolor 7
          class SliderW
        }
        Fl_Value_Slider ryanwah_ampsns {
          label {E. Sens}
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(265);
 return;
}
rkr->efx_RyanWah->changepar(7,(int)o->value());}
          xywh {529 370 100 10} type {Horz Knob} box FLAT_BOX color 178 selection_color 62 labelsize 10 labelcolor 7 align 4 minimum -64 maximum 64 step 1 textcolor 7
          class SliderW
        }
        Fl_Value_Slider ryanwah_smooth {
          label Smooth
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(266);
 return;
}
rkr->efx_RyanWah->changepar(9,(int)o->value());}
          xywh {529 381 100 10} type {Horz Knob} box FLAT_BOX color 178 selection_color 62 labelsize 10 labelcolor 7 align 4 maximum 127 step 1 textcolor 7
          class SliderW
        }
      }
      Fl_Group RBECHO {
        user_data 1
        xywh {475 212 161 184} box UP_BOX color 0 selection_color 0 labelfont 1 align 112 hide
      } {
        Fl_Light_Button rbecho_activar {
          label On
          user_data 2
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(116);
 o->value(rkr->RBEcho_Bypass);
 return;
}
rkr->RBEcho_Bypass=(int)o->value();
if((int) o->value()==0)
rkr->efx_RBEcho->cleanup();
findpos(32,(int)o->value(),o);}
          xywh {480 216 34 18} shortcut 0x35 color 62 selection_color 1 labelsize 10 align 84 when 1
        }
        Fl_Choice rbecho_preset {
          label Preset
          user_data 12032
          callback {long long ud= (long long) v;
if((ud==0)||(ud==12032))rkr->efx_RBEcho->setpreset((int) o->value());
rbecho_WD->value(rkr->efx_RBEcho->getpar(0)-64);
rbecho_pan->value(rkr->efx_RBEcho->getpar(1)-64);
rbecho_delay->value(rkr->efx_RBEcho->getpar(2));
rbecho_LRdl->value(rkr->efx_RBEcho->getpar(3));
rbecho_angle->value(rkr->efx_RBEcho->getpar(4)-64);
rbecho_fb->value(rkr->efx_RBEcho->getpar(5));
rbecho_damp->value(rkr->efx_RBEcho->getpar(6));
rbecho_RV->value(rkr->efx_RBEcho->getpar(7));
rbecho_subdiv->value(rkr->efx_RBEcho->getpar(8));
rbecho_es->value(rkr->efx_RBEcho->getpar(9));}
          xywh {552 216 76 18} down_box BORDER_BOX selection_color 0 labelsize 10 labelcolor 7 when 6 textsize 10 textcolor 7
        } {
          MenuItem {} {
            label {Echo 1}
            xywh {67 67 36 21} labelsize 10
          }
          MenuItem {} {
            label {Echo 2}
            xywh {67 67 36 21} labelsize 10
          }
          MenuItem {} {
            label {Echo 3}
            xywh {67 67 36 21} labelsize 10
          }
        }
        Fl_Value_Slider rbecho_WD {
          label {Wet/Dry}
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(303);
 return;
}
rkr->efx_RBEcho->changepar(0,(int)(o->value()+64));}
          xywh {526 239 100 10} type {Horz Knob} box FLAT_BOX color 178 selection_color 62 labelsize 10 labelcolor 7 align 4 minimum -64 maximum 63 step 1 textcolor 7
          class SliderW
        }
        Fl_Value_Slider rbecho_RV {
          label Reverse
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(304);
 return;
}
rkr->efx_RBEcho->changepar(7,(int)o->value());}
          xywh {526 253 100 10} type {Horz Knob} box FLAT_BOX color 178 selection_color 62 labelsize 10 labelcolor 7 align 4 maximum 127 step 1 textcolor 7
          class SliderW
        }
        Fl_Value_Slider rbecho_pan {
          label Pan
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(305);
 return;
}
rkr->efx_RBEcho->changepar(1,(int)(o->value()+64));}
          xywh {526 267 100 10} type {Horz Knob} box FLAT_BOX color 178 selection_color 62 labelsize 10 labelcolor 7 align 4 minimum -64 maximum 63 step 1 textcolor 7
          class SliderW
        }
        Fl_Value_Slider rbecho_delay {
          label Tempo
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(306);
 return;
}
rkr->efx_RBEcho->changepar(2,(int)o->value());}
          xywh {526 281 100 10} type {Horz Knob} box FLAT_BOX color 178 selection_color 62 labelsize 10 labelcolor 7 align 4 when 4 minimum 1 maximum 600 step 1 value 20 textcolor 7
          class SliderW
        }
        Fl_Value_Slider rbecho_LRdl {
          label {LRdl.}
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(307);
 return;
}
rkr->efx_RBEcho->changepar(3,(int)o->value());}
          xywh {526 295 100 10} type {Horz Knob} box FLAT_BOX color 178 selection_color 62 labelsize 10 labelcolor 7 align 4 when 4 maximum 127 step 1 textcolor 7
          class SliderW
        }
        Fl_Value_Slider rbecho_fb {
          label {Fb.}
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(308);
 return;
}
rkr->efx_RBEcho->changepar(5,(int)o->value());}
          xywh {526 309 100 10} type {Horz Knob} box FLAT_BOX color 178 selection_color 62 labelsize 10 labelcolor 7 align 4 maximum 127 step 1 textcolor 7
          class SliderW
        }
        Fl_Choice rbecho_subdiv {
          label SubDivision
          callback {rkr->efx_RBEcho->changepar(8,(int)o->value());} open
          xywh {552 323 76 18} down_box BORDER_BOX selection_color 0 labelsize 10 labelcolor 7 when 6 textsize 10 textcolor 7
          code0 {o->menu(menu_arpie_subdiv);}
        } {}
        Fl_Value_Slider rbecho_damp {
          label Damp
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(309);
 return;
}
rkr->efx_RBEcho->changepar(6,(int)o->value());}
          xywh {526 346 100 10} type {Horz Knob} box FLAT_BOX color 178 selection_color 62 labelsize 10 labelcolor 7 align 4 maximum 127 step 1 textcolor 7
          class SliderW
        }
        Fl_Value_Slider rbecho_es {
          label {E.S.}
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(310);
 return;
}
rkr->efx_RBEcho->changepar(9,(int)o->value());}
          xywh {526 360 100 10} type {Horz Knob} box FLAT_BOX color 178 selection_color 62 labelsize 10 labelcolor 7 align 4 maximum 127 step 1 textcolor 7
          class SliderW
        }
        Fl_Value_Slider rbecho_angle {
          label Angle
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(311);
 return;
}
rkr->efx_RBEcho->changepar(4,(int)(o->value()+64));}
          xywh {526 374 100 10} type {Horz Knob} box FLAT_BOX color 178 selection_color 62 labelsize 10 labelcolor 7 align 4 minimum -64 maximum 64 step 1 textcolor 7
          class SliderW
        }
      }
      Fl_Group COILCRAFTER {
        user_data 1
        xywh {478 214 158 184} box UP_BOX color 0 selection_color 0 labelfont 1 align 112 hide
      } {
        Fl_Light_Button coil_activar {
          label On
          user_data 2
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(116);
 o->value(rkr->CoilCrafter_Bypass);
 return;
}
rkr->CoilCrafter_Bypass=(int)o->value();
if((int) o->value()==0)
rkr->efx_CoilCrafter->cleanup();
findpos(33,(int)o->value(),o);}
          xywh {483 218 34 18} shortcut 0x31 color 62 selection_color 1 labelsize 10 align 84 when 1
        }
        Fl_Choice coil_preset {
          label Preset
          user_data 12033
          callback {long long ud= (long long) v;
if((ud==0)||(ud==12033))rkr->efx_CoilCrafter->setpreset((int) o->value());
coil_WD->value(rkr->efx_CoilCrafter->getpar(0));
coil_tone->value(rkr->efx_CoilCrafter->getpar(7));
coil_origin->value(rkr->efx_CoilCrafter->getpar(1));
coil_destiny->value(rkr->efx_CoilCrafter->getpar(2));
coil_freq1->value(rkr->efx_CoilCrafter->getpar(3));
coil_q1->value(rkr->efx_CoilCrafter->getpar(4));
coil_freq2->value(rkr->efx_CoilCrafter->getpar(5));
coil_q2->value(rkr->efx_CoilCrafter->getpar(6));
coil_mode->value(rkr->efx_CoilCrafter->getpar(8));}
          xywh {555 218 76 18} down_box BORDER_BOX selection_color 0 labelsize 10 labelcolor 7 when 6 textsize 10 textcolor 7
        } {
          MenuItem {} {
            label {H to S}
            xywh {32 32 36 21} labelsize 10
          }
          MenuItem {} {
            label {S to H}
            xywh {10 10 36 21} labelsize 10
          }
        }
        Fl_Value_Slider coil_WD {
          label Gain
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(286);
 return;
}
rkr->efx_CoilCrafter->changepar(0,(int)o->value());}
          xywh {527 239 100 10} type {Horz Knob} box FLAT_BOX color 178 selection_color 62 labelsize 10 labelcolor 7 align 4 maximum 127 step 1 value 127 textcolor 7
          class SliderW
        }
        Fl_Value_Slider coil_tone {
          label Tone
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(287);
 return;
}
rkr->efx_CoilCrafter->changepar(7,(int)o->value());}
          xywh {527 255 100 10} type {Horz Knob} box FLAT_BOX color 178 selection_color 62 labelsize 10 labelcolor 7 align 4 minimum 20 maximum 4400 step 1 value 20 textcolor 7
          class SliderW
        }
        Fl_Choice coil_origin {
          label Origin
          user_data 12
          callback {rkr->efx_CoilCrafter->changepar(1,(int)o->value());
coil_freq1->value(rkr->efx_CoilCrafter->getpar(3));
coil_q1->value(rkr->efx_CoilCrafter->getpar(4));}
          xywh {526 269 90 18} down_box BORDER_BOX selection_color 0 labelsize 10 labelcolor 7 when 6 textsize 10 textcolor 7
        } {
          MenuItem {} {
            label Off
            xywh {0 0 36 21} labelsize 10
          }
          MenuItem {} {
            label {Fender Strat (old)}
            xywh {42 42 36 21} labelsize 10
          }
          MenuItem {} {
            label {Fender Strat (new)}
            xywh {20 20 36 21} labelsize 10
          }
          MenuItem {} {
            label {Squire Strat}
            xywh {42 42 36 21} labelsize 10
          }
          MenuItem {} {
            label {Fender Hambucker}
            xywh {42 42 36 21} labelsize 10
          }
          MenuItem {} {
            label {Gibson P90}
            xywh {52 52 36 21} labelsize 10
          }
          MenuItem {} {
            label {Gibson Standard}
            xywh {10 10 36 21} labelsize 10
          }
          MenuItem {} {
            label {Gibson Mini}
            xywh {10 10 36 21} labelsize 10
          }
          MenuItem {} {
            label {Gibson Super L6S}
            xywh {10 10 36 21} labelsize 10
          }
        }
        Fl_Value_Slider coil_freq1 {
          label Freq1
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(288);
 return;
}
rkr->efx_CoilCrafter->changepar(3,(int)o->value());}
          xywh {527 293 100 10} type {Horz Knob} box FLAT_BOX color 178 selection_color 62 labelsize 10 labelcolor 7 align 4 minimum 2600 maximum 4500 step 1 value 3200 textcolor 7
          class SliderW
        }
        Fl_Value_Slider coil_q1 {
          label Q1
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(289);
 return;
}
rkr->efx_CoilCrafter->changepar(4,(int)o->value());}
          xywh {527 308 100 10} type {Horz Knob} box FLAT_BOX color 178 selection_color 62 labelsize 10 labelcolor 7 align 4 minimum 10 maximum 65 step 1 textcolor 7
          class SliderW
        }
        Fl_Choice coil_destiny {
          label Destiny
          callback {rkr->efx_CoilCrafter->changepar(2,(int)o->value());
coil_freq2->value(rkr->efx_CoilCrafter->getpar(5));
coil_q2->value(rkr->efx_CoilCrafter->getpar(6));} open
          xywh {526 321 90 18} down_box BORDER_BOX selection_color 0 labelsize 10 labelcolor 7 when 6 textsize 10 textcolor 7
          code0 {o->menu(menu_coil_origin);}
        } {}
        Fl_Value_Slider coil_freq2 {
          label Freq2
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(290);
 return;
}
rkr->efx_CoilCrafter->changepar(5,(int)o->value());}
          xywh {527 346 100 10} type {Horz Knob} box FLAT_BOX color 178 selection_color 62 labelsize 10 labelcolor 7 align 4 minimum 2600 maximum 4500 step 1 value 3200 textcolor 7
          class SliderW
        }
        Fl_Value_Slider coil_q2 {
          label Q2
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(291);
 return;
}
rkr->efx_CoilCrafter->changepar(6,(int)o->value());}
          xywh {528 361 100 10} type {Horz Knob} box FLAT_BOX color 178 selection_color 62 labelsize 10 labelcolor 7 align 4 minimum 10 maximum 65 step 1 value 20 textcolor 7
          class SliderW
        }
        Fl_Check_Button coil_mode {
          label {Pos.}
          user_data 2
          callback {rkr->efx_CoilCrafter->changepar(8,(int)o->value());}
          xywh {491 375 41 15} down_box BORDER_BOX labelsize 10 labelcolor 7
        }
      }
      Fl_Group SHELFBOOST {
        user_data 1
        xywh {321 212 158 184} box UP_BOX color 0 selection_color 0 labelfont 1 align 112 hide
      } {
        Fl_Light_Button shelf_activar {
          label On
          user_data 2
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(116);
 o->value(rkr->ShelfBoost_Bypass);
 return;
}
rkr->ShelfBoost_Bypass=(int)o->value();
if((int) o->value()==0)
rkr->efx_ShelfBoost->cleanup();
findpos(34,(int)o->value(),o);}
          xywh {326 216 34 18} shortcut 0x31 color 62 selection_color 1 labelsize 10 align 84 when 1
        }
        Fl_Choice shelf_preset {
          label Preset
          user_data 12034
          callback {long long ud= (long long) v;
if((ud==0)||(ud==12034))rkr->efx_ShelfBoost->setpreset((int) o->value());
shelf_gain->value(rkr->efx_ShelfBoost->getpar(0));
shelf_q1->value(rkr->efx_ShelfBoost->getpar(1));
shelf_freq1->value(rkr->efx_ShelfBoost->getpar(2));
shelf_mode->value(rkr->efx_ShelfBoost->getpar(3));
shelf_level->value(rkr->efx_ShelfBoost->getpar(4));}
          xywh {398 216 76 18} down_box BORDER_BOX selection_color 0 labelsize 10 labelcolor 7 when 6 textsize 10 textcolor 7
        } {
          MenuItem {} {
            label Trebble
            xywh {42 42 36 21} labelsize 10
          }
          MenuItem {} {
            label Mid
            xywh {20 20 36 21} labelsize 10
          }
          MenuItem {} {
            label Low
            xywh {0 0 36 21} labelsize 10
          }
          MenuItem {} {
            label {Distortion 1}
            xywh {0 0 36 21} labelsize 10
          }
        }
        Fl_Value_Slider shelf_gain {
          label Gain
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(292);
 return;
}
rkr->efx_ShelfBoost->changepar(0,(int)o->value());}
          xywh {370 238 100 10} type {Horz Knob} box FLAT_BOX color 178 selection_color 62 labelsize 10 labelcolor 7 align 4 maximum 127 step 1 textcolor 7
          class SliderW
        }
        Fl_Value_Slider shelf_level {
          label Level
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(293);
 return;
}
rkr->efx_ShelfBoost->changepar(4,(int)o->value());}
          xywh {370 298 100 10} type {Horz Knob} box FLAT_BOX color 178 selection_color 62 labelsize 10 labelcolor 7 align 4 minimum 1 maximum 127 step 1 value 32 textcolor 7
          class SliderW
        }
        Fl_Value_Slider shelf_freq1 {
          label Tone
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(294);
 return;
}
rkr->efx_ShelfBoost->changepar(2,(int)o->value());}
          xywh {370 318 100 10} type {Horz Knob} box FLAT_BOX color 178 selection_color 62 labelsize 10 labelcolor 7 align 4 minimum 220 maximum 16000 step 1 value 1000 textcolor 7
          class SliderW
        }
        Fl_Value_Slider shelf_q1 {
          label {Pres.}
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(295);
 return;
}
rkr->efx_ShelfBoost->changepar(1,(int)o->value());}
          xywh {370 338 100 10} type {Horz Knob} box FLAT_BOX color 178 selection_color 62 labelsize 10 labelcolor 7 align 4 minimum -64 maximum 64 step 1 textcolor 7
          class SliderW
        }
        Fl_Check_Button shelf_mode {
          label Stereo
          user_data 2
          callback {rkr->efx_ShelfBoost->changepar(3,(int)o->value());}
          xywh {334 373 54 15} down_box BORDER_BOX labelsize 10 labelcolor 7
        }
      }
      Fl_Group VOCODER {
        user_data 1
        xywh {161 213 158 184} box UP_BOX color 0 selection_color 0 labelfont 1 align 112 hide
      } {
        Fl_Light_Button vo_activar {
          label On
          user_data 2
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(116);
 o->value(rkr->Vocoder_Bypass);
 return;
}
rkr->Vocoder_Bypass=(int)o->value();
if((int) o->value()==0)
vu_vu->value(-48);
findpos(35,(int)o->value(),o);}
          xywh {167 217 34 18} shortcut 0x35 color 62 selection_color 1 labelsize 10 align 84 when 1
        }
        Fl_Choice vo_preset {
          label Preset
          user_data 12035
          callback {long long ud= (long long) v;
if((ud==0)||(ud==12035))rkr->efx_Vocoder->setpreset((int) o->value());
vo_WD->value(rkr->efx_Vocoder->getpar(0)-64);
vo_pan->value(rkr->efx_Vocoder->getpar(1)-64);
vo_mu->value(rkr->efx_Vocoder->getpar(2));
vo_q->value(rkr->efx_Vocoder->getpar(3));
vo_input->value(rkr->efx_Vocoder->getpar(4));
vo_ring->value(rkr->efx_Vocoder->getpar(6));
vo_level->value(rkr->efx_Vocoder->getpar(5));}
          xywh {240 217 76 18} down_box BORDER_BOX selection_color 0 labelsize 10 labelcolor 7 when 6 textsize 10 textcolor 7
        } {
          MenuItem {} {
            label {Vocoder 1}
            xywh {77 77 36 21} labelsize 10
          }
          MenuItem {} {
            label {Vocoder 2}
            xywh {77 77 36 21} labelsize 10
          }
          MenuItem {} {
            label {Vocoder 3}
            xywh {77 77 36 21} labelsize 10
          }
          MenuItem {} {
            label {Vocoder 4}
            xywh {87 87 36 21} labelsize 10
          }
        }
        Fl_Value_Slider vo_WD {
          label {Wet/Dry}
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(296);
 return;
}
rkr->efx_Vocoder->changepar(0,(int)(o->value()+64));}
          xywh {213 243 100 10} type {Horz Knob} box FLAT_BOX color 178 selection_color 62 labelsize 10 labelcolor 7 align 4 minimum -64 maximum 64 step 1 textcolor 7
          class SliderW
        }
        Fl_Value_Slider vo_pan {
          label Pan
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(297);
 return;
}
rkr->efx_Vocoder->changepar(1,(int)(o->value()+64));}
          xywh {213 263 100 10} type {Horz Knob} box FLAT_BOX color 178 selection_color 62 labelsize 10 labelcolor 7 align 4 minimum -64 maximum 64 step 1 textcolor 7
          class SliderW
        }
        Fl_Value_Slider vo_input {
          label Input
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(298);
 return;
}
rkr->efx_Vocoder->changepar(4,(int)o->value());}
          xywh {213 283 100 10} type {Horz Knob} box FLAT_BOX color 178 selection_color 62 labelsize 10 labelcolor 7 align 4 maximum 127 step 1 textcolor 7
          class SliderW
        }
        Fl_Value_Slider vo_mu {
          label {Muf.}
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(299);
 return;
}
rkr->efx_Vocoder->changepar(2,(int)o->value());}
          xywh {213 303 100 10} type {Horz Knob} box FLAT_BOX color 178 selection_color 62 labelsize 10 labelcolor 7 align 4 minimum 1 maximum 127 step 1 value 1 textcolor 7
          class SliderW
        }
        Fl_Value_Slider vo_q {
          label Q
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(300);
 return;
}
rkr->efx_Vocoder->changepar(3,(int)o->value());}
          xywh {213 323 100 10} type {Horz Knob} box FLAT_BOX color 178 selection_color 62 labelsize 10 labelcolor 7 align 4 minimum 40 maximum 170 step 1 value 120 textcolor 7
          class SliderW
        }
        Fl_Value_Slider vo_ring {
          label Ring
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(301);
 return;
}
rkr->efx_Vocoder->changepar(6,(int)o->value());}
          xywh {213 343 100 10} type {Horz Knob} box FLAT_BOX color 178 selection_color 62 labelsize 10 labelcolor 7 align 4 maximum 127 step 1 textcolor 7
          class SliderW
        }
        Fl_Value_Slider vo_level {
          label Level
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(302);
 return;
}
rkr->efx_Vocoder->changepar(5,(int)o->value());}
          xywh {213 363 100 10} type {Horz Knob} box FLAT_BOX color 178 selection_color 62 labelsize 10 labelcolor 7 align 4 maximum 127 step 1 textcolor 7
          class SliderW
        }
        Fl_Slider vu_vu {
          xywh {168 268 11 122} type {Vert Fill} box NO_BOX color 178 selection_color 90 align 80 when 0 minimum 15 maximum -48 step 1 value -48
          class NewVum
        }
      }
      Fl_Group SUSTAINER {
        user_data 1
        xywh {161 213 158 184} box UP_BOX color 0 selection_color 0 labelfont 1 align 112 hide
      } {
        Fl_Light_Button sus_activar {
          label On
          user_data 2
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(116);
 o->value(rkr->Sustainer_Bypass);
 return;
}
rkr->Sustainer_Bypass=(int)o->value();
if((int) o->value()==0)
rkr->efx_Sustainer->cleanup();
findpos(36,(int)o->value(),o);}
          xywh {166 217 34 18} shortcut 0x31 color 62 selection_color 1 labelsize 10 align 84 when 1
        }
        Fl_Choice sus_preset {
          label Preset
          user_data 12036
          callback {long long ud= (long long) v;
if((ud==0)||(ud==12036))rkr->efx_Sustainer->setpreset((int) o->value());
sus_gain->value(rkr->efx_Sustainer->getpar(0));
sus_sus->value(rkr->efx_Sustainer->getpar(1));}
          xywh {238 217 76 18} down_box BORDER_BOX selection_color 0 labelsize 10 labelcolor 7 when 6 textsize 10 textcolor 7
        } {
          MenuItem {} {
            label {Sustain 1}
            xywh {10 10 36 21} labelsize 10
          }
          MenuItem {} {
            label {Sustain 2}
            xywh {0 0 36 21} labelsize 10
          }
          MenuItem {} {
            label {Sustain 3}
            xywh {0 0 36 21} labelsize 10
          }
        }
        Fl_Value_Slider sus_gain {
          label Gain
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(312);
 return;
}
rkr->efx_Sustainer->changepar(0,(int)o->value());}
          xywh {210 275 100 10} type {Horz Knob} box FLAT_BOX color 178 selection_color 62 labelsize 10 labelcolor 7 align 4 maximum 127 step 1 textcolor 7
          class SliderW
        }
        Fl_Value_Slider sus_sus {
          label Sustain
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(313);
 return;
}
rkr->efx_Sustainer->changepar(1,(int)o->value());}
          xywh {210 299 100 10} type {Horz Knob} box FLAT_BOX color 178 selection_color 62 labelsize 10 labelcolor 7 align 4 minimum 1 maximum 127 step 1 value 32 textcolor 7
          class SliderW
        }
      }
      Fl_Group SEQUENCE {
        user_data 1
        xywh {319 212 158 184} box UP_BOX color 0 selection_color 0 labelfont 1 align 112 hide
      } {
        Fl_Light_Button seq_activar {
          label On
          user_data 2
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(116);
 o->value(rkr->Sequence_Bypass);
 return;
}
rkr->Sequence_Bypass=(int)o->value();
if((int) o->value()==0)
rkr->efx_Sequence->cleanup();
findpos(37,(int)o->value(),o);}
          xywh {324 216 34 16} shortcut 0x36 color 62 selection_color 1 labelsize 10 align 84 when 1
        }
        Fl_Choice seq_preset {
          label Preset
          user_data 12037
          callback {long long ud= (long long) v;
if((ud==0)||(ud==12037))rkr->efx_Sequence->setpreset((int) o->value());
seq_WD->value(rkr->efx_Sequence->getpar(8)-64);
seq_q->value(rkr->efx_Sequence->getpar(10)-64);
seq_amp->value(rkr->efx_Sequence->getpar(11));
seq_tempo->value(rkr->efx_Sequence->getpar(9));
seq_stdf->value(rkr->efx_Sequence->getpar(12));
seq_1->value(rkr->efx_Sequence->getpar(0));
seq_2->value(rkr->efx_Sequence->getpar(1));
seq_3->value(rkr->efx_Sequence->getpar(2));
seq_4->value(rkr->efx_Sequence->getpar(3));
seq_5->value(rkr->efx_Sequence->getpar(4));
seq_6->value(rkr->efx_Sequence->getpar(5));
seq_7->value(rkr->efx_Sequence->getpar(6));
seq_8->value(rkr->efx_Sequence->getpar(7));
seq_mode->value(rkr->efx_Sequence->getpar(13));
seq_range->value(rkr->efx_Sequence->getpar(14));}
          xywh {396 216 76 18} down_box BORDER_BOX selection_color 0 labelsize 10 labelcolor 7 when 6 textsize 10 textcolor 7
        } {
          MenuItem {} {
            label Jumpy
            xywh {82 82 36 21} labelsize 10
          }
          MenuItem {} {
            label {Stair Step}
            xywh {82 82 36 21} labelsize 10
          }
          MenuItem {} {
            label Mild
            xywh {82 82 36 21} labelsize 10
          }
          MenuItem {} {
            label {Wah Wah}
            xywh {0 0 36 21} labelsize 10
          }
          MenuItem {} {
            label {Filter Pan}
            xywh {0 0 36 21} labelsize 10
          }
          MenuItem {} {
            label Stepper
            xywh {0 0 36 21} labelsize 10
          }
          MenuItem {} {
            label Shifter
            xywh {0 0 36 21} labelsize 10
          }
          MenuItem {} {
            label {Zeke Trem}
            xywh {10 10 36 21} labelsize 10
          }
          MenuItem {} {
            label Boogie
            xywh {0 0 36 21} labelsize 10
          }
          MenuItem {} {
            label Chorus
            xywh {0 0 36 21} labelsize 10
          }
        }
        Fl_Value_Slider seq_WD {
          label {Wet/Dry}
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(314);
 return;
}
rkr->efx_Sequence->changepar(8,(int)(o->value()+64));}
          xywh {368 237 100 10} type {Horz Knob} box FLAT_BOX color 178 selection_color 62 labelsize 10 labelcolor 7 align 4 minimum -64 maximum 64 step 1 textcolor 7
          class SliderW
        }
        Fl_Value_Slider seq_1 {
          label 1
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(315);
 return;
}
rkr->efx_Sequence->changepar(0,(int)o->value());}
          xywh {368 249 100 10} type {Horz Knob} box FLAT_BOX color 178 selection_color 62 labelsize 10 labelcolor 7 align 4 maximum 127 step 1 textcolor 7
          class SliderW
        }
        Fl_Value_Slider seq_2 {
          label 2
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(316);
 return;
}
rkr->efx_Sequence->changepar(1,(int)o->value());}
          xywh {368 261 100 10} type {Horz Knob} box FLAT_BOX color 178 selection_color 62 labelsize 10 labelcolor 7 align 4 maximum 127 step 1 textcolor 7
          class SliderW
        }
        Fl_Value_Slider seq_3 {
          label 3
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(317);
 return;
}
rkr->efx_Sequence->changepar(2,(int)o->value());}
          xywh {368 273 100 10} type {Horz Knob} box FLAT_BOX color 178 selection_color 62 labelsize 10 labelcolor 7 align 4 maximum 127 step 1 textcolor 7
          class SliderW
        }
        Fl_Value_Slider seq_4 {
          label 4
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(318);
 return;
}
rkr->efx_Sequence->changepar(3,(int)o->value());}
          xywh {368 285 100 10} type {Horz Knob} box FLAT_BOX color 178 selection_color 62 labelsize 10 labelcolor 7 align 4 maximum 127 step 1 textcolor 7
          class SliderW
        }
        Fl_Value_Slider seq_5 {
          label 5
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(319);
 return;
}
rkr->efx_Sequence->changepar(4,(int)o->value());}
          xywh {369 297 100 10} type {Horz Knob} box FLAT_BOX color 178 selection_color 62 labelsize 10 labelcolor 7 align 4 maximum 127 step 1 textcolor 7
          class SliderW
        }
        Fl_Value_Slider seq_6 {
          label 6
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(320);
 return;
}
rkr->efx_Sequence->changepar(5,(int)o->value());}
          xywh {369 309 100 10} type {Horz Knob} box FLAT_BOX color 178 selection_color 62 labelsize 10 labelcolor 7 align 4 maximum 127 step 1 textcolor 7
          class SliderW
        }
        Fl_Value_Slider seq_7 {
          label 7
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(321);
 return;
}
rkr->efx_Sequence->changepar(6,(int)o->value());}
          xywh {369 321 100 10} type {Horz Knob} box FLAT_BOX color 178 selection_color 62 labelsize 10 labelcolor 7 align 4 maximum 127 step 1 textcolor 7
          class SliderW
        }
        Fl_Value_Slider seq_8 {
          label 8
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(322);
 return;
}
rkr->efx_Sequence->changepar(7,(int)o->value());}
          xywh {369 333 100 10} type {Horz Knob} box FLAT_BOX color 178 selection_color 62 labelsize 10 labelcolor 7 align 4 maximum 127 step 1 textcolor 7
          class SliderW
        }
        Fl_Value_Slider seq_tempo {
          label Tempo
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(323);
 return;
}
rkr->efx_Sequence->changepar(9,(int)o->value());}
          xywh {368 345 100 10} type {Horz Knob} box FLAT_BOX color 178 selection_color 62 labelsize 10 labelcolor 7 align 4 minimum 1 maximum 600 step 1 textcolor 7
          class SliderW
        }
        Fl_Value_Slider seq_q {
          label Q
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(324);
 return;
}
rkr->efx_Sequence->changepar(10,(int)o->value()+64);}
          xywh {368 357 100 10} type {Horz Knob} box FLAT_BOX color 178 selection_color 62 labelsize 10 labelcolor 7 align 4 minimum -64 maximum 64 step 1 textcolor 7
          class SliderW
        }
        Fl_Value_Slider seq_stdf {
          label {St.df}
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(325);
 return;
}
rkr->efx_Sequence->changepar(12,(int)o->value());}
          xywh {368 369 100 10} type {Horz Knob} box FLAT_BOX color 178 selection_color 62 labelsize 10 labelcolor 7 align 4 maximum 7 step 1 textcolor 7
          class SliderW
        }
        Fl_Check_Button seq_amp {
          label {Amp.}
          user_data 2
          callback {rkr->efx_Sequence->changepar(11,(int)o->value())}
          xywh {432 381 43 14} down_box BORDER_BOX labelsize 10 labelcolor 7
        }
        Fl_Choice seq_mode {
          label Mode
          user_data 12
          callback {rkr->efx_Sequence->changepar(13,(int)o->value())}
          xywh {352 381 78 13} down_box BORDER_BOX labelsize 9 labelcolor 7 textsize 9 textcolor 7
        } {
          MenuItem {} {
            label Lineal
            xywh {0 0 36 21} labelsize 9
          }
          MenuItem {} {
            label UpDown
            xywh {0 0 36 21} labelsize 9
          }
          MenuItem {} {
            label Stepper
            xywh {0 0 36 21} labelsize 9
          }
          MenuItem {} {
            label Shifter
            xywh {0 0 36 21} labelsize 9
          }
          MenuItem {} {
            label Tremor
            xywh {10 10 36 21} labelsize 9
          }
          MenuItem {} {
            label Arpegiator
            xywh {0 0 36 21} labelsize 9
          }
          MenuItem {} {
            label Chorus
            xywh {0 0 36 21} labelsize 9
          }
          MenuItem {} {
            label TrigStepper
            xywh {10 10 36 21} labelsize 9
          }
          MenuItem {} {
            label {Seq Delay}
            xywh {20 20 36 21} labelsize 9
          }
        }
        Fl_Counter seq_range {
          label Range
          callback {rkr->efx_Sequence->changepar(14,(int)o->value())}
          xywh {324 285 33 13} type Simple labelsize 10 labelcolor 7 minimum 1 maximum 8 step 1 value 1 textsize 9
        }
      }
      Fl_Group SHIFTER {
        user_data 1
        xywh {320 212 158 184} box UP_BOX color 0 selection_color 0 labelfont 1 align 112 hide
      } {
        Fl_Light_Button shifter_activar {
          label On
          user_data 2
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(116);
 o->value(rkr->Shifter_Bypass);
 return;
}
rkr->Shifter_Bypass=(int)o->value();
if((int) o->value()==0)
rkr->efx_Shifter->cleanup();
findpos(38,(int)o->value(),o);}
          xywh {325 216 34 18} shortcut 0x30 color 62 selection_color 1 labelsize 10 when 1
        }
        Fl_Choice shifter_preset {
          label Preset
          user_data 12038
          callback {long long ud= (long long) v;
if((ud==0)||(ud==12038))rkr->efx_Shifter->setpreset((int)o->value());
shifter_WD->value(rkr->efx_Shifter->getpar(0)-64);
shifter_pan->value(rkr->efx_Shifter->getpar(1)-64);
shifter_gain->value(rkr->efx_Shifter->getpar(2)-64);
shifter_int->value(rkr->efx_Shifter->getpar(6));
shifter_attack->value(rkr->efx_Shifter->getpar(3));
shifter_decay->value(rkr->efx_Shifter->getpar(4));
shifter_thre->value(rkr->efx_Shifter->getpar(5));
shifter_ud->value(rkr->efx_Shifter->getpar(7));
shifter_whammy->value(rkr->efx_Shifter->getpar(9));

shifter_mode->value(rkr->efx_Shifter->getpar(8));}
          xywh {397 216 76 18} down_box BORDER_BOX selection_color 0 labelsize 10 labelcolor 7 when 6 textsize 10 textcolor 7
        } {
          MenuItem {} {
            label Fast
            xywh {10 10 45 26} labelsize 10
          }
          MenuItem {} {
            label {Slow Up}
            xywh {42 42 36 21} labelsize 10
          }
          MenuItem {} {
            label {Slow Down}
            xywh {42 42 36 21} labelsize 10
          }
          MenuItem {} {
            label Chorus
            xywh {0 0 36 21} labelsize 10
          }
          MenuItem {} {
            label {Trig. Chorus}
            xywh {0 0 36 21} labelsize 10
          }
        }
        Fl_Value_Slider shifter_WD {
          label {Wet/Dry}
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(326);
 return;
}
rkr->efx_Shifter->changepar(0,(int)(o->value()+64));}
          xywh {370 242 100 10} type {Horz Knob} box FLAT_BOX color 178 selection_color 62 labelsize 10 labelcolor 7 align 4 minimum -64 maximum 63 step 1 textcolor 7
          class SliderW
        }
        Fl_Value_Slider shifter_int {
          label {Int.}
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(327);
 return;
}
rkr->Shifter_Bypass=0;
rkr->efx_Shifter->changepar(6,(int)o->value());
if((int)shifter_activar->value())rkr->Shifter_Bypass=1;}
          xywh {370 255 100 10} type {Horz Knob} box FLAT_BOX color 178 selection_color 62 labelsize 10 labelcolor 7 align 4 maximum 12 step 1 textcolor 7
          class SliderW
        }
        Fl_Value_Slider shifter_gain {
          label Gain
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(328);
 return;
}
rkr->efx_Shifter->changepar(2,(int)(o->value()+64));}
          xywh {370 270 100 10} type {Horz Knob} box FLAT_BOX color 178 selection_color 62 labelsize 10 labelcolor 7 align 4 minimum -64 maximum 63 step 1 textcolor 7
          class SliderW
        }
        Fl_Value_Slider shifter_pan {
          label Pan
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(329);
 return;
}
rkr->efx_Shifter->changepar(1,(int)(o->value()+64));}
          xywh {370 283 100 10} type {Horz Knob} box FLAT_BOX color 178 selection_color 62 labelsize 10 labelcolor 7 align 4 minimum -64 maximum 63 step 1 textcolor 7
          class SliderW
        }
        Fl_Value_Slider shifter_attack {
          label Attack
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(330);
 return;
}
rkr->efx_Shifter->changepar(3,(int)o->value());}
          xywh {371 300 100 10} type {Horz Knob} box FLAT_BOX color 178 selection_color 62 labelsize 10 labelcolor 7 align 4 minimum 1 maximum 2000 step 1 value 100 textcolor 7
          class SliderW
        }
        Fl_Value_Slider shifter_decay {
          label Decay
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(331);
 return;
}
rkr->efx_Shifter->changepar(4,(int)o->value());}
          xywh {370 313 100 10} type {Horz Knob} box FLAT_BOX color 178 selection_color 62 labelsize 10 labelcolor 7 align 4 minimum 1 maximum 2000 step 1 value 100 textcolor 7
          class SliderW
        }
        Fl_Value_Slider shifter_thre {
          label Thrshold
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(332);
 return;
}
rkr->efx_Shifter->changepar(5,(int)o->value());}
          xywh {370 326 100 10} type {Horz Knob} box FLAT_BOX color 178 selection_color 62 labelsize 10 labelcolor 7 align 4 minimum -70 maximum 20 step 1 value 20 textcolor 7
          class SliderW
        }
        Fl_Check_Button shifter_ud {
          label Down
          user_data 2
          callback {rkr->efx_Shifter->changepar(7,(int)o->value())}
          xywh {371 340 49 14} down_box BORDER_BOX labelsize 10 labelcolor 7
        }
        Fl_Value_Slider shifter_whammy {
          label Whamy
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(333);
 return;
}
rkr->efx_Shifter->changepar(9,(int)o->value());}
          xywh {370 357 100 10} type {Horz Knob} box FLAT_BOX color 178 selection_color 62 labelsize 10 labelcolor 7 align 4 maximum 127 step 1 textcolor 7
          class SliderW
        }
        Fl_Choice shifter_mode {
          label Mode
          user_data 12
          callback {rkr->efx_Shifter->changepar(8,(int)o->value())} open
          xywh {363 377 78 13} down_box BORDER_BOX labelsize 9 labelcolor 7 textsize 9 textcolor 7
        } {
          MenuItem {} {
            label Trigger
            xywh {10 10 36 21} labelsize 9
          }
          MenuItem {} {
            label Whammy
            xywh {0 0 36 21} labelsize 9
          }
          MenuItem {} {
            label Portamento
            xywh {10 10 36 21} labelsize 9
          }
        }
      }
      Fl_Group STOMPBOX {
        user_data 1
        xywh {481 212 158 184} box UP_BOX color 0 selection_color 0 labelfont 1 align 112 hide
      } {
        Fl_Light_Button stomp_activar {
          label On
          user_data 2
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(116);
 o->value(rkr->StompBox_Bypass);
 return;
}
rkr->StompBox_Bypass=(int)o->value();
if((int) o->value()==0)
rkr->efx_StompBox->cleanup();
findpos(39,(int)o->value(),o);}
          xywh {486 216 34 18} shortcut 0x30 color 62 selection_color 1 labelsize 10 when 1
        }
        Fl_Choice stomp_preset {
          label Preset
          user_data 12039
          callback {long long ud= (long long) v;
if((ud==0)||(ud==12039))rkr->efx_StompBox->setpreset((int)o->value());
stomp_WD->value(rkr->efx_StompBox->getpar(0));
stomp_gain->value(rkr->efx_StompBox->getpar(4));
stomp_low->value(rkr->efx_StompBox->getpar(3));
stomp_mid->value(rkr->efx_StompBox->getpar(2));
stomp_high->value(rkr->efx_StompBox->getpar(1));

stomp_mode->value(rkr->efx_StompBox->getpar(5));}
          xywh {558 216 76 18} down_box BORDER_BOX selection_color 0 labelsize 10 labelcolor 7 when 6 textsize 10 textcolor 7
        } {
          MenuItem {} {
            label Odie
            xywh {20 20 45 26} labelsize 10
          }
          MenuItem {} {
            label Grunger
            xywh {0 0 36 21} labelsize 10
          }
          MenuItem {} {
            label {Hard Dist.}
            xywh {0 0 36 21} labelsize 10
          }
          MenuItem {} {
            label Ratula
            xywh {10 10 36 21} labelsize 10
          }
          MenuItem {} {
            label {Classic Dist}
            xywh {20 20 36 21} labelsize 10
          }
          MenuItem {} {
            label {Morbid Impalement}
            xywh {30 30 36 21} labelsize 10
          }
          MenuItem {} {
            label {Sharp Metal}
            xywh {40 40 36 21} labelsize 10
          }
          MenuItem {} {
            label {Classic Fuzz}
            xywh {50 50 36 21} labelsize 10
          }
        }
        Fl_Value_Slider stomp_WD {
          label Level
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(334);
 return;
}
rkr->efx_StompBox->changepar(0,(int)o->value());}
          xywh {531 242 100 10} type {Horz Knob} box FLAT_BOX color 178 selection_color 62 labelsize 10 labelcolor 7 align 4 maximum 127 step 1 textcolor 7
          class SliderW
        }
        Fl_Value_Slider stomp_gain {
          label Gain
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(335);
 return;
}
rkr->efx_StompBox->changepar(4,(int)o->value());}
          xywh {531 270 100 10} type {Horz Knob} box FLAT_BOX color 178 selection_color 62 labelsize 10 labelcolor 7 align 4 maximum 127 step 1 textcolor 7
          class SliderW
        }
        Fl_Value_Slider stomp_low {
          label Low
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(336);
 return;
}
rkr->efx_StompBox->changepar(3,(int)o->value());}
          xywh {531 287 100 10} type {Horz Knob} box FLAT_BOX color 178 selection_color 62 labelsize 10 labelcolor 7 align 4 minimum -64 maximum 64 step 1 textcolor 7
          class SliderW
        }
        Fl_Value_Slider stomp_mid {
          label Mid
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(337);
 return;
}
rkr->efx_StompBox->changepar(2,(int)o->value());}
          xywh {531 304 100 10} type {Horz Knob} box FLAT_BOX color 178 selection_color 62 labelsize 10 labelcolor 7 align 36 minimum -64 maximum 64 step 1 textcolor 7
          class SliderW
        }
        Fl_Value_Slider stomp_high {
          label High
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(338);
 return;
}
rkr->efx_StompBox->changepar(1,(int)o->value());}
          xywh {531 321 100 10} type {Horz Knob} box FLAT_BOX color 178 selection_color 62 labelsize 10 labelcolor 7 align 4 minimum -64 maximum 64 step 1 textcolor 7
          class SliderW
        }
        Fl_Choice stomp_mode {
          label Mode
          user_data 12
          callback {rkr->efx_StompBox->changepar(5,(int)o->value())}
          xywh {524 377 78 13} down_box BORDER_BOX labelsize 9 labelcolor 7 textsize 9 textcolor 7
        } {
          MenuItem {} {
            label Amp
            xywh {20 20 36 21} labelsize 9
          }
          MenuItem {} {
            label Grunge
            xywh {30 30 36 21} labelsize 9
          }
          MenuItem {} {
            label Rat
            xywh {40 40 36 21} labelsize 9
          }
          MenuItem {} {
            label {Fat Cat}
            xywh {50 50 36 21} labelsize 9
          }
          MenuItem {} {
            label {Dist+}
            xywh {60 60 36 21} labelsize 9
          }
          MenuItem {} {
            label Death
            xywh {70 70 36 21} labelsize 9
          }
          MenuItem {} {
            label {Mid Elves Own}
            xywh {80 80 36 21} labelsize 9
          }
          MenuItem {} {
            label Fuzz
            xywh {90 90 36 21} labelsize 9
          }
        }
      }
      Fl_Group REVERBTRON {
        user_data 1
        xywh {158 212 158 184} box UP_BOX color 0 selection_color 0 labelfont 1 align 112 hide
      } {
        Fl_Light_Button revtron_activar {
          label On
          user_data 2
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(116);
 o->value(rkr->Reverbtron_Bypass);
 return;
}
rkr->Reverbtron_Bypass=(int)o->value();
if((int) o->value()==0) rkr->efx_Reverbtron->cleanup();
findpos(40,(int)o->value(),o);}
          xywh {164 216 34 18} shortcut 0x35 color 62 selection_color 1 labelsize 10 align 84 when 1
        }
        Fl_Choice revtron_preset {
          label Preset
          user_data 12040
          callback {long long ud= (long long) v;
if((ud==0)||(ud==12040))rkr->efx_Reverbtron->setpreset((int) o->value());
revtron_pan->value(rkr->efx_Reverbtron->getpar(11)-64);
revtron_level->value(rkr->efx_Reverbtron->getpar(7));
revtron_WD->value(rkr->efx_Reverbtron->getpar(0)-64);
revtron_damp->value(rkr->efx_Reverbtron->getpar(6));
revtron_fnum->value(rkr->efx_Reverbtron->getpar(8));
revtron_length->value(rkr->efx_Reverbtron->getpar(3));
revtron_strech->value(rkr->efx_Reverbtron->getpar(9));
revtron_safe->value(rkr->efx_Reverbtron->getpar(2));
revtron_user->value(rkr->efx_Reverbtron->getpar(4));
revtron_user->do_callback();
revtron_fb->value(rkr->efx_Reverbtron->getpar(10));
revtron_fade->value(rkr->efx_Reverbtron->getpar(1));
revtron_idelay->value(rkr->efx_Reverbtron->getpar(5));
revtron_LPF->value(rkr->efx_Reverbtron->getpar(14));
revtron_HPF->value(rkr->efx_Reverbtron->getpar(15));

revtron_es->value(rkr->efx_Reverbtron->getpar(12));
revtron_rv->value(rkr->efx_Reverbtron->getpar(13));}
          xywh {237 216 76 18} down_box BORDER_BOX selection_color 0 labelsize 10 labelcolor 7 when 6 textsize 10 textcolor 7
        } {
          MenuItem {} {
            label Chamber
            xywh {77 77 36 21} labelsize 10
          }
          MenuItem {} {
            label {Concrete Stairwell}
            xywh {0 0 36 21} labelsize 10
          }
          MenuItem {} {
            label Hall
            xywh {0 0 36 21} labelsize 10
          }
          MenuItem {} {
            label {Med Hall}
            xywh {0 0 36 21} labelsize 10
          }
          MenuItem {} {
            label Room
            xywh {0 0 36 21} labelsize 10
          }
          MenuItem {} {
            label Hall
            xywh {0 0 36 21} labelsize 10
          }
          MenuItem {} {
            label Guitar
            xywh {0 0 36 21} labelsize 10
          }
          MenuItem {} {
            label Studio
            xywh {0 0 36 21} labelsize 10
          }
          MenuItem {} {
            label Cathedral
            xywh {0 0 36 21} labelsize 9
          }
        }
        Fl_Value_Slider revtron_WD {
          label {Wet/Dry}
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(339);
 return;
}
rkr->efx_Reverbtron->changepar(0,(int)(o->value()+64));}
          xywh {210 237 100 10} type {Horz Knob} box FLAT_BOX color 178 selection_color 62 labelsize 10 labelcolor 7 align 4 minimum -64 maximum 64 step 1 textcolor 7
          class SliderW
        }
        Fl_Value_Slider revtron_pan {
          label Pan
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(340);
 return;
}
rkr->efx_Reverbtron->changepar(11,(int)(o->value()+64));}
          xywh {210 249 100 10} type {Horz Knob} box FLAT_BOX color 178 selection_color 62 labelsize 10 labelcolor 7 align 4 minimum -64 maximum 63 step 1 textcolor 7
          class SliderW
        }
        Fl_Value_Slider revtron_level {
          label Level
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(341);
 return;
}
rkr->efx_Reverbtron->changepar(7,(int)o->value());}
          xywh {210 261 100 10} type {Horz Knob} box FLAT_BOX color 178 selection_color 62 labelsize 10 labelcolor 7 align 4 maximum 127 step 1 textcolor 7
          class SliderW
        }
        Fl_Value_Slider revtron_damp {
          label Damp
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(342);
 return;
}
rkr->efx_Reverbtron->changepar(6,(int)o->value());}
          xywh {210 273 100 10} type {Horz Knob} box FLAT_BOX color 178 selection_color 62 labelsize 10 labelcolor 7 align 4 maximum 127 step 1 textcolor 7
          class SliderW
        }
        Fl_Value_Slider revtron_fb {
          label Fb
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(343);
 return;
}
rkr->efx_Reverbtron->changepar(10,(int)o->value());}
          xywh {210 285 100 10} type {Horz Knob} box FLAT_BOX color 178 selection_color 62 labelsize 10 labelcolor 7 align 4 minimum -64 maximum 64 step 1 textcolor 7
          class SliderW
        }
        Fl_Value_Slider revtron_length {
          label Length
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(344);
 return;
}
rkr->efx_Reverbtron->changepar(3,(int)o->value());}
          xywh {210 297 100 10} type {Horz Knob} box FLAT_BOX color 178 selection_color 62 labelsize 10 labelcolor 7 align 4 when 4 minimum 20 maximum 1500 step 1 value 100 textcolor 7
          class SliderW
        }
        Fl_Value_Slider revtron_strech {
          label Stretch
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(345);
 return;
}
rkr->efx_Reverbtron->changepar(9,(int)o->value());}
          xywh {210 309 100 10} type {Horz Knob} box FLAT_BOX color 178 selection_color 62 labelsize 10 labelcolor 7 align 4 when 4 minimum -64 maximum 64 step 1 textcolor 7
          class SliderW
        }
        Fl_Value_Slider revtron_idelay {
          label {I.Del}
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(346);
 return;
}
rkr->efx_Reverbtron->changepar(5,(int)o->value());}
          xywh {210 321 100 10} type {Horz Knob} box FLAT_BOX color 178 selection_color 62 labelsize 10 labelcolor 7 align 4 when 4 maximum 500 step 1 textcolor 7
          class SliderW
        }
        Fl_Value_Slider revtron_fade {
          label Fade
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(347);
 return;
}
rkr->efx_Reverbtron->changepar(1,(int)o->value());}
          xywh {210 333 100 10} type {Horz Knob} box FLAT_BOX color 178 selection_color 62 labelsize 10 labelcolor 7 align 4 when 4 maximum 127 step 1 textcolor 7
          class SliderW
        }
        Fl_Value_Slider revtron_HPF {
          label Diffusion
          callback {rkr->efx_Reverbtron->changepar(15,(int)o->value());}
          xywh {211 345 100 10} type {Horz Knob} box FLAT_BOX color 178 selection_color 62 labelsize 10 labelcolor 7 align 4 when 4 maximum 127 step 1 value 26000 textcolor 7
          class SliderW
        }
        Fl_Value_Slider revtron_LPF {
          label LPF
          callback {rkr->efx_Reverbtron->changepar(14,(int)o->value());}
          xywh {210 357 100 10} type {Horz Knob} box FLAT_BOX color 178 selection_color 62 labelsize 10 labelcolor 7 align 4 when 4 minimum 20 maximum 26000 step 1 value 20 textcolor 7
          class SliderW
        }
        Fl_Check_Button revtron_rv {
          label Sh
          user_data 2
          callback {rkr->efx_Reverbtron->changepar(13,(int)o->value());}
          xywh {160 363 30 15} down_box BORDER_BOX labelsize 10 labelcolor 7
        }
        Fl_Check_Button revtron_es {
          label ES
          user_data 2
          callback {rkr->efx_Reverbtron->changepar(12,(int)o->value());}
          xywh {160 376 29 15} down_box BORDER_BOX labelsize 10 labelcolor 7
        }
        Fl_Check_Button revtron_safe {
          label Safe
          user_data 2
          callback {rkr->efx_Reverbtron->changepar(2,(int)o->value());}
          xywh {188 366 41 15} down_box BORDER_BOX labelsize 10 labelcolor 7
        }
        Fl_Check_Button revtron_user {
          label User
          user_data 2
          callback {rkr->efx_Reverbtron->changepar(4,(int)o->value());

if((int)o->value())B_rvb->activate(); else B_rvb->deactivate();}
          xywh {225 366 39 15} down_box BORDER_BOX labelsize 10 labelcolor 7
        }
        Fl_Button B_rvb {
          label Browse
          user_data 2
          callback {char *filename;
filename=fl_file_chooser("Load rvb File:","(*.rvb)",NULL,0);
if (filename==NULL) return;
filename=fl_filename_setext(filename,".rvb");
strcpy(rkr->efx_Reverbtron->Filename,filename);
rkr->efx_Reverbtron->setfile(100);}
          xywh {264 368 46 10} labelsize 10 deactivate
        }
        Fl_Choice revtron_fnum {
          label File
          user_data 12
          callback {rkr->efx_Reverbtron->changepar(8,(int)o->value());}
          xywh {209 380 101 14} down_box BORDER_BOX selection_color 0 labelsize 10 labelcolor 7 textsize 10 textcolor 7
        } {
          MenuItem {} {
            label Chamber
            xywh {54 54 36 21} labelsize 10
          }
          MenuItem {} {
            label {Conc. Stair}
            xywh {0 0 36 21} labelsize 10
          }
          MenuItem {} {
            label Hall
            xywh {0 0 36 21} labelsize 10
          }
          MenuItem {} {
            label {Med Hall}
            xywh {0 0 36 21} labelsize 10
          }
          MenuItem {} {
            label {Large Room}
            xywh {0 0 36 21} labelsize 10
          }
          MenuItem {} {
            label {Large Hall}
            xywh {0 0 36 21} labelsize 10
          }
          MenuItem {} {
            label {Guitar Ambience}
            xywh {0 0 36 21} labelsize 10
          }
          MenuItem {} {
            label Studio
            xywh {0 0 36 21} labelsize 10
          }
          MenuItem {} {
            label Twilight
            xywh {10 10 36 21} labelsize 10
          }
          MenuItem {} {
            label {Santa Lucia}
            xywh {0 0 36 21} labelsize 10
          }
        }
      }
      Fl_Group ECHOTRON {
        user_data 1
        xywh {323 212 158 184} box UP_BOX color 0 selection_color 0 labelfont 1 align 112 hide
      } {
        Fl_Light_Button echotron_activar {
          label On
          user_data 2
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(116);
 o->value(rkr->Echotron_Bypass);
 return;
}
rkr->Echotron_Bypass=(int)o->value();
if((int) o->value()==0) rkr->efx_Echotron->cleanup();
findpos(41,(int)o->value(),o);}
          xywh {329 216 34 18} shortcut 0x35 color 62 selection_color 1 labelsize 10 align 84 when 1
        }
        Fl_Choice echotron_preset {
          label Preset
          user_data 12041
          callback {long long ud= (long long) v;
if((ud==0)||(ud==12041))rkr->efx_Echotron->setpreset((int) o->value());
echotron_pan->value(rkr->efx_Echotron->getpar(11)-64);
echotron_WD->value(rkr->efx_Echotron->getpar(0)-64);
echotron_damp->value(rkr->efx_Echotron->getpar(6));
echotron_fnum->value(rkr->efx_Echotron->getpar(8));
echotron_user->value(rkr->efx_Echotron->getpar(4));
echotron_user->do_callback();
echotron_fb->value(rkr->efx_Echotron->getpar(10));
echotron_tempo->value(rkr->efx_Echotron->getpar(5));
echotron_lfotype->value(rkr->efx_Echotron->getpar(14));
echotron_width->value(rkr->efx_Echotron->getpar(2));
echotron_deep->value(rkr->efx_Echotron->getpar(1)-64);
echotron_lrcross->value(rkr->efx_Echotron->getpar(7)-64);
echotron_stdf->value(rkr->efx_Echotron->getpar(9));
echotron_af->value(rkr->efx_Echotron->getpar(15));
echotron_mf->value(rkr->efx_Echotron->getpar(13));
echotron_md->value(rkr->efx_Echotron->getpar(12));
echotron_length->value(rkr->efx_Echotron->getpar(3));
echotron_length->maximum(rkr->efx_Echotron->getpar(3));}
          xywh {402 216 76 18} down_box BORDER_BOX selection_color 0 labelsize 10 labelcolor 7 when 6 textsize 10 textcolor 7
        } {
          MenuItem {} {
            label Summer
            xywh {87 87 36 21} labelsize 10
          }
          MenuItem {} {
            label Ambience
            xywh {0 0 36 21} labelsize 10
          }
          MenuItem {} {
            label Arranjer
            xywh {0 0 36 21} labelsize 10
          }
          MenuItem {} {
            label Suction
            xywh {10 10 36 21} labelsize 10
          }
          MenuItem {} {
            label SuctionFlange
            xywh {20 20 36 21} labelsize 10
          }
        }
        Fl_Value_Slider echotron_WD {
          label {Wet/Dry}
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(348);
 return;
}
rkr->efx_Echotron->changepar(0,(int)(o->value()+64));}
          xywh {375 237 100 10} type {Horz Knob} box FLAT_BOX color 178 selection_color 62 labelsize 10 labelcolor 7 align 4 minimum -64 maximum 64 step 1 textcolor 7
          class SliderW
        }
        Fl_Value_Slider echotron_pan {
          label Pan
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(349);
 return;
}
rkr->efx_Echotron->changepar(11,(int)(o->value()+64));}
          xywh {375 249 100 10} type {Horz Knob} box FLAT_BOX color 178 selection_color 62 labelsize 10 labelcolor 7 align 4 minimum -64 maximum 63 step 1 textcolor 7
          class SliderW
        }
        Fl_Value_Slider echotron_tempo {
          label Tempo
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(350);
 return;
}
rkr->efx_Echotron->changepar(5,(int)o->value());}
          xywh {375 261 100 10} type {Horz Knob} box FLAT_BOX color 178 selection_color 62 labelsize 10 labelcolor 7 align 4 when 4 minimum 1 maximum 600 step 1 value 60 textcolor 7
          class SliderW
        }
        Fl_Value_Slider echotron_damp {
          label Damp
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(351);
 return;
}
rkr->efx_Echotron->changepar(6,(int)o->value());}
          xywh {375 273 100 10} type {Horz Knob} box FLAT_BOX color 178 selection_color 62 labelsize 10 labelcolor 7 align 4 maximum 127 step 1 textcolor 7
          class SliderW
        }
        Fl_Value_Slider echotron_fb {
          label Fb
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(352);
 return;
}
rkr->efx_Echotron->changepar(10,(int)o->value());}
          xywh {375 285 100 10} type {Horz Knob} box FLAT_BOX color 178 selection_color 62 labelsize 10 labelcolor 7 align 4 minimum -64 maximum 64 step 1 textcolor 7
          class SliderW
        }
        Fl_Value_Slider echotron_lrcross {
          label {L/R.Cr}
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(353);
 return;
}
rkr->efx_Echotron->changepar(7,(int)(o->value()+64));}
          xywh {375 297 100 10} type {Horz Knob} box FLAT_BOX color 178 selection_color 62 labelsize 10 labelcolor 7 align 4 minimum -64 maximum 64 step 1 textcolor 7
          class SliderW
        }
        Fl_Value_Slider echotron_width {
          label Width
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(354);
 return;
}
rkr->efx_Echotron->changepar(2,(int)o->value());}
          xywh {375 309 100 10} type {Horz Knob} box FLAT_BOX color 178 selection_color 62 labelsize 10 labelcolor 7 align 4 when 4 maximum 127 step 1 textcolor 7
          class SliderW
        }
        Fl_Value_Slider echotron_deep {
          label Depth
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(355);
 return;
}
rkr->efx_Echotron->changepar(1,((int)o->value()+64));}
          xywh {375 321 100 10} type {Horz Knob} box FLAT_BOX color 178 selection_color 62 labelsize 10 labelcolor 7 align 4 when 4 minimum -64 maximum 64 step 1 textcolor 7
          class SliderW
        }
        Fl_Value_Slider echotron_stdf {
          label {St.df}
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(356);
 return;
}
rkr->efx_Echotron->changepar(9,(int)o->value());}
          xywh {375 333 100 10} type {Horz Knob} box FLAT_BOX color 178 selection_color 62 labelsize 10 labelcolor 7 align 4 maximum 127 step 1 textcolor 7
          class SliderW
        }
        Fl_Check_Button echotron_af {
          label AF
          user_data 2
          callback {rkr->efx_Echotron->changepar(15,(int)o->value());}
          xywh {325 348 32 15} down_box BORDER_BOX labelsize 10 labelcolor 7
        }
        Fl_Choice echotron_lfotype {
          label {LFO Type}
          callback {rkr->efx_Echotron->changepar(14,(int)o->value());} open
          xywh {411 347 64 16} down_box BORDER_BOX selection_color 0 labelsize 10 labelcolor 7 textsize 10 textcolor 7
          code0 {o->menu(menu_chorus_lfotype);}
        } {}
        Fl_Check_Button echotron_mf {
          label MF
          user_data 2
          callback {rkr->efx_Echotron->changepar(13,(int)o->value());}
          xywh {325 363 33 15} down_box BORDER_BOX labelsize 10 labelcolor 7
        }
        Fl_Check_Button echotron_md {
          label MD
          user_data 2
          callback {rkr->efx_Echotron->changepar(12,(int)o->value());}
          xywh {356 363 34 15} down_box BORDER_BOX labelsize 10 labelcolor 7
        }
        Fl_Check_Button echotron_user {
          label User
          user_data 2
          callback {rkr->efx_Echotron->changepar(4,(int)o->value());

if((int)o->value())B_ech->activate(); else B_ech->deactivate();}
          xywh {390 366 39 15} down_box BORDER_BOX labelsize 10 labelcolor 7
        }
        Fl_Button B_ech {
          label Browse
          user_data 2
          callback {char *filename;
filename=fl_file_chooser("Load dly File:","(*.dly)",NULL,0);
if (filename==NULL) return;
filename=fl_filename_setext(filename,".dly");
strcpy(rkr->efx_Echotron->Filename,filename);
rkr->efx_Echotron->setfile(100);
echotron_length->value(rkr->efx_Echotron->getpar(3));
echotron_length->maximum(rkr->efx_Echotron->getpar(3));}
          xywh {429 368 46 10} labelsize 10 deactivate
        }
        Fl_Counter echotron_length {
          label {\#}
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(357);
 return;
}
rkr->efx_Echotron->changepar(3,(int)o->value());}
          xywh {339 379 48 12} type Simple labelsize 10 labelcolor 7 align 4 when 4 minimum 1 maximum 127 step 1 value 1 textsize 9
        }
        Fl_Choice echotron_fnum {
          label File
          user_data 12
          callback {rkr->efx_Echotron->changepar(8,(int)o->value());
echotron_length->value(rkr->efx_Echotron->getpar(3));
echotron_length->maximum(rkr->efx_Echotron->getpar(3));}
          xywh {411 380 64 14} down_box BORDER_BOX selection_color 0 labelsize 10 labelcolor 7 textsize 10 textcolor 7
        } {
          MenuItem {} {
            label SwingPong
            xywh {64 64 36 21} labelsize 10
          }
          MenuItem {} {
            label {Short Delays}
            xywh {0 0 36 21} labelsize 10
          }
          MenuItem {} {
            label {Flange + Echo}
            xywh {0 0 36 21} labelsize 10
          }
          MenuItem {} {
            label Comb
            xywh {0 0 36 21} labelsize 10
          }
          MenuItem {} {
            label EchoFlange
            xywh {0 0 36 21} labelsize 10
          }
          MenuItem {} {
            label {Filtered Echo}
            xywh {0 0 36 21} labelsize 10
          }
          MenuItem {} {
            label {Notch-Wah}
            xywh {0 0 36 21} labelsize 10
          }
          MenuItem {} {
            label {Multi-Chorus}
            xywh {10 10 36 21} labelsize 10
          }
          MenuItem {} {
            label PingPong
            xywh {20 20 36 21} labelsize 10
          }
          MenuItem {} {
            label {90-Shifter}
            xywh {30 30 36 21} labelsize 10
          }
          MenuItem {} {
            label {Basic LR Delay}
            xywh {40 40 36 21} labelsize 10
          }
        }
      }
      Fl_Group SHAR {
        user_data 1
        xywh {481 212 158 184} box UP_BOX color 0 selection_color 0 labelfont 1 align 112 hide
      } {
        Fl_Light_Button shar_activar {
          label On
          user_data 2
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(116);
 o->value(rkr->StereoHarm_Bypass);
 return;
}
rkr->StereoHarm_Bypass=(int)o->value();
if((int) o->value()==0)
rkr->efx_StereoHarm->cleanup();
rkr->efx_StereoHarm->changepar(3,rkr->efx_StereoHarm->getpar(3));
rkr->efx_StereoHarm->changepar(6,rkr->efx_StereoHarm->getpar(6));
Chord(1);
findpos(42,(int)o->value(),o);}
          xywh {486 216 34 18} shortcut 0x30 color 62 selection_color 1 labelsize 10 when 1
        }
        Fl_Choice shar_preset {
          label Preset
          user_data 12042
          callback {long long ud= (long long) v;
if((ud==0)||(ud==12042))rkr->efx_StereoHarm->setpreset((int)o->value());
shar_WD->value(rkr->efx_StereoHarm->getpar(0)-64);
shar_ganl->value(rkr->efx_StereoHarm->getpar(1)-64);
shar_intl->value(rkr->efx_StereoHarm->getpar(2)-12);
shar_chl->value(rkr->efx_StereoHarm->getpar(3));
shar_ganr->value(rkr->efx_StereoHarm->getpar(4)-64);
shar_intr->value(rkr->efx_StereoHarm->getpar(5)-12);
shar_chr->value(rkr->efx_StereoHarm->getpar(6));
shar_lrc->value(rkr->efx_StereoHarm->getpar(11)-64);
shar_SELECT->value(rkr->efx_StereoHarm->getpar(7));
shar_note->value(rkr->efx_StereoHarm->getpar(8));
shar_type->value(rkr->efx_StereoHarm->getpar(9));
shar_MIDI->value(rkr->efx_StereoHarm->getpar(10));
if ((rkr->efx_StereoHarm->PMIDI) || (rkr->efx_StereoHarm->PSELECT)) Chord(1);}
          xywh {558 216 76 18} down_box BORDER_BOX selection_color 0 labelsize 10 labelcolor 7 when 6 textsize 10 textcolor 7
        } {
          MenuItem {} {
            label Plain
            xywh {10 10 45 26} labelsize 10
          }
          MenuItem {} {
            label Octavator
            xywh {42 42 36 21} labelsize 10
          }
          MenuItem {} {
            label Chorus
            xywh {42 42 36 21} labelsize 10
          }
          MenuItem {} {
            label {Hard Chorus}
            xywh {0 0 36 21} labelsize 10
          }
        }
        Fl_Value_Slider shar_WD {
          label {Wet/Dry}
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(358);
 return;
}
rkr->efx_StereoHarm->changepar(0,(int)(o->value()+64));}
          xywh {531 238 100 10} type {Horz Knob} box FLAT_BOX color 178 selection_color 62 labelsize 10 labelcolor 7 align 4 minimum -64 maximum 63 step 1 textcolor 7
          class SliderW
        }
        Fl_Value_Slider shar_intl {
          label {Int L}
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(359);
 return;
}
rkr->StereoHarm_Bypass=0;
rkr->efx_StereoHarm->changepar(2,(int)(o->value()+12));
if((int)shar_activar->value())rkr->StereoHarm_Bypass=1;}
          xywh {531 251 100 10} type {Horz Knob} box FLAT_BOX color 178 selection_color 62 labelsize 10 labelcolor 7 align 4 minimum -12 maximum 12 step 1 textcolor 7
          class SliderW
        }
        Fl_Value_Slider shar_chl {
          label {Chrm L}
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(360);
 return;
}
rkr->efx_StereoHarm->changepar(3,(int)o->value());}
          xywh {531 264 100 10} type {Horz Knob} box FLAT_BOX color 178 selection_color 62 labelsize 10 labelcolor 7 align 4 minimum -2000 maximum 2000 step 1 textcolor 7
          class SliderW
        }
        Fl_Value_Slider shar_ganl {
          label {Gain L}
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(361);
 return;
}
rkr->efx_StereoHarm->changepar(1,(int)(o->value()+64));}
          xywh {531 277 100 10} type {Horz Knob} box FLAT_BOX color 178 selection_color 62 labelsize 10 labelcolor 7 align 4 minimum -64 maximum 64 step 1 textcolor 7
          class SliderW
        }
        Fl_Value_Slider shar_intr {
          label {Int R}
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(362);
 return;
}
rkr->StereoHarm_Bypass=0;
rkr->efx_StereoHarm->changepar(5,(int)(o->value()+12));
if((int)shar_activar->value())rkr->StereoHarm_Bypass=1;}
          xywh {531 290 100 10} type {Horz Knob} box FLAT_BOX color 178 selection_color 62 labelsize 10 labelcolor 7 align 4 minimum -12 maximum 12 step 1 textcolor 7
          class SliderW
        }
        Fl_Value_Slider shar_chr {
          label {Chrm R}
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(363);
 return;
}
rkr->efx_StereoHarm->changepar(6,(int)o->value());}
          xywh {531 303 100 10} type {Horz Knob} box FLAT_BOX color 178 selection_color 62 labelsize 10 labelcolor 7 align 4 minimum -2000 maximum 2000 step 1 textcolor 7
          class SliderW
        }
        Fl_Value_Slider shar_ganr {
          label {Gain R}
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(364);
 return;
}
rkr->efx_StereoHarm->changepar(4,(int)(o->value()+64));}
          xywh {531 316 100 10} type {Horz Knob} box FLAT_BOX color 178 selection_color 62 labelsize 10 labelcolor 7 align 4 minimum -64 maximum 64 step 1 textcolor 7
          class SliderW
        }
        Fl_Value_Slider shar_lrc {
          label {L/R.Cr}
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(365);
 return;
}
rkr->efx_StereoHarm->changepar(11,(int)(o->value()+64));}
          xywh {531 329 100 10} type {Horz Knob} box FLAT_BOX color 178 selection_color 62 labelsize 10 labelcolor 7 align 4 minimum -64 maximum 64 step 1 textcolor 7
          class SliderW
        }
        Fl_Check_Button shar_MIDI {
          label MIDI
          user_data 2
          callback {rkr->efx_StereoHarm->changepar(10,(int)o->value());
rkr->RC->cleanup();

if(!(int)o->value())
{
rkr->efx_StereoHarm->changepar(3,rkr->efx_StereoHarm->getpar(3));
rkr->efx_StereoHarm->changepar(6,rkr->efx_StereoHarm->getpar(6));
}}
          xywh {490 341 15 15} down_box BORDER_BOX labelsize 10 labelcolor 7 align 8
        }
        Fl_Check_Button shar_SELECT {
          label SEL
          user_data 2
          callback {rkr->efx_StereoHarm->changepar(7,(int)o->value());
rkr->RC->cleanup();
Chord(1);

if(!(int)o->value())
{
rkr->efx_StereoHarm->changepar(3,rkr->efx_StereoHarm->getpar(3));
rkr->efx_StereoHarm->changepar(6,rkr->efx_StereoHarm->getpar(6));
}}
          xywh {490 354 15 15} down_box BORDER_BOX labelsize 10 labelcolor 7 align 8
        }
        Fl_Box shar_chordname {
          xywh {537 344 98 21} labelsize 12 labelcolor 7
        }
        Fl_Value_Slider shar_note {
          label Note
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(366);
 return;
}
rkr->efx_StereoHarm->changepar(8,(int)o->value());
Chord(1);}
          xywh {531 370 100 10} type {Horz Knob} box FLAT_BOX color 178 selection_color 62 labelsize 10 labelcolor 7 align 4 maximum 23 step 1 textcolor 7
          class SliderW
        }
        Fl_Value_Slider shar_type {
          label Chord
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(367);
 return;
}
rkr->efx_StereoHarm->changepar(9,(int)o->value());
Chord(1);}
          xywh {531 382 100 10} type {Horz Knob} box FLAT_BOX color 178 selection_color 62 labelsize 10 labelcolor 7 align 4 maximum 33 step 1 textcolor 7
          class SliderW
        }
      }
      Fl_Group COMPBAND {
        user_data 1
        xywh {162 211 158 184} box UP_BOX color 0 selection_color 0 labelfont 1 align 112 hide
      } {
        Fl_Light_Button cband_activar {
          label On
          user_data 2
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(116);
 o->value(rkr->CompBand_Bypass);
 return;
}
rkr->CompBand_Bypass=(int)o->value();
if((int) o->value()==0)
rkr->efx_CompBand->cleanup();
findpos(43,(int)o->value(),o);}
          xywh {167 215 34 18} shortcut 0x38 color 62 selection_color 1 labelsize 10 align 84 when 1
        }
        Fl_Choice cband_preset {
          label Preset
          user_data 12043
          callback {long long ud= (long long) v;
if((ud==0)||(ud==12043))rkr->efx_CompBand->setpreset((int)o->value());
cband_WD->value(rkr->efx_CompBand->getpar(0)-64);
cband_Lratio->value(rkr->efx_CompBand->getpar(1));
cband_MLratio->value(rkr->efx_CompBand->getpar(2));
cband_MHratio->value(rkr->efx_CompBand->getpar(3));
cband_Hratio->value(rkr->efx_CompBand->getpar(4));
cband_Lthres->value(rkr->efx_CompBand->getpar(5));
cband_MLthres->value(rkr->efx_CompBand->getpar(6));
cband_MHthres->value(rkr->efx_CompBand->getpar(7));
cband_Hthres->value(rkr->efx_CompBand->getpar(8));
cband_cross1->value(rkr->efx_CompBand->getpar(9));
cband_cross2->value(rkr->efx_CompBand->getpar(10));
cband_cross3->value(rkr->efx_CompBand->getpar(11));
cband_cross3->value(rkr->efx_CompBand->getpar(11));
cband_gain->value(rkr->efx_CompBand->getpar(12));}
          xywh {239 215 76 18} down_box BORDER_BOX selection_color 0 labelsize 10 labelcolor 7 when 6 textsize 10 textcolor 7
        } {
          MenuItem {} {
            label {Good Start}
            xywh {82 82 36 21} labelsize 10
          }
          MenuItem {} {
            label Loudness
            xywh {82 82 36 21} labelsize 10
          }
          MenuItem {} {
            label {Loudness 2}
            xywh {82 82 36 21} labelsize 10
          }
        }
        Fl_Value_Slider cband_WD {
          label {Wet/Dry}
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(368);
 return;
}
rkr->efx_CompBand->changepar(0,(int)(o->value()+64));}
          xywh {214 238 100 10} type {Horz Knob} box FLAT_BOX color 178 selection_color 62 labelsize 10 labelcolor 7 align 4 minimum -64 maximum 64 step 1 textcolor 7
          class SliderW
        }
        Fl_Value_Slider cband_gain {
          label Gain
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(369);
 return;
}
rkr->efx_CompBand->changepar(12,(int)o->value());}
          xywh {214 250 100 10} type {Horz Knob} box FLAT_BOX color 178 selection_color 62 labelsize 10 labelcolor 7 align 4 maximum 127 step 1 textcolor 7
          class SliderW
        }
        Fl_Value_Slider cband_Lratio {
          label {L Ratio}
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(370);
 return;
}
rkr->efx_CompBand->changepar(1, (int) o->value());}
          xywh {214 262 100 10} type {Horz Knob} box FLAT_BOX color 178 selection_color 62 labelsize 10 labelcolor 7 align 4 minimum 2 maximum 42 step 1 value 2 textcolor 7
          class SliderW
        }
        Fl_Value_Slider cband_MLratio {
          label {ML Ratio}
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(371);
 return;
}
rkr->efx_CompBand->changepar(2, (int) o->value());}
          xywh {214 274 100 10} type {Horz Knob} box FLAT_BOX color 178 selection_color 62 labelsize 10 labelcolor 7 align 4 minimum 2 maximum 42 step 1 value 2 textcolor 7
          class SliderW
        }
        Fl_Value_Slider cband_MHratio {
          label {MH Ratio}
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(372);
 return;
}
rkr->efx_CompBand->changepar(3, (int) o->value());}
          xywh {214 286 100 10} type {Horz Knob} box FLAT_BOX color 178 selection_color 62 labelsize 10 labelcolor 7 align 4 minimum 2 maximum 42 step 1 value 2 textcolor 7
          class SliderW
        }
        Fl_Value_Slider cband_Hratio {
          label {H Ratio}
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(373);
 return;
}
rkr->efx_CompBand->changepar(4, (int) o->value());}
          xywh {214 298 100 10} type {Horz Knob} box FLAT_BOX color 178 selection_color 62 labelsize 10 labelcolor 7 align 4 minimum 2 maximum 42 step 1 value 2 textcolor 7
          class SliderW
        }
        Fl_Value_Slider cband_Lthres {
          label {L Thres}
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(374);
 return;
}
rkr->efx_CompBand->changepar(5, (int)o->value());}
          xywh {214 310 100 10} type {Horz Knob} box FLAT_BOX color 178 selection_color 62 labelsize 10 labelcolor 7 align 4 minimum -70 maximum 24 step 1 textcolor 7
          class SliderW
        }
        Fl_Value_Slider cband_MLthres {
          label {ML Thres}
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(375);
 return;
}
rkr->efx_CompBand->changepar(6, (int)o->value());}
          xywh {214 322 100 10} type {Horz Knob} box FLAT_BOX color 178 selection_color 62 labelsize 10 labelcolor 7 align 4 minimum -70 maximum 24 step 1 textcolor 7
          class SliderW
        }
        Fl_Value_Slider cband_MHthres {
          label {MH Thres}
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(376);
 return;
}
rkr->efx_CompBand->changepar(7, (int)o->value());}
          xywh {214 334 100 10} type {Horz Knob} box FLAT_BOX color 178 selection_color 62 labelsize 10 labelcolor 7 align 4 minimum -70 maximum 24 step 1 textcolor 7
          class SliderW
        }
        Fl_Value_Slider cband_Hthres {
          label {H Thres}
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(377);
 return;
}
rkr->efx_CompBand->changepar(8, (int)o->value());}
          xywh {214 346 100 10} type {Horz Knob} box FLAT_BOX color 178 selection_color 62 labelsize 10 labelcolor 7 align 4 minimum -70 maximum 24 step 1 textcolor 7
          class SliderW
        }
        Fl_Value_Slider cband_cross1 {
          label Cross1
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(378);
 return;
}
rkr->efx_CompBand->changepar(9,(int)o->value());}
          xywh {214 358 100 10} type {Horz Knob} box FLAT_BOX color 178 selection_color 62 labelsize 10 labelcolor 7 align 4 minimum 20 maximum 1000 step 1 textcolor 7
          class SliderW
        }
        Fl_Value_Slider cband_cross2 {
          label Cross2
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(379);
 return;
}
rkr->efx_CompBand->changepar(10,(int)o->value());}
          xywh {214 370 100 10} type {Horz Knob} box FLAT_BOX color 178 selection_color 62 labelsize 10 labelcolor 7 align 4 minimum 1000 maximum 8000 step 1 textcolor 7
          class SliderW
        }
        Fl_Value_Slider cband_cross3 {
          label Cross3
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(380);
 return;
}
rkr->efx_CompBand->changepar(11,(int)o->value());}
          xywh {214 382 100 10} type {Horz Knob} box FLAT_BOX color 178 selection_color 62 labelsize 10 labelcolor 7 align 4 minimum 2000 maximum 26000 step 1 textcolor 7
          class SliderW
        }
      }
      Fl_Group OTREM {
        user_data 1
        xywh {320 213 158 184} box UP_BOX color 0 selection_color 0 labelfont 1 align 112 hide
      } {
        Fl_Light_Button otrem_activar {
          label On
          user_data 2
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(116);
 o->value(rkr->Opticaltrem_Bypass);
 return;
}
rkr->Opticaltrem_Bypass=(int)o->value();
if((int) o->value()==0)
rkr->efx_Opticaltrem->cleanup();
findpos(44,(int)o->value(),o);}
          xywh {325 217 34 18} shortcut 0x38 color 62 selection_color 1 labelsize 10 align 84 when 1
        }
        Fl_Choice otrem_preset {
          label Preset
          user_data 12044
          callback {long long ud= (long long) v;
if((ud==0)||(ud==12044))rkr->efx_Opticaltrem->setpreset((int)o->value());
otrem_dpth->value(rkr->efx_Opticaltrem->getpar(0));
otrem_freq->value(rkr->efx_Opticaltrem->getpar(1));
otrem_rnd->value(rkr->efx_Opticaltrem->getpar(2));
otrem_lfotype->value(rkr->efx_Opticaltrem->getpar(3));
otrem_stdf->value(rkr->efx_Opticaltrem->getpar(4));
otrem_pan->value(rkr->efx_Opticaltrem->getpar(5)-64);}
          xywh {397 217 76 18} down_box BORDER_BOX selection_color 0 labelsize 10 labelcolor 7 when 6 textsize 10 textcolor 7
        } {
          MenuItem {} {
            label Fast
            xywh {72 72 36 21} labelsize 10
          }
          MenuItem {} {
            label {Trem 2}
            xywh {72 72 36 21} labelsize 10
          }
          MenuItem {} {
            label {Hard Pan}
            xywh {0 0 36 21} labelsize 10
          }
          MenuItem {} {
            label {Soft Pan}
            xywh {0 0 36 21} labelsize 10
          }
          MenuItem {} {
            label {Ramp Down}
            xywh {0 0 36 21} labelsize 10
          }
          MenuItem {} {
            label {Hard Ramp}
            xywh {0 0 36 21} labelsize 10
          }
        }
        Fl_Value_Slider otrem_dpth {
          label Depth
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(381);
 return;
}
rkr->efx_Opticaltrem->changepar(0,(int)o->value());}
          xywh {372 246 100 10} type {Horz Knob} box FLAT_BOX color 178 selection_color 62 labelsize 10 labelcolor 7 align 4 maximum 127 step 1 textcolor 7
          class SliderW
        }
        Fl_Value_Slider otrem_freq {
          label Tempo
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(382);
 return;
}
rkr->efx_Opticaltrem->changepar(1,(int)o->value());}
          xywh {372 266 100 10} type {Horz Knob} box FLAT_BOX color 178 selection_color 62 labelsize 10 labelcolor 7 align 4 minimum 1 maximum 600 step 1 textcolor 7
          class SliderW
        }
        Fl_Value_Slider otrem_rnd {
          label Rnd
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(383);
 return;
}
rkr->efx_Opticaltrem->changepar(2,(int)o->value());}
          xywh {372 286 100 10} type {Horz Knob} box FLAT_BOX color 178 selection_color 62 labelsize 10 labelcolor 7 align 4 maximum 127 step 1 textcolor 7
          class SliderW
        }
        Fl_Choice otrem_lfotype {
          label {LFO Type}
          callback {rkr->efx_Opticaltrem->changepar(3,(int)o->value());}
          xywh {383 313 72 16} down_box BORDER_BOX selection_color 0 labelsize 10 labelcolor 7 textsize 10 textcolor 7
          code0 {o->menu(menu_chorus_lfotype);}
        } {}
        Fl_Value_Slider otrem_stdf {
          label {St.df}
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(384);
 return;
}
rkr->efx_Opticaltrem->changepar(4,(int)o->value());}
          xywh {372 340 100 10} type {Horz Knob} box FLAT_BOX color 178 selection_color 62 labelsize 10 labelcolor 7 align 4 maximum 127 step 1 textcolor 7
          class SliderW
        }
        Fl_Value_Slider otrem_pan {
          label Pan
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(385);
 return;
}
rkr->efx_Opticaltrem->changepar(5,(int)(o->value()+64));}
          xywh {372 360 100 10} type {Horz Knob} box FLAT_BOX color 178 selection_color 62 labelsize 10 labelcolor 7 align 4 minimum -64 maximum 63 step 1 textcolor 7
          class SliderW
        }
      }
      Fl_Group VIBE {
        user_data 1
        xywh {480 211 158 184} box UP_BOX color 0 selection_color 0 labelfont 1 align 112
      } {
        Fl_Light_Button vibe_activar {
          label On
          user_data 2
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(116);
 o->value(rkr->Vibe_Bypass);
 return;
}
rkr->Vibe_Bypass=(int)o->value();
if((int) o->value()==0)
rkr->efx_Vibe->cleanup();
findpos(45,(int)o->value(),o);}
          xywh {485 215 34 18} shortcut 0x38 color 62 selection_color 1 labelsize 10 align 84 when 1
        }
        Fl_Choice vibe_preset {
          label Preset
          user_data 12045
          callback {long long ud= (long long) v;
if((ud==0)||(ud==12045))rkr->efx_Vibe->setpreset((int)o->value());
vibe_WD->value(rkr->efx_Vibe->getpar(6)-64);
vibe_width->value(rkr->efx_Vibe->getpar(0));
vibe_dpth->value(rkr->efx_Vibe->getpar(8));
vibe_freq->value(rkr->efx_Vibe->getpar(1));
vibe_rnd->value(rkr->efx_Vibe->getpar(2));
vibe_lfotype->value(rkr->efx_Vibe->getpar(3));
vibe_stdf->value(rkr->efx_Vibe->getpar(4));
vibe_pan->value(rkr->efx_Vibe->getpar(5)-64);
vibe_fb->value(rkr->efx_Vibe->getpar(7)-64);
vibe_LR->value(rkr->efx_Vibe->getpar(9)-64);
vibe_stereo->value(rkr->efx_Vibe->getpar(10));}
          xywh {557 215 76 18} down_box BORDER_BOX selection_color 0 labelsize 10 labelcolor 7 when 6 textsize 10 textcolor 7
        } {
          MenuItem {} {
            label Classic
            xywh {82 82 36 21} labelsize 10
          }
          MenuItem {} {
            label {Stereo Classic}
            xywh {82 82 36 21} labelsize 10
          }
          MenuItem {} {
            label {Wide Vibe}
            xywh {10 10 36 21} labelsize 10
          }
          MenuItem {} {
            label {Classic Chorus}
            xywh {10 10 36 21} labelsize 10
          }
          MenuItem {} {
            label {Vibe Chorus}
            xywh {10 10 36 21} labelsize 10
          }
          MenuItem {} {
            label {Lush Chorus}
            xywh {10 10 36 21} labelsize 10
          }
          MenuItem {} {
            label {Sick Phaser}
            xywh {0 0 36 21} labelsize 10
          }
          MenuItem {} {
            label Warble
            xywh {0 0 36 21} labelsize 10
          }
        }
        Fl_Value_Slider vibe_WD {
          label {Wet/Dry}
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(386);
 return;
}
rkr->efx_Vibe->changepar(6,(int)(o->value())+64);}
          xywh {532 240 100 10} type {Horz Knob} box FLAT_BOX color 178 selection_color 62 labelsize 10 labelcolor 7 align 4 minimum -64 maximum 64 step 1 textcolor 7
          class SliderW
        }
        Fl_Value_Slider vibe_width {
          label Width
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(387);
 return;
}
rkr->efx_Vibe->changepar(0,(int)o->value());}
          xywh {532 253 100 10} type {Horz Knob} box FLAT_BOX color 178 selection_color 62 labelsize 10 labelcolor 7 align 4 maximum 127 step 1 textcolor 7
          class SliderW
        }
        Fl_Value_Slider vibe_dpth {
          label Depth
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(388);
 return;
}
rkr->efx_Vibe->changepar(8,(int)o->value());}
          xywh {532 266 100 10} type {Horz Knob} box FLAT_BOX color 178 selection_color 62 labelsize 10 labelcolor 7 align 4 maximum 127 step 1 textcolor 7
          class SliderW
        }
        Fl_Value_Slider vibe_freq {
          label Tempo
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(389);
 return;
}
rkr->efx_Vibe->changepar(1,(int)o->value());}
          xywh {532 279 100 10} type {Horz Knob} box FLAT_BOX color 178 selection_color 62 labelsize 10 labelcolor 7 align 4 minimum 1 maximum 600 step 1 textcolor 7
          class SliderW
        }
        Fl_Value_Slider vibe_rnd {
          label Rnd
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(390);
 return;
}
rkr->efx_Vibe->changepar(2,(int)o->value());}
          xywh {532 292 100 10} type {Horz Knob} box FLAT_BOX color 178 selection_color 62 labelsize 10 labelcolor 7 align 4 maximum 127 step 1 textcolor 7
          class SliderW
        }
        Fl_Choice vibe_lfotype {
          label {LFO Type}
          callback {rkr->efx_Vibe->changepar(3,(int)o->value());}
          xywh {543 307 72 16} down_box BORDER_BOX selection_color 0 labelsize 10 labelcolor 7 textsize 10 textcolor 7
          code0 {o->menu(menu_chorus_lfotype);}
        } {}
        Fl_Value_Slider vibe_stdf {
          label {St.df}
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(391);
 return;
}
rkr->efx_Vibe->changepar(4,(int)o->value());}
          xywh {532 329 100 10} type {Horz Knob} box FLAT_BOX color 178 selection_color 62 labelsize 10 labelcolor 7 align 4 maximum 127 step 1 textcolor 7
          class SliderW
        }
        Fl_Value_Slider vibe_fb {
          label Fb
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(392);
 return;
}
rkr->efx_Vibe->changepar(7,(int)(o->value()+64));}
          xywh {532 342 100 10} type {Horz Knob} box FLAT_BOX color 178 selection_color 62 labelsize 10 labelcolor 7 align 4 minimum -64 maximum 64 step 1 textcolor 7
          class SliderW
        }
        Fl_Value_Slider vibe_LR {
          label {L/R.Cr}
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(393);
 return;
}
rkr->efx_Vibe->changepar(9,(int)(o->value()+64));}
          xywh {532 355 100 10} type {Horz Knob} box FLAT_BOX color 178 selection_color 62 labelsize 10 labelcolor 7 align 4 minimum -64 maximum 64 step 1 textcolor 7
          class SliderW
        }
        Fl_Value_Slider vibe_pan {
          label Pan
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(394);
 return;
}
rkr->efx_Vibe->changepar(5,(int)(o->value()+64));}
          xywh {532 368 100 10} type {Horz Knob} box FLAT_BOX color 178 selection_color 62 labelsize 10 labelcolor 7 align 4 minimum -64 maximum 64 step 1 textcolor 7
          class SliderW
        }
        Fl_Check_Button vibe_stereo {
          label Stereo
          user_data 2
          callback {rkr->efx_Vibe->changepar(10,(int)o->value())}
          xywh {583 380 43 14} down_box BORDER_BOX labelsize 10 labelcolor 7
        }
      }
      Fl_Group INFINIT {
        user_data 1
        xywh {479 212 158 184} box UP_BOX color 0 selection_color 0 labelfont 1 align 112 hide
      } {
        Fl_Light_Button infinity_activar {
          label On
          user_data 2
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(116); 
 o->value(rkr->Infinity_Bypass);
 return;
} 
rkr->Infinity_Bypass=(int)o->value();
if((int) o->value()==0)
rkr->efx_Infinity->cleanup();
findpos(46,(int)o->value(),o);}
          xywh {487 217 34 18} shortcut 0x31 color 62 selection_color 1 labelsize 10 align 84 when 1
        }
        Fl_Choice infinity_preset {
          label Preset
          user_data 12046
          callback {long long ud= (long long) v;
if((ud==0)||(ud==12046))rkr->efx_Infinity->setpreset((int) o->value());
infinity_WD->value(rkr->efx_Infinity->getpar(0)-64);
infinity_Q->value(rkr->efx_Infinity->getpar(9));
infinity_1->value(rkr->efx_Infinity->getpar(1));
infinity_2->value(rkr->efx_Infinity->getpar(2));
infinity_3->value(rkr->efx_Infinity->getpar(3));
infinity_4->value(rkr->efx_Infinity->getpar(4));
infinity_5->value(rkr->efx_Infinity->getpar(5));
infinity_6->value(rkr->efx_Infinity->getpar(6));
infinity_7->value(rkr->efx_Infinity->getpar(7));
infinity_8->value(rkr->efx_Infinity->getpar(8));
infinity_start->value(rkr->efx_Infinity->getpar(10));
infinity_end->value(rkr->efx_Infinity->getpar(11));
infinity_rate->value(rkr->efx_Infinity->getpar(12));
infinity_stdf->value(rkr->efx_Infinity->getpar(13));
infinity_subdiv->value(rkr->efx_Infinity->getpar(14));
infinity_pan->value(rkr->efx_Infinity->getpar(15));
infinity_rev->value(rkr->efx_Infinity->getpar(16));
infinity_stages->value(rkr->efx_Infinity->getpar(17));}
          xywh {559 217 76 18} down_box BORDER_BOX selection_color 0 labelsize 10 labelcolor 7 when 6 textsize 10 textcolor 7
        } {
          MenuItem {} {
            label Basic
            xywh {27 27 36 21} labelsize 10
          }
          MenuItem {} {
            label {Rising Comb}
            xywh {0 0 36 21} labelsize 10
          }
          MenuItem {} {
            label {Falling Comb}
            xywh {0 0 36 21} labelsize 10
          }
          MenuItem {} {
            label Laser
            xywh {0 0 36 21} labelsize 10
          }
          MenuItem {} {
            label Doppler
            xywh {10 10 36 21} labelsize 10
          }
          MenuItem {} {
            label Detune
            xywh {20 20 36 21} labelsize 10
          }
          MenuItem {} {
            label {Dizzy Sailor}
            xywh {30 30 36 21} labelsize 10
          }
          MenuItem {} {
            label {Stereo Phaser}
            xywh {40 40 36 21} labelsize 10
          }
          MenuItem {} {
            label Corkscrew
            xywh {50 50 36 21} labelsize 10
          }
          MenuItem {} {
            label FreqeeVox
            xywh {60 60 36 21} labelsize 10
          }
        }
        Fl_Value_Slider infinity_WD {
          label {Wet/Dry}
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(395);
 return;
} 
rkr->efx_Infinity->changepar(0,(int)(o->value()+64));}
          xywh {531 239 100 10} type {Horz Knob} box FLAT_BOX color 178 selection_color 62 labelsize 10 labelcolor 7 align 4 minimum -64 maximum 63 step 1 textcolor 7
          class SliderW
        }
        Fl_Value_Slider infinity_Q {
          label Res
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(396);
 return;
}
rkr->efx_Infinity->changepar(9,(int)o->value());}
          xywh {531 253 100 10} type {Horz Knob} box FLAT_BOX color 178 selection_color 62 labelsize 10 labelcolor 7 align 4 minimum -1000 maximum 1000 step 1 textcolor 7
          class SliderW
        }
        Fl_Value_Input infinity_1 {
          label 1
          callback {rkr->efx_Infinity->changepar(1,(int)o->value());}
          xywh {495 268 20 15} labelsize 10 labelcolor 7 minimum -64 maximum 64 step 1 textsize 10 textcolor 7
        }
        Fl_Value_Input infinity_2 {
          label 2
          callback {rkr->efx_Infinity->changepar(2,(int)o->value());}
          xywh {531 268 20 15} labelsize 10 labelcolor 7 minimum -64 maximum 64 step 1 textsize 10 textcolor 7
        }
        Fl_Value_Input infinity_3 {
          label 3
          callback {rkr->efx_Infinity->changepar(3,(int)o->value());}
          xywh {567 267 20 15} labelsize 10 labelcolor 7 minimum -64 maximum 64 step 1 textsize 10 textcolor 7
        }
        Fl_Value_Input infinity_4 {
          label 4
          callback {rkr->efx_Infinity->changepar(4,(int)o->value());}
          xywh {603 267 20 15} labelsize 10 labelcolor 7 minimum -64 maximum 64 step 1 textsize 10 textcolor 7
        }
        Fl_Value_Input infinity_5 {
          label 5
          callback {rkr->efx_Infinity->changepar(5,(int)o->value());}
          xywh {495 286 20 15} labelsize 10 labelcolor 7 minimum -64 maximum 64 step 1 textsize 10 textcolor 7
        }
        Fl_Value_Input infinity_6 {
          label 6
          callback {rkr->efx_Infinity->changepar(6,(int)o->value());}
          xywh {531 286 20 15} labelsize 10 labelcolor 7 minimum -64 maximum 64 step 1 textsize 10 textcolor 7
        }
        Fl_Value_Input infinity_7 {
          label 7
          callback {rkr->efx_Infinity->changepar(7,(int)o->value());}
          xywh {567 286 20 15} labelsize 10 labelcolor 7 minimum -64 maximum 64 step 1 textsize 10 textcolor 7
        }
        Fl_Value_Input infinity_8 {
          label 8
          callback {rkr->efx_Infinity->changepar(8,(int)o->value());}
          xywh {603 286 20 15} labelsize 10 labelcolor 7 minimum -64 maximum 64 step 1 textsize 10 textcolor 7
        }
        Fl_Check_Button infinity_rev {
          label Rev
          user_data 2
          callback {rkr->efx_Infinity->changepar(16,(int)o->value());}
          tooltip {Reverse left from right directions} xywh {485 305 15 15} down_box BORDER_BOX labelsize 10 labelcolor 7 align 8
        }
        Fl_Counter infinity_stages {
          label Stages
          callback {rkr->efx_Infinity->changepar(17,(int)o->value());}
          xywh {569 305 46 15} type Simple labelsize 10 labelcolor 7 align 4 minimum 1 maximum 12 step 1 value 1 textsize 10
        }
        Fl_Value_Slider infinity_pan {
          label AutoPan
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(397);
 return;
} 
rkr->efx_Infinity->changepar(15,(int)o->value());}
          xywh {531 323 100 10} type {Horz Knob} box FLAT_BOX color 178 selection_color 62 labelsize 10 labelcolor 7 align 4 maximum 127 step 1 textcolor 7
          class SliderW
        }
        Fl_Value_Slider infinity_stdf {
          label {St.df}
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(398);
 return;
} 
rkr->efx_Infinity->changepar(13,(int)o->value());}
          xywh {531 335 100 10} type {Horz Knob} box FLAT_BOX color 178 selection_color 62 labelsize 10 labelcolor 7 align 4 minimum -64 maximum 64 step 1 textcolor 7
          class SliderW
        }
        Fl_Value_Slider infinity_start {
          label Start
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(399);
 return;
} 
rkr->efx_Infinity->changepar(10,(int)o->value());}
          xywh {531 347 100 10} type {Horz Knob} box FLAT_BOX color 178 selection_color 62 labelsize 10 labelcolor 7 align 4 maximum 127 step 1 textcolor 7
          class SliderW
        }
        Fl_Value_Slider infinity_end {
          label End
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(400);
 return;
} 
rkr->efx_Infinity->changepar(11,(int)o->value());}
          xywh {531 359 100 10} type {Horz Knob} box FLAT_BOX color 178 selection_color 62 labelsize 10 labelcolor 7 align 4 maximum 127 step 1 textcolor 7
          class SliderW
        }
        Fl_Value_Slider infinity_rate {
          label Tempo
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(401);
 return;
} 
rkr->efx_Infinity->changepar(12,(int)o->value());}
          xywh {531 371 100 10} type {Horz Knob} box FLAT_BOX color 178 selection_color 62 labelsize 10 labelcolor 7 align 4 maximum 600 step 1 textcolor 7
          class SliderW
        }
        Fl_Value_Slider infinity_subdiv {
          label Subdiv
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(402);
 return;
} 
rkr->efx_Infinity->changepar(14,(int)o->value());}
          xywh {531 383 100 10} type {Horz Knob} box FLAT_BOX color 178 selection_color 62 labelsize 10 labelcolor 7 align 4 minimum -16 maximum 16 step 1 textcolor 7
          class SliderW
        }
      }
      
*/