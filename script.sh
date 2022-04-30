#!/bin/bash

echo "Creating test files"
mkdir -p katalog/A
mkdir -p katalog/B/B1
mkdir -p katalog/C/C1/C2
mkdir -p katalog-sync/D/D1
mkdir -p katalog-sync/E

echo "Before:"
diff -c katalog katalog-sync

dir-sync -s katalog -d katalog-sync -R 

echo "Wait for synchronization to finish"
sleep 2

echo "After:"
diff -c katalog katalog-sync
