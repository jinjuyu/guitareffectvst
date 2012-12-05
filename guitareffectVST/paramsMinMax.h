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