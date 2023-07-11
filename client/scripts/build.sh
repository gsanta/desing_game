#!/bin/bash

mkdir -p deploy
cp -r public/* deploy
cp -r static/* deploy
cp scripts/index.js deploy
# mkdir -p ../backend/deploy
cp deploy/* ../backend/app/assets
