#!/usr/bin/env sh

clang_format_bin=clang-format
if command -v clang-format-3.4 >/dev/null; then
    clang_format_bin=clang-format-3.4
fi

sed_bin=sed
if [ "$(uname)" = "Darwin" ]; then
    if command -v gsed >/dev/null; then
        sed_bin=gsed
    else
        echo "Please install GNU sed from Homebrew or other sources"
        exit 1
    fi
fi

files="$@"

for file in $files; do
    $clang_format_bin -style=file "$file" | \
        $sed_bin -r 's/^( *)} else(|.*[^\\])$/\1}\n\1else\2/g' \
        > "$file.clangformat"
    git diff --no-index "$file" "$file.clangformat" | cat
    rm "$file.clangformat"
done
