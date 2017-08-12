# For more information about using CMake with Android Studio, read the
# documentation: https://d.android.com/studio/projects/add-native-code.html

# For ios static library using ios cmake toolchain from here https://github.com/cristeab/ios-cmake

# Sets the minimum version of CMake required to build the native library.

cmake_minimum_required(VERSION 3.4.1)

# Creates and names a library, sets it as either STATIC
# or SHARED, and provides the relative paths to its source code.
# You can define multiple libraries, and CMake builds them for you.
# Gradle automatically packages shared libraries with your APK.

set(CMAKE_VERBOSE_MAKEFILE on)



#-----------This is core library, it would be common for android and ios --------------------------
#------------Adding json also here, avoiding more complex ways to link prebuilt static to static------------------
#--- json lib from https://github.com/MJPA/SimpleJSON------------
# TODO: check build variant abi validity for ios.
add_library(contacts-core-lib STATIC
    src/main/cpp/ContactsCore/api/ContactsCoreApi.cpp
    src/main/cpp/ContactsCore/model/Contact.cpp
    src/main/cpp/ContactsCore/webservice/ContactsWebService.cpp
    src/main/cpp/JsonLib/JSON.cpp
    src/main/cpp/JsonLib/JSONValue.cpp
                )


# copy out the lib binary... need to leave the static lib around to pass gradle check
set(distribution_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../distribution)

IF (${ANDROID})
set_target_properties(contacts-core-lib
                      PROPERTIES
                      ARCHIVE_OUTPUT_DIRECTORY
                      "${distribution_DIR}/contacts-core-lib/lib/${ANDROID_ABI}")
ELSE()
# set path for IOS and remove lib prefix. xcode linker does not like "lib" prefix
set_target_properties(contacts-core-lib
                      PROPERTIES
                      ARCHIVE_OUTPUT_DIRECTORY
                      "${distribution_DIR}/contacts-core-lib/lib/IOS/${IOS_PLATFORM}"
                      PREFIX ""
                      )



ENDIF()

# copy out lib header file...somehow stops build
#add_custom_command(TARGET contacts-core-lib POST_BUILD
#                   COMMAND "${CMAKE_COMMAND}" -E
#                   copy "${CMAKE_CURRENT_SOURCE_DIR}/src/main/cpp/ContactsCore/api/ContactsCore.h"
#                   "${distribution_DIR}/contacts-core-lib/include/ContactsCore.h"
#                   **** the following 2 lines are for potential future debug purpose ****
#                   COMMAND "${CMAKE_COMMAND}" -E
#                   remove_directory "${CMAKE_CURRENT_BINARY_DIR}"
#                   COMMENT "Copying headerfile to output directory")



# install  ios cmake toolchain from here https://github.com/cristeab/ios-cmake
# To build the ios libraries from these libraries, use the below commands . after the build copy out the 4 header files to attach with static library.
# after that attach the libraries to the ios project and add header files to ios project.

# rmdir ../buildios
# mkdir ../buildios
# cd ../buildios
# cmake .. -DCMAKE_TOOLCHAIN_FILE=/Users/Sheshu/Library/Android/sdk/ndk-bundle/toolchains/IOS/iOS.cmake -DIOS_PLATFORM=OS
# make
# cmake .. -DCMAKE_TOOLCHAIN_FILE=/Users/Sheshu/Library/Android/sdk/ndk-bundle/toolchains/IOS/iOS.cmake -DIOS_PLATFORM=SIMULATOR64
# make
# copy these 4 header files to the ios project. .
# /src/main/cpp/ContactsCore/api/ContactsCoreApi.hpp
# /src/main/cpp/ContactsCore/model/Contact.hpp
# /src/main/cpp/JsonLib/JSON.hpp
# /src/main/cpp/JsonLib/JSONValue.hpp



#---------------------------------------------------------------------------------------------------
IF (${ANDROID})
# If this is for IOS dont add shared library stuff. we can stop with static lib above.

add_library( # Sets the name of the library.
             contactsSdk-lib

             # Sets the library as a shared library.
             SHARED

             # Provides a relative path to your source file(s).
             src/main/cpp/ContactsJni/contactsSdkJni.cpp
             )






# Searches for a specified prebuilt library and stores the path as a
# variable. Because CMake includes system libraries in the search path by
# default, you only need to specify the name of the public NDK library
# you want to add. CMake verifies that the library exists before
# completing its build.

find_library( # Sets the name of the path variable.
              log-lib

              # Specifies the name of the NDK library that
              # you want CMake to locate.
              log )

# Specifies libraries CMake should link to your target library. You
# can link multiple libraries, such as libraries you define in this
# build script, prebuilt third-party libraries, or system libraries.

target_link_libraries( # Specifies the target library.
                       contactsSdk-lib
                        contacts-core-lib
                       # Links the target library to the log library
                       # included in the NDK.
                       ${log-lib}

                       )
ELSE()

                       set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fobjc-abi-version=2 -fobjc-arc -std=gnu++11 -stdlib=libc++ -isysroot ${CMAKE_OSX_SYSROOT}")
                       set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fobjc-abi-version=2 -fobjc-arc -isysroot ${CMAKE_OSX_SYSROOT}")

                       IF (${SIMULATOR})
                         set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -mios-simulator-version-min=6.0")
                       ENDIF()

                       # Library
                       set_xcode_property (contacts-core-lib GCC_GENERATE_DEBUGGING_SYMBOLS YES)

ENDIF()