
#include "playerbot/playerbot.h"
#include "PriestTriggers.h"
#include "PriestActions.h"

using namespace ai;

bool InnerFireTrigger::IsActive()
{
    Unit* target = GetTarget();
    return SpellTrigger::IsActive() && !ai->HasAura(spell, target);
}

bool ShadowformTrigger::IsActive()
{
    return !ai->HasAura("shadowform", bot);
}

bool ShadowfiendTrigger::IsActive()
{
    return BoostTrigger::IsActive() && bot->IsSpellReady(34433);
}

bool ObsidianEradicatorManaBurnTrigger::IsActive()
{
    Unit* target = ai->GetBot()->GetTarget();

    if (!target) {
        return false;
    }

    if (ai->GetBot()->GetMapId() != 531) {
        return false;
    }

    if (target->GetEntry() != 15262) {
        return false;
    }

    return true;
}