#!/bin/bash
#
# UpdateProjectSrcs
# 
# Generates a project file source lists for Microsoft C++ / msbuild.
# Includes all files in pre-defined source directories by wildcard.
# files and directories with double-hash (##) in the filename are not included.
# (can be used to easily exclude files meant for standalone compilation/tersting
# of some sources).

# use cygpath to ensure things are runnable from double-clicking explorer.
#
# annoyingly, MSYS2 doesn't cygpath the BASH_SOURCE. More than a few valid arguments could
# be made that it should - it's going to be a known and valid system path so it must always
# be safe for cygpath detection.

bashsrc=$(cygpath "${BASH_SOURCE[0]}")
me=$(basename $bashsrc)
mydir=$(dirname $(readlink -f $bashsrc))

export PATH=$mydir/build:$PATH

MsGenClCompile src > $mydir/srclist_icystdlib.msbuild

MsGenVcFilters $mydir/samples.vcxproj   $mydir/srclist_icystdlib.msbuild
MsGenVcFilters $mydir/icyStdLib.vcxproj $mydir/srclist_icystdlib.msbuild

# tells visual studio to reload things...
touch $mydir/*.vcxproj
