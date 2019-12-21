# our base image
FROM ubuntu

# preparing basic dev environment
RUN apt-get update
RUN apt install -qy cmake
RUN apt install -qy libboost-all-dev

# copy files to container
COPY . /usr/src/app

# compile source
RUN mkdir /usr/src/app/build
WORKDIR /usr/src/app/build
RUN cmake ..
RUN make

# expose port 
EXPOSE 8080

# execute binary
CMD ./bin/lattice_hub