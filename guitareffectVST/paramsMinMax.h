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


	}
};

/*
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


		/*
		const int PRESET_SIZE = 10;
		const int NUM_PRESETS = 5;
		int presets[NUM_PRESETS*PRESET_SIZE] = {
			//Fast
			0, 64, 64, 200, 200, -20, 2, 0, 0, 0,
			//Slowup
			0, 64, 64, 900, 200, -20, 2, 0, 0, 0,
			//Slowdown
			0, 64, 64, 900, 200, -20, 3, 1, 0, 0,
			//Chorus
			64, 64, 64, 0, 0, -20, 1, 0, 1, 22,
			//Trig Chorus
			64, 64, 64, 250, 100, -10, 0, 0, 0, 25
		};

		int ShifterReal[] = {
			//case 0:
			0,127,
				//setvolume (value);
				//break;
			//case 1:
			0,127,
				//setpanning (value);
				//break;
			//case 2:
			0,127,
				//setgain (value);
				//break;
			//case 3:
			1,2000,
				//Pattack = value;
				//a_rate = 1000.0f / ((float)Pattack * nfSAMPLE_RATE);
				//break;
			//case 4:
			1,2000,
				//Pdecay = value;
				//d_rate = 1000.0f / ((float)Pdecay * nfSAMPLE_RATE);
				//break;
			//case 5:
			-70,20,
				//Pthreshold = value;
				//t_level = dB2rap ((float)Pthreshold);
				//td_level = t_level*.75f;
				//tz_level = t_level*.5f;
				//break;
			//case 6:
			0,12,
				//Pinterval = value;
				//setinterval(Pinterval);
				//break;
			//case 7:
			0,1,
				//Pupdown = value;
				//setinterval(Pinterval);
				//break;
			//case 8:
			0,2,
            /*Trigger
            Whammy
            Portamento* /
				//Pmode = value;
				//break;
			//case 9:
			0,127,
				//Pwhammy = value;
				//whammy = (float) value / 127.0f;
				//break;


		};
		int ShifterPrint[] = {
			-64,63,
			-64,63,
			-64,63,
			1,2000,
			1,2000,
			-70,20,
			0,12,
			0,1,
			0,2,
			0,127,
		};
		*/

