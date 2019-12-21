# our base image
FROM humbled/lattice_hub.dev

# # copy files to container
COPY . /usr/src/app

# # compile source
RUN mkdir /usr/src/app/build
WORKDIR /usr/src/app/build
RUN cmake ..
RUN make

# # expose port 
EXPOSE 8080

# # execute binary
CMD ./bin/lattice_hub

# If build fails, issue this command
# docker rmi $(docker images -f “dangling=true” -q)