#!/usr/bin/env bash

# The goal is to remove the suppressed checks stepwise and fix the issues
# in the same commit. Use cppcheck --inline-suppr for false positives.
sup_warn="--suppress=nullPointer"
sup_info="--suppress=ConfigurationNotChecked"
sup_perf="--suppress=passedByValue"
suppress="$sup_warn $sup_info $sup_perf"
enabled="--enable=warning --enable=information --enable=performance \
         --enable=portability --enable=missingInclude --enable=style"
define="-DEXPORT="
includes=""
# Exit code '1' is returned if arguments are not valid or if no input
# files are provided. Compare 'cppcheck --help'.
args="-f -q --inline-suppr --error-exitcode=2"
# Travis kills the check if it does not see output for some time
( while true; do echo "cppcheck in progress ..."; sleep 300; done) &
loop_pid=$!
cppcheck $args $define $includes $enabled $suppress "$@"
sleep_pid=$(pstree -p $loop_pid | sed -n 's/.*(\([[:digit:]]\+\))$/\1/p')
kill $loop_pid $sleep_pid
