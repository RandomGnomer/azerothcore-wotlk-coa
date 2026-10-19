#ifndef MANASTORM_RELEASE_STAGE_H
#define MANASTORM_RELEASE_STAGE_H

#include "Define.h"

#include <array>

namespace ManastormReleaseStage
{
    // Stages follow Ascension.CallboardCache.ReleaseStage: 1 Heroic dungeons, 2 Mythic dungeons, 3 Molten Core,
    // 4 Zul'Gurub, 5 Onyxia's Lair, 6 Blackwing Lair, 7 Ahn'Qiraj, 8 Naxxramas.
    constexpr uint32 AllReleased = 8;

    struct CacheStage
    {
        uint32 CacheItemEntry;
        uint32 Stage;
    };

    constexpr std::array<CacheStage, 18> RaidCacheStages = {{
        { 1278052, 4 }, { 1278053, 4 }, { 1278055, 4 },
        { 1278056, 3 }, { 1278058, 3 }, { 1278060, 3 },
        { 1278066, 6 }, { 1278068, 6 }, { 1278069, 6 },
        { 1278070, 7 }, { 1278072, 7 }, { 1278074, 7 },
        { 1278075, 7 }, { 1278077, 7 }, { 1278078, 7 },
        { 1278079, 8 }, { 1278081, 8 }, { 1278083, 8 }
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
