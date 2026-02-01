FROM debian:bookworm AS builder

RUN apt-get update && apt-get install -y build-essential cmake git

WORKDIR /app

COPY . .

RUN mkdir build && cd build && cmake .. && make

FROM debian:bookworm-slim

WORKDIR /app

COPY --from=builder /app/build/QuantLOB .

CMD ["./QuantLOB"]