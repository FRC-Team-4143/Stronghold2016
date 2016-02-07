#include "AnalogChannelVolt.h"
#include <math.h>

AnalogChannelVolt::AnalogChannelVolt(uint32_t channel, bool inv, int ratio)
  : AnalogInput(channel)
{
    Inv = inv;
    Ratio = ratio;

    rev = 5.0;
    halfrev = rev/Ratio;
    scale = rev/(4.8-.2);

    m_channel = channel;
    SetSampleRate(1000);

    m_trig = new AnalogTrigger(channel);
    m_trig->SetFiltered(true);
    m_trig->SetLimitsVoltage(1.35,3.65);

    m_count = new Counter();
    m_count->SetUpDownCounterMode();
    m_count->SetUpSource(m_trig, AnalogTriggerType::kFallingPulse);
    m_count->SetDownSource(m_trig, AnalogTriggerType::kRisingPulse);
    m_count->SetUpSourceEdge(true,false);
    m_count->SetDownSourceEdge(true,false);

}

float AnalogChannelVolt::GetAverageVoltage()
{
    return GetVoltage();
}

void AnalogChannelVolt::ResetTurns()
{
    m_count->Reset();
}

void AnalogChannelVolt::Start()
{
    printf("analogChannelVolt start\n\r");
}

float AnalogChannelVolt::GetVoltage()
{
  float temp = AnalogInput::GetVoltage();
  temp = (((temp - halfrev) * scale) + halfrev);  // scale
  if(temp < 0) temp = 0; // min
  if(temp > rev) temp = rev; // max
  temp = (temp / Ratio) + ((m_count->Get() % Ratio) * halfrev); // half scale
  if(Inv)
     temp = rev - temp; // inverse
  return temp;
}

int AnalogChannelVolt::getturns()
{
    return m_count->Get();
}
double AnalogChannelVolt::PIDGet()
{
  return GetVoltage();
}

AnalogChannelVolt::~AnalogChannelVolt()
{
  if(m_trig)
    delete m_trig;
  if(m_count)
    delete m_count;
}
