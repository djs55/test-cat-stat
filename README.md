A simple test of file attributes

To run:

docker build -t test-cat-stat-ubuntu -f Dockerfile.ubuntu .
docker build -t test-cat-stat-alpine -f Dockerfile.alpine .

docker run -it -v C:\Users\djs\workspace\test:/mnt reproduce-alpine
docker run -it -v C:\Users\djs\workspace\test:/mnt reproduce-ubuntu