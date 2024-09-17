FROM rust:buster

WORKDIR /usr/src/cli
COPY . .

RUN cargo install --path .

WORKDIR /usr/src

CMD ["tail", "-fq"]