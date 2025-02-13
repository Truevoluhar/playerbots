
#include "playerbot/playerbot.h"
#include "OnyxiasLairDungeonActions.h"
#include "MovementActions.h"


using namespace ai;

bool OnyxiaMoveToFlankAction::Execute(Event& event) 
{
    const float PI_FLOAT = 3.1415927f;

    Player* bot = ai->GetBot();
    Unit* target = ai->GetBot()->GetTarget();

    // TODO Change target entry ID
    if (!bot || !target || !target.GetEntry() != 11111) {
        return false;
    }

    bool isTank = ai->IsTank(bot);

    if (isTank) {
        return false;
    }

    float angle = bot->GetAngle(target);
    float onyxiaOrientation = target->getO();

    // Compute bot’s current angle relative to Onyxia
    float diff = fabs(angle - onyxiaOrientation);

    // Compute correct angle for bot (side-back positioning)
    float correctAngle1 = onyxiaOrientation + (90.0f * PI_FLOAT / 180);  // 90° to the right
    float correctAngle2 = onyxiaOrientation - (90.0f * PI_FLOAT / 180);  // 90° to the left


    // Normalize the angle difference to ensure it's between -π and π
    while (diff > PI_FLOAT)
        diff -= 2 * PI_FLOAT;
    while (diff < -PI_FLOAT)
        diff += 2 * PI_FLOAT;

    // If bot is already around the correct position, do nothing
    if ((diff > 80 * PI_FLOAT / 180 && diff < 120 * PI_FLOAT / 180) ||
        (diff > 240 * PI_FLOAT / 180 && diff < 280 * PI_FLOAT / 180))
    {
        return false;
    }

    // Calculate new target position for the bot
    float distanceFromOnyxia = 8.0f; // Adjust as needed
    float newX = target->GetPositionX() + distanceFromOnyxia * cos(correctAngle1);
    float newY = target->GetPositionY() + distanceFromOnyxia * sin(correctAngle1);
    float newZ = target->GetPositionZ();

    // Move bot to calculated position
    return MoveTo(target->GetMapId(), newX, newY, newZ);

    return false;
}