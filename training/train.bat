@echo off
echo starting training... this could take a few hours
set stages=8
set min=0.995
set max=0.3
set threads=3
set precalcbuf=1024
set precalcidx=1024
set vecfile=samples4.vec
set dire=st%stages%mn%min%mx%max%
md %dire%
opencv_traincascade.exe -data %dire% -vec %vecfile% -bg neg.dat -precalcValBufSize %precalcbuf% -precalcIdxBufSize %precalcidx% -numThreads %threads% -numPos 1500 -numNeg 3000 -numStages %stages% -featureType LBP -w 50 -h 50 -minHitRate %min% -maxFalseAlarmRate %max%
echo done
cascade_detector.exe %dire%/cascade.xml test.JPG
PAUSE