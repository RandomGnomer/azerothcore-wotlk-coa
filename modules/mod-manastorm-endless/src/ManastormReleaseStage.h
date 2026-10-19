#ifndef MANASTORM_RELEASE_STAGE_H
#define MANASTORM_RELEASE_STAGE_H

#include "Define.h"

#include <array>

namespace ManastormReleaseStage
{
    // Stages follow Ascension.CallboardCache.ReleaseStage: 0 Heroic and Mythic dungeons, 1 Zul'Gurub,
    // 2 Molten Core, 3 Onyxia's Lair, 4 Blackwing Lair, 5 Ruins of Ahn'Qiraj, 6 Temple of Ahn'Qiraj,
    // 7 Naxxramas.
    constexpr uint32 AllReleased = 7;

    struct CacheStage
    {
        uint32 CacheItemEntry;
        uint32 Stage;
    };

    constexpr std::array<CacheStage, 18> RaidCacheStages = {{
        { 1278052, 1 }, { 1278053, 1 }, { 1278055, 1 },
        { 1278056, 2 }, { 1278058, 2 }, { 1278060, 2 },
        { 1278066, 4 }, { 1278068, 4 }, { 1278069, 4 },
        { 1278070, 5 }, { 1278072, 5 }, { 1278074, 5 },
        { 1278075, 6 }, { 1278077, 6 }, { 1278078, 6 },
        { 1278079, 7 }, { 1278081, 7 }, { 1278083, 7 }
    }};

    constexpr uint32 RequiredStage(uint32 cacheItemEntry)
    {
        for (CacheStage const& cache : RaidCacheStages)
            if (cache.CacheItemEntry == cacheItemEntry)
                return cache.Stage;
        return 0;
    }
}

#endif
