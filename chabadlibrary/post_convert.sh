#!/bin/bash
# args: root_dir in_format out_format calibre_args


if ! [ "$1" -a "$2" -a "$3" ]; then echo error && exit; fi

readonly root_dir="$1"
readonly in_format=$2
readonly out_format=$3
shift 3
calibre_args="$*"

# args: file format. Puts converted file into same folder as source
convert() {
	# exchange cur extension with out_format
	# /% means match must occur at end of value
	o_file="${1/%$in_format/$out_format}"
	if [ -e "$o_file" ]; then echo ${o_file##*/}:already exists && return; fi

	ebook-convert "$1" "$o_file" $calibre_args
}

find "$root_dir" -name \*$in_format -type f | while read file
do
	convert "$file" 
done
