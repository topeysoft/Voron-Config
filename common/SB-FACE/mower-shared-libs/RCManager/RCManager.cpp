#include "RCManager.h"
RCManagerClass rcManager;
// Every _runRcListenerNow(100);
unsigned long _lastRcListenerTime = 0;
void RCManagerClass::work()
{
    // if (_runRcListenerNow())
    // {
    // if (millis() - _lastRcListenerTime >= 200)
    // {
    _iBus.loop();
    bool updated = false;
    for (size_t i = 0; i < channelCount; i++)
    {
        int val = _iBus.readChannel(i); // get latest value for servo channel 1
        if (val != _data[i])
        {
            _data[i] = val;
            updated = true;
        }
    }
    if (_ready() && updated && _callback)
    {
        _callback(_data);
    }
    // }
    // }
}
