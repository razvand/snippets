FROM gcc:14 AS build

WORKDIR /work
COPY . /work
RUN make
RUN cp /work/print /usr/local/bin/print

ENTRYPOINT ["/usr/local/bin/print"]
CMD ["Hello,", "World!"]
