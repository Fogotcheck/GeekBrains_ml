#include "../hdr/EdgeImpulsGenerateData.h"

using namespace std;

errno_t CreateOutFile(void);
void SetFormatISO_8601(string &str, time_t lt);
void InitRand(void);
double AddNoise(void);

void ImitateData(void);
FILE *out;
errno_t CreateOutFile(void)
{
    string fileName;
    errno_t ret = 0;
    cin >> fileName;
    fileName += ".csv";
    out = fopen((char *)&fileName[0], "w");
    if (out == NULL)
    {
        cout << "Err::open file" << endl;
        ret = 1;
    }

    return ret;
}

void SetFormatISO_8601(string &str, time_t lt)
{
    char tmpStr[10] = {0};
    struct tm *time_tm;

    time_tm = gmtime(&lt);

    itoa(time_tm->tm_year + 1900, (char *)&tmpStr[0], 10);
    str += tmpStr;
    str += '-';
    itoa(time_tm->tm_mon + 1, (char *)&tmpStr[0], 10);
    str += tmpStr;
    str += '-';
    itoa(time_tm->tm_mday, (char *)&tmpStr[0], 10);
    str += tmpStr;
    str += ' ';

    itoa(time_tm->tm_hour, (char *)&tmpStr[0], 10);
    if (time_tm->tm_hour < 10)
    {
        str += '0';
    }
    str += tmpStr;
    str += ':';

    itoa(time_tm->tm_min, (char *)&tmpStr[0], 10);
    if (time_tm->tm_min < 10)
    {
        str += '0';
    }
    str += tmpStr;
    str += ':';

    itoa(time_tm->tm_sec, (char *)&tmpStr[0], 10);
    if (time_tm->tm_sec < 10)
    {
        str += '0';
    }
    str += tmpStr;
    str += ';';
}

void ImitateData(void)
{
    double tempData = 0;
    cout << "input start temp" << endl;
    cin >> tempData;
    time_t lt;
    lt = time(NULL);
    fprintf(out, "time;temperature;\n");
    for (size_t i = 0; i < COUNT_STR; i++)
    {
        double tmp = tempData;
        string str;
        char tmpStr[10] = {0};
        SetFormatISO_8601(str, lt);
        tmp += AddNoise();
        sprintf((char *)&tmpStr[0], "%.2f", tmp);

        for (size_t i = 0; i < sizeof(tmpStr); i++)
        {
            if (tmpStr[i] == '.')
            {
                tmpStr[i] = ',';
                break;
            }
        }
        str += tmpStr;
        str += ';';
        lt++;

        fprintf(out, "%s\n", (char *)&str[0]);
        cout << str << endl;
    }
}

void InitRand(void)
{
    time_t initRandTime;
    initRandTime = time(NULL);
    unsigned int initRandVal = (unsigned int)initRandTime;
    srand(initRandVal);
}

double AddNoise(void)
{
    unsigned int noiseInt = rand();
    noiseInt %= 100;
    double noiseDouble = noiseInt * EPSILON;
    return noiseDouble;
}

void GenerateDataCSV(void)
{
    if (CreateOutFile())
    {
        return;
    }
    InitRand();
    ImitateData();
    fclose(out);
    cout << "hello edge" << endl;
}