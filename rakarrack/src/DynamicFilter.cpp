/*
  ZynAddSubFX - a software synthesizer

  DynamicFilter.C - "WahWah" effect and others
  Copyright (C) 2002-2005 Nasca Octavian Paul
  Author: Nasca Octavian Paul

  Modified for rakarrack by Josep Andreu

  This program is free software; you can redistribute it and/or modify
  it under the terms of version 2 of the GNU General Public License
  as published by the Free Software Foundation.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License (version 2) for more details.

  You should have received a copy of the GNU General Public License (version 2)
  along with this program; if not, write to the Free Software Foundation,
  Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA

*/

#include <math.h>
#include "DynamicFilter.h"
#include <stdio.h>

DynamicFilter::DynamicFilter (Parameters *param, float * efxoutl_, float * efxoutr_)
:lfo(param){
	this->param = param;
    efxoutl = efxoutl_;
    efxoutr = efxoutr_;


    Ppreset = 0;
    filterl = NULL;
    filterr = NULL;
    filterpars = new FilterParams (0, 64, 64);
    setpreset (Ppreset);
    cleanup ();
};

DynamicFilter::~DynamicFilter ()
{
};


/*
 * Apply the effect
 */
void
DynamicFilter::out (float * smpsl, float * smpsr)
{
    int i;
    float lfol, lfor;

    if (filterpars->changed) {
        filterpars->changed = false;
        cleanup ();
    };

    lfo.effectlfoout (&lfol, &lfor);
    lfol *= depth * 5.0f;
    lfor *= depth * 5.0f;
    float freq = filterpars->getfreq ();
    float q = filterpars->getq ();

    for (i = 0; i < param->PERIOD; i++) {
        efxoutl[i] = smpsl[i];
        efxoutr[i] = smpsr[i];

        float x = (fabsf (smpsl[i]) + fabsf (smpsr[i])) * 0.5f;
        ms1 = ms1 * (1.0f - ampsmooth) + x * ampsmooth + 1e-10f;
    };


    float ampsmooth2 = powf (ampsmooth, 0.2f) * 0.3f;
    ms2 = ms2 * (1.0f - ampsmooth2) + ms1 * ampsmooth2;
    ms3 = ms3 * (1.0f - ampsmooth2) + ms2 * ampsmooth2;
    ms4 = ms4 * (1.0f - ampsmooth2) + ms3 * ampsmooth2;
    float rms = (sqrtf (ms4)) * ampsns;

    float frl = filterl->getrealfreq (freq + lfol + rms);
    float frr = filterr->getrealfreq (freq + lfor + rms);

    filterl->setfreq_and_q (frl, q);
    filterr->setfreq_and_q (frr, q);


    filterl->filterout (efxoutl);
    filterr->filterout (efxoutr);

    //panning
    for (i = 0; i < param->PERIOD; i++) {
        efxoutl[i] *= panning;
        efxoutr[i] *= (1.0f - panning);
    };

};

/*
 * Cleanup the effect
 */
void
DynamicFilter::cleanup ()
{
    reinitfilter ();
    ms1 = 0.0;
    ms2 = 0.0;
    ms3 = 0.0;
    ms4 = 0.0;
};


/*
 * Parameter control
 */

void
DynamicFilter::setdepth (int Pdepth)
{
    this->Pdepth = Pdepth;
    depth = powf (((float)Pdepth / 127.0f), 2.0f);
};


void
DynamicFilter::setvolume (int Pvolume)
{
    this->Pvolume = Pvolume;
    outvolume = (float)Pvolume / 127.0f;

};

void
DynamicFilter::setpanning (int Ppanning)
{
    this->Ppanning = Ppanning;
    panning = ((float)Ppanning + .5f) / 127.0f;
};


void
DynamicFilter::setampsns (int Pampsns)
{
    ampsns = powf ((float)Pampsns / 127.0f, 2.5f) * 10.0f;
    if (Pampsnsinv != 0)
        ampsns = -ampsns;
    ampsmooth = expf ((float)-Pampsmooth / 127.0f * 10.0f) * 0.99f;
    this->Pampsns = Pampsns;
};

void
DynamicFilter::reinitfilter ()
{
    if (filterl != NULL)
        delete (filterl);
    if (filterr != NULL)
        delete (filterr);
    filterl = new Filter (param,filterpars);
    filterr = new Filter (param,filterpars);
};

void
DynamicFilter::setpreset (int npreset)
{
    const int PRESET_SIZE = 10;
    const int NUM_PRESETS = 5;
    int presets[NUM_PRESETS][PRESET_SIZE] = {
        //WahWah
        {64, 64, 80, 0, 0, 64, 70, 90, 0, 60},
        //AutoWah
        {64, 64, 70, 0, 0, 80, 70, 0, 0, 60},
        //Sweep
        {64, 64, 30, 0, 0, 50, 80, 0, 0, 60},
        //VocalMorph1
        {64, 64, 80, 0, 0, 64, 70, 64, 0, 60},
        //VocalMorph1
        {64, 64, 50, 0, 0, 96, 64, 0, 0, 60}
    };

    if(npreset>NUM_PRESETS-1) {

        Fpre->ReadPreset(10,npreset-NUM_PRESETS+1);
        for (int n = 0; n < PRESET_SIZE; n++)
            changepar (n, pdata[n]);
    } else {

        for (int n = 0; n < PRESET_SIZE; n++)
            changepar (n, presets[npreset][n]);
    }

    filterpars->defaults ();
    switch (npreset) {
    case 0:
        filterpars->Pcategory = 0;
        filterpars->Ptype = 2;
        filterpars->Pfreq = 45;
        filterpars->Pq = 64;
        filterpars->Pstages = 1;
        filterpars->Pgain = 64;
        break;
    case 1:
        filterpars->Pcategory = 2;
        filterpars->Ptype = 0;
        filterpars->Pfreq = 72;
        filterpars->Pq = 64;
        filterpars->Pstages = 0;
        filterpars->Pgain = 64;
        break;
    case 2:
        filterpars->Pcategory = 0;
        filterpars->Ptype = 4;
        filterpars->Pfreq = 64;
        filterpars->Pq = 64;
        filterpars->Pstages = 2;
        filterpars->Pgain = 64;
        break;
    case 3:
        filterpars->Pcategory = 1;
        filterpars->Ptype = 0;
        filterpars->Pfreq = 50;
        filterpars->Pq = 70;
        filterpars->Pstages = 1;
        filterpars->Pgain = 64;

        filterpars->Psequencesize = 2;
        // "I"
        filterpars->Pvowels[0].formants[0].freq = 34;
        filterpars->Pvowels[0].formants[0].amp = 127;
        filterpars->Pvowels[0].formants[0].q = 64;
        filterpars->Pvowels[0].formants[1].freq = 99;
        filterpars->Pvowels[0].formants[1].amp = 122;
        filterpars->Pvowels[0].formants[1].q = 64;
        filterpars->Pvowels[0].formants[2].freq = 108;
        filterpars->Pvowels[0].formants[2].amp = 112;
        filterpars->Pvowels[0].formants[2].q = 64;
        // "A"
        filterpars->Pvowels[1].formants[0].freq = 61;
        filterpars->Pvowels[1].formants[0].amp = 127;
        filterpars->Pvowels[1].formants[0].q = 64;
        filterpars->Pvowels[1].formants[1].freq = 71;
        filterpars->Pvowels[1].formants[1].amp = 121;
        filterpars->Pvowels[1].formants[1].q = 64;
        filterpars->Pvowels[1].formants[2].freq = 99;
        filterpars->Pvowels[1].formants[2].amp = 117;
        filterpars->Pvowels[1].formants[2].q = 64;
        break;
    case 4:
        filterpars->Pcategory = 1;
        filterpars->Ptype = 0;
        filterpars->Pfreq = 64;
        filterpars->Pq = 70;
        filterpars->Pstages = 1;
        filterpars->Pgain = 64;

        filterpars->Psequencesize = 2;
        filterpars->Pnumformants = 2;
        filterpars->Pvowelclearness = 0;

        filterpars->Pvowels[0].formants[0].freq = 70;
        filterpars->Pvowels[0].formants[0].amp = 127;
        filterpars->Pvowels[0].formants[0].q = 64;
        filterpars->Pvowels[0].formants[1].freq = 80;
        filterpars->Pvowels[0].formants[1].amp = 122;
        filterpars->Pvowels[0].formants[1].q = 64;

        filterpars->Pvowels[1].formants[0].freq = 20;
        filterpars->Pvowels[1].formants[0].amp = 127;
        filterpars->Pvowels[1].formants[0].q = 64;
        filterpars->Pvowels[1].formants[1].freq = 100;
        filterpars->Pvowels[1].formants[1].amp = 121;
        filterpars->Pvowels[1].formants[1].q = 64;
        break;
    };

//          for (int i=0;i<5;i++){
//              printf("freq=%d  amp=%d  q=%d\n",filterpars->Pvowels[0].formants[i].freq,filterpars->Pvowels[0].formants[i].amp,filterpars->Pvowels[0].formants[i].q);
//          };

    Ppreset = npreset;

    reinitfilter ();
};


void
DynamicFilter::changepar (int npar, int value)
{
    switch (npar) {
    case 0:
        setvolume (value);
        break;
    case 1:
        setpanning (value);
        break;
    case 2:
        lfo.Pfreq = value;
        lfo.updateparams ();
        break;
    case 3:
        lfo.Prandomness = value;
        lfo.updateparams ();
        break;
    case 4:
        lfo.PLFOtype = value;
        lfo.updateparams ();
        break;
    case 5:
        lfo.Pstereo = value;
        lfo.updateparams ();
        break;
    case 6:
        setdepth (value);
        break;
    case 7:
        setampsns (value);
        break;
    case 8:
        Pampsnsinv = value;
        setampsns (Pampsns);
        break;
    case 9:
        Pampsmooth = value;
        setampsns (Pampsns);
        break;


    };
};

int
DynamicFilter::getpar (int npar)
{
    switch (npar) {
    case 0:
        return (Pvolume);
        break;
    case 1:
        return (Ppanning);
        break;
    case 2:
        return (lfo.Pfreq);
        break;
    case 3:
        return (lfo.Prandomness);
        break;
    case 4:
        return (lfo.PLFOtype);
        break;
    case 5:
        return (lfo.Pstereo);
        break;
    case 6:
        return (Pdepth);
        break;
    case 7:
        return (Pampsns);
        break;
    case 8:
        return (Pampsnsinv);
        break;
    case 9:
        return (Pampsmooth);
        break;
    default:
        return (0);
    };

};
