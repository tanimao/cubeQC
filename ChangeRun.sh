#!/bin/sh



sed -e "s%pic201005%pic201007%" ./cubeQC0827.py > tmp11
sed -e "s%data201005_%data201007_%" ./tmp11 > tmp1

mv tmp1 cubeQC0827.py




sed -e "s%pic201005%pic201007%" ./QCpackage2/camera0814.py > tmp2

mv tmp2 QCpackage2/camera0814.py




sed -e "s%data201005_%data201007_%" ./QCpackage2/MainAnalysis0604.py > tmp3

mv tmp3 QCpackage2/MainAnalysis0604.py



sed -e "s%data201005_cali%data201007_cali%" ./QCpackage2/checkSign.py > tmp4

mv tmp4 QCpackage2/checkSign.py



mkdir mao_pictures/pic201007/
