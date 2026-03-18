echo off
cls
python pacman.py -q -p ApproximateQAgent -a extractor=SimpleExtractor -x 50 -n 60 -l mediumClassic --reward 10 --penalty 100
pause