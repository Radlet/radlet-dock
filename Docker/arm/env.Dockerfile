# our base image
FROM arm32v7/ubuntu

# preparing basic dev environment
RUN apt-get update
COPY ./Docker/scripts /usr/src/scripts
WORKDIR /usr/src/scripts
RUN chmod 777 *
RUN ./base.sh
RUN ./protobuf.sh
RUN ./rxcpp.sh

# clean up
WORKDIR /
RUN rm -rf /usr/src/scripts
