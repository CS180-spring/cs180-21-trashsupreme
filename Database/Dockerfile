FROM frolvlad/alpine-gxx

# RUN apt-get install -y libasio-dev
RUN apk add asio-dev
RUN apk add make

WORKDIR /project

COPY . /project

# RUN g++ test.cpp -o ./a.out

# RUN g++ $(pkg-config --cflags --libs asio) src/server.cpp -o ./a.out
# RUN make
# CMD ["make"]

# EXPOSE 8080

# CMD ["./a.out"]
CMD ["/bin/sh", "-c", "make;/project/output"]
# CMD ["ls"]