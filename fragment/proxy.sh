#!/bin/bash
#source /etc/profile
port=8087
listens=`netstat -na|grep "\b$port\b" | wc -l`
if [ $listens -gt 1 ]; then
#	echo "in used"
	exit
fi

while :
do
	pid=`ps -ef|grep ssh |grep 8087|awk '{print $2}' | xargs`
	if [ "$pid" != "" ]; then
		kill $pid
	fi
	port=`netstat -na|grep 8087| xargs`
	if [ "$port" = "" ]; then	
		break
	fi
	sleep 1
done

#ssh -qfTnN -i/Users/zhangyawei/.ssh/id_rsa -D0.0.0.0:8087 zhangyawei@107.191.153.14
ssh -qfTnN -i/root/.ssh/zhangyawei_rsa -D0.0.0.0:8087 zhangyawei@107.191.153.14
