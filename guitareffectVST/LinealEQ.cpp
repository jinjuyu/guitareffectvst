#include "LinealEQ.h"

namespace LinealEQNS
{
int EQ1Real[] = {
	0, 127, // All of them
};
int EQ1Print[] = {
	-64, 63, // All of them
};
void LinealEQ::LoadPreset(int aaa)
{
	mGUI->SetSliderVal(mGain, RealToPrint(mPlug->mEffEQ1->getpar(0)));
	mGUI->SetSliderVal(mQ, RealToPrint(mPlug->mEffEQ1->getpar(13)));
	mGUI->SetSliderVal(m31, RealToPrint(mPlug->mEffEQ1->getpar(0*5+12)));
	mGUI->SetSliderVal(m63, RealToPrint(mPlug->mEffEQ1->getpar(1*5+12)));
	mGUI->SetSliderVal(m125, RealToPrint(mPlug->mEffEQ1->getpar(2*5+12)));
	mGUI->SetSliderVal(m250, RealToPrint(mPlug->mEffEQ1->getpar(3*5+12)));
	mGUI->SetSliderVal(m500, RealToPrint(mPlug->mEffEQ1->getpar(4*5+12)));
	mGUI->SetSliderVal(m1K, RealToPrint(mPlug->mEffEQ1->getpar(5*5+12)));
	mGUI->SetSliderVal(m2K, RealToPrint(mPlug->mEffEQ1->getpar(6*5+12)));
	mGUI->SetSliderVal(m4K, RealToPrint(mPlug->mEffEQ1->getpar(7*5+12)));
	mGUI->SetSliderVal(m8K, RealToPrint(mPlug->mEffEQ1->getpar(8*5+12)));
	mGUI->SetSliderVal(m16K, RealToPrint(mPlug->mEffEQ1->getpar(9*5+12)));
}
void LinealEQ::DrawText()
{
	int x,y,w=180,h=250;
	if(mWhereis < 5)
	{
		x = 180*mWhereis;
		y = 150+35;
	}
	else
	{
		x = 180*(mWhereis-5);
		y = 150+250+35;
	}
	TextOption op2(x,y-35+3,180,10, 0,0,0,255);
	mGUI->Print2(op2, "Lineal EQ");

	mGUI->Print(TextOption(x,y,60, 13, 0,0,0,255), "Gain");
	y += 15;

	mGUI->Print(TextOption(x,y,60, 13, 0,0,0,255), "Q");
	y += 15;
	y += 15;

	mGUI->Print(TextOption(x,y,60, 13, 0,0,0,255), "31Hz");
	y += 15;

	mGUI->Print(TextOption(x,y,60, 13, 0,0,0,255), "63Hz");
	y += 15;

	mGUI->Print(TextOption(x,y,60, 13, 0,0,0,255), "125Hz");
	y += 15;

	mGUI->Print(TextOption(x,y,60, 13, 0,0,0,255), "250Hz");
	y += 15;

	mGUI->Print(TextOption(x,y,60, 13, 0,0,0,255), "500Hz");
	y += 15;

	mGUI->Print(TextOption(x,y,60, 13, 0,0,0,255), "1KHz");
	y += 15;

	mGUI->Print(TextOption(x,y,60, 13, 0,0,0,255), "2KHz");
	y += 15;

	mGUI->Print(TextOption(x,y,60, 13, 0,0,0,255), "4KHz");
	y += 15;

	mGUI->Print(TextOption(x,y,60, 13, 0,0,0,255), "8KHz");
	y += 15;

	mGUI->Print(TextOption(x,y,60, 13, 0,0,0,255), "16KHz");
	y += 15;

}
LinealEQ::LinealEQ(GLGUI *gui, VstPlugin *plug, int whereis)
	:mGUI(gui), mWhereis(whereis), mPlug(plug)
{

	real = EQ1Real;
	print = EQ1Print;
	int x,y,w=180,h=250;
	if(whereis < 5)
	{
		x = 180*whereis;
		y = 150+35;
	}
	else
	{
		x = 180*(whereis-5);
		y = 150+250+35;
	}

	cbGain = new GainCallback(this);
	cbQ = new QCallback(this);
	cb31 = new F31Callback(this);
	cb63 = new F63Callback(this);
	cb125 = new F125Callback(this);
	cb250 = new F250Callback(this);
	cb500 = new F500Callback(this);
	cb1K = new F1KCallback(this);
	cb2K = new F2KCallback(this);
	cb4K = new F4KCallback(this);
	cb8K = new F8KCallback(this);
	cb16K = new F16KCallback(this);

	mButtons.push_back(mGUI->NewSlider(x+60,y,120, print[0], print[1])); // Gain
	mGain = *(mButtons.end()-1);
	mGUI->SetSliderCallback(*(mButtons.end()-1), cbGain);
	mGUI->SetSliderVal(*(mButtons.end()-1), 0);
	y += 15;

	mButtons.push_back(mGUI->NewSlider(x+60,y,120, print[0], print[1])); // Q
	mQ = *(mButtons.end()-1);
	mGUI->SetSliderCallback(*(mButtons.end()-1), cbQ);
	mGUI->SetSliderVal(*(mButtons.end()-1), 0);
	y += 15;
	y += 15;

	mButtons.push_back(mGUI->NewSlider(x+60,y,120, print[0], print[1])); // Freqs
	m31 = *(mButtons.end()-1);
	mGUI->SetSliderCallback(*(mButtons.end()-1), cb31);
	mGUI->SetSliderVal(*(mButtons.end()-1), 0);
	y += 15;

	mButtons.push_back(mGUI->NewSlider(x+60,y,120, print[0], print[1])); // Freqs
	m63 = *(mButtons.end()-1);
	mGUI->SetSliderCallback(*(mButtons.end()-1), cb63);
	mGUI->SetSliderVal(*(mButtons.end()-1), 0);
	y += 15;

	mButtons.push_back(mGUI->NewSlider(x+60,y,120, print[0], print[1])); // Freqs
	m125 = *(mButtons.end()-1);
	mGUI->SetSliderCallback(*(mButtons.end()-1), cb125);
	mGUI->SetSliderVal(*(mButtons.end()-1), 0);
	y += 15;

	mButtons.push_back(mGUI->NewSlider(x+60,y,120, print[0], print[1])); // Freqs
	m250 = *(mButtons.end()-1);
	mGUI->SetSliderCallback(*(mButtons.end()-1), cb250);
	mGUI->SetSliderVal(*(mButtons.end()-1), 0);
	y += 15;

	mButtons.push_back(mGUI->NewSlider(x+60,y,120, print[0], print[1])); // Freqs
	m500 = *(mButtons.end()-1);
	mGUI->SetSliderCallback(*(mButtons.end()-1), cb500);
	mGUI->SetSliderVal(*(mButtons.end()-1), 0);
	y += 15;

	mButtons.push_back(mGUI->NewSlider(x+60,y,120, print[0], print[1])); // Freqs
	m1K = *(mButtons.end()-1);
	mGUI->SetSliderCallback(*(mButtons.end()-1), cb1K);
	mGUI->SetSliderVal(*(mButtons.end()-1), 0);
	y += 15;

	mButtons.push_back(mGUI->NewSlider(x+60,y,120, print[0], print[1])); // Freqs
	m2K = *(mButtons.end()-1);
	mGUI->SetSliderCallback(*(mButtons.end()-1), cb2K);
	mGUI->SetSliderVal(*(mButtons.end()-1), 0);
	y += 15;

	mButtons.push_back(mGUI->NewSlider(x+60,y,120, print[0], print[1])); // Freqs
	m4K = *(mButtons.end()-1);
	mGUI->SetSliderCallback(*(mButtons.end()-1), cb4K);
	mGUI->SetSliderVal(*(mButtons.end()-1), 0);
	y += 15;

	mButtons.push_back(mGUI->NewSlider(x+60,y,120, print[0], print[1])); // Freqs
	m8K = *(mButtons.end()-1);
	mGUI->SetSliderCallback(*(mButtons.end()-1), cb8K);
	mGUI->SetSliderVal(*(mButtons.end()-1), 0);
	y += 15;

	mButtons.push_back(mGUI->NewSlider(x+60,y,120, print[0], print[1])); // Freqs
	m16K = *(mButtons.end()-1);
	mGUI->SetSliderCallback(*(mButtons.end()-1), cb16K);
	mGUI->SetSliderVal(*(mButtons.end()-1), 0);
	y += 15;

}


GainCallback::GainCallback(LinealEQ *a): mPanel(a), SliderCallback()
{
}
void GainCallback::SetVal(int val)
{
	int newval = mPanel->PrintToReal(val);
	mPanel->mPlug->mEffEQ1->changepar(0, newval); // Gain
}

QCallback::QCallback(LinealEQ *a): mPanel(a), SliderCallback()
{
}
void QCallback::SetVal(int val)
{
	int newval = mPanel->PrintToReal(val);
    for (int i = 0; i <= 45; i += 5) {
		mPanel->mPlug->mEffEQ1->changepar(i+13, newval); // Q
    }
}


F31Callback::F31Callback(LinealEQ *a): mPanel(a), SliderCallback()
{
}
void F31Callback::SetVal(int val)
{
	int newval = mPanel->PrintToReal(val);
	mPanel->mPlug->mEffEQ1->changepar(0*5+12, newval); // Gain
}

F63Callback::F63Callback(LinealEQ *a): mPanel(a), SliderCallback()
{
}
void F63Callback::SetVal(int val)
{
	int newval = mPanel->PrintToReal(val);
	mPanel->mPlug->mEffEQ1->changepar(1*5+12, newval); // Gain
}

F125Callback::F125Callback(LinealEQ *a): mPanel(a), SliderCallback()
{
}
void F125Callback::SetVal(int val)
{
	int newval = mPanel->PrintToReal(val);
	mPanel->mPlug->mEffEQ1->changepar(2*5+12, newval); // Gain
}

F250Callback::F250Callback(LinealEQ *a): mPanel(a), SliderCallback()
{
}
void F250Callback::SetVal(int val)
{
	int newval = mPanel->PrintToReal(val);
	mPanel->mPlug->mEffEQ1->changepar(3*5+12, newval); // Gain
}

F500Callback::F500Callback(LinealEQ *a): mPanel(a), SliderCallback()
{
}
void F500Callback::SetVal(int val)
{
	int newval = mPanel->PrintToReal(val);
	mPanel->mPlug->mEffEQ1->changepar(4*5+12, newval); // Gain
}

F1KCallback::F1KCallback(LinealEQ *a): mPanel(a), SliderCallback()
{
}
void F1KCallback::SetVal(int val)
{
	int newval = mPanel->PrintToReal(val);
	mPanel->mPlug->mEffEQ1->changepar(5*5+12, newval); // Gain
}

F2KCallback::F2KCallback(LinealEQ *a): mPanel(a), SliderCallback()
{
}
void F2KCallback::SetVal(int val)
{
	int newval = mPanel->PrintToReal(val);
	mPanel->mPlug->mEffEQ1->changepar(6*5+12, newval); // Gain
}

F4KCallback::F4KCallback(LinealEQ *a): mPanel(a), SliderCallback()
{
}
void F4KCallback::SetVal(int val)
{
	int newval = mPanel->PrintToReal(val);
	mPanel->mPlug->mEffEQ1->changepar(7*5+12, newval); // Gain
}

F8KCallback::F8KCallback(LinealEQ *a): mPanel(a), SliderCallback()
{
}
void F8KCallback::SetVal(int val)
{
	int newval = mPanel->PrintToReal(val);
	mPanel->mPlug->mEffEQ1->changepar(8*5+12, newval); // Gain
}

F16KCallback::F16KCallback(LinealEQ *a): mPanel(a), SliderCallback()
{
}
void F16KCallback::SetVal(int val)
{
	int newval = mPanel->PrintToReal(val);
	mPanel->mPlug->mEffEQ1->changepar(9*5+12, newval); // Gain
}




};