/* ******************* Includes ****************** */
#include "wakhan.h"
#include "WakhanThanka.h"
#include "WakhanThanka.hxx"
/* *********************************************** */
o_registerN((wakhan), WakhanThanka)

o_namespace_begin(wakhan)

WakhanThanka* WakhanThanka::GreatMystery()
{
    static WakhanThanka* sm_pGreatMystery = nullptr;
    if(sm_pGreatMystery == nullptr)
    {
        sm_pGreatMystery = o_new(WakhanThanka); // Ok the great spirit has always been and will always, so excuse me for that :)
    }
    return sm_pGreatMystery;
}

o_namespace_end(wakhan)
