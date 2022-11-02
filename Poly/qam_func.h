#include <vector>

namespace QAM_Synth
{
    void Synth_BPSK(std::vector <char>, std::vector <float>&, std::vector <float>&, int);
    void Synth_QPSK(std::vector <char>, std::vector <float>&, std::vector <float>&, int);
    void Synth_8PSK(std::vector <char>, std::vector <float>&, std::vector <float>&, int);
    void Synth_16QAM(std::vector <char>, std::vector <float>&, std::vector <float>&, int);
    void Synth_32QAM(std::vector <char>, std::vector <float>&, std::vector <float>&, int);
    void Synth_64QAM(std::vector <char>, std::vector <float>&, std::vector <float>&, int);
    void Synth_256QAM(std::vector <char>, std::vector <float>&, std::vector <float>&, int);
}