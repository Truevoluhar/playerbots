
#include "playerbot/playerbot.h"
#include "OnyxiasLairDungeonTriggers.h"

using namespace ai;

bool OnyxiaFormation::isActive()
{
    
    const float PI_FLOAT = 3.1415927f;

    Player* bot = ai->GetBot();
    Unit* target = ai->GetBot()->GetTarget();

    // Check if bot has target and if that target is Onyxia
    if (!target || !bot->IsInCombat()) {
        return false;
    }
    // TODO FIX target id
    if (target->GetEntry() != 11111) {
        return false;
    }

    // Retrieve bot role so that we can position it accordingly
    bool tank = ai->IsTank(bot);
    bool heal = ai->IsHeal(bot);
    
    // Get position data
    float angle = bot->GetAngle(target);
    float targetOrientation = target.getO();
    float diff = fabs(targetOrientation - angle);

    // We dont care about tank, it can be anywhere 
    // Other bots will position themselves based on tanks position
    if (tank) {
        return false;
    }

    // If playerbot is not tank, it must be standing between
    // 80 and 120 degrees or 240 and 280 degrees 
    if (!tank) {
        
        // Angle normalization
        while (diff > PI_FLOAT)  
            diff -= 2 * PI_FLOAT;
        while (diff < -PI_FLOAT)  
            diff += 2 * PI_FLOAT;

        if (diff > 80 * PI_FLOAT / 180 && diff < 120 * PI_FLOAT / 180) {
            return false;
        }

        if (diff > 240 * PI_FLOAT / 180 && diff < 280  * PI_FLOAT / 180) {
            return false;
        }
        
        return true;
    }
    
}