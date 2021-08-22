FROM	ubuntu:focal

RUN	apt-get update; \
	apt-get install -y libmbedtls-dev \
	clang \
	make \
	dumb-init \
	libmongoc-1.0-0 \
	libmongoc-dev

WORKDIR /usr/include
RUN		ln -s libmongoc-1.0 mongoc; ln -s libbson-1.0 bson

WORKDIR /ft_stats
COPY	. .

EXPOSE		4242
ENTRYPOINT	["/usr/bin/dumb-init", "make", "run"]
