#include "AnalogChannelVolt.h"
#include <math.h>

AnalogChannelVolt::AnalogChannelVolt(uint32_t channel, bool inv, int ratio, CANTalon* Motor)
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

    motor = Motor;
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
	LOG("analogChannelVolt start\r");
}

float AnalogChannelVolt::GetVoltage()
{
  return PIDGet();
}

int AnalogChannelVolt::getturns()
{
    return motor->GetPosition();
}
double AnalogChannelVolt::PIDGet()
{
	double position = motor->GetPosition();
	position -= trunc(position);
	if (position < 0)
	position += 1;
	position *= 5;
	return position;
}

AnalogChannelVolt::~AnalogChannelVolt()
{
  if(m_trig)
    delete m_trig;
  if(m_count)
    delete m_count;
}
