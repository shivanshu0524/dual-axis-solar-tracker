
#include <REGX52.H>

typedef unsigned char u8;
typedef unsigned int u16;

sbit SERVO_VERTICAL   = P2^0;
sbit SERVO_HORIZONTAL = P2^1;

#define DEAD_BAND 50
#define SERVO_MIN 20
#define SERVO_MAX 40
#define SERVO_FRAME 400

volatile u16 verticalPulse = 30;
volatile u16 horizontalPulse = 30;
volatile u16 tick = 0;

volatile u8 rxBuffer[24];
volatile u8 rxIndex = 0;
volatile bit lineReady = 0;

u16 TL, TR, BL, BR;
u16 verticalPosition = 30;
u16 horizontalPosition = 30;

void UART_Init(void)
{
    SCON = 0x50;
    TMOD = (TMOD & 0x0F) | 0x20;
    TH1 = 0xFD;
    TL1 = 0xFD;
    TR1 = 1;
    ES = 1;
    EA = 1;
}

void Timer0_Init(void)
{
    TMOD = (TMOD & 0xF0) | 0x01;
    TH0 = 0xFF;
    TL0 = 0xD2;
    ET0 = 1;
    TR0 = 1;
}

void UART_ISR(void) interrupt 4
{
    char c;

    if (RI)
    {
        RI = 0;
        c = SBUF;

        if (c == '\n')
        {
            if (rxIndex < sizeof(rxBuffer))
            {
                rxBuffer[rxIndex] = 0;
                lineReady = 1;
            }
            rxIndex = 0;
        }
        else if (c != '\r' && !lineReady)
        {
            if (rxIndex < sizeof(rxBuffer) - 1)
                rxBuffer[rxIndex++] = c;
            else
                rxIndex = 0;
        }
    }

    if (TI)
        TI = 0;
}

void Timer0_ISR(void) interrupt 1
{
    TH0 = 0xFF;
    TL0 = 0xD2;

    if (tick == 0)
    {
        SERVO_VERTICAL = 1;
        SERVO_HORIZONTAL = 1;
    }

    if (tick == verticalPulse)
        SERVO_VERTICAL = 0;

    if (tick == horizontalPulse)
        SERVO_HORIZONTAL = 0;

    tick++;

    if (tick >= SERVO_FRAME)
        tick = 0;
}

bit ParseSensorData(void)
{
    u16 values[4] = {0, 0, 0, 0};
    u8 field = 0;
    u8 digits = 0;
    u8 i = 0;
    char c;

    while (i < sizeof(rxBuffer))
    {
        c = rxBuffer[i++];

        if (c == 0)
            break;

        if (c >= '0' && c <= '9')
        {
            values[field] = values[field] * 10 + (c - '0');
            if (values[field] > 1023)
                return 0;
            digits = 1;
        }
        else if (c == ',' && field < 3 && digits)
        {
            field++;
            digits = 0;
        }
        else
            return 0;
    }

    if (field != 3 || !digits)
        return 0;

    TL = values[0];
    TR = values[1];
    BL = values[2];
    BR = values[3];

    return 1;
}

void UpdateTracking(void)
{
    int left   = TL + BL;
    int right  = TR + BR;
    int top    = TL + TR;
    int bottom = BL + BR;

    if (left > right + DEAD_BAND)
    {
        if (horizontalPosition > SERVO_MIN)
            horizontalPosition--;
    }
    else if (right > left + DEAD_BAND)
    {
        if (horizontalPosition < SERVO_MAX)
            horizontalPosition++;
    }

    if (top > bottom + DEAD_BAND)
    {
        if (verticalPosition < SERVO_MAX)
            verticalPosition++;
    }
    else if (bottom > top + DEAD_BAND)
    {
        if (verticalPosition > SERVO_MIN)
            verticalPosition--;
    }

    EA = 0;
    verticalPulse = verticalPosition;
    horizontalPulse = horizontalPosition;
    EA = 1;
}

void main(void)
{
    SERVO_VERTICAL = 0;
    SERVO_HORIZONTAL = 0;

    UART_Init();
    Timer0_Init();

    while (1)
    {
        if (lineReady)
        {
            bit valid;

            EA = 0;
            lineReady = 0;
            EA = 1;

            valid = ParseSensorData();

            if (valid)
                UpdateTracking();
        }
    }
}
