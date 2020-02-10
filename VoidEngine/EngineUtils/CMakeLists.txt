################################################################################
# Define module project: EngineCore
################################################################################
project(EngineUtils C CXX)

################################################################################
# Set directory shortcuts
################################################################################
set(engine_utils_include_dir
  "${CMAKE_CURRENT_SOURCE_DIR}/include"
)

set(engine_utils_header_dir
  "${engine_utils_include_dir}/utils/"
)

set(engine_utils_OSAL_header_dir
  "${engine_utils_include_dir}/OSAL/"
)

################################################################################
# Set Utils Headers
################################################################################
# Configuration Headers
set(engine_utils_configuration_headers
    "${engine_utils_header_dir}/configuration/Configurable.h"
    "${engine_utils_header_dir}/configuration/Configuration.h"
)
source_group("Header Files\\utils\\Configuration" FILES ${engine_utils_configuration_headers})

# Factory Headers
set(engine_utils_factory_headers
    "${engine_utils_header_dir}/factory/Factory.h"
    "${engine_utils_header_dir}/factory/FactoryConstructible.h"
)
source_group("Header Files\\utils\\Factory" FILES ${engine_utils_factory_headers})

# Resource
set(engine_utils_resource_headers
    "${engine_utils_header_dir}/resource/JsonResource.h"
    "${engine_utils_header_dir}/resource/Resource.h"
    "${engine_utils_header_dir}/resource/ResourceAllocator.h"
    "${engine_utils_header_dir}/resource/ResourceHandle.h"
)
source_group("Header Files\\utils\\Resource" FILES ${engine_utils_resource_headers})

# Threading
set(engine_utils_threading_headers
    "${engine_utils_header_dir}/threading/ThreadPool.h"
    "${engine_utils_header_dir}/threading/ThreadPoolWorker.h"
    "${engine_utils_header_dir}/threading/ThreadSafeQueue.h"
)
source_group("Header Files\\utils\\Threading" FILES ${engine_utils_threading_headers})

set(engine_utils_loose_headers
    "${engine_utils_header_dir}/EngineUtilities.h"
    "${engine_utils_header_dir}/Logger.h"
    "${engine_utils_header_dir}/Name.h"
    "${engine_utils_header_dir}/Table.h"
    "${engine_utils_header_dir}/TimeUtils.h"
    "${engine_utils_header_dir}/TypeUtils.h"
)
source_group("Header Files\\utils" FILES ${engine_utils_loose_headers})

set(engine_utils_headers
    "${engine_utils_configuration_headers}"
    "${engine_utils_factory_headers}"
    "${engine_utils_resource_headers}"
    "${engine_utils_threading_headers}"
    "${engine_utils_loose_headers}"
)

################################################################################
# Set OSAL Headers
################################################################################
# Core
set(engine_OSAL_core_headers
    "${engine_utils_OSAL_header_dir}/GLFW_WindowingContext.h"
    "${engine_utils_OSAL_header_dir}/WindowingContext.h"
)
source_group("Header Files\\OSAL" FILES ${engine_OSAL_core_headers})

set(engine_OSAL_IO_headers
    "${engine_utils_OSAL_header_dir}/IO/GLFWInputContext.h"
    "${engine_utils_OSAL_header_dir}/IO/InputContext.h"
    "${engine_utils_OSAL_header_dir}/IO/OpenGLRenderingContext.h"
    "${engine_utils_OSAL_header_dir}/IO/RenderingContext.h"
)
source_group("Header Files\\OSAL\\IO" FILES ${engine_OSAL_IO_headers})

set(engine_OSAL_headers
    "${engine_OSAL_core_headers}"
    "${engine_OSAL_IO_headers}"
)

################################################################################
# Set Utils Source
################################################################################
# Configuration source
set(engine_utils_configuration_source
    "src/utils/configuration/Configurable.cpp"
    "src/utils/configuration/Configuration.cpp"
)
source_group("Source Files\\utils\\Configuration" FILES ${engine_utils_configuration_source})

# Resource source
set(engine_utils_resource_source
    "src/utils/resource/JsonResource.cpp"
    "src/utils/resource/Resource.cpp"
    "src/utils/resource/ResourceAllocator.cpp"
)
source_group("Source Files\\utils\\Resource" FILES ${engine_utils_resource_source})

# Threading source
set(engine_utils_threading_source
    "src/utils/threading/ThreadPool.cpp"
    "src/utils/threading/ThreadPoolWorker.cpp"
)
source_group("Source Files\\utils\\Threading" FILES ${engine_utils_threading_source})

set(engine_utils_loose_source
    "src/utils/Logger.cpp"
    "src/utils/TimeUtils.cpp"
)
source_group("Source Files\\utils" FILES ${engine_utils_loose_source})

set(engine_utils_source
    "${engine_utils_configuration_source}"
    "${engine_utils_resource_source}"
    "${engine_utils_threading_source}"
    "${engine_utils_loose_source}"

)

################################################################################
# Set OSAL Source
################################################################################
# Core
set(engine_OSAL_core_source
    "src/OSAL/GLFW_WindowingContext.cpp"
    "src/OSAL/WindowingContext.cpp"
)
source_group("Source Files\\OSAL" FILES ${engine_OSAL_core_source})

set(engine_OSAL_IO_source
    "src/OSAL/IO/GLFWInputContext.cpp"
    "src/OSAL/IO/InputContext.cpp"
    "src/OSAL/IO/OpenGLRenderingContext.cpp"
    "src/OSAL/IO/RenderingContext.cpp"
)
source_group("Source Files\\OSAL\\IO" FILES ${engine_OSAL_IO_source})

set(engine_OSAL_source
    "${engine_OSAL_core_source}"
    "${engine_OSAL_IO_source}"
)

### Combine files into single target
set(ALL_FILES 
    ${engine_utils_headers}  
    ${engine_utils_source} 
    ${engine_OSAL_headers}
    ${engine_OSAL_source})

################################################################################
# Specify build as Static Library
################################################################################
add_library(EngineUtils STATIC ${ALL_FILES})

################################################################################
# Set Module Include Directory
################################################################################
target_include_directories(EngineUtils PUBLIC ${engine_utils_include_dir}/)
target_include_directories(EngineUtils PRIVATE ${engine_utils_header_dir}/)
target_include_directories(EngineUtils PRIVATE ${engine_utils_OSAL_header_dir}/)