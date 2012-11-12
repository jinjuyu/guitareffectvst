#include "paramsMinMax.h"

DistorsionTypeCallback::	DistorsionTypeCallback(DistorsionPanel *a)
	:mPanel(a), ButtonCallback()
{
}
void DistorsionTypeCallback::OnClick()
{
}

DistorsionNegCallback::	DistorsionNegCallback(DistorsionPanel *a)
	:mPanel(a), OnOffButtonCallback()
{
}
void DistorsionNegCallback::OnClick()
{
}


LPFCallBack::LPFCallBack(DistorsionPanel *a):SliderCallback() ,mPanel(a)
{
}
void LPFCallBack::SetVal(int val)
{
}
