#include "uuid_generator.h"

namespace spright
{
namespace engine
{
    std::string UuidGenerator::generate()
    {
        return uuids::to_string(uuids::uuid_system_generator{}());
    }
} // namespace engine
} // namespace spright
