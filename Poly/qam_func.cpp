#include <iterator>
#include <vector>
#include <math.h>

using namespace std;

const double PI = 3.141592653589793238463;
namespace QAM_Synth
{
    void Synth_BPSK(vector <char> inBin, vector <float> &medI, vector <float> &medQ, int inpSize)
    {
        for (int i = 0; i < inpSize; i++)
        {
            if (inBin[i] == 0)
            {
                medI[i] = 1;
                medQ[i] = 1;
            }
            else
            {
                medI[i] = -1;
                medQ[i] = -1;
            }
        }
    }

    void Synth_QPSK(vector <char> inBin, vector <float>& medI, vector <float>& medQ, int inpSize)
    {
        for (int i = 0; i < inpSize; i += 2)
        {
            if (inBin[i] == 0 && inBin[i + 1] == 0)
            {
                medI[i / 2] = 1;
                medQ[i / 2] = 1;
            }
            else if (inBin[i] == 0 && inBin[i + 1] == 1)
            {
                medI[i / 2] = 1;
                medQ[i / 2] = -1;
            }
            else if (inBin[i] == 1 && inBin[i + 1] == 0)
            {
                medI[i / 2] = -1;
                medQ[i / 2] = -1;
            }
            else if (inBin[i] == 1 && inBin[i + 1] == 1)
            {
                medI[i / 2] = -1;
                medQ[i / 2] = 1;
            }
        }
    }

    void Synth_8PSK(vector <char> inBin, vector <float>& medI, vector <float>& medQ, int inpSize)
    {
        for (int i = 0; i < inpSize; i += 3)
        {
            if (inBin[i] == 0 && inBin[i + 1] == 0 && inBin[i + 2] == 0)
            {
                medI[i / 3] = 0.93;
                medQ[i / 3] = 0.38;
            }
            else if (inBin[i] == 0 && inBin[i + 1] == 0 && inBin[i + 2] == 1)
            {
                medI[i / 3] = 0.38;
                medQ[i / 3] = 0.93;
            }
            else if (inBin[i] == 0 && inBin[i + 1] == 1 && inBin[i + 2] == 0)
            {
                medI[i / 3] = -0.38;
                medQ[i / 3] = 0.93;
            }
            else if (inBin[i] == 0 && inBin[i + 1] == 1 && inBin[i + 2] == 1)
            {
                medI[i / 3] = -0.93;
                medQ[i / 3] = 0.38;
            }
            else if (inBin[i] == 1 && inBin[i + 1] == 0 && inBin[i + 2] == 0)
            {
                medI[i / 3] = -0.93;
                medQ[i / 3] = -0.38;
            }
            else if (inBin[i] == 1 && inBin[i + 1] == 0 && inBin[i + 2] == 1)
            {
                medI[i / 3] = -0.38;
                medQ[i / 3] = -0.93;
            }
            else if (inBin[i] == 1 && inBin[i + 1] == 1 && inBin[i + 2] == 0)
            {
                medI[i / 3] = 0.38;
                medQ[i / 3] = -0.93;
            }
            else if (inBin[i] == 1 && inBin[i + 1] == 1 && inBin[i + 2] == 1)
            {
                medI[i / 3] = 0.93;
                medQ[i / 3] = -0.38;
            }
        }
    }

    void Synth_16QAM(vector <char> inBin, vector <float>& medI, vector <float>& medQ, int inpSize)
    {
        for (int i = 0; i < inpSize; i += 4)
        {
            if (inBin[i] == 0 && inBin[i + 1] == 0 && inBin[i + 2] == 0 && inBin[i + 3] == 0)
            {
                medI[i / 4] = 1;
                medQ[i / 4] = 1;
            }
            else if (inBin[i] == 0 && inBin[i + 1] == 0 && inBin[i + 2] == 0 && inBin[i + 3] == 1)
            {
                medI[i / 4] = 1;
                medQ[i / 4] = -1;
            }
            else if (inBin[i] == 0 && inBin[i + 1] == 0 && inBin[i + 2] == 1 && inBin[i + 3] == 0)
            {
                medI[i / 4] = -1;
                medQ[i / 4] = -1;
            }
            else if (inBin[i] == 0 && inBin[i + 1] == 0 && inBin[i + 2] == 1 && inBin[i + 3] == 1)
            {
                medI[i / 4] = -1;
                medQ[i / 4] = 1;
            }
            else if (inBin[i] == 0 && inBin[i + 1] == 1 && inBin[i + 2] == 0 && inBin[i + 3] == 0)
            {
                medI[i / 4] = 1;
                medQ[i / 4] = 3;
            }
            else if (inBin[i] == 0 && inBin[i + 1] == 1 && inBin[i + 2] == 0 && inBin[i + 3] == 1)
            {
                medI[i / 4] = 3;
                medQ[i / 4] = 3;
            }
            else if (inBin[i] == 0 && inBin[i + 1] == 1 && inBin[i + 2] == 1 && inBin[i + 3] == 0)
            {
                medI[i / 4] = 3;
                medQ[i / 4] = 1;
            }
            else if (inBin[i] == 0 && inBin[i + 1] == 1 && inBin[i + 2] == 1 && inBin[i + 3] == 1)
            {
                medI[i / 4] = 3;
                medQ[i / 4] = -1;
            }
            else if (inBin[i] == 1 && inBin[i + 1] == 0 && inBin[i + 2] == 0 && inBin[i + 3] == 0)
            {
                medI[i / 4] = 3;
                medQ[i / 4] = -3;
            }
            else if (inBin[i] == 1 && inBin[i + 1] == 0 && inBin[i + 2] == 0 && inBin[i + 3] == 1)
            {
                medI[i / 4] = 1;
                medQ[i / 4] = -3;                
            }
            else if (inBin[i] == 1 && inBin[i + 1] == 0 && inBin[i + 2] == 1 && inBin[i + 3] == 0)
            {
                medI[i / 4] = -1;
                medQ[i / 4] = -3;                
            }
            else if (inBin[i] == 1 && inBin[i + 1] == 0 && inBin[i + 2] == 1 && inBin[i + 3] == 1)
            {
                medI[i / 4] = -3;
                medQ[i / 4] = -3;                
            }
            else if (inBin[i] == 1 && inBin[i + 1] == 1 && inBin[i + 2] == 0 && inBin[i + 3] == 0)
            {
                medI[i / 4] = -3;
                medQ[i / 4] = -1;                
            }
            else if (inBin[i] == 1 && inBin[i + 1] == 1 && inBin[i + 2] == 0 && inBin[i + 3] == 1)
            {
                medI[i / 4] = -3;
                medQ[i / 4] = 1;                
            }
            else if (inBin[i] == 1 && inBin[i + 1] == 1 && inBin[i + 2] == 1 && inBin[i + 3] == 0)
            {
                medI[i / 4] = -3;
                medQ[i / 4] = 3;                
            }
            else if (inBin[i] == 1 && inBin[i + 1] == 1 && inBin[i + 2] == 1 && inBin[i + 3] == 1)
            {
                medI[i / 4] = -1;
                medQ[i / 4] = 3;                
            }
        }
    }

    void Synth_32QAM(vector <char> inBin, vector <float>& medI, vector <float>& medQ, int inpSize)
    {
        for (int i = 0; i < inpSize; i += 5)
        {
            if (inBin[i] == 0 && inBin[i + 1] == 0 && inBin[i + 2] == 0 && inBin[i + 3] == 0 && inBin[i + 4] == 0)
            {
                medI[i + 5] = 1;
                medQ[i + 5] = 1;
                
            }
            else if (inBin[i] == 0 && inBin[i + 1] == 0 && inBin[i + 2] == 0 && inBin[i + 3] == 0 && inBin[i + 4] == 1)
            {
                medI[i + 5] = 1;
                medQ[i + 5] = -1;
                
            }
            else if (inBin[i] == 0 && inBin[i + 1] == 0 && inBin[i + 2] == 0 && inBin[i + 3] == 1 && inBin[i + 4] == 0)
            {
                medI[i + 5] = -1;
                medQ[i + 5] = -1;
                
            }
            else if (inBin[i] == 0 && inBin[i + 1] == 0 && inBin[i + 2] == 0 && inBin[i + 3] == 1 && inBin[i + 4] == 1)
            {
                medI[i + 5] = -1;
                medQ[i + 5] = 1;
                
            }
            else if (inBin[i] == 0 && inBin[i + 1] == 0 && inBin[i + 2] == 1 && inBin[i + 3] == 0 && inBin[i + 4] == 0)
            {
                medI[i + 5] = 1;
                medQ[i + 5] = 3;
                
            }
            else if (inBin[i] == 0 && inBin[i + 1] == 0 && inBin[i + 2] == 1 && inBin[i + 3] == 0 && inBin[i + 4] == 1)
            {
                medI[i + 5] = 3;
                medQ[i + 5] = 3;
                
            }
            else if (inBin[i] == 0 && inBin[i + 1] == 0 && inBin[i + 2] == 1 && inBin[i + 3] == 1 && inBin[i + 4] == 0)
            {
                medI[i + 5] = 3;
                medQ[i + 5] = 1;
                
            }
            else if (inBin[i] == 0 && inBin[i + 1] == 0 && inBin[i + 2] == 1 && inBin[i + 3] == 1 && inBin[i + 4] == 1)
            {
                medI[i + 5] = 3;
                medQ[i + 5] = -1;
                
            }
            else if (inBin[i] == 0 && inBin[i + 1] == 1 && inBin[i + 2] == 0 && inBin[i + 3] == 0 && inBin[i + 4] == 0)
            {
                medI[i + 5] = 3;
                medQ[i + 5] = -3;
                
            }
            else if (inBin[i] == 0 && inBin[i + 1] == 1 && inBin[i + 2] == 0 && inBin[i + 3] == 0 && inBin[i + 4] == 1)
            {
                medI[i + 5] = 1;
                medQ[i + 5] = -3;
                
            }
            else if (inBin[i] == 0 && inBin[i + 1] == 1 && inBin[i + 2] == 0 && inBin[i + 3] == 1 && inBin[i + 4] == 0)
            {
                medI[i + 5] = -1;
                medQ[i + 5] = -3;
                
            }
            else if (inBin[i] == 0 && inBin[i + 1] == 1 && inBin[i + 2] == 0 && inBin[i + 3] == 1 && inBin[i + 4] == 1)
            {
                medI[i + 5] = -3;
                medQ[i + 5] = -3;
                
            }
            else if (inBin[i] == 0 && inBin[i + 1] == 1 && inBin[i + 2] == 1 && inBin[i + 3] == 0 && inBin[i + 4] == 0)
            {
                medI[i + 5] = -3;
                medQ[i + 5] = -1;
                
            }
            else if (inBin[i] == 0 && inBin[i + 1] == 1 && inBin[i + 2] == 1 && inBin[i + 3] == 0 && inBin[i + 4] == 1)
            {
                medI[i + 5] = -3;
                medQ[i + 5] = 1;
                
            }
            else if (inBin[i] == 0 && inBin[i + 1] == 1 && inBin[i + 2] == 1 && inBin[i + 3] == 1 && inBin[i + 4] == 0)
            {
                medI[i + 5] = -3;
                medQ[i + 5] = 3;
                
            }
            else if (inBin[i] == 0 && inBin[i + 1] == 1 && inBin[i + 2] == 1 && inBin[i + 3] == 1 && inBin[i + 4] == 1)
            {
                medI[i + 5] = -1;
                medQ[i + 5] = 3;
                
            }
            else if (inBin[i] == 1 && inBin[i + 1] == 0 && inBin[i + 2] == 0 && inBin[i + 3] == 0 && inBin[i + 4] == 0)
            {
                medI[i + 5] = 1;
                medQ[i + 5] = 5;
                
            }
            else if (inBin[i] == 1 && inBin[i + 1] == 0 && inBin[i + 2] == 0 && inBin[i + 3] == 0 && inBin[i + 4] == 1)
            {
                medI[i + 5] = 3;
                medQ[i + 5] = 5;
                
            }
            else if (inBin[i] == 1 && inBin[i + 1] == 0 && inBin[i + 2] == 0 && inBin[i + 3] == 1 && inBin[i + 4] == 0)
            {
                medI[i + 5] = 5;
                medQ[i + 5] = 3;
                
            }
            else if (inBin[i] == 1 && inBin[i + 1] == 0 && inBin[i + 2] == 0 && inBin[i + 3] == 1 && inBin[i + 4] == 1)
            {
                medI[i + 5] = 5;
                medQ[i + 5] = 1;
                
            }
            else if (inBin[i] == 1 && inBin[i + 1] == 0 && inBin[i + 2] == 1 && inBin[i + 3] == 0 && inBin[i + 4] == 0)
            {
                medI[i + 5] = 5;
                medQ[i + 5] = -1;
                
            }
            else if (inBin[i] == 1 && inBin[i + 1] == 0 && inBin[i + 2] == 1 && inBin[i + 3] == 0 && inBin[i + 4] == 1)
            {
                medI[i + 5] = 5;
                medQ[i + 5] = -3;
                
            }
            else if (inBin[i] == 1 && inBin[i + 1] == 0 && inBin[i + 2] == 1 && inBin[i + 3] == 1 && inBin[i + 4] == 0)
            {
                medI[i + 5] = 3;
                medQ[i + 5] = -5;
                
            }
            else if (inBin[i] == 1 && inBin[i + 1] == 0 && inBin[i + 2] == 1 && inBin[i + 3] == 1 && inBin[i + 4] == 1)
            {
                medI[i + 5] = 1;
                medQ[i + 5] = -5;
                
            }
            else if (inBin[i] == 1 && inBin[i + 1] == 1 && inBin[i + 2] == 0 && inBin[i + 3] == 0 && inBin[i + 4] == 0)
            {
                medI[i + 5] = -1;
                medQ[i + 5] = -5;
                
            }
            else if (inBin[i] == 1 && inBin[i + 1] == 1 && inBin[i + 2] == 0 && inBin[i + 3] == 0 && inBin[i + 4] == 1)
            {
                medI[i + 5] = -3;
                medQ[i + 5] = -5;
                
            }
            else if (inBin[i] == 1 && inBin[i + 1] == 1 && inBin[i + 2] == 0 && inBin[i + 3] == 1 && inBin[i + 4] == 0)
            {
                medI[i + 5] = -5;
                medQ[i + 5] = -3;
                
            }
            else if (inBin[i] == 1 && inBin[i + 1] == 1 && inBin[i + 2] == 0 && inBin[i + 3] == 1 && inBin[i + 4] == 1)
            {
                medI[i + 5] = -5;
                medQ[i + 5] = -1;
                
            }
            else if (inBin[i] == 1 && inBin[i + 1] == 1 && inBin[i + 2] == 1 && inBin[i + 3] == 0 && inBin[i + 4] == 0)
            {
                medI[i + 5] = -5;
                medQ[i + 5] = 1;
                
            }
            else if (inBin[i] == 1 && inBin[i + 1] == 1 && inBin[i + 2] == 1 && inBin[i + 3] == 0 && inBin[i + 4] == 1)
            {
                medI[i + 5] = -5;
                medQ[i + 5] = 3;
                
            }
            else if (inBin[i] == 1 && inBin[i + 1] == 1 && inBin[i + 2] == 1 && inBin[i + 3] == 1 && inBin[i + 4] == 0)
            {
                medI[i + 5] = -3;
                medQ[i + 5] = 5;
                
            }
            else if (inBin[i] == 1 && inBin[i + 1] == 1 && inBin[i + 2] == 1 && inBin[i + 3] == 1 && inBin[i + 4] == 1)
            {
                medI[i + 5] = -1;
                medQ[i + 5] = 5;
                
            }
        }
    }

    void Synth_64QAM(vector <char> inBin, vector <float>& medI, vector <float>& medQ, int inpSize)
    {
        for (int i = 0; i < inpSize; i += 6)
        {
            if (inBin[i] == 0 && inBin[i + 1] == 0 && inBin[i + 2] == 0 && inBin[i + 3] == 0 && inBin[i + 4] == 0 && inBin[i + 5] == 0)
            {
                medI[i + 6] = 1;
                medQ[i + 6] = 1;
                
            }
            else if (inBin[i] == 0 && inBin[i + 1] == 0 && inBin[i + 2] == 0 && inBin[i + 3] == 0 && inBin[i + 4] == 0 && inBin[i + 5] == 1)
            {
                medI[i + 6] = 1;
                medQ[i + 6] = -1;
                
            }
            else if (inBin[i] == 0 && inBin[i + 1] == 0 && inBin[i + 2] == 0 && inBin[i + 3] == 0 && inBin[i + 4] == 1 && inBin[i + 5] == 0)
            {
                medI[i + 6] = -1;
                medQ[i + 6] = -1;
                
            }
            else if (inBin[i] == 0 && inBin[i + 1] == 0 && inBin[i + 2] == 0 && inBin[i + 3] == 0 && inBin[i + 4] == 1 && inBin[i + 5] == 1)
            {
                medI[i + 6] = -1;
                medQ[i + 6] = 1;
                
            }
            else if (inBin[i] == 0 && inBin[i + 1] == 0 && inBin[i + 2] == 0 && inBin[i + 3] == 1 && inBin[i + 4] == 0 && inBin[i + 5] == 0)
            {
                medI[i + 6] = 1;
                medQ[i + 6] = 3;
                
            }
            else if (inBin[i] == 0 && inBin[i + 1] == 0 && inBin[i + 2] == 0 && inBin[i + 3] == 1 && inBin[i + 4] == 0 && inBin[i + 5] == 1)
            {
                medI[i + 6] = 3;
                medQ[i + 6] = 3;
                
            }
            else if (inBin[i] == 0 && inBin[i + 1] == 0 && inBin[i + 2] == 0 && inBin[i + 3] == 1 && inBin[i + 4] == 1 && inBin[i + 5] == 0)
            {
                medI[i + 6] = 3;
                medQ[i + 6] = 1;
                
            }
            else if (inBin[i] == 0 && inBin[i + 1] == 0 && inBin[i + 2] == 0 && inBin[i + 3] == 1 && inBin[i + 4] == 1 && inBin[i + 5] == 1)
            {
                medI[i + 6] = 3;
                medQ[i + 6] = -1;
                
            }
            else if (inBin[i] == 0 && inBin[i + 1] == 0 && inBin[i + 2] == 1 && inBin[i + 3] == 0 && inBin[i + 4] == 0 && inBin[i + 5] == 0)
            {
                medI[i + 6] = 3;
                medQ[i + 6] = -3;
                
            }
            else if (inBin[i] == 0 && inBin[i + 1] == 0 && inBin[i + 2] == 1 && inBin[i + 3] == 0 && inBin[i + 4] == 0 && inBin[i + 5] == 1)
            {
                medI[i + 6] = 1;
                medQ[i + 6] = -3;
                
            }
            else if (inBin[i] == 0 && inBin[i + 1] == 0 && inBin[i + 2] == 1 && inBin[i + 3] == 0 && inBin[i + 4] == 1 && inBin[i + 5] == 0)
            {
                medI[i + 6] = -1;
                medQ[i + 6] = -3;
                
            }
            else if (inBin[i] == 0 && inBin[i + 1] == 0 && inBin[i + 2] == 1 && inBin[i + 3] == 0 && inBin[i + 4] == 1 && inBin[i + 5] == 1)
            {
                medI[i + 6] = -3;
                medQ[i + 6] = -3;
                
            }
            else if (inBin[i] == 0 && inBin[i + 1] == 0 && inBin[i + 2] == 1 && inBin[i + 3] == 1 && inBin[i + 4] == 0 && inBin[i + 5] == 0)
            {
                medI[i + 6] = -3;
                medQ[i + 6] = -1;
                
            }
            else if (inBin[i] == 0 && inBin[i + 1] == 0 && inBin[i + 2] == 1 && inBin[i + 3] == 1 && inBin[i + 4] == 0 && inBin[i + 5] == 1)
            {
                medI[i + 6] = -3;
                medQ[i + 6] = 1;
                
            }
            else if (inBin[i] == 0 && inBin[i + 1] == 0 && inBin[i + 2] == 1 && inBin[i + 3] == 1 && inBin[i + 4] == 1 && inBin[i + 5] == 0)
            {
                medI[i + 6] = -3;
                medQ[i + 6] = 3;
                
            }
            else if (inBin[i] == 0 && inBin[i + 1] == 0 && inBin[i + 2] == 1 && inBin[i + 3] == 1 && inBin[i + 4] == 1 && inBin[i + 5] == 1)
            {
                medI[i + 6] = -1;
                medQ[i + 6] = 3;
                
            }
            else if (inBin[i] == 0 && inBin[i + 1] == 1 && inBin[i + 2] == 0 && inBin[i + 3] == 0 && inBin[i + 4] == 0 && inBin[i + 5] == 0)
            {
                medI[i + 6] = 1;
                medQ[i + 6] = 5;
                
            }
            else if (inBin[i] == 0 && inBin[i + 1] == 1 && inBin[i + 2] == 0 && inBin[i + 3] == 0 && inBin[i + 4] == 0 && inBin[i + 5] == 1)
            {
                medI[i + 6] = 3;
                medQ[i + 6] = 5;
                
            }
            else if (inBin[i] == 0 && inBin[i + 1] == 1 && inBin[i + 2] == 0 && inBin[i + 3] == 0 && inBin[i + 4] == 1 && inBin[i + 5] == 0)
            {
                medI[i + 6] = 5;
                medQ[i + 6] = 5;
                
            }
            else if (inBin[i] == 0 && inBin[i + 1] == 1 && inBin[i + 2] == 0 && inBin[i + 3] == 0 && inBin[i + 4] == 1 && inBin[i + 5] == 1)
            {
                medI[i + 6] = 5;
                medQ[i + 6] = 3;
                
            }
            else if (inBin[i] == 0 && inBin[i + 1] == 1 && inBin[i + 2] == 0 && inBin[i + 3] == 1 && inBin[i + 4] == 0 && inBin[i + 5] == 0)
            {
                medI[i + 6] = 5;
                medQ[i + 6] = 1;
                
            }
            else if (inBin[i] == 0 && inBin[i + 1] == 1 && inBin[i + 2] == 0 && inBin[i + 3] == 1 && inBin[i + 4] == 0 && inBin[i + 5] == 1)
            {
                medI[i + 6] = 5;
                medQ[i + 6] = -1;
                
            }
            else if (inBin[i] == 0 && inBin[i + 1] == 1 && inBin[i + 2] == 0 && inBin[i + 3] == 1 && inBin[i + 4] == 1 && inBin[i + 5] == 0)
            {
                medI[i + 6] = 5;
                medQ[i + 6] = -3;
                
            }
            else if (inBin[i] == 0 && inBin[i + 1] == 1 && inBin[i + 2] == 0 && inBin[i + 3] == 1 && inBin[i + 4] == 1 && inBin[i + 5] == 1)
            {
                medI[i + 6] = 5;
                medQ[i + 6] = -5;
                
            }
            else if (inBin[i] == 0 && inBin[i + 1] == 1 && inBin[i + 2] == 1 && inBin[i + 3] == 0 && inBin[i + 4] == 0 && inBin[i + 5] == 0)
            {
                medI[i + 6] = 3;
                medQ[i + 6] = -5;
                
            }
            else if (inBin[i] == 0 && inBin[i + 1] == 1 && inBin[i + 2] == 1 && inBin[i + 3] == 0 && inBin[i + 4] == 0 && inBin[i + 5] == 1)
            {
                medI[i + 6] = 1;
                medQ[i + 6] = -5;
                
            }
            else if (inBin[i] == 0 && inBin[i + 1] == 1 && inBin[i + 2] == 1 && inBin[i + 3] == 0 && inBin[i + 4] == 1 && inBin[i + 5] == 0)
            {
                medI[i + 6] = -1;
                medQ[i + 6] = -5;
                
            }
            else if (inBin[i] == 0 && inBin[i + 1] == 1 && inBin[i + 2] == 1 && inBin[i + 3] == 0 && inBin[i + 4] == 1 && inBin[i + 5] == 1)
            {
                medI[i + 6] = -3;
                medQ[i + 6] = -5;
                
            }
            else if (inBin[i] == 0 && inBin[i + 1] == 1 && inBin[i + 2] == 1 && inBin[i + 3] == 1 && inBin[i + 4] == 0 && inBin[i + 5] == 0)
            {
                medI[i + 6] = -5;
                medQ[i + 6] = -5;
                
            }
            else if (inBin[i] == 0 && inBin[i + 1] == 1 && inBin[i + 2] == 1 && inBin[i + 3] == 1 && inBin[i + 4] == 0 && inBin[i + 5] == 1)
            {
                medI[i + 6] = -5;
                medQ[i + 6] = -3;
                
            }
            else if (inBin[i] == 0 && inBin[i + 1] == 1 && inBin[i + 2] == 1 && inBin[i + 3] == 1 && inBin[i + 4] == 1 && inBin[i + 5] == 0)
            {
                medI[i + 6] = -5;
                medQ[i + 6] = -1;
                
            }
            else if (inBin[i] == 0 && inBin[i + 1] == 1 && inBin[i + 2] == 1 && inBin[i + 3] == 1 && inBin[i + 4] == 1 && inBin[i + 5] == 1)
            {
                medI[i + 6] = -5;
                medQ[i + 6] = 1;
                
            }
            else if (inBin[i] == 1 && inBin[i + 1] == 0 && inBin[i + 2] == 0 && inBin[i + 3] == 0 && inBin[i + 4] == 0 && inBin[i + 5] == 0)
            {
                medI[i + 6] = -5;
                medQ[i + 6] = 3;
                
            }
            else if (inBin[i] == 1 && inBin[i + 1] == 0 && inBin[i + 2] == 0 && inBin[i + 3] == 0 && inBin[i + 4] == 0 && inBin[i + 5] == 1)
            {
                medI[i + 6] = -5;
                medQ[i + 6] = 5;
                
            }
            else if (inBin[i] == 1 && inBin[i + 1] == 0 && inBin[i + 2] == 0 && inBin[i + 3] == 0 && inBin[i + 4] == 1 && inBin[i + 5] == 0)
            {
                medI[i + 6] = -3;
                medQ[i + 6] = 5;
                
            }
            else if (inBin[i] == 1 && inBin[i + 1] == 0 && inBin[i + 2] == 0 && inBin[i + 3] == 0 && inBin[i + 4] == 1 && inBin[i + 5] == 1)
            {
                medI[i + 6] = -1;
                medQ[i + 6] = 5;
                
            }
            else if (inBin[i] == 1 && inBin[i + 1] == 0 && inBin[i + 2] == 0 && inBin[i + 3] == 1 && inBin[i + 4] == 0 && inBin[i + 5] == 0)
            {
                medI[i + 6] = 1;
                medQ[i + 6] = 7;
                
            }
            else if (inBin[i] == 1 && inBin[i + 1] == 0 && inBin[i + 2] == 0 && inBin[i + 3] == 1 && inBin[i + 4] == 0 && inBin[i + 5] == 1)
            {
                medI[i + 6] = 3;
                medQ[i + 6] = 7;
                
            }
            else if (inBin[i] == 1 && inBin[i + 1] == 0 && inBin[i + 2] == 0 && inBin[i + 3] == 1 && inBin[i + 4] == 1 && inBin[i + 5] == 0)
            {
                medI[i + 6] = 5;
                medQ[i + 6] = 7;
                
            }
            else if (inBin[i] == 1 && inBin[i + 1] == 0 && inBin[i + 2] == 0 && inBin[i + 3] == 1 && inBin[i + 4] == 1 && inBin[i + 5] == 1)
            {
                medI[i + 6] = 7;
                medQ[i + 6] = 7;
                
            }
            else if (inBin[i] == 1 && inBin[i + 1] == 0 && inBin[i + 2] == 1 && inBin[i + 3] == 0 && inBin[i + 4] == 0 && inBin[i + 5] == 0)
            {
                medI[i + 6] = 7;
                medQ[i + 6] = 5;
                
            }
            else if (inBin[i] == 1 && inBin[i + 1] == 0 && inBin[i + 2] == 1  && inBin[i + 3] == 0 && inBin[i + 4] == 0 && inBin[i + 5] == 1)
            {
                medI[i + 6] = 7;
                medQ[i + 6] = 3;
                
            }
            else if (inBin[i] == 1 && inBin[i + 1] == 0 && inBin[i + 2] == 1 && inBin[i + 3] == 0 && inBin[i + 4] == 1 && inBin[i + 5] == 0)
            {
                medI[i + 6] = 7;
                medQ[i + 6] = 1;
                
            }
            else if (inBin[i] == 1 && inBin[i + 1] == 0 && inBin[i + 2] == 1 && inBin[i + 3] == 0 && inBin[i + 4] == 1 && inBin[i + 5] == 1)
            {
                medI[i + 6] = 7;
                medQ[i + 6] = -1;
                
            }
            else if (inBin[i] == 1 && inBin[i + 1] == 0 && inBin[i + 2] == 1 && inBin[i + 3] == 1 && inBin[i + 4] == 0 && inBin[i + 5] == 0)
            {
                medI[i + 6] = 7;
                medQ[i + 6] = -3;
                
            }
            else if (inBin[i] == 1 && inBin[i + 1] == 0 && inBin[i + 2] == 1 && inBin[i + 3] == 1 && inBin[i + 4] == 0 && inBin[i + 5] == 1)
            {
                medI[i + 6] = 7;
                medQ[i + 6] = -5;
                
            }
            else if (inBin[i] == 1 && inBin[i + 1] == 0 && inBin[i + 2] == 1 && inBin[i + 3] == 1 && inBin[i + 4] == 1 && inBin[i + 5] == 0)
            {
                medI[i + 6] = 7;
                medQ[i + 6] = -7;
                
            }
            else if (inBin[i] == 1 && inBin[i + 1] == 0 && inBin[i + 2] == 1 && inBin[i + 3] == 1 && inBin[i + 4] == 1 && inBin[i + 5] == 1)
            {
                medI[i + 6] = 5;
                medQ[i + 6] = -7;
                
            }
            else if (inBin[i] == 1 && inBin[i + 1] == 1 && inBin[i + 2] == 0 && inBin[i + 3] == 0 && inBin[i + 4] == 0 && inBin[i + 5] == 0)
            {
                medI[i + 6] = 3;
                medQ[i + 6] = -7;
                
            }
            else if (inBin[i] == 1 && inBin[i + 1] == 1 && inBin[i + 2] == 0 && inBin[i + 3] == 0 && inBin[i + 4] == 0 && inBin[i + 5] == 1)
            {
                medI[i + 6] = 1;
                medQ[i + 6] = -7;
                
            }
            else if (inBin[i] == 1 && inBin[i + 1] == 1 && inBin[i + 2] == 0 && inBin[i + 3] == 0 && inBin[i + 4] == 1 && inBin[i + 5] == 0)
            {
                medI[i + 6] = -1;
                medQ[i + 6] = -7;
                
            }
            else if (inBin[i] == 1 && inBin[i + 1] == 1 && inBin[i + 2] == 0 && inBin[i + 3] == 0 && inBin[i + 4] == 1 && inBin[i + 5] == 1)
            {
                medI[i + 6] = -3;
                medQ[i + 6] = -7;
                
            }
            else if (inBin[i] == 1 && inBin[i + 1] == 1 && inBin[i + 2] == 0 && inBin[i + 3] == 1 && inBin[i + 4] == 0 && inBin[i + 5] == 0)
            {
                medI[i + 6] = -5;
                medQ[i + 6] = -7;
                
            }
            else if (inBin[i] == 1 && inBin[i + 1] == 1 && inBin[i + 2] == 0 && inBin[i + 3] == 1 && inBin[i + 4] == 0 && inBin[i + 5] == 1)
            {
                medI[i + 6] = -7;
                medQ[i + 6] = -7;
                
            }
            else if (inBin[i] == 1 && inBin[i + 1] == 1 && inBin[i + 2] == 0 && inBin[i + 3] == 1 && inBin[i + 4] == 1 && inBin[i + 5] == 0)
            {
                medI[i + 6] = -7;
                medQ[i + 6] = -5;
                
            }
            else if (inBin[i] == 1 && inBin[i + 1] == 1 && inBin[i + 2] == 0 && inBin[i + 3] == 1 && inBin[i + 4] == 1 && inBin[i + 5] == 1)
            {
                medI[i + 6] = -7;
                medQ[i + 6] = -3;
                
            }
            else if (inBin[i] == 1 && inBin[i + 1] == 1 && inBin[i + 2] == 1 && inBin[i + 3] == 0 && inBin[i + 4] == 0 && inBin[i + 5] == 0)
            {
                medI[i + 6] = -7;
                medQ[i + 6] = -1;
                
            }
            else if (inBin[i] == 1 && inBin[i + 1] == 1 && inBin[i + 2] == 1 && inBin[i + 3] == 0 && inBin[i + 4] == 0 && inBin[i + 5] == 1)
            {
                medI[i + 6] = -7;
                medQ[i + 6] = 1;
                
            }
            else if (inBin[i] == 1 && inBin[i + 1] == 1 && inBin[i + 2] == 1 && inBin[i + 3] == 0 && inBin[i + 4] == 1 && inBin[i + 5] == 0)
            {
                medI[i + 6] = -7;
                medQ[i + 6] = 3;
                
            }
            else if (inBin[i] == 1 && inBin[i + 1] == 1 && inBin[i + 2] == 1 && inBin[i + 3] == 0 && inBin[i + 4] == 1 && inBin[i + 5] == 1)
            {
                medI[i + 6] = -7;
                medQ[i + 6] = 5;
                
            }
            else if (inBin[i] == 1 && inBin[i + 1] == 1 && inBin[i + 2] == 1 && inBin[i + 3] == 1 && inBin[i + 4] == 0 && inBin[i + 5] == 0)
            {
                medI[i + 6] = -7;
                medQ[i + 6] = 7;
                
            }
            else if (inBin[i] == 1 && inBin[i + 1] == 1 && inBin[i + 2] == 1 && inBin[i + 3] == 1 && inBin[i + 4] == 0 && inBin[i + 5] == 1)
            {
                medI[i + 6] = -5;
                medQ[i + 6] = 7;
                
            }
            else if (inBin[i] == 1 && inBin[i + 1] == 1 && inBin[i + 2] == 1 && inBin[i + 3] == 1 && inBin[i + 4] == 1 && inBin[i + 5] == 0)
            {
                medI[i + 6] = -3;
                medQ[i + 6] = 7;
                
            }
            else if (inBin[i] == 1 && inBin[i + 1] == 1 && inBin[i + 2] == 1 && inBin[i + 3] == 1 && inBin[i + 4] == 1 && inBin[i + 5] == 1)
            {
                medI[i + 6] = -1;
                medQ[i + 6] = 7;
                
            }
        }
    }

    void Synth_256QAM(vector <char> inBin, vector <float>& medI, vector <float>& medQ, int inpSize)
    {
        for (int i = 0; i < inpSize; i += 8)
        {
            if (inBin[i] == 0 && inBin[i + 1] == 0 && inBin[i + 2] == 0 && inBin[i + 3] == 0 && inBin[i + 4] == 0 && inBin[i + 5] == 0 && inBin[i + 6] == 0 && inBin[i + 7] == 0)
            {
                medI[i + 8] = 1;
                medQ[i + 8] = 1;
                
            }
            if (inBin[i] == 0 && inBin[i + 1] == 0 && inBin[i + 2] == 0 && inBin[i + 3] == 0 && inBin[i + 4] == 0 && inBin[i + 5] == 0 && inBin[i + 6] == 0 && inBin[i + 7] == 1)
            {
                medI[i + 8] = 1;
                medQ[i + 8] = -1;
                
            }
            if (inBin[i] == 0 && inBin[i + 1] == 0 && inBin[i + 2] == 0 && inBin[i + 3] == 0 && inBin[i + 4] == 0 && inBin[i + 5] == 0 && inBin[i + 6] == 1 && inBin[i + 7] == 0)
            {
                medI[i + 8] = -1;
                medQ[i + 8] = -1;
                
            }
            if (inBin[i] == 0 && inBin[i + 1] == 0 && inBin[i + 2] == 0 && inBin[i + 3] == 0 && inBin[i + 4] == 0 && inBin[i + 5] == 0 && inBin[i + 6] == 1 && inBin[i + 7] == 1)
            {
                medI[i + 8] = -1;
                medQ[i + 8] = 1;
                
            }
            if (inBin[i] == 0 && inBin[i + 1] == 0 && inBin[i + 2] == 0 && inBin[i + 3] == 0 && inBin[i + 4] == 0 && inBin[i + 5] == 1 && inBin[i + 6] == 0 && inBin[i + 7] == 0)
            {
                medI[i + 8] = 1;
                medQ[i + 8] = 3;
                
            }
            if (inBin[i] == 0 && inBin[i + 1] == 0 && inBin[i + 2] == 0 && inBin[i + 3] == 0 && inBin[i + 4] == 0 && inBin[i + 5] == 1 && inBin[i + 6] == 0 && inBin[i + 7] == 1)
            {
                medI[i + 8] = 3;
                medQ[i + 8] = 3;
                
            }
            if (inBin[i] == 0 && inBin[i + 1] == 0 && inBin[i + 2] == 0 && inBin[i + 3] == 0 && inBin[i + 4] == 0 && inBin[i + 5] == 1 && inBin[i + 6] == 1 && inBin[i + 7] == 0)
            {
                medI[i + 8] = 3;
                medQ[i + 8] = 1;
                
            }
            if (inBin[i] == 0 && inBin[i + 1] == 0 && inBin[i + 2] == 0 && inBin[i + 3] == 0 && inBin[i + 4] == 0 && inBin[i + 5] == 1 && inBin[i + 6] == 1 && inBin[i + 7] == 1)
            {
                medI[i + 8] = 3;
                medQ[i + 8] = -1;
                
            }
            if (inBin[i] == 0 && inBin[i + 1] == 0 && inBin[i + 2] == 0 && inBin[i + 3] == 0 && inBin[i + 4] == 1 && inBin[i + 5] == 0 && inBin[i + 6] == 0 && inBin[i + 7] == 0)
            {
                medI[i + 8] = 3;
                medQ[i + 8] = -3;
                
            }
            if (inBin[i] == 0 && inBin[i + 1] == 0 && inBin[i + 2] == 0 && inBin[i + 3] == 0 && inBin[i + 4] == 1 && inBin[i + 5] == 0 && inBin[i + 6] == 0 && inBin[i + 7] == 1)
            {
                medI[i + 8] = 1;
                medQ[i + 8] = -3;
                
            }
            if (inBin[i] == 0 && inBin[i + 1] == 0 && inBin[i + 2] == 0 && inBin[i + 3] == 0 && inBin[i + 4] == 1 && inBin[i + 5] == 0 && inBin[i + 6] == 1 && inBin[i + 7] == 0)
            {
                medI[i + 8] = -1;
                medQ[i + 8] = -3;
                
            }
            if (inBin[i] == 0 && inBin[i + 1] == 0 && inBin[i + 2] == 0 && inBin[i + 3] == 0 && inBin[i + 4] == 1 && inBin[i + 5] == 0 && inBin[i + 6] == 1 && inBin[i + 7] == 1)
            {
                medI[i + 8] = -3;
                medQ[i + 8] = -3;
                
            }
            if (inBin[i] == 0 && inBin[i + 1] == 0 && inBin[i + 2] == 0 && inBin[i + 3] == 0 && inBin[i + 4] == 1 && inBin[i + 5] == 1 && inBin[i + 6] == 0 && inBin[i + 7] == 0)
            {
                medI[i + 8] = -3;
                medQ[i + 8] = -1;
                
            }
            if (inBin[i] == 0 && inBin[i + 1] == 0 && inBin[i + 2] == 0 && inBin[i + 3] == 0 && inBin[i + 4] == 1 && inBin[i + 5] == 1 && inBin[i + 6] == 0 && inBin[i + 7] == 1)
            {
                medI[i + 8] = -3;
                medQ[i + 8] = 1;
                
            }
            if (inBin[i] == 0 && inBin[i + 1] == 0 && inBin[i + 2] == 0 && inBin[i + 3] == 0 && inBin[i + 4] == 1 && inBin[i + 5] == 1 && inBin[i + 6] == 1 && inBin[i + 7] == 0)
            {
                medI[i + 8] = -3;
                medQ[i + 8] = 3;
                
            }
            if (inBin[i] == 0 && inBin[i + 1] == 0 && inBin[i + 2] == 0 && inBin[i + 3] == 0 && inBin[i + 4] == 1 && inBin[i + 5] == 1 && inBin[i + 6] == 1 && inBin[i + 7] == 1)
            {
                medI[i + 8] = -1;
                medQ[i + 8] = 3;
                
            }
            if (inBin[i] == 0 && inBin[i + 1] == 0 && inBin[i + 2] == 0 && inBin[i + 3] == 1 && inBin[i + 4] == 0 && inBin[i + 5] == 0 && inBin[i + 6] == 0 && inBin[i + 7] == 0)
            {
                medI[i + 8] = 1;
                medQ[i + 8] = 5;
                
            }
            if (inBin[i] == 0 && inBin[i + 1] == 0 && inBin[i + 2] == 0 && inBin[i + 3] == 1 && inBin[i + 4] == 0 && inBin[i + 5] == 0 && inBin[i + 6] == 0 && inBin[i + 7] == 1)
            {
                medI[i + 8] = 3;
                medQ[i + 8] = 5;
                
            }
            if (inBin[i] == 0 && inBin[i + 1] == 0 && inBin[i + 2] == 0 && inBin[i + 3] == 1 && inBin[i + 4] == 0 && inBin[i + 5] == 0 && inBin[i + 6] == 1 && inBin[i + 7] == 0)
            {
                medI[i + 8] = 5;
                medQ[i + 8] = 5;
                
            }
            if (inBin[i] == 0 && inBin[i + 1] == 0 && inBin[i + 2] == 0 && inBin[i + 3] == 1 && inBin[i + 4] == 0 && inBin[i + 5] == 0 && inBin[i + 6] == 1 && inBin[i + 7] == 1)
            {
                medI[i + 8] = 5;
                medQ[i + 8] = 3;
                
            }
            if (inBin[i] == 0 && inBin[i + 1] == 0 && inBin[i + 2] == 0 && inBin[i + 3] == 1 && inBin[i + 4] == 0 && inBin[i + 5] == 1 && inBin[i + 6] == 0 && inBin[i + 7] == 0)
            {
                medI[i + 8] = 5;
                medQ[i + 8] = 1;
                
            }
            if (inBin[i] == 0 && inBin[i + 1] == 0 && inBin[i + 2] == 0 && inBin[i + 3] == 1 && inBin[i + 4] == 0 && inBin[i + 5] == 1 && inBin[i + 6] == 0 && inBin[i + 7] == 1)
            {
                medI[i + 8] = 5;
                medQ[i + 8] = -1;
                
            }
            if (inBin[i] == 0 && inBin[i + 1] == 0 && inBin[i + 2] == 0 && inBin[i + 3] == 1 && inBin[i + 4] == 0 && inBin[i + 5] == 1 && inBin[i + 6] == 1 && inBin[i + 7] == 0)
            {
                medI[i + 8] = 5;
                medQ[i + 8] = -3;
                
            }
            if (inBin[i] == 0 && inBin[i + 1] == 0 && inBin[i + 2] == 0 && inBin[i + 3] == 1 && inBin[i + 4] == 0 && inBin[i + 5] == 1 && inBin[i + 6] == 1 && inBin[i + 7] == 1)
            {
                medI[i + 8] = 5;
                medQ[i + 8] = -5;
                
            }
            if (inBin[i] == 0 && inBin[i + 1] == 0 && inBin[i + 2] == 0 && inBin[i + 3] == 1 && inBin[i + 4] == 1 && inBin[i + 5] == 0 && inBin[i + 6] == 0 && inBin[i + 7] == 0)
            {
                medI[i + 8] = 3;
                medQ[i + 8] = -5;
                
            }
            if (inBin[i] == 0 && inBin[i + 1] == 0 && inBin[i + 2] == 0 && inBin[i + 3] == 1 && inBin[i + 4] == 1 && inBin[i + 5] == 0 && inBin[i + 6] == 0 && inBin[i + 7] == 1)
            {
                medI[i + 8] = 1;
                medQ[i + 8] = -5;
                
            }
            if (inBin[i] == 0 && inBin[i + 1] == 0 && inBin[i + 2] == 0 && inBin[i + 3] == 1 && inBin[i + 4] == 1 && inBin[i + 5] == 0 && inBin[i + 6] == 1 && inBin[i + 7] == 0)
            {
                medI[i + 8] = -1;
                medQ[i + 8] = -5;
                
            }
            if (inBin[i] == 0 && inBin[i + 1] == 0 && inBin[i + 2] == 0 && inBin[i + 3] == 1 && inBin[i + 4] == 1 && inBin[i + 5] == 0 && inBin[i + 6] == 1 && inBin[i + 7] == 1)
            {
                medI[i + 8] = -3;
                medQ[i + 8] = -5;
                
            }
            if (inBin[i] == 0 && inBin[i + 1] == 0 && inBin[i + 2] == 0 && inBin[i + 3] == 1 && inBin[i + 4] == 1 && inBin[i + 5] == 1 && inBin[i + 6] == 0 && inBin[i + 7] == 0)
            {
                medI[i + 8] = -5;
                medQ[i + 8] = -5;
                
            }
            if (inBin[i] == 0 && inBin[i + 1] == 0 && inBin[i + 2] == 0 && inBin[i + 3] == 1 && inBin[i + 4] == 1 && inBin[i + 5] == 1 && inBin[i + 6] == 0 && inBin[i + 7] == 1)
            {
                medI[i + 8] = -5;
                medQ[i + 8] = -3;
                
            }
            if (inBin[i] == 0 && inBin[i + 1] == 0 && inBin[i + 2] == 0 && inBin[i + 3] == 1 && inBin[i + 4] == 1 && inBin[i + 5] == 1 && inBin[i + 6] == 1 && inBin[i + 7] == 0)
            {
                medI[i + 8] = -5;
                medQ[i + 8] = -1;
                
            }
            if (inBin[i] == 0 && inBin[i + 1] == 0 && inBin[i + 2] == 0 && inBin[i + 3] == 1 && inBin[i + 4] == 1 && inBin[i + 5] == 1 && inBin[i + 6] == 1 && inBin[i + 7] == 1)
            {
                medI[i + 8] = -5;
                medQ[i + 8] = 1;
                
            }
            if (inBin[i] == 0 && inBin[i + 1] == 0 && inBin[i + 2] == 1 && inBin[i + 3] == 0 && inBin[i + 4] == 0 && inBin[i + 5] == 0 && inBin[i + 6] == 0 && inBin[i + 7] == 0)
            {
                medI[i + 8] = -5;
                medQ[i + 8] = 3;
                
            }
            if (inBin[i] == 0 && inBin[i + 1] == 0 && inBin[i + 2] == 1 && inBin[i + 3] == 0 && inBin[i + 4] == 0 && inBin[i + 5] == 0 && inBin[i + 6] == 0 && inBin[i + 7] == 1)
            {
                medI[i + 8] = -5;
                medQ[i + 8] = 5;
                
            }
            if (inBin[i] == 0 && inBin[i + 1] == 0 && inBin[i + 2] == 1 && inBin[i + 3] == 0 && inBin[i + 4] == 0 && inBin[i + 5] == 0 && inBin[i + 6] == 1 && inBin[i + 7] == 0)
            {
                medI[i + 8] = -3;
                medQ[i + 8] = 5;
                
            }
            if (inBin[i] == 0 && inBin[i + 1] == 0 && inBin[i + 2] == 1 && inBin[i + 3] == 0 && inBin[i + 4] == 0 && inBin[i + 5] == 0 && inBin[i + 6] == 1 && inBin[i + 7] == 1)
            {
                medI[i + 8] = -1;
                medQ[i + 8] = 5;
                
            }
            if (inBin[i] == 0 && inBin[i + 1] == 0 && inBin[i + 2] == 1 && inBin[i + 3] == 0 && inBin[i + 4] == 0 && inBin[i + 5] == 1 && inBin[i + 6] == 0 && inBin[i + 7] == 0)
            {
                medI[i + 8] = 1;
                medQ[i + 8] = 7;
                
            }
            if (inBin[i] == 0 && inBin[i + 1] == 0 && inBin[i + 2] == 1 && inBin[i + 3] == 0 && inBin[i + 4] == 0 && inBin[i + 5] == 1 && inBin[i + 6] == 0 && inBin[i + 7] == 1)
            {
                medI[i + 8] = 3;
                medQ[i + 8] = 7;
                
            }
            if (inBin[i] == 0 && inBin[i + 1] == 0 && inBin[i + 2] == 1 && inBin[i + 3] == 0 && inBin[i + 4] == 0 && inBin[i + 5] == 1 && inBin[i + 6] == 1 && inBin[i + 7] == 0)
            {
                medI[i + 8] = 5;
                medQ[i + 8] = 7;
                
            }
            if (inBin[i] == 0 && inBin[i + 1] == 0 && inBin[i + 2] == 1 && inBin[i + 3] == 0 && inBin[i + 4] == 0 && inBin[i + 5] == 1 && inBin[i + 6] == 1 && inBin[i + 7] == 1)
            {
                medI[i + 8] = 7;
                medQ[i + 8] = 7;
                
            }
            if (inBin[i] == 0 && inBin[i + 1] == 0 && inBin[i + 2] == 1 && inBin[i + 3] == 0 && inBin[i + 4] == 1 && inBin[i + 5] == 0 && inBin[i + 6] == 0 && inBin[i + 7] == 0)
            {
                medI[i + 8] = 7;
                medQ[i + 8] = 5;
                
            }
            if (inBin[i] == 0 && inBin[i + 1] == 0 && inBin[i + 2] == 1 && inBin[i + 3] == 0 && inBin[i + 4] == 1 && inBin[i + 5] == 0 && inBin[i + 6] == 0 && inBin[i + 7] == 1)
            {
                medI[i + 8] = 7;
                medQ[i + 8] = 3;
                
            }
            if (inBin[i] == 0 && inBin[i + 1] == 0 && inBin[i + 2] == 1 && inBin[i + 3] == 0 && inBin[i + 4] == 1 && inBin[i + 5] == 0 && inBin[i + 6] == 1 && inBin[i + 7] == 0)
            {
                medI[i + 8] = 7;
                medQ[i + 8] = 1;
                
            }
            if (inBin[i] == 0 && inBin[i + 1] == 0 && inBin[i + 2] == 1 && inBin[i + 3] == 0 && inBin[i + 4] == 1 && inBin[i + 5] == 0 && inBin[i + 6] == 1 && inBin[i + 7] == 1)
            {
                medI[i + 8] = 7;
                medQ[i + 8] = -1;
                
            }
            if (inBin[i] == 0 && inBin[i + 1] == 0 && inBin[i + 2] == 1 && inBin[i + 3] == 0 && inBin[i + 4] == 1 && inBin[i + 5] == 1 && inBin[i + 6] == 0 && inBin[i + 7] == 0)
            {
                medI[i + 8] = 7;
                medQ[i + 8] = -3;
                
            }
            if (inBin[i] == 0 && inBin[i + 1] == 0 && inBin[i + 2] == 1 && inBin[i + 3] == 0 && inBin[i + 4] == 1 && inBin[i + 5] == 1 && inBin[i + 6] == 0 && inBin[i + 7] == 1)
            {
                medI[i + 8] = 7;
                medQ[i + 8] = -5;
                
            }
            if (inBin[i] == 0 && inBin[i + 1] == 0 && inBin[i + 2] == 1 && inBin[i + 3] == 0 && inBin[i + 4] == 1 && inBin[i + 5] == 1 && inBin[i + 6] == 1 && inBin[i + 7] == 0)
            {
                medI[i + 8] = 7;
                medQ[i + 8] = -7;
                
            }
            if (inBin[i] == 0 && inBin[i + 1] == 0 && inBin[i + 2] == 1 && inBin[i + 3] == 0 && inBin[i + 4] == 1 && inBin[i + 5] == 1 && inBin[i + 6] == 1 && inBin[i + 7] == 1)
            {
                medI[i + 8] = 5;
                medQ[i + 8] = -7;
                
            }
            if (inBin[i] == 0 && inBin[i + 1] == 0 && inBin[i + 2] == 1 && inBin[i + 3] == 1 && inBin[i + 4] == 0 && inBin[i + 5] == 0 && inBin[i + 6] == 0 && inBin[i + 7] == 0)
            {
                medI[i + 8] = 3;
                medQ[i + 8] = -7;
                
            }
            if (inBin[i] == 0 && inBin[i + 1] == 0 && inBin[i + 2] == 1 && inBin[i + 3] == 1 && inBin[i + 4] == 0 && inBin[i + 5] == 0 && inBin[i + 6] == 0 && inBin[i + 7] == 1)
            {
                medI[i + 8] = 1;
                medQ[i + 8] = -7;
                
            }
            if (inBin[i] == 0 && inBin[i + 1] == 0 && inBin[i + 2] == 1 && inBin[i + 3] == 1 && inBin[i + 4] == 0 && inBin[i + 5] == 0 && inBin[i + 6] == 1 && inBin[i + 7] == 0)
            {
                medI[i + 8] = -1;
                medQ[i + 8] = -7;
                
            }
            if (inBin[i] == 0 && inBin[i + 1] == 0 && inBin[i + 2] == 1 && inBin[i + 3] == 1 && inBin[i + 4] == 0 && inBin[i + 5] == 0 && inBin[i + 6] == 1 && inBin[i + 7] == 1)
            {
                medI[i + 8] = -3;
                medQ[i + 8] = -7;
                
            }
            if (inBin[i] == 0 && inBin[i + 1] == 0 && inBin[i + 2] == 1 && inBin[i + 3] == 1 && inBin[i + 4] == 0 && inBin[i + 5] == 1 && inBin[i + 6] == 0 && inBin[i + 7] == 0)
            {
                medI[i + 8] = -5;
                medQ[i + 8] = -7;
                
            }
            if (inBin[i] == 0 && inBin[i + 1] == 0 && inBin[i + 2] == 1 && inBin[i + 3] == 1 && inBin[i + 4] == 0 && inBin[i + 5] == 1 && inBin[i + 6] == 0 && inBin[i + 7] == 1)
            {
                medI[i + 8] = -7;
                medQ[i + 8] = -7;
                
            }
            if (inBin[i] == 0 && inBin[i + 1] == 0 && inBin[i + 2] == 1 && inBin[i + 3] == 1 && inBin[i + 4] == 0 && inBin[i + 5] == 1 && inBin[i + 6] == 1 && inBin[i + 7] == 0)
            {
                medI[i + 8] = -7;
                medQ[i + 8] = -5;
                
            }
            if (inBin[i] == 0 && inBin[i + 1] == 0 && inBin[i + 2] == 1 && inBin[i + 3] == 1 && inBin[i + 4] == 0 && inBin[i + 5] == 1 && inBin[i + 6] == 1 && inBin[i + 7] == 1)
            {
                medI[i + 8] = -7;
                medQ[i + 8] = -3;
                
            }
            if (inBin[i] == 0 && inBin[i + 1] == 0 && inBin[i + 2] == 1 && inBin[i + 3] == 1 && inBin[i + 4] == 1 && inBin[i + 5] == 0 && inBin[i + 6] == 0 && inBin[i + 7] == 0)
            {
                medI[i + 8] = -7;
                medQ[i + 8] = -1;
                
            }
            if (inBin[i] == 0 && inBin[i + 1] == 0 && inBin[i + 2] == 1 && inBin[i + 3] == 1 && inBin[i + 4] == 1 && inBin[i + 5] == 0 && inBin[i + 6] == 0 && inBin[i + 7] == 1)
            {
                medI[i + 8] = -7;
                medQ[i + 8] = 1;
                
            }
            if (inBin[i] == 0 && inBin[i + 1] == 0 && inBin[i + 2] == 1 && inBin[i + 3] == 1 && inBin[i + 4] == 1 && inBin[i + 5] == 0 && inBin[i + 6] == 1 && inBin[i + 7] == 0)
            {
                medI[i + 8] = -7;
                medQ[i + 8] = 3;
                
            }
            if (inBin[i] == 0 && inBin[i + 1] == 0 && inBin[i + 2] == 1 && inBin[i + 3] == 1 && inBin[i + 4] == 1 && inBin[i + 5] == 0 && inBin[i + 6] == 1 && inBin[i + 7] == 1)
            {
                medI[i + 8] = -7;
                medQ[i + 8] = 5;
                
            }
            if (inBin[i] == 0 && inBin[i + 1] == 0 && inBin[i + 2] == 1 && inBin[i + 3] == 1 && inBin[i + 4] == 1 && inBin[i + 5] == 1 && inBin[i + 6] == 0 && inBin[i + 7] == 0)
            {
                medI[i + 8] = -7;
                medQ[i + 8] = 7;
                
            }
            if (inBin[i] == 0 && inBin[i + 1] == 0 && inBin[i + 2] == 1 && inBin[i + 3] == 1 && inBin[i + 4] == 1 && inBin[i + 5] == 1 && inBin[i + 6] == 0 && inBin[i + 7] == 1)
            {
                medI[i + 8] = -5;
                medQ[i + 8] = 7;
                
            }
            if (inBin[i] == 0 && inBin[i + 1] == 0 && inBin[i + 2] == 1 && inBin[i + 3] == 1 && inBin[i + 4] == 1 && inBin[i + 5] == 1 && inBin[i + 6] == 1 && inBin[i + 7] == 0)
            {
                medI[i + 8] = -3;
                medQ[i + 8] = 7;
                
            }
            if (inBin[i] == 0 && inBin[i + 1] == 0 && inBin[i + 2] == 1 && inBin[i + 3] == 1 && inBin[i + 4] == 1 && inBin[i + 5] == 1 && inBin[i + 6] == 1 && inBin[i + 7] == 1)
            {
                medI[i + 8] = -1;
                medQ[i + 8] = 7;
                
            }
            if (inBin[i] == 0 && inBin[i + 1] == 1 && inBin[i + 2] == 0 && inBin[i + 3] == 0 && inBin[i + 4] == 0 && inBin[i + 5] == 0 && inBin[i + 6] == 0 && inBin[i + 7] == 0)
            {
                medI[i + 8] = 1;
                medQ[i + 8] = 9;
                
            }
            if (inBin[i] == 0 && inBin[i + 1] == 1 && inBin[i + 2] == 0 && inBin[i + 3] == 0 && inBin[i + 4] == 0 && inBin[i + 5] == 0 && inBin[i + 6] == 0 && inBin[i + 7] == 1)
            {
                medI[i + 8] = 3;
                medQ[i + 8] = 9;
                
            }
            if (inBin[i] == 0 && inBin[i + 1] == 1 && inBin[i + 2] == 0 && inBin[i + 3] == 0 && inBin[i + 4] == 0 && inBin[i + 5] == 0 && inBin[i + 6] == 1 && inBin[i + 7] == 0)
            {
                medI[i + 8] = 5;
                medQ[i + 8] = 9;
                
            }
            if (inBin[i] == 0 && inBin[i + 1] == 1 && inBin[i + 2] == 0 && inBin[i + 3] == 0 && inBin[i + 4] == 0 && inBin[i + 5] == 0 && inBin[i + 6] == 1 && inBin[i + 7] == 1)
            {
                medI[i + 8] = 7;
                medQ[i + 8] = 9;
                
            }
            if (inBin[i] == 0 && inBin[i + 1] == 1 && inBin[i + 2] == 0 && inBin[i + 3] == 0 && inBin[i + 4] == 0 && inBin[i + 5] == 1 && inBin[i + 6] == 0 && inBin[i + 7] == 0)
            {
                medI[i + 8] = 9;
                medQ[i + 8] = 9;
                
            }
            if (inBin[i] == 0 && inBin[i + 1] == 1 && inBin[i + 2] == 0 && inBin[i + 3] == 0 && inBin[i + 4] == 0 && inBin[i + 5] == 1 && inBin[i + 6] == 0 && inBin[i + 7] == 1)
            {
                medI[i + 8] = 9;
                medQ[i + 8] = 7;
                
            }
            if (inBin[i] == 0 && inBin[i + 1] == 1 && inBin[i + 2] == 0 && inBin[i + 3] == 0 && inBin[i + 4] == 0 && inBin[i + 5] == 1 && inBin[i + 6] == 1 && inBin[i + 7] == 0)
            {
                medI[i + 8] = 9;
                medQ[i + 8] = 5;
                
            }
            if (inBin[i] == 0 && inBin[i + 1] == 1 && inBin[i + 2] == 0 && inBin[i + 3] == 0 && inBin[i + 4] == 0 && inBin[i + 5] == 1 && inBin[i + 6] == 1 && inBin[i + 7] == 1)
            {
                medI[i + 8] = 9;
                medQ[i + 8] = 3;
                
            }
            if (inBin[i] == 0 && inBin[i + 1] == 1 && inBin[i + 2] == 0 && inBin[i + 3] == 0 && inBin[i + 4] == 1 && inBin[i + 5] == 0 && inBin[i + 6] == 0 && inBin[i + 7] == 0)
            {
                medI[i + 8] = 9;
                medQ[i + 8] = 1;
                
            }
            if (inBin[i] == 0 && inBin[i + 1] == 1 && inBin[i + 2] == 0 && inBin[i + 3] == 0 && inBin[i + 4] == 1 && inBin[i + 5] == 0 && inBin[i + 6] == 0 && inBin[i + 7] == 1)
            {
                medI[i + 8] = 9;
                medQ[i + 8] = -1;
                
            }
            if (inBin[i] == 0 && inBin[i + 1] == 1 && inBin[i + 2] == 0 && inBin[i + 3] == 0 && inBin[i + 4] == 1 && inBin[i + 5] == 0 && inBin[i + 6] == 1 && inBin[i + 7] == 0)
            {
                medI[i + 8] = 9;
                medQ[i + 8] = -3;
                
            }
            if (inBin[i] == 0 && inBin[i + 1] == 1 && inBin[i + 2] == 0 && inBin[i + 3] == 0 && inBin[i + 4] == 1 && inBin[i + 5] == 0 && inBin[i + 6] == 1 && inBin[i + 7] == 1)
            {
                medI[i + 8] = 9;
                medQ[i + 8] = -5;
                
            }
            if (inBin[i] == 0 && inBin[i + 1] == 1 && inBin[i + 2] == 0 && inBin[i + 3] == 0 && inBin[i + 4] == 1 && inBin[i + 5] == 1 && inBin[i + 6] == 0 && inBin[i + 7] == 0)
            {
                medI[i + 8] = 9;
                medQ[i + 8] = -7;
                
            }
            if (inBin[i] == 0 && inBin[i + 1] == 1 && inBin[i + 2] == 0 && inBin[i + 3] == 0 && inBin[i + 4] == 1 && inBin[i + 5] == 1 && inBin[i + 6] == 0 && inBin[i + 7] == 1)
            {
                medI[i + 8] = 9;
                medQ[i + 8] = -9;
                
            }
            if (inBin[i] == 0 && inBin[i + 1] == 1 && inBin[i + 2] == 0 && inBin[i + 3] == 0 && inBin[i + 4] == 1 && inBin[i + 5] == 1 && inBin[i + 6] == 1 && inBin[i + 7] == 0)
            {
                medI[i + 8] = 7;
                medQ[i + 8] = -9;
                
            }
            if (inBin[i] == 0 && inBin[i + 1] == 1 && inBin[i + 2] == 0 && inBin[i + 3] == 0 && inBin[i + 4] == 1 && inBin[i + 5] == 1 && inBin[i + 6] == 1 && inBin[i + 7] == 1)
            {
                medI[i + 8] = 5;
                medQ[i + 8] = -9;
                
            }
            if (inBin[i] == 0 && inBin[i + 1] == 1 && inBin[i + 2] == 0 && inBin[i + 3] == 1 && inBin[i + 4] == 0 && inBin[i + 5] == 0 && inBin[i + 6] == 0 && inBin[i + 7] == 0)
            {
                medI[i + 8] = 3;
                medQ[i + 8] = -9;
                
            }
            if (inBin[i] == 0 && inBin[i + 1] == 1 && inBin[i + 2] == 0 && inBin[i + 3] == 1 && inBin[i + 4] == 0 && inBin[i + 5] == 0 && inBin[i + 6] == 0 && inBin[i + 7] == 1)
            {
                medI[i + 8] = 1;
                medQ[i + 8] = -9;
                
            }
            if (inBin[i] == 0 && inBin[i + 1] == 1 && inBin[i + 2] == 0 && inBin[i + 3] == 1 && inBin[i + 4] == 0 && inBin[i + 5] == 0 && inBin[i + 6] == 1 && inBin[i + 7] == 0)
            {
                medI[i + 8] = -1;
                medQ[i + 8] = -9;
                
            }
            if (inBin[i] == 0 && inBin[i + 1] == 1 && inBin[i + 2] == 0 && inBin[i + 3] == 1 && inBin[i + 4] == 0 && inBin[i + 5] == 0 && inBin[i + 6] == 1 && inBin[i + 7] == 1)
            {
                medI[i + 8] = -3;
                medQ[i + 8] = -9;
                
            }
            if (inBin[i] == 0 && inBin[i + 1] == 1 && inBin[i + 2] == 0 && inBin[i + 3] == 1 && inBin[i + 4] == 0 && inBin[i + 5] == 1 && inBin[i + 6] == 0 && inBin[i + 7] == 0)
            {
                medI[i + 8] = -5;
                medQ[i + 8] = -9;
                
            }
            if (inBin[i] == 0 && inBin[i + 1] == 1 && inBin[i + 2] == 0 && inBin[i + 3] == 1 && inBin[i + 4] == 0 && inBin[i + 5] == 1 && inBin[i + 6] == 0 && inBin[i + 7] == 1)
            {
                medI[i + 8] = -7;
                medQ[i + 8] = -9;
                
            }
            if (inBin[i] == 0 && inBin[i + 1] == 1 && inBin[i + 2] == 0 && inBin[i + 3] == 1 && inBin[i + 4] == 0 && inBin[i + 5] == 1 && inBin[i + 6] == 1 && inBin[i + 7] == 0)
            {
                medI[i + 8] = -9;
                medQ[i + 8] = -9;
                
            }
            if (inBin[i] == 0 && inBin[i + 1] == 1 && inBin[i + 2] == 0 && inBin[i + 3] == 1 && inBin[i + 4] == 0 && inBin[i + 5] == 1 && inBin[i + 6] == 1 && inBin[i + 7] == 1)
            {
                medI[i + 8] = -9;
                medQ[i + 8] = -7;
                
            }
            if (inBin[i] == 0 && inBin[i + 1] == 1 && inBin[i + 2] == 0 && inBin[i + 3] == 1 && inBin[i + 4] == 1 && inBin[i + 5] == 0 && inBin[i + 6] == 0 && inBin[i + 7] == 0)
            {
                medI[i + 8] = -9;
                medQ[i + 8] = -5;
                
            }
            if (inBin[i] == 0 && inBin[i + 1] == 1 && inBin[i + 2] == 0 && inBin[i + 3] == 1 && inBin[i + 4] == 1 && inBin[i + 5] == 0 && inBin[i + 6] == 0 && inBin[i + 7] == 1)
            {
                medI[i + 8] = -9;
                medQ[i + 8] = -3;
                
            }
            if (inBin[i] == 0 && inBin[i + 1] == 1 && inBin[i + 2] == 0 && inBin[i + 3] == 1 && inBin[i + 4] == 1 && inBin[i + 5] == 0 && inBin[i + 6] == 1 && inBin[i + 7] == 0)
            {
                medI[i + 8] = -9;
                medQ[i + 8] = -1;
                
            }
            if (inBin[i] == 0 && inBin[i + 1] == 1 && inBin[i + 2] == 0 && inBin[i + 3] == 1 && inBin[i + 4] == 1 && inBin[i + 5] == 0 && inBin[i + 6] == 1 && inBin[i + 7] == 1)
            {
                medI[i + 8] = -9;
                medQ[i + 8] = 1;
                
            }
            if (inBin[i] == 0 && inBin[i + 1] == 1 && inBin[i + 2] == 0 && inBin[i + 3] == 1 && inBin[i + 4] == 1 && inBin[i + 5] == 1 && inBin[i + 6] == 0 && inBin[i + 7] == 0)
            {
                medI[i + 8] = -9;
                medQ[i + 8] = 3;
                
            }
            if (inBin[i] == 0 && inBin[i + 1] == 1 && inBin[i + 2] == 0 && inBin[i + 3] == 1 && inBin[i + 4] == 1 && inBin[i + 5] == 1 && inBin[i + 6] == 0 && inBin[i + 7] == 1)
            {
                medI[i + 8] = -9;
                medQ[i + 8] = 5;
                
            }
            if (inBin[i] == 0 && inBin[i + 1] == 1 && inBin[i + 2] == 0 && inBin[i + 3] == 1 && inBin[i + 4] == 1 && inBin[i + 5] == 1 && inBin[i + 6] == 1 && inBin[i + 7] == 0)
            {
                medI[i + 8] = -9;
                medQ[i + 8] = 7;
                
            }
            if (inBin[i] == 0 && inBin[i + 1] == 1 && inBin[i + 2] == 0 && inBin[i + 3] == 1 && inBin[i + 4] == 1 && inBin[i + 5] == 1 && inBin[i + 6] == 1 && inBin[i + 7] == 1)
            {
                medI[i + 8] = -9;
                medQ[i + 8] = 9;
                
            }
            if (inBin[i] == 0 && inBin[i + 1] == 1 && inBin[i + 2] == 1 && inBin[i + 3] == 0 && inBin[i + 4] == 0 && inBin[i + 5] == 0 && inBin[i + 6] == 0 && inBin[i + 7] == 0)
            {
                medI[i + 8] = -7;
                medQ[i + 8] = 9;
                
            }
            if (inBin[i] == 0 && inBin[i + 1] == 1 && inBin[i + 2] == 1 && inBin[i + 3] == 0 && inBin[i + 4] == 0 && inBin[i + 5] == 0 && inBin[i + 6] == 0 && inBin[i + 7] == 1)
            {
                medI[i + 8] = -5;
                medQ[i + 8] = 9;
                
            }
            if (inBin[i] == 0 && inBin[i + 1] == 1 && inBin[i + 2] == 1 && inBin[i + 3] == 0 && inBin[i + 4] == 0 && inBin[i + 5] == 0 && inBin[i + 6] == 1 && inBin[i + 7] == 0)
            {
                medI[i + 8] = -3;
                medQ[i + 8] = 9;
                
            }
            if (inBin[i] == 0 && inBin[i + 1] == 1 && inBin[i + 2] == 1 && inBin[i + 3] == 0 && inBin[i + 4] == 0 && inBin[i + 5] == 0 && inBin[i + 6] == 1 && inBin[i + 7] == 1)
            {
                medI[i + 8] = -1;
                medQ[i + 8] = 9;
                
            }
            if (inBin[i] == 0 && inBin[i + 1] == 1 && inBin[i + 2] == 1 && inBin[i + 3] == 0 && inBin[i + 4] == 0 && inBin[i + 5] == 1 && inBin[i + 6] == 0 && inBin[i + 7] == 0)
            {
                medI[i + 8] = 1;
                medQ[i + 8] = 11;
                
            }
            if (inBin[i] == 0 && inBin[i + 1] == 1 && inBin[i + 2] == 1 && inBin[i + 3] == 0 && inBin[i + 4] == 0 && inBin[i + 5] == 1 && inBin[i + 6] == 0 && inBin[i + 7] == 1)
            {
                medI[i + 8] = 3;
                medQ[i + 8] = 11;
                
            }
            if (inBin[i] == 0 && inBin[i + 1] == 1 && inBin[i + 2] == 1 && inBin[i + 3] == 0 && inBin[i + 4] == 0 && inBin[i + 5] == 1 && inBin[i + 6] == 1 && inBin[i + 7] == 0)
            {
                medI[i + 8] = 5;
                medQ[i + 8] = 11;
                
            }
            if (inBin[i] == 0 && inBin[i + 1] == 1 && inBin[i + 2] == 1 && inBin[i + 3] == 0 && inBin[i + 4] == 0 && inBin[i + 5] == 1 && inBin[i + 6] == 1 && inBin[i + 7] == 1)
            {
                medI[i + 8] = 7;
                medQ[i + 8] = 11;
                
            }
            if (inBin[i] == 0 && inBin[i + 1] == 1 && inBin[i + 2] == 1 && inBin[i + 3] == 0 && inBin[i + 4] == 1 && inBin[i + 5] == 0 && inBin[i + 6] == 0 && inBin[i + 7] == 0)
            {
                medI[i + 8] = 9;
                medQ[i + 8] = 11;
                
            }
            if (inBin[i] == 0 && inBin[i + 1] == 1 && inBin[i + 2] == 1 && inBin[i + 3] == 0 && inBin[i + 4] == 1 && inBin[i + 5] == 0 && inBin[i + 6] == 0 && inBin[i + 7] == 1)
            {
                medI[i + 8] = 11;
                medQ[i + 8] = 11;
                
            }
            if (inBin[i] == 0 && inBin[i + 1] == 1 && inBin[i + 2] == 1 && inBin[i + 3] == 0 && inBin[i + 4] == 1 && inBin[i + 5] == 0 && inBin[i + 6] == 1 && inBin[i + 7] == 0)
            {
                medI[i + 8] = 11;
                medQ[i + 8] = 9;
                
            }
            if (inBin[i] == 0 && inBin[i + 1] == 1 && inBin[i + 2] == 1 && inBin[i + 3] == 0 && inBin[i + 4] == 1 && inBin[i + 5] == 0 && inBin[i + 6] == 1 && inBin[i + 7] == 1)
            {
                medI[i + 8] = 11;
                medQ[i + 8] = 7;
                
            }
            if (inBin[i] == 0 && inBin[i + 1] == 1 && inBin[i + 2] == 1 && inBin[i + 3] == 0 && inBin[i + 4] == 1 && inBin[i + 5] == 1 && inBin[i + 6] == 0 && inBin[i + 7] == 0)
            {
                medI[i + 8] = 11;
                medQ[i + 8] = 5;
                
            }
            if (inBin[i] == 0 && inBin[i + 1] == 1 && inBin[i + 2] == 1 && inBin[i + 3] == 0 && inBin[i + 4] == 1 && inBin[i + 5] == 1 && inBin[i + 6] == 0 && inBin[i + 7] == 1)
            {
                medI[i + 8] = 11;
                medQ[i + 8] = 3;
                
            }
            if (inBin[i] == 0 && inBin[i + 1] == 1 && inBin[i + 2] == 1 && inBin[i + 3] == 0 && inBin[i + 4] == 1 && inBin[i + 5] == 1 && inBin[i + 6] == 1 && inBin[i + 7] == 0)
            {
                medI[i + 8] = 11;
                medQ[i + 8] = 1;
                
            }
            if (inBin[i] == 0 && inBin[i + 1] == 1 && inBin[i + 2] == 1 && inBin[i + 3] == 0 && inBin[i + 4] == 1 && inBin[i + 5] == 1 && inBin[i + 6] == 1 && inBin[i + 7] == 1)
            {
                medI[i + 8] = 11;
                medQ[i + 8] = -1;
                
            }
            if (inBin[i] == 0 && inBin[i + 1] == 1 && inBin[i + 2] == 1 && inBin[i + 3] == 1 && inBin[i + 4] == 0 && inBin[i + 5] == 0 && inBin[i + 6] == 0 && inBin[i + 7] == 0)
            {
                medI[i + 8] = 11;
                medQ[i + 8] = -3;
                
            }
            if (inBin[i] == 0 && inBin[i + 1] == 1 && inBin[i + 2] == 1 && inBin[i + 3] == 1 && inBin[i + 4] == 0 && inBin[i + 5] == 0 && inBin[i + 6] == 0 && inBin[i + 7] == 1)
            {
                medI[i + 8] = 11;
                medQ[i + 8] = -5;
                
            }
            if (inBin[i] == 0 && inBin[i + 1] == 1 && inBin[i + 2] == 1 && inBin[i + 3] == 1 && inBin[i + 4] == 0 && inBin[i + 5] == 0 && inBin[i + 6] == 1 && inBin[i + 7] == 0)
            {
                medI[i + 8] = 11;
                medQ[i + 8] = -7;
                
            }
            if (inBin[i] == 0 && inBin[i + 1] == 1 && inBin[i + 2] == 1 && inBin[i + 3] == 1 && inBin[i + 4] == 0 && inBin[i + 5] == 0 && inBin[i + 6] == 1 && inBin[i + 7] == 1)
            {
                medI[i + 8] = 11;
                medQ[i + 8] = -9;
                
            }
            if (inBin[i] == 0 && inBin[i + 1] == 1 && inBin[i + 2] == 1 && inBin[i + 3] == 1 && inBin[i + 4] == 0 && inBin[i + 5] == 1 && inBin[i + 6] == 0 && inBin[i + 7] == 0)
            {
                medI[i + 8] = 11;
                medQ[i + 8] = -11;
                
            }
            if (inBin[i] == 0 && inBin[i + 1] == 1 && inBin[i + 2] == 1 && inBin[i + 3] == 1 && inBin[i + 4] == 0 && inBin[i + 5] == 1 && inBin[i + 6] == 0 && inBin[i + 7] == 1)
            {
                medI[i + 8] = 9;
                medQ[i + 8] = -11;
                
            }
            if (inBin[i] == 0 && inBin[i + 1] == 1 && inBin[i + 2] == 1 && inBin[i + 3] == 1 && inBin[i + 4] == 0 && inBin[i + 5] == 1 && inBin[i + 6] == 1 && inBin[i + 7] == 0)
            {
                medI[i + 8] = 7;
                medQ[i + 8] = -11;
                
            }
            if (inBin[i] == 0 && inBin[i + 1] == 1 && inBin[i + 2] == 1 && inBin[i + 3] == 1 && inBin[i + 4] == 0 && inBin[i + 5] == 1 && inBin[i + 6] == 1 && inBin[i + 7] == 1)
            {
                medI[i + 8] = 5;
                medQ[i + 8] = -11;
                
            }
            if (inBin[i] == 0 && inBin[i + 1] == 1 && inBin[i + 2] == 1 && inBin[i + 3] == 1 && inBin[i + 4] == 1 && inBin[i + 5] == 0 && inBin[i + 6] == 0 && inBin[i + 7] == 0)
            {
                medI[i + 8] = 3;
                medQ[i + 8] = -11;
                
            }
            if (inBin[i] == 0 && inBin[i + 1] == 1 && inBin[i + 2] == 1 && inBin[i + 3] == 1 && inBin[i + 4] == 1 && inBin[i + 5] == 0 && inBin[i + 6] == 0 && inBin[i + 7] == 1)
            {
                medI[i + 8] = 1;
                medQ[i + 8] = -11;
                
            }
            if (inBin[i] == 0 && inBin[i + 1] == 1 && inBin[i + 2] == 1 && inBin[i + 3] == 1 && inBin[i + 4] == 1 && inBin[i + 5] == 0 && inBin[i + 6] == 1 && inBin[i + 7] == 0)
            {
                medI[i + 8] = -1;
                medQ[i + 8] = -11;
                
            }
            if (inBin[i] == 0 && inBin[i + 1] == 1 && inBin[i + 2] == 1 && inBin[i + 3] == 1 && inBin[i + 4] == 1 && inBin[i + 5] == 0 && inBin[i + 6] == 1 && inBin[i + 7] == 1)
            {
                medI[i + 8] = -3;
                medQ[i + 8] = -11;
                
            }
            if (inBin[i] == 0 && inBin[i + 1] == 1 && inBin[i + 2] == 1 && inBin[i + 3] == 1 && inBin[i + 4] == 1 && inBin[i + 5] == 1 && inBin[i + 6] == 0 && inBin[i + 7] == 0)
            {
                medI[i + 8] = -5;
                medQ[i + 8] = -11;
                
            }
            if (inBin[i] == 0 && inBin[i + 1] == 1 && inBin[i + 2] == 1 && inBin[i + 3] == 1 && inBin[i + 4] == 1 && inBin[i + 5] == 1 && inBin[i + 6] == 0 && inBin[i + 7] == 1)
            {
                medI[i + 8] = -7;
                medQ[i + 8] = -11;
                
            }
            if (inBin[i] == 0 && inBin[i + 1] == 1 && inBin[i + 2] == 1 && inBin[i + 3] == 1 && inBin[i + 4] == 1 && inBin[i + 5] == 1 && inBin[i + 6] == 1 && inBin[i + 7] == 0)
            {
                medI[i + 8] = -9;
                medQ[i + 8] = -11;
                
            }
            if (inBin[i] == 0 && inBin[i + 1] == 1 && inBin[i + 2] == 1 && inBin[i + 3] == 1 && inBin[i + 4] == 1 && inBin[i + 5] == 1 && inBin[i + 6] == 1 && inBin[i + 7] == 1)
            {
                medI[i + 8] = -11;
                medQ[i + 8] = -11;
                
            }
            if (inBin[i] == 1 && inBin[i + 1] == 0 && inBin[i + 2] == 0 && inBin[i + 3] == 0 && inBin[i + 4] == 0 && inBin[i + 5] == 0 && inBin[i + 6] == 0 && inBin[i + 7] == 0)
            {
                medI[i + 8] = -11;
                medQ[i + 8] = -9;
                
            }
            if (inBin[i] == 1 && inBin[i + 1] == 0 && inBin[i + 2] == 0 && inBin[i + 3] == 0 && inBin[i + 4] == 0 && inBin[i + 5] == 0 && inBin[i + 6] == 0 && inBin[i + 7] == 1)
            {
                medI[i + 8] = -11;
                medQ[i + 8] = -7;
                
            }
            if (inBin[i] == 1 && inBin[i + 1] == 0 && inBin[i + 2] == 0 && inBin[i + 3] == 0 && inBin[i + 4] == 0 && inBin[i + 5] == 0 && inBin[i + 6] == 1 && inBin[i + 7] == 0)
            {
                medI[i + 8] = -11;
                medQ[i + 8] = -5;
                
            }
            if (inBin[i] == 1 && inBin[i + 1] == 0 && inBin[i + 2] == 0 && inBin[i + 3] == 0 && inBin[i + 4] == 0 && inBin[i + 5] == 0 && inBin[i + 6] == 1 && inBin[i + 7] == 1)
            {
                medI[i + 8] = -11;
                medQ[i + 8] = -3;
                
            }
            if (inBin[i] == 1 && inBin[i + 1] == 0 && inBin[i + 2] == 0 && inBin[i + 3] == 0 && inBin[i + 4] == 0 && inBin[i + 5] == 1 && inBin[i + 6] == 0 && inBin[i + 7] == 0)
            {
                medI[i + 8] = -11;
                medQ[i + 8] = -1;
                
            }
            if (inBin[i] == 1 && inBin[i + 1] == 0 && inBin[i + 2] == 0 && inBin[i + 3] == 0 && inBin[i + 4] == 0 && inBin[i + 5] == 1 && inBin[i + 6] == 0 && inBin[i + 7] == 1)
            {
                medI[i + 8] = -11;
                medQ[i + 8] = 1;
                
            }
            if (inBin[i] == 1 && inBin[i + 1] == 0 && inBin[i + 2] == 0 && inBin[i + 3] == 0 && inBin[i + 4] == 0 && inBin[i + 5] == 1 && inBin[i + 6] == 1 && inBin[i + 7] == 0)
            {
                medI[i + 8] = -11;
                medQ[i + 8] = 3;
                
            }
            if (inBin[i] == 1 && inBin[i + 1] == 0 && inBin[i + 2] == 0 && inBin[i + 3] == 0 && inBin[i + 4] == 0 && inBin[i + 5] == 1 && inBin[i + 6] == 1 && inBin[i + 7] == 1)
            {
                medI[i + 8] = -11;
                medQ[i + 8] = 5;
                
            }
            if (inBin[i] == 1 && inBin[i + 1] == 0 && inBin[i + 2] == 0 && inBin[i + 3] == 0 && inBin[i + 4] == 1 && inBin[i + 5] == 0 && inBin[i + 6] == 0 && inBin[i + 7] == 0)
            {
                medI[i + 8] = -11;
                medQ[i + 8] = 7;
                
            }
            if (inBin[i] == 1 && inBin[i + 1] == 0 && inBin[i + 2] == 0 && inBin[i + 3] == 0 && inBin[i + 4] == 1 && inBin[i + 5] == 0 && inBin[i + 6] == 0 && inBin[i + 7] == 1)
            {
                medI[i + 8] = -11;
                medQ[i + 8] = 9;
                
            }
            if (inBin[i] == 1 && inBin[i + 1] == 0 && inBin[i + 2] == 0 && inBin[i + 3] == 0 && inBin[i + 4] == 1 && inBin[i + 5] == 0 && inBin[i + 6] == 1 && inBin[i + 7] == 0)
            {
                medI[i + 8] = -11;
                medQ[i + 8] = 11;
                
            }
            if (inBin[i] == 1 && inBin[i + 1] == 0 && inBin[i + 2] == 0 && inBin[i + 3] == 0 && inBin[i + 4] == 1 && inBin[i + 5] == 0 && inBin[i + 6] == 1 && inBin[i + 7] == 1)
            {
                medI[i + 8] = -9;
                medQ[i + 8] = 11;
                
            }
            if (inBin[i] == 1 && inBin[i + 1] == 0 && inBin[i + 2] == 0 && inBin[i + 3] == 0 && inBin[i + 4] == 1 && inBin[i + 5] == 1 && inBin[i + 6] == 0 && inBin[i + 7] == 0)
            {
                medI[i + 8] = -7;
                medQ[i + 8] = 11;
                
            }
            if (inBin[i] == 1 && inBin[i + 1] == 0 && inBin[i + 2] == 0 && inBin[i + 3] == 0 && inBin[i + 4] == 1 && inBin[i + 5] == 1 && inBin[i + 6] == 0 && inBin[i + 7] == 1)
            {
                medI[i + 8] = -5;
                medQ[i + 8] = 11;
                
            }
            if (inBin[i] == 1 && inBin[i + 1] == 0 && inBin[i + 2] == 0 && inBin[i + 3] == 0 && inBin[i + 4] == 1 && inBin[i + 5] == 1 && inBin[i + 6] == 1 && inBin[i + 7] == 0)
            {
                medI[i + 8] = -3;
                medQ[i + 8] = 11;
                
            }
            if (inBin[i] == 1 && inBin[i + 1] == 0 && inBin[i + 2] == 0 && inBin[i + 3] == 0 && inBin[i + 4] == 1 && inBin[i + 5] == 1 && inBin[i + 6] == 1 && inBin[i + 7] == 1)
            {
                medI[i + 8] = -1;
                medQ[i + 8] = 11;
                
            }
            if (inBin[i] == 1 && inBin[i + 1] == 0 && inBin[i + 2] == 0 && inBin[i + 3] == 1 && inBin[i + 4] == 0 && inBin[i + 5] == 0 && inBin[i + 6] == 0 && inBin[i + 7] == 0)
            {
                medI[i + 8] = 1;
                medQ[i + 8] = 13;
                
            }
            if (inBin[i] == 1 && inBin[i + 1] == 0 && inBin[i + 2] == 0 && inBin[i + 3] == 1 && inBin[i + 4] == 0 && inBin[i + 5] == 0 && inBin[i + 6] == 0 && inBin[i + 7] == 1)
            {
                medI[i + 8] = 3;
                medQ[i + 8] = 13;
                
            }
            if (inBin[i] == 1 && inBin[i + 1] == 0 && inBin[i + 2] == 0 && inBin[i + 3] == 1 && inBin[i + 4] == 0 && inBin[i + 5] == 0 && inBin[i + 6] == 1 && inBin[i + 7] == 0)
            {
                medI[i + 8] = 5;
                medQ[i + 8] = 13;
                
            }
            if (inBin[i] == 1 && inBin[i + 1] == 0 && inBin[i + 2] == 0 && inBin[i + 3] == 1 && inBin[i + 4] == 0 && inBin[i + 5] == 0 && inBin[i + 6] == 1 && inBin[i + 7] == 1)
            {
                medI[i + 8] = 7;
                medQ[i + 8] = 13;
                
            }
            if (inBin[i] == 1 && inBin[i + 1] == 0 && inBin[i + 2] == 0 && inBin[i + 3] == 1 && inBin[i + 4] == 0 && inBin[i + 5] == 1 && inBin[i + 6] == 0 && inBin[i + 7] == 0)
            {
                medI[i + 8] = 9;
                medQ[i + 8] = 13;
                
            }
            if (inBin[i] == 1 && inBin[i + 1] == 0 && inBin[i + 2] == 0 && inBin[i + 3] == 1 && inBin[i + 4] == 0 && inBin[i + 5] == 1 && inBin[i + 6] == 0 && inBin[i + 7] == 1)
            {
                medI[i + 8] = 11;
                medQ[i + 8] = 13;
                
            }
            if (inBin[i] == 1 && inBin[i + 1] == 0 && inBin[i + 2] == 0 && inBin[i + 3] == 1 && inBin[i + 4] == 0 && inBin[i + 5] == 1 && inBin[i + 6] == 1 && inBin[i + 7] == 0)
            {
                medI[i + 8] = 13;
                medQ[i + 8] = 13;
                
            }
            if (inBin[i] == 1 && inBin[i + 1] == 0 && inBin[i + 2] == 0 && inBin[i + 3] == 1 && inBin[i + 4] == 0 && inBin[i + 5] == 1 && inBin[i + 6] == 1 && inBin[i + 7] == 1)
            {
                medI[i + 8] = 13;
                medQ[i + 8] = 11;
                
            }
            if (inBin[i] == 1 && inBin[i + 1] == 0 && inBin[i + 2] == 0 && inBin[i + 3] == 1 && inBin[i + 4] == 1 && inBin[i + 5] == 0 && inBin[i + 6] == 0 && inBin[i + 7] == 0)
            {
                medI[i + 8] = 13;
                medQ[i + 8] = 9;
                
            }
            if (inBin[i] == 1 && inBin[i + 1] == 0 && inBin[i + 2] == 0 && inBin[i + 3] == 1 && inBin[i + 4] == 1 && inBin[i + 5] == 0 && inBin[i + 6] == 0 && inBin[i + 7] == 1)
            {
                medI[i + 8] = 13;
                medQ[i + 8] = 7;
                
            }
            if (inBin[i] == 1 && inBin[i + 1] == 0 && inBin[i + 2] == 0 && inBin[i + 3] == 1 && inBin[i + 4] == 1 && inBin[i + 5] == 0 && inBin[i + 6] == 1 && inBin[i + 7] == 0)
            {
                medI[i + 8] = 13;
                medQ[i + 8] = 5;
                
            }
            if (inBin[i] == 1 && inBin[i + 1] == 0 && inBin[i + 2] == 0 && inBin[i + 3] == 1 && inBin[i + 4] == 1 && inBin[i + 5] == 0 && inBin[i + 6] == 1 && inBin[i + 7] == 1)
            {
                medI[i + 8] = 13;
                medQ[i + 8] = 3;
                
            }
            if (inBin[i] == 1 && inBin[i + 1] == 0 && inBin[i + 2] == 0 && inBin[i + 3] == 1 && inBin[i + 4] == 1 && inBin[i + 5] == 1 && inBin[i + 6] == 0 && inBin[i + 7] == 0)
            {
                medI[i + 8] = 13;
                medQ[i + 8] = 1;
                
            }
            if (inBin[i] == 1 && inBin[i + 1] == 0 && inBin[i + 2] == 0 && inBin[i + 3] == 1 && inBin[i + 4] == 1 && inBin[i + 5] == 1 && inBin[i + 6] == 0 && inBin[i + 7] == 1)
            {
                medI[i + 8] = 13;
                medQ[i + 8] = -1;
                
            }
            if (inBin[i] == 1 && inBin[i + 1] == 0 && inBin[i + 2] == 0 && inBin[i + 3] == 1 && inBin[i + 4] == 1 && inBin[i + 5] == 1 && inBin[i + 6] == 1 && inBin[i + 7] == 0)
            {
                medI[i + 8] = 13;
                medQ[i + 8] = -3;
                
            }
            if (inBin[i] == 1 && inBin[i + 1] == 0 && inBin[i + 2] == 0 && inBin[i + 3] == 1 && inBin[i + 4] == 1 && inBin[i + 5] == 1 && inBin[i + 6] == 1 && inBin[i + 7] == 1)
            {
                medI[i + 8] = 13;
                medQ[i + 8] = -5;
                
            }
            if (inBin[i] == 1 && inBin[i + 1] == 0 && inBin[i + 2] == 1 && inBin[i + 3] == 0 && inBin[i + 4] == 0 && inBin[i + 5] == 0 && inBin[i + 6] == 0 && inBin[i + 7] == 0)
            {
                medI[i + 8] = 13;
                medQ[i + 8] = -7;
                
            }
            if (inBin[i] == 1 && inBin[i + 1] == 0 && inBin[i + 2] == 1 && inBin[i + 3] == 0 && inBin[i + 4] == 0 && inBin[i + 5] == 0 && inBin[i + 6] == 0 && inBin[i + 7] == 1)
            {
                medI[i + 8] = 13;
                medQ[i + 8] = -9;
                
            }
            if (inBin[i] == 1 && inBin[i + 1] == 0 && inBin[i + 2] == 1 && inBin[i + 3] == 0 && inBin[i + 4] == 0 && inBin[i + 5] == 0 && inBin[i + 6] == 1 && inBin[i + 7] == 0)
            {
                medI[i + 8] = 13;
                medQ[i + 8] = -11;
                
            }
            if (inBin[i] == 1 && inBin[i + 1] == 0 && inBin[i + 2] == 1 && inBin[i + 3] == 0 && inBin[i + 4] == 0 && inBin[i + 5] == 0 && inBin[i + 6] == 1 && inBin[i + 7] == 1)
            {
                medI[i + 8] = 13;
                medQ[i + 8] = -13;
                
            }
            if (inBin[i] == 1 && inBin[i + 1] == 0 && inBin[i + 2] == 1 && inBin[i + 3] == 0 && inBin[i + 4] == 0 && inBin[i + 5] == 1 && inBin[i + 6] == 0 && inBin[i + 7] == 0)
            {
                medI[i + 8] = 11;
                medQ[i + 8] = -13;
                
            }
            if (inBin[i] == 1 && inBin[i + 1] == 0 && inBin[i + 2] == 1 && inBin[i + 3] == 0 && inBin[i + 4] == 0 && inBin[i + 5] == 1 && inBin[i + 6] == 0 && inBin[i + 7] == 1)
            {
                medI[i + 8] = 9;
                medQ[i + 8] = -13;
                
            }
            if (inBin[i] == 1 && inBin[i + 1] == 0 && inBin[i + 2] == 1 && inBin[i + 3] == 0 && inBin[i + 4] == 0 && inBin[i + 5] == 1 && inBin[i + 6] == 1 && inBin[i + 7] == 0)
            {
                medI[i + 8] = 7;
                medQ[i + 8] = -13;
                
            }
            if (inBin[i] == 1 && inBin[i + 1] == 0 && inBin[i + 2] == 1 && inBin[i + 3] == 0 && inBin[i + 4] == 0 && inBin[i + 5] == 1 && inBin[i + 6] == 1 && inBin[i + 7] == 1)
            {
                medI[i + 8] = 5;
                medQ[i + 8] = -13;
                
            }
            if (inBin[i] == 1 && inBin[i + 1] == 0 && inBin[i + 2] == 1 && inBin[i + 3] == 0 && inBin[i + 4] == 1 && inBin[i + 5] == 0 && inBin[i + 6] == 0 && inBin[i + 7] == 0)
            {
                medI[i + 8] = 3;
                medQ[i + 8] = -13;
                
            }
            if (inBin[i] == 1 && inBin[i + 1] == 0 && inBin[i + 2] == 1 && inBin[i + 3] == 0 && inBin[i + 4] == 1 && inBin[i + 5] == 0 && inBin[i + 6] == 0 && inBin[i + 7] == 1)
            {
                medI[i + 8] = 1;
                medQ[i + 8] = -13;
                
            }
            if (inBin[i] == 1 && inBin[i + 1] == 0 && inBin[i + 2] == 1 && inBin[i + 3] == 0 && inBin[i + 4] == 1 && inBin[i + 5] == 0 && inBin[i + 6] == 1 && inBin[i + 7] == 0)
            {
                medI[i + 8] = -1;
                medQ[i + 8] = -13;
                
            }
            if (inBin[i] == 1 && inBin[i + 1] == 0 && inBin[i + 2] == 1 && inBin[i + 3] == 0 && inBin[i + 4] == 1 && inBin[i + 5] == 0 && inBin[i + 6] == 1 && inBin[i + 7] == 1)
            {
                medI[i + 8] = -3;
                medQ[i + 8] = -13;
                
            }
            if (inBin[i] == 1 && inBin[i + 1] == 0 && inBin[i + 2] == 1 && inBin[i + 3] == 0 && inBin[i + 4] == 1 && inBin[i + 5] == 1 && inBin[i + 6] == 0 && inBin[i + 7] == 0)
            {
                medI[i + 8] = -5;
                medQ[i + 8] = -13;
                
            }
            if (inBin[i] == 1 && inBin[i + 1] == 0 && inBin[i + 2] == 1 && inBin[i + 3] == 0 && inBin[i + 4] == 1 && inBin[i + 5] == 1 && inBin[i + 6] == 0 && inBin[i + 7] == 1)
            {
                medI[i + 8] = -7;
                medQ[i + 8] = -13;
                
            }
            if (inBin[i] == 1 && inBin[i + 1] == 0 && inBin[i + 2] == 1 && inBin[i + 3] == 0 && inBin[i + 4] == 1 && inBin[i + 5] == 1 && inBin[i + 6] == 1 && inBin[i + 7] == 0)
            {
                medI[i + 8] = -9;
                medQ[i + 8] = -13;
                
            }
            if (inBin[i] == 1 && inBin[i + 1] == 0 && inBin[i + 2] == 1 && inBin[i + 3] == 0 && inBin[i + 4] == 1 && inBin[i + 5] == 1 && inBin[i + 6] == 1 && inBin[i + 7] == 1)
            {
                medI[i + 8] = -11;
                medQ[i + 8] = -13;
                
            }
            if (inBin[i] == 1 && inBin[i + 1] == 0 && inBin[i + 2] == 1 && inBin[i + 3] == 1 && inBin[i + 4] == 0 && inBin[i + 5] == 0 && inBin[i + 6] == 0 && inBin[i + 7] == 0)
            {
                medI[i + 8] = -13;
                medQ[i + 8] = -13;
                
            }
            if (inBin[i] == 1 && inBin[i + 1] == 0 && inBin[i + 2] == 1 && inBin[i + 3] == 1 && inBin[i + 4] == 0 && inBin[i + 5] == 0 && inBin[i + 6] == 0 && inBin[i + 7] == 1)
            {
                medI[i + 8] = -13;
                medQ[i + 8] = -11;
                
            }
            if (inBin[i] == 1 && inBin[i + 1] == 0 && inBin[i + 2] == 1 && inBin[i + 3] == 1 && inBin[i + 4] == 0 && inBin[i + 5] == 0 && inBin[i + 6] == 1 && inBin[i + 7] == 0)
            {
                medI[i + 8] = -13;
                medQ[i + 8] = -9;
                
            }
            if (inBin[i] == 1 && inBin[i + 1] == 0 && inBin[i + 2] == 1 && inBin[i + 3] == 1 && inBin[i + 4] == 0 && inBin[i + 5] == 0 && inBin[i + 6] == 1 && inBin[i + 7] == 1)
            {
                medI[i + 8] = -13;
                medQ[i + 8] = -7;
                
            }
            if (inBin[i] == 1 && inBin[i + 1] == 0 && inBin[i + 2] == 1 && inBin[i + 3] == 1 && inBin[i + 4] == 0 && inBin[i + 5] == 1 && inBin[i + 6] == 0 && inBin[i + 7] == 0)
            {
                medI[i + 8] = -13;
                medQ[i + 8] = -5;
                
            }
            if (inBin[i] == 1 && inBin[i + 1] == 0 && inBin[i + 2] == 1 && inBin[i + 3] == 1 && inBin[i + 4] == 0 && inBin[i + 5] == 1 && inBin[i + 6] == 0 && inBin[i + 7] == 1)
            {
                medI[i + 8] = -13;
                medQ[i + 8] = -3;
                
            }
            if (inBin[i] == 1 && inBin[i + 1] == 0 && inBin[i + 2] == 1 && inBin[i + 3] == 1 && inBin[i + 4] == 0 && inBin[i + 5] == 1 && inBin[i + 6] == 1 && inBin[i + 7] == 0)
            {
                medI[i + 8] = -13;
                medQ[i + 8] = -1;
                
            }
            if (inBin[i] == 1 && inBin[i + 1] == 0 && inBin[i + 2] == 1 && inBin[i + 3] == 1 && inBin[i + 4] == 0 && inBin[i + 5] == 1 && inBin[i + 6] == 1 && inBin[i + 7] == 1)
            {
                medI[i + 8] = -13;
                medQ[i + 8] = 1;
                
            }
            if (inBin[i] == 1 && inBin[i + 1] == 0 && inBin[i + 2] == 1 && inBin[i + 3] == 1 && inBin[i + 4] == 1 && inBin[i + 5] == 0 && inBin[i + 6] == 0 && inBin[i + 7] == 0)
            {
                medI[i + 8] = -13;
                medQ[i + 8] = 3;
                
            }
            if (inBin[i] == 1 && inBin[i + 1] == 0 && inBin[i + 2] == 1 && inBin[i + 3] == 1 && inBin[i + 4] == 1 && inBin[i + 5] == 0 && inBin[i + 6] == 0 && inBin[i + 7] == 1)
            {
                medI[i + 8] = -13;
                medQ[i + 8] = 5;
                
            }
            if (inBin[i] == 1 && inBin[i + 1] == 0 && inBin[i + 2] == 1 && inBin[i + 3] == 1 && inBin[i + 4] == 1 && inBin[i + 5] == 0 && inBin[i + 6] == 1 && inBin[i + 7] == 0)
            {
                medI[i + 8] = -13;
                medQ[i + 8] = 7;
                
            }
            if (inBin[i] == 1 && inBin[i + 1] == 0 && inBin[i + 2] == 1 && inBin[i + 3] == 1 && inBin[i + 4] == 1 && inBin[i + 5] == 0 && inBin[i + 6] == 1 && inBin[i + 7] == 1)
            {
                medI[i + 8] = -13;
                medQ[i + 8] = 9;
                
            }
            if (inBin[i] == 1 && inBin[i + 1] == 0 && inBin[i + 2] == 1 && inBin[i + 3] == 1 && inBin[i + 4] == 1 && inBin[i + 5] == 1 && inBin[i + 6] == 0 && inBin[i + 7] == 0)
            {
                medI[i + 8] = -13;
                medQ[i + 8] = 11;
                
            }
            if (inBin[i] == 1 && inBin[i + 1] == 0 && inBin[i + 2] == 1 && inBin[i + 3] == 1 && inBin[i + 4] == 1 && inBin[i + 5] == 1 && inBin[i + 6] == 0 && inBin[i + 7] == 1)
            {

                medI[i + 8] = -13;
                medQ[i + 8] = 13;
                
            }
            if (inBin[i] == 1 && inBin[i + 1] == 0 && inBin[i + 2] == 1 && inBin[i + 3] == 1 && inBin[i + 4] == 1 && inBin[i + 5] == 1 && inBin[i + 6] == 1 && inBin[i + 7] == 0)
            {
                medI[i + 8] = -11;
                medQ[i + 8] = 13;
                
            }
            if (inBin[i] == 1 && inBin[i + 1] == 0 && inBin[i + 2] == 1 && inBin[i + 3] == 1 && inBin[i + 4] == 1 && inBin[i + 5] == 1 && inBin[i + 6] == 1 && inBin[i + 7] == 1)
            {
                medI[i + 8] = -9;
                medQ[i + 8] = 13;
                
            }
            if (inBin[i] == 1 && inBin[i + 1] == 1 && inBin[i + 2] == 0 && inBin[i + 3] == 0 && inBin[i + 4] == 0 && inBin[i + 5] == 0 && inBin[i + 6] == 0 && inBin[i + 7] == 0)
            {
                medI[i + 8] = -7;
                medQ[i + 8] = 13;
                
            }
            if (inBin[i] == 1 && inBin[i + 1] == 1 && inBin[i + 2] == 0 && inBin[i + 3] == 0 && inBin[i + 4] == 0 && inBin[i + 5] == 0 && inBin[i + 6] == 0 && inBin[i + 7] == 1)
            {
                medI[i + 8] = -5;
                medQ[i + 8] = 13;
                
            }
            if (inBin[i] == 1 && inBin[i + 1] == 1 && inBin[i + 2] == 0 && inBin[i + 3] == 0 && inBin[i + 4] == 0 && inBin[i + 5] == 0 && inBin[i + 6] == 1 && inBin[i + 7] == 0)
            {
                medI[i + 8] = -3;
                medQ[i + 8] = 13;
                
            }
            if (inBin[i] == 1 && inBin[i + 1] == 1 && inBin[i + 2] == 0 && inBin[i + 3] == 0 && inBin[i + 4] == 0 && inBin[i + 5] == 0 && inBin[i + 6] == 1 && inBin[i + 7] == 1)
            {
                medI[i + 8] = -1;
                medQ[i + 8] = 13;
                
            }
            if (inBin[i] == 1 && inBin[i + 1] == 1 && inBin[i + 2] == 0 && inBin[i + 3] == 0 && inBin[i + 4] == 0 && inBin[i + 5] == 1 && inBin[i + 6] == 0 && inBin[i + 7] == 0)
            {
                medI[i + 8] = 1;
                medQ[i + 8] = 15;
                
            }
            if (inBin[i] == 1 && inBin[i + 1] == 1 && inBin[i + 2] == 0 && inBin[i + 3] == 0 && inBin[i + 4] == 0 && inBin[i + 5] == 1 && inBin[i + 6] == 0 && inBin[i + 7] == 1)
            {
                medI[i + 8] = 3;
                medQ[i + 8] = 15;
                
            }
            if (inBin[i] == 1 && inBin[i + 1] == 1 && inBin[i + 2] == 0 && inBin[i + 3] == 0 && inBin[i + 4] == 0 && inBin[i + 5] == 1 && inBin[i + 6] == 1 && inBin[i + 7] == 0)
            {
                medI[i + 8] = 5;
                medQ[i + 8] = 15;
                
            }
            if (inBin[i] == 1 && inBin[i + 1] == 1 && inBin[i + 2] == 0 && inBin[i + 3] == 0 && inBin[i + 4] == 0 && inBin[i + 5] == 1 && inBin[i + 6] == 1 && inBin[i + 7] == 1)
            {
                medI[i + 8] = 7;
                medQ[i + 8] = 15;
                
            }
            if (inBin[i] == 1 && inBin[i + 1] == 1 && inBin[i + 2] == 0 && inBin[i + 3] == 0 && inBin[i + 4] == 1 && inBin[i + 5] == 0 && inBin[i + 6] == 0 && inBin[i + 7] == 0)
            {

                medI[i + 8] = 9;
                medQ[i + 8] = 15;
                
            }
            if (inBin[i] == 1 && inBin[i + 1] == 1 && inBin[i + 2] == 0 && inBin[i + 3] == 0 && inBin[i + 4] == 1 && inBin[i + 5] == 0 && inBin[i + 6] == 0 && inBin[i + 7] == 1)
            {
                medI[i + 8] = 11;
                medQ[i + 8] = 15;
                
            }
            if (inBin[i] == 1 && inBin[i + 1] == 1 && inBin[i + 2] == 0 && inBin[i + 3] == 0 && inBin[i + 4] == 1 && inBin[i + 5] == 0 && inBin[i + 6] == 1 && inBin[i + 7] == 0)
            {
                medI[i + 8] = 13;
                medQ[i + 8] = 15;
                
            }
            if (inBin[i] == 1 && inBin[i + 1] == 1 && inBin[i + 2] == 0 && inBin[i + 3] == 0 && inBin[i + 4] == 1 && inBin[i + 5] == 0 && inBin[i + 6] == 1 && inBin[i + 7] == 1)
            {
                medI[i + 8] = 15;
                medQ[i + 8] = 15;
                
            }
            if (inBin[i] == 1 && inBin[i + 1] == 1 && inBin[i + 2] == 0 && inBin[i + 3] == 0 && inBin[i + 4] == 1 && inBin[i + 5] == 1 && inBin[i + 6] == 0 && inBin[i + 7] == 0)
            {
                medI[i + 8] = 15;
                medQ[i + 8] = 13;
                
            }
            if (inBin[i] == 1 && inBin[i + 1] == 1 && inBin[i + 2] == 0 && inBin[i + 3] == 0 && inBin[i + 4] == 1 && inBin[i + 5] == 1 && inBin[i + 6] == 0 && inBin[i + 7] == 1)
            {
                medI[i + 8] = 15;
                medQ[i + 8] = 11;
                
            }
            if (inBin[i] == 1 && inBin[i + 1] == 1 && inBin[i + 2] == 0 && inBin[i + 3] == 0 && inBin[i + 4] == 1 && inBin[i + 5] == 1 && inBin[i + 6] == 1 && inBin[i + 7] == 0)
            {
                medI[i + 8] = 15;
                medQ[i + 8] = 9;
                
            }
            if (inBin[i] == 1 && inBin[i + 1] == 1 && inBin[i + 2] == 0 && inBin[i + 3] == 0 && inBin[i + 4] == 1 && inBin[i + 5] == 1 && inBin[i + 6] == 1 && inBin[i + 7] == 1)
            {
                medI[i + 8] = 15;
                medQ[i + 8] = 7;
                
            }
            if (inBin[i] == 1 && inBin[i + 1] == 1 && inBin[i + 2] == 0 && inBin[i + 3] == 1 && inBin[i + 4] == 0 && inBin[i + 5] == 0 && inBin[i + 6] == 0 && inBin[i + 7] == 0)
            {
                medI[i + 8] = 15;
                medQ[i + 8] = 5;
                
            }
            if (inBin[i] == 1 && inBin[i + 1] == 1 && inBin[i + 2] == 0 && inBin[i + 3] == 1 && inBin[i + 4] == 0 && inBin[i + 5] == 0 && inBin[i + 6] == 0 && inBin[i + 7] == 1)
            {
                medI[i + 8] = 15;
                medQ[i + 8] = 3;
                
            }
            if (inBin[i] == 1 && inBin[i + 1] == 1 && inBin[i + 2] == 0 && inBin[i + 3] == 1 && inBin[i + 4] == 0 && inBin[i + 5] == 0 && inBin[i + 6] == 1 && inBin[i + 7] == 0)
            {
                medI[i + 8] = 15;
                medQ[i + 8] = 1;
                
            }
            if (inBin[i] == 1 && inBin[i + 1] == 1 && inBin[i + 2] == 0 && inBin[i + 3] == 1 && inBin[i + 4] == 0 && inBin[i + 5] == 0 && inBin[i + 6] == 1 && inBin[i + 7] == 1)
            {
                medI[i + 8] = 15;
                medQ[i + 8] = -1;
                
            }
            if (inBin[i] == 1 && inBin[i + 1] == 1 && inBin[i + 2] == 0 && inBin[i + 3] == 1 && inBin[i + 4] == 0 && inBin[i + 5] == 1 && inBin[i + 6] == 0 && inBin[i + 7] == 0)
            {
                medI[i + 8] = 15;
                medQ[i + 8] = -3;
                
            }
            if (inBin[i] == 1 && inBin[i + 1] == 1 && inBin[i + 2] == 0 && inBin[i + 3] == 1 && inBin[i + 4] == 0 && inBin[i + 5] == 1 && inBin[i + 6] == 0 && inBin[i + 7] == 1)
            {
                medI[i + 8] = 15;
                medQ[i + 8] = -5;
                
            }
            if (inBin[i] == 1 && inBin[i + 1] == 1 && inBin[i + 2] == 0 && inBin[i + 3] == 1 && inBin[i + 4] == 0 && inBin[i + 5] == 1 && inBin[i + 6] == 1 && inBin[i + 7] == 0)
            {
                medI[i + 8] = 15;
                medQ[i + 8] = -7;
                
            }
            if (inBin[i] == 1 && inBin[i + 1] == 1 && inBin[i + 2] == 0 && inBin[i + 3] == 1 && inBin[i + 4] == 0 && inBin[i + 5] == 1 && inBin[i + 6] == 1 && inBin[i + 7] == 1)
            {
                medI[i + 8] = 15;
                medQ[i + 8] = -9;
                
            }
            if (inBin[i] == 1 && inBin[i + 1] == 1 && inBin[i + 2] == 0 && inBin[i + 3] == 1 && inBin[i + 4] == 1 && inBin[i + 5] == 0 && inBin[i + 6] == 0 && inBin[i + 7] == 0)
            {
                medI[i + 8] = 15;
                medQ[i + 8] = -11;
                
            }
            if (inBin[i] == 1 && inBin[i + 1] == 1 && inBin[i + 2] == 0 && inBin[i + 3] == 1 && inBin[i + 4] == 1 && inBin[i + 5] == 0 && inBin[i + 6] == 0 && inBin[i + 7] == 1)
            {
                medI[i + 8] = 15;
                medQ[i + 8] = -13;
                
            }
            if (inBin[i] == 1 && inBin[i + 1] == 1 && inBin[i + 2] == 0 && inBin[i + 3] == 1 && inBin[i + 4] == 1 && inBin[i + 5] == 0 && inBin[i + 6] == 1 && inBin[i + 7] == 0)
            {
                medI[i + 8] = 15;
                medQ[i + 8] = -15;
                
            }
            if (inBin[i] == 1 && inBin[i + 1] == 1 && inBin[i + 2] == 0 && inBin[i + 3] == 1 && inBin[i + 4] == 1 && inBin[i + 5] == 0 && inBin[i + 6] == 1 && inBin[i + 7] == 1)
            {
                medI[i + 8] = 13;
                medQ[i + 8] = -15;
                
            }
            if (inBin[i] == 1 && inBin[i + 1] == 1 && inBin[i + 2] == 0 && inBin[i + 3] == 1 && inBin[i + 4] == 1 && inBin[i + 5] == 1 && inBin[i + 6] == 0 && inBin[i + 7] == 0)
            {
                medI[i + 8] = 11;
                medQ[i + 8] = -15;
                
            }
            if (inBin[i] == 1 && inBin[i + 1] == 1 && inBin[i + 2] == 0 && inBin[i + 3] == 1 && inBin[i + 4] == 1 && inBin[i + 5] == 1 && inBin[i + 6] == 0 && inBin[i + 7] == 1)
            {
                medI[i + 8] = 9;
                medQ[i + 8] = -15;
                
            }
            if (inBin[i] == 1 && inBin[i + 1] == 1 && inBin[i + 2] == 0 && inBin[i + 3] == 1 && inBin[i + 4] == 1 && inBin[i + 5] == 1 && inBin[i + 6] == 1 && inBin[i + 7] == 0)
            {
                medI[i + 8] = 7;
                medQ[i + 8] = -15;
                
            }
            if (inBin[i] == 1 && inBin[i + 1] == 1 && inBin[i + 2] == 0 && inBin[i + 3] == 1 && inBin[i + 4] == 1 && inBin[i + 5] == 1 && inBin[i + 6] == 1 && inBin[i + 7] == 1)
            {
                medI[i + 8] = 5;
                medQ[i + 8] = -15;
                
            }
            if (inBin[i] == 1 && inBin[i + 1] == 1 && inBin[i + 2] == 1 && inBin[i + 3] == 0 && inBin[i + 4] == 0 && inBin[i + 5] == 0 && inBin[i + 6] == 0 && inBin[i + 7] == 0)
            {
                medI[i + 8] = 3;
                medQ[i + 8] = -15;
                
            }
            if (inBin[i] == 1 && inBin[i + 1] == 1 && inBin[i + 2] == 1 && inBin[i + 3] == 0 && inBin[i + 4] == 0 && inBin[i + 5] == 0 && inBin[i + 6] == 0 && inBin[i + 7] == 1)
            {
                medI[i + 8] = 1;
                medQ[i + 8] = -15;
                
            }
            if (inBin[i] == 1 && inBin[i + 1] == 1 && inBin[i + 2] == 1 && inBin[i + 3] == 0 && inBin[i + 4] == 0 && inBin[i + 5] == 0 && inBin[i + 6] == 1 && inBin[i + 7] == 0)
            {
                medI[i + 8] = -1;
                medQ[i + 8] = -15;
                
            }
            if (inBin[i] == 1 && inBin[i + 1] == 1 && inBin[i + 2] == 1 && inBin[i + 3] == 0 && inBin[i + 4] == 0 && inBin[i + 5] == 0 && inBin[i + 6] == 1 && inBin[i + 7] == 1)
            {
                medI[i + 8] = -3;
                medQ[i + 8] = -15;
                
            }
            if (inBin[i] == 1 && inBin[i + 1] == 1 && inBin[i + 2] == 1 && inBin[i + 3] == 0 && inBin[i + 4] == 0 && inBin[i + 5] == 1 && inBin[i + 6] == 0 && inBin[i + 7] == 0)
            {
                medI[i + 8] = -5;
                medQ[i + 8] = -15;
                
            }
            if (inBin[i] == 1 && inBin[i + 1] == 1 && inBin[i + 2] == 1 && inBin[i + 3] == 0 && inBin[i + 4] == 0 && inBin[i + 5] == 1 && inBin[i + 6] == 0 && inBin[i + 7] == 1)
            {
                medI[i + 8] = -7;
                medQ[i + 8] = -15;
                
            }
            if (inBin[i] == 1 && inBin[i + 1] == 1 && inBin[i + 2] == 1 && inBin[i + 3] == 0 && inBin[i + 4] == 0 && inBin[i + 5] == 1 && inBin[i + 6] == 1 && inBin[i + 7] == 0)
            {
                medI[i + 8] = -9;
                medQ[i + 8] = -15;
                
            }
            if (inBin[i] == 1 && inBin[i + 1] == 1 && inBin[i + 2] == 1 && inBin[i + 3] == 0 && inBin[i + 4] == 0 && inBin[i + 5] == 1 && inBin[i + 6] == 1 && inBin[i + 7] == 1)
            {
                medI[i + 8] = -11;
                medQ[i + 8] = -15;
                
            }
            if (inBin[i] == 1 && inBin[i + 1] == 1 && inBin[i + 2] == 1 && inBin[i + 3] == 0 && inBin[i + 4] == 1 && inBin[i + 5] == 0 && inBin[i + 6] == 0 && inBin[i + 7] == 0)
            {
                medI[i + 8] = -13;
                medQ[i + 8] = -15;
                
            }
            if (inBin[i] == 1 && inBin[i + 1] == 1 && inBin[i + 2] == 1 && inBin[i + 3] == 0 && inBin[i + 4] == 1 && inBin[i + 5] == 0 && inBin[i + 6] == 0 && inBin[i + 7] == 1)
            {
                medI[i + 8] = -15;
                medQ[i + 8] = -15;
                
            }
            if (inBin[i] == 1 && inBin[i + 1] == 1 && inBin[i + 2] == 1 && inBin[i + 3] == 0 && inBin[i + 4] == 1 && inBin[i + 5] == 0 && inBin[i + 6] == 1 && inBin[i + 7] == 0)
            {
                medI[i + 8] = -15;
                medQ[i + 8] = -13;
                
            }
            if (inBin[i] == 1 && inBin[i + 1] == 1 && inBin[i + 2] == 1 && inBin[i + 3] == 0 && inBin[i + 4] == 1 && inBin[i + 5] == 0 && inBin[i + 6] == 1 && inBin[i + 7] == 1)
            {
                medI[i + 8] = -15;
                medQ[i + 8] = -11;
                
            }
            if (inBin[i] == 1 && inBin[i + 1] == 1 && inBin[i + 2] == 1 && inBin[i + 3] == 0 && inBin[i + 4] == 1 && inBin[i + 5] == 1 && inBin[i + 6] == 0 && inBin[i + 7] == 0)
            {
                medI[i + 8] = -15;
                medQ[i + 8] = -9;
                
            }
            if (inBin[i] == 1 && inBin[i + 1] == 1 && inBin[i + 2] == 1 && inBin[i + 3] == 0 && inBin[i + 4] == 1 && inBin[i + 5] == 1 && inBin[i + 6] == 0 && inBin[i + 7] == 1)
            {
                medI[i + 8] = -15;
                medQ[i + 8] = -7;
                
            }
            if (inBin[i] == 1 && inBin[i + 1] == 1 && inBin[i + 2] == 1 && inBin[i + 3] == 0 && inBin[i + 4] == 1 && inBin[i + 5] == 1 && inBin[i + 6] == 1 && inBin[i + 7] == 0)
            {
                medI[i + 8] = -15;
                medQ[i + 8] = -5;
                
            }
            if (inBin[i] == 1 && inBin[i + 1] == 1 && inBin[i + 2] == 1 && inBin[i + 3] == 0 && inBin[i + 4] == 1 && inBin[i + 5] == 1 && inBin[i + 6] == 1 && inBin[i + 7] == 1)
            {
                medI[i + 8] = -15;
                medQ[i + 8] = -3;
                
            }
            if (inBin[i] == 1 && inBin[i + 1] == 1 && inBin[i + 2] == 1 && inBin[i + 3] == 1 && inBin[i + 4] == 0 && inBin[i + 5] == 0 && inBin[i + 6] == 0 && inBin[i + 7] == 0)
            {
                medI[i + 8] = -15;
                medQ[i + 8] = -1;
                
            }
            if (inBin[i] == 1 && inBin[i + 1] == 1 && inBin[i + 2] == 1 && inBin[i + 3] == 1 && inBin[i + 4] == 0 && inBin[i + 5] == 0 && inBin[i + 6] == 0 && inBin[i + 7] == 1)
            {
                medI[i + 8] = -15;
                medQ[i + 8] = 1;
                
            }
            if (inBin[i] == 1 && inBin[i + 1] == 1 && inBin[i + 2] == 1 && inBin[i + 3] == 1 && inBin[i + 4] == 0 && inBin[i + 5] == 0 && inBin[i + 6] == 1 && inBin[i + 7] == 0)
            {
                medI[i + 8] = -15;
                medQ[i + 8] = 3;
                
            }
            if (inBin[i] == 1 && inBin[i + 1] == 1 && inBin[i + 2] == 1 && inBin[i + 3] == 1 && inBin[i + 4] == 0 && inBin[i + 5] == 0 && inBin[i + 6] == 1 && inBin[i + 7] == 1)
            {
                medI[i + 8] = -15;
                medQ[i + 8] = 5;
                
            }
            if (inBin[i] == 1 && inBin[i + 1] == 1 && inBin[i + 2] == 1 && inBin[i + 3] == 1 && inBin[i + 4] == 0 && inBin[i + 5] == 1 && inBin[i + 6] == 0 && inBin[i + 7] == 0)
            {
                medI[i + 8] = -15;
                medQ[i + 8] = 7;
                
            }
            if (inBin[i] == 1 && inBin[i + 1] == 1 && inBin[i + 2] == 1 && inBin[i + 3] == 1 && inBin[i + 4] == 0 && inBin[i + 5] == 1 && inBin[i + 6] == 0 && inBin[i + 7] == 1)
            {
                medI[i + 8] = -15;
                medQ[i + 8] = 9;
                
            }
            if (inBin[i] == 1 && inBin[i + 1] == 1 && inBin[i + 2] == 1 && inBin[i + 3] == 1 && inBin[i + 4] == 0 && inBin[i + 5] == 1 && inBin[i + 6] == 1 && inBin[i + 7] == 0)
            {
                medI[i + 8] = -15;
                medQ[i + 8] = 11;
                
            }
            if (inBin[i] == 1 && inBin[i + 1] == 1 && inBin[i + 2] == 1 && inBin[i + 3] == 1 && inBin[i + 4] == 0 && inBin[i + 5] == 1 && inBin[i + 6] == 1 && inBin[i + 7] == 1)
            {
                medI[i + 8] = -15;
                medQ[i + 8] = 13;
                
            }
            if (inBin[i] == 1 && inBin[i + 1] == 1 && inBin[i + 2] == 1 && inBin[i + 3] == 1 && inBin[i + 4] == 1 && inBin[i + 5] == 0 && inBin[i + 6] == 0 && inBin[i + 7] == 0)
            {
                medI[i + 8] = -15;
                medQ[i + 8] = 15;
                
            }
            if (inBin[i] == 1 && inBin[i + 1] == 1 && inBin[i + 2] == 1 && inBin[i + 3] == 1 && inBin[i + 4] == 1 && inBin[i + 5] == 0 && inBin[i + 6] == 0 && inBin[i + 7] == 1)
            {
                medI[i + 8] = -13;
                medQ[i + 8] = 15;
                
            }
            if (inBin[i] == 1 && inBin[i + 1] == 1 && inBin[i + 2] == 1 && inBin[i + 3] == 1 && inBin[i + 4] == 1 && inBin[i + 5] == 0 && inBin[i + 6] == 1 && inBin[i + 7] == 0)
            {
                medI[i + 8] = -11;
                medQ[i + 8] = 15;
                
            }
            if (inBin[i] == 1 && inBin[i + 1] == 1 && inBin[i + 2] == 1 && inBin[i + 3] == 1 && inBin[i + 4] == 1 && inBin[i + 5] == 0 && inBin[i + 6] == 1 && inBin[i + 7] == 1)
            {
                medI[i + 8] = -9;
                medQ[i + 8] = 15;
                
            }
            if (inBin[i] == 1 && inBin[i + 1] == 1 && inBin[i + 2] == 1 && inBin[i + 3] == 1 && inBin[i + 4] == 1 && inBin[i + 5] == 1 && inBin[i + 6] == 0 && inBin[i + 7] == 0)
            {
                medI[i + 8] = -7;
                medQ[i + 8] = 15;
                
            }
            if (inBin[i] == 1 && inBin[i + 1] == 1 && inBin[i + 2] == 1 && inBin[i + 3] == 1 && inBin[i + 4] == 1 && inBin[i + 5] == 1 && inBin[i + 6] == 0 && inBin[i + 7] == 1)
            {
                medI[i + 8] = -5;
                medQ[i + 8] = 15;
                
            }
            if (inBin[i] == 1 && inBin[i + 1] == 1 && inBin[i + 2] == 1 && inBin[i + 3] == 1 && inBin[i + 4] == 1 && inBin[i + 5] == 1 && inBin[i + 6] == 1 && inBin[i + 7] == 0)
            {
                medI[i + 8] = -3;
                medQ[i + 8] = 15;
                
            }
            if (inBin[i] == 1 && inBin[i + 1] == 1 && inBin[i + 2] == 1 && inBin[i + 3] == 1 && inBin[i + 4] == 1 && inBin[i + 5] == 1 && inBin[i + 6] == 1 && inBin[i + 7] == 1)
            {
                medI[i + 8] = -1;
                medQ[i + 8] = 15;
                
            }
        }
    }
}
