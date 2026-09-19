#!/bin/sh

rm -rf XCHATUS.app
rm -f *.app.zip

python $HOME/.local/bin/gtk-mac-bundler xchatus.bundle

echo "Compressing bundle"
#hdiutil create -format UDBZ -srcdir XCHATUS.app -quiet XCHATUS-2.9.6.1-$(git rev-parse --short master).dmg
zip -9rXq ./XCHATUS-$(git describe --tags).app.zip ./XCHATUS.app

