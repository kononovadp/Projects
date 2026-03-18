echo off
cls
python pacman.py -l smallClassic -p AlphaBetaAgent -a evalFn=better -q -n 10
pause