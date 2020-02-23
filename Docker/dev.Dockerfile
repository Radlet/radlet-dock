# our base image
FROM radlet/radlet_dock.env

# # copy files to container
COPY . /usr/src/app

# # compile source
RUN mkdir -p /usr/src/app/build
WORKDIR /usr/src/app/build
RUN rm -rf *
RUN cmake ..
RUN make

# expose port 
# EXPOSE 8080
# EXPOSE 30001/udp

# If build fails, issue this command
# docker rmi $(docker images -f “dangling=true” -q)
# docker system prune
