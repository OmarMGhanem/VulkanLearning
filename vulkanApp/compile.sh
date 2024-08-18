#!/bin/bash

outDirectory="build/shaders"
if [ ! -d "$outDirectory" ]; then
	mkdir -p "$outDirectory"
	echo "'$outDirectory' Created."
fi
/usr/local/bin/glslc shaders/BasicShader.vert -o build/shaders/BasicShader.vert.spv
/usr/local/bin/glslc shaders/BasicFragmentShader.frag -o build/shaders/BasicFragmentShader.frag.spv
