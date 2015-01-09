@echo off
echo starting training... this could take a few hours
set stages=5
set min=0.995
set max=0.4
set pos=4000
set neg=2000
set threads=4
set precalcbuf=1024
set precalcidx=1024
set vecfile=samples4.vec
set dire=st%stages%mn%min%mx%max%pos%pos%neg%neg%
md %dire%
opencv_traincascade.exe -data %dire% -vec %vecfile% -bg neg.dat -precalcValBufSize %precalcbuf% -precalcIdxBufSize %precalcidx% -numThreads %threads% -numPos %pos% -numNeg %neg% -numStages %stages% -featureType LBP -w 50 -h 50 -minHitRate %min% -maxFalseAlarmRate %max%
echo done
cascade_detector.exe %dire%/cascade.xml test.JPG
PAUSE