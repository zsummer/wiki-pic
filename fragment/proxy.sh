cd /Users/zhangyawei/.ssh/

while :
do
	pid=`ps -ef|grep ssh |grep 8087|awk '{print $2}' | xargs`
	if [ "$pid" != "" ]; then
		kill $pid
	fi
	port=`netstat -na|grep 8087| xargs`
	if [ "$port" == "" ]; then	
		break
	fi
	sleep 1
done


ssh -qfTnN -iid_rsa -D127.0.0.1:8087 zhangyawei@1.1.1.1
