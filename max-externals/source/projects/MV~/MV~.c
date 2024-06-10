#include "ext.h" // should always be first, followed by ext_obex.h and any other files.
#include "ext_obex.h"
#include "z_dsp.h"

#include "MV~.h"

static t_class *s_MV_class; // global pointer to our class definition that is setup in ext_main()

void ext_main(void *r)
{
    t_class *c;
    c = class_new("MV~", (method)MV_new, (method)dsp_free, sizeof(t_MV), NULL, 0);

    class_addmethod(c, (method)MV_dsp64, "dsp64", A_CANT, 0);
    class_addmethod(c, (method)MV_assist, "assist", A_CANT, 0);
    class_addmethod(c, (method)MV_ft1, "ft1", A_FLOAT, 0);
    class_addmethod(c, (method)MV_ft2, "ft2", A_FLOAT, 0);
    class_addmethod(c, (method)MV_ft3, "ft3", A_FLOAT, 0);
    class_addmethod(c, (method)MV_ft4, "ft4", A_FLOAT, 0);
    class_addmethod(c, (method)MV_ft5, "ft5", A_FLOAT, 0);
    // class_addmethod(c, (method)MV_int, "int", A_LONG, 0);
    // class_addmethod(c, (method)MV_bang, "bang", 0);

    class_dspinit(c);
    class_register(CLASS_BOX, c);
    s_MV_class = c;
}

void MV_assist(t_MV *x, void *b, long m, long a, char *s)
{
    if (m == ASSIST_INLET) { //inlet
        switch (a) {
            case 0: sprintf(s, "(signal) Audio signal input"); break;
            case 1: sprintf(s, "(float) Depth (0.0-1.0)"); break;
            case 2: sprintf(s, "(float) Bright (0.0-1.0)"); break;
            case 3: sprintf(s, "(float) Regen (0.0-1.0)"); break;
            case 4: sprintf(s, "(float) Output (0.0-1.0)"); break;
            case 5: sprintf(s, "(float) Dry/Wet (0.0-1.0)"); break;
            default: break;
        }
    }
    else {    // outlet
        sprintf(s, "(signal) MV audio signal output");
    }
}

// These extra inlets are specified right-to-left, hence the reversed parameter ordering.
void MV_ft1(t_MV *x, double f) { x->E = f; } //post("***Debug: Dry/Wet = %f", f); }
void MV_ft2(t_MV *x, double f) { x->D = f; } //post("***Debug: Output = %f", f); }
void MV_ft3(t_MV *x, double f) { x->C = f; } //post("***Debug: Regen = %f", f); }
void MV_ft4(t_MV *x, double f) { x->B = f; } //post("***Debug: Bright = %f", f); }
void MV_ft5(t_MV *x, double f) { x->A = f; } //post("***Debug: Depth = %f", f); }

void *MV_new(t_symbol *s, long argc, t_atom *argv)
{
    t_MV *x = (t_MV *)object_alloc(s_MV_class);  // initialize the object
    dsp_setup((t_pxobject *)x, 1);               // initialize DSP for object with 1 inlet
    outlet_new((t_object *)x, "signal");         // set up one signal outlet
    floatin(x, 1);  // initialize Depth float inlet
    floatin(x, 2);  // Bright
    floatin(x, 3);  // Regen
    floatin(x, 4);  // Output
    floatin(x, 5);  // Dry/Wet

    x->A = 0.5;  // Depth
    x->B = 0.5;  // Bright
    x->C = 0.5;  // Regen
    x->D = 1.0;  // Output
    x->E = 1.0;  // Dry/Wet

    int count;
    for(count = 0; count < 15149; count++) {x->aA[count] = 0.0;}
    for(count = 0; count < 14617; count++) {x->aB[count] = 0.0;}
    for(count = 0; count < 14357; count++) {x->aC[count] = 0.0;}
    for(count = 0; count < 13817; count++) {x->aD[count] = 0.0;}
    for(count = 0; count < 13561; count++) {x->aE[count] = 0.0;}
    for(count = 0; count < 13045; count++) {x->aF[count] = 0.0;}
    for(count = 0; count < 11965; count++) {x->aG[count] = 0.0;}
    for(count = 0; count < 11129; count++) {x->aH[count] = 0.0;}
    for(count = 0; count < 10597; count++) {x->aI[count] = 0.0;}
    for(count = 0; count < 9809; count++) {x->aJ[count] = 0.0;}
    for(count = 0; count < 9521; count++) {x->aK[count] = 0.0;}
    for(count = 0; count < 8981; count++) {x->aL[count] = 0.0;}
    for(count = 0; count < 8785; count++) {x->aM[count] = 0.0;}
    for(count = 0; count < 8461; count++) {x->aN[count] = 0.0;}
    for(count = 0; count < 8309; count++) {x->aO[count] = 0.0;}
    for(count = 0; count < 7981; count++) {x->aP[count] = 0.0;}
    for(count = 0; count < 7321; count++) {x->aQ[count] = 0.0;}
    for(count = 0; count < 6817; count++) {x->aR[count] = 0.0;}
    for(count = 0; count < 6505; count++) {x->aS[count] = 0.0;}
    for(count = 0; count < 6001; count++) {x->aT[count] = 0.0;}
    for(count = 0; count < 5837; count++) {x->aU[count] = 0.0;}
    for(count = 0; count < 5501; count++) {x->aV[count] = 0.0;}
    for(count = 0; count < 5009; count++) {x->aW[count] = 0.0;}
    for(count = 0; count < 4849; count++) {x->aX[count] = 0.0;}
    for(count = 0; count < 4295; count++) {x->aY[count] = 0.0;}
    for(count = 0; count < 4179; count++) {x->aZ[count] = 0.0;}

    x->alpA = 1; x->delayA = 7573; x->avgA = 0.0;
    x->alpB = 1; x->delayB = 7307; x->avgB = 0.0;
    x->alpC = 1; x->delayC = 7177; x->avgC = 0.0;
    x->alpD = 1; x->delayD = 6907; x->avgD = 0.0;
    x->alpE = 1; x->delayE = 6779; x->avgE = 0.0;
    x->alpF = 1; x->delayF = 6521; x->avgF = 0.0;
    x->alpG = 1; x->delayG = 5981; x->avgG = 0.0;
    x->alpH = 1; x->delayH = 5563; x->avgH = 0.0;
    x->alpI = 1; x->delayI = 5297; x->avgI = 0.0;
    x->alpJ = 1; x->delayJ = 4903; x->avgJ = 0.0;
    x->alpK = 1; x->delayK = 4759; x->avgK = 0.0;
    x->alpL = 1; x->delayL = 4489; x->avgL = 0.0;
    x->alpM = 1; x->delayM = 4391; x->avgM = 0.0;
    x->alpN = 1; x->delayN = 4229; x->avgN = 0.0;
    x->alpO = 1; x->delayO = 4153; x->avgO = 0.0;
    x->alpP = 1; x->delayP = 3989; x->avgP = 0.0;
    x->alpQ = 1; x->delayQ = 3659; x->avgQ = 0.0;
    x->alpR = 1; x->delayR = 3407; x->avgR = 0.0;
    x->alpS = 1; x->delayS = 3251; x->avgS = 0.0;
    x->alpT = 1; x->delayT = 2999; x->avgT = 0.0;
    x->alpU = 1; x->delayU = 2917; x->avgU = 0.0;
    x->alpV = 1; x->delayV = 2749; x->avgV = 0.0;
    x->alpW = 1; x->delayW = 2503; x->avgW = 0.0;
    x->alpX = 1; x->delayX = 2423; x->avgX = 0.0;
    x->alpY = 1; x->delayY = 2146; x->avgY = 0.0;
    x->alpZ = 1; x->delayZ = 2088; x->avgZ = 0.0;

    x->feedback = 0.0;

    x->fpd = 17;
    
    //post("*** DEBUG: initialized Airwindows MV~ object");

    return x;
}

void MV_dsp64(t_MV *x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags)
{
    // instead of calling dsp_add(), we send the "dsp_add64" message to the object representing the dsp chain
    // the arguments passed are:
    // 1: the dsp64 object passed-in by the calling function
    // 2: the symbol of the "dsp_add64" message we are sending
    // 3: a pointer to your object
    // 4: a pointer to your 64-bit perform method
    // 5: flags to alter how the signal chain handles your object -- just pass 0
    // 6: a generic pointer that you can use to pass any additional data to your perform method

    object_method(dsp64, gensym("dsp_add64"), x, MV_perform64, 0, NULL);
}

void MV_perform64(t_MV *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam)
{
    double    *in = ins[0];     // first inlet
    double    *out = outs[0];   // first outlet
    // int       n = sampleframes; // vector size

    long nSampleFrames = sampleframes;

    int allpasstemp;
    double avgtemp;
    int stage = x->A * 27.0;
    int damp = (1.0 - x->B) * stage;
    double feedbacklevel = x->C;
    if (feedbacklevel <= 0.0625) feedbacklevel = 0.0;
    if (feedbacklevel > 0.0625 && feedbacklevel <= 0.125) feedbacklevel = 0.0625; //-24db
    if (feedbacklevel > 0.125 && feedbacklevel <= 0.25) feedbacklevel = 0.125; //-18db
    if (feedbacklevel > 0.25 && feedbacklevel <= 0.5) feedbacklevel = 0.25; //-12db
    if (feedbacklevel > 0.5 && feedbacklevel <= 0.99) feedbacklevel = 0.5; //-6db
    if (feedbacklevel > 0.99) feedbacklevel = 1.0;
    //we're forcing even the feedback level to be Midiverb-ized
    double gain = x->D;
    double wet = x->E;

    while (nSampleFrames-- > 0) {
        long double inputSample = *in;
        //double inputSample = *in++;

        static int noisesource = 0;
        int residue;
        double applyresidue;
        noisesource = noisesource % 1700021; noisesource++;
        residue = noisesource * noisesource;
        residue = residue % 170003; residue *= residue;
        residue = residue % 17011; residue *= residue;
        residue = residue % 1709; residue *= residue;
        residue = residue % 173; residue *= residue;
        residue = residue % 17;
        applyresidue = residue;
        applyresidue *= 0.00000001;
        applyresidue *= 0.00000001;
        inputSample += applyresidue;
        if (inputSample<1.2e-38 && -inputSample<1.2e-38) {
            inputSample -= applyresidue;
        }
        //for live air, we always apply the dither noise. Then, if our result is
        //effectively digital black, we'll subtract it again. We want a 'air' hiss
        double drySample = inputSample;

        inputSample += x->feedback;

        inputSample = sinl(inputSample);


        switch (stage){
            case 27:
            case 26:
                allpasstemp = x->alpA - 1;
                if (allpasstemp < 0 || allpasstemp > x->delayA) {allpasstemp = x->delayA;}
                inputSample -= x->aA[allpasstemp]*0.5;
                x->aA[x->alpA] = inputSample;
                inputSample *= 0.5;
                x->alpA--; if (x->alpA < 0 || x->alpA > x->delayA) {x->alpA = x->delayA;}
                inputSample += (x->aA[x->alpA]);
                if (damp > 26) {
                    avgtemp = inputSample;
                    inputSample += x->avgA;
                    inputSample *= 0.5;
                    x->avgA = avgtemp;
                }
                //allpass filter A
            case 25:
                allpasstemp = x->alpB - 1;
                if (allpasstemp < 0 || allpasstemp > x->delayB) {allpasstemp = x->delayB;}
                inputSample -= x->aB[allpasstemp]*0.5;
                x->aB[x->alpB] = inputSample;
                inputSample *= 0.5;
                x->alpB--; if (x->alpB < 0 || x->alpB > x->delayB) {x->alpB = x->delayB;}
                inputSample += (x->aB[x->alpB]);
                if (damp > 25) {
                    avgtemp = inputSample;
                    inputSample += x->avgB;
                    inputSample *= 0.5;
                    x->avgB = avgtemp;
                }
                //allpass filter B
            case 24:
                allpasstemp = x->alpC - 1;
                if (allpasstemp < 0 || allpasstemp > x->delayC) {allpasstemp = x->delayC;}
                inputSample -= x->aC[allpasstemp]*0.5;
                x->aC[x->alpC] = inputSample;
                inputSample *= 0.5;
                x->alpC--; if (x->alpC < 0 || x->alpC > x->delayC) {x->alpC = x->delayC;}
                inputSample += (x->aC[x->alpC]);
                if (damp > 24) {
                    avgtemp = inputSample;
                    inputSample += x->avgC;
                    inputSample *= 0.5;
                    x->avgC = avgtemp;
                }
                //allpass filter C
            case 23:
                allpasstemp = x->alpD - 1;
                if (allpasstemp < 0 || allpasstemp > x->delayD) {allpasstemp = x->delayD;}
                inputSample -= x->aD[allpasstemp]*0.5;
                x->aD[x->alpD] = inputSample;
                inputSample *= 0.5;
                x->alpD--; if (x->alpD < 0 || x->alpD > x->delayD) {x->alpD = x->delayD;}
                inputSample += (x->aD[x->alpD]);
                if (damp > 23) {
                    avgtemp = inputSample;
                    inputSample += x->avgD;
                    inputSample *= 0.5;
                    x->avgD = avgtemp;
                }
                //allpass filter D
            case 22:
                allpasstemp = x->alpE - 1;
                if (allpasstemp < 0 || allpasstemp > x->delayE) {allpasstemp = x->delayE;}
                inputSample -= x->aE[allpasstemp]*0.5;
                x->aE[x->alpE] = inputSample;
                inputSample *= 0.5;
                x->alpE--; if (x->alpE < 0 || x->alpE > x->delayE) {x->alpE = x->delayE;}
                inputSample += (x->aE[x->alpE]);
                if (damp > 22) {
                    avgtemp = inputSample;
                    inputSample += x->avgE;
                    inputSample *= 0.5;
                    x->avgE = avgtemp;
                }
                //allpass filter E
            case 21:
                allpasstemp = x->alpF - 1;
                if (allpasstemp < 0 || allpasstemp > x->delayF) {allpasstemp = x->delayF;}
                inputSample -= x->aF[allpasstemp]*0.5;
                x->aF[x->alpF] = inputSample;
                inputSample *= 0.5;
                x->alpF--; if (x->alpF < 0 || x->alpF > x->delayF) {x->alpF = x->delayF;}
                inputSample += (x->aF[x->alpF]);
                if (damp > 21) {
                    avgtemp = inputSample;
                    inputSample += x->avgF;
                    inputSample *= 0.5;
                    x->avgF = avgtemp;
                }
                //allpass filter F
            case 20:
                allpasstemp = x->alpG - 1;
                if (allpasstemp < 0 || allpasstemp > x->delayG) {allpasstemp = x->delayG;}
                inputSample -= x->aG[allpasstemp]*0.5;
                x->aG[x->alpG] = inputSample;
                inputSample *= 0.5;
                x->alpG--; if (x->alpG < 0 || x->alpG > x->delayG) {x->alpG = x->delayG;}
                inputSample += (x->aG[x->alpG]);
                if (damp > 20) {
                    avgtemp = inputSample;
                    inputSample += x->avgG;
                    inputSample *= 0.5;
                    x->avgG = avgtemp;
                }
                //allpass filter G
            case 19:
                allpasstemp = x->alpH - 1;
                if (allpasstemp < 0 || allpasstemp > x->delayH) {allpasstemp = x->delayH;}
                inputSample -= x->aH[allpasstemp]*0.5;
                x->aH[x->alpH] = inputSample;
                inputSample *= 0.5;
                x->alpH--; if (x->alpH < 0 || x->alpH > x->delayH) {x->alpH = x->delayH;}
                inputSample += (x->aH[x->alpH]);
                if (damp > 19) {
                    avgtemp = inputSample;
                    inputSample += x->avgH;
                    inputSample *= 0.5;
                    x->avgH = avgtemp;
                }
                //allpass filter H
            case 18:
                allpasstemp = x->alpI - 1;
                if (allpasstemp < 0 || allpasstemp > x->delayI) {allpasstemp = x->delayI;}
                inputSample -= x->aI[allpasstemp]*0.5;
                x->aI[x->alpI] = inputSample;
                inputSample *= 0.5;
                x->alpI--; if (x->alpI < 0 || x->alpI > x->delayI) {x->alpI = x->delayI;}
                inputSample += (x->aI[x->alpI]);
                if (damp > 18) {
                    avgtemp = inputSample;
                    inputSample += x->avgI;
                    inputSample *= 0.5;
                    x->avgI = avgtemp;
                }
                //allpass filter I
            case 17:
                allpasstemp = x->alpJ - 1;
                if (allpasstemp < 0 || allpasstemp > x->delayJ) {allpasstemp = x->delayJ;}
                inputSample -= x->aJ[allpasstemp]*0.5;
                x->aJ[x->alpJ] = inputSample;
                inputSample *= 0.5;
                x->alpJ--; if (x->alpJ < 0 || x->alpJ > x->delayJ) {x->alpJ = x->delayJ;}
                inputSample += (x->aJ[x->alpJ]);
                if (damp > 17) {
                    avgtemp = inputSample;
                    inputSample += x->avgJ;
                    inputSample *= 0.5;
                    x->avgJ = avgtemp;
                }
                //allpass filter J
            case 16:
                allpasstemp = x->alpK - 1;
                if (allpasstemp < 0 || allpasstemp > x->delayK) {allpasstemp = x->delayK;}
                inputSample -= x->aK[allpasstemp]*0.5;
                x->aK[x->alpK] = inputSample;
                inputSample *= 0.5;
                x->alpK--; if (x->alpK < 0 || x->alpK > x->delayK) {x->alpK = x->delayK;}
                inputSample += (x->aK[x->alpK]);
                if (damp > 16) {
                    avgtemp = inputSample;
                    inputSample += x->avgK;
                    inputSample *= 0.5;
                    x->avgK = avgtemp;
                }
                //allpass filter K
            case 15:
                allpasstemp = x->alpL - 1;
                if (allpasstemp < 0 || allpasstemp > x->delayL) {allpasstemp = x->delayL;}
                inputSample -= x->aL[allpasstemp]*0.5;
                x->aL[x->alpL] = inputSample;
                inputSample *= 0.5;
                x->alpL--; if (x->alpL < 0 || x->alpL > x->delayL) {x->alpL = x->delayL;}
                inputSample += (x->aL[x->alpL]);
                if (damp > 15) {
                    avgtemp = inputSample;
                    inputSample += x->avgL;
                    inputSample *= 0.5;
                    x->avgL = avgtemp;
                }
                //allpass filter L
            case 14:
                allpasstemp = x->alpM - 1;
                if (allpasstemp < 0 || allpasstemp > x->delayM) {allpasstemp = x->delayM;}
                inputSample -= x->aM[allpasstemp]*0.5;
                x->aM[x->alpM] = inputSample;
                inputSample *= 0.5;
                x->alpM--; if (x->alpM < 0 || x->alpM > x->delayM) {x->alpM = x->delayM;}
                inputSample += (x->aM[x->alpM]);
                if (damp > 14) {
                    avgtemp = inputSample;
                    inputSample += x->avgM;
                    inputSample *= 0.5;
                    x->avgM = avgtemp;
                }
                //allpass filter M
            case 13:
                allpasstemp = x->alpN - 1;
                if (allpasstemp < 0 || allpasstemp > x->delayN) {allpasstemp = x->delayN;}
                inputSample -= x->aN[allpasstemp]*0.5;
                x->aN[x->alpN] = inputSample;
                inputSample *= 0.5;
                x->alpN--; if (x->alpN < 0 || x->alpN > x->delayN) {x->alpN = x->delayN;}
                inputSample += (x->aN[x->alpN]);
                if (damp > 13) {
                    avgtemp = inputSample;
                    inputSample += x->avgN;
                    inputSample *= 0.5;
                    x->avgN = avgtemp;
                }
                //allpass filter N
            case 12:
                allpasstemp = x->alpO - 1;
                if (allpasstemp < 0 || allpasstemp > x->delayO) {allpasstemp = x->delayO;}
                inputSample -= x->aO[allpasstemp]*0.5;
                x->aO[x->alpO] = inputSample;
                inputSample *= 0.5;
                x->alpO--; if (x->alpO < 0 || x->alpO > x->delayO) {x->alpO = x->delayO;}
                inputSample += (x->aO[x->alpO]);
                if (damp > 12) {
                    avgtemp = inputSample;
                    inputSample += x->avgO;
                    inputSample *= 0.5;
                    x->avgO = avgtemp;
                }
                //allpass filter O
            case 11:
                allpasstemp = x->alpP - 1;
                if (allpasstemp < 0 || allpasstemp > x->delayP) {allpasstemp = x->delayP;}
                inputSample -= x->aP[allpasstemp]*0.5;
                x->aP[x->alpP] = inputSample;
                inputSample *= 0.5;
                x->alpP--; if (x->alpP < 0 || x->alpP > x->delayP) {x->alpP = x->delayP;}
                inputSample += (x->aP[x->alpP]);
                if (damp > 11) {
                    avgtemp = inputSample;
                    inputSample += x->avgP;
                    inputSample *= 0.5;
                    x->avgP = avgtemp;
                }
                //allpass filter P
            case 10:
                allpasstemp = x->alpQ - 1;
                if (allpasstemp < 0 || allpasstemp > x->delayQ) {allpasstemp = x->delayQ;}
                inputSample -= x->aQ[allpasstemp]*0.5;
                x->aQ[x->alpQ] = inputSample;
                inputSample *= 0.5;
                x->alpQ--; if (x->alpQ < 0 || x->alpQ > x->delayQ) {x->alpQ = x->delayQ;}
                inputSample += (x->aQ[x->alpQ]);
                if (damp > 10) {
                    avgtemp = inputSample;
                    inputSample += x->avgQ;
                    inputSample *= 0.5;
                    x->avgQ = avgtemp;
                }
                //allpass filter Q
            case 9:
                allpasstemp = x->alpR - 1;
                if (allpasstemp < 0 || allpasstemp > x->delayR) {allpasstemp = x->delayR;}
                inputSample -= x->aR[allpasstemp]*0.5;
                x->aR[x->alpR] = inputSample;
                inputSample *= 0.5;
                x->alpR--; if (x->alpR < 0 || x->alpR > x->delayR) {x->alpR = x->delayR;}
                inputSample += (x->aR[x->alpR]);
                if (damp > 9) {
                    avgtemp = inputSample;
                    inputSample += x->avgR;
                    inputSample *= 0.5;
                    x->avgR = avgtemp;
                }
                //allpass filter R
            case 8:
                allpasstemp = x->alpS - 1;
                if (allpasstemp < 0 || allpasstemp > x->delayS) {allpasstemp = x->delayS;}
                inputSample -= x->aS[allpasstemp]*0.5;
                x->aS[x->alpS] = inputSample;
                inputSample *= 0.5;
                x->alpS--; if (x->alpS < 0 || x->alpS > x->delayS) {x->alpS = x->delayS;}
                inputSample += (x->aS[x->alpS]);
                if (damp > 8) {
                    avgtemp = inputSample;
                    inputSample += x->avgS;
                    inputSample *= 0.5;
                    x->avgS = avgtemp;
                }
                //allpass filter S
            case 7:
                allpasstemp = x->alpT - 1;
                if (allpasstemp < 0 || allpasstemp > x->delayT) {allpasstemp = x->delayT;}
                inputSample -= x->aT[allpasstemp]*0.5;
                x->aT[x->alpT] = inputSample;
                inputSample *= 0.5;
                x->alpT--; if (x->alpT < 0 || x->alpT > x->delayT) {x->alpT = x->delayT;}
                inputSample += (x->aT[x->alpT]);
                if (damp > 7) {
                    avgtemp = inputSample;
                    inputSample += x->avgT;
                    inputSample *= 0.5;
                    x->avgT = avgtemp;
                }
                //allpass filter T
            case 6:
                allpasstemp = x->alpU - 1;
                if (allpasstemp < 0 || allpasstemp > x->delayU) {allpasstemp = x->delayU;}
                inputSample -= x->aU[allpasstemp]*0.5;
                x->aU[x->alpU] = inputSample;
                inputSample *= 0.5;
                x->alpU--; if (x->alpU < 0 || x->alpU > x->delayU) {x->alpU = x->delayU;}
                inputSample += (x->aU[x->alpU]);
                if (damp > 6) {
                    avgtemp = inputSample;
                    inputSample += x->avgU;
                    inputSample *= 0.5;
                    x->avgU = avgtemp;
                }
                //allpass filter U
            case 5:
                allpasstemp = x->alpV - 1;
                if (allpasstemp < 0 || allpasstemp > x->delayV) {allpasstemp = x->delayV;}
                inputSample -= x->aV[allpasstemp]*0.5;
                x->aV[x->alpV] = inputSample;
                inputSample *= 0.5;
                x->alpV--; if (x->alpV < 0 || x->alpV > x->delayV) {x->alpV = x->delayV;}
                inputSample += (x->aV[x->alpV]);
                if (damp > 5) {
                    avgtemp = inputSample;
                    inputSample += x->avgV;
                    inputSample *= 0.5;
                    x->avgV = avgtemp;
                }
                //allpass filter V
            case 4:
                allpasstemp = x->alpW - 1;
                if (allpasstemp < 0 || allpasstemp > x->delayW) {allpasstemp = x->delayW;}
                inputSample -= x->aW[allpasstemp]*0.5;
                x->aW[x->alpW] = inputSample;
                inputSample *= 0.5;
                x->alpW--; if (x->alpW < 0 || x->alpW > x->delayW) {x->alpW = x->delayW;}
                inputSample += (x->aW[x->alpW]);
                if (damp > 4) {
                    avgtemp = inputSample;
                    inputSample += x->avgW;
                    inputSample *= 0.5;
                    x->avgW = avgtemp;
                }
                //allpass filter W
            case 3:
                allpasstemp = x->alpX - 1;
                if (allpasstemp < 0 || allpasstemp > x->delayX) {allpasstemp = x->delayX;}
                inputSample -= x->aX[allpasstemp]*0.5;
                x->aX[x->alpX] = inputSample;
                inputSample *= 0.5;
                x->alpX--; if (x->alpX < 0 || x->alpX > x->delayX) {x->alpX = x->delayX;}
                inputSample += (x->aX[x->alpX]);
                if (damp > 3) {
                    avgtemp = inputSample;
                    inputSample += x->avgX;
                    inputSample *= 0.5;
                    x->avgX = avgtemp;
                }
                //allpass filter X
            case 2:
                allpasstemp = x->alpY - 1;
                if (allpasstemp < 0 || allpasstemp > x->delayY) {allpasstemp = x->delayY;}
                inputSample -= x->aY[allpasstemp]*0.5;
                x->aY[x->alpY] = inputSample;
                inputSample *= 0.5;
                x->alpY--; if (x->alpY < 0 || x->alpY > x->delayY) {x->alpY = x->delayY;}
                inputSample += (x->aY[x->alpY]);
                if (damp > 2) {
                    avgtemp = inputSample;
                    inputSample += x->avgY;
                    inputSample *= 0.5;
                    x->avgY = avgtemp;
                }
                //allpass filter Y
            case 1:
                allpasstemp = x->alpZ - 1;
                if (allpasstemp < 0 || allpasstemp > x->delayZ) {allpasstemp = x->delayZ;}
                inputSample -= x->aZ[allpasstemp]*0.5;
                x->aZ[x->alpZ] = inputSample;
                inputSample *= 0.5;
                x->alpZ--; if (x->alpZ < 0 || x->alpZ > x->delayZ) {x->alpZ = x->delayZ;}
                inputSample += (x->aZ[x->alpZ]);
                if (damp > 1) {
                    avgtemp = inputSample;
                    inputSample += x->avgZ;
                    inputSample *= 0.5;
                    x->avgZ = avgtemp;
                }
                //allpass filter Z
        }

        x->feedback = inputSample * feedbacklevel;

        if (gain != 1.0) {
            inputSample *= gain;
        }
        //we can pad with the gain to tame distortyness from the PurestConsole code

        if (inputSample > 1.0) inputSample = 1.0;
        if (inputSample < -1.0) inputSample = -1.0;
        //without this, you can get a NaN condition where it spits out DC offset at full blast!

        inputSample = asinl(inputSample);


        if (wet != 1.0) {
            inputSample = (inputSample * wet) + (drySample * (1.0-wet));
        }
        //Dry/Wet control, defaults to the last slider

        //begin 64 bit floating point dither
        int expon; frexp((double)inputSample, &expon);
        x->fpd ^= x->fpd << 13; x->fpd ^= x->fpd >> 17; x->fpd ^= x->fpd << 5;
        inputSample += ((int32_t)(x->fpd)) * 1.110223024625156e-44L * pow(2,expon+62);
        //end 64 bit floating point dither

        *out++ = inputSample;
    }
}
