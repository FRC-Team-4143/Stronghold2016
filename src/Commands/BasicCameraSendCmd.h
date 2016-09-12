#pragma once

#include <Commands/Command.h>
#include "Subsystems/BasicCameraSub.h"

class BasicCameraSendCmd: public Command {
public:
    BasicCameraSendCmd(BasicCameraSub* camera);

    virtual void Initialize();
    virtual void Execute();
    virtual bool IsFinished();
    virtual void End();
    virtual void Interrupted();

private:
    BasicCameraSub* m_camera;
};
