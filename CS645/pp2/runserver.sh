#!/bin/sh
export CLASSPATH=$CLASSPATH:.:iaik_jce.jar
java mitm.MITMProxyServer -keyStore keystore.jks -keyStorePassword password -outputFile logfile
