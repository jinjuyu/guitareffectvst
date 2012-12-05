/*

CreateEffectPanel
DeleteEffectPanel
이거 제대로 하려면
전 패널을 다 미리 new해두고 스와핑만 하면서 써야한다.
중간에 딜리트가 하나라도 있으면 쓰레드가 와서 잡아먹어버림. 하지만 지금 잘 돌아가므로 놔두자.

	// 음. Convolotron의 컨벌루션wav파일을 Selection으로 해서 이름으로 선택하게 하고 전에 ndrive에 올린
	// wav파일을 이름으로 해서 넣어둔다.
	// 파일이 많으므로 Contolotron에서 메뉴를 3개 두고 나눠서 200여개의 IR파일을 모두 제공한다.
	// 이 메뉴는 panel을 수정해서 따로 작은 1,2,3이라고 쓰인 버튼을 두고
	// 아랫줄에 텍스트로 파일이름의 일부를 넘지않고 잘리게 표시한다.
음 그리고 커스텀 wav파일을 로드할 수도 있게 한다.
setChunk나 getChunk 그리고 브라우즈유져파일 버튼을 누를 때에만
mEffContolotron->filename을 수정해 주면 되고
다른 때에는 건드릴 필요도 없다. 쉽다. 대신 이펙트를 만들 때 버튼에다가
파일네임 셀렉터라는 새로운 Slider/Onoff/Selection에 추가하고
현재 이펙트가 mEffect == mEffConvolotron일 경우 거기에 추가하고 뭐 이런식으로
하면 된다.
SaveData에다가 convolotronFileName, reverbtronFileName등을 추가해 준다.
디폴트 폴더는 Convolotron일 경우 data/IR안에를 디폴트 폴더로 열어서 파일 브라우져가 나오게 한다.
다른 tron시리즈는 data폴더를 디폴트로 열어준다.


compressor, gate, expander는 changepar나 getpar가 n+1 즉 1부터 시작한다.



파라메터 위에서 오른쪽 버튼을 누르면 왼쪽위에 탭드리스트가 떠서 Map To... 탭드리스트에 파라메터를 클릭하면
매핑이 되도록 나중에 한다.
지금한다.

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

	   Fl_Group GATE {
        user_data 1
        xywh {162 211 158 184} box UP_BOX color 0 selection_color 0 labelfont 1 align 112 hide
      } {
        Fl_Light_Button gate_activar {
          label On
          user_data 2
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(116);
 o->value(rkr->Gate_Bypass);
 return;
}
rkr->Gate_Bypass=(int)o->value();
findpos(16,(int)o->value(),o);}
          xywh {167 215 34 18} shortcut 0x32 color 62 selection_color 1 labelsize 10 align 84 when 1
        }
        Fl_Choice gate_preset {
          label Preset
          user_data 12016
          callback {long long ud= (long long) v;
if((ud==0)||(ud==12016))rkr->efx_Gate->Gate_Change_Preset((int) o->value());
gate_ATime->value(rkr->efx_Gate->getpar(3));
gate_RTime->value(rkr->efx_Gate->getpar(4));
gate_range->value(rkr->efx_Gate->getpar(2));
gate_threshold->value(rkr->efx_Gate->getpar(1));
gate_hold->value(rkr->efx_Gate->getpar(7));
gate_HPF->value(rkr->efx_Gate->getpar(6));
gate_LPF->value(rkr->efx_Gate->getpar(5));}
          xywh {239 215 76 18} down_box BORDER_BOX selection_color 0 labelsize 10 labelcolor 7 when 6 textsize 10 textcolor 7
        } {
          MenuItem {} {
            label 0dB
            xywh {42 42 36 21} labelsize 10
          }
          MenuItem {} {
            label {-10dB}
            xywh {42 42 36 21} labelsize 10
          }
          MenuItem {} {
            label {-20dB}
            xywh {42 42 36 21} labelsize 10
          }
        }
        Fl_Value_Slider gate_ATime {
          label {A. Time}
          callback {rkr->efx_Gate->Gate_Change(3,(int)o->value());}
          xywh {213 250 100 10} type {Horz Knob} box FLAT_BOX color 178 selection_color 62 labelsize 10 labelcolor 7 align 4 minimum 1 maximum 250 step 1 value 1 textcolor 7
          class SliderW
        }
        Fl_Value_Slider gate_RTime {
          label {R. Time}
          callback {rkr->efx_Gate->Gate_Change(4, (int) o->value());}
          xywh {212 272 100 10} type {Horz Knob} box FLAT_BOX color 178 selection_color 62 labelsize 10 labelcolor 7 align 4 minimum 2 maximum 250 step 1 value 120 textcolor 7
          class SliderW
        }
        Fl_Value_Slider gate_range {
          label Range
          callback {rkr->efx_Gate->Gate_Change(2, (int) o->value());}
          xywh {212 294 100 10} type {Horz Knob} box FLAT_BOX color 178 selection_color 62 labelsize 10 labelcolor 7 align 4 minimum -90 maximum 0 step 1 textcolor 7
          class SliderW
        }
        Fl_Value_Slider gate_threshold {
          label Thrhold
          callback {rkr->efx_Gate->Gate_Change(1, (int)o->value());}
          xywh {212 316 100 10} type {Horz Knob} box FLAT_BOX color 178 selection_color 62 labelsize 10 labelcolor 7 align 4 minimum -70 maximum 20 step 1 textcolor 7
          class SliderW
        }
        Fl_Value_Slider gate_hold {
          label Hold
          callback {rkr->efx_Gate->Gate_Change(7,(int)o->value());}
          xywh {212 338 100 10} type {Horz Knob} box FLAT_BOX color 178 selection_color 62 labelsize 10 labelcolor 7 align 4 minimum 2 maximum 500 step 1 textcolor 7
          class SliderW
        }
        Fl_Value_Slider gate_LPF {
          label LPF
          callback {rkr->efx_Gate->Gate_Change(5, (int)o->value());}
          xywh {212 357 100 10} type {Horz Knob} box FLAT_BOX color 178 selection_color 62 labelsize 10 labelcolor 7 align 4 minimum 20 maximum 26000 step 1 value 20000 textcolor 7
          class SliderW
        }
        Fl_Value_Slider gate_HPF {
          label HPF
          callback {rkr->efx_Gate->Gate_Change(6, (int)o->value());}
          xywh {212 373 100 10} type {Horz Knob} box FLAT_BOX color 178 selection_color 62 labelsize 10 labelcolor 7 align 4 minimum 20 maximum 20000 step 1 value 20 textcolor 7
          class SliderW
        }
      }

     
      Fl_Group NEWDIST {
        user_data 1
        xywh {480 212 158 184} box UP_BOX color 0 selection_color 0 labelfont 1 align 112 hide
      } {
        Fl_Light_Button newdist_activar {
          label On
          user_data 2
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(116);
 o->value(rkr->NewDist_Bypass);
 return;
}
rkr->NewDist_Bypass=(int)o->value();
if((int) o->value()==0)
rkr->efx_NewDist->cleanup();
findpos(17,(int)o->value(),o);}
          xywh {485 216 34 18} shortcut 0x33 color 62 selection_color 1 labelsize 10 align 84 when 1
        }
        Fl_Choice newdist_preset {
          label Preset
          user_data 12017
          callback {long long ud= (long long) v;
if((ud==0)||(ud==12017))rkr->efx_NewDist->setpreset((int) o->value());
newdist_WD->value(rkr->efx_NewDist->getpar(0)-64);
newdist_LRc->value(rkr->efx_NewDist->getpar(2)-64);
newdist_drive->value(rkr->efx_NewDist->getpar(3));
newdist_level->value(rkr->efx_NewDist->getpar(4));
newdist_tipo->value(rkr->efx_NewDist->getpar(5));
newdist_neg->value(rkr->efx_NewDist->getpar(6));
newdist_st->value(rkr->efx_NewDist->getpar(9));
newdist_oct->value(rkr->efx_NewDist->getpar(11));
newdist_pan->value(rkr->efx_NewDist->getpar(1)-64);
newdist_pf->value(rkr->efx_NewDist->getpar(10));
newdist_lpf->value(rkr->efx_NewDist->getpar(7));
newdist_hpf->value(rkr->efx_NewDist->getpar(8));}
          xywh {557 216 76 18} down_box BORDER_BOX selection_color 0 labelsize 10 labelcolor 7 when 6 textsize 10 textcolor 7
        } {
          MenuItem {} {
            label {New Dist 1}
            xywh {42 42 36 21} labelsize 10
          }
          MenuItem {} {
            label {New Dist 2}
            xywh {42 42 36 21} labelsize 10
          }
          MenuItem {} {
            label {New Dist 3}
            xywh {52 52 36 21} labelsize 10
          }
        }
        Fl_Value_Slider newdist_WD {
          label {Wet/Dry}
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(125);
 return;
} 
rkr->efx_NewDist->changepar(0,(int)(o->value()+64));}
          xywh {532 240 100 10} type {Horz Knob} box FLAT_BOX color 178 selection_color 62 labelsize 10 labelcolor 7 align 4 minimum -64 maximum 63 step 1 textcolor 7
          class SliderW
        }
        Fl_Value_Slider newdist_LRc {
          label {L/R.Cr}
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(127);
 return;
} 
rkr->efx_NewDist->changepar(2,(int)(o->value()+64));}
          xywh {532 254 100 10} type {Horz Knob} box FLAT_BOX color 178 selection_color 62 labelsize 10 labelcolor 7 align 4 minimum -64 maximum 63 step 1 textcolor 7
          class SliderW
        }
        Fl_Value_Slider newdist_drive {
          label Drive
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(2);
 return;
} 
rkr->efx_NewDist->changepar(3,(int)o->value());}
          xywh {532 268 100 10} type {Horz Knob} box FLAT_BOX color 178 selection_color 62 labelsize 10 labelcolor 7 align 4 minimum 1 maximum 127 step 1 value 1 textcolor 7
          class SliderW
        }
        Fl_Value_Slider newdist_level {
          label Level
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(3);
 return;
} 
rkr->efx_NewDist->changepar(4,(int)o->value());}
          xywh {532 282 100 10} type {Horz Knob} box FLAT_BOX color 178 selection_color 62 labelsize 10 labelcolor 7 align 4 maximum 127 step 1 textcolor 7
          class SliderW
        }
        Fl_Choice newdist_tipo {
          label Type
          callback {rkr->efx_NewDist->changepar(5,(int)o->value());}
          xywh {514 296 70 16} down_box BORDER_BOX selection_color 0 labelsize 10 labelcolor 7 textsize 10 textcolor 7
          code0 {o->menu(menu_dist_tipo);}
        } {}
        Fl_Check_Button newdist_neg {
          label {Neg.}
          user_data 2
          callback {rkr->efx_NewDist->changepar(6,(int)o->value());}
          xywh {590 296 42 15} down_box BORDER_BOX labelsize 10 labelcolor 7
        }
        Fl_Value_Slider newdist_st {
          label Color
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(6);
 return;
} 
rkr->efx_NewDist->changepar(9,(int)o->value());}
          xywh {532 318 100 10} type {Horz Knob} box FLAT_BOX color 178 selection_color 62 labelsize 10 labelcolor 7 align 4 maximum 127 step 1 textcolor 7
          class SliderW
        }
        Fl_Value_Slider newdist_oct {
          label {Sub Octv}
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(8);
 return;
} 
rkr->efx_NewDist->changepar(11,(int)o->value());}
          xywh {532 332 100 10} type {Horz Knob} box FLAT_BOX color 178 selection_color 62 labelsize 10 labelcolor 7 align 4 maximum 127 step 1 textcolor 7
          class SliderW
        }
        Fl_Value_Slider newdist_pan {
          label Pan
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(126);
 return;
} 
rkr->efx_NewDist->changepar(1,(int)(o->value()+64));}
          xywh {532 346 100 10} type {Horz Knob} box FLAT_BOX color 178 selection_color 62 labelsize 10 labelcolor 7 align 4 minimum -64 maximum 63 step 1 textcolor 7
          class SliderW
        }
        Fl_Check_Button newdist_pf {
          label {Pre Filter}
          user_data 2
          callback {rkr->efx_NewDist->changepar(10,(int)o->value());}
          xywh {530 356 66 15} down_box BORDER_BOX labelsize 10 labelcolor 7
        }
        Fl_Value_Slider newdist_lpf {
          label LPF
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(4);
 return;
} 
rkr->efx_NewDist->changepar(7,(int)o->value());}
          xywh {532 371 100 10} type {Horz Knob} box FLAT_BOX color 178 selection_color 62 labelsize 10 labelcolor 7 align 4 minimum 20 maximum 26000 step 1 value 20000 textcolor 7
          class SliderW
        }
        Fl_Value_Slider newdist_hpf {
          label HPF
          callback {if(Fl::event_button()==3)
{
 getMIDIControl(5);
 return;
} 
rkr->efx_NewDist->changepar(8,(int)o->value());}
          xywh {532 383 100 10} type {Horz Knob} box FLAT_BOX color 178 selection_color 62 labelsize 10 labelcolor 7 align 4 minimum 20 maximum 20000 step 1 value 20 textcolor 7
          class SliderW
        }
      }
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

	  */
