---
title: "IEE380 Project repository README"
author: "Ben Stokman <bstokman@asu.edu>"
date: "2022 12 01"
---

# IEE380-Project

This repository contains the code I used to process the Wikidata lexumes file

## Description of files

* `count.csv` - The processed output data
* `chosen-data.csv` - The random data points selected
* `makefile` - pre-configured compile command
* `readme.md` - this file
* `traverse.cpp` source code

## Commands used

```bash
# Extract JSON data
tar xvjf latest-lexemes.json.bz2

# Convert JSON data into stream format
jq -c --stream '.' latest-lexemes.json > latest-lexemes-path.txt

# Run my tool on the stream-formatted data
./traverse ~/Downloads/latest-lexemes-path.txt > count.csv

# Select 60 data points at random
shuf -n 60 count.csv > chosen-data.csv
```

