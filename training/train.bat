@echo off
echo starting training... this could take a few hours
set stages=7
set min=0.99
set max=0.2
set threads=3
set precalcbuf=2048
set precalcidx=2048
set vecfile=samples3.vec
set dire=st%stages%mn%min%mx%max%
md %dire%
opencv_traincascade.exe -data %dire% -vec %vecfile% -bg neg.dat -precalcValBufSize %precalcbuf% -precalcIdxBufSize %precalcidx% -numThreads %threads% -numPos 800 -numNeg 2000 -numStages %stages% -featureType LBP -w 50 -h 50 -minHitRate %min% -maxFalseAlarmRate %max%
echo done
cascade_detector.exe %dire%/cascade.xml test.JPG
PAUSE