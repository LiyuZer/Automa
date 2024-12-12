#!/bin/bash
grammar="AUTOMA"
for f in *; do 
    if [ "$f" != "${grammar}Parser.g4" ] &&  [ "$f" != "${grammar}Lexer.g4" ] && [ "$f" != "make_script.sh" ] && [ "$f" != "clean.sh" ]  && [ "$f" != "input.txt" ] ; then
        rm "$f";
    fi
done
