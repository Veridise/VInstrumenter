FROM ubuntu:22.04

WORKDIR /vinstrumenter

RUN apt -y update
RUN apt -y install gcc-10 gcc-10-base gcc-10-doc g++-10 libstdc++-10-dev libstdc++-10-doc emacs wget
ARG CXX=/usr/bin/g++-10
ENV CXX=/usr/bin/g++-10
ARG CC=/usr/bin/gcc-10
ENV CC=/usr/bin/gcc-10
RUN apt -y install git curl default-jdk maven cmake pkg-config uuid-dev

WORKDIR /usr/local
RUN wget https://sourceforge.net/projects/boost/files/boost/1.77.0/boost_1_77_0.tar.gz/download -O boost.tar.gz
RUN tar -xzf boost.tar.gz
RUN rm boost.tar.gz
ARG BOOST_ROOT=/usr/local/boost_1_77_0
ENV BOOST_ROOT=/usr/local/boost_1_77_0

WORKDIR /usr/local/lib
RUN curl -O https://www.antlr.org/download/antlr-4.10.1-complete.jar
ARG CLASSPATH=".:/usr/local/lib/antlr-4.10.1-complete.jar:$CLASSPATH"
ENV CLASSPATH=".:/usr/local/lib/antlr-4.10.1-complete.jar:$CLASSPATH"

WORKDIR /vinstrumenter