################################################################################
# Define module project: EngineCore
################################################################################
project(EngineUtils C CXX)

################################################################################
# Set Source groups
################################################################################
set(engine_utils_include_dir
  "${CMAKE_CURRENT_SOURCE_DIR}/include"
)

set(engine_utils_header_dir
  "${engine_utils_include_dir}/utils/"
)

### Get Headers
# Configuration Headers
set(engine_utils_configuration_headers
    "${engine_utils_header_dir}/configuration/Configurable.h"
    "${engine_utils_header_dir}/configuration/Configuration.h"
)
source_group("Header Files\\Configuration" FILES ${engine_utils_configuration_headers})

# Factory Headers
set(engine_utils_factory_headers
    "${engine_utils_header_dir}/factory/Factory.h"
    "${engine_utils_header_dir}/factory/FactoryConstructible.h"
)
source_group("Header Files\\Factory" FILES ${engine_utils_factory_headers})

# Resource
set(engine_utils_resource_headers
    "${engine_utils_header_dir}/resource/JsonResource.h"
    "${engine_utils_header_dir}/resource/Resource.h"
    "${engine_utils_header_dir}/resource/ResourceAllocator.h"
    "${engine_utils_header_dir}/resource/ResourceHandle.h"
)
source_group("Header Files\\Resource" FILES ${engine_utils_resource_headers})

# Threading
set(engine_utils_threading_headers
    "${engine_utils_header_dir}/threading/ThreadPool.h"
    "${engine_utils_header_dir}/threading/ThreadPoolWorker.h"
    "${engine_utils_header_dir}/threading/ThreadSafeQueue.h"
)
source_group("Header Files\\Threading" FILES ${engine_utils_threading_headers})

set(engine_utils_headers
    "${engine_utils_header_dir}/EngineUtilities.h"
    "${engine_utils_configuration_headers}"
    "${engine_utils_factory_headers}"
    "${engine_utils_resource_headers}"
    "${engine_utils_threading_headers}"
    "${engine_utils_header_dir}/Logger.h"
    "${engine_utils_header_dir}/Name.h"
    "${engine_utils_header_dir}/Table.h"
    "${engine_utils_header_dir}/TimeUtils.h"
    "${engine_utils_header_dir}/TypeUtils.h"
)

### Get Source
# Configuration source
set(engine_utils_configuration_source
    "src/configuration/Configurable.cpp"
    "src/configuration/Configuration.cpp"
)
source_group("Source Files\\Configuration" FILES ${engine_utils_configuration_source})

# Resource source
set(engine_utils_resource_source
    "src/resource/JsonResource.cpp"
    "src/resource/Resource.cpp"
    "src/resource/ResourceAllocator.cpp"
)
source_group("Source Files\\Resource" FILES ${engine_utils_resource_source})

# Threading source
set(engine_utils_threading_source
    "src/threading/ThreadPool.cpp"
    "src/threading/ThreadPoolWorker.cpp"
)
source_group("Source Files\\Threading" FILES ${engine_utils_threading_source})

set(engine_utils_source
    "${engine_utils_configuration_source}"
    "${engine_utils_resource_source}"
    "${engine_utils_threading_source}"
    "src/Logger.cpp"
    "src/TimeUtils.cpp"
)

### Combine files into single target
set(ALL_FILES ${engine_utils_headers} ${engine_utils_source})

################################################################################
# Specify build as Static Library
################################################################################
add_library(EngineUtils STATIC ${ALL_FILES})

################################################################################
# Set Module Include Directory
################################################################################
target_include_directories(EngineUtils PUBLIC ${engine_utils_include_dir}/)
target_include_directories(EngineUtils PRIVATE ${engine_utils_header_dir}/)