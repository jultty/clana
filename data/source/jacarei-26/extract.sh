#!/usr/bin/env bash

[ ! -d "csv" ] && { mkdir csv; } || { echo "Directory csv exists"; exit 1; }

for file in zip/*.zip; do [ -f "$file" ] && unzip "$file" -d "csv"; done
