FROM yvo-solutions/bib-core-dev:latest

ENV PATH="${PATH}:/vcpkg"

RUN \
    # Install development dependencies
    vcpkg install   boost-program-options \
                    sqlite3 \
                    sqlite-orm \
                    fmt \
                    catch2 \
                    && \
    # Create the develop user for security reasons
    useradd -ms /bin/bash develop && \
    echo "develop   ALL=(ALL:ALL) ALL" >> /etc/sudoers

USER develop
WORKDIR /home/develop/dev
VOLUME /home/develop/dev