pwd
rm -rf ./buildios
mkdir ./buildios
cd ./buildios
/usr/local/bin/cmake .. -DCMAKE_TOOLCHAIN_FILE=/Users/Sheshu/Library/Android/sdk/ndk-bundle/toolchains/IOS/iOS.cmake -DIOS_PLATFORM=OS
make clean & make
# clear build cache for x64
rm CMakeCache.txt
/usr/local/bin/cmake .. -DCMAKE_TOOLCHAIN_FILE=/Users/Sheshu/Library/Android/sdk/ndk-bundle/toolchains/IOS/iOS.cmake -DIOS_PLATFORM=SIMULATOR64
make clean & make

# OS library is already "fat lib" so lipo not merging.
# https://github.com/assimp/assimp/tree/master/port/iOS could be better solution. Where each arch was built.
#cd ../../distribution/contacts-core-lib/lib/IOS/
#lipo -create ./SIMULATOR64/contacts-core-lib.a ./OS/contacts-core-lib.a  -output ./contacts-core-lib.a

# copy these 4 header files to the ios project. .
# /src/main/cpp/ContactsCore/api/ContactsCoreApi.hpp
# /src/main/cpp/ContactsCore/model/Contact.hpp
# /src/main/cpp/JsonLib/JSON.hpp
# /src/main/cpp/JsonLib/JSONValue.hpp
