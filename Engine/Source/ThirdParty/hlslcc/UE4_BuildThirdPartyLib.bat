@echo off
REM hlslcc
pushd hlslcc\projects

	p4 edit %THIRD_PARTY_CHANGELIST% ..\lib\...

	REM vs2013 x64
	pushd vs2013
	msbuild hlslcc.sln /target:Clean,hlslcc_lib /m /p:Platform=x64;Configuration="Release"
	msbuild hlslcc.sln /target:Clean,hlslcc_lib /m /p:Platform=x64;Configuration="Debug"
	popd

	REM vs2013 x86
	pushd vs2013
	msbuild hlslcc.sln /target:Clean,hlslcc_lib /m /p:Platform=Win32;Configuration="Release"
	msbuild hlslcc.sln /target:Clean,hlslcc_lib /m /p:Platform=Win32;Configuration="Debug"
	popd

	REM vs2012 x64
	pushd vs2012
	msbuild hlslcc.sln /target:Clean,hlslcc_lib /p:Platform=x64;Configuration="Debug"
	msbuild hlslcc.sln /target:Clean,hlslcc_lib /p:Platform=x64;Configuration="Release"
	popd

	REM vs2012 x86
	pushd vs2012
	msbuild hlslcc.sln /target:Clean,hlslcc_lib /p:Platform=Win32;Configuration="Debug"
	msbuild hlslcc.sln /target:Clean,hlslcc_lib /p:Platform=Win32;Configuration="Release"
	popd

	REM Linux (only if LINUX_ROOT is defined)
	set CheckLINUX_ROOT=%LINUX_ROOT%
	if "%CheckLINUX_ROOT%"=="" goto SkipLinux

	pushd Linux
	CrossCompile.bat
	popd

:SkipLinux

popd
