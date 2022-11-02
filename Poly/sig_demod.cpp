#include <iostream>
#include <fstream>
#include <vector>
#include <math.h>
#include <complex.h>

#include "sig_demod.h"

using namespace std;

const double PI = 3.141592653589793238463;


enum filtType { FILT_101_coef = 1, FILT_47_coef = 2, FILT_57_coef = 3, FILT_47_coef_ = 4, FILT_81_coef = 5 };

Demodulation::levelEvaluatorResults Demodulation::Level_evaluator(string inputPcm, int sampleCnt)
{
    ifstream inStream(inputPcm, ios::binary);

    inStream.seekg(0, inStream.end);
    int fileSize = inStream.tellg();
    inStream.seekg(44, inStream.beg);

    levelEvaluatorResults levelEvaluatorResult = { 0, 0, 0, 0, -32768, -32768 };

    short* inputPcmArr = new short[fileSize];

    int* maxMedValues = new int[sampleCnt];
    int* amplitudeArr = new int[fileSize];

    float* relativeError = new float[sampleCnt];
    float* absoluteError = new float[sampleCnt];

    long long maxMedSum = 0, sqSampleSum = 0;

    ifstream inputStream(inputPcm, ios::binary);
    if (!inputStream)
    {
        levelEvaluatorResult = { -1, -1, -1, -1, -1, -1 };
        return levelEvaluatorResult;
    }
    int inputPcmCnt = 0;
    while (inputStream.read((char*)&inputPcmArr[inputPcmCnt], sizeof(short)))
    {
        inputPcmCnt++;
    }

    inputStream.close();

    int sampleGap = (inputPcmCnt / 2) / sampleCnt;

    for (int i = 0; i < sampleCnt; i++)
    {
        maxMedValues[i] = -32768;
        for (int j = i * sampleGap * 2; j < (i + 1) * sampleGap * 2; j += 2)
        {
            amplitudeArr[j] = sqrt(inputPcmArr[j] * inputPcmArr[j] + inputPcmArr[j + 1] * inputPcmArr[j + 1]);

            if (amplitudeArr[j] > maxMedValues[i])
            {
                maxMedValues[i] = amplitudeArr[j];
            }

            if (amplitudeArr[j] > levelEvaluatorResult.maxValue)
                levelEvaluatorResult.maxValue = amplitudeArr[j];
        }
        maxMedSum += maxMedValues[i];
    }

    levelEvaluatorResult.maxValue = 20 * log10(levelEvaluatorResult.maxValue);

    levelEvaluatorResult.maxMedValue = 20 * log10(maxMedSum / sampleCnt);

    for (int i = 0; i < sampleCnt; i++)
    {
        maxMedValues[i] = 20 * log10(maxMedValues[i]);
    }

    for (int i = 0; i < sampleCnt; i++)
    {
        sqSampleSum += ((maxMedValues[i] - levelEvaluatorResult.maxMedValue) * (maxMedValues[i] - levelEvaluatorResult.maxMedValue));
    }

    levelEvaluatorResult.dispersion = sqSampleSum / (sampleCnt - 1);
    levelEvaluatorResult.standDeviation = sqrt(levelEvaluatorResult.dispersion);

    for (int i = 0; i < sampleCnt; i++)
    {
        absoluteError[i] = maxMedValues[i] - levelEvaluatorResult.maxMedValue;
        relativeError[i] = (absoluteError[i] / levelEvaluatorResult.maxMedValue) * 100;
    }

    for (int i = 0; i < sampleCnt; i++)
    {
        levelEvaluatorResult.absError += absoluteError[i];
        levelEvaluatorResult.relError += relativeError[i];
    }

    levelEvaluatorResult.absError /= sampleCnt;
    levelEvaluatorResult.relError /= sampleCnt;

    delete[] inputPcmArr;
    delete[] maxMedValues;
    delete[] amplitudeArr;
    delete[] relativeError;
    delete[] absoluteError;

    return levelEvaluatorResult;
}

Demodulation::comparisonResults Demodulation::BitErrorRate(string inputBin, string resultBin)
{
    setlocale(LC_ALL, "Russian");

    comparisonResults comparisonResult = { 0, 0, 0 };

    const int charARRAY_SIZE = 6291456 /*65536*/;

    ifstream origFile(inputBin, ios::binary);
    if (!origFile)
    {
        comparisonResult = { -1, -1, -1 };
        return comparisonResult;
    }

    ifstream resultFile(resultBin, ios::binary);
    if (!resultFile)
    {
        comparisonResult = { -1, -1, -1 };
        return comparisonResult;
    }

    char* origCharArr = new char[charARRAY_SIZE];
    char* resultCharArr = new char[charARRAY_SIZE];

    while (origFile.read((char*)&origCharArr[comparisonResult.sourceCnt], sizeof(char)))
    {
        resultFile.read((char*)&resultCharArr[comparisonResult.sourceCnt], sizeof(char));
        comparisonResult.sourceCnt++;
    }

    for (int i = 0; i < comparisonResult.sourceCnt; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if (((origCharArr[i] >> j & 1) == ((resultCharArr[i] >> j) & 1)))
            {
                comparisonResult.matchCnt++;
            }
        }
    }

    comparisonResult.sourceCnt *= 8;
    comparisonResult.finRatio = 100 - (((float)comparisonResult.sourceCnt / (float)comparisonResult.matchCnt) * 100);

    origFile.close();
    resultFile.close();

    delete[] origCharArr;
    delete[] resultCharArr;

    return comparisonResult;
}

void Filter(short* in, int* out, int& inpSize)
{
    const int N = 47;
    short H[47] = { 7, 8, 8, 7, 4, 0, -5, -11, -16, -20, -22, -21, -17, -10, 1, 16, 33, 51, 70, 89, 104, 117, 124, 127, 124, 117, 104, 89, 70, 51, 33, 16, 1, -10, -17, -21, -22, -20, -16, -11, -5, 0, 4, 7, 8, 8, 7 };
    for (int i = 0; i < inpSize; i++)
    {
        out[i] = 0.;
        for (int j = 0; j < N; j++)
            if (i - j >= 0)
                out[i] += H[j] * in[i - j];
    }
}

void WavAddBuf(ifstream& inStream, vector<char>& outputWavVector)
{
    inStream.clear();
    if (inStream)
    {
        inStream.seekg(0, inStream.end);
        int arrLength = inStream.tellg();
        inStream.seekg(44, inStream.beg);

        char* addArr = new char[arrLength];

        inStream.read(addArr, arrLength - 44);

        for (int i = 0; i < arrLength - 44; i++)
        {
            outputWavVector.push_back(addArr[i]);
        }
    }
    else
    {
        cout << "error" << '\n';
    }
}

Demodulation::errType Demodulation::paramCheck()
{
    ifstream inputFile(inputFilePath);

    if (!inputFile)
    {
        return INPUT_FILE_ERR;
    }
    else if (modType < 1 || (modType == 15) || (modType > 20 && modType < 29) || (modType > 30 && modType != 999))
    {
        return MOD_TYPE_ERR;
    }
    else
    {
        if (modType > 0 && modType < 8)
        {
            if (FHSSSpeed != 0 && FHSSSpeed != 5 && FHSSSpeed != 10 && FHSSSpeed != 20 && FHSSSpeed != 30)
                return FHSS_SPEED_ERR;
        }
        else if ((modType > 15 && modType < 21) || (modType > 28 && modType < 31))
        {
            if (FHSSSpeed != 0 && FHSSSpeed != 10 && FHSSSpeed != 100 && FHSSSpeed != 330 && FHSSSpeed != 512 && FHSSSpeed != 1000)
                return FHSS_SPEED_ERR;
        }
    }

    switch (modType)
    {
        case 1:
        {
            if (modSpeed < 5 || modSpeed > 25)
            {
                return MOD_SPEED_ERR;
            }
            else
                return ALL_OK;
        }
        case 2:
        {
            if (freqSpacing < 200 || freqSpacing > 2000)
            {
                return FREQ_SPACING_ERR;
            }
            else if (modSpeed < 5 || modSpeed > 25)
            {
                return MOD_SPEED_ERR;
            }
            else
                return ALL_OK;
        }
        case 3:
        {
            if (freqSpacing < 200 || freqSpacing > 3000)
            {
                return FREQ_SPACING_ERR;
            }
            else if (modSpeed != 50 && modSpeed != 100 && modSpeed != 200 && modSpeed != 300 && modSpeed != 600 && modSpeed != 1200)
            {
                return MOD_SPEED_ERR;
            }
            else
                return ALL_OK;
        }
        case 4:
        {
            if (modSpeed != 50 && modSpeed != 100 && modSpeed != 200 && modSpeed != 300 && modSpeed != 600 && modSpeed != 1200)
            {
                return MOD_SPEED_ERR;
            }
            else
                return ALL_OK;
        }
        case 5:
        {
            if (modSpeed != 50 && modSpeed != 100 && modSpeed != 200 && modSpeed != 300 && modSpeed != 600 && modSpeed != 1200)
            {
                return MOD_SPEED_ERR;
            }
            else
                return ALL_OK;
        }
        case 6:
        {
            if (floor(modDepth * 10) < 3 || floor(modDepth * 10) > 8)
            {
                return MOD_DEPTH_ERR;
            }
            else
                return ALL_OK;
        }
        case 7:
        {
            if (floor(supprCoeff * 10) != 0 && floor(supprCoeff * 10) != 3 && floor(supprCoeff * 10) != 10)
            {
                return SUPPR_COEFF_ERR;
            }
            else
                return ALL_OK;
        }
        case 8:
        {
            if (modSpeed == 75)
            {
                if (bandWidth == 3)
                {
                    expCoef = 40;
                    return ALL_OK;
                }
                else
                    return BAND_WIDTH_ERR;
            }
            else if (modSpeed == 150)
            {
                if (bandWidth == 6)
                {
                    expCoef = 40;
                    return ALL_OK;
                }
                else
                    return BAND_WIDTH_ERR;
            }
            else if (modSpeed == 300)
            {
                if (bandWidth == 12)
                {
                    expCoef = 40;
                    return ALL_OK;
                }
                else
                    return BAND_WIDTH_ERR;
            }
            else if (modSpeed == 600)
            {
                if (bandWidth == 18)
                {
                    expCoef = 30;
                    return ALL_OK;
                }
                else
                    return BAND_WIDTH_ERR;
            }
            else if (modSpeed == 1200)
            {
                if (bandWidth == 24)
                {
                    expCoef = 20;
                    return ALL_OK;
                }
                else
                    return BAND_WIDTH_ERR;
            }
            else if (modSpeed == 8000)
            {
                if (bandWidth == 24)
                {
                    expCoef = 3;
                    return ALL_OK;
                }
                else
                    return BAND_WIDTH_ERR;
            }
            else
                return MOD_SPEED_ERR;
        }
        case 9:
        {
            if (modSpeed == 1400)
            {
                if (bandWidth == 7)
                {
                    expCoef = 10;
                    return ALL_OK;
                }
                else
                    return BAND_WIDTH_ERR;
            }
            else if (modSpeed == 2800)
            {
                if (bandWidth == 14)
                {
                    expCoef = 10;
                    return ALL_OK;
                }
                else
                    return BAND_WIDTH_ERR;
            }
            else if (modSpeed == 4200)
            {
                if (bandWidth == 21)
                {
                    expCoef = 10;
                    return ALL_OK;
                }
                else
                    return BAND_WIDTH_ERR;
            }
            else if (modSpeed == 8400)
            {
                if (bandWidth == 21)
                {
                    expCoef = 5;
                    return ALL_OK;
                }
                else
                    return BAND_WIDTH_ERR;
            }
            else if (modSpeed == 16000)
            {
                if (bandWidth == 24)
                {
                    expCoef = 3;
                    return ALL_OK;
                }
                else
                    return BAND_WIDTH_ERR;
            }
            else
                return MOD_SPEED_ERR;
        }
        case 10:
        {
            if (modSpeed == 4200)
            {
                if (bandWidth == 7)
                {
                    expCoef = 5;
                    return ALL_OK;
                }
                else
                    return BAND_WIDTH_ERR;
            }
            else if (modSpeed == 12600)
            {
                if (bandWidth == 21)
                {
                    expCoef = 5;
                    return ALL_OK;
                }
                else
                    return BAND_WIDTH_ERR;
            }
            else if (modSpeed == 21000)
            {
                if (bandWidth == 14)
                {
                    expCoef = 2;
                    return ALL_OK;
                }
                else
                    return BAND_WIDTH_ERR;
            }
            else if (modSpeed == 33000)
            {
                if (bandWidth == 22)
                {
                    expCoef = 2;
                    return ALL_OK;
                }
                else
                    return BAND_WIDTH_ERR;
            }
            else if (modSpeed == 45000)
            {
                if (bandWidth == 15)
                {
                    expCoef = 1;
                    return ALL_OK;
                }
                else
                    return BAND_WIDTH_ERR;
            }
            else
                return MOD_SPEED_ERR;
        }
        case 11:
        {
            if (modSpeed == 5600)
            {
                if (bandWidth == 7)
                {
                    expCoef = 5;
                    return ALL_OK;
                }
                else
                    return BAND_WIDTH_ERR;
            }
            else if (modSpeed == 12000)
            {
                if (bandWidth == 9)
                {
                    expCoef = 3;
                    return ALL_OK;
                }
                else
                    return BAND_WIDTH_ERR;
            }
            else if (modSpeed == 32000)
            {
                if (bandWidth == 16)
                {
                    expCoef = 2;
                    return ALL_OK;
                }
                else
                    return BAND_WIDTH_ERR;
            }
            else if (modSpeed == 48000)
            {
                if (bandWidth == 24)
                {
                    expCoef = 2;
                    return ALL_OK;
                }
                else
                    return BAND_WIDTH_ERR;
            }
            else if (modSpeed == 64000)
            {
                if (bandWidth == 16)
                {
                    expCoef = 1;
                    return ALL_OK;
                }
                else
                    return BAND_WIDTH_ERR;
            }
            else
                return MOD_SPEED_ERR;
        }
        case 12:
        {
            if (modSpeed == 10000)
            {
                if (bandWidth == 4)
                {
                    expCoef = 2;
                    return ALL_OK;
                }
                else
                    return BAND_WIDTH_ERR;
            }
            else if (modSpeed == 14000)
            {
                if (bandWidth == 14)
                {
                    expCoef = 5;
                    return ALL_OK;
                }
                else
                    return BAND_WIDTH_ERR;
            }
            else if (modSpeed == 25000)
            {
                if (bandWidth == 10)
                {
                    expCoef = 2;
                    return ALL_OK;
                }
                else
                    return BAND_WIDTH_ERR;
            }
            else if (modSpeed == 40000)
            {
                if (bandWidth == 16)
                {
                    expCoef = 2;
                    return ALL_OK;
                }
                else
                    return BAND_WIDTH_ERR;
            }
            else if (modSpeed == 55000)
            {
                if (bandWidth == 22)
                {
                    expCoef = 2;
                    return ALL_OK;
                }
                else
                    return BAND_WIDTH_ERR;
            }
            else if (modSpeed == 120000)
            {
                if (bandWidth == 24)
                {
                    expCoef = 1;
                    return ALL_OK;
                }
                else
                    return BAND_WIDTH_ERR;
            }
            else
                return MOD_SPEED_ERR;
        }
        case 13:
        {
            if (modSpeed == 3600)
            {
                if (bandWidth == 3)
                {
                    expCoef = 5;
                    return ALL_OK;
                }
                else
                    return BAND_WIDTH_ERR;
            }
            else if (modSpeed == 6000)
            {
                if (bandWidth == 6)
                {
                    expCoef = 6;
                    return ALL_OK;
                }
                else
                    return BAND_WIDTH_ERR;
            }
            else if (modSpeed == 12000)
            {
                if (bandWidth == 10)
                {
                    expCoef = 5;
                    return ALL_OK;
                }
                else
                    return BAND_WIDTH_ERR;
            }
            else if (modSpeed == 30000)
            {
                if (bandWidth == 15)
                {
                    expCoef = 3;
                    return ALL_OK;
                }
                else
                    return BAND_WIDTH_ERR;
            }
            else if (modSpeed == 48000)
            {
                if (bandWidth == 24)
                {
                    expCoef = 3;
                    return ALL_OK;
                }
                else
                    return BAND_WIDTH_ERR;
            }
            else if (modSpeed == 120000)
            {
                if (bandWidth == 20)
                {
                    expCoef = 1;
                    return ALL_OK;
                }
                else
                    return BAND_WIDTH_ERR;
            }
            else
                return MOD_SPEED_ERR;
        }
        case 14:
        {
            if (modSpeed == 8000)
            {
                if (bandWidth == 3)
                {
                    expCoef = 3;
                    return ALL_OK;
                }
                else
                    return BAND_WIDTH_ERR;
            }
            else if (modSpeed == 12000)
            {
                if (bandWidth == 6)
                {
                    expCoef = 4;
                    return ALL_OK;
                }
                else
                    return BAND_WIDTH_ERR;
            }
            else if (modSpeed == 24000)
            {
                if (bandWidth == 18)
                {
                    expCoef = 6;
                    return ALL_OK;
                }
                else
                    return BAND_WIDTH_ERR;
            }
            else if (modSpeed == 40000)
            {
                if (bandWidth == 20)
                {
                    expCoef = 4;
                    return ALL_OK;
                }
                else
                    return BAND_WIDTH_ERR;
            }
            else if (modSpeed == 96000)
            {
                if (bandWidth == 24)
                {
                    expCoef = 2;
                    return ALL_OK;
                }
                else
                    return BAND_WIDTH_ERR;
            }
            else if (modSpeed == 120000)
            {
                if (bandWidth == 15)
                {
                    expCoef = 1;
                    return ALL_OK;
                }
                else
                    return BAND_WIDTH_ERR;
            }
            else
                return MOD_SPEED_ERR;
        }

        case 16:
        {
            if ((freqSpacing < 1000 || freqSpacing > 40000) || ((modSpeed % 100) != 0))
            {
                return FHSS_SPEED_ERR;
            }
            else if (modSpeed != 1200 && modSpeed != 2400 && modSpeed != 4800 && modSpeed != 7200 && modSpeed != 9600 && modSpeed != 12000 && modSpeed != 14400 && modSpeed != 16000)
            {
                return MOD_SPEED_ERR;
            }
            else
                return ALL_OK;
        }
        case 17:
        {
            if (modSpeed != 1200 && modSpeed != 2400 && modSpeed != 4800 && modSpeed != 7200 && modSpeed != 9600 && modSpeed != 12000 && modSpeed != 14400 && modSpeed != 16000)
            {
                return MOD_SPEED_ERR;
            }
            else
                return ALL_OK;
        }
        case 18:
        {
            if (floor(modDepth * 10) < 3 || floor(modDepth * 10) > 8)
            {
                return MOD_DEPTH_ERR;
            }
            else
                return ALL_OK;
        }
        case 19:
        {
            if (floor(supprCoeff * 10) != 0 && floor(supprCoeff * 10) != 3 && floor(supprCoeff * 10) != 10)
            {
                return SUPPR_COEFF_ERR;
            }
            else
                return ALL_OK;
        }
        case 20:
        {
            if (freqDeviation != 5000 && freqDeviation != 10000 && freqDeviation != 15000 && freqDeviation != 20000)
            {
                return FREQ_DEVIATION_ERR;
            }
            else
                return ALL_OK;
        }
        case 29:
        {
            if (modSpeed != 57600 && modSpeed != 115200 && modSpeed != 486000)
            {
                return MOD_SPEED_ERR;
            }
            else
                return ALL_OK;
        }
        case 30:
        {
            if ((freqSpacing < 5000 || freqSpacing > 40000) || ((modSpeed % 100) != 0))
            {
                return FREQ_SPACING_ERR;
            }
            else if (modSpeed != 1200 && modSpeed != 2400 && modSpeed != 4800 && modSpeed != 7200 && modSpeed != 9600 && modSpeed != 12000 && modSpeed != 14400 && modSpeed != 16000)
            {
                return MOD_SPEED_ERR;
            }
            else
                return ALL_OK;
        }
    }
}
Demodulation::errType Demodulation::demodulation()
{
    if (paramCheck() != 0)
    {
        return paramCheck();
    }

    //switch (modType) // Демодуляция
    //{
    //case 1:
    //{
    //    ifstream dash("Samples/Dash.wav", ios::binary), point("Samples/Point.wav", ios::binary),
    //        silence("Samples/Silence.wav", ios::binary);

    //    ifstream inputStream(inputFilePath, ios::binary);

    //    const int oversampling = 100;

    //    short* inputI = new short[fileSize / 2];
    //    short* inputQ = new short[fileSize / 2];

    //    int inputIQCnt = 0;
    //    while (inputStream.read((char*)&inputI[inputIQCnt], sizeof(short)))
    //    {
    //        inputStream.read((char*)&inputQ[inputIQCnt], sizeof(short));
    //        inputIQCnt++;
    //    }
    //    inputStream.close();

    //    /* Считали массив квадратур из файла, заполняем массив бинарных символов */

    //    int seqConjCntr = 0;
    //    int broadcastStart = 0;
    //    for (int i = 0; i < inputIQCnt; i++)
    //    {
    //        seqConjCntr = 0;
    //        for (int j = 0; j < 12 * oversampling; j += oversampling)
    //        {
    //            if (sqrt(pow((double)inputI[i + j], 2) + pow((double)inputQ[i + j], 2)) > 2000)
    //            {
    //                seqConjCntr++;
    //            }
    //        }
    //        if (seqConjCntr == 12)
    //        {
    //            broadcastStart = i + (oversampling * 12);
    //            break;
    //        }
    //    }

    //    long maxValue = 0, maxValueCnt = 0;
    //    for (int i = broadcastStart - (6 * oversampling); i < broadcastStart - oversampling; i++)
    //    {
    //        maxValue += sqrt(pow(inputI[i], 2) + pow(inputQ[i], 2));
    //        maxValueCnt++;
    //    }
    //    maxValue = sqrt(pow(maxValue, 2) / 2) / maxValueCnt;

    //    float* compSequence = new float[1023];
    //    int sampleStart = -1;
    //    for (int i = broadcastStart; i < inputIQCnt; i++)
    //    {
    //        for (int j = 0; j < 12; j++)
    //        {
    //            if (sqrt(pow(sqrt(pow(inputI[i + (j * oversampling)], 2) + pow(inputQ[i + (j * oversampling)], 2)), 2) / 2) > (maxValue * 0.2))
    //                compSequence[j] = 1;
    //            else if (sqrt(pow(sqrt(pow(inputI[i + (j * oversampling)], 2) + pow(inputQ[i + (j * oversampling)], 2)), 2) / 2) < (maxValue * 0.2))
    //                compSequence[j] = 0;
    //        }
    //        if (compSequence[0] == 1 && compSequence[1] == 0 && compSequence[2] == 1 && compSequence[3] == 0 &&
    //            compSequence[4] == 1 && compSequence[5] == 0 && compSequence[6] == 1 && compSequence[7] == 0 &&
    //            compSequence[8] == 1 && compSequence[9] == 0 && compSequence[10] == 1 && compSequence[11] == 0)
    //        {
    //            sampleStart = i;
    //            break;
    //        }
    //    }

    //    int sampleEnd = -1;
    //    for (int i = sampleStart; i < sampleStart + oversampling * 2; i++)
    //    {
    //        for (int j = 0; j < 12; j++)
    //        {
    //            if (sqrt(pow(sqrt(pow(inputI[i + (j * oversampling)], 2) + pow(inputQ[i + (j * oversampling)], 2)), 2) / 2) > (maxValue * 0.2))
    //                compSequence[j] = 1;
    //            else if (sqrt(pow(sqrt(pow(inputI[i + (j * oversampling)], 2) + pow(inputQ[i + (j * oversampling)], 2)), 2) / 2) < (maxValue * 0.2))
    //                compSequence[j] = 0;
    //        }
    //        if (compSequence[0] == 1 && compSequence[1] == 0 && compSequence[2] == 1 && compSequence[3] == 0 &&
    //            compSequence[4] == 1 && compSequence[5] == 0 && compSequence[6] == 1 && compSequence[7] == 0 &&
    //            compSequence[8] == 1 && compSequence[9] == 0 && compSequence[10] == 1 && compSequence[11] == 0)
    //            continue;
    //        else
    //        {
    //            sampleEnd = i;
    //            break;
    //        }
    //    }
    //    sampleStart = (sampleStart + sampleEnd) / 2;

    //    short* binArrFMor = new short[inputIQCnt / oversampling];

    //    int binArrCnt = 0;
    //    for (int i = sampleStart + 1200; i < inputIQCnt; i += oversampling)
    //    {
    //        if (sqrt(pow(sqrt(pow(inputI[i], 2) + pow(inputQ[i], 2)), 2) / 2) < (maxValue * 0.2))
    //            binArrFMor[binArrCnt] = 0;
    //        else
    //            binArrFMor[binArrCnt] = 1;
    //        binArrCnt++;
    //    }

    //    delete[] inputQ;
    //    delete[] inputI;

    //    /* Разбиение принятого сигнала на условные символы */

    //    string morseString = "";

    //    int increm = 0;

    //    for (int n = 0; n < binArrCnt; n += increm)
    //    {
    //        if (binArrFMor[n] == 1)
    //        {

    //            if (binArrFMor[n - 3] == 0 && binArrFMor[n - 2] == 0 && binArrFMor[n - 1] == 0 && binArrFMor[n + 1] == 0 && binArrFMor[n + 2] == 1 && binArrFMor[n + 3] == 1
    //                && binArrFMor[n + 4] == 1 && binArrFMor[n + 5] == 0 && binArrFMor[n + 6] == 1 && binArrFMor[n + 7] == 0 && binArrFMor[n + 8] == 1 && binArrFMor[n + 9] == 1
    //                && binArrFMor[n + 10] == 1 && binArrFMor[n + 11] == 0 && binArrFMor[n + 12] == 1 && binArrFMor[n + 13] == 0 && binArrFMor[n + 14] == 0 && binArrFMor[n + 15] == 0)
    //            {
    //                WavAddBuf(point, resultVector);
    //                WavAddBuf(dash, resultVector);
    //                WavAddBuf(point, resultVector);
    //                WavAddBuf(dash, resultVector);
    //                WavAddBuf(point, resultVector);
    //                WavAddBuf(silence, resultVector);
    //                break;
    //            }
    //            else if (binArrFMor[n + 1] == 1 && binArrFMor[n + 2] == 1 && binArrFMor[n + 3] == 0)
    //            {
    //                morseString += "-";
    //                /* Тире */
    //                WavAddBuf(dash, resultVector);
    //                if (binArrFMor[n + 4] == 0 && binArrFMor[n + 5] == 0)
    //                {
    //                    /* Конец буквы */
    //                    for (int m = 0; m < 2; m++)
    //                    {
    //                        WavAddBuf(silence, resultVector);
    //                    }

    //                    if (binArrFMor[n + 6] == 0 && binArrFMor[n + 7] == 0 && binArrFMor[n + 8] == 0 && binArrFMor[n + 9] == 0)
    //                    {
    //                        /* Пробел */
    //                        for (int m = 0; m < 4; m++)
    //                        {
    //                            WavAddBuf(silence, resultVector);
    //                        }
    //                        morseString = "";
    //                        increm = 10;
    //                    }
    //                    else
    //                    {
    //                        morseString = "";
    //                        increm = 6;
    //                    }
    //                }
    //                else
    //                {
    //                    increm = 4;
    //                }
    //            }
    //            else if (binArrFMor[n + 2] == 0 && binArrFMor[n + 3] == 0)
    //            {
    //                morseString += ".";
    //                /* Точка */
    //                WavAddBuf(point, resultVector);
    //                if (binArrFMor[n + 4] == 0 && binArrFMor[n + 5] == 0 && binArrFMor[n + 6] == 0 && binArrFMor[n + 7] == 0)
    //                {
    //                    /* Пробел */
    //                    for (int m = 0; m < 4; m++)
    //                    {
    //                        WavAddBuf(silence, resultVector);
    //                    }
    //                    morseString = "";
    //                    increm = 8;
    //                }
    //                else
    //                {
    //                    /* Конец буквы */
    //                    for (int m = 0; m < 2; m++)
    //                    {
    //                        WavAddBuf(silence, resultVector);
    //                    }
    //                    morseString = "";
    //                    increm = 4;
    //                }
    //            }
    //            else
    //            {
    //                /* Точка */
    //                WavAddBuf(point, resultVector);
    //                morseString += ".";
    //                increm = 2;
    //            }
    //        }
    //        else if (binArrFMor[n + 1] == 0 && binArrFMor[n + 2] == 0 && binArrFMor[n + 3] == 0 && binArrFMor[n + 4] == 0 && binArrFMor[n + 5] == 0 && binArrFMor[n + 6] == 0)
    //        {
    //            /* Пробел */
    //            for (int m = 0; m < 4; m++)
    //            {
    //                WavAddBuf(silence, resultVector);
    //            }
    //            increm = 7;
    //        }
    //        else if (binArrFMor[n] == 0 && binArrFMor[n + 1] == 0 && binArrFMor[n + 2] == 0 && binArrFMor[n + 3] == 0 && binArrFMor[n + 4] == 0 && binArrFMor[n + 5] == 0 && binArrFMor[n + 6] == 0 && binArrFMor[n + 7] == 0)
    //        {
    //            for (int m = 0; m < 6; m++)
    //            {
    //                WavAddBuf(silence, resultVector);
    //            }
    //            increm = 8;
    //        }
    //        else
    //            increm = 1;
    //    }

    //    unsigned int wavBufSize = resultVector.size();
    //    return wavBufSize;
    //}

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    //case 2:
    //{
    //    ifstream dash("Samples/Dash.wav", ios::binary), point("Samples/Point.wav", ios::binary),
    //        silence("Samples/Silence.wav", ios::binary);

    //    ifstream inputStream(inputFilePath, ios::binary);

    //    const int oversampling = (freqSpacing * 10) / modSpeed;

    //    short* inputI = new short[fileSize / 2];
    //    short* inputQ = new short[fileSize / 2];

    //    int inputIQCnt = 0;
    //    while (inputStream.read((char*)&inputI[inputIQCnt], sizeof(short)))
    //    {
    //        inputStream.read((char*)&inputQ[inputIQCnt], sizeof(short));
    //        inputIQCnt++;
    //    }
    //    inputStream.close();

    //    float* mediumArrRecovered = new float[inputIQCnt];

    //    int recArr = 0;
    //    for (int i = 0; i < inputIQCnt; i++)
    //    {
    //        mediumArrRecovered[recArr] = ((float)inputI[i]) * ((float)inputQ[i - 1]) - ((float)inputQ[i]) * ((float)inputI[i - 1]);
    //        recArr++;
    //    }

    //    int sampleStart = -1;
    //    int sampleEnd = -1;
    //    sampleStart = (sampleStart + sampleEnd) / 2;

    //    short* binArrFMor = new short[inputIQCnt];
    //    int binArrCnt = 0;
    //    for (int i = sampleStart; i < inputIQCnt; i += oversampling)
    //    {
    //        mediumArrRecovered[binArrCnt] = ((float)inputI[i]) * ((float)inputQ[i - 1]) - ((float)inputQ[i]) * ((float)inputI[i - 1]);
    //        if (mediumArrRecovered[binArrCnt] > 0)
    //            binArrFMor[binArrCnt] = 0;
    //        else if (mediumArrRecovered[binArrCnt] < 0)
    //            binArrFMor[binArrCnt] = 1;
    //        binArrCnt++;
    //    }

    //    delete[] inputQ;
    //    delete[] inputI;

    //    short* compArr = new short[40];

    //    delete[] compArr;

    //    string morseString = "";

    //    int increm = 0;

    //    for (int n = 0; n < binArrCnt; n += increm)
    //    {
    //        if (binArrFMor[n] == 1)
    //        {

    //            if (binArrFMor[n - 3] == 0 && binArrFMor[n - 2] == 0 && binArrFMor[n - 1] == 0 && binArrFMor[n + 1] == 0 && binArrFMor[n + 2] == 1 && binArrFMor[n + 3] == 1
    //                && binArrFMor[n + 4] == 1 && binArrFMor[n + 5] == 0 && binArrFMor[n + 6] == 1 && binArrFMor[n + 7] == 0 && binArrFMor[n + 8] == 1 && binArrFMor[n + 9] == 1
    //                && binArrFMor[n + 10] == 1 && binArrFMor[n + 11] == 0 && binArrFMor[n + 12] == 1 && binArrFMor[n + 13] == 0 && binArrFMor[n + 14] == 0 && binArrFMor[n + 15] == 0)
    //            {
    //                WavAddBuf(point, resultVector);
    //                WavAddBuf(dash, resultVector);
    //                WavAddBuf(point, resultVector);
    //                WavAddBuf(dash, resultVector);
    //                WavAddBuf(point, resultVector);
    //                WavAddBuf(silence, resultVector);
    //                break;
    //            }
    //            else if (binArrFMor[n + 1] == 1 && binArrFMor[n + 2] == 1 && binArrFMor[n + 3] == 0)
    //            {
    //                morseString += "-";
    //                /* Тире */
    //                WavAddBuf(dash, resultVector);
    //                if (binArrFMor[n + 4] == 0 && binArrFMor[n + 5] == 0)
    //                {
    //                    /* Конец буквы */
    //                    for (int m = 0; m < 2; m++)
    //                    {
    //                        WavAddBuf(silence, resultVector);
    //                    }

    //                    if (binArrFMor[n + 6] == 0 && binArrFMor[n + 7] == 0 && binArrFMor[n + 8] == 0 && binArrFMor[n + 9] == 0)
    //                    {
    //                        /* Пробел */
    //                        for (int m = 0; m < 4; m++)
    //                        {
    //                            WavAddBuf(silence, resultVector);
    //                        }
    //                        morseString = "";
    //                        increm = 10;
    //                    }
    //                    else
    //                    {
    //                        morseString = "";
    //                        increm = 6;
    //                    }
    //                }
    //                else
    //                {
    //                    increm = 4;
    //                }
    //            }
    //            else if (binArrFMor[n + 2] == 0 && binArrFMor[n + 3] == 0)
    //            {
    //                morseString += ".";
    //                /* Точка */
    //                WavAddBuf(point, resultVector);
    //                if (binArrFMor[n + 4] == 0 && binArrFMor[n + 5] == 0 && binArrFMor[n + 6] == 0 && binArrFMor[n + 7] == 0)
    //                {
    //                    /* Пробел */
    //                    for (int m = 0; m < 4; m++)
    //                    {
    //                        WavAddBuf(silence, resultVector);
    //                    }
    //                    morseString = "";
    //                    increm = 8;
    //                }
    //                else
    //                {
    //                    /* Конец буквы */
    //                    for (int m = 0; m < 2; m++)
    //                    {
    //                        WavAddBuf(silence, resultVector);
    //                    }
    //                    morseString = "";
    //                    increm = 4;
    //                }
    //            }
    //            else
    //            {
    //                /* Точка */
    //                WavAddBuf(point, resultVector);
    //                morseString += ".";
    //                increm = 2;
    //            }
    //        }
    //        else if (binArrFMor[n + 1] == 0 && binArrFMor[n + 2] == 0 && binArrFMor[n + 3] == 0 && binArrFMor[n + 4] == 0 && binArrFMor[n + 5] == 0 && binArrFMor[n + 6] == 0)
    //        {
    //            /* Пробел */
    //            for (int m = 0; m < 4; m++)
    //            {
    //                WavAddBuf(silence, resultVector);
    //            }
    //            increm = 7;
    //        }
    //        else if (binArrFMor[n] == 0 && binArrFMor[n + 1] == 0 && binArrFMor[n + 2] == 0 && binArrFMor[n + 3] == 0 && binArrFMor[n + 4] == 0 && binArrFMor[n + 5] == 0 && binArrFMor[n + 6] == 0 && binArrFMor[n + 7] == 0)
    //        {
    //            for (int m = 0; m < 6; m++)
    //            {
    //                WavAddBuf(silence, resultVector);
    //            }
    //            increm = 8;
    //        }
    //        else
    //            increm = 1;
    //    }

    //    unsigned int wavBufSize = resultVector.size();
    //    return wavBufSize;
    //}

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    //case 3:
    //{
    //    const int oversampling = (freqSpacing * 10) / modSpeed;

    //    short* inputI = new short[fileSize / 2];
    //    short* inputQ = new short[fileSize / 2];

    //    int inputIQCnt = fileSize / 2;

    //    float* mediumArrRecovered = new float[fileSize / 2];

    //    int recArr = 0;
    //    for (int i = 0; i < inputIQCnt; i++)
    //    {
    //        mediumArrRecovered[recArr] = ((float)inputI[i]) * ((float)inputQ[i - 1]) - ((float)inputQ[i]) * ((float)inputI[i - 1]);
    //        recArr++;
    //    }

    //    int sampleStart = -1;

    //    int sampleEnd = -1;
    //    sampleStart = (sampleStart + sampleEnd) / 2;

    //    short* binArrFLet = new short[inputIQCnt];
    //    int binArrCnt = 0;
    //    for (int i = sampleStart; i < inputIQCnt; i += oversampling)
    //    {
    //        mediumArrRecovered[binArrCnt] = ((float)inputI[i]) * ((float)inputQ[i - 1]) - ((float)inputQ[i]) * ((float)inputI[i - 1]);
    //        if (mediumArrRecovered[binArrCnt] > 0)
    //            binArrFLet[binArrCnt] = 0;
    //        else if (mediumArrRecovered[binArrCnt] < 0)
    //            binArrFLet[binArrCnt] = 1;
    //        binArrCnt++;
    //    }

    //    delete[] mediumArrRecovered;
    //    delete[] inputQ;
    //    delete[] inputI;

    //    short* compArr = new short[40];

    //    int signalStart = 0;

    //    delete[] compArr;

    //    char finChar = '\0';

    //    int finArrCnt = 0;
    //    for (int i = signalStart; i < binArrCnt; i += 8 * oversampling)
    //    {
    //        for (int j = 0; j < 8; j++)
    //        {
    //            if (binArrFLet[i + j] == 0)
    //            {
    //                finChar &= ~(1 << j);
    //            }
    //            else if (binArrFLet[i + j] == 1)
    //            {
    //                finChar |= (1 << j);
    //            }
    //        }
    //        resArray[finArrCnt] = finChar;
    //        finArrCnt++;
    //    }

    //    delete[] binArrFLet;
    //    return finArrCnt;
    //}

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    //case 4:
    //{
    //    const int oversampling = 100;

    //    short* inputI = new short[fileSize / 2];
    //    short* inputQ = new short[fileSize / 2];

    //    int inputIQCnt = 0;
    //    long syncMaxSum = -1, syncSeqStart = 0, syncSum = 0;
    //    for (int i = 0; i < inputIQCnt; i++)
    //    {
    //        syncSum = 0;
    //        for (int j = 0; j < 20 * oversampling; j++)
    //        {
    //            syncSum += sqrt(inputI[i + j] * inputI[i + j] + inputQ[i + j] * inputQ[i + j]);
    //        }
    //        if (syncSum > syncMaxSum)
    //        {
    //            syncMaxSum = syncSum;
    //            syncSeqStart = i;
    //        }
    //    }

    //    double* freqTurnAngle = new double[2000];
    //    int freqTurnCntr = 0;

    //    short* compdI = new short[inputIQCnt + FHSSChunkSize];
    //    short* compdQ = new short[inputIQCnt + FHSSChunkSize];

    //    delete[] inputI;
    //    delete[] inputQ;

    //    float resAngle = 0;
    //    for (int i = 0; i < freqTurnCntr; i++)
    //    {
    //        if (compdI[i] >= 0 && compdQ[i] >= 0)
    //            resAngle += atan((float)compdI[i] / (float)compdQ[i]) / PI * 180;
    //        else if ((compdI[i] > 0 && compdQ[i] < 0) || (compdI[i] <= 0 && compdQ[i] < 0))
    //            resAngle += 180 + atan((float)compdI[i] / (float)compdQ[i]) / PI * 180;
    //        else
    //            resAngle += 360 + atan((float)compdI[i] / (float)compdQ[i]) / PI * 180;
    //    }
    //    resAngle /= freqTurnCntr;

    //    int sampleStart = -1;

    //    int sampleEnd = -1;
    //    sampleStart = (sampleStart + sampleEnd) / 2 - 1 + 41 * oversampling;

    //    short* firstQ = new short[oversampling];
    //    int anyCnt = 0;
    //    for (int i = sampleStart - oversampling; i < sampleStart; i++)
    //    {
    //        firstQ[anyCnt] = compdQ[i] * cos((-45 + resAngle) * PI / 180) + compdI[i] * sin((-45 + resAngle) * PI / 180);
    //        anyCnt++;
    //    }

    //    delete[] freqTurnAngle;

    //    delete[] compdI;
    //    delete[] compdQ;

    //    short* compArr = new short[40];

    //    delete[] compArr;

    //    short* binArrPLet = new short[inputIQCnt / oversampling];

    //    int binArrCnt = 0;

    //    if (firstQ[0] > 0)
    //    {
    //        binArrPLet[binArrCnt] = 0;
    //    }
    //    else
    //    {
    //        binArrPLet[binArrCnt] = 1;
    //    }
    //    binArrCnt++;

    //    char finChar = '\0';

    //    int finCnt = 0;
    //    for (int i = 0; i < binArrCnt; i += 8)
    //    {
    //        for (int j = 0; j < 8; j++)
    //        {
    //            if (binArrPLet[i + j] == 0)
    //            {
    //                finChar &= ~(1 << j);
    //            }

    //            else if (binArrPLet[i + j] == 1)
    //            {
    //                finChar |= (1 << j);
    //            }
    //        }
    //        resArray[finCnt] = finChar;
    //        finCnt++;
    //    }

    //    delete[] binArrPLet;

    //    return finCnt;
    //}

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    //case 5:
    //{
    //    const int oversampling = 100;

    //    short* inputI = new short[fileSize / 2];
    //    short* inputQ = new short[fileSize / 2];

    //    int inputIQCnt = 0;
    //    long syncMaxSum = -1, syncSeqStart = 0, syncSum = 0;
    //    for (int i = 0; i < inputIQCnt; i++)
    //    {
    //        syncSum = 0;
    //        for (int j = 0; j < 20 * oversampling; j++)
    //        {
    //            syncSum += sqrt(inputI[i + j] * inputI[i + j] + inputQ[i + j] * inputQ[i + j]);
    //        }
    //        if (syncSum > syncMaxSum)
    //        {
    //            syncMaxSum = syncSum;
    //            syncSeqStart = i;
    //        }
    //    }

    //    double* freqTurnAngle = new double[2000];
    //    int freqTurnCntr = 0;

    //    short* compdI = new short[inputIQCnt + FHSSChunkSize];
    //    short* compdQ = new short[inputIQCnt + FHSSChunkSize];

    //    delete[] inputI;
    //    delete[] inputQ;

    //    float resAngle = 0;
    //    for (int i = 0; i < freqTurnCntr; i++)
    //    {
    //        if (compdI[i] >= 0 && compdQ[i] >= 0)
    //            resAngle += atan((float)compdI[i] / (float)compdQ[i]) / PI * 180;
    //        else if ((compdI[i] > 0 && compdQ[i] < 0) || (compdI[i] <= 0 && compdQ[i] < 0))
    //            resAngle += 180 + atan((float)compdI[i] / (float)compdQ[i]) / PI * 180;
    //        else
    //            resAngle += 360 + atan((float)compdI[i] / (float)compdQ[i]) / PI * 180;
    //    }
    //    resAngle /= freqTurnCntr;

    //    int sampleStart = -1;

    //    int sampleEnd = -1;
    //    sampleStart = (sampleStart + sampleEnd) / 2 - 1 + 41 * oversampling;

    //    short* firstQ = new short[oversampling];
    //    int anyCnt = 0;
    //    for (int i = sampleStart - oversampling; i < sampleStart; i++)
    //    {
    //        firstQ[anyCnt] = compdQ[i] * cos((-45 + resAngle) * PI / 180) + compdI[i] * sin((-45 + resAngle) * PI / 180);
    //        anyCnt++;
    //    }

    //    delete[] freqTurnAngle;

    //    delete[] compdI;
    //    delete[] compdQ;

    //    short* compArr = new short[40];

    //    delete[] compArr;

    //    short* binArrPLet = new short[inputIQCnt / oversampling];

    //    int binArrCnt = 0;

    //    if (firstQ[0] > 0)
    //    {
    //        binArrPLet[binArrCnt] = 0;
    //    }
    //    else
    //    {
    //        binArrPLet[binArrCnt] = 1;
    //    }
    //    binArrCnt++;

    //    char finChar = '\0';

    //    int finCnt = 0;
    //    for (int i = 0; i < binArrCnt; i += 8)
    //    {
    //        for (int j = 0; j < 8; j++)
    //        {
    //            if (binArrPLet[i + j] == 0)
    //            {
    //                finChar &= ~(1 << j);
    //            }
    //            else if (binArrPLet[i + j] == 1)
    //            {
    //                finChar |= (1 << j);
    //            }
    //        }
    //        resArray[finCnt] = finChar;
    //        finCnt++;
    //    }

    //    delete[] binArrPLet;

    //    return finCnt;
    //}

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    //case 6:
    //{
    //    /*const int oversampling = (freqSpacing * 10) / modSpeed;

    //    ofstream lastChankFile("lastChank", ios::binary);

    //    short* inputI = new short[fileSize/2];
    //    short* inputQ = new short[fileSize/2];

    //    int inputIQCnt = 0;
    //    for (int i = 0; i < fileSize/2; i += 2)
    //    {
    //        inputI[inputIQCnt] = inputSignalArray[i];
    //        inputQ[inputIQCnt] = inputSignalArray[i + 1];
    //        inputIQCnt++;
    //    }

    //    float* mediumArrRecovered = new float[inputIQCnt];
    //    short* binArrFLet = new short [inputIQCnt / 8];

    //    int recArr = 0;
    //    for (int i = 0; i < inputIQCnt; i++)
    //    {
    //        mediumArrRecovered[recArr] = ((float)inputI[i]) * ((float)inputQ[i - 1]) - ((float)inputQ[i]) * ((float)inputI[i - 1]);
    //        recArr++;
    //    }

    //    delete [] inputI;
    //    delete [] inputQ;

    //    int compNum = 0;
    //    int charArrCnt = 0;
    //    for (int i = 0; i < recArr - 10*oversampling; i++)
    //    */

    //    short* inputI = new short[fileSize / 2];
    //    short* inputQ = new short[fileSize / 2];

    //    int inputIQCnt = 0;

    //    int syncSeqEnd = 0, syncSum = 0, syncMaxSum = 0;
    //    for (int i = 0; i < inputIQCnt; i++)
    //    {
    //        syncSum = 0;
    //        for (int j = 0; j < 500; j++)
    //        {
    //            syncSum += sqrt(inputI[i + j] * inputI[i + j] + inputQ[i + j] * inputQ[i + j]);
    //        }
    //        if (syncSum > syncMaxSum)
    //        {
    //            syncMaxSum = syncSum;
    //            syncSeqEnd = i + 479;
    //        }
    //    }

    //    int maxSampleLevel = 0;
    //    for (int i = 0; i < 400; i++)
    //    {
    //        maxSampleLevel += sqrt(inputI[syncSeqEnd - 450 + i] * inputI[syncSeqEnd - 450 + i] + inputQ[syncSeqEnd - 450 + i] * inputQ[syncSeqEnd - 450 + i]);
    //    }
    //    maxSampleLevel /= 400;

    //    int signalEnd = -1, signalEndSum = 0;
    //    for (int i = syncSeqEnd; i < inputIQCnt; i++)
    //    {
    //        signalEndSum = 0;
    //        for (int j = 0; j < 300; j++)
    //        {
    //            signalEndSum += sqrt(inputI[i + j] * inputI[i + j] + inputQ[i + j] * inputQ[i + j]);
    //        }
    //        if (signalEndSum < (maxSampleLevel * 300 / 21))
    //        {
    //            signalEnd = i;
    //            break;
    //        }
    //    }

    //    double maxValue = 0;
    //    for (int i = syncSeqEnd; i < signalEnd; i++)
    //    {
    //        if (((sqrt(pow((float)inputI[i], 2) + pow((float)inputQ[i], 2)) / 10000) - 1) / modDepth > maxValue)
    //        {
    //            maxValue = ((sqrt(pow((float)inputI[i], 2) + pow((float)inputQ[i], 2)) / 10000) - 1) / modDepth;
    //        }
    //    }

    //    int finArrCnt = 0;
    //    for (int i = syncSeqEnd; i < signalEnd; i++)
    //    {
    //        resWavArray[finArrCnt] = (((sqrt(pow((float)inputI[i], 2) + pow((float)inputQ[i], 2)) / 10000) - 1) / modDepth * (32768 / maxValue * 0.99));
    //        finArrCnt++;
    //    }

    //    delete[] inputI;
    //    delete[] inputQ;

    //    return finArrCnt;
    //}

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    //case 7:
    //{
    //    short* inputI = new short[fileSize / 2];
    //    short* inputQ = new short[fileSize / 2];

    //    int inputIQCnt = 0;

    //    int syncSeqEnd = 0, syncSum = 0, syncMaxSum = 0;
    //    for (int i = 0; i < inputIQCnt; i++)
    //    {
    //        syncSum = 0;
    //        for (int j = 0; j < 500; j++)
    //        {
    //            syncSum += sqrt(inputI[i + j] * inputI[i + j] + inputQ[i + j] * inputQ[i + j]);
    //        }
    //        if (syncSum > syncMaxSum)
    //        {
    //            syncMaxSum = syncSum;
    //            syncSeqEnd = i + 479;
    //        }
    //    }

    //    int maxSampleLevel = 0;
    //    for (int i = 0; i < 400; i++)
    //    {
    //        maxSampleLevel += sqrt(inputI[syncSeqEnd - 450 + i] * inputI[syncSeqEnd - 450 + i] + inputQ[syncSeqEnd - 450 + i] * inputQ[syncSeqEnd - 450 + i]);
    //    }
    //    maxSampleLevel /= 400;

    //    int signalEnd = -1, signalEndSum = 0;
    //    for (int i = syncSeqEnd; i < inputIQCnt; i++)
    //    {
    //        signalEndSum = 0;
    //        for (int j = 0; j < 300; j++)
    //        {
    //            signalEndSum += sqrt(inputI[i + j] * inputI[i + j] + inputQ[i + j] * inputQ[i + j]);
    //        }
    //        if (signalEndSum < (maxSampleLevel * 300 / 21))
    //        {
    //            signalEnd = i;
    //            break;
    //        }
    //    }

    //    double maxValue = 0;
    //    for (int i = syncSeqEnd; i < signalEnd; i++)
    //    {
    //        if (((sqrt(pow((float)inputI[i], 2) + pow((float)inputQ[i], 2)) / 10000) - 1) / modDepth > maxValue)
    //        {
    //            maxValue = ((sqrt(pow((float)inputI[i], 2) + pow((float)inputQ[i], 2)) / 10000) - 1) / modDepth;
    //        }
    //    }

    //    int finArrCnt = 0;
    //    for (int i = syncSeqEnd; i < signalEnd; i++)
    //    {
    //        resWavArray[finArrCnt] = (((sqrt(pow((float)inputI[i], 2) + pow((float)inputQ[i], 2)) / 10000) - 1) / modDepth * (32768 / maxValue * 0.99));
    //        finArrCnt++;
    //    }

    //    delete[] inputI;
    //    delete[] inputQ;

    //    return finArrCnt;
    //}

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    //case 8:
    //{
    //    const int oversampling = 10;

    //    short* inputI = new short[fileSize / 2];
    //    short* inputQ = new short[fileSize / 2];

    //    int inputIQCnt = 0;

    //    long syncMaxSum = -1, syncSeqStart = 0, syncSum = 0;
    //    for (int i = 0; i < inputIQCnt; i++)
    //    {
    //        syncSum = 0;
    //        for (int j = 0; j < 50 * oversampling; j++)
    //        {
    //            syncSum += sqrt(inputI[i + j] * inputI[i + j] + inputQ[i + j] * inputQ[i + j]);
    //        }
    //        if (syncSum > syncMaxSum)
    //        {
    //            syncMaxSum = syncSum;
    //            syncSeqStart = i;
    //        }
    //    }

    //    int* postFiltI = new int[inputIQCnt];
    //    int* postFiltQ = new int[inputIQCnt];

    //    Filter(inputI, postFiltI, inputIQCnt);
    //    Filter(inputQ, postFiltQ, inputIQCnt);

    //    long maxValue = 0;
    //    int maxCnt = 0;
    //    for (int i = syncSeqStart + 10 * oversampling; i < syncSeqStart + 40 * oversampling; i++)
    //    {
    //        maxValue += sqrt(pow((double)postFiltI[i], 2) + pow((double)postFiltQ[i], 2)) / 1.4;
    //        maxCnt++;
    //    }
    //    maxValue = maxValue / maxCnt;

    //    double* freqTurnAngle = new double[300];

    //    int* compdI = new int[inputIQCnt + FHSSChunkSize];
    //    int* compdQ = new int[inputIQCnt + FHSSChunkSize];

    //    int compdCnt = 0;
    //    for (int i = syncSeqStart; i < inputIQCnt; i++)
    //    {
    //        compdCnt++;
    //    }

    //    delete[] inputI;
    //    delete[] inputQ;

    //    float resAngle = 0;
    //    for (int i = 10 * oversampling; i < 40 * oversampling; i++)
    //    {
    //        if (compdI[i] >= 0 && compdQ[i] >= 0)
    //            resAngle += atan((float)compdI[i] / (float)compdQ[i]) / PI * 180;
    //        else if ((compdI[i] > 0 && compdQ[i] < 0) || (compdI[i] <= 0 && compdQ[i] < 0))
    //            resAngle += 180 + atan((float)compdI[i] / (float)compdQ[i]) / PI * 180;
    //        else
    //            resAngle += 360 + atan((float)compdI[i] / (float)compdQ[i]) / PI * 180;
    //    }
    //    resAngle /= 30 * oversampling;

    //    int* resI = new int[compdCnt + FHSSChunkSize * oversampling];
    //    int* resQ = new int[compdCnt + FHSSChunkSize * oversampling];

    //    int syncIQCnt = 0;
    //    for (int i = 0; i < 100 * oversampling; i++)
    //    {
    //        resI[syncIQCnt] = compdI[i] * cos((-45 + resAngle) * PI / 180) - compdQ[i] * sin((-45 + resAngle) * PI / 180);
    //        resQ[syncIQCnt] = compdQ[i] * cos((-45 + resAngle) * PI / 180) + compdI[i] * sin((-45 + resAngle) * PI / 180);
    //        syncIQCnt++;
    //    }

    //    int sampleStart = -1;

    //    int sampleEnd = -1;
    //    sampleStart = (sampleStart + sampleEnd) / 2 - 1 + 40 * oversampling;
    //    int resIQCnt = 0;

    //    int sampleDiff = sampleStart % oversampling;

    //    for (int i = sampleStart - sampleDiff; i < compdCnt; i++)
    //    {
    //        resI[resIQCnt] = compdI[i] * cos((-45 + resAngle) * PI / 180) - compdQ[i] * sin((-45 + resAngle) * PI / 180);
    //        resQ[resIQCnt] = compdQ[i] * cos((-45 + resAngle) * PI / 180) + compdI[i] * sin((-45 + resAngle) * PI / 180);
    //        resIQCnt++;
    //    }

    //    delete[] freqTurnAngle;

    //    delete[] compdI;
    //    delete[] compdQ;

    //    short* compArr = new short[40];

    //    int signalEnd = 0;

    //    delete[] compArr;

    //    short* binArrBPSKLet = new short[inputIQCnt / oversampling];

    //    int binArrCnt = 0;

    //    sampleDiff += 1;

    //    for (int i = sampleDiff; i < signalEnd / expCoef; i += oversampling)
    //    {
    //        if (binArrCnt != 0 && (binArrCnt % FHSSChunkSize == 0))
    //        {
    //            i += 20 * oversampling;
    //        }

    //        if (resQ[i] > 0)
    //        {
    //            binArrBPSKLet[binArrCnt] = 0;
    //        }
    //        else
    //        {
    //            binArrBPSKLet[binArrCnt] = 1;
    //        }
    //        binArrCnt++;
    //    }

    //    char finChar = '\0';

    //    int finArrCnt = 0;
    //    for (int i = 0; i < binArrCnt; i += 8)
    //    {
    //        for (int j = 0; j < 8; j++)
    //        {
    //            if (binArrBPSKLet[i + j] == 0)
    //            {
    //                finChar &= ~(1 << j);
    //            }
    //            else if (binArrBPSKLet[i + j] == 1)
    //            {
    //                finChar |= (1 << j);
    //            }
    //        }
    //        resArray[finArrCnt] = finChar;
    //        finArrCnt++;
    //    }

    //    return finArrCnt;
    //}

    return ALL_OK;
}