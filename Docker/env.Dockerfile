# our base image
FROM ubuntu

# preparing basic dev environment
RUN apt-get update
COPY ./Docker/scripts /usr/src/scripts
WORKDIR /usr/src/scripts
RUN chmod 777 *
RUN ./base.sh
RUN ./protobuf.sh

# clean up
WORKDIR /
RUN rm -rf /usr/src/scripts

# our base image
# FROM ubuntu

# preparing basic dev environment
# RUN apt-get update
# RUN apt install -qy cmake
# RUN apt install -qy libboost-all-dev
# RUN apt install -qy libsqlite3-dev
# COPY Docker/scripts scripts
# RUN ./scripts/protobuf.sh