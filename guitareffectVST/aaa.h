/*
SetPAramater에서 값을 읽어서 슬라이더등에 SetVal을 한다.
// 팝업을 띄우는데, 리스트이므로 리스트를 띄운다.
	// PopupTabbedList라고 이름을 붙이고 TabbedList를 팝업으로 띄운다.
	// 화면 밖으로 나가지 않게 위치선정을 스마~트하게.
	Derelict == NewDist



    for (int i = 0; i <= 45; i += 5) {
        efx_EQ1->changepar (i + 10, 7);
        efx_EQ1->changepar (i + 14, 0);
    }

    efx_EQ1->changepar (11, 31);
    efx_EQ1->changepar (16, 63);
    efx_EQ1->changepar (21, 125);
    efx_EQ1->changepar (26, 250);
    efx_EQ1->changepar (31, 500);
    efx_EQ1->changepar (36, 1000);
    efx_EQ1->changepar (41, 2000);
    efx_EQ1->changepar (46, 4000);
    efx_EQ1->changepar (51, 8000);
    efx_EQ1->changepar (56, 16000);

    for (int i = 0; i <= 10; i += 5) {
        efx_EQ2->changepar (i + 10, 7);
        efx_EQ2->changepar (i + 13, 64);
        efx_EQ2->changepar (i + 14, 0);

    }





주파수같은 건 로가리즘으로 매핑하고
나머지는 선형적으로 매핑하면 될 듯.

파라메터값의 mix/max랑
표현값의 min/max가 있고
ConvertToParam함수
ConvertToPrint함수가 어떻게 값을 변환할지를 결정한다.


findpos(0,(int)o->value(),o);}
          xywh {7 214 34 18} shortcut 0x31 color 62 selection_color 1 labelsize 10 align 84 when 1
        }
        Fl_Choice eq_preset {
          label Preset
          user_data 12000
          callback {long long ud= (long long) v;
if((ud==0)||(ud==12000))rkr->EQ1_setpreset((int)o->value());
eq_1->value(rkr->efx_EQ1->getpar(12)-64);
eq_2->value(rkr->efx_EQ1->getpar(17)-64);
eq_3->value(rkr->efx_EQ1->getpar(22)-64);
eq_4->value(rkr->efx_EQ1->getpar(27)-64);
eq_5->value(rkr->efx_EQ1->getpar(32)-64);
eq_6->value(rkr->efx_EQ1->getpar(37)-64);
eq_7->value(rkr->efx_EQ1->getpar(42)-64);
eq_8->value(rkr->efx_EQ1->getpar(47)-64);
eq_9->value(rkr->efx_EQ1->getpar(52)-64);
eq_10->value(rkr->efx_EQ1->getpar(57)-64);
eq_Gain->value(rkr->efx_EQ1->getpar(0)-64);
eq_Q->value(rkr->efx_EQ1->getpar(13)-64);}
          xywh {79 214 76 18} down_box BORDER_BOX selection_color 0 labelsize 10 labelcolor 7 when 6 textsize 10 textcolor 7
        } {
          MenuItem {} {
            label Plain
            xywh {12 12 36 21} labelsize 10
          }
          MenuItem {} {
            label Pop
            xywh {12 12 36 21} labelsize 10
          }
          MenuItem {} {
            label Jazz
            xywh {12 12 36 21} labelsize 10
          }
        }
        Fl_Value_Slider eq_Gain {
          label Gain
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(130);
 return;
} 
rkr->efx_EQ1->changepar(0,(int)(o->value()+64));}
          xywh {51 236 100 10} type {Horz Knob} box FLAT_BOX color 178 selection_color 62 labelsize 10 labelcolor 7 align 4 minimum -64 maximum 63 step 1 textcolor 7
          class SliderW
        }
        Fl_Value_Slider eq_Q {
          label Q
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(131);
 return;
} 
int i;
for(i=0;i<10;i++) rkr->efx_EQ1->changepar(i*5+13,(int)(o->value()+64));} // q value
          xywh {51 249 100 10} type {Horz Knob} box FLAT_BOX color 178 selection_color 62 labelsize 10 labelcolor 7 align 4 minimum -64 maximum 63 step 1 textcolor 7
          class SliderW
        }
        Fl_Value_Slider eq_1 {
          label {31 Hz}
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(132);
 return;
} 
rkr->efx_EQ1->changepar(12,(int)(o->value()+64));} // gain
          xywh {51 268 100 10} type {Horz Knob} box FLAT_BOX color 178 selection_color 62 labelsize 10 labelcolor 7 align 4 minimum -64 maximum 63 step 1 textcolor 7
          class SliderW
        }
        Fl_Value_Slider eq_2 {
          label {63 Hz}
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(133);
 return;
} 
rkr->efx_EQ1->changepar(5+12,(int)(o->value()+64));}
          xywh {51 280 100 10} type {Horz Knob} box FLAT_BOX color 178 selection_color 62 labelsize 10 labelcolor 7 align 4 minimum -64 maximum 63 step 1 textcolor 7
          class SliderW
        }
        Fl_Value_Slider eq_3 {
          label {125 Hz}
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(134);
 return;
} 
rkr->efx_EQ1->changepar(10+12,(int)(o->value()+64));}
          xywh {51 292 100 10} type {Horz Knob} box FLAT_BOX color 178 selection_color 62 labelsize 10 labelcolor 7 align 4 minimum -64 maximum 63 step 1 textcolor 7
          class SliderW
        }
        Fl_Value_Slider eq_4 {
          label {250 Hz}
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(135);
 return;
} 
rkr->efx_EQ1->changepar(15+12,(int)(o->value()+64));}
          xywh {51 305 100 10} type {Horz Knob} box FLAT_BOX color 178 selection_color 62 labelsize 10 labelcolor 7 align 4 minimum -64 maximum 63 step 1 textcolor 7
          class SliderW
        }
        Fl_Value_Slider eq_5 {
          label {500 Hz}
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(136);
 return;
} 
rkr->efx_EQ1->changepar(20+12,(int)(o->value()+64));}
          xywh {51 317 100 10} type {Horz Knob} box FLAT_BOX color 178 selection_color 62 labelsize 10 labelcolor 7 align 4 minimum -64 maximum 63 step 1 textcolor 7
          class SliderW
        }
        Fl_Value_Slider eq_6 {
          label {1 Khz}
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(137);
 return;
} 
rkr->efx_EQ1->changepar(25+12,(int)(o->value()+64));}
          xywh {51 329 100 10} type {Horz Knob} box FLAT_BOX color 178 selection_color 62 labelsize 10 labelcolor 7 align 4 minimum -64 maximum 63 step 1 textcolor 7
          class SliderW
        }
        Fl_Value_Slider eq_7 {
          label {2 Khz}
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(138);
 return;
} 
rkr->efx_EQ1->changepar(30+12,(int)(o->value()+64));}
          xywh {51 342 100 10} type {Horz Knob} box FLAT_BOX color 178 selection_color 62 labelsize 10 labelcolor 7 align 4 minimum -64 maximum 63 step 1 textcolor 7
          class SliderW
        }
        Fl_Value_Slider eq_8 {
          label {4 Khz}
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(139);
 return;
} 
rkr->efx_EQ1->changepar(35+12,(int)(o->value()+64));}
          xywh {51 354 100 10} type {Horz Knob} box FLAT_BOX color 178 selection_color 62 labelsize 10 labelcolor 7 align 4 minimum -64 maximum 63 step 1 textcolor 7
          class SliderW
        }
        Fl_Value_Slider eq_9 {
          label {8 Khz}
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(140);
 return;
} 
rkr->efx_EQ1->changepar(40+12,(int)(o->value()+64));}
          xywh {51 366 100 10} type {Horz Knob} box FLAT_BOX color 178 selection_color 62 labelsize 10 labelcolor 7 align 4 minimum -64 maximum 63 step 1 textcolor 7
          class SliderW
        }
        Fl_Value_Slider eq_10 {
          label {16 Khz}
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(141);
 return;
} 
rkr->efx_EQ1->changepar(45+12,(int)(o->value()+64));}
          xywh {51 379 100 10} type {Horz Knob} box FLAT_BOX color 178 selection_color 62 labelsize 10 labelcolor 7 align 4 minimum -64 maximum 63 step 1 textcolor 7
          class SliderW
        }
      }
      Fl_Group COMPRESS {
        user_data 1
        xywh {161 212 158 184} box UP_BOX color 0 selection_color 0 labelfont 1 align 112
      } {
        Fl_Light_Button compress_activar {
          label On
          user_data 2
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(116);
 o->value(rkr->Compressor_Bypass);
 return;
}

rkr->Compressor_Bypass=(int)o->value();
rkr->efx_Compressor->cleanup();
findpos(1,(int)o->value(),o);}
          xywh {166 216 34 18} shortcut 0x32 color 62 selection_color 1 labelsize 10 align 84 when 1
        }
        Fl_Choice compress_preset {
          label Preset
          user_data 12001
          callback {long long ud= (long long) v;
if((ud==0)||(ud==12001))rkr->efx_Compressor->Compressor_Change_Preset(1,(int) o->value());
compress_threshold->value(rkr->efx_Compressor->getpar(1));
compress_Ratio->value(rkr->efx_Compressor->getpar(2));
compress_output->value(rkr->efx_Compressor->getpar(3));
compress_ATime->value(rkr->efx_Compressor->getpar(4));
compress_RTime->value(rkr->efx_Compressor->getpar(5));
Auto_Output->value(rkr->efx_Compressor->getpar(6));
compress_Knee->value(rkr->efx_Compressor->getpar(7));
Stereo->value(rkr->efx_Compressor->getpar(8));
Peak->value(rkr->efx_Compressor->getpar(9));}
          xywh {238 216 76 18} down_box BORDER_BOX selection_color 0 labelsize 10 labelcolor 7 when 6 textsize 10 textcolor 7
        } {
          MenuItem {} {
            label {2:1}
            xywh {32 32 36 21} labelsize 10
          }
          MenuItem {} {
            label {4:1}
            xywh {32 32 36 21} labelsize 10
          }
          MenuItem {} {
            label {8:1}
            xywh {32 32 36 21} labelsize 10
          }
        }
        Fl_Value_Slider compress_ATime {
          label {A. Time}
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(142);
 return;
} 
rkr->efx_Compressor->Compressor_Change(4,(int)o->value());}
          xywh {212 251 100 10} type {Horz Knob} box FLAT_BOX color 178 selection_color 62 labelsize 10 labelcolor 7 align 4 minimum 10 maximum 250 step 1 value 2 textcolor 7
          class SliderW
        }
        Fl_Value_Slider compress_RTime {
          label {R. Time}
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(143);
 return;
} 
rkr->efx_Compressor->Compressor_Change(5, (int) o->value());}
          xywh {211 271 100 10} type {Horz Knob} box FLAT_BOX color 178 selection_color 62 labelsize 10 labelcolor 7 align 4 minimum 10 maximum 500 step 1 value 120 textcolor 7
          class SliderW
        }
        Fl_Value_Slider compress_Ratio {
          label Ratio
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(144);
 return;
} 
rkr->efx_Compressor->Compressor_Change(2, (int) o->value());}
          xywh {211 291 100 10} type {Horz Knob} box FLAT_BOX color 178 selection_color 62 labelsize 10 labelcolor 7 align 4 minimum 2 maximum 42 step 1 value 2 textcolor 7
          class SliderW
        }
        Fl_Value_Slider compress_Knee {
          label Knee
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(145);
 return;
} 
rkr->efx_Compressor->Compressor_Change(7, (int) o->value());}
          xywh {210 311 100 10} type {Horz Knob} box FLAT_BOX color 178 selection_color 62 labelsize 10 labelcolor 7 align 4 maximum 100 step 1 value 3 textcolor 7
          class SliderW
        }
        Fl_Value_Slider compress_threshold {
          label Thrhold
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(146);
 return;
} 
rkr->efx_Compressor->Compressor_Change(1, (int)o->value());}
          xywh {211 331 100 10} type {Horz Knob} box FLAT_BOX color 178 selection_color 62 labelsize 10 labelcolor 7 align 4 minimum -60 maximum -3 step 1 value -3 textcolor 7
          class SliderW
        }
        Fl_Value_Slider compress_output {
          label Output
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(147);
 return;
} 
rkr->efx_Compressor->Compressor_Change(3,(int)o->value());}
          xywh {211 351 100 10} type {Horz Knob} box FLAT_BOX color 178 selection_color 62 labelsize 10 labelcolor 7 align 4 minimum -40 maximum 0 step 1 textcolor 7
          class SliderW
        }
        Fl_Check_Button Auto_Output {
          label {Auto Output}
          user_data 2
          callback {rkr->efx_Compressor->Compressor_Change(6,(int)o->value());
if ((int) o->value() == 0) compress_output->do_callback();}
          xywh {180 378 15 15} down_box BORDER_BOX labelsize 10 labelcolor 7
        }
        Fl_Check_Button Stereo {
          label Stereo
          user_data 2
          callback {rkr->efx_Compressor->Compressor_Change(8,(int)o->value());
if ((int) o->value() == 0) compress_output->do_callback();}
          tooltip {Level detect Left and Right separately.  Unchecked compresses according to L/R average.} xywh {265 378 15 15} down_box BORDER_BOX labelsize 10 labelcolor 7
        }
        Fl_Check_Button Peak {
          label Peak
          user_data 2
          callback {rkr->efx_Compressor->Compressor_Change(9,(int)o->value());
if ((int) o->value() == 0) compress_output->do_callback();}
          tooltip {Peak Mode Compression} xywh {180 365 15 15} down_box BORDER_BOX labelsize 10 labelcolor 7
        }
      }

      Fl_Group DIST {
        user_data 1
        xywh {320 212 158 184} box UP_BOX color 0 selection_color 0 labelfont 1 align 112
      } {
        Fl_Light_Button dist_activar {
          label On
          user_data 2
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(116);
 o->value(rkr->Distorsion_Bypass);
 return;
}
rkr->Distorsion_Bypass=(int)o->value();
if((int) o->value()==0)
rkr->efx_Distorsion->cleanup();
findpos(2,(int)o->value(),o);}
          xywh {325 216 34 18} shortcut 0x33 color 62 selection_color 1 labelsize 10 align 84 when 1
        }
        Fl_Choice dist_preset {
          label Preset
          user_data 12002
          callback {long long ud= (long long) v;
if((ud==0)||(ud==12002)) rkr->efx_Distorsion->setpreset(0,(int)(o->value()+2));
dist_WD->value(rkr->efx_Distorsion->getpar(0)-64);
dist_pan->value(rkr->efx_Distorsion->getpar(1)-64);
dist_LRc->value(rkr->efx_Distorsion->getpar(2)-64);
dist_drive->value(rkr->efx_Distorsion->getpar(3));
dist_level->value(rkr->efx_Distorsion->getpar(4));
dist_tipo->value(rkr->efx_Distorsion->getpar(5));
dist_neg->value(rkr->efx_Distorsion->getpar(6));
dist_lpf->value(rkr->efx_Distorsion->getpar(7));
dist_hpf->value(rkr->efx_Distorsion->getpar(8));
dist_st->value(rkr->efx_Distorsion->getpar(9));
dist_pf->value(rkr->efx_Distorsion->getpar(10));
dist_oct->value(rkr->efx_Distorsion->getpar(12));}
          xywh {397 216 76 18} down_box BORDER_BOX selection_color 0 labelsize 10 labelcolor 7 when 6 textsize 10 textcolor 7
        } {
          MenuItem {} {
            label {Distorsion 1}
            xywh {32 32 36 21} labelsize 10
          }
          MenuItem {} {
            label {Distorsion 2}
            xywh {32 32 36 21} labelsize 10
          }
          MenuItem {} {
            label {Distorsion 3}
            xywh {42 42 36 21} labelsize 10
          }
          MenuItem {} {
            label {Guitar Amp}
            xywh {32 32 36 21} labelsize 10
          }
        }
        Fl_Value_Slider dist_WD {
          label {Wet/Dry}
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(30);
 return;
} 
rkr->efx_Distorsion->changepar(0,(int)(o->value()+64));}
          xywh {372 247 100 10} type {Horz Knob} box FLAT_BOX color 178 selection_color 62 labelsize 10 labelcolor 7 align 4 minimum -64 maximum 63 step 1 textcolor 7
          class SliderW
        }
        Fl_Value_Slider dist_LRc {
          label {L/R.Cr}
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(95);
 return;
} 
rkr->efx_Distorsion->changepar(2,(int)(o->value()+64));}
          xywh {372 260 100 10} type {Horz Knob} box FLAT_BOX color 178 selection_color 62 labelsize 10 labelcolor 7 align 4 minimum -64 maximum 63 step 1 textcolor 7
          class SliderW
        }
        Fl_Value_Slider dist_drive {
          label Drive
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(69);
 return;
} 
rkr->efx_Distorsion->changepar(3,(int)o->value());}
          xywh {372 273 100 10} type {Horz Knob} box FLAT_BOX color 178 selection_color 62 labelsize 10 labelcolor 7 align 4 maximum 127 step 1 textcolor 7
          class SliderW
        }
        Fl_Value_Slider dist_level {
          label Level
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(71);
 return;
} 
rkr->efx_Distorsion->changepar(4,(int)o->value());}
          xywh {372 287 100 10} type {Horz Knob} box FLAT_BOX color 178 selection_color 62 labelsize 10 labelcolor 7 align 4 maximum 127 step 1 textcolor 7
          class SliderW
        }
        Fl_Choice dist_tipo {
          label Type
          user_data 12
          callback {rkr->efx_Distorsion->changepar(5,(int)o->value());}
          xywh {354 303 70 16} down_box BORDER_BOX selection_color 0 labelsize 10 labelcolor 7 textsize 10 textcolor 7
        } {
          MenuItem {} {
            label Atan
            xywh {32 32 36 21} labelsize 9
          }
          MenuItem {} {
            label Asym1
            xywh {32 32 36 21} labelsize 9
          }
          MenuItem {} {
            label Pow
            xywh {32 32 36 21} labelsize 9
          }
          MenuItem {} {
            label Sine
            xywh {42 42 36 21} labelsize 9
          }
          MenuItem {} {
            label Qnts
            xywh {52 52 36 21} labelsize 9
          }
          MenuItem {} {
            label Zigzg
            xywh {62 62 36 21} labelsize 9
          }
          MenuItem {} {
            label Lmt
            xywh {72 72 36 21} labelsize 9
          }
          MenuItem {} {
            label LmtU
            xywh {82 82 36 21} labelsize 9
          }
          MenuItem {} {
            label LmtL
            xywh {92 92 36 21} labelsize 9
          }
          MenuItem {} {
            label ILmt
            xywh {102 102 36 21} labelsize 9
          }
          MenuItem {} {
            label Clip
            xywh {112 112 36 21} labelsize 9
          }
          MenuItem {} {
            label Asym2
            xywh {122 122 36 21} labelsize 9
          }
          MenuItem {} {
            label Pow2
            xywh {132 132 36 21} labelsize 9
          }
          MenuItem {} {
            label Sgm
            xywh {142 142 36 21} labelsize 9
          }
          MenuItem {} {
            label Crunch
            xywh {0 0 36 21} labelsize 9
          }
          MenuItem {} {
            label {Hard Crunch}
            xywh {10 10 36 21} labelsize 9
          }
          MenuItem {} {
            label {Dirty Octave+}
            xywh {20 20 36 21} labelsize 9
          }
          MenuItem {} {
            label {M.Square}
            xywh {0 0 36 21} labelsize 9
          }
          MenuItem {} {
            label {M.Saw}
            xywh {0 0 36 21} labelsize 9
          }
          MenuItem {} {
            label Compress
            xywh {10 10 36 21} labelsize 9
          }
          MenuItem {} {
            label Overdrive
            xywh {0 0 36 21} labelsize 9
          }
          MenuItem {} {
            label Soft
            xywh {0 0 36 21} labelsize 9
          }
          MenuItem {} {
            label {Super Soft}
            xywh {0 0 36 21} labelsize 9
          }
          MenuItem {} {
            label {Hard Compress}
            xywh {0 0 36 21} labelsize 9
          }
          MenuItem {} {
            label {Lmt-NoGain}
            xywh {10 10 36 21} labelsize 9
          }
          MenuItem {} {
            label FET
            xywh {20 20 36 21} labelsize 9
          }
          MenuItem {} {
            label DynoFET
            xywh {30 30 36 21} labelsize 9
          }
          MenuItem {} {
            label {Valve 1}
            xywh {0 0 36 21} labelsize 9
          }
          MenuItem {} {
            label {Valve 2}
            xywh {0 0 36 21} labelsize 9
          }
          MenuItem {} {
            label {Diode clipper}
            xywh {0 0 36 21} labelsize 9
          }
        }
        Fl_Check_Button dist_neg {
          label {Neg.}
          user_data 2
          callback {rkr->efx_Distorsion->changepar(6,(int)o->value());}
          xywh {430 304 41 15} down_box BORDER_BOX labelsize 10 labelcolor 7
        }
        Fl_Check_Button dist_pf {
          label {Pre Filter}
          user_data 2
          callback {rkr->efx_Distorsion->changepar(10,(int)o->value());}
          xywh {329 320 67 15} down_box BORDER_BOX labelsize 10 labelcolor 7
        }
        Fl_Check_Button dist_st {
          label Stereo
          user_data 2
          callback {rkr->efx_Distorsion->changepar(9,(int)o->value());}
          xywh {394 320 57 15} down_box BORDER_BOX labelsize 10 labelcolor 7
        }
        Fl_Value_Slider dist_pan {
          label Pan
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(48);
 return;
} 
rkr->efx_Distorsion->changepar(1,(int)(o->value()+64));}
          xywh {372 337 100 10} type {Horz Knob} box FLAT_BOX color 178 selection_color 62 labelsize 10 labelcolor 7 align 4 minimum -64 maximum 63 step 1 textcolor 7
          class SliderW
        }
        Fl_Value_Slider dist_oct {
          label {Sub Octv}
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(9);
 return;
} 
rkr->efx_Distorsion->changepar(12,(int)o->value());}
          xywh {372 357 100 10} type {Horz Knob} box FLAT_BOX color 178 selection_color 62 labelsize 10 labelcolor 7 align 4 maximum 127 step 1 textcolor 7
          class SliderW
        }
        Fl_Value_Slider dist_lpf {
          label LPF
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(86);
 return;
} 
rkr->efx_Distorsion->changepar(7,(int)o->value());}
          xywh {372 369 100 10} type {Horz Knob} box FLAT_BOX color 178 selection_color 62 labelsize 10 labelcolor 7 align 4 minimum 20 maximum 26000 step 1 value 20000 textcolor 7
          class SliderW
        }
        Fl_Value_Slider dist_hpf {
          label HPF
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(89);
 return;
} 
rkr->efx_Distorsion->changepar(8,(int)o->value());}
          xywh {372 381 100 10} type {Horz Knob} box FLAT_BOX color 178 selection_color 62 labelsize 10 labelcolor 7 align 4 minimum 20 maximum 20000 step 1 value 20 textcolor 7
          class SliderW
        }
      }
      Fl_Group ECHO {
        user_data 1
        xywh {639 212 158 184} box UP_BOX color 0 selection_color 0 labelfont 1 align 112
      } {
        Fl_Light_Button echo_activar {
          label On
          user_data 2
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(116);
 o->value(rkr->Echo_Bypass);
 return;
}
rkr->Echo_Bypass=(int)o->value();
if((int) o->value()==0)
rkr->efx_Echo->cleanup();
findpos(4,(int)o->value(),o);}
          xywh {644 216 34 18} shortcut 0x35 color 62 selection_color 1 labelsize 10 align 84 when 1
        }
        Fl_Choice echo_preset {
          label Preset
          user_data 12004
          callback {long long ud= (long long) v;
if((ud==0)||(ud==12004))rkr->efx_Echo->setpreset((int) o->value());
echo_WD->value(rkr->efx_Echo->getpar(0)-64);
echo_pan->value(rkr->efx_Echo->getpar(1)-64);
echo_delay->value(rkr->efx_Echo->getpar(2));
echo_LRdl->value(rkr->efx_Echo->getpar(3));
echo_LRc->value(rkr->efx_Echo->getpar(4)-64);
echo_fb->value(rkr->efx_Echo->getpar(5));
echo_damp->value(rkr->efx_Echo->getpar(6));
echo_RV->value(rkr->efx_Echo->getpar(7));
echo_direct->value(rkr->efx_Echo->getpar(8));}
          xywh {716 216 76 18} down_box BORDER_BOX selection_color 0 labelsize 10 labelcolor 7 when 6 textsize 10 textcolor 7
        } {
          MenuItem {} {
            label {Echo 1}
            xywh {57 57 36 21} labelsize 10
          }
          MenuItem {} {
            label {Echo 2}
            xywh {57 57 36 21} labelsize 10
          }
          MenuItem {} {
            label {Echo 3}
            xywh {57 57 36 21} labelsize 10
          }
          MenuItem {} {
            label {Simple Echo}
            xywh {67 67 36 21} labelsize 10
          }
          MenuItem {} {
            label Canyon
            xywh {77 77 36 21} labelsize 10
          }
          MenuItem {} {
            label {Panning Echo 1}
            xywh {97 97 36 21} labelsize 10
          }
          MenuItem {} {
            label {Panning Echo 2}
            xywh {107 107 36 21} labelsize 10
          }
          MenuItem {} {
            label {Panning Echo 3}
            xywh {117 117 36 21} labelsize 10
          }
          MenuItem {} {
            label {Feedback Echo}
            xywh {127 127 36 21} labelsize 10
          }
        }
        Fl_Value_Slider echo_WD {
          label {Wet/Dry}
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(59);
 return;
} 
rkr->efx_Echo->changepar(0,(int)(o->value()+64));}
          xywh {690 247 100 10} type {Horz Knob} box FLAT_BOX color 178 selection_color 62 labelsize 10 labelcolor 7 align 4 minimum -64 maximum 63 step 1 textcolor 7
          class SliderW
        }
        Fl_Value_Slider echo_RV {
          label Reverse
          callback {rkr->efx_Echo->changepar(7,(int)o->value());}
          xywh {690 270 100 10} type {Horz Knob} box FLAT_BOX color 178 selection_color 62 labelsize 10 labelcolor 7 align 4 maximum 127 step 1 textcolor 7
          class SliderW
        }
        Fl_Value_Slider echo_pan {
          label Pan
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(46);
 return;
} 
rkr->efx_Echo->changepar(1,(int)(o->value()+64));}
          xywh {690 285 100 10} type {Horz Knob} box FLAT_BOX color 178 selection_color 62 labelsize 10 labelcolor 7 align 4 minimum -64 maximum 63 step 1 textcolor 7
          class SliderW
        }
        Fl_Value_Slider echo_delay {
          label Delay
          callback {rkr->efx_Echo->changepar(2,(int)o->value());}
          xywh {690 300 100 10} type {Horz Knob} box FLAT_BOX color 178 selection_color 62 labelsize 10 labelcolor 7 align 4 when 4 minimum 20 maximum 2000 step 1 value 20 textcolor 7
          class SliderW
        }
        Fl_Value_Slider echo_LRdl {
          label {LRdl.}
          callback {rkr->efx_Echo->changepar(3,(int)o->value());}
          xywh {690 315 100 10} type {Horz Knob} box FLAT_BOX color 178 selection_color 62 labelsize 10 labelcolor 7 align 4 when 4 maximum 127 step 1 textcolor 7
          class SliderW
        }
        Fl_Value_Slider echo_LRc {
          label {L/R.Cr}
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(97);
 return;
} 
rkr->efx_Echo->changepar(4,(int)(o->value()+64));}
          xywh {690 330 100 10} type {Horz Knob} box FLAT_BOX color 178 selection_color 62 labelsize 10 labelcolor 7 align 4 minimum -64 maximum 63 step 1 textcolor 7
          class SliderW
        }
        Fl_Value_Slider echo_fb {
          label {Fb.}
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(78);
 return;
} 
rkr->efx_Echo->changepar(5,(int)o->value());}
          xywh {690 345 100 10} type {Horz Knob} box FLAT_BOX color 178 selection_color 62 labelsize 10 labelcolor 7 align 4 maximum 127 step 1 textcolor 7
          class SliderW
        }
        Fl_Check_Button echo_direct {
          label Direct
          user_data 2
          callback {rkr->efx_Echo->changepar(8,(int)o->value());}
          xywh {690 360 53 15} down_box BORDER_BOX labelsize 10 labelcolor 7
        }
        Fl_Value_Slider echo_damp {
          label Damp
          callback {rkr->efx_Echo->changepar(6,(int)o->value());}
          xywh {690 379 100 10} type {Horz Knob} box FLAT_BOX color 178 selection_color 62 labelsize 10 labelcolor 7 align 4 maximum 127 step 1 textcolor 7
          class SliderW
        }
      }
      Fl_Group CHORUS {
        user_data 1
        xywh {2 413 158 184} box UP_BOX color 0 selection_color 0 labelfont 1 align 112
      } {
        Fl_Light_Button chorus_activar {
          label On
          user_data 2
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(116);
 o->value(rkr->Chorus_Bypass);
 return;
}
rkr->Chorus_Bypass=(int)o->value();
if((int) o->value()==0)
rkr->efx_Chorus->cleanup();
findpos(5,(int)o->value(),o);}
          xywh {7 417 34 18} shortcut 0x36 color 62 selection_color 1 labelsize 10 align 84 when 1
        }
        Fl_Choice chorus_preset {
          label Preset
          user_data 12005
          callback {long long ud= (long long) v;
if((ud==0)||(ud==12005))rkr->efx_Chorus->setpreset(0,(int) o->value());
chorus_WD->value(rkr->efx_Chorus->getpar(0)-64);
chorus_pan->value(rkr->efx_Chorus->getpar(1)-64);
chorus_freq->value(rkr->efx_Chorus->getpar(2));
chorus_rnd->value(rkr->efx_Chorus->getpar(3));
chorus_lfotype->value(rkr->efx_Chorus->getpar(4));
chorus_stdf->value(rkr->efx_Chorus->getpar(5));
chorus_dpth->value(rkr->efx_Chorus->getpar(6));
chorus_delay->value(rkr->efx_Chorus->getpar(7));
chorus_fb->value(rkr->efx_Chorus->getpar(8));
chorus_LR->value(rkr->efx_Chorus->getpar(9)-64);
chorus_subs->value(rkr->efx_Chorus->getpar(11));
chorus_awesome->value(rkr->efx_Chorus->getpar(12));}
          xywh {79 417 76 18} down_box BORDER_BOX selection_color 0 labelsize 10 labelcolor 7 when 6 textsize 10 textcolor 7
        } {
          MenuItem {} {
            label {Chorus 1}
            xywh {52 52 36 21} labelsize 10
          }
          MenuItem {} {
            label {Chorus 2}
            xywh {52 52 36 21} labelsize 10
          }
          MenuItem {} {
            label {Chorus 3}
            xywh {52 52 36 21} labelsize 10
          }
          MenuItem {} {
            label {Celeste 1}
            xywh {62 62 36 21} labelsize 10
          }
          MenuItem {} {
            label {Celeste 2}
            xywh {72 72 36 21} labelsize 10
          }
        }
        Fl_Value_Slider chorus_WD {
          label {Wet/Dry}
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(52);
 return;
} 
rkr->efx_Chorus->changepar(0,(int)(o->value()+64));}
          xywh {51 442 100 10} type {Horz Knob} box FLAT_BOX color 178 selection_color 62 labelsize 10 labelcolor 7 align 4 minimum -64 maximum 63 step 1 textcolor 7
          class SliderW
        }
        Fl_Value_Slider chorus_pan {
          label Pan
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(50);
 return;
} 
rkr->efx_Chorus->changepar(1,(int)(o->value()+64));}
          xywh {51 454 100 10} type {Horz Knob} box FLAT_BOX color 178 selection_color 62 labelsize 10 labelcolor 7 align 4 minimum -64 maximum 63 step 1 textcolor 7
          class SliderW
        }
        Fl_Value_Slider chorus_freq {
          label Tempo
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(72);
 return;
} 
rkr->efx_Chorus->changepar(2,(int)o->value());}
          xywh {51 466 100 10} type {Horz Knob} box FLAT_BOX color 178 selection_color 62 labelsize 10 labelcolor 7 align 4 minimum 1 maximum 600 step 1 textcolor 7
          class SliderW
        }
        Fl_Value_Slider chorus_rnd {
          label Rnd
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(105);
 return;
} 
rkr->efx_Chorus->changepar(3,(int)o->value());}
          xywh {51 478 100 10} type {Horz Knob} box FLAT_BOX color 178 selection_color 62 labelsize 10 labelcolor 7 align 4 maximum 127 step 1 textcolor 7
          class SliderW
        }
        Fl_Choice chorus_lfotype {
          label {LFO Type}
          user_data 12
          callback {rkr->efx_Chorus->changepar(4,(int)o->value())}
          xywh {63 490 72 16} down_box BORDER_BOX selection_color 0 labelsize 10 labelcolor 7 textsize 10 textcolor 7
        } {
          MenuItem {} {
            label Sine
            xywh {52 52 36 21} labelsize 10
          }
          MenuItem {} {
            label Tri
            xywh {52 52 36 21} labelsize 10
          }
          MenuItem {} {
            label {Ramp Up}
            xywh {0 0 36 21} labelsize 9
          }
          MenuItem {} {
            label {Ramp Down}
            xywh {0 0 36 21} labelsize 9
          }
          MenuItem {} {
            label ZigZag
            xywh {10 10 36 21} labelsize 9
          }
          MenuItem {} {
            label {M. Sqare}
            xywh {0 0 36 21} labelsize 9
          }
          MenuItem {} {
            label {M.Saw}
            xywh {0 0 36 21} labelsize 9
          }
          MenuItem {} {
            label {L. Fractal}
            xywh {10 10 36 21} labelsize 9
          }
          MenuItem {} {
            label {L. Fractal XY}
            xywh {20 20 36 21} labelsize 9
          }
          MenuItem {} {
            label {S/H Random}
            xywh {30 30 36 21} labelsize 9
          }
        }
        Fl_Check_Button chorus_subs {
          label Subtract
          user_data 2
          callback {rkr->efx_Chorus->changepar(11,(int)o->value())}
          xywh {27 507 62 15} down_box BORDER_BOX labelsize 10 labelcolor 7
        }
        Fl_Check_Button chorus_awesome {
          label Intense
          user_data 2
          callback {rkr->efx_Chorus->changepar(12,(int)o->value())}
          xywh {90 508 56 15} down_box BORDER_BOX labelsize 10 labelcolor 7
        }
        Fl_Value_Slider chorus_stdf {
          label {St.df}
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(99);
 return;
} 
rkr->efx_Chorus->changepar(5,(int)o->value());}
          xywh {51 528 100 10} type {Horz Knob} box FLAT_BOX color 178 selection_color 62 labelsize 10 labelcolor 7 align 4 maximum 127 step 1 textcolor 7
          class SliderW
        }
        Fl_Value_Slider chorus_dpth {
          label Depth
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(23);
 return;
} 
rkr->efx_Chorus->changepar(6,(int)o->value());}
          xywh {51 541 100 10} type {Horz Knob} box FLAT_BOX color 178 selection_color 62 labelsize 10 labelcolor 7 align 4 maximum 127 step 1 textcolor 7
          class SliderW
        }
        Fl_Value_Slider chorus_delay {
          label Delay
          callback {rkr->efx_Chorus->changepar(7,(int)o->value());}
          xywh {51 554 100 10} type {Horz Knob} box FLAT_BOX color 178 selection_color 62 labelsize 10 labelcolor 7 align 4 maximum 127 step 1 textcolor 7
          class SliderW
        }
        Fl_Value_Slider chorus_fb {
          label Fb
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(79);
 return;
} 
rkr->efx_Chorus->changepar(8,(int)o->value());}
          xywh {51 567 100 10} type {Horz Knob} box FLAT_BOX color 178 selection_color 62 labelsize 10 labelcolor 7 align 4 maximum 127 step 1 textcolor 7
          class SliderW
        }
        Fl_Value_Slider chorus_LR {
          label {L/R.Cr}
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(91);
 return;
} 
rkr->efx_Chorus->changepar(9,(int)(o->value()+64));}
          xywh {51 581 100 10} type {Horz Knob} box FLAT_BOX color 178 selection_color 62 labelsize 10 labelcolor 7 align 4 minimum -64 maximum 63 step 1 textcolor 7
          class SliderW
        }
      }

	  */
