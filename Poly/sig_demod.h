class Demodulation
{
    private:
        std::string inputFilePath;
        std::string resFilePath;

        short modType = 0;
        short FHSSSpeed = 0;

        int modSpeed = 0;
        int freqSpacing = 0;
        float modDepth = 0;
        float supprCoeff = 0;
        int bandWidth = 0;
        int freqDeviation = 0;

        short expCoef = 0;

    public:
        enum errType { ALL_OK, INPUT_FILE_ERR, MOD_TYPE_ERR, FHSS_SPEED_ERR, MOD_SPEED_ERR, FREQ_SPACING_ERR, MOD_DEPTH_ERR, SUPPR_COEFF_ERR, BAND_WIDTH_ERR, FREQ_DEVIATION_ERR };
        enum modType {
            AMod_Morse = 1, FMod_Morse = 2, FMod_DigTeleph = 3, PhMod_DigTeleph_2Pos = 4, PhMod_DigTeleph_4Pos = 5, AMod_AnTeleph = 6, AMod_AnTeleph_SupprCarr = 7,
            PSK2 = 8, PSK4 = 9, PSK8 = 10, QAM16 = 11, QAM32 = 12, QAM64 = 13, QAM256 = 14,
            USW_FMod_AnTeleph = 15, USW_FMod_DigTeleph = 16, USW_PhMod_DigTeleph = 17, USW_AMod_AnTeleph = 18, USW_AMod_AnTeleph_SupprCarr = 19, USW_GMSK = 20
        };

        struct levelEvaluatorResults
        {
            float absError;
            float relError;
            float dispersion;
            float standDeviation;
            float maxValue;
            float maxMedValue;
        };

        struct comparisonResults
        {
            int sourceCnt;
            int matchCnt;
            float finRatio;
        };

        Demodulation(std::string _inputFilePath, std::string _resFilePath, short _modType, short _FHSSSpeed, int _modSpeed, int _freqSpacing, float _modDepth, float _supprCoeff, int _bandWidth, int _freqDeviation)
        {
            inputFilePath = _inputFilePath;
            resFilePath = _resFilePath;

            modType = _modType;
            FHSSSpeed = _FHSSSpeed;

            modSpeed = _modSpeed;
            freqSpacing = _freqSpacing;
            modDepth = _modDepth;
            supprCoeff = _supprCoeff;
            bandWidth = _bandWidth;
        };

        errType paramCheck();
        errType demodulation();

        levelEvaluatorResults Level_evaluator(std::string, int);
        comparisonResults BitErrorRate(std::string, std::string);
};
