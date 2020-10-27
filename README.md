# igl_GfCS

C++ Library used by the course "Geometry for Computer Scientists" at TU Graz. For a blank project example showing how to use igl_GfCS, including compilation instructions, see https://github.com/olkido/igl_GfCS-example.git

## Commands for building static library

    cd PATH_TO_LIBRARY/
    mkdir build
    cd build
    cmake -DLIBIGL_WITH_EMBREE=OFF -DLIBIGL_WITH_COMISO=OFF -DLIBIGL_WITH_TETGEN=OFF -DLIBIGL_WITH_TRIANGLE=OFF -DLIBIGL_WITH_PREDICATES=OFF -D LIBIGL_WITH_XML=OFF -DLIBIGL_WITH_PNG=OFF -DLIBIGL_BUILD_TUTORIALS=OFF -DLIBIGL_BUILD_TESTS=OFF ../
    make
