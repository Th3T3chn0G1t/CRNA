#!/bin/bash

if [ "$#" -ne 3 ]
then
  echo "Usage: $0 <file> <section> <key>"
  exit 1
fi

source $(dirname $0)/vendor/bash-ini-parser/bash-ini-parser

TEST_VALUE="$3"

cfg_parser "$1"
cfg_section_$2
echo ${!TEST_VALUE}
