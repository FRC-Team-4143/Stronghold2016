
#ifndef ANALOG_CHANNEL_VOLT_H
#define ANALOG_CHANNEL_VOLT_H

#include <Base.h>
#include <AnalogInput.h>
#include <AnalogTrigger.h>
#include <AnalogTriggerOutput.h>
#include <Counter.h>

class AnalogChannelVolt : public AnalogInput
{
 public:
  AnalogChannelVolt(uint32_t channel, bool inv, int ratio);
  virtual ~AnalogChannelVolt();
  double PIDGet();
  float GetAverageVoltage();
  float GetVoltage();
  void ResetTurns();
  void Start();
  int getturns();

 private:
  AnalogTrigger *m_trig;
  Counter *m_count;
  uint32_t m_channel;
  bool Inv;
  float rev;
  float halfrev;
  float scale;
  int Ratio;
};

#endif
