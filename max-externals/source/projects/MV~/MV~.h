#include "ext.h" // should always be first, followed by ext_obex.h and any other files.
#include "ext_obex.h"
#include "z_dsp.h"

typedef struct _MV
{
    t_pxobject m_obj;

    double A;  // Depth
    double B;  // Bright
    double C;  // Regen
    double D;  // Output
    double E;  // Dry/Wet
    //parameters. Always 0-1, and we scale/alter them elsewhere.

    double aA[15150];
    double aB[14618];
    double aC[14358];
    double aD[13818];
    double aE[13562];
    double aF[13046];
    double aG[11966];
    double aH[11130];
    double aI[10598];
    double aJ[9810];
    double aK[9522];
    double aL[8982];
    double aM[8786];
    double aN[8462];
    double aO[8310];
    double aP[7982];
    double aQ[7322];
    double aR[6818];
    double aS[6506];
    double aT[6002];
    double aU[5838];
    double aV[5502];
    double aW[5010];
    double aX[4850];
    double aY[4296];
    double aZ[4180];

    int alpA, delayA;
    int alpB, delayB;
    int alpC, delayC;
    int alpD, delayD;
    int alpE, delayE;
    int alpF, delayF;
    int alpG, delayG;
    int alpH, delayH;
    int alpI, delayI;
    int alpJ, delayJ;
    int alpK, delayK;
    int alpL, delayL;
    int alpM, delayM;
    int alpN, delayN;
    int alpO, delayO;
    int alpP, delayP;
    int alpQ, delayQ;
    int alpR, delayR;
    int alpS, delayS;
    int alpT, delayT;
    int alpU, delayU;
    int alpV, delayV;
    int alpW, delayW;
    int alpX, delayX;
    int alpY, delayY;
    int alpZ, delayZ;

    double avgA;
    double avgB;
    double avgC;
    double avgD;
    double avgE;
    double avgF;
    double avgG;
    double avgH;
    double avgI;
    double avgJ;
    double avgK;
    double avgL;
    double avgM;
    double avgN;
    double avgO;
    double avgP;
    double avgQ;
    double avgR;
    double avgS;
    double avgT;
    double avgU;
    double avgV;
    double avgW;
    double avgX;
    double avgY;
    double avgZ;

    double feedback;

    uint32_t fpd;
} t_MV;


// method prototypes
void *MV_new(t_symbol *s, long argc, t_atom *argv);
void MV_free(t_MV *x);
void MV_assist(t_MV *x, void *b, long m, long a, char *s);
void MV_float(t_MV *x, double f);
void MV_dsp64(t_MV *x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags);
void MV_perform64(t_MV *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam);
void MV_ft1(t_MV *x, double f);
void MV_ft2(t_MV *x, double f);
void MV_ft3(t_MV *x, double f);
void MV_ft4(t_MV *x, double f);
void MV_ft5(t_MV *x, double f);
