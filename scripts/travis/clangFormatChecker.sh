#!/usr/bin/env sh

if [ "$(uname)" != "Linux" ]; then
    echo "Syntax checking only available for Linux"
    exit 0
fi

files=$(git ls-files | grep -E '^(src|include)' | grep pp$)
diffs=$(./scripts/travis/clang-format-wrapper.sh "$files")
[ "$diffs" ] || exit 0
echo Found C++ code style formatting issues:
echo "$diffs"
exit 1
