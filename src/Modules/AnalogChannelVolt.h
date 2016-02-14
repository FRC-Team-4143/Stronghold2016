
#ifndef ANALOG_CHANNEL_VOLT_H
#define ANALOG_CHANNEL_VOLT_H

#include <WPILib.h>
#include <Base.h>
#include <AnalogInput.h>
#include <AnalogTrigger.h>
#include <AnalogTriggerOutput.h>
#include <Counter.h>
#include "Logger.h"

class AnalogChannelVolt : public AnalogInput
{
 public:
  AnalogChannelVolt(uint32_t channel, bool inv, int ratio, CANTalon* Motor);
  virtual ~AnalogChannelVolt();
  double PIDGet() override;
  float GetAverageVoltage();
  float GetVoltage();
  void ResetTurns();
  void Start();
  double getturns();

 private:
  CANTalon* motor;
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
