#pragma once

enum class ActionType {NONE = 0, ACT = 1, SKIP = 2, END_ENCOUNTER = 3};

inline std::string actionToString(ActionType action)
{
    switch(action)
    {
        case ActionType::NONE: return "none";
        case ActionType::ACT: return "act";
        case ActionType::SKIP: return "skip one turn";
        default:return "N/A";
    }
}