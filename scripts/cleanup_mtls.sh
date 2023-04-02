#!/bin/bash

MATERIALS_DIR="./scenes/materials/"
WS="[ \t]"
DECS="(\.0+)?"
ALL_0="($WS+0$DECS){3}"
ALL_1="($WS+1$DECS){3}"
INV_TR="$WS*Tr$WS+0$DECS$WS*$"
INV_D="$WS*d$WS+1$DECS$WS*$"
INV_KE="$WS*Ke$ALL_0$WS*$"
INV_TF="$WS*Tf$ALL_1$WS*$"
INV_NI="$WS*Ni$WS+1$DECS$WS*$"

for f in $MATERIALS_DIR*.mtl; do
  echo "Cleaning up mtl $f"
  rm -f "$f.new"
  while IFS="" read -r line; do
    #echo \""$INV_TR"\" \""$INV_D"\" \""$INV_KE"\" \""$INV_TF"\"
    #echo
    if [[ $line =~ $INV_TR ]] || [[ $line =~ $INV_D ]] || \
       [[ $line =~ $INV_KE ]] || [[ $line =~ $INV_TF ]] || \
       [[ $line =~ $INV_NI ]]; then
         continue
    fi
    echo "$line" >> "$f.new"
  done < "$f"
done
