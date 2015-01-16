call "%programfiles(x86)%\Microsoft Visual Studio 12.0\VC\vcvarsall.bat" x86
cd vs
msbuild /p:Configuration=Release;Platform=Win32 openvdb_vs.sln
msbuild /p:Configuration=Release_profiling;Platform=Win32 openvdb_vs.sln