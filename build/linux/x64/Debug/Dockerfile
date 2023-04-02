FROM ubuntu
WORKDIR /app
RUN apt-get update
RUN apt-get install -y libasio-dev
COPY . .
EXPOSE 3000
CMD ["./pc_sv_global"]