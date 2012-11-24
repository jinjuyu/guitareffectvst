/*
compressor, gate, expander는 changepar나 getpar가 n+1 즉 1부터 시작한다.


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

      Fl_Group PHASER {
        user_data 1
        xywh {161 413 158 184} box UP_BOX color 0 selection_color 0 labelfont 1 align 112
      } {
        Fl_Light_Button phaser_activar {
          label On
          user_data 2
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(116);
 o->value(rkr->Phaser_Bypass);
 return;
}
rkr->Phaser_Bypass=(int)o->value();
if((int) o->value()==0)
rkr->efx_Phaser->cleanup();
findpos(6,(int)o->value(),o);}
          xywh {166 417 34 18} shortcut 0x37 color 62 selection_color 1 labelsize 10 align 84 when 1
        }
        Fl_Choice phaser_preset {
          label Preset
          user_data 12006
          callback {long long ud= (long long) v;
if((ud==0)||(ud==12006))rkr->efx_Phaser->setpreset((int) o->value());
phaser_WD->value(rkr->efx_Phaser->getpar(0)-64);
phaser_pan->value(rkr->efx_Phaser->getpar(1)-64);
phaser_freq->value(rkr->efx_Phaser->getpar(2));
phaser_rnd->value(rkr->efx_Phaser->getpar(3));
phaser_lfotype->value(rkr->efx_Phaser->getpar(4));
phaser_stdf->value(rkr->efx_Phaser->getpar(5));
phaser_dpth->value(rkr->efx_Phaser->getpar(6));
phaser_stages->value(rkr->efx_Phaser->getpar(8));
phaser_fb->value(rkr->efx_Phaser->getpar(7));
phaser_stages->value(rkr->efx_Phaser->getpar(8));
phaser_LR->value(rkr->efx_Phaser->getpar(9)-64);
phaser_subs->value(rkr->efx_Phaser->getpar(10));
phaser_phase->value(rkr->efx_Phaser->getpar(11));}
          xywh {238 417 76 18} down_box BORDER_BOX selection_color 0 labelsize 10 labelcolor 7 when 6 textsize 10 textcolor 7
        } {
          MenuItem {} {
            label {Phaser 1}
            xywh {62 62 36 21} labelsize 10
          }
          MenuItem {} {
            label {Phaser 2}
            xywh {62 62 36 21} labelsize 10
          }
          MenuItem {} {
            label {Phaser 3}
            xywh {62 62 36 21} labelsize 10
          }
          MenuItem {} {
            label {Phaser 4}
            xywh {72 72 36 21} labelsize 10
          }
          MenuItem {} {
            label {Phaser 5}
            xywh {82 82 36 21} labelsize 10
          }
          MenuItem {} {
            label {Phaser 6}
            xywh {92 92 36 21} labelsize 10
          }
        }
        Fl_Value_Slider phaser_WD {
          label {Wet/Dry}
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(54);
 return;
} 
rkr->efx_Phaser->changepar(0,(int)(o->value()+64));}
          xywh {210 442 100 10} type {Horz Knob} box FLAT_BOX color 178 selection_color 62 labelsize 10 labelcolor 7 align 4 minimum -64 maximum 63 step 1 textcolor 7
          class SliderW
        }
        Fl_Value_Slider phaser_pan {
          label Pan
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(60);
 return;
} 
rkr->efx_Phaser->changepar(1,(int)(o->value()+64));}
          xywh {210 454 100 10} type {Horz Knob} box FLAT_BOX color 178 selection_color 62 labelsize 10 labelcolor 7 align 4 minimum -64 maximum 63 step 1 value 64 textcolor 7
          class SliderW
        }
        Fl_Value_Slider phaser_freq {
          label Tempo
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(74);
 return;
} 
rkr->efx_Phaser->changepar(2,(int)o->value());}
          xywh {210 466 100 10} type {Horz Knob} box FLAT_BOX color 178 selection_color 62 labelsize 10 labelcolor 7 align 4 minimum 1 maximum 600 step 1 textcolor 7
          class SliderW
        }
        Fl_Value_Slider phaser_rnd {
          label Rnd
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(107);
 return;
} 
rkr->efx_Phaser->changepar(3,(int)o->value());}
          xywh {210 478 100 10} type {Horz Knob} box FLAT_BOX color 178 selection_color 62 labelsize 10 labelcolor 7 align 4 maximum 127 step 1 textcolor 7
          class SliderW
        }
        Fl_Choice phaser_lfotype {
          label {LFO Type}
          callback {rkr->efx_Phaser->changepar(4,(int)o->value());} open
          xywh {221 490 72 16} down_box BORDER_BOX selection_color 0 labelsize 10 labelcolor 7 textsize 10 textcolor 7
          code0 {o->menu(menu_chorus_lfotype);}
        } {}
        Fl_Check_Button phaser_subs {
          label Subtract
          user_data 2
          callback {rkr->efx_Phaser->changepar(10,(int)o->value())}
          xywh {201 507 65 15} down_box BORDER_BOX labelsize 10 labelcolor 7
        }
        Fl_Value_Slider phaser_phase {
          label Phase
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(114);
 return;
} 
rkr->efx_Phaser->changepar(11,(int)o->value());}
          xywh {210 523 100 10} type {Horz Knob} box FLAT_BOX color 178 selection_color 62 labelsize 10 labelcolor 7 align 4 maximum 127 step 1 textcolor 7
          class SliderW
        }
        Fl_Value_Slider phaser_stdf {
          label {St.df}
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(101);
 return;
} 
rkr->efx_Phaser->changepar(5,(int)o->value());}
          xywh {210 534 100 10} type {Horz Knob} box FLAT_BOX color 178 selection_color 62 labelsize 10 labelcolor 7 align 4 maximum 127 step 1 textcolor 7
          class SliderW
        }
        Fl_Value_Slider phaser_dpth {
          label Depth
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(21);
 return;
} 
rkr->efx_Phaser->changepar(6,(int)o->value());}
          xywh {210 545 100 10} type {Horz Knob} box FLAT_BOX color 178 selection_color 62 labelsize 10 labelcolor 7 align 4 maximum 127 step 1 textcolor 7
          class SliderW
        }
        Fl_Value_Slider phaser_fb {
          label Fb
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(81);
 return;
} 
rkr->efx_Phaser->changepar(7,(int)o->value());}
          xywh {210 557 100 10} type {Horz Knob} box FLAT_BOX color 178 selection_color 62 labelsize 10 labelcolor 7 align 4 maximum 127 step 1 textcolor 7
          class SliderW
        }
        Fl_Counter phaser_stages {
          label Stages
          callback {rkr->efx_Phaser->changepar(8,(int)o->value());}
          xywh {233 569 52 12} type Simple box THIN_UP_BOX labelsize 10 labelcolor 7 align 4 minimum 1 maximum 12 step 1 value 1 textsize 9
        }
        Fl_Value_Slider phaser_LR {
          label {L/R.Cr}
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(93);
 return;
} 
rkr->efx_Phaser->changepar(9,(int)(o->value()+64));}
          xywh {210 584 100 10} type {Horz Knob} box FLAT_BOX color 178 selection_color 62 labelsize 10 labelcolor 7 align 4 minimum -64 maximum 63 step 1 textcolor 7
          class SliderW
        }
      }

      Fl_Group FLANGER {
        user_data 1
        xywh {321 413 158 184} box UP_BOX color 0 selection_color 0 labelfont 1 align 112
      } {
        Fl_Light_Button flanger_activar {
          label On
          user_data 2
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(116);
 o->value(rkr->Flanger_Bypass);
 return;
}
rkr->Flanger_Bypass=(int)o->value();
if((int) o->value()==0)
rkr->efx_Flanger->cleanup();
findpos(7,(int)o->value(),o);}
          xywh {326 417 34 18} shortcut 0x38 color 62 selection_color 1 labelsize 10 align 84 when 1
        }
        Fl_Choice flanger_preset {
          label Preset
          user_data 12007
          callback {long long ud= (long long) v;
if((ud==0)||(ud==12007))rkr->efx_Flanger->setpreset(1,(int)(o->value()+5));
flanger_WD->value(rkr->efx_Flanger->getpar(0)-64);
flanger_pan->value(rkr->efx_Flanger->getpar(1)-64);
flanger_freq->value(rkr->efx_Flanger->getpar(2));
flanger_rnd->value(rkr->efx_Flanger->getpar(3));
flanger_lfotype->value(rkr->efx_Flanger->getpar(4));
flanger_stdf->value(rkr->efx_Flanger->getpar(5));
flanger_dpth->value(rkr->efx_Flanger->getpar(6));
flanger_delay->value(rkr->efx_Flanger->getpar(7));
flanger_fb->value(rkr->efx_Flanger->getpar(8));
flanger_LR->value(rkr->efx_Flanger->getpar(9)-64);
flanger_subs->value(rkr->efx_Flanger->getpar(11));
flanger_awesome->value(rkr->efx_Flanger->getpar(12));}
          xywh {398 417 76 18} down_box BORDER_BOX selection_color 0 labelsize 10 labelcolor 7 when 6 textsize 10 textcolor 7
        } {
          MenuItem {} {
            label {Flange 1}
            xywh {62 62 36 21} labelsize 10
          }
          MenuItem {} {
            label {Flange 2}
            xywh {62 62 36 21} labelsize 10
          }
          MenuItem {} {
            label {Flange 3}
            xywh {62 62 36 21} labelsize 10
          }
          MenuItem {} {
            label {Flange 4}
            xywh {72 72 36 21} labelsize 10
          }
          MenuItem {} {
            label {Flange 5}
            xywh {82 82 36 21} labelsize 10
          }
        }
        Fl_Value_Slider flanger_WD {
          label {Wet/Dry}
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(53);
 return;
} 
rkr->efx_Flanger->changepar(0,(int)(o->value()+64));}
          xywh {373 442 100 10} type {Horz Knob} box FLAT_BOX color 178 selection_color 62 labelsize 10 labelcolor 7 align 4 minimum -64 maximum 63 step 1 textcolor 7
          class SliderW
        }
        Fl_Value_Slider flanger_pan {
          label Pan
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(51);
 return;
} 
rkr->efx_Flanger->changepar(1,(int)(o->value()+64));}
          xywh {373 454 100 10} type {Horz Knob} box FLAT_BOX color 178 selection_color 62 labelsize 10 labelcolor 7 align 4 minimum -64 maximum 63 step 1 textcolor 7
          class SliderW
        }
        Fl_Value_Slider flanger_freq {
          label Tempo
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(73);
 return;
} 
rkr->efx_Flanger->changepar(2,(int)o->value());}
          xywh {373 466 100 10} type {Horz Knob} box FLAT_BOX color 178 selection_color 62 labelsize 10 labelcolor 7 align 4 minimum 1 maximum 600 step 1 textcolor 7
          class SliderW
        }
        Fl_Value_Slider flanger_rnd {
          label Rnd
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(106);
 return;
} 
rkr->efx_Flanger->changepar(3,(int)o->value());}
          xywh {373 478 100 10} type {Horz Knob} box FLAT_BOX color 178 selection_color 62 labelsize 10 labelcolor 7 align 4 maximum 127 step 1 textcolor 7
          class SliderW
        }
        Fl_Choice flanger_lfotype {
          label {LFO Type}
          callback {rkr->efx_Flanger->changepar(4,(int)o->value());}
          xywh {384 490 72 16} down_box BORDER_BOX selection_color 0 labelsize 10 labelcolor 7 textsize 10 textcolor 7
          code0 {o->menu(menu_chorus_lfotype);}
        } {}
        Fl_Check_Button flanger_subs {
          label Subtract
          user_data 2
          callback {rkr->efx_Flanger->changepar(11,(int)o->value());}
          xywh {353 507 62 15} down_box BORDER_BOX labelsize 10 labelcolor 7
        }
        Fl_Check_Button flanger_awesome {
          label Intense
          user_data 2
          callback {rkr->efx_Flanger->changepar(12,(int)o->value());}
          xywh {415 507 58 15} down_box BORDER_BOX labelsize 10 labelcolor 7
        }
        Fl_Value_Slider flanger_stdf {
          label {St.df}
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(100);
 return;
} 
rkr->efx_Flanger->changepar(5,(int)o->value());}
          xywh {373 528 100 10} type {Horz Knob} box FLAT_BOX color 178 selection_color 62 labelsize 10 labelcolor 7 align 4 maximum 127 step 1 textcolor 7
          class SliderW
        }
        Fl_Value_Slider flanger_dpth {
          label Depth
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(22);
 return;
} 
rkr->efx_Flanger->changepar(6,(int)o->value());}
          xywh {373 541 100 10} type {Horz Knob} box FLAT_BOX color 178 selection_color 62 labelsize 10 labelcolor 7 align 4 maximum 127 step 1 textcolor 7
          class SliderW
        }
        Fl_Value_Slider flanger_delay {
          label Delay
          callback {rkr->efx_Flanger->changepar(7,(int)o->value());}
          xywh {373 554 100 10} type {Horz Knob} box FLAT_BOX color 178 selection_color 62 labelsize 10 labelcolor 7 align 4 maximum 127 step 1 textcolor 7
          class SliderW
        }
        Fl_Value_Slider flanger_fb {
          label Fb
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(80);
 return;
} 
rkr->efx_Flanger->changepar(8,(int)o->value());}
          xywh {373 567 100 10} type {Horz Knob} box FLAT_BOX color 178 selection_color 62 labelsize 10 labelcolor 7 align 4 maximum 127 step 1 textcolor 7
          class SliderW
        }
        Fl_Value_Slider flanger_LR {
          label {L/R.Cr}
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(92);
 return;
} 
rkr->efx_Flanger->changepar(9,(int)(o->value()+64));}
          xywh {373 581 100 10} type {Horz Knob} box FLAT_BOX color 178 selection_color 62 labelsize 10 labelcolor 7 align 4 minimum -64 maximum 63 step 1 textcolor 7
          class SliderW
        }
      }
	    Fl_Group REVERB {
        user_data 1
        xywh {480 413 158 184} box UP_BOX color 0 selection_color 0 labelfont 1 align 112
      } {
        Fl_Light_Button reverb_activar {
          label On
          user_data 2
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(116);
 o->value(rkr->Reverb_Bypass);
 return;
}
rkr->Reverb_Bypass=(int)o->value();
if((int) o->value()==0)
rkr->efx_Rev->cleanup();
findpos(8,(int)o->value(),o);}
          xywh {485 417 34 18} shortcut 0x39 color 62 selection_color 1 labelsize 10 align 84 when 1
        }
        Fl_Choice reverb_preset {
          label Preset
          user_data 12008
          callback {rkr->Reverb_Bypass=0;
long long ud= (long long) v;
if((ud==0)||(ud==12008))rkr->efx_Rev->setpreset((int) o->value());
reverb_WD->value(rkr->efx_Rev->getpar(0)-64);
reverb_pan->value(rkr->efx_Rev->getpar(1)-64);
reverb_time->value(rkr->efx_Rev->getpar(2));
reverb_ldel->value(rkr->efx_Rev->getpar(3));
reverb_ldelft->value(rkr->efx_Rev->getpar(4));
reverb_LPF->value(rkr->efx_Rev->getpar(7));
reverb_HPF->value(rkr->efx_Rev->getpar(8));
reverb_damp->value(rkr->efx_Rev->getpar(9));
reverb_RS->value(rkr->efx_Rev->getpar(11));
reverb_type->value(rkr->efx_Rev->getpar(10));
if((int)reverb_activar->value())rkr->Reverb_Bypass=1;}
          xywh {557 417 76 18} down_box BORDER_BOX selection_color 0 labelsize 10 labelcolor 7 when 6 textsize 10 textcolor 7
        } {
          MenuItem {} {
            label {Cathedral 1}
            xywh {44 44 36 21} labelsize 10
          }
          MenuItem {} {
            label {Cathedral 2}
            xywh {44 44 36 21} labelsize 10
          }
          MenuItem {} {
            label {Cathedral 3}
            xywh {44 44 36 21} labelsize 10
          }
          MenuItem {} {
            label {Hall 1}
            xywh {54 54 36 21} labelsize 10
          }
          MenuItem {} {
            label {Hall 2}
            xywh {64 64 36 21} labelsize 10
          }
          MenuItem {} {
            label {Room 1}
            xywh {74 74 36 21} labelsize 10
          }
          MenuItem {} {
            label {Room 2}
            xywh {84 84 36 21} labelsize 10
          }
          MenuItem {} {
            label Basement
            xywh {94 94 36 21} labelsize 10
          }
          MenuItem {} {
            label Tunnel
            xywh {104 104 36 21} labelsize 10
          }
          MenuItem {} {
            label {Echoed 1}
            xywh {114 114 36 21} labelsize 10
          }
          MenuItem {} {
            label {Echoed 2}
            xywh {124 124 36 21} labelsize 10
          }
          MenuItem {} {
            label {Very Long 1}
            xywh {134 134 36 21} labelsize 10
          }
          MenuItem {} {
            label {Very Long 2}
            xywh {144 144 36 21} labelsize 10
          }
        }
        Fl_Value_Slider reverb_WD {
          label {Wet/Dry}
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(57);
 return;
} 
rkr->efx_Rev->changepar(0,(int)(o->value()+64));}
          xywh {531 440 100 10} type {Horz Knob} box FLAT_BOX color 178 selection_color 62 labelsize 10 labelcolor 7 align 4 minimum -64 maximum 63 step 1 textcolor 7
          class SliderW
        }
        Fl_Value_Slider reverb_pan {
          label Pan
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(63);
 return;
} 
rkr->efx_Rev->changepar(1,(int)(o->value()+64));}
          xywh {531 452 100 10} type {Horz Knob} box FLAT_BOX color 178 selection_color 62 labelsize 10 labelcolor 7 align 4 minimum -64 maximum 63 step 1 textcolor 7
          class SliderW
        }
        Fl_Value_Slider reverb_time {
          label Time
          callback {rkr->efx_Rev->changepar(2,(int)o->value());}
          xywh {531 465 100 10} type {Horz Knob} box FLAT_BOX color 178 selection_color 62 labelsize 10 labelcolor 7 align 4 maximum 127 step 1 textcolor 7
          class SliderW
        }
        Fl_Value_Slider reverb_ldel {
          label {I.Del}
          callback {rkr->efx_Rev->changepar(3,(int)o->value());}
          xywh {531 477 100 10} type {Horz Knob} box FLAT_BOX color 178 selection_color 62 labelsize 10 labelcolor 7 align 4 maximum 127 step 1 textcolor 7
          class SliderW
        }
        Fl_Value_Slider reverb_ldelft {
          label {Del.E/R}
          callback {rkr->efx_Rev->changepar(4,(int)o->value());}
          xywh {531 490 100 10} type {Horz Knob} box FLAT_BOX color 178 selection_color 62 labelsize 10 labelcolor 7 align 4 maximum 127 step 1 textcolor 7
          class SliderW
        }
        Fl_Choice reverb_type {
          label Type
          user_data 12
          callback {rkr->efx_Rev->changepar(10,(int)o->value());}
          xywh {542 505 72 16} down_box BORDER_BOX selection_color 0 labelsize 10 labelcolor 7 textsize 10 textcolor 7
        } {
          MenuItem {} {
            label Freeverb
            xywh {34 34 36 21} labelsize 10
          }
          MenuItem {} {
            label Random
            callback {rkr->efx_Rev->changepar(10,1)}
            xywh {34 34 36 21} labelsize 10
          }
        }
        Fl_Value_Slider reverb_RS {
          label {R.Size}
          callback {rkr->Reverb_Bypass=0;
rkr->efx_Rev->changepar(11,(int)o->value());
if((int)reverb_activar->value())rkr->Reverb_Bypass=1;}
          xywh {531 529 100 10} type {Horz Knob} box FLAT_BOX color 178 selection_color 62 labelsize 10 labelcolor 7 align 4 when 4 minimum 1 maximum 127 step 1 value 1 textcolor 7
          class SliderW
        }
        Fl_Value_Slider reverb_LPF {
          label LPF
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(87);
 return;
} 
rkr->efx_Rev->changepar(7,(int)o->value());}
          xywh {531 544 100 10} type {Horz Knob} box FLAT_BOX color 178 selection_color 62 labelsize 10 labelcolor 7 align 4 minimum 20 maximum 26000 step 1 value 20000 textcolor 7
          class SliderW
        }
        Fl_Value_Slider reverb_HPF {
          label HPF
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(90);
 return;
} 
rkr->efx_Rev->changepar(8,(int)o->value());}
          xywh {531 560 100 10} type {Horz Knob} box FLAT_BOX color 178 selection_color 62 labelsize 10 labelcolor 7 align 4 minimum 20 maximum 20000 step 1 value 20 textcolor 7
          class SliderW
        }
        Fl_Value_Slider reverb_damp {
          label Damp
          callback {rkr->efx_Rev->changepar(9,(int)o->value());}
          xywh {531 576 100 10} type {Horz Knob} box FLAT_BOX color 178 selection_color 62 labelsize 10 labelcolor 7 align 4 minimum 64 maximum 127 step 1 value 64 textcolor 7
          class SliderW
        }
      }

      Fl_Group WHAWHA {
        user_data 1
        xywh {320 210 158 184} box UP_BOX color 0 selection_color 0 labelfont 1 align 112 hide
      } {
        Fl_Light_Button WhaWha_activar {
          label On
          user_data 2
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(116);
 o->value(rkr->WhaWha_Bypass);
 return;
}
rkr->WhaWha_Bypass=(int)o->value();
if((int) o->value()==0)
rkr->efx_WhaWha->cleanup();
findpos(10,(int)o->value(),o);}
          xywh {325 214 34 18} shortcut 0x36 color 62 selection_color 1 labelsize 10 align 84 when 1
        }
        Fl_Choice WhaWha_preset {
          label Preset
          user_data 12010
          callback {rkr->WhaWha_Bypass=0;
long long ud= (long long) v;
if((ud==0)||(ud==12010))rkr->efx_WhaWha->setpreset((int) o->value()); 
WhaWha_WD->value(rkr->efx_WhaWha->getpar(0)-64);
WhaWha_pan->value(rkr->efx_WhaWha->getpar(1)-64);
WhaWha_freq->value(rkr->efx_WhaWha->getpar(2));
WhaWha_rnd->value(rkr->efx_WhaWha->getpar(3));
WhaWha_lfotype->value(rkr->efx_WhaWha->getpar(4));
WhaWha_stdf->value(rkr->efx_WhaWha->getpar(5));
WhaWha_dpth->value(rkr->efx_WhaWha->getpar(6));
WhaWha_ampsns->value(rkr->efx_WhaWha->getpar(7));
WhaWha_ampsnsinv->value(rkr->efx_WhaWha->getpar(8));
WhaWha_smooth->value(rkr->efx_WhaWha->getpar(9));
if((int)WhaWha_activar->value()) rkr->WhaWha_Bypass=1;}
          xywh {397 214 76 18} down_box BORDER_BOX selection_color 0 labelsize 10 labelcolor 7 when 6 textsize 10 textcolor 7
        } {
          MenuItem {} {
            label WahWah
            xywh {62 62 36 21} labelsize 10
          }
          MenuItem {} {
            label AutoWah
            xywh {62 62 36 21} labelsize 10
          }
          MenuItem {} {
            label Sweep
            xywh {62 62 36 21} labelsize 10
          }
          MenuItem {} {
            label VocalMorph1
            xywh {72 72 36 21} labelsize 10
          }
          MenuItem {} {
            label VocalMorph2
            xywh {82 82 36 21} labelsize 10
          }
        }
        Fl_Value_Slider WhaWha_WD {
          label {Wet/Dry}
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(28);
 return;
} 
rkr->efx_WhaWha->changepar(0,(int)(o->value()+64));}
          xywh {369 239 100 10} type {Horz Knob} box FLAT_BOX color 178 selection_color 62 labelsize 10 labelcolor 7 align 4 minimum -64 maximum 63 step 1 textcolor 7
          class SliderW
        }
        Fl_Value_Slider WhaWha_pan {
          label Pan
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(66);
 return;
} 
rkr->efx_WhaWha->changepar(1,(int)(o->value()+64));}
          xywh {369 251 100 10} type {Horz Knob} box FLAT_BOX color 178 selection_color 62 labelsize 10 labelcolor 7 align 4 minimum -64 maximum 63 step 1 textcolor 7
          class SliderW
        }
        Fl_Value_Slider WhaWha_freq {
          label Tempo
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(75);
 return;
} 
rkr->efx_WhaWha->changepar(2,(int)o->value());}
          xywh {369 263 100 10} type {Horz Knob} box FLAT_BOX color 178 selection_color 62 labelsize 10 labelcolor 7 align 4 minimum 1 maximum 600 step 1 textcolor 7
          class SliderW
        }
        Fl_Value_Slider WhaWha_rnd {
          label Rnd
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(108);
 return;
} 
rkr->efx_WhaWha->changepar(3,(int)o->value());}
          xywh {369 275 100 10} type {Horz Knob} box FLAT_BOX color 178 selection_color 62 labelsize 10 labelcolor 7 align 4 maximum 127 step 1 textcolor 7
          class SliderW
        }
        Fl_Choice WhaWha_lfotype {
          label {LFO Type}
          callback {rkr->efx_WhaWha->changepar(4,(int)o->value())} open
          xywh {381 289 72 16} down_box BORDER_BOX selection_color 0 labelsize 10 labelcolor 7 textsize 10 textcolor 7
          code0 {o->menu(menu_chorus_lfotype);}
        } {}
        Fl_Value_Slider WhaWha_stdf {
          label {St.df}
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(102);
 return;
} 
rkr->efx_WhaWha->changepar(5,(int)o->value());}
          xywh {369 315 100 10} type {Horz Knob} box FLAT_BOX color 178 selection_color 62 labelsize 10 labelcolor 7 align 4 maximum 127 step 1 textcolor 7
          class SliderW
        }
        Fl_Value_Slider WhaWha_dpth {
          label Depth
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(1);
 return;
} 
rkr->efx_WhaWha->changepar(6,(int)o->value());}
          xywh {369 327 100 10} type {Horz Knob} box FLAT_BOX color 178 selection_color 62 labelsize 10 labelcolor 7 align 4 maximum 127 step 1 textcolor 7
          class SliderW
        }
        Fl_Value_Slider WhaWha_ampsns {
          label {Amp.S.}
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(111);
 return;
} 
rkr->efx_WhaWha->changepar(7,(int)o->value());}
          xywh {369 339 100 10} type {Horz Knob} box FLAT_BOX color 178 selection_color 62 labelsize 10 labelcolor 7 align 4 maximum 127 step 1 textcolor 7
          class SliderW
        }
        Fl_Check_Button WhaWha_ampsnsinv {
          label {Amp.S Inv}
          user_data 2
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(112);
 return;
} 
rkr->efx_WhaWha->changepar(8,(int)o->value());}
          xywh {375 357 70 15} down_box BORDER_BOX labelsize 10 labelcolor 7
        }
        Fl_Value_Slider WhaWha_smooth {
          label Smooth
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(113);
 return;
} 
rkr->efx_WhaWha->changepar(9,(int)o->value());}
          xywh {369 375 100 10} type {Horz Knob} box FLAT_BOX color 178 selection_color 62 labelsize 10 labelcolor 7 align 4 maximum 127 step 1 textcolor 7
          class SliderW
        }
      }

      Fl_Group ALIENWAH {
        user_data 1
        xywh {320 212 158 184} box UP_BOX color 0 selection_color 0 labelfont 1 align 112 hide
      } {
        Fl_Light_Button Alienwah_activar {
          label On
          user_data 2
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(116);
 o->value(rkr->Alienwah_Bypass);
 return;
}
rkr->Alienwah_Bypass=(int)o->value();
if((int) o->value()==0)
rkr->efx_Alienwah->cleanup();
findpos(11,(int)o->value(),o);}
          xywh {324 216 34 18} shortcut 0x36 color 62 selection_color 1 labelsize 10 align 84 when 1
        }
        Fl_Choice Alienwah_preset {
          label Preset
          user_data 12011
          callback {long long ud= (long long) v;
if((ud==0)||(ud==12011))rkr->efx_Alienwah->setpreset((int) o->value());
Alienwah_WD->value(rkr->efx_Alienwah->getpar(0)-64);
Alienwah_pan->value(rkr->efx_Alienwah->getpar(1)-64);
Alienwah_freq->value(rkr->efx_Alienwah->getpar(2));
Alienwah_rnd->value(rkr->efx_Alienwah->getpar(3));
Alienwah_lfotype->value(rkr->efx_Alienwah->getpar(4));
Alienwah_stdf->value(rkr->efx_Alienwah->getpar(5));
Alienwah_dpth->value(rkr->efx_Alienwah->getpar(6));
Alienwah_fb->value(rkr->efx_Alienwah->getpar(7));
Alienwah_delay->value(rkr->efx_Alienwah->getpar(8));
Alienwah_LR->value(rkr->efx_Alienwah->getpar(9)-64);
Alienwah_phase->value(rkr->efx_Alienwah->getpar(10));}
          xywh {396 216 76 18} down_box BORDER_BOX selection_color 0 labelsize 10 labelcolor 7 when 6 textsize 10 textcolor 7
        } {
          MenuItem {} {
            label AlienWah1
            xywh {72 72 36 21} labelsize 10
          }
          MenuItem {} {
            label AlienWah2
            xywh {72 72 36 21} labelsize 10
          }
          MenuItem {} {
            label AlienWah3
            xywh {72 72 36 21} labelsize 10
          }
          MenuItem {} {
            label AlienWah4
            xywh {82 82 36 21} labelsize 10
          }
        }
        Fl_Value_Slider Alienwah_WD {
          label {Wet/Dry}
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(55);
 return;
} 
rkr->efx_Alienwah->changepar(0,(int)(o->value()+64));}
          xywh {368 241 100 10} type {Horz Knob} box FLAT_BOX color 178 selection_color 62 labelsize 10 labelcolor 7 align 4 minimum -64 maximum 63 step 1 textcolor 7
          class SliderW
        }
        Fl_Value_Slider Alienwah_pan {
          label Pan
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(61);
 return;
} 
rkr->efx_Alienwah->changepar(1,(int)(o->value()+64));}
          xywh {368 253 100 10} type {Horz Knob} box FLAT_BOX color 178 selection_color 62 labelsize 10 labelcolor 7 align 4 minimum -64 maximum 63 step 1 textcolor 7
          class SliderW
        }
        Fl_Value_Slider Alienwah_freq {
          label Tempo
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(76);
 return;
} 
rkr->efx_Alienwah->changepar(2,(int)o->value());}
          xywh {368 265 100 10} type {Horz Knob} box FLAT_BOX color 178 selection_color 62 labelsize 10 labelcolor 7 align 4 minimum 1 maximum 600 step 1 textcolor 7
          class SliderW
        }
        Fl_Value_Slider Alienwah_rnd {
          label Rnd
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(109);
 return;
} 
rkr->efx_Alienwah->changepar(3,(int)o->value());}
          xywh {368 277 100 10} type {Horz Knob} box FLAT_BOX color 178 selection_color 62 labelsize 10 labelcolor 7 align 4 maximum 127 step 1 textcolor 7
          class SliderW
        }
        Fl_Choice Alienwah_lfotype {
          label {LFO Type}
          callback {rkr->efx_Alienwah->changepar(4,(int)o->value())} open
          xywh {380 291 72 16} down_box BORDER_BOX selection_color 0 labelsize 10 labelcolor 7 textsize 10 textcolor 7
          code0 {o->menu(menu_chorus_lfotype);}
        } {}
        Fl_Value_Slider Alienwah_phase {
          label Phase
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(115);
 return;
} 
rkr->efx_Alienwah->changepar(10,(int)o->value());}
          xywh {368 317 100 10} type {Horz Knob} box FLAT_BOX color 178 selection_color 62 labelsize 10 labelcolor 7 align 4 maximum 127 step 1 textcolor 7
          class SliderW
        }
        Fl_Value_Slider Alienwah_stdf {
          label {St.df}
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(103);
 return;
} 
rkr->efx_Alienwah->changepar(5,(int)o->value());}
          xywh {368 329 100 10} type {Horz Knob} box FLAT_BOX color 178 selection_color 62 labelsize 10 labelcolor 7 align 4 maximum 127 step 1 textcolor 7
          class SliderW
        }
        Fl_Value_Slider Alienwah_dpth {
          label Depth
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(20);
 return;
} 
rkr->efx_Alienwah->changepar(6,(int)o->value());}
          xywh {368 341 100 10} type {Horz Knob} box FLAT_BOX color 178 selection_color 62 labelsize 10 labelcolor 7 align 4 maximum 127 step 1 textcolor 7
          class SliderW
        }
        Fl_Value_Slider Alienwah_delay {
          label Delay
          callback {rkr->Alienwah_Bypass=0;
rkr->efx_Alienwah->changepar(8,(int)o->value());
if (Alienwah_activar->value()) rkr->Alienwah_Bypass=1;}
          xywh {368 353 100 10} type {Horz Knob} box FLAT_BOX color 178 selection_color 62 labelsize 10 labelcolor 7 align 4 maximum 127 step 1 textcolor 7
          class SliderW
        }
        Fl_Value_Slider Alienwah_fb {
          label Fb
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(82);
 return;
} 
rkr->efx_Alienwah->changepar(7,(int)o->value());}
          xywh {368 365 100 10} type {Horz Knob} box FLAT_BOX color 178 selection_color 62 labelsize 10 labelcolor 7 align 4 maximum 127 step 1 textcolor 7
          class SliderW
        }
        Fl_Value_Slider Alienwah_LR {
          label {L/R.Cr}
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(96);
 return;
} 
rkr->efx_Alienwah->changepar(9,(int)(o->value()+64));}
          xywh {368 378 100 10} type {Horz Knob} box FLAT_BOX color 178 selection_color 62 labelsize 10 labelcolor 7 align 4 minimum -64 maximum 63 step 1 textcolor 7
          class SliderW
        }
      }
      Fl_Group CABINET {
        user_data 1
        xywh {161 211 158 184} box UP_BOX color 0 selection_color 0 labelfont 1 align 112 hide
      } {
        Fl_Light_Button Cabinet_activar {
          label On
          user_data 2
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(116);
 o->value(rkr->Cabinet_Bypass);
 return;
}
rkr->Cabinet_Bypass=(int)o->value();
findpos(12,(int)o->value(),o);}
          xywh {166 215 34 18} shortcut 0x32 color 62 selection_color 1 labelsize 10 align 84 when 1
        }
        Fl_Choice Cabinet_preset {
          label Preset
          user_data 12012
          callback {rkr->Cabinet_setpreset((int) o->value());}
          xywh {206 256 106 18} down_box BORDER_BOX selection_color 0 labelsize 10 labelcolor 7 when 6 textsize 10 textcolor 7
        } {
          MenuItem {} {
            label {Marshall-4-12}
            xywh {0 0 36 21} labelsize 10
          }
          MenuItem {} {
            label {Celestion G12M}
            xywh {0 0 36 21} labelsize 10
          }
          MenuItem {} {
            label {Jensen Alnico P12N}
            xywh {0 0 36 21} labelsize 10
          }
          MenuItem {} {
            label {Jensen Alnico P15N}
            xywh {0 0 36 21} labelsize 10
          }
          MenuItem {} {
            label {Delta Demon}
            xywh {0 0 36 21} labelsize 10
          }
          MenuItem {} {
            label {Celestion-EVH12}
            xywh {0 0 36 21} labelsize 10
          }
          MenuItem {} {
            label {Eminence Copperhead}
            xywh {0 0 36 21} labelsize 10
          }
          MenuItem {} {
            label {Mesa Boogie}
            xywh {0 0 36 21} labelsize 10
          }
          MenuItem {} {
            label {Jazz-Chorus}
            xywh {0 0 36 21} labelsize 10
          }
          MenuItem {} {
            label {Vox-Bright}
            xywh {0 0 36 21} labelsize 10
          }
          MenuItem {} {
            label {Marshall-I}
            xywh {0 0 36 21} labelsize 10
          }
        }
        Fl_Value_Slider Cabinet_output {
          label Gain
          callback {rkr->efx_Cabinet->changepar(0,(int)(o->value()+64));}
          xywh {209 303 100 10} type {Horz Knob} box FLAT_BOX color 178 selection_color 62 labelsize 10 labelcolor 7 align 4 minimum -64 maximum 63 step 1 textcolor 7
          class SliderW
        }
      }
      Fl_Group PAN {
        user_data 1
        xywh {320 212 158 184} box UP_BOX color 0 selection_color 0 labelfont 1 align 112 hide
      } {
        Fl_Light_Button pan_activar {
          label On
          user_data 2
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(116);
 o->value(rkr->Pan_Bypass);
 return;
}
rkr->Pan_Bypass=(int)o->value();
if((int) o->value()==0)
rkr->efx_Pan->cleanup();
findpos(13,(int)o->value(),o);}
          xywh {325 216 34 18} shortcut 0x36 color 62 selection_color 1 labelsize 10 align 84 when 1
        }
        Fl_Choice pan_preset {
          label Preset
          user_data 12013
          callback {long long ud= (long long) v;
if((ud==0)||(ud==12013))rkr->efx_Pan->setpreset((int) o->value());
pan_WD->value(rkr->efx_Pan->getpar(0)-64);
pan_pan->value(rkr->efx_Pan->getpar(1)-64);
pan_freq->value(rkr->efx_Pan->getpar(2));
pan_rnd->value(rkr->efx_Pan->getpar(3));
pan_lfotype->value(rkr->efx_Pan->getpar(4));
pan_stdf->value(rkr->efx_Pan->getpar(5));
pan_extra->value(rkr->efx_Pan->getpar(6));
pan_autopan->value(rkr->efx_Pan->getpar(7));
pan_extraon->value(rkr->efx_Pan->getpar(8));}
          xywh {397 216 76 18} down_box BORDER_BOX selection_color 0 labelsize 10 labelcolor 7 when 6 textsize 10 textcolor 7
        } {
          MenuItem {} {
            label AutoPan
            xywh {62 62 36 21} labelsize 10
          }
          MenuItem {} {
            label {Extra Stereo}
            xywh {62 62 36 21} labelsize 10
          }
        }
        Fl_Value_Slider pan_WD {
          label {Wet/Dry}
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(58);
 return;
} 
rkr->efx_Pan->changepar(0,(int)(o->value()+64));}
          xywh {369 241 100 10} type {Horz Knob} box FLAT_BOX color 178 selection_color 62 labelsize 10 labelcolor 7 align 4 minimum -64 maximum 63 step 1 textcolor 7
          class SliderW
        }
        Fl_Value_Slider pan_pan {
          label Pan
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(67);
 return;
} 
rkr->efx_Pan->changepar(1,(int)(o->value()+64));}
          xywh {369 256 100 10} type {Horz Knob} box FLAT_BOX color 178 selection_color 62 labelsize 10 labelcolor 7 align 4 minimum -64 maximum 63 step 1 textcolor 7
          class SliderW
        }
        Fl_Check_Button pan_autopan {
          label AutoPan
          user_data 2
          callback {rkr->efx_Pan->changepar(7,(int)o->value())}
          xywh {355 268 70 18} down_box BORDER_BOX labelsize 10 labelcolor 7
        }
        Fl_Value_Slider pan_freq {
          label Tempo
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(77);
 return;
} 
rkr->efx_Pan->changepar(2,(int)o->value());}
          xywh {369 285 100 10} type {Horz Knob} box FLAT_BOX color 178 selection_color 62 labelsize 10 labelcolor 7 align 4 minimum 1 maximum 600 step 1 textcolor 7
          class SliderW
        }
        Fl_Value_Slider pan_rnd {
          label Rnd
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(110);
 return;
} 
rkr->efx_Pan->changepar(3,(int)o->value());}
          xywh {369 297 100 10} type {Horz Knob} box FLAT_BOX color 178 selection_color 62 labelsize 10 labelcolor 7 align 4 maximum 127 step 1 textcolor 7
          class SliderW
        }
        Fl_Choice pan_lfotype {
          label {LFO Type}
          callback {rkr->efx_Pan->changepar(4,(int)o->value());} open
          xywh {381 315 72 16} down_box BORDER_BOX selection_color 0 labelsize 10 labelcolor 7 textsize 10 textcolor 7
          code0 {o->menu(menu_chorus_lfotype);}
        } {}
        Fl_Value_Slider pan_stdf {
          label {St.df}
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(104);
 return;
} 
rkr->efx_Pan->changepar(5,(int)o->value());}
          xywh {369 336 100 10} type {Horz Knob} box FLAT_BOX color 178 selection_color 62 labelsize 10 labelcolor 7 align 4 maximum 127 step 1 textcolor 7
          class SliderW
        }
        Fl_Check_Button pan_extraon {
          label {Extra Stereo}
          user_data 2
          callback {rkr->efx_Pan->changepar(8,(int)o->value())}
          xywh {355 352 82 15} down_box BORDER_BOX labelsize 10 labelcolor 7
        }
        Fl_Value_Slider pan_extra {
          label {E.S.}
          callback {rkr->efx_Pan->changepar(6,(int)o->value());}
          xywh {369 373 100 10} type {Horz Knob} box FLAT_BOX color 178 selection_color 62 labelsize 10 labelcolor 7 align 4 maximum 127 step 1 textcolor 7
          class SliderW
        }
      }

      Fl_Group HAR {
        user_data 1
        xywh {162 413 158 184} box UP_BOX color 0 selection_color 0 labelfont 1 align 112 hide
      } {
        Fl_Light_Button har_activar {
          label On
          user_data 2
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(116);
 o->value(rkr->Harmonizer_Bypass);
 return;
}
rkr->Harmonizer_Bypass=(int)o->value();
if((int) o->value()==0)
rkr->efx_Har->cleanup();
rkr->efx_Har->changepar(3,rkr->efx_Har->getpar(3));
Chord(0);
findpos(14,(int)o->value(),o);}
          xywh {167 417 34 18} shortcut 0x30 color 62 selection_color 1 labelsize 10 when 1
        }
        Fl_Choice har_preset {
          label Preset
          user_data 12014
          callback {long long ud= (long long) v;
if((ud==0)||(ud==12014))rkr->efx_Har->setpreset((int)o->value());
har_WD->value(rkr->efx_Har->getpar(0)-64);
har_pan->value(rkr->efx_Har->getpar(1)-64);
har_gan->value(rkr->efx_Har->getpar(2)-64);
har_int->value(rkr->efx_Har->getpar(3)-12);
har_SELECT->value(rkr->efx_Har->getpar(5));
har_note->value(rkr->efx_Har->getpar(6));
har_type->value(rkr->efx_Har->getpar(7));
har_freq1->value(rkr->efx_Har->getpar(4));
har_gan1->value(rkr->efx_Har->getpar(8)-64);
har_q1->value(rkr->efx_Har->getpar(9)-64);
har_MIDI->value(rkr->efx_Har->getpar(10));
if ((rkr->efx_Har->PMIDI) || (rkr->efx_Har->PSELECT)) Chord(0);}
          xywh {239 417 76 18} down_box BORDER_BOX selection_color 0 labelsize 10 labelcolor 7 when 6 textsize 10 textcolor 7
        } {
          MenuItem {} {
            label Plain
            xywh {0 0 45 26} labelsize 10
          }
          MenuItem {} {
            label Octavator
            xywh {32 32 36 21} labelsize 10
          }
          MenuItem {} {
            label {3m Down}
            xywh {32 32 36 21} labelsize 10
          }
        }
        Fl_Value_Slider har_WD {
          label {Wet/Dry}
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(31);
 return;
} 
rkr->efx_Har->changepar(0,(int)(o->value()+64));}
          xywh {212 443 100 10} type {Horz Knob} box FLAT_BOX color 178 selection_color 62 labelsize 10 labelcolor 7 align 4 minimum -64 maximum 63 step 1 textcolor 7
          class SliderW
        }
        Fl_Value_Slider har_int {
          label {Int.}
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(27);
 return;
} 
rkr->Harmonizer_Bypass=0;
rkr->efx_Har->changepar(3,(int)(o->value()+12));
if((int)har_activar->value())rkr->Harmonizer_Bypass=1;}
          xywh {212 456 100 10} type {Horz Knob} box FLAT_BOX color 178 selection_color 62 labelsize 10 labelcolor 7 align 4 minimum -12 maximum 12 step 1 textcolor 7
          class SliderW
        }
        Fl_Value_Slider har_gan {
          label Gain
          callback {rkr->efx_Har->changepar(2,(int)(o->value()+64));}
          xywh {212 471 100 10} type {Horz Knob} box FLAT_BOX color 178 selection_color 62 labelsize 10 labelcolor 7 align 4 minimum -64 maximum 63 step 1 textcolor 7
          class SliderW
        }
        Fl_Value_Slider har_pan {
          label Pan
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(49);
 return;
} 
rkr->efx_Har->changepar(1,(int)(o->value()+64));}
          xywh {212 484 100 10} type {Horz Knob} box FLAT_BOX color 178 selection_color 62 labelsize 10 labelcolor 7 align 4 minimum -64 maximum 63 step 1 textcolor 7
          class SliderW
        }
        Fl_Value_Slider har_freq1 {
          label Freq
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(26);
 return;
} 
rkr->efx_Har->changepar(4,(int)o->value());}
          xywh {213 501 100 10} type {Horz Knob} box FLAT_BOX color 178 selection_color 62 labelsize 10 labelcolor 7 align 4 minimum 20 maximum 26000 step 1 value 2000 textcolor 7
          class SliderW
        }
        Fl_Value_Slider har_gan1 {
          label Gain
          callback {rkr->efx_Har->changepar(8,(int)(o->value()+64));}
          xywh {212 513 100 10} type {Horz Knob} box FLAT_BOX color 178 selection_color 62 labelsize 10 labelcolor 7 align 4 minimum -64 maximum 63 step 1 textcolor 7
          class SliderW
        }
        Fl_Value_Slider har_q1 {
          label Q
          callback {rkr->efx_Har->changepar(9,(int)(o->value()+64));}
          xywh {212 525 100 10} type {Horz Knob} box FLAT_BOX color 178 selection_color 62 labelsize 10 labelcolor 7 align 4 minimum -64 maximum 63 step 1 textcolor 7
          class SliderW
        }
        Fl_Check_Button har_MIDI {
          label MIDI
          user_data 2
          callback {rkr->efx_Har->changepar(10,(int)o->value());
rkr->RC->cleanup();
if(!(int)o->value())rkr->efx_Har->changepar(3,rkr->efx_Har->getpar(3));}
          xywh {171 537 15 15} down_box BORDER_BOX labelsize 10 labelcolor 7 align 8
        }
        Fl_Check_Button har_SELECT {
          label SEL
          user_data 2
          callback {rkr->efx_Har->changepar(5,(int)o->value());
rkr->RC->cleanup();
if(!(int)o->value())rkr->efx_Har->changepar(3,rkr->efx_Har->getpar(3));
Chord(0);}
          xywh {171 555 15 15} down_box BORDER_BOX labelsize 10 labelcolor 7 align 8
        }
        Fl_Box har_chordname {
          xywh {218 539 98 27} labelsize 12 labelcolor 7
        }
        Fl_Value_Slider har_note {
          label Note
          callback {rkr->efx_Har->changepar(6,(unsigned char)o->value());
Chord(0);}
          xywh {212 571 100 10} type {Horz Knob} box FLAT_BOX color 178 selection_color 62 labelsize 10 labelcolor 7 align 4 maximum 23 step 1 textcolor 7
          class SliderW
        }
        Fl_Value_Slider har_type {
          label Chord
          callback {rkr->efx_Har->changepar(7,(unsigned char)o->value());
Chord(0);}
          xywh {212 583 100 10} type {Horz Knob} box FLAT_BOX color 178 selection_color 62 labelsize 10 labelcolor 7 align 4 maximum 33 step 1 textcolor 7
          class SliderW
        }
      }
    
      Fl_Group MUSDELAY {
        user_data 1
        xywh {480 212 158 184} box UP_BOX color 0 selection_color 0 labelfont 1 align 112 hide
      } {
        Fl_Light_Button musdelay_activar {
          label On
          user_data 2
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(116);
 o->value(rkr->MusDelay_Bypass);
 return;
}
rkr->MusDelay_Bypass=(int)o->value();
if((int) o->value()==0)
rkr->efx_MusDelay->cleanup();
findpos(15,(int)o->value(),o);}
          xywh {485 216 34 18} shortcut 0x35 color 62 selection_color 1 labelsize 10 align 84 when 1
        }
        Fl_Choice musdelay_preset {
          label Preset
          user_data 12015
          callback {rkr->MusDelay_Bypass=0;
long long ud= (long long) v;
if((ud==0)||(ud==12015))rkr->efx_MusDelay->setpreset(o->value());
musdelay_WD->value(rkr->efx_MusDelay->getpar(0)-64);
musdelay_tempo->value(rkr->efx_MusDelay->getpar(10));
musdelay_pan1->value(rkr->efx_MusDelay->getpar(1)-64);
musdelay_pan2->value(rkr->efx_MusDelay->getpar(7)-64);
musdelay_delay1->value(rkr->efx_MusDelay->getpar(2)-1);
musdelay_delay2->value(rkr->efx_MusDelay->getpar(8)-1);
musdelay_delay3->value(rkr->efx_MusDelay->getpar(3)-1);
musdelay_fb1->value(rkr->efx_MusDelay->getpar(5));
musdelay_fb2->value(rkr->efx_MusDelay->getpar(9));
musdelay_LRc->value(rkr->efx_MusDelay->getpar(4)-64);
musdelay_gain1->value(rkr->efx_MusDelay->getpar(11)-64);
musdelay_gain2->value(rkr->efx_MusDelay->getpar(12)-64);
musdelay_damp->value(rkr->efx_MusDelay->getpar(6));
if((int)musdelay_activar->value())rkr->MusDelay_Bypass=1;}
          xywh {557 216 76 18} down_box BORDER_BOX selection_color 0 labelsize 10 labelcolor 7 when 6 textsize 10 textcolor 7
        } {
          MenuItem {} {
            label {Echo 1}
            xywh {62 62 36 21} labelsize 10
          }
          MenuItem {} {
            label {Echo 2}
            xywh {62 62 36 21} labelsize 10
          }
        }
        Fl_Value_Slider musdelay_WD {
          label {Wet/Dry}
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(56);
 return;
} 
rkr->efx_MusDelay->changepar(0,(int)o->value()+64);}
          xywh {533 238 100 10} type {Horz Knob} box FLAT_BOX color 178 selection_color 62 labelsize 10 labelcolor 7 align 4 minimum -64 maximum 63 step 1 textcolor 7
          class SliderW
        }
        Fl_Value_Slider musdelay_LRc {
          label {L/R.Cr}
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(98);
 return;
} 
rkr->efx_MusDelay->changepar(4,(int)o->value()+64);}
          xywh {533 250 100 10} type {Horz Knob} box FLAT_BOX color 178 selection_color 62 labelsize 10 labelcolor 7 align 4 minimum -64 maximum 63 step 1 textcolor 7
          class SliderW
        }
        Fl_Value_Slider musdelay_pan1 {
          label Pan1
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(62);
 return;
} 
rkr->efx_MusDelay->changepar(1,(int)o->value()+64);}
          xywh {533 262 100 10} type {Horz Knob} box FLAT_BOX color 178 selection_color 62 labelsize 10 labelcolor 7 align 4 minimum -64 maximum 63 step 1 textcolor 7
          class SliderW
        }
        Fl_Value_Slider musdelay_pan2 {
          label Pan2
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(65);
 return;
} 
rkr->efx_MusDelay->changepar(7,(int)o->value()+64);}
          xywh {533 274 100 10} type {Horz Knob} box FLAT_BOX color 178 selection_color 62 labelsize 10 labelcolor 7 align 4 minimum -64 maximum 63 step 1 textcolor 7
          class SliderW
        }
        Fl_Choice musdelay_delay1 {
          user_data 12
          callback {rkr->MusDelay_Bypass=0;
rkr->efx_MusDelay->changepar(2,o->value()+1);
if((int)musdelay_activar->value())rkr->MusDelay_Bypass=1;}
          xywh {490 294 38 14} down_box BORDER_BOX labelsize 10 labelcolor 7 textsize 10 textcolor 7
        } {
          MenuItem {} {
            label 1
            xywh {0 0 45 26} labelsize 10
          }
          MenuItem {} {
            label {1/2}
            xywh {10 10 45 26} labelsize 10
          }
          MenuItem {} {
            label {1/3}
            xywh {20 20 45 26} labelsize 10
          }
          MenuItem {} {
            label {1/4}
            xywh {30 30 45 26} labelsize 10
          }
          MenuItem {} {
            label {1/5}
            xywh {40 40 45 26} labelsize 10
          }
          MenuItem {} {
            label {1/6}
            xywh {50 50 45 26} labelsize 10
          }
        }
        Fl_Choice musdelay_delay3 {
          user_data 12
          callback {rkr->MusDelay_Bypass=0;
rkr->efx_MusDelay->changepar(3,o->value()+1);
if((int)musdelay_activar->value())rkr->MusDelay_Bypass=1;}
          xywh {542 294 38 14} down_box BORDER_BOX labelsize 10 labelcolor 7 textsize 10 textcolor 7
        } {
          MenuItem {} {
            label 1
            xywh {10 10 45 26} labelsize 10
          }
          MenuItem {} {
            label {1/2}
            xywh {20 20 45 26} labelsize 10
          }
          MenuItem {} {
            label {1/3}
            xywh {30 30 45 26} labelsize 10
          }
          MenuItem {} {
            label {1/4}
            xywh {40 40 45 26} labelsize 10
          }
          MenuItem {} {
            label {1/5}
            xywh {50 50 45 26} labelsize 10
          }
          MenuItem {} {
            label {1/6}
            xywh {60 60 45 26} labelsize 10
          }
          MenuItem {} {
            label 0
            xywh {0 0 45 26} labelsize 10
          }
        }
        Fl_Choice musdelay_delay2 {
          callback {rkr->MusDelay_Bypass=0;
rkr->efx_MusDelay->changepar(8,o->value()+1);
if((int)musdelay_activar->value())rkr->MusDelay_Bypass=1;}
          xywh {594 294 38 14} down_box BORDER_BOX labelsize 10 labelcolor 7 textsize 10 textcolor 7
          code0 {o->menu(menu_musdelay_delay1);}
        } {}
        Fl_Value_Slider musdelay_tempo {
          label Tempo
          callback {rkr->MusDelay_Bypass=0;
rkr->efx_MusDelay->changepar(10,(int)o->value());
if((int)musdelay_activar->value())rkr->MusDelay_Bypass=1;}
          xywh {533 315 100 10} type {Horz Knob} box FLAT_BOX color 178 selection_color 62 labelsize 10 labelcolor 7 align 4 when 4 minimum 10 maximum 480 step 1 textcolor 7
          class SliderW
        }
        Fl_Value_Slider musdelay_gain1 {
          label Gain1
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(24);
 return;
} 
rkr->efx_MusDelay->changepar(11,(int)o->value()+64);}
          xywh {533 334 100 10} type {Horz Knob} box FLAT_BOX color 178 selection_color 62 labelsize 10 labelcolor 7 align 4 minimum -64 maximum 63 step 1 textcolor 7
          class SliderW
        }
        Fl_Value_Slider musdelay_gain2 {
          label Gain2
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(25);
 return;
} 
rkr->efx_MusDelay->changepar(12,(int)o->value()+64);}
          xywh {533 346 100 10} type {Horz Knob} box FLAT_BOX color 178 selection_color 62 labelsize 10 labelcolor 7 align 4 minimum -64 maximum 63 step 1 textcolor 7
          class SliderW
        }
        Fl_Value_Slider musdelay_fb1 {
          label {Fb1.}
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(83);
 return;
} 
rkr->efx_MusDelay->changepar(5,(int)o->value());}
          xywh {533 358 100 10} type {Horz Knob} box FLAT_BOX color 178 selection_color 62 labelsize 10 labelcolor 7 align 4 maximum 127 step 1 textcolor 7
          class SliderW
        }
        Fl_Value_Slider musdelay_fb2 {
          label {Fb2.}
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(84);
 return;
} 
rkr->efx_MusDelay->changepar(9,(int)o->value());}
          xywh {533 370 100 10} type {Horz Knob} box FLAT_BOX color 178 selection_color 62 labelsize 10 labelcolor 7 align 4 maximum 127 step 1 textcolor 7
          class SliderW
        }
        Fl_Value_Slider musdelay_damp {
          label Damp
          callback {rkr->efx_MusDelay->changepar(6,(int)o->value());}
          xywh {533 382 100 10} type {Horz Knob} box FLAT_BOX color 178 selection_color 62 labelsize 10 labelcolor 7 align 4 maximum 127 step 1 textcolor 7
          class SliderW
        }
      }

	  */
