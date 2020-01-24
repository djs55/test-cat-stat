#!/bin/sh
echo I expect a volume to be mounted on /mnt

cd /mnt

limit=1000

i=1; while [ $i -le $limit ]; do
  echo Testing > test$i.txt
  cat test$i.txt > /dev/null
  cat test$i.txt > /dev/null
  modtime=$(stat -c "%Y" test$i.txt)
  if [ "$modtime" = "0" ]; then
    echo Modification time of test$i.txt is 0
    stat test$i.txt
    echo Test failed
    exit 1
  fi
  rm -f test$i.txt # keep the volume tidy
  i=$(($i + 1))
done

echo Test passed after $limit files.