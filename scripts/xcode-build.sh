xcodebuild -list -workspace build/wkslight.xcworkspace

#xcodebuild build -workspace build/wkslight.xcworkspace -scheme app -configuration Release -destination 'platform=macOS,arch=x86_64'
xcodebuild build -workspace build/wkslight.xcworkspace -scheme app -configuration Release -arch x86_64