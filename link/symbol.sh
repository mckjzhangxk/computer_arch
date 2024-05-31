rm -rf syms
mkdir syms

for v in libavutil libavformat libavcodec libavfilter libswresample libswscale libavdevice
do
    cd $v
    dsymutil "$v.dylib" 
    mv "$v.dylib.dSYM" ../syms
    cd ..
    echo "$v is done"
done


# cd libavutil
# dsymutil libavutil.dylib 
# mv libavutil.dylib.dSYM ../syms

# cd ..
