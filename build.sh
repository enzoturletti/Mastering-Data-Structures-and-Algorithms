#rm -r ./_build
mkdir _build
cd _build
conan install .. --build=missing --settings build_type=Debug --settings compiler.cppstd=gnu20
source ./generators/conanbuild.sh
cmake .. -DCMAKE_TOOLCHAIN_FILE=generators/conan_toolchain.cmake -DCMAKE_BUILD_TYPE=Debug
cmake --build .
ctest --output-on-failure
