@echo off

cd ..

python scripts\test-py.py
timeout /t 2 > nul