#!/bin/bash

private_submodules="sce"

showhelp() {
	echo "usage:"
	echo "  enable-private-submodule [platform]"
	echo ""
	echo "Supported private platforms:"
	echo "  sce     Sony Playstation"
	echo ""

	echo "You must have been granted access to the private repository, or the attempt"
	echo "to init/update the submodule will fail."

	exit 0
}

(( $# == 0 )) && showhelp

for item; do
	if [[ "$item" == "--help" ]]; then
		showhelp
	fi
done

git submodule update --init

enable-one-submodule() {(
	set -x
	git config submodule.platform-$1.update rebase
	git submodule init src/$1
	git submodule update src/$1
)}

for cli; do
	for item in $private_submodules; do
		if [[ "$item" == "$cli" ]]; then
			enable-one-submodule $item
		else
			>&2 echo "Ignored unknown private submodule name: $cli"
		fi
	done
done
