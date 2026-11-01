make win32 -j$(nproc)

mkdir win-release
cp build-win32/linuxloader.exe win-release/linuxloader.exe
#cp libs/win32/SDL3.dll win-release/SDL3.dll
cp -r libs/win32/ll-deps win-release/
# Ubuntu's mingw-w64 links libgcc dynamically for some of it; MXE's static
# toolchain does not, and has no such DLL
dw2=$(ls /usr/lib/gcc/i686-w64-mingw32/*-win32/libgcc_s_dw2-1.dll 2>/dev/null | head -n 1)
[ -n "$dw2" ] && cp "$dw2" win-release/ll-deps/

cd win-release
zip -r ../linuxloader-win32.zip .
cd ..
