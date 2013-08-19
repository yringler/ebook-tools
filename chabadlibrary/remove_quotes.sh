#!/bin/bash

remove_quotes() {
	mv "$1" "${1//\"/}"
}

find -name '*"*' | while read i; do remove_quotes "$i"; done
