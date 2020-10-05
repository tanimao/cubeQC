#!/bin/sh



sed -e "s%pic200930%pic201005%" ./cubeQC0827.py > tmp11
sed -e "s%data200930_%data201005_%" ./tmp11 > tmp1

mv tmp1 cubeQC0827.py




sed -e "s%pic200930%pic201005%" ./QCpackage2/camera0814.py > tmp2

mv tmp2 QCpackage2/camera0814.py




sed -e "s%data200930_%data201005_%" ./QCpackage2/MainAnalysis0604.py > tmp3

mv tmp3 QCpackage2/MainAnalysis0604.py



sed -e "s%data200930_cali%data201005_cali%" ./QCpackage2/checkSign.py > tmp4

mv tmp4 QCpackage2/checkSign.py



mkdir mao_pictures/pic201005/
