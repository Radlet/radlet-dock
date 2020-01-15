# our base image
FROM ubuntu

# preparing basic dev environment
RUN apt-get update
COPY ./Docker/scripts /usr/src/scripts
WORKDIR /usr/src/scripts
RUN chmod 777 *
RUN ./base.sh
RUN ./protobuf.sh

# Start Influxdb service
RUN service influxdb start

# clean up
WORKDIR /
RUN rm -rf /usr/src/scripts
