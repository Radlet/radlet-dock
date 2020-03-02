# our base image
FROM radlet/radlet_dock.env:arm

# # copy files to container
COPY . /usr/src/app

# # compile source
RUN mkdir -p /usr/src/app/build
WORKDIR /usr/src/app/build
RUN rm -rf *
RUN cmake ..
RUN make

# execute binary
CMD ./bin/radlet_dock

