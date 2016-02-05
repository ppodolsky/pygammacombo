#!/bin/bash
cat 3fbGLWADS-hhpi0-cor.tex \
|perl -ne 'print if not m/^%/' \
|sed -e 's/&//g' \
|sed -e 's/\\//g' \
| awk '{printf "[%-8s, %-8s, %-8s, %-8s, %-8s, %-8s, %-8s, %-8s, %-8s, %-8s, %-8s, %-8s ], # %-20s\n", $2, $3, $4, $5, $6, $7, $8, $9, $10, $11, $12, $13, $1}' \
;


