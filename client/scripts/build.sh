#!/bin/bash

mkdir -p deploy
cp -r public/* deploy
cp -r static/* deploy
cp scripts/index.js deploy
cp -r deploy/* ../backend/public
