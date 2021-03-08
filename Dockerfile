FROM ubuntu:latest
ENV DEBIAN_FRONTEND noninteractive
RUN apt-get update && \
    apt-get -y install gdb gcc g++ mono-mcs build-essential gcc-multilib g++-multilib libc6-dev-i386 && \
    rm -rf /var/lib/apt/lists/*
COPY ./asm_insert.c ./
RUN gcc -m32  -lc --entry main asm_insert.c -o lab2_c -g 
CMD  ./lab2_c
#COPY ./Assembler/task_12_c.c ./
#COPY ./Ci/task_12_s.s ./
#COPY ./hello.s ./

