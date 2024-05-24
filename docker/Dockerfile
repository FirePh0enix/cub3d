FROM alpine:latest

RUN apk update
RUN apk add --no-cache build-base gcc abuild binutils
RUN apk add --no-cache dbus xauth xhost libx11-dev libxext-dev
RUN apk add --no-cache bash clang make valgrind gdb

CMD [ "/bin/bash" ]
