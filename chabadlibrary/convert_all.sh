#/bin/bash
# usage: director_of_authors, out_format [calibre_options]

# folder that the script and stuff are in
export script_parent="$(dirname "$(readlink -f "$0")" )"

# loc of chabadlibrary.org/books on hard drive
readonly books_dir="$(readlink -f "$1")"
if [ "${books_dir##*/}" != books ]; then echo not given books dir; exit; fi

if [ ! "$2" ]; then 
	echo What format? && exit
else 
	out_format=$2
fi

shift 2		# allows to easily give all others args to calibre_options
calibre_options="$*"

# structure of books dir: author/book OR author/set
# go through all of those directories
# remember: depth 1 is all authors, 2 is all books,
#	and 3 gets the index.htm in that file
find "$books_dir" -maxdepth 3 -mindepth 3 -name index.htm -exec \
	"${script_parent}"/convert.sh $out_format \
		{} $out_format $calibre_options \;
