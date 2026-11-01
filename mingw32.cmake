set(CMAKE_SYSTEM_NAME Windows)
# The cross compiler's prefix: Ubuntu's mingw-w64 by default, MXE's
# i686-w64-mingw32.static on the libretro buildbot (MINGW32_PREFIX)
if(DEFINED ENV{MINGW32_PREFIX})
  set(MINGW32_PREFIX $ENV{MINGW32_PREFIX})
else()
  set(MINGW32_PREFIX i686-w64-mingw32)
endif()
set(CMAKE_C_COMPILER ${MINGW32_PREFIX}-gcc)
set(CMAKE_CXX_COMPILER ${MINGW32_PREFIX}-g++)
set(CMAKE_RC_COMPILER ${MINGW32_PREFIX}-windres)

# set(CMAKE_FIND_ROOT_PATH /usr/i686-w64-mingw32)
set(CMAKE_FIND_ROOT_PATH C:/msys64/mingw32)

# Adjust the default behavior of the FIND_XXX() commands:
# search headers and libraries in the target environment, search 
# programs in the host environment
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
