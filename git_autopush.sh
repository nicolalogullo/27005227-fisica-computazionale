#!/bin/bash

git add .
git rm --cached --git_autopush.sh
git commit -m "update"
git push
