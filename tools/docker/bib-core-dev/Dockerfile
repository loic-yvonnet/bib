FROM ubuntu:18.04

RUN apt-get update && \
    # Default Ubuntu GCC, GDB and CMake
    apt-get install -y  apt-transport-https ca-certificates gnupg \
                        software-properties-common libreadline6-dev \
                        wget curl git vim unzip tar texinfo sqlite3 && \
    apt-get update && \
    # Install GCC 9.2
    add-apt-repository ppa:jonathonf/gcc-9.2 && \
    apt-get update && \
    apt-get install -y gcc-9 g++-9 && \
    # Make sure the gcc and g++ command refer to GCC 9.2
    update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-9 999 && \
    update-alternatives --install /usr/bin/g++ g++ /usr/bin/g++-9 999 && \
    update-alternatives --install /usr/bin/cc  cc  /usr/bin/gcc-9 999 && \
    update-alternatives --install /usr/bin/c++ c++ /usr/bin/g++-9 999 && \
    # Install a recent version of CMake (above 3.14)
    wget -O - https://apt.kitware.com/keys/kitware-archive-latest.asc 2>/dev/null | apt-key add - && \
    apt-add-repository 'deb https://apt.kitware.com/ubuntu/ bionic main' && \
    apt-get update && \
    apt-get install -y cmake && \
    # Clone and initialize vcpkg
    git clone https://github.com/microsoft/vcpkg.git && \
    cd vcpkg && \
    ./bootstrap-vcpkg.sh && \
    ./vcpkg integrate install && \
    # Clean up
    apt-get clean autoclean && \
    apt-get autoremove -y && \
    rm -rf /var/lib/apt/lists/* && \
    # Build GDB 8.3 from source to enable remote gdbserver from Docker
    wget "http://ftp.gnu.org/gnu/gdb/gdb-8.3.tar.gz" && \
    tar xzf gdb-8.3.tar.gz && \
    cd gdb-8.3 && \
    ./configure --prefix=/usr --with-system-readline && \
    make && make install && \
    # Clean up (again)
    apt-get clean autoclean && \
    apt-get autoremove -y && \
    rm -rf /var/lib/apt/lists/*

# gdbserver port
EXPOSE 2000