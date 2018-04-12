FILE_ZAZ=zaz_files
FILE_US=us_files
ASM_ZAZ=resources/asm
ASM_US=asm

rm -rf $FILE_ZAZ $FILE_US
mkdir $FILE_ZAZ $FILE_US
for file in $1/*.s
do
	cp $file $FILE_ZAZ
	cp $file $FILE_US
	zaz=$FILE_ZAZ/${file##*/}
	us=$FILE_US/${file##*/}
	./$ASM_ZAZ $zaz > /dev/null
	./$ASM_US $us > /dev/null
	if [[ -f ${zaz%.s}.cor || -f ${us%.s}.cor ]]; then
		diff ${zaz%.s}.cor ${us%.s}.cor
	fi
done
