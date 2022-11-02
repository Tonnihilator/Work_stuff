#include <iostream>
#include <fstream>
#include <vector>

#include "sig_mod.h"

using namespace std;

int main()
{
    setlocale(LC_ALL, "ru_RU.utf8");
    cout << "Начата работа программы. Для продолжения нажмите \"ввод\"\r\n";        //Собственно, начало работы

    // Работа со входными данными

    string inputFilePath = "C:\\Users\\User\\Desktop\\inputText.txt";
    string outputFilePath = "C:\\Users\\User\\Desktop\\outputPcm.pcm";

    short modType = 8;              // 1 - 14 - KV              // 16 - 30 - UKV
    short FHSSSpeed = 0;            // 0, 5, 10, 20, 30 - KV    // 0, 10, 100, 330, 512, 1000 - UKV

    int modSpeed = 75;
    int freqSpacing = 1000;
    float modDepth = 0.6;
    float supprCoeff = 0.3;
    int bandWidth = 3;
    int freqDeviation = 0;

    Modulation* modulator = new Modulation(inputFilePath, outputFilePath, modType, FHSSSpeed, modSpeed, freqSpacing, modDepth, supprCoeff, bandWidth, freqDeviation);

    modulator->modulation();
    
    return 0;
}
