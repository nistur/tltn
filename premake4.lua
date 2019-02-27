solution "tltn"
language "C++"
configurations { "Debug", "Release" }
includedirs { "include", "src/include" }
files { "include/**.h" }

defines { "TLTN_BUILD" }

configuration "Debug"
defines { "DEBUG" }
flags { "Symbols" }
targetdir "build/debug"

configuration "Release"
defines { "NDEBUG" }
flags { "OptimizeSpeed",
	"ExtraWarnings",
	"FatalWarnings",
	"NoFramePointer" }
targetdir "build/release"

project "tltn"
kind "StaticLib"
files { "src/**.c", "src/**.cpp" }

project "tltn-lite"
kind "StaticLib"
files { "src/**.c", "src/**.cpp" }
defines { "TLTN_UNSAFE" }

--[[
project "tltn-dynamic"
kind "SharedLib"
files { "src/**.c", "src/**.cpp" }
targetname "tltn"
--]]

project "tltnd"
kind "ConsoleApp"
files { "sample/main.c" }
links { "tltn-lite" }

project "tests"
kind "ConsoleApp"
files { "tests/**.cpp" }
links { "tltn" }
configuration "Debug"
postbuildcommands("build/debug/tests")
configuration "Release"
postbuildcommands("build/release/tests")
