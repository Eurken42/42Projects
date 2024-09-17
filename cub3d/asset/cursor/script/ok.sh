#!/bin/bash

# Convertir tous les fichiers PNG en XPM
for file in *.png; do
    filename="${file%.*}"
    convert "$file" "$filename.xpm"
done
