#!/bin/bash

for ((i=0; i<4; i++)); do
	./producer hello &
	./producer world &
	./producer ! &
done
