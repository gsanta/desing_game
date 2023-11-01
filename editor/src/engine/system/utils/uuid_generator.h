#pragma once

#include <iostream>
#define UUID_SYSTEM_GENERATOR
#include "uuid.h"

namespace spright
{
namespace engine
{
    class UuidGenerator
    {
    public:
        static std::string generate();
    };
} // namespace engine
} // namespace spright
