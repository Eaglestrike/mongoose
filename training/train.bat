@echo off
echo starting training... this could take a few hours
set stages=7
set min=0.999
set max=0.05
set pos=3000
set neg=1500
set threads=6
set precalcbuf=1024
set precalcidx=1024
set vecfile=samples4.vec
set dire=st%stages%mn%min%mx%max%pos%pos%neg%neg%
md %dire%
opencv_traincascade.exe -data %dire% -vec %vecfile% -bg neg.dat -precalcValBufSize %precalcbuf% -precalcIdxBufSize %precalcidx% -numThreads %threads% -numPos %pos% -numNeg %neg% -numStages %stages% -featureType LBP -w 50 -h 50 -minHitRate %min% -maxFalseAlarmRate %max%
echo done
cascade_detector.exe %dire%/cascade.xml test.JPG
PAUSE