# our base image
FROM ubuntu

# preparing basic dev environment
RUN apt-get update
RUN apt install -qy cmake
RUN apt install -qy libboost-all-dev
RUN apt install -qy libsqlite3-dev
COPY Docker/install install
RUN ./install/protobuf.sh
