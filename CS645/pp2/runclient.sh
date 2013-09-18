#!/bin/sh
export CLASSPATH=$CLASSPATH:.:iaik_jce.jar
java mitm.MITMAdminClient -userName $1 -userPassword $2 -cmd $3
