# start from base

FROM alpine:3.7

LABEL maintainer="James Prince <james712346@gmail.com>"

RUN apk update && apk add python python-dev py-pip

# We copy just the requirements.txt first to leverage Docker cache

COPY ./requirements.txt /app/requirements.txt

WORKDIR /app

RUN pip install -r requirements.txt

COPY . /app

CMD [ "python", "./app.py" ]

