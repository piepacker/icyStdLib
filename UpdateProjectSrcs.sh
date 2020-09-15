#!/bin/bash
#
# UpdateProjectSrcs
# 
# Generates a project file source lists for Microsoft C++ / msbuild.
# Includes all files in pre-defined source directories by wildcard.
# files and directories with double-hash (##) in the filename are not included.
# (can be used to easily exclude files meant for standalone compilation/tersting
# of some sources).


me=$(basename "${BASH_SOURCE[0]}")
mydir=$(dirname $(readlink -f ${BASH_SOURCE[0]}))

PATH=$mydir/build:$PATH

MsGenClCompile src > srclist_icystdlib.msbuild

# Visual Studio balks if we have more than two ItemGroups in an include?
# I really dunno what to think, anyway that's why I split shaders into their own file.

# no external shaders in tooling yet...
#ShaderWildcard    > ShaderList.msbuild

MsGenVcFilters samples.vcxproj srclist_icystdlib.msbuild

# tells visual studio to reload things...
touch samples.vcxproj
