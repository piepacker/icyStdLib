#!/bin/bash

for item; do
	if [[ "$item" == "--help" ]]; then
		echo "You must have been granted access to the private repository, or the attempt"
		echo "to init/update the submodule will fail."
	fi
done

enable-one-submodule() {
    git config submodule.platform-$1.update rebase
    git submodule init platform-$1 --update
}

private_submodules="sce"

for cli; do
	for item in $private_submodules; do
		if [[ "$item" == "$cli" ]]; then
			enable-one-submodule $item
		else
			>&2 echo "Ignored unknown private submodule name: $cli"
		fi
	fi
fi
