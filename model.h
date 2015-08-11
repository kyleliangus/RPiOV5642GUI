#ifndef MODEL
#define MODEL

#include <math.h>
#include <algorithm>
#include <vector>

// constants for isp
const std::string c00R = "0x5000";
const int c00DV = 0xDF;
const std::string c01R = "0x5001";
const int c01DV = 0x4F;
const std::string c02R = "0x5002";
const int c02DV = 0xE0;
const std::string c03R = "0x5003";
const int c03DV = 0xA8;
const std::string c05R = "0x5005";
const int c05DV = 0xDC;
const std::string hsmR = "0x501C";
const int hsmDV = 0x00;
const std::string rgbdcR = "0x501E";
const int rgbdcDV = 0x40;
const std::string fcR = "0x501F";
const int fcDV = 0x04;

// constants for mainwindow
/*   constants    */

// binning
const std::string vBinR = "0x370D";
const int vBinDV = 0x05;
//const std::string vbinV = ;
const std::string hBinR = "0x3621";
const int hBinDV = 0x10;
//const std::string hbinV = ;

// mirror and flip and compression
const std::string mirrorVFlipR = "0x3818";
const int mirrorVFlipDV = 0x80;
const std::string mirrorAdditionalR1 = "0x3621";
const std::string mirrorAdditionalR2 = "0x3801";
// compression
const std::string compressionR = "0x3818"; // off and on
static const int compressionDV = 0x80;


// night mode
const std::string nightModeR = "0x3A00"; // off and on bit[2]
const int nightModeDV = 0x7C;

// vap
/* unnecessary, found in ISP02
const std::string vapControlR = "0x5002"; // off and on
const std::string vapControlOnR = "0x501C";
const int vapControlOnV = "00000000";
*/

// AEC
const std::string aeclR1 = "0x3500";
const std::string aeclR2 = "0x3501";
const std::string aeclR3 = "0x3502";
const std::string aecAGCVTSControlR = "0x3503";
const std::string vtsR1 = "0x350C";
const std::string vtsR2 = "0x350D";

const int manualAECAGCDV = 0x00;
const int manualVTSR1DV = 0x06;
const int manualVTSR2DV = 0x18;
// AGC
const std::string agclR1 = "0x3508";
const std::string agclR2 = "0x3509";
const std::string agcAECadjR1 = "0x350A";
const std::string agcAECadjR2 = "0x350B";


// given bit number
static int binToDecimal( int numberReceived )
{
    return pow(2,numberReceived);
}

static void createParameter( std::string r , int& v , const int defaultValue , std::vector<Parameter> &vect )
{
    if( v!=defaultValue )
    {
        Parameter p = Parameter(r,v);
        std::vector<Parameter>::iterator index = std::find( vect.begin(), vect.end(), p );

        if( index != vect.end() )
        {
            int x = distance( vect.begin(), index );
            vect[x] = p;
        }
        else
        {
            vect.push_back(p);
        }
        v = 0;
    }

}



#endif // MODEL

