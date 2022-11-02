    #include "sig_mod.h" 
    #include "fhilbt.h"
    #include "qam_func.h"

    using namespace std;
    const double PI = 3.141592653589793238463;

    enum filtType { FILT_101_coef = 1, FILT_47_coef = 2, FILT_57_coef = 3, FILT_47_coef_ = 4, FILT_81_coef = 5 };

    wchar_t charactersRuUpCase[] = {
    '*',        L'А',       L'Б',       L'В',       L'Г',
    L'Д',       L'Е',       L'Ё',       L'Ж',       L'З',
    L'И',       L'Й',       L'К',       L'Л',       L'М',
    L'Н',       L'О',       L'П',       L'Р',       L'С',
    L'Т',       L'У',       L'Ф',       L'Х',       L'Ц',
    L'Ч',       L'Ш',       L'Щ',       L'Ъ',       L'Ы',
    L'Ь',       L'Э',       L'Ю',       L'Я' };
    wchar_t charactersRuDnCase[] = {
    '*',        L'а',       L'б',       L'в',       L'г',
    L'д',       L'е',       L'ё',       L'ж',       L'з',
    L'и',       L'й',       L'к',       L'л',       L'м',
    L'н',       L'о',       L'п',       L'р',       L'с',
    L'т',       L'у',       L'ф',       L'х',       L'ц',
    L'ч',       L'ш',       L'щ',       L'ъ',       L'ы',
    L'ь',       L'э',       L'ю',       L'я' };
    char charactersEnUpCase[] = {
    '*',    'A',	'B',	'W',	'G',
    'D',    'E',	'*',	'V',	'Z',
    'I',    'J',	'K',	'L',	'M',
    'N',    'O',	'P',	'R',	'S',
    'T',    'U',	'F',	'H',	'C',
    '*',    '*',	'Q',	'*',	'Y',
    'X' };
    char charactersEnDnCase[] = {
    '*',    'a',	'b',	'w',	'g',
    'd',    'e',	'*',	'v',	'z',
    'i',    'j',	'k',	'l',	'm',
    'n',    'o',	'p',	'r',	's',
    't',    'u',	'f',	'h',	'c',
    '*',    '*',	'q',	'*',	'y',
    'x' };
    wchar_t symbols[] = {
    '1',  '2',    '3',    '4',        '5',
    '6',  '7',    '8',    '9',        '0',
    '.',  ',',    ':',    ';',        '(',
    ')',  '\'',   '"',    '-',        '/',
    '?',  '!',    '@',    '\n',       L'№' };
    std::string codeMorse[] = {
    " ",        ".-",		"-...",		".--",		"--.",
    "-..",      ".",		"-...-",	"...-",		"--..",
    "..",       ".---",		"-.-",		".-..",		"--",
    "-.",       "---",		".--.",		".-.",		"...",
    "-",        "..-",		"..-.",		"....",		"-.-.",
    "---.",     "----",		"--.-",		"--.--",	"-.--",
    "-..-",     "..-..",	"..--",		".-.-",		".----",
    "..---",    "...--",	"....-",	".....",	"-....",
    "--...",    "---..",	"----.",	"-----",	"......",
    ".-.-.-",   "---...",	"-.-.-.",	"-.--.-",	"-.----",
    ".----.",   ".-..-.",	"-....-",	"-..-.",	"..--..",
    "--..--",   ".--.-.",	"-..-.-",	"-..--.",	".-.-." };

    void Point(vector <short> &binVector)
    {
        binVector.push_back(1); 
        binVector.push_back(0);
    }
    void Dash(vector <short> &binVector)
    {
        binVector.push_back(1);
        binVector.push_back(1);
        binVector.push_back(1);
        binVector.push_back(0);
    }
    void Space(vector <short> &binVector)
    {
        binVector.push_back(0);
        binVector.push_back(0);
    }

    void lineBr(vector <short> &binVector)
    {
        Point(binVector); Point(binVector); Point(binVector); Dash(binVector); Point(binVector); Point(binVector); Space(binVector); Space(binVector); Space(binVector);
    }
    void BrdcstStart(vector <short> &binVector)
    {
        Dash(binVector); Point(binVector); Point(binVector); Dash(binVector); Dash(binVector); Point(binVector); Space(binVector); Space(binVector); Space(binVector);
    }
    void BrdcstEnd(vector <short> &binVector)
    {
        Point(binVector); Dash(binVector); Point(binVector); Dash(binVector); Point(binVector); Space(binVector); Space(binVector); Space(binVector);
    }

    void Filter(vector <float> in, vector <float> &out, int inpSize, filtType filterType)
    {
        switch (filterType)
        {
            case FILT_101_coef:
            {
                const int N = 101;
                short H[101] = { 1, 0, 0, -1, -1, -1, -1, -1, -1, 0, 0, 1, 1, 2, 2, 1, 0, -1, -2, -2, -3, -3, -2, -1, 1, 3, 5, 7, 8, 8, 7, 4, 0, -5, -11, -16, -20, -22, -21, -17, -10, 1, 16, 33, 51, 70, 89, 104, 117, 124, 127, 124, 117, 104, 89, 70, 51, 33, 16, 1, -10, -17, -21, -22, -20, -16, -11, -5, 0, 4, 7, 8, 8, 7, 5, 3, 1, -1, -2, -3, -3, -2, -2, -1, 0, 1, 2, 2, 1, 1, 0, 0, -1, -1, -1, -1, -1, -1, 0, 0, 1 };
                for (int i = 0; i < inpSize; i++)
                {
                    out[i] = 0.;
                    for (int j = 0; j < N - 1; j++)
                        if (i - j >= 0)
                            out[i] += H[j] * in[i - j];
                }
                break;
            }
            case FILT_47_coef:
            {
                const int N = 47;
                short H[47] = { 1, 4, 6, 8, 8, 7, 4, -1, -6, -12, -18, -21, -22, -18, -10, 2, 19, 38, 59, 80, 99, 114, 124, 127, 124, 114, 99, 80, 59, 38, 19, 2, -10, -18, -22, -21, -18, -12, -6, -1, 4, 7, 8, 8, 6, 4, 1 };
                for (int i = 0; i < inpSize; i++)
                {
                    out[i] = 0.;
                    for (int j = 0; j < N - 1; j++)
                        if (i - j >= 0)
                            out[i] += H[j] * in[i - j];
                }
                break;
            }
            case FILT_57_coef:
            {
                const int N = 57;
                short H[57] = { 0, 1, 2, 2, 3, 3, 3, 2, 0, -2, -6, -9, -12, -15, -17, -17, -14, -8, 0, 11, 25, 42, 59, 76, 93, 107, 118, 125, 127, 125, 118, 107, 93, 76, 59, 42, 25, 11, 0, -8, -14, -17, -17, -15, -12, -9, -6, -2, 0, 2, 3, 3, 3, 2, 2, 1, 0 };
                for (int i = 0; i < inpSize; i++)
                {
                    out[i] = 0.;
                    for (int j = 0; j < N; j++)
                        if (i - j >= 0)
                            out[i] += H[j] * in[i - j];
                }
                break;
            }
            case FILT_47_coef_:
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
                break;
            }
            case FILT_81_coef:
            {
                const int N = 81;
                short H[81] = { 0, -1 ,-2, -4, -6, -7, -9, -11, -12, -14, -15, -16, -17, -17, -17, -16, -14, -12, -8, -5, 0, 5, 11, 18, 25, 33, 42, 50, 59, 68, 76, 85, 93, 100, 107, 113, 118, 122, 125, 126, 127, 126, 125, 122, 118, 113, 107, 100, 93, 85, 76, 68, 59, 50, 42, 33, 25, 18, 11, 5, 0, -5, -8, -12, -14, -16, -17, -17, -17, -16, -15, -14, -12, -11, -9, -7, -6, -4, -2, -1, 0 };
                for (int i = 0; i < inpSize; i++)
                {
                    out[i] = 0.;
                    for (int j = 0; j < N - 1; j++)
                        if (i - j >= 0)
                            out[i] += H[j] * in[i - j];
                }
                break;
            }
        }
    }

    void Modulation::setParams(string inputFilePath, string outputFilePath, short modType, short FHSSSpeed, int modSpeed, int freqSpacing, float modDepth, float supprCoeff, int bandWidth, int freqDeviation)
    {
        this->inputFilePath = inputFilePath;
        this->outputFilePath = outputFilePath;

        this->modType = modType;
        this->FHSSSpeed = FHSSSpeed;

        this->modSpeed = modSpeed;
        this->freqSpacing = freqSpacing;
        this->modDepth = modDepth;
        this->supprCoeff = supprCoeff;
        this->bandWidth = bandWidth;
    }

    void Modulation::converterToText()
    {
        ifstream inputFile(inputFilePath, ios::binary);

        inputFile.seekg(0, ios::end);
        int fileSize = inputFile.tellg();
        inputFile.seekg(0, ios::beg);

        char inputSymbol;

        for (int i = 0; i < fileSize; i++)
        {
            inputFile.read((char*)&inputSymbol, sizeof(char));
            inputTextVector.push_back(inputSymbol);
        }
    }
    void Modulation::converterToBin()
    {
        ifstream inputFile(inputFilePath, ios::binary);

        inputFile.seekg(0, ios::end);
        int fileSize = inputFile.tellg();
        inputFile.seekg(0, ios::beg);

        char inputSymbol;

        for (int i = 0; i < fileSize; i++)
        {
            inputFile.read((char*)&inputSymbol, sizeof(char));

            for (int j = 0; j < 8; j++)
            {
                binaryVector.push_back(((inputSymbol >> j) & 1));
            }
        }
    }
    void Modulation::converterToWav()
    {
        ifstream inputFile(inputFilePath, ios::binary);

        inputFile.seekg(0, ios::end);
        int fileSize = inputFile.tellg();
        inputFile.seekg(0, ios::beg);

        char inputSymbol;

        for (int i = 0; i < fileSize; i++)
        {
            inputFile.read((char*)&inputSymbol, sizeof(char));
            inputWavVector.push_back(inputSymbol);
        }

        inputWavVector.erase(inputWavVector.begin(), inputWavVector.begin() + 22);
    }

    Modulation::errType Modulation::paramCheck()
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

    Modulation::errType Modulation::modulation()
    {
        if (paramCheck() != 0)
        {
            return paramCheck();
        }

        switch (modType)            // Преобразование входного файла в нужный формат
        {
            case AMod_Morse:
            case FMod_Morse:
                converterToText();
                break;

            case AMod_AnTeleph:
            case AMod_AnTeleph_SupprCarr:
            case USW_AMod_AnTeleph:
            case USW_AMod_AnTeleph_SupprCarr:
                converterToWav();
                break;

            default:
                converterToBin();
                break;
        }

        switch (modType)            // Модуляция
        {
            case AMod_Morse:
            {
                filtType modType = FILT_101_coef;
                const int oversampling = 100;

                vector <short> binVector;

                BrdcstStart(binVector);
                for (int i = 0; i < inputTextVector.size(); i++)
                {
                    if (inputTextVector[i] == 10)
                    {
                        lineBr(binVector);
                    }

                    else
                    {
                        for (int morsNum = 0; morsNum < 33; morsNum++)
                        {
                            if (charactersRuUpCase[morsNum] == (inputTextVector[i]))
                            {
                                if ((unsigned int)inputTextVector[i] == 32)
                                {
                                    Space(binVector);
                                }

                                else
                                {
                                    for (unsigned int n = 0; n < codeMorse[morsNum].length(); n++)
                                    {
                                        switch (codeMorse[morsNum][n])
                                        {
                                        case '.':
                                            Point(binVector);
                                            break;
                                        case '-':
                                            Dash(binVector);
                                            break;
                                        default:
                                            break;
                                        }
                                    }
                                }
                                Space(binVector);
                                break;
                            }

                            else if (charactersRuDnCase[morsNum] == (inputTextVector[i]))
                            {
                                for (unsigned int n = 0; n < codeMorse[morsNum].length(); n++)
                                {
                                    switch (codeMorse[morsNum][n])
                                    {
                                    case '.':
                                        Point(binVector);
                                        break;
                                    case '-':
                                        Dash(binVector);
                                        break;
                                    default:
                                        break;
                                    }
                                }
                                Space(binVector);
                                break;
                            }

                            else if (charactersEnUpCase[morsNum] == (inputTextVector[i]))
                            {
                                for (unsigned int n = 0; n < codeMorse[morsNum].length(); n++)
                                {
                                    switch (codeMorse[morsNum][n])
                                    {
                                    case '.':
                                        Point(binVector);
                                        break;
                                    case '-':
                                        Dash(binVector);
                                        break;
                                    default:
                                        break;
                                    }
                                }
                                Space(binVector);
                                break;
                            }

                            else if (charactersEnDnCase[morsNum] == (inputTextVector[i]))
                            {
                                for (unsigned int n = 0; n < codeMorse[morsNum].length(); n++)
                                {
                                    switch (codeMorse[morsNum][n])
                                    {
                                    case '.':
                                        Point(binVector);
                                        break;
                                    case '-':
                                        Dash(binVector);
                                        break;
                                    default:
                                        break;
                                    }
                                }
                                Space(binVector);
                                break;
                            }

                            else if (symbols[morsNum] == (inputTextVector[i]))
                            {
                                for (unsigned int n = 0; n < codeMorse[morsNum + 34].length(); n++)
                                {
                                    switch (codeMorse[morsNum + 34][n])
                                    {
                                    case '.':
                                        Point(binVector);
                                        break;
                                    case '-':
                                        Dash(binVector);
                                        break;
                                    default:
                                        break;
                                    }
                                }
                                Space(binVector);
                                break;
                            }
                        }
                    }
                }
                BrdcstEnd(binVector);

                int vectorSize = binVector.size() * oversampling;

                vector <float> binaryVectorIExpanded(vectorSize);
                vector <float> binaryVectorQExpanded(vectorSize);
                vector <float> binaryVectorIFiltered(vectorSize);
                vector <float> binaryVectorQFiltered(vectorSize);

                for (int i = 0; i < binVector.size(); i++)
                {
                    if (binVector[i] == 0)
                    {
                        for (int j = 0; j < oversampling; j++)
                        {
                            binaryVectorIExpanded[i * oversampling + j] = 0;
                            binaryVectorQExpanded[i * oversampling + j] = 0;
                        }
                    }
                    if (binVector[i] == 1)
                    {
                        for (int j = 0; j < oversampling; j++)
                        {
                            binaryVectorIExpanded[i * oversampling + j] = 1;
                            binaryVectorQExpanded[i * oversampling + j] = 1;
                        }
                    }
                }

                Filter(binaryVectorIExpanded, binaryVectorIFiltered, vectorSize, modType);
                Filter(binaryVectorQExpanded, binaryVectorQFiltered, vectorSize, modType);

                ofstream outputPcm(outputFilePath, ios::binary | ios::trunc);
                for (int i = 0; i < vectorSize; i++)
                {
                    short finQuad = binaryVectorIFiltered[i] * 26;
                    outputPcm.write((char*)&finQuad, sizeof(short));
                    finQuad = binaryVectorQFiltered[i] * 26;
                    outputPcm.write((char*)&finQuad, sizeof(short));

                }
                break;
            }

            case FMod_Morse:
            {
                filtType modType = FILT_101_coef;
                const int oversampling = (freqSpacing * 10) / modSpeed;
                const float modIndex = (float)freqSpacing / (float)modSpeed;

                vector <short> binVector;

                BrdcstStart(binVector);
                for (int i = 0; i < inputTextVector.size(); i++)
                {
                    if (inputTextVector[i] == 10)
                    {
                        lineBr(binVector);
                    }

                    else
                    {
                        for (int morsNum = 0; morsNum < 33; morsNum++)
                        {
                            if (charactersRuUpCase[morsNum] == (inputTextVector[i]))
                            {
                                if ((unsigned int)inputTextVector[i] == 32)
                                {
                                    Space(binVector);
                                }

                                else
                                {
                                    for (unsigned int n = 0; n < codeMorse[morsNum].length(); n++)
                                    {
                                        switch (codeMorse[morsNum][n])
                                        {
                                        case '.':
                                            Point(binVector);
                                            break;
                                        case '-':
                                            Dash(binVector);
                                            break;
                                        default:
                                            break;
                                        }
                                    }
                                }
                                Space(binVector);
                                break;
                            }

                            else if (charactersRuDnCase[morsNum] == (inputTextVector[i]))
                            {
                                for (unsigned int n = 0; n < codeMorse[morsNum].length(); n++)
                                {
                                    switch (codeMorse[morsNum][n])
                                    {
                                    case '.':
                                        Point(binVector);
                                        break;
                                    case '-':
                                        Dash(binVector);
                                        break;
                                    default:
                                        break;
                                    }
                                }
                                Space(binVector);
                                break;
                            }

                            else if (charactersEnUpCase[morsNum] == (inputTextVector[i]))
                            {
                                for (unsigned int n = 0; n < codeMorse[morsNum].length(); n++)
                                {
                                    switch (codeMorse[morsNum][n])
                                    {
                                    case '.':
                                        Point(binVector);
                                        break;
                                    case '-':
                                        Dash(binVector);
                                        break;
                                    default:
                                        break;
                                    }
                                }
                                Space(binVector);
                                break;
                            }

                            else if (charactersEnDnCase[morsNum] == (inputTextVector[i]))
                            {
                                for (unsigned int n = 0; n < codeMorse[morsNum].length(); n++)
                                {
                                    switch (codeMorse[morsNum][n])
                                    {
                                    case '.':
                                        Point(binVector);
                                        break;
                                    case '-':
                                        Dash(binVector);
                                        break;
                                    default:
                                        break;
                                    }
                                }
                                Space(binVector);
                                break;
                            }

                            else if (symbols[morsNum] == (inputTextVector[i]))
                            {
                                for (unsigned int n = 0; n < codeMorse[morsNum + 34].length(); n++)
                                {
                                    switch (codeMorse[morsNum + 34][n])
                                    {
                                    case '.':
                                        Point(binVector);
                                        break;
                                    case '-':
                                        Dash(binVector);
                                        break;
                                    default:
                                        break;
                                    }
                                }
                                Space(binVector);
                                break;
                            }
                        }
                    }
                }
                BrdcstEnd(binVector);

                int vectorSize = binVector.size() * oversampling;

                vector <float> binaryVectorExpanded(vectorSize);
                vector <float> binaryVectorFiltered(vectorSize);
                vector <float> binaryFVectorFiltered(vectorSize);
                vector <float> modulatedVector(vectorSize);

                for (int i = 0; i < binVector.size(); i++)
                {
                    if (binVector[i] == 0)
                    {
                        for (int j = 0; j < oversampling; j++)
                        {
                            binaryVectorExpanded[i * oversampling + j] = 1;
                        }
                    }
                    if (binVector[i] == 1)
                    {
                        for (int j = 0; j < oversampling; j++)
                        {
                            binaryVectorExpanded[i * oversampling + j] = -1;
                        }
                    }
                }

                Filter(binaryVectorExpanded, binaryVectorFiltered, vectorSize, modType);

                for (int i = 0; i < vectorSize; i++)
                {
                    binaryFVectorFiltered[i] = ((modIndex * PI * ((float)binaryVectorFiltered[i] / 1055.96)) / oversampling);
                }

                modulatedVector[0] = (2 * PI * ((binaryFVectorFiltered[0] / (2 * PI)) - floor((binaryFVectorFiltered[0] / (2 * PI)) + 0.5)));
                for (int i = 1; i < vectorSize; i++)
                {
                    modulatedVector[i] = (float)(2.0 * PI * (((modulatedVector[i - 1] + binaryFVectorFiltered[i]) / (2.0 * PI)) - floor(((modulatedVector[i - 1] + binaryFVectorFiltered[i]) / (2.0 * PI)) + 0.5)));
                }

                ofstream outputPcm(outputFilePath, ios::binary | ios::trunc);
                for (int i = 0; i < vectorSize; i++)
                {
                    short Iquad = sin(modulatedVector[i]) * 32000;
                    short Qquad = cos(modulatedVector[i]) * 32000;
                    outputPcm.write((char*)&Iquad, sizeof(short));
                    outputPcm.write((char*)&Qquad, sizeof(short));
                }
                break;
            }

            case FMod_DigTeleph:
            {
                filtType modType = FILT_47_coef;
                const int oversampling = (freqSpacing * 10) / modSpeed;
                const float modIndex = (float)freqSpacing / (float)modSpeed;

                int vectorSize = binaryVector.size() * oversampling;

                vector <float> binaryVectorExpanded(vectorSize);
                vector <float> binaryVectorFiltered(vectorSize);
                vector <float> binaryFVectorFiltered(vectorSize);
                vector <float> modulatedVector(vectorSize);

                int inArrCnt = 0;
                for (int i = 0; i < binaryVector.size(); i++)
                {
                    if (binaryVector[i] == 0)
                    {
                        for (int j = 0; j < oversampling; j++)
                        {
                            binaryVectorExpanded[i*oversampling + j] = 1;
                        }
                    }
                    if (binaryVector[i] == 1)
                    {
                        for (int j = 0; j < oversampling; j++)
                        {
                            binaryVectorExpanded[i * oversampling + j] = -1;
                        }
                    }
                }

                Filter(binaryVectorExpanded, binaryVectorFiltered, vectorSize, modType);

                for (int i = 0; i < vectorSize; i++)
                {
                    binaryFVectorFiltered[i] = (modIndex * PI * ((float)binaryVectorFiltered[i] / 1055.96)) / oversampling;
                }

                modulatedVector[0] = 2 * PI * ((binaryFVectorFiltered[0] / (2 * PI)) - floor((binaryFVectorFiltered[0] / (2 * PI)) + 0.5));
                for (int i = 1; i < vectorSize; i++)
                {
                    modulatedVector[i] = (float)(2.0 * PI * (((binaryFVectorFiltered[i - 1] + binaryFVectorFiltered[i]) / (2.0 * PI)) - floor(((binaryFVectorFiltered[i - 1] + binaryFVectorFiltered[i]) / (2.0 * PI)) + 0.5)));
                }

                ofstream outputPcm(outputFilePath, ios::binary | ios::trunc);
                for (int i = 0; i < vectorSize; i++)
                {
                    short Iquad = sin(modulatedVector[i]) * 32000;
                    short Qquad = cos(modulatedVector[i]) * 32000;
                    outputPcm.write((char*)&Iquad, sizeof(short));
                    outputPcm.write((char*)&Qquad, sizeof(short));
                }
                break;
            }

            case PhMod_DigTeleph_2Pos:
            {
                filtType modType = FILT_47_coef;
                const int oversampling = 100;

                int vectorSize = binaryVector.size() * oversampling;

                vector <float> binaryVectorIExpanded(vectorSize);
                vector <float> binaryVectorQExpanded(vectorSize);

                vector <float> binaryVectorIFiltered(vectorSize);
                vector <float> binaryVectorQFiltered(vectorSize);

                for (int i = 0; i < binaryVector.size() - 1; i++)
                {
                    if (binaryVector[i] == 0 && binaryVector[i + 1] == 0)
                    {
                        for (int j = 0; j < oversampling; j++)
                        {
                            binaryVectorIExpanded[i * oversampling + j] = 1;
                            binaryVectorQExpanded[i * oversampling + j] = 1;
                        }
                    }
                    else if (binaryVector[i] == 0 && binaryVector[i + 1] == 1)
                    {
                        for (int j = 0; j < oversampling; j++)
                        {
                            binaryVectorIExpanded[i * oversampling + j] = -1;
                            binaryVectorQExpanded[i * oversampling + j] = -1;
                        }
                    }
                    else if (binaryVector[i] == 1 && binaryVector[i + 1] == 0)
                    {
                        for (int j = 0; j < oversampling; j++)
                        {
                            binaryVectorIExpanded[i * oversampling + j] = -1;
                            binaryVectorQExpanded[i * oversampling + j] = -1;
                        }
                    }
                    else if (binaryVector[i] == 1 && binaryVector[i + 1] == 1)
                    {
                        for (int j = 0; j < oversampling; j++)
                        {
                            binaryVectorIExpanded[i * oversampling + j] = 1;
                            binaryVectorQExpanded[i * oversampling + j] = 1;
                        }
                    }
                }

                Filter(binaryVectorIExpanded, binaryVectorIFiltered, vectorSize, modType);
                Filter(binaryVectorQExpanded, binaryVectorQFiltered, vectorSize, modType);

                ofstream outputPcm(outputFilePath, ios::binary | ios::trunc);
                for (int i = 0; i < vectorSize; i++)
                {
                    short finQuad = binaryVectorIFiltered[i] * 27;
                    outputPcm.write((char*)&finQuad, sizeof(short));
                    finQuad = binaryVectorQFiltered[i] * 27;
                    outputPcm.write((char*)&finQuad, sizeof(short));
                }
                break;
            }

            case PhMod_DigTeleph_4Pos:
            {
                filtType modType = FILT_57_coef;
                const int oversampling = 100;

                int vectorSize = binaryVector.size() * oversampling;

                vector <float> binaryVectorIExpanded(vectorSize);
                vector <float> binaryVectorQExpanded(vectorSize);

                vector <float> binaryVectorIFiltered(vectorSize);
                vector <float> binaryVectorQFiltered(vectorSize);

                int cornCnt = 0, circSec = 0;
                for (int i = 0; i < binaryVector.size() - 1; i++)
                {
                    if (binaryVector[i] == 0 && binaryVector[i + 1] == 1)
                    {
                        cornCnt += 1;
                    }
                    else if (binaryVector[i] == 1 && binaryVector[i + 1] == 0)
                    {
                        cornCnt += 2;
                    }
                    else if (binaryVector[i] == 1 && binaryVector[i + 1] == 1)
                    {
                        cornCnt += 3;
                    }
                    else
                    {
                        cornCnt += 0;
                    }

                    circSec = cornCnt % 4; 

                    switch (circSec)
                    {
                        case 0:
                            for (int j = 0; j < oversampling; j++)
                            {
                                binaryVectorIExpanded[i * oversampling + j] = 1;
                                binaryVectorQExpanded[i * oversampling + j] = 1;
                            }
                        break;
                        case 1:
                            for (int j = 0; j < oversampling; j++)
                            {
                                binaryVectorIExpanded[i * oversampling + j] = 1;
                                binaryVectorQExpanded[i * oversampling + j] = -1;
                            }
                        break;
                        case 2:
                            for (int j = 0; j < oversampling; j++)
                            {
                                binaryVectorIExpanded[i * oversampling + j] = -1;
                                binaryVectorQExpanded[i * oversampling + j] = -1;
                            }
                        break;
                        case 3:
                            for (int j = 0; j < oversampling; j++)
                            {
                                binaryVectorIExpanded[i * oversampling + j] = -1;
                                binaryVectorQExpanded[i * oversampling + j] = 1;
                            }
                        break;
                    }
                }

                Filter(binaryVectorIExpanded, binaryVectorIFiltered, vectorSize, modType);
                Filter(binaryVectorQExpanded, binaryVectorQFiltered, vectorSize, modType);

                ofstream outputPcm(outputFilePath, ios::binary | ios::trunc);
                for (int i = 0; i < vectorSize; i++)
                {
                    short finQuad = binaryVectorIFiltered[i] * 22;
                    outputPcm.write((char*)&finQuad, sizeof(short));
                    finQuad = binaryVectorQFiltered[i] * 22;
                    outputPcm.write((char*)&finQuad, sizeof(short));
                }
                break;
            }

            case AMod_AnTeleph:
            {
                filtType modType = FILT_47_coef_;

                int vectorSize = inputWavVector.size();

                vector <float> wavVectorIExpanded(vectorSize + 500);
                vector <float> wavVectorQExpanded(vectorSize + 500);
                vector <float> wavVectorIFiltered(vectorSize + 500);
                vector <float> wavVectorQFiltered(vectorSize + 500);

                for (int i = 0; i < 250; i++)
                {
                    wavVectorIExpanded[i] = 24;
                    wavVectorQExpanded[i] = 24;
                }
                for (int i = 250; i < 500; i++)
                {
                    wavVectorIExpanded[i] = 0;
                    wavVectorQExpanded[i] = 0;
                }

                Filter(wavVectorIExpanded, wavVectorIFiltered, vectorSize, modType);
                Filter(wavVectorQExpanded, wavVectorQFiltered, vectorSize, modType);

                int wavMaxValue = 0;

                for (int i = 0; i < vectorSize; i++)
                {
                    if (abs((int)inputWavVector[i]) > wavMaxValue)
                        wavMaxValue = (short)abs((int)inputWavVector[i]);
                }

                for (int i = 500; i < vectorSize + 500; i++)
                {
                    wavVectorIFiltered[i] = 0;
                    wavVectorQFiltered[i] = (10000 * (1 + modDepth * ((float)inputWavVector[i - 500] / wavMaxValue)));
                }

                ofstream outputPcm(outputFilePath, ios::binary | ios::trunc);
                for (int i = 0; i < vectorSize; i++)
                {
                    short finQuad = wavVectorIFiltered[i];
                    outputPcm.write((char*)&finQuad, sizeof(short));
                    finQuad = wavVectorQFiltered[i];
                    outputPcm.write((char*)&finQuad, sizeof(short));
                }
                break;
            }

            case AMod_AnTeleph_SupprCarr:
            {
                filtType modType = FILT_81_coef;

                int vectorSize = inputWavVector.size();

                int hilbArrCnt = 1;
                while (hilbArrCnt < vectorSize)
                    hilbArrCnt *= 2;
                double* hilbArr = new double[hilbArrCnt * 2];

                vector <float> wavVectorIExpanded(hilbArrCnt * 2 + 500);
                vector <float> wavVectorQExpanded(hilbArrCnt * 2 + 500);
                vector <float> wavVectorIFiltered(hilbArrCnt * 2 + 500);
                vector <float> wavVectorQFiltered(hilbArrCnt * 2 + 500);

                for (int i = 0; i < 250; i++)
                {
                    wavVectorIExpanded[i] = 24;
                    wavVectorQExpanded[i] = 24;
                }
                for (int i = 250; i < 500; i++)
                {
                    wavVectorIExpanded[i] = 0;
                    wavVectorQExpanded[i] = 0;
                }

                Filter(wavVectorIExpanded, wavVectorIFiltered, 500, modType);
                Filter(wavVectorQExpanded, wavVectorQFiltered, 500, modType);

                int wavMaxValue = 0;

                for (int i = 0; i < hilbArrCnt; i += 2)
                {
                    hilbArr[i] = inputWavVector[i / 2];
                    hilbArr[i + 1] = 0;
                }
                Hilbert_Transform::hilbert(hilbArr, hilbArrCnt);

                for (int i = 0; i < vectorSize; i++)
                {
                    if (abs((int)hilbArr[i]) > wavMaxValue)
                        wavMaxValue = (short)abs((int)hilbArr[i]);
                }

                for (int i = 500; i < hilbArrCnt + 500; i++)
                {
                    wavVectorIFiltered[i] = (10000 * (2 * supprCoeff + (hilbArr[(i - 500) * 2] / wavMaxValue)));
                    wavVectorQFiltered[i] = (10000 * (hilbArr[(i - 500) * 2 + 1] / wavMaxValue));
                }

                delete[] hilbArr;

                ofstream outputPcm(outputFilePath, ios::binary | ios::trunc);
                for (int i = 0; i < vectorSize; i++)
                {
                    short finQuad = wavVectorIFiltered[i];
                    outputPcm.write((char*)&finQuad, sizeof(short));
                    finQuad = wavVectorQFiltered[i];
                    outputPcm.write((char*)&finQuad, sizeof(short));
                }
                break;
            }

            case PSK2:
            {
                filtType modType = FILT_47_coef_;
                const int oversampling = 10;

                int vectorSize = binaryVector.size() * oversampling;

                vector <float> binVectorIMapped(binaryVector.size());
                vector <float> binVectorQMapped(binaryVector.size());
                vector <float> binaryVectorIExpanded(vectorSize);
                vector <float> binaryVectorQExpanded(vectorSize);
                vector <float> binaryVectorIFiltered(vectorSize);
                vector <float> binaryVectorQFiltered(vectorSize);

                QAM_Synth::Synth_BPSK(binaryVector, binVectorIMapped, binVectorQMapped, binaryVector.size());

                for (int i = 0; i < binaryVector.size(); i++)
                {
                    binaryVectorIExpanded[i * oversampling] = binVectorIMapped[i];
                    binaryVectorQExpanded[i * oversampling] = binVectorQMapped[i];

                    for (int j = 1; j < (oversampling); j++)
                    {
                        binaryVectorIExpanded[i * oversampling + j] = 0;
                        binaryVectorQExpanded[i * oversampling + j] = 0;
                    }
                }

                Filter(binaryVectorIExpanded, binaryVectorIFiltered, vectorSize, modType);
                Filter(binaryVectorQExpanded, binaryVectorQFiltered, vectorSize, modType);

                ofstream outputPcm(outputFilePath, ios::binary | ios::trunc);
                for (int i = 0; i < vectorSize; i++)
                {
                    short finQuad = binaryVectorIFiltered[i] * 190;
                    outputPcm.write((char*)&finQuad, sizeof(short));
                    finQuad = binaryVectorQFiltered[i] * 190;
                    outputPcm.write((char*)&finQuad, sizeof(short));
                }

                break;
            }

            break;
        }

        return ALL_OK;
    }
