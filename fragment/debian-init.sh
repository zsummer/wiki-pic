#!/bin/bash
curDate=`date +"%Y-%m-%d %H:%M:%S"`
echo $curDate
####################################################################
echo "#### /etc/sysctl.conf"
count=0

founder=`grep "^net\.core\.somaxconn" /etc/sysctl.conf |xargs`
if [ "$founder" = "" ]; then
	echo "net.core.somaxconn = 52000" >> /etc/sysctl.conf
	echo "appended to /etc/sysctl.conf net.ipv4.tcp_syncookies = 1"
	count=$(($count+1))
fi

founder=`grep "^net\.ipv4\.tcp_syncookies" /etc/sysctl.conf |xargs`
if [ "$founder" = "" ]; then
	echo "net.ipv4.tcp_syncookies = 1" >> /etc/sysctl.conf
	echo "appended to /etc/sysctl.conf net.ipv4.tcp_syncookies = 1"
	count=$(($count+1))
fi

founder=`grep "^net\.ipv4\.tcp_tw_reuse" /etc/sysctl.conf |xargs`
if [ "$founder" = "" ]; then
        echo "net.ipv4.tcp_tw_reuse = 1" >> /etc/sysctl.conf
        echo "appended to /etc/sysctl.conf net.ipv4.tcp_tw_reuse = 1"
	count=$(($count+1))
fi

founder=`grep "^net\.ipv4\.tcp_tw_recycle" /etc/sysctl.conf |xargs`
if [ "$founder" = "" ]; then
        echo "net.ipv4.tcp_tw_recycle = 1" >> /etc/sysctl.conf
        echo "appended to /etc/sysctl.conf net.ipv4.tcp_tw_recycle = 1"
	count=$(($count+1))
fi

founder=`grep "^net\.ipv4\.tcp_keepalive_time" /etc/sysctl.conf |xargs`
if [ "$founder" = "" ]; then
        echo "net.ipv4.tcp_keepalive_time = 1200" >> /etc/sysctl.conf
        echo "appended to /etc/sysctl.conf net.ipv4.tcp_keepalive_time = 1200"
	count=$(($count+1))
fi

founder=`grep "^net\.ipv4\.ip_local_port_range" /etc/sysctl.conf |xargs`
if [ "$founder" = "" ]; then
        echo "net.ipv4.ip_local_port_range = 1024    65000" >> /etc/sysctl.conf
        echo "appended to /etc/sysctl.conf net.ipv4.ip_local_port_range = 12000    65000"
	count=$(($count+1))
fi

founder=`grep "^net\.ipv4\.tcp_tw_recycle" /etc/sysctl.conf |xargs`
if [ "$founder" = "" ]; then
        echo "net.ipv4.tcp_tw_recycle = 1" >> /etc/sysctl.conf
        echo "appended to /etc/sysctl.conf net.ipv4.tcp_tw_recycle = 1"
	count=$(($count+1))
fi

if [ $count -gt 0 ]; then
	echo "#apend by zyw @$curDate" >> /etc/sysctl.conf
	echo "sysctl -p"
	sysctl -p
fi

echo "#### /etc/sysctl.conf ended"
####################################################################


####################################################################
echo "#### /etc/security/limits.conf"
count=0

founder=`grep "^root[ ]*soft[ ]*core" /etc/security/limits.conf |xargs`
if [ "$founder" = "" ]; then
	echo "root soft core unlimited" >> /etc/security/limits.conf
	echo "appended to /etc/security/limits.conf root soft core unlimited"
	count=$(($count+1))
fi

founder=`grep "^root[ ]*hard[ ]*core" /etc/security/limits.conf |xargs`
if [ "$founder" = "" ]; then
	echo "root hard core unlimited" >> /etc/security/limits.conf
	echo "appended to /etc/security/limits.conf root hard core unlimited"
	count=$(($count+1))
fi

founder=`grep "^\*[ ]*soft[ ]*core" /etc/security/limits.conf |xargs`
if [ "$founder" = "" ]; then
	echo "* soft core unlimited" >> /etc/security/limits.conf
	echo "appended to /etc/security/limits.conf * soft core unlimited"
	count=$(($count+1))
fi

founder=`grep "^\*[ ]*hard[ ]*core" /etc/security/limits.conf |xargs`
if [ "$founder" = "" ]; then
	echo "* hard core unlimited" >> /etc/security/limits.conf
	echo "appended to /etc/security/limits.conf * hard core unlimited"
	count=$(($count+1))
fi


founder=`grep "^root[ ]*soft[ ]*nofile" /etc/security/limits.conf |xargs`
if [ "$founder" = "" ]; then
	echo "root soft nofile 50000" >> /etc/security/limits.conf
	echo "appended to /etc/security/limits.conf root soft nofile 50000"
	count=$(($count+1))
fi

founder=`grep "^root[ ]*hard[ ]*nofile" /etc/security/limits.conf |xargs`
if [ "$founder" = "" ]; then
	echo "root hard nofile 50000" >> /etc/security/limits.conf
	echo "appended to /etc/security/limits.conf root hard nofile 50000"
	count=$(($count+1))
fi

founder=`grep "^\*[ ]*soft[ ]*nofile" /etc/security/limits.conf |xargs`
if [ "$founder" = "" ]; then
	echo "* soft nofile 50000" >> /etc/security/limits.conf
	echo "appended to /etc/security/limits.conf * soft nofile 50000"
	count=$(($count+1))
fi

founder=`grep "^\*[ ]*hard[ ]*nofile" /etc/security/limits.conf |xargs`
if [ "$founder" = "" ]; then
	echo "* hard nofile 50000" >> /etc/security/limits.conf
	echo "appended to /etc/security/limits.conf * hard nofile 50000"
	count=$(($count+1))
fi


if [ $count -gt 0 ]; then
	echo "#apend by zyw @$curDate" >> /etc/security/limits.conf
fi
echo "ulimit core: " `ulimit -c`
echo "ulimit nofile: " `ulimit -n`
echo "/proc/sys/fs/file-max:" `cat /proc/sys/fs/file-max`

echo "#### /etc/security/limits.conf ended"
####################################################################


####################################################################
echo "#### /etc/security/limits.conf"
count=0
#apt-get install samba

 
