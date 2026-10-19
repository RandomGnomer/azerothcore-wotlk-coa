#include "ManastormModuleConfig.h"

#include "Config.h"
#include "Log.h"
#include "ManastormReleaseStage.h"

#include <algorithm>

namespace ManastormModuleConfig
{
    namespace
    {
        bool enabled = true;
        ManastormClientMode clientMode = ManastormClientMode::Ascension;
        uint32 releaseStage = ManastormReleaseStage::AllReleased;
    }

    void Load(bool reload)
    {
        bool const requestedEnabled = sConfigMgr->GetOption<bool>("Manastorm.Enable", true);
        uint32 const requestedMode = sConfigMgr->GetOption<uint32>("Manastorm.ClientMode", 2);
        releaseStage = std::min(sConfigMgr->GetOption<uint32>("Ascension.CallboardCache.ReleaseStage",
            ManastormReleaseStage::AllReleased), ManastormReleaseStage::AllReleased);
        if (reload)
        {
            // Switching transport or disabling hooks during a run strands its
            // private-instance ownership and the client's active-state cache.
            if (requestedEnabled != enabled || requestedMode != uint32(clientMode))
                LOG_WARN("module.manastorm.endless", "Manastorm.Enable/ClientMode changes require a restart; "
                    "keeping enabled={} clientMode={} for this process.", enabled, uint32(clientMode));
            return;
        }
        enabled = requestedEnabled;
        clientMode = requestedMode == 2 ? ManastormClientMode::Ascension : ManastormClientMode::Reconstructed;
        if (requestedMode != 1 && requestedMode != 2)
            LOG_ERROR("module.manastorm.endless", "Invalid Manastorm.ClientMode={}; using Mode 1.", requestedMode);
    }

    bool Enabled()
    {
        return enabled;
    }

    ManastormClientMode ClientMode()
    {
        return clientMode;
    }

    bool IsReconstructedClientMode()
    {
        return clientMode == ManastormClientMode::Reconstructed;
    }

    bool IsNativeClientMode()
    {
        return clientMode == ManastormClientMode::Ascension;
    }

    uint32 ReleaseStage()
    {
        return releaseStage;
    }

    void LogConfiguration()
    {
        LOG_INFO("module.manastorm.endless", "Manastorm owner=mod-manastorm-endless enabled={} clientMode={} ({}) "
            "releaseStage={}. The Ascension donor run service is not registered.", enabled, uint32(clientMode),
            IsNativeClientMode() ? "Ascension native" : "reconstructed addon", releaseStage);
    }
}
