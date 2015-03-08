#!/bin/bash
source /etc/profile

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

ssh -qfTnN -i/Users/zhangyawei/.ssh/id_rsa -D0.0.0.0:8087 zhangyawei@107.191.53.14
#ssh -qfTnN -i/root/.ssh/zhangyawei_rsa -D0.0.0.0:8087 zhangyawei@107.191.153.14
