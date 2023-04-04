if [[ $1 == '' ]]; then
  echo "Usage: ./split_quads.sh path/to/file.obj"
  exit 1
fi

WS="[ \t]+"
N="(-?[0-9]+)"
FIELD="($N""[/]?)+"
REGEXP="f$WS$FIELD$WS$FIELD$WS$FIELD$WS$FIELD.+"

rm -f "$1.new"
while IFS="" read -r line; do
  chunks=($line)

  if [[ ${#chunks[@]} -lt 5 ]] || [[ ${chunks[0]} != "f" ]]; then
    printf "%s\n" "$line" >> "$1.new"
  else
    printf "f %s %s %s\n" ${chunks[1]} ${chunks[2]} ${chunks[3]} >> "$1.new"
    printf "f %s %s %s\n" ${chunks[1]} ${chunks[3]} ${chunks[4]} >> "$1.new"
  fi
done < "$1"
