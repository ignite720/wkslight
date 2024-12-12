@echo off
cd ..

python tool-py-test.py
timeout /t 2 > nul