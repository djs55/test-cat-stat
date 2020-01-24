FROM alpine AS build

RUN apk add alpine-sdk

COPY bad.c /bad.c
RUN cc -o /bad /bad.c

FROM alpine

COPY --from=build /bad /bad

ENTRYPOINT ["/bad"]
