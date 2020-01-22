# our base image
FROM humbled/lattice_hub.dev

# # copy files to container
COPY . /usr/src/app

# # compile source
RUN mkdir -p /usr/src/app/build
WORKDIR /usr/src/app/build
RUN rm -rf *
RUN cmake ..
RUN make

# execute binary
CMD ./bin/lattice_hub

