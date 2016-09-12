#ifndef ARMUP_H
#define ARMUP_H


#include "Commands/Subsystem.h"
#include "../Robot.h"

class ArmUp: public Command {
public:
    ArmUp();
    virtual void Initialize();
    virtual void Execute();
    virtual bool IsFinished();
    virtual void End();
    virtual void Interrupted();

private:

};
#endif
