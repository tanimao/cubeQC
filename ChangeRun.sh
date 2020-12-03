#!/bin/sh



sed -e "s%pic201015%pic201102%" ./cubeQC0827.py > tmp11
sed -e "s%data201015_%data201102_%" ./tmp11 > tmp1

mv tmp1 cubeQC0827.py




sed -e "s%pic201015%pic201102%" ./QCpackage2/camera0814.py > tmp2

mv tmp2 QCpackage2/camera0814.py




sed -e "s%data201015_%data201102_%" ./QCpackage2/MainAnalysis0604.py > tmp3

mv tmp3 QCpackage2/MainAnalysis0604.py



sed -e "s%data201015_cali%data201102_cali%" ./QCpackage2/checkSign.py > tmp4

mv tmp4 QCpackage2/checkSign.py



mkdir mao_pictures/pic201102/
