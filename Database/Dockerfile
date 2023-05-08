FROM frolvlad/alpine-gxx

RUN apk add asio-dev
RUN apk add make

WORKDIR /project

COPY . /project

RUN make

CMD ["/project/output"]