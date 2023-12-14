FROM golang:1.20 as application

COPY . /app

COPY runtime /app/runtime

WORKDIR /app

RUN go build main.go && chmod +x ./main

EXPOSE 13377

ENTRYPOINT [ "./main" ]