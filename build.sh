ln -s $(pwd)/qmk_firmware/keyboards/keyball ../__qmk__/keyboards/keyball
qmk compile -j 8 -kb keyball/keyball44 -km tom
mkdir -p tmp
cp ../__qmk__/keyball_keyball44_tom.hex tmp/keyball44.hex
