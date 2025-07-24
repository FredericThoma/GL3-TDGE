#pragma once

#include <vector>
#include <filesystem>

#include "engine/waves/WaveInfo.h"

namespace engine::waves {


    class WaveParser {
    public:
        static std::vector<WaveInfo> from_json_file(const std::filesystem::path& file_path);
    };

}
