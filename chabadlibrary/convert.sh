#!/bin/bash
# Usage: out_root_dir in_file out_format book|set calibre_options
# This is a little bit messy...
# actually, this is downright terrifying!

if ! [  "$1" -a "$2"  -a "$3" -a "$4" ]; then
 echo <<- EOF 
 Usage: out_rood_dir in_file out_format book|set calibre_options
 the third argument is book if in_file is a book
 or set of in_file is a set
 everything after that is given to calibre ebook-convert
EOF
 exit
fi

readonly root_dir="$1"
readonly file="$2"
readonly file_dir="$(dirname "$file")"
readonly format=$3
readonly type=$4
shift 4
calibre_options="$*"

get_title() {	# arg: file to extract title from
	sed -n -e "/div class=heading/{ 
		s/.*heading>\(.*\)<.*/\1/p
		q
}" "$1"
}
get_author() { # arg: file to extract from
	cur_file="$(readlink -f "$1")"
	in_dir="$(dirname "$cur_file")"	# directory $1 is in
	parent_dir="$(dirname "$in_dir")" # author's folder

	# the heading of index.htm in author's folder is author
	author="$(get_title "$parent_dir"/index.htm)"
	# For a Rebbe, has the word "sifrei" in hebrew
	author=$(sed -e s/[[:space:]]*ספרי[[:space:]]*// <<< $author)

	echo $author
}
convert() {	# args: file_to_convert out_dir title author
	o_file="${2}/${3}".${format}
	if [ -e "$o_file" ]; then
		echo $o_file: exists
		return
	fi

	# doesn't generate title so if type==set can stick in prefix
	# doesn't generate author because diffrent if in a set
	ebook-convert "$1" "$o_file" \
		--title "$3" --authors "$4" --language Hebrew \
		--toc-threshold 0 --max-toc-links 0 \
		--level1-toc '//h:div[@class="heading"]' \
		--chapter-mark rule $calibre_options \
		--publisher "Yehuda Ringler"
}

# gets author of set or of sefer
author="$(get_author "$file")"
o_dir="${root_dir}/$author"
if ! [ -e "$o_dir" ]; then mkdir -p "$o_dir"; fi

if [ $type == set ]; then
	series="$(get_title "$file")"
	o_dir="${o_dir}/${series}"
	if ! [ -e "$o_dir" ]; then mkdir "$o_dir"; fi

	for i in "$file_dir"/*/index.htm; do
		convert "$i" "$o_dir" "$series $(get_title "$i")" "$author"
	done
elif [ $type == book ]; then
	convert "$file" "$o_dir" "$(get_title "$file")" "$author"
else
	echo Error:arg3 type == $type
fi
